#include "DxLib.h"
#include <string.h>
#include "define.h"

extern int mode_kaiwa;

int tensuu_niteirudo(char str1[],char str2[],char hyoujou1,char hyoujou2)
{
	int kasantensuu_itti=5;
	int kasantensuu_boinitti=1;
	int tensuu=0;
	int nagasa_str1=0;
	int nagasa_str2=0;
	int i,ii;
	int kiridasisuu=0;
	char kiridasimoji_str1[MAXMOJISUU_kaiwa];
	char kiridasimoji_str2[MAXMOJISUU_kaiwa];
	for (i=0;i<MAXMOJISUU_kaiwa;i++){
		kiridasimoji_str1[i]=0;
		kiridasimoji_str2[i]=0;
	}

	nagasa_str1=strlen(str1);
	nagasa_str2=strlen(str2);

	//切り出し数を増やしながら比較して点数化
	kiridasisuu=0;
	tensuu=0;
	while(1){
		kiridasisuu+=2;
		if (kiridasisuu>=MAXMOJISUU_kaiwa){
			break;
		}
		for (i=0;i<nagasa_str1;i+=2){
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return -1;}
			if (strlen(str1)>=kiridasisuu+i){
				strncpy( kiridasimoji_str1 , str1+i , kiridasisuu );
				//最後に\0を付加
				kiridasimoji_str1[kiridasisuu] = '\0';//取り出した文字数分の最後に'\0'を入れる
				for (ii=0;ii<nagasa_str2;ii+=2){
					if (strlen(str2)>=kiridasisuu+ii){
						strncpy( kiridasimoji_str2 , str2+ii , kiridasisuu );
						//最後に\0を付加
						kiridasimoji_str2[kiridasisuu] = '\0';//取り出した文字数分の最後に'\0'を入れる
						//
						if (strcmp(kiridasimoji_str1,kiridasimoji_str2)==0){//一致した場合
							//一致点数を加算
							tensuu+=kasantensuu_itti*kiridasisuu;
						}else{
							//一致しなかった場合
						}
					}
				}
			}
		}
	}

	//表情が似ているかを判断して点数に反映 int hyoujou1,int hyoujou2
	//ai_hyoujou_konomi[]は、喜ばすのが好きかとか笑わすのが好きかとかの
	//AIごとの性格を決める変数であるので今回は関係ない
	//今回はあくまでどの表情とどの表情に親和性があるかを考慮する
	//親和性があれば点数加算、なければ点数減点
	if (hyoujou1==0){
		if (hyoujou2==0){//喜びと喜び
			tensuu=(int)(tensuu*200/100);
		}
		if (hyoujou2==1){//喜びと怒り
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==2){//喜びと冷笑
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==3){//喜びと励ますしぐさ
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==4){//喜びと真剣な表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==5){//喜びと泣く（悲しみ・痛み）
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==6){//喜びと不安そうな表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==7){//喜びと落ち込む
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==8){//喜びと笑顔
			tensuu=(int)(tensuu*80/100);
		}
		if (hyoujou2==9){//喜びとしかめっ面
			tensuu=(int)(tensuu*0/100);
		}
	}
	if (hyoujou1==1){
		if (hyoujou2==0){//怒りと喜び
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==1){//怒りと怒り
			tensuu=(int)(tensuu*200/100);
		}
		if (hyoujou2==2){//怒りと冷笑
			tensuu=(int)(tensuu*150/100);
		}
		if (hyoujou2==3){//怒りと励ますしぐさ
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==4){//怒りと真剣な表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==5){//怒りと泣く（悲しみ・痛み）
			tensuu=(int)(tensuu*180/100);
		}
		if (hyoujou2==6){//怒りと不安そうな表情
			tensuu=(int)(tensuu*120/100);
		}
		if (hyoujou2==7){//怒りと落ち込む
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==8){//怒りと笑顔
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==9){//怒りとしかめっ面
			tensuu=(int)(tensuu*120/100);
		}
	}
	if (hyoujou1==2){
		if (hyoujou2==0){//冷笑と喜び
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==1){//冷笑と怒り
			tensuu=(int)(tensuu*120/100);
		}
		if (hyoujou2==2){//冷笑と冷笑
			tensuu=(int)(tensuu*200/100);
		}
		if (hyoujou2==3){//冷笑と励ますしぐさ
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==4){//冷笑と真剣な表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==5){//冷笑と泣く（悲しみ・痛み）
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==6){//冷笑と不安そうな表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==7){//冷笑と落ち込む
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==8){//冷笑と笑顔
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==9){//冷笑としかめっ面
			tensuu=(int)(tensuu*120/100);
		}
	}
	if (hyoujou1==3){
		if (hyoujou2==0){//励ますしぐさと喜び
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==1){//励ますしぐさと怒り
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==2){//励ますしぐさと冷笑
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==3){//励ますしぐさと励ますしぐさ
			tensuu=(int)(tensuu*200/100);
		}
		if (hyoujou2==4){//励ますしぐさと真剣な表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==5){//励ますしぐさと泣く（悲しみ・痛み）
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==6){//励ますしぐさと不安そうな表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==7){//励ますしぐさと落ち込む
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==8){//励ますしぐさと笑顔
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==9){//励ますしぐさとしかめっ面
			tensuu=(int)(tensuu*0/100);
		}
	}
	if (hyoujou1==4){
		if (hyoujou2==0){//真剣な表情と喜び
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==1){//真剣な表情と怒り
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==2){//真剣な表情と冷笑
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==3){//真剣な表情と励ますしぐさ
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==4){//真剣な表情と真剣な表情
			tensuu=(int)(tensuu*200/100);
		}
		if (hyoujou2==5){//真剣な表情と泣く（悲しみ・痛み）
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==6){//真剣な表情と不安そうな表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==7){//真剣な表情と落ち込む
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==8){//真剣な表情と笑顔
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==9){//真剣な表情としかめっ面
			tensuu=(int)(tensuu*0/100);
		}
	}
	if (hyoujou1==5){
		if (hyoujou2==0){//泣く（悲しみ・痛み）と喜び
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==1){//泣く（悲しみ・痛み）と怒り
			tensuu=(int)(tensuu*180/100);
		}
		if (hyoujou2==2){//泣く（悲しみ・痛み）と冷笑
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==3){//泣く（悲しみ・痛み）と励ますしぐさ
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==4){//泣く（悲しみ・痛み）と真剣な表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==5){//泣く（悲しみ・痛み）と泣く（悲しみ・痛み）
			tensuu=(int)(tensuu*200/100);
		}
		if (hyoujou2==6){//泣く（悲しみ・痛み）と不安そうな表情
			tensuu=(int)(tensuu*100/100);
		}
		if (hyoujou2==7){//泣く（悲しみ・痛み）と落ち込む
			tensuu=(int)(tensuu*150/100);
		}
		if (hyoujou2==8){//泣く（悲しみ・痛み）と笑顔
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==9){//泣く（悲しみ・痛み）としかめっ面
			tensuu=(int)(tensuu*0/100);
		}
	}
	if (hyoujou1==6){
		if (hyoujou2==0){//不安そうな表情と喜び
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==1){//不安そうな表情と怒り
			tensuu=(int)(tensuu*120/100);
		}
		if (hyoujou2==2){//不安そうな表情と冷笑
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==3){//不安そうな表情と励ますしぐさ
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==4){//不安そうな表情と真剣な表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==5){//不安そうな表情と泣く（悲しみ・痛み）
			tensuu=(int)(tensuu*100/100);
		}
		if (hyoujou2==6){//不安そうな表情と不安そうな表情
			tensuu=(int)(tensuu*200/100);
		}
		if (hyoujou2==7){//不安そうな表情と落ち込む
			tensuu=(int)(tensuu*100/100);
		}
		if (hyoujou2==8){//不安そうな表情と笑顔
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==9){//不安そうな表情としかめっ面
			tensuu=(int)(tensuu*120/100);
		}
	}
	if (hyoujou1==7){
		if (hyoujou2==0){//落ち込むと喜び
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==1){//落ち込むと怒り
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==2){//落ち込むと冷笑
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==3){//落ち込むと励ますしぐさ
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==4){//落ち込むと真剣な表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==5){//落ち込むと泣く（悲しみ・痛み）
			tensuu=(int)(tensuu*120/100);
		}
		if (hyoujou2==6){//落ち込むと不安そうな表情
			tensuu=(int)(tensuu*100/100);
		}
		if (hyoujou2==7){//落ち込むと落ち込む
			tensuu=(int)(tensuu*200/100);
		}
		if (hyoujou2==8){//落ち込むと笑顔
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==9){//落ち込むとしかめっ面
			tensuu=(int)(tensuu*0/100);
		}
	}
	if (hyoujou1==8){
		if (hyoujou2==0){//笑顔と喜び
			tensuu=(int)(tensuu*120/100);
		}
		if (hyoujou2==1){//笑顔と怒り
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==2){//笑顔と冷笑
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==3){//笑顔と励ますしぐさ
			tensuu=(int)(tensuu*80/100);
		}
		if (hyoujou2==4){//笑顔と真剣な表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==5){//笑顔と泣く（悲しみ・痛み）
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==6){//笑顔と不安そうな表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==7){//笑顔と落ち込む
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==8){//笑顔と笑顔
			tensuu=(int)(tensuu*200/100);
		}
		if (hyoujou2==9){//笑顔としかめっ面
			tensuu=(int)(tensuu*0/100);
		}
	}
	if (hyoujou1==9){
		if (hyoujou2==0){//しかめっ面と喜び
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==1){//しかめっ面と怒り
			tensuu=(int)(tensuu*120/100);
		}
		if (hyoujou2==2){//しかめっ面と冷笑
			tensuu=(int)(tensuu*100/100);
		}
		if (hyoujou2==3){//しかめっ面と励ますしぐさ
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==4){//しかめっ面と真剣な表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==5){//しかめっ面と泣く（悲しみ・痛み）
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==6){//しかめっ面と不安そうな表情
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==7){//しかめっ面と落ち込む
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==8){//しかめっ面と笑顔
			tensuu=(int)(tensuu*0/100);
		}
		if (hyoujou2==9){//しかめっ面としかめっ面
			tensuu=(int)(tensuu*200/100);
		}
	}

	return tensuu+1;//0点回避
}

