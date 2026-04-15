#include "DxLib.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include "define.h"


extern struct tosiyori_data tosiyoridata[TOSIYORISUU];
extern int mode;
extern int year;
extern int month;
extern char namestring[RIKISISUU][12];//(力士IDごとの四股名,全角５文字まで)四股名
extern char hometownstring[SICHOUSONSUU][28];//(2544市町村分,全角13文字まで)出身地
extern struct rikisi_data rikisidata[RIKISISUU];//力士データ用構造体変数708人分用意
extern char heyastring[HEYASUU][12];//(54部屋分,全角５文字まで)相撲部屋
extern char bandukenamestring[10][12];//(10名称分、全角5文字まで)番付名
extern int x1[40];//[]内のリスト番号の左上x座標、初期化はwinmain関数内でする
extern int x2[40];//右下ｘ座標
extern int y1[40];//左上y座標
extern int y2[40];//右下y座標
extern int rx1[40];//[]内の右リスト番号の左上x座標、初期化はwinmain関数内でする
extern int rx2[40];//右下ｘ座標
extern int ry1[40];//左上y座標
extern int ry2[40];//右下y座標
extern char tanshuku_bashostring[6][3];//6場所分1文字づつ
extern void draw_buttonUP(void);//UPボタンの表示ルーチン
extern void draw_buttonUP_mouse(void);//カーソルがのっているとき用のUPボタンの表示ルーチン
extern void buttonUP_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonUP(void);//UPボタンをクリックしたら1を返し、そうでなければ0をかえす
								//さらに、当該ボタン上にマウスカーソルがあれば画像変更もする
extern void draw_buttonDOWN(void);//DOWNボタンの表示ルーチン
extern void draw_buttonDOWN_mouse(void);//カーソルがのっているとき用のDOWNボタンの表示ルーチン
extern void buttonDOWN_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonDOWN(void);//DOWNボタンをクリックしたら1を返し、そうでなければ0をかえす
								//さらに、当該ボタン上にマウスカーソルがあれば画像変更もする
extern void draw_buttonUPFAST(void);//UPボタンの表示ルーチン
extern void draw_buttonUPFAST_mouse(void);//カーソルがのっているとき用のUPボタンの表示ルーチン
extern void buttonUPFAST_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonUPFAST(void);//UPボタンをクリックしたら1を返し、そうでなければ0をかえす
								//さらに、当該ボタン上にマウスカーソルがあれば画像変更もする
extern void draw_buttonDOWNFAST(void);//DOWNボタンの表示ルーチン
extern void draw_buttonDOWNFAST_mouse(void);//カーソルがのっているとき用のDOWNボタンの表示ルーチン
extern void buttonDOWNFAST_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonDOWNFAST(void);//DOWNボタンをクリックしたら1を返し、そうでなければ0をかえす
extern int get_mouseclick(int x1,int y1,int x2,int y2);//座標(x1,y1)と(x2,y2)に囲まれたところで
extern int retire_sentaku_page;


void retirerikisi_rikisiid(int x);
void retirerikisihyoji_rikisiid(int x);


void retirerikisi_rikisiid(int x){
	retirerikisihyoji_rikisiid(x);

		// キー入力待ち(この一文を入れないとうまくいかないみたい)
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		if (get_mouseclick(x2[0]-16,y1[0]-70,x2[0]-16+64,y1[0]-70+16)==1 ){
			return;
		}
		if (retire_sentaku_page>0){
			if (get_mouseclick_buttonUPFAST() == 1){//右リストUPボタンをクリック
				retire_sentaku_page--;
				retirerikisihyoji_rikisiid(x);
				WaitTimer(150);
			}
		}
		if (retire_sentaku_page<9){
			if (get_mouseclick_buttonDOWNFAST() == 1){//右リストDOWNボタンをクリック
				retire_sentaku_page++;
				retirerikisihyoji_rikisiid(x);
				WaitTimer(150);
			}
		}

		// メッセージ処理
		if( ProcessMessage() == -1 )
		{
			mode=1;
			return ;	// エラーが起きたらループから抜ける
		}
		Sleep(1);
	}

}