/*							//母音が同じでないか
							//kiridasimoji_str1が「あ」の母音だった場合
							if (strcmp(kiridasimoji_str1,"あ")==0
							|| strcmp(kiridasimoji_str1,"か")==0
							|| strcmp(kiridasimoji_str1,"が")==0
							|| strcmp(kiridasimoji_str1,"さ")==0
							|| strcmp(kiridasimoji_str1,"ざ")==0
							|| strcmp(kiridasimoji_str1,"た")==0
							|| strcmp(kiridasimoji_str1,"だ")==0
							|| strcmp(kiridasimoji_str1,"な")==0
							|| strcmp(kiridasimoji_str1,"は")==0
							|| strcmp(kiridasimoji_str1,"ば")==0
							|| strcmp(kiridasimoji_str1,"ぱ")==0
							|| strcmp(kiridasimoji_str1,"ま")==0
							|| strcmp(kiridasimoji_str1,"や")==0
							|| strcmp(kiridasimoji_str1,"ら")==0
							|| strcmp(kiridasimoji_str1,"わ")==0)
							{
								if (strcmp(kiridasimoji_str2,"あ")==0
								|| strcmp(kiridasimoji_str2,"か")==0
								|| strcmp(kiridasimoji_str2,"が")==0
								|| strcmp(kiridasimoji_str2,"さ")==0
								|| strcmp(kiridasimoji_str2,"ざ")==0
								|| strcmp(kiridasimoji_str2,"た")==0
								|| strcmp(kiridasimoji_str2,"だ")==0
								|| strcmp(kiridasimoji_str2,"な")==0
								|| strcmp(kiridasimoji_str2,"は")==0
								|| strcmp(kiridasimoji_str2,"ば")==0
								|| strcmp(kiridasimoji_str2,"ぱ")==0
								|| strcmp(kiridasimoji_str2,"ま")==0
								|| strcmp(kiridasimoji_str2,"や")==0
								|| strcmp(kiridasimoji_str2,"ら")==0
								|| strcmp(kiridasimoji_str2,"わ")==0)
								{
									//母音一致点数を加算
									tensuu+=kasantensuu_boinitti*kiridasisuu;
								}
							}
							//kiridasimoji_str1が「い」の母音だった場合
							if (strcmp(kiridasimoji_str1,"い")==0
							|| strcmp(kiridasimoji_str1,"き")==0
							|| strcmp(kiridasimoji_str1,"ぎ")==0
							|| strcmp(kiridasimoji_str1,"し")==0
							|| strcmp(kiridasimoji_str1,"じ")==0
							|| strcmp(kiridasimoji_str1,"ち")==0
							|| strcmp(kiridasimoji_str1,"ぢ")==0
							|| strcmp(kiridasimoji_str1,"に")==0
							|| strcmp(kiridasimoji_str1,"ひ")==0
							|| strcmp(kiridasimoji_str1,"び")==0
							|| strcmp(kiridasimoji_str1,"ぴ")==0
							|| strcmp(kiridasimoji_str1,"み")==0
							|| strcmp(kiridasimoji_str1,"い")==0
							|| strcmp(kiridasimoji_str1,"り")==0
							|| strcmp(kiridasimoji_str1,"い")==0)
							{
								if (strcmp(kiridasimoji_str2,"い")==0
								|| strcmp(kiridasimoji_str2,"き")==0
								|| strcmp(kiridasimoji_str2,"ぎ")==0
								|| strcmp(kiridasimoji_str2,"し")==0
								|| strcmp(kiridasimoji_str2,"じ")==0
								|| strcmp(kiridasimoji_str2,"ち")==0
								|| strcmp(kiridasimoji_str2,"ぢ")==0
								|| strcmp(kiridasimoji_str2,"に")==0
								|| strcmp(kiridasimoji_str2,"ひ")==0
								|| strcmp(kiridasimoji_str2,"び")==0
								|| strcmp(kiridasimoji_str2,"ぴ")==0
								|| strcmp(kiridasimoji_str2,"み")==0
								|| strcmp(kiridasimoji_str2,"い")==0
								|| strcmp(kiridasimoji_str2,"り")==0
								|| strcmp(kiridasimoji_str2,"い")==0)
								{
									//母音一致点数を加算
									tensuu+=kasantensuu_boinitti*kiridasisuu;
								}
							}
							//kiridasimoji_str1が「う」の母音だった場合
							if (strcmp(kiridasimoji_str1,"う")==0
							|| strcmp(kiridasimoji_str1,"く")==0
							|| strcmp(kiridasimoji_str1,"ぐ")==0
							|| strcmp(kiridasimoji_str1,"す")==0
							|| strcmp(kiridasimoji_str1,"ず")==0
							|| strcmp(kiridasimoji_str1,"つ")==0
							|| strcmp(kiridasimoji_str1,"づ")==0
							|| strcmp(kiridasimoji_str1,"ぬ")==0
							|| strcmp(kiridasimoji_str1,"ふ")==0
							|| strcmp(kiridasimoji_str1,"ぶ")==0
							|| strcmp(kiridasimoji_str1,"ぷ")==0
							|| strcmp(kiridasimoji_str1,"む")==0
							|| strcmp(kiridasimoji_str1,"ゆ")==0
							|| strcmp(kiridasimoji_str1,"る")==0
							|| strcmp(kiridasimoji_str1,"う")==0)
							{
								if (strcmp(kiridasimoji_str2,"う")==0
								|| strcmp(kiridasimoji_str2,"く")==0
								|| strcmp(kiridasimoji_str2,"ぐ")==0
								|| strcmp(kiridasimoji_str2,"す")==0
								|| strcmp(kiridasimoji_str2,"ず")==0
								|| strcmp(kiridasimoji_str2,"つ")==0
								|| strcmp(kiridasimoji_str2,"づ")==0
								|| strcmp(kiridasimoji_str2,"ぬ")==0
								|| strcmp(kiridasimoji_str2,"ふ")==0
								|| strcmp(kiridasimoji_str2,"ぶ")==0
								|| strcmp(kiridasimoji_str2,"ぷ")==0
								|| strcmp(kiridasimoji_str2,"む")==0
								|| strcmp(kiridasimoji_str2,"ゆ")==0
								|| strcmp(kiridasimoji_str2,"る")==0
								|| strcmp(kiridasimoji_str2,"う")==0)
								{
									//母音一致点数を加算
									tensuu+=kasantensuu_boinitti*kiridasisuu;
								}
							}
							//kiridasimoji_str1が「え」の母音だった場合
							if (strcmp(kiridasimoji_str1,"え")==0
							|| strcmp(kiridasimoji_str1,"け")==0
							|| strcmp(kiridasimoji_str1,"げ")==0
							|| strcmp(kiridasimoji_str1,"せ")==0
							|| strcmp(kiridasimoji_str1,"ぜ")==0
							|| strcmp(kiridasimoji_str1,"て")==0
							|| strcmp(kiridasimoji_str1,"で")==0
							|| strcmp(kiridasimoji_str1,"ね")==0
							|| strcmp(kiridasimoji_str1,"へ")==0
							|| strcmp(kiridasimoji_str1,"べ")==0
							|| strcmp(kiridasimoji_str1,"ぺ")==0
							|| strcmp(kiridasimoji_str1,"め")==0
							|| strcmp(kiridasimoji_str1,"え")==0
							|| strcmp(kiridasimoji_str1,"れ")==0
							|| strcmp(kiridasimoji_str1,"え")==0)
							{
								if (strcmp(kiridasimoji_str2,"え")==0
								|| strcmp(kiridasimoji_str2,"け")==0
								|| strcmp(kiridasimoji_str2,"げ")==0
								|| strcmp(kiridasimoji_str2,"せ")==0
								|| strcmp(kiridasimoji_str2,"ぜ")==0
								|| strcmp(kiridasimoji_str2,"て")==0
								|| strcmp(kiridasimoji_str2,"で")==0
								|| strcmp(kiridasimoji_str2,"ね")==0
								|| strcmp(kiridasimoji_str2,"へ")==0
								|| strcmp(kiridasimoji_str2,"べ")==0
								|| strcmp(kiridasimoji_str2,"ぺ")==0
								|| strcmp(kiridasimoji_str2,"め")==0
								|| strcmp(kiridasimoji_str2,"え")==0
								|| strcmp(kiridasimoji_str2,"れ")==0
								|| strcmp(kiridasimoji_str2,"え")==0)
								{
									//母音一致点数を加算
									tensuu+=kasantensuu_boinitti*kiridasisuu;
								}
							}
							//kiridasimoji_str1が「お」の母音だった場合
							if (strcmp(kiridasimoji_str1,"お")==0
							|| strcmp(kiridasimoji_str1,"こ")==0
							|| strcmp(kiridasimoji_str1,"ご")==0
							|| strcmp(kiridasimoji_str1,"そ")==0
							|| strcmp(kiridasimoji_str1,"ぞ")==0
							|| strcmp(kiridasimoji_str1,"と")==0
							|| strcmp(kiridasimoji_str1,"ど")==0
							|| strcmp(kiridasimoji_str1,"の")==0
							|| strcmp(kiridasimoji_str1,"ほ")==0
							|| strcmp(kiridasimoji_str1,"ぼ")==0
							|| strcmp(kiridasimoji_str1,"ぽ")==0
							|| strcmp(kiridasimoji_str1,"も")==0
							|| strcmp(kiridasimoji_str1,"よ")==0
							|| strcmp(kiridasimoji_str1,"ろ")==0
							|| strcmp(kiridasimoji_str1,"を")==0)
							{
								if (strcmp(kiridasimoji_str2,"お")==0
								|| strcmp(kiridasimoji_str2,"こ")==0
								|| strcmp(kiridasimoji_str2,"ご")==0
								|| strcmp(kiridasimoji_str2,"そ")==0
								|| strcmp(kiridasimoji_str2,"ぞ")==0
								|| strcmp(kiridasimoji_str2,"と")==0
								|| strcmp(kiridasimoji_str2,"ど")==0
								|| strcmp(kiridasimoji_str2,"の")==0
								|| strcmp(kiridasimoji_str2,"ほ")==0
								|| strcmp(kiridasimoji_str2,"ぼ")==0
								|| strcmp(kiridasimoji_str2,"ぽ")==0
								|| strcmp(kiridasimoji_str2,"も")==0
								|| strcmp(kiridasimoji_str2,"よ")==0
								|| strcmp(kiridasimoji_str2,"ろ")==0
								|| strcmp(kiridasimoji_str2,"を")==0)
								{
									//母音一致点数を加算
									tensuu+=kasantensuu_boinitti*kiridasisuu;
								}
*/