void retirerikisihyoji_rikisiid(int x)
{
long kyuujou_kirokusuu_long=0;
long tempsize_kyuujou=0;
//int kyuujou_kirokusuu;
long kyuujou_kirokusuu=0;
int kyuujou_rikisiid=0;
int kyuujou_year=0;
int kyuujou_month=0;
char kyuujou_bandukenameid=0;
char kyuujou_bandukesuuji=0;
int kyuujou_yasumi=0;
char kyuujou_kyuujoustring[21];
int kyuujou_yasumi_total=0;
int kyuujou_yasumi_total_makuuti=0;

	char yomikomiokflag=0;
	int i;
	int ii;
	int nowrenban=0;
	int temp_rikisiid=0;
	char temp_list_namestring[20][12];
	char temp_namestring[12];
	char temp_hometownstring[28];
	char temp_heyastring[12];
	char temp_heyaid=0;
	int temp_hatudohyo_year=0;
	char temp_hatudohyo_month=0;
	int temp_retire_year=0;
	int temp_retire_month=0;
	char temp_jikosaiko_bandukenameid=0;
	char temp_jikosaiko_bandukesuuji=0;
	int temp_makuuti_win=0;
	int temp_makuuti_lost=0;
	int temp_kiroku_yuushoukaisuu=0;
	int temp_kinbosisuu=0;
	int temp_shukunshousuu=0;
	int temp_kantoushousuu=0;
	int temp_ginoushousuu=0;
	int temp_wintotal=0;
	int temp_losttotal=0;
	int temp_kiroku_renshou=0;
	int temp_kiroku_renpai=0;
	char temp_kako_yuushouflag[180];
	char temp_kako_bandukehigasiornisi[180];
	char temp_kako_bandukenameid[180];
	char temp_kako_bandukesuuji[180];
	char temp_kako_win[180];
	char temp_kako_lost[180];
	char temp_jikosaiko_tournament=0;
	int temp_yuushoukaisuu_tournament=0;
	int temp_age=0;
	int yearhosei=0;
	char jinbouhyojiflag=0;
	char temp_filename[MAX_PATH];
	for (i=0;i<180;i++){
		temp_kako_yuushouflag[i]=0;
		temp_kako_bandukehigasiornisi[i]=0;
		temp_kako_bandukenameid[i]=0;
		temp_kako_bandukesuuji[i]=0;
		temp_kako_win[i]=0;
		temp_kako_lost[i]=0;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (i=0;i<MAX_PATH;i++){
		temp_filename[i]=0;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (i=0;i<20;i++){
		for (ii=0;ii<12;ii++){
			temp_list_namestring[i][ii]=0;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (i=0;i<12;i++){
		temp_namestring[i]=0;
		temp_heyastring[i]=0;
	}
	for (i=0;i<28;i++){
		temp_hometownstring[i]=0;
	}
	for (i=0;i<21;i++){
		kyuujou_kyuujoustring[i]=0;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//しばらくお待ちください表示
	ClearDrawScreen();
	DrawString(100,300,"表示準備中です",CRWHITE);
	DrawString(100,350,"しばらくお待ちください",CRWHITE);
	ScreenFlip();

	nowrenban=0;
	yomikomiokflag=0;
	//オープンするファイルの選択
	FILE *fp;
	while(nowrenban<RETIREMAXFILESUU){//
		if (yomikomiokflag==0){
			//ファイルオープン
			if (nowrenban==0){
				strcpy(temp_filename,"data/dat/retirerikisi.dat\0");
				fp = fopen(temp_filename,"rb");
				if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return;}
			}else{
				sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",nowrenban+1);
				fp = fopen(temp_filename,"rb");
				if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return;}
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//ここからメイン表示用読み込み
		yomikomiokflag=0;
		if(fread(&temp_rikisiid,sizeof(temp_rikisiid),1,fp)<1){//EOFor読み取り失敗
			nowrenban++;
			fclose(fp);
		}else{
			yomikomiokflag=1;
			fread(temp_namestring,sizeof(namestring[rikisidata[0].nameid]),1,fp);
			fread(temp_hometownstring,sizeof(hometownstring[rikisidata[0].hometownid]),1,fp);
			fread(temp_heyastring,sizeof(heyastring[rikisidata[0].heyaid]),1,fp);
			fread(&temp_heyaid,sizeof(rikisidata[0].heyaid),1,fp);
			fread(&temp_hatudohyo_year,sizeof(rikisidata[0].hatudohyo_year),1,fp);
			fread(&temp_hatudohyo_month,sizeof(rikisidata[0].hatudohyo_month),1,fp);
			fread(&temp_retire_year,sizeof(year),1,fp);
			fread(&temp_retire_month,sizeof(month),1,fp);
			fread(&temp_jikosaiko_bandukenameid,sizeof(rikisidata[0].jikosaiko_bandukenameid),1,fp);
			fread(&temp_jikosaiko_bandukesuuji,sizeof(rikisidata[0].jikosaiko_bandukesuuji),1,fp);
			fread(&temp_makuuti_win,sizeof(rikisidata[0].makuuti_win),1,fp);
			fread(&temp_makuuti_lost,sizeof(rikisidata[0].makuuti_lost),1,fp);
			fread(&temp_kiroku_yuushoukaisuu,sizeof(rikisidata[0].kiroku_yuushoukaisuu),1,fp);
			fread(&temp_kinbosisuu,sizeof(rikisidata[0].kinbosisuu),1,fp);
			fread(&temp_shukunshousuu,sizeof(rikisidata[0].shukunshousuu),1,fp);
			fread(&temp_kantoushousuu,sizeof(rikisidata[0].kantoushousuu),1,fp);
			fread(&temp_ginoushousuu,sizeof(rikisidata[0].ginoushousuu),1,fp);
			fread(&temp_wintotal,sizeof(rikisidata[0].wintotal),1,fp);
			fread(&temp_losttotal,sizeof(rikisidata[0].losttotal),1,fp);
			fread(&temp_kiroku_renshou,sizeof(rikisidata[0].kiroku_renshou),1,fp);
			fread(&temp_kiroku_renpai,sizeof(rikisidata[0].kiroku_renpai),1,fp);
			fread(temp_kako_yuushouflag,sizeof(rikisidata[0].kako_yuushouflag),1,fp);
			fread(temp_kako_bandukehigasiornisi,sizeof(rikisidata[0].kako_bandukehigasiornisi),1,fp);
			fread(temp_kako_bandukenameid,sizeof(rikisidata[0].kako_bandukenameid),1,fp);
			fread(temp_kako_bandukesuuji,sizeof(rikisidata[0].kako_bandukesuuji),1,fp);
			fread(temp_kako_win,sizeof(rikisidata[0].kako_win),1,fp);
			fread(temp_kako_lost,sizeof(rikisidata[0].kako_lost),1,fp);
			fread(&temp_jikosaiko_tournament,sizeof(rikisidata[0].jikosaiko_tournament),1,fp);
			fread(&temp_yuushoukaisuu_tournament,sizeof(rikisidata[0].yuushoukaisuu_tournament),1,fp);
			fread(&temp_age,sizeof(rikisidata[0].age),1,fp);
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (temp_rikisiid==x && yomikomiokflag==1){
			//ファイルクローズ
			fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	///////////休場数読込//////////////////////
	strcpy(temp_filename,"data/dat/r_kyuujou_index.dat");
	fp = fopen(temp_filename,"rb");
	if( fp == NULL ){
		//ここにエラー処理
		ClearDrawScreen();
		DrawFormatString(187,369,CRWHITE,"%sのオープン失敗",temp_filename);
		ScreenFlip();
		WaitKey();
		mode=1;return ;
	}else{
		kyuujou_kirokusuu_long=0;
		while(1){
			if (fread(&kyuujou_rikisiid,sizeof(int),1,fp)<1){
				break;
			}
			if (kyuujou_rikisiid==temp_rikisiid){
				break;
			}
			fread(&kyuujou_kirokusuu,sizeof(int),1,fp);
			kyuujou_kirokusuu_long+=kyuujou_kirokusuu;
			//if( ProcessMessage() == -1 ){mode=1;return ;}
		}
	}
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}

	tempsize_kyuujou=sizeof(int)*4+sizeof(char)*2+sizeof(kyuujou_kyuujoustring);

	strcpy(temp_filename,"data/dat/r_kyuujou.dat");
	fp = fopen(temp_filename,"rb");
	if( fp == NULL ){
		//ここにエラー処理
		ClearDrawScreen();
		DrawFormatString(187,369,CRWHITE,"%sのオープン失敗",temp_filename);
		ScreenFlip();
		WaitKey();
		mode=1;return ;
	}else{
		fseek(fp,tempsize_kyuujou*kyuujou_kirokusuu_long,SEEK_SET );
		kyuujou_yasumi_total=0;
		kyuujou_yasumi_total_makuuti=0;
		while(1){
			if (fread(&kyuujou_rikisiid,sizeof(int),1,fp)<1){
				break;
			}
			if (kyuujou_rikisiid!=temp_rikisiid){
				break;
			}
			fread(&kyuujou_year,sizeof(int),1,fp);
			fread(&kyuujou_month,sizeof(int),1,fp);
			fread(&kyuujou_bandukenameid,sizeof(char),1,fp);
			fread(&kyuujou_bandukesuuji,sizeof(char),1,fp);
			fread(&kyuujou_yasumi,sizeof(int),1,fp);
			fread(kyuujou_kyuujoustring,sizeof(kyuujou_kyuujoustring),1,fp);
			kyuujou_yasumi_total+=kyuujou_yasumi;
			if (kyuujou_bandukenameid<=4){
				kyuujou_yasumi_total_makuuti+=kyuujou_yasumi;
			}
			if( ProcessMessage() == -1 ){mode=1;return ;}
		}
	}
	fclose(fp);
	/////////休場数読込ここまで//////////////////




			ClearDrawScreen();
			DrawBox(0,0,640,480,CRLINE,TRUE);//大枠描画
			DrawBox(3,3,637,477,CRBACK,TRUE);
			DrawBox(0,21,187,480,CRLINE,TRUE);
			DrawBox(3,24,184,477,CRBACK,TRUE);
			DrawBox(184,21,640,369,CRLINE,TRUE);
			DrawBox(187,24,637,366,CRBACK,TRUE);
			DrawBox(184,366,640,480,CRLINE,TRUE);
			DrawBox(187,369,637,477,CRBACK,TRUE);
			DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分
			DrawBox(3,76,183,475,CRTAB,TRUE);

			//タブ表示
			/*DrawBox(3,76,183,475,CRTAB,TRUE);
			if (retire_sentaku_category==0){//全幕内経験者+自部屋表示
				DrawBox(3,60,62,76,CRTAB,TRUE);
			}else if(retire_sentaku_category==1){//自部屋表示
				DrawBox(63,60,126,76,CRTAB,TRUE);
			}else{//最高位順表示
				DrawBox(127,60,183,76,CRTAB,TRUE);
			}*/

				//右リスト枠表示
				DrawBox(464,76,639,367,CRKEIJIBANOFF,FALSE);//右リスト部分
				DrawBox(463,75,639,367,CRKEIJIBANOFF,FALSE);//右リスト部分
					
			//if (retire_sentaku_category==0 || (retire_sentaku_category==1 && retiresuu_jiheya>0) || (retire_sentaku_category==2 && retiresuu_saikoui>0)){

					//DrawString(187,450,"ページ指定ジャンプ",CRGREEN);//ver2.39での変更（追加）
					DrawFormatString(187,24,CRWHITE,"%s",
					temp_namestring);
					DrawFormatString(187,44,CRWHITE,"%s出身 %s部屋",
					temp_hometownstring,
					temp_heyastring);
					DrawFormatString(187,64,CRWHITE,"%4d年%d月初土俵  %4d年%d月引退",
					temp_hatudohyo_year,
					temp_hatudohyo_month,
					temp_retire_year,
					temp_retire_month);
					DrawFormatString(187,84,CRWHITE,"引退年齢 %d才",
					temp_age);
					DrawString(187,104,"最高位",CRWHITE);
					if (temp_jikosaiko_bandukesuuji>1 ){
						DrawFormatString(187+112,104,CRWHITE,"%s%d枚目",
						bandukenamestring[temp_jikosaiko_bandukenameid],
						temp_jikosaiko_bandukesuuji
						);
					}else if (temp_jikosaiko_bandukesuuji==1 ){
						DrawFormatString(187+112,104,CRWHITE,"%s筆頭",
						bandukenamestring[temp_jikosaiko_bandukenameid]
						);
					}else{
						DrawFormatString(187+112,104,CRWHITE,"%s",
						bandukenamestring[temp_jikosaiko_bandukenameid]
						);
					}
		DrawFormatString(187,124,CRWHITE,"通算 %d勝%d敗%d休(.%d)",
		temp_wintotal,
		temp_losttotal,
		kyuujou_yasumi_total,
		(int)(temp_wintotal*1000/(temp_wintotal+temp_losttotal)));
		if (temp_makuuti_win+temp_makuuti_lost<1){
			DrawFormatString(187,144,CRWHITE,"幕内通算 %d勝%d敗%d休(.000)",
			temp_makuuti_win,
			temp_makuuti_lost,
			kyuujou_yasumi_total_makuuti);
		}else{
			DrawFormatString(187,144,CRWHITE,"幕内通算 %d勝%d敗%d休(.%d)",
			temp_makuuti_win,
			temp_makuuti_lost,
			kyuujou_yasumi_total_makuuti,
			(int)(temp_makuuti_win*1000/(temp_makuuti_win+temp_makuuti_lost)));
		}
		DrawFormatString(187,164,CRWHITE,"幕内在位 %d場所",
		(int)((temp_makuuti_win+temp_makuuti_lost+kyuujou_yasumi_total_makuuti)/15));
					DrawFormatString(187,184,CRWHITE,"幕内最高優勝 %d回",
					temp_kiroku_yuushoukaisuu);
					DrawFormatString(187,204,CRWHITE,"金星数 %d個",
					temp_kinbosisuu);
					DrawFormatString(187,224,CRWHITE,"殊勲賞受賞 %d回",
					temp_shukunshousuu);
					DrawFormatString(187,244,CRWHITE,"敢闘賞受賞 %d回",
					temp_kantoushousuu);
					DrawFormatString(187,264,CRWHITE,"技能賞受賞 %d回",
					temp_ginoushousuu);
					DrawFormatString(187,284,CRWHITE,"最多連勝 %d連勝",
					temp_kiroku_renshou);
					DrawFormatString(187,304,CRWHITE,"最多連敗 %d連敗",
					temp_kiroku_renpai);
					DrawString(187,324,"ガチンコ杯最高",CRWHITE);
					if (temp_jikosaiko_tournament==0){
						DrawString(187+128,324,"未出場",CRWHITE);
					}else if (temp_jikosaiko_tournament<=6){
						DrawFormatString(187+128,324,CRWHITE,"%6d回戦進出",temp_jikosaiko_tournament);
					}else if(temp_jikosaiko_tournament==7){
						DrawString(187+128,324,"準々決勝進出",CRWHITE);
					}else if(temp_jikosaiko_tournament==8){
						DrawString(187+128,324,"準決勝進出",CRWHITE);
					}else if(temp_jikosaiko_tournament==9){
						DrawString(187+128,324,"決勝進出",CRWHITE);
					}else{
						DrawFormatString(187+128,324,CRWHITE,"優勝%6d回",temp_yuushoukaisuu_tournament);
					}
					//DrawFormatString(187,344,CRWHITE,"ID %d",temp_rikisiid);
					//廃業してなかったらIDとともに人望を表示
					jinbouhyojiflag=0;
					for (i=0;i<TOSIYORISUU;i++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}
						if (tosiyoridata[i].rikisiid==temp_rikisiid && tosiyoridata[i].shozokuheyaid!=-1){
							DrawFormatString(187,344,CRWHITE,"ID %d  人望 %d",temp_rikisiid,tosiyoridata[i].jinbou);
							jinbouhyojiflag=1;
							break;
						}
					}
					if (jinbouhyojiflag==0){
						DrawFormatString(187,344,CRWHITE,"ID %d  人望なし(廃業)",temp_rikisiid);
					}

			//}
			SetFontSize( 12 ) ;
			if( ProcessMessage() == -1 ){mode=1;return ;}
			/*DrawString(230,5,"幕内経験者またはあなたの部屋の引退力士",CRWHITE);
			DrawString(3+4,60+3,"引退順",CRWHITE);
			DrawString(3+4+60,60+3,"自部屋",CRWHITE);
			DrawString(3+4+70+50,60+3,"最高位順",CRWHITE);
			if (retire_sentaku_category==0){//全部表示
				DrawFormatString(3,78,CRBLACK,"%d／%dページ",all_retiresentaku_page+1,(int)((retiresuu_total+19)/20));
			}
			if (retire_sentaku_category==1 && retiresuu_jiheya>0){//自部屋表示
				DrawFormatString(3,78,CRBLACK,"%d／%dページ",jiheya_retiresentaku_page+1,(int)((retiresuu_jiheya+19)/20));
			}
			if (retire_sentaku_category==2 && retiresuu_saikoui>0){//最高位順表示
				DrawFormatString(3,78,CRBLACK,"%d／%dページ",saikoui_retiresentaku_page+1,(int)((retiresuu_saikoui+19)/20));
			}*/
			//if (retire_sentaku_category==0 || (retire_sentaku_category==1 && retiresuu_jiheya>0) || (retire_sentaku_category==2 && retiresuu_saikoui>0)){
					yearhosei=(temp_retire_year*12+temp_retire_month);
					for (i=0;i<18;i++){
						if (temp_kako_bandukehigasiornisi[i+retire_sentaku_page*18]!=-1){
							DrawFormatString(rx1[i*2+4]-10,ry1[i*2+4],CRWHITE,"%02d%s",
							((int)((yearhosei-(i+retire_sentaku_page*18)*2)/12))%100,tanshuku_bashostring[((int)((temp_retire_month+3)/2)-i+4+18)%6]);
							if (temp_kako_bandukehigasiornisi[i+retire_sentaku_page*18]==1 ){
								DrawString(rx1[i*2+4]+20,ry1[i*2+4],"東",CRWHITE);
							}else{
								DrawString(rx1[i*2+4]+20,ry1[i*2+4],"西",CRWHITE);
							}
							if (temp_kako_bandukesuuji[i+retire_sentaku_page*18]!=0){
								DrawFormatString(rx1[i*2+4]+32,ry1[i*2+4],CRWHITE,"%s%3d",
								bandukenamestring[temp_kako_bandukenameid[i+retire_sentaku_page*18]],
								temp_kako_bandukesuuji[i+retire_sentaku_page*18]);
							}else{
								DrawFormatString(rx1[i*2+4]+32,ry1[i*2+4],CRWHITE,"%s",
								bandukenamestring[temp_kako_bandukenameid[i+retire_sentaku_page*18]]);
							}
				if (temp_kako_bandukenameid[i+retire_sentaku_page*18]<=5 && (temp_kako_win[i+retire_sentaku_page*18]+temp_kako_lost[i+retire_sentaku_page*18])<15){
					DrawFormatString(rx1[i*2+5]+22,ry1[i*2+5],CRGREEN,"%2d－%2d-%d",
					temp_kako_win[i+retire_sentaku_page*18],temp_kako_lost[i+retire_sentaku_page*18],15-(temp_kako_win[i+retire_sentaku_page*18]+temp_kako_lost[i+retire_sentaku_page*18]));
				}else if (temp_kako_bandukenameid[i+retire_sentaku_page*18]>5 && (temp_kako_win[i+retire_sentaku_page*18]+temp_kako_lost[i+retire_sentaku_page*18])<7){
					DrawFormatString(rx1[i*2+5]+22,ry1[i*2+5],CRGREEN,"%2d－%2d-%d",
					temp_kako_win[i+retire_sentaku_page*18],temp_kako_lost[i+retire_sentaku_page*18],7-(temp_kako_win[i+retire_sentaku_page*18]+temp_kako_lost[i+retire_sentaku_page*18]));
				}else{
					DrawFormatString(rx1[i*2+5]+22,ry1[i*2+5],CRGREEN,"%2d－%2d",
					temp_kako_win[i+retire_sentaku_page*18],temp_kako_lost[i+retire_sentaku_page*18]);
				}
							if (temp_kako_yuushouflag[i+retire_sentaku_page*18]==1){
								DrawString(622,ry1[i*2+5],"優",CRWHITE);
							}
						}
					}
					DrawFormatString(rx1[2]+76,ry1[2]+3,CRWHITE,"%2d/%d頁",
					retire_sentaku_page+1,
					(int)(((temp_retire_year*12+temp_retire_month)-(temp_hatudohyo_year*12+temp_hatudohyo_month)+2)/2/18)+1
					);
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					//左リスト表示
					/*if (retire_sentaku_category==0){//全部表示
						DrawBox(x1[(retirerikisisentaku_num_all%20)*2],y1[(retirerikisisentaku_num_all%20)*2],x1[(retirerikisisentaku_num_all%20)*2]+180,y1[(retirerikisisentaku_num_all%20)*2]+17,CRKEIJIBANON,TRUE);//クリックしたところを強調
						for(i=0;i<20;i++){
							if (i+all_retiresentaku_page*20<retiresuu_total){
								DrawFormatString(x1[i*2],y1[i*2],CRBLACK,"%s",temp_list_namestring[i]);
							}
						}
					}
					if (retire_sentaku_category==1 && retiresuu_jiheya>0){//自部屋表示
						DrawBox(x1[(retirerikisisentaku_num_jiheya%20)*2],y1[(retirerikisisentaku_num_jiheya%20)*2],x1[(retirerikisisentaku_num_jiheya%20)*2]+180,y1[(retirerikisisentaku_num_jiheya%20)*2]+17,CRKEIJIBANON,TRUE);//クリックしたところを強調
						for(i=0;i<20;i++){
							if (i+jiheya_retiresentaku_page*20<retiresuu_jiheya){
								DrawFormatString(x1[i*2],y1[i*2],CRBLACK,"%s",temp_list_namestring[i]);
							}
						}
					}
					if (retire_sentaku_category==2 && retiresuu_saikoui>0){//最高位順表示
						DrawBox(x1[(retirerikisisentaku_num_saikoui%20)*2],y1[(retirerikisisentaku_num_saikoui%20)*2],x1[(retirerikisisentaku_num_saikoui%20)*2]+180,y1[(retirerikisisentaku_num_saikoui%20)*2]+17,CRKEIJIBANON,TRUE);//クリックしたところを強調
						for(i=0;i<20;i++){
							if (i+saikoui_retiresentaku_page*20<retiresuu_saikoui){
								DrawFormatString(x1[i*2],y1[i*2],CRBLACK,"%s",temp_list_namestring[i]);
							}
						}
					}*/

			//}

			//draw_buttonkensakuLEFT();
			draw_buttonUPFAST();
			draw_buttonDOWNFAST();
			//draw_buttonUP();
			//draw_buttonDOWN();

			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			SetFontSize( 16 ) ;
			if( ProcessMessage() == -1 ){mode=1;return ;}


			DrawString(x2[0]-16,y1[0]-70,"戻る",CRGREEN);

			DrawString(187,369,"ご面倒かけますが、さらに詳しい情報は",CRWHITE);
			DrawFormatString(187,369+16,CRWHITE,"ID %d %s部屋の相撲部屋画面の",temp_heyaid,heyastring[temp_heyaid]);
			DrawString(187,369+32,"「引退力士表示」をクリック願います",CRWHITE);

			ScreenFlip();
			break;
		}

	}//ループ終端

	return;


}