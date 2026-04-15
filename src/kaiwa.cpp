#include "DxLib.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include "define.h"


extern char katati_kaiwa;//0→人間と力士AIの会話、1→力士AIと力士AIの会話
extern int nextspeaking_heya(int now_hanasite,int heyaid);//現在のid_hanasiteを除いて次の話し手(聞き手)を決定させるルーチン
extern char str_hyoujou[HYOUJOUSHURUISUU][21];

/////////////////////////////////
extern int rikisisentaku_id;
extern int day;
extern char kyuujouflag[RIKISISUU];//1で休場
extern char kyuujoumode;
extern int kyuujoukonbasho[RIKISISUU][15];//今場所の何日目に休場したかrikisidata[].winkonbasho[]みたいなもん
extern struct rikisi_data rikisidata[RIKISISUU];//力士データ用構造体変数708人分用意
//extern rikisidata[RIKISISUU];//力士データ用構造体変数708人分用意


/////////////////////////////////

extern struct ai_data aikaiwadata[AISUU];//AIごとの個性のデータ
extern struct human_data humankaiwadata[HUMANSUU];//AIごとの個性のデータ
extern struct wrikisi_data wrikisidata[1];//話題対象力士データ


//話題フラグ
//状況フラグ
extern char day_kaiwa;//場所中の何日目か
extern char jflag;//会話の周りの状況フラグ
			//0→ごくごく一般的な会話状況、2～10はランダム天気
			//11～15→ユーザー定義
			//1→小相撲関連な会話状況→aikaiwadata[].sumoflagのフラグ状況を参照する

extern short int id_hanasite;//話し手
extern short int id_kikite;//聞き手

extern char type_hanasite;//話し手の言語タイプ
extern char type_kikite;//聞き手の言語タイプ

extern char studyflag;
extern int kaiwacount;

extern char kako_str[KAKOHYOJISUU][MAXMOJISUU_kaiwa];//表示用
extern char kako_hyoujounum[KAKOHYOJISUU];
extern int kako_id_hanasite[KAKOHYOJISUU];//AI同志の会話の表示用

extern int mode_kaiwa;//1：終了フラグ、2：ゲーム準備処理完了フラグ、
		//9:会話入力からやり直し
		//10:会話入力待ち
		//15:会話入力完了
		//20:表情入力待ち
		//25:表情入力完了
extern int get_mouseclick(int x1,int y1,int x2,int y2);//座標(x1,y1)と(x2,y2)に囲まれたところで
												//クリックしたかどうか
												//当該座標上でクリックしたなら１を返し、
												//そうでなければ、0を返す
extern int MouseInput ;//マウス入力用
extern int MouseX,MouseY;//マウス座標取得用
extern int FontHandle16;
extern int FontHandle12;
extern long maxfilesize;//本番用
extern int filesuu_kaiwadata;
extern char kaiwabundanflag;//ゲーム立ち上げ後は前のやり取りとはつながらないので、それをわからせるため
extern char kaesikaiwabundanflag;
extern char inputstr[MAXMOJISUU_kaiwa] ;//人間の発言
extern char kaesistr[MAXMOJISUU_kaiwa];//AIの発言
extern char kaiwastr[MAXMOJISUU_kaiwa];//記録する際の発言
extern char hyoujounum;
extern char kaesihyoujounum;
extern int ai_hyoujou_konomi[HYOUJOUSHURUISUU];//AIは相手のどんな表情を好む
										//のかの表情ごとの好み度合い、表情の種類分
										//AIの性格をこれで変えられる
extern char oumugaesiflag;

extern void kaiwa_main_hyoji(void);

extern int tensuu_niteirudo(char str1[],char str2[],char hyoujou1,char hyoujou2);
extern int check_hiragana(char checkstr[]);
extern int CheckHitKey_test(int a);
extern long Getfilesize(char name[]);//返り値が0は存在するけどファイルサイズ0、-1→エラー、-2→存在無し



void kaiwa(void){
	long size_1data=sizeof(short int)*1+sizeof(char)*9+sizeof(char)*MAXMOJISUU_kaiwa;
	char temp_char=0;//ダミー書込み用
	char lastdatazurasisuu=0;
	int chouseipoint=0;//AIの発言を決定する際のdameflagの代わりの減点方式で使用
	int chouseipoint_warizan=0;//AIの発言を決定する際のdameflagの代わりの減点方式で使用
	int kaeri=0;
	int i,ii,iii,iiii;
	long filesize_kaiwadata[MAXFILESUU];
	char temp_filename[MAX_PATH];
	char String[ 256 ] ;
    int InputHandle =0;
	long fpendflag=0;
	long seekendflag=0;
	int yomikomicount=0;
	char *ichi;
	int tensuu=0;
	char okikaeflag=0;
	char okikaestr[MAXMOJISUU_kaiwa];
int sounyuukaisuu=0;
int okikaekaisuu=0;
	for (i=0;i<256;i++){
		String[i]=0;
	}
	for (i=0;i<MAXMOJISUU_kaiwa;i++){
		inputstr[i]=0;
		okikaestr[i]=0;
	}
	for (i=0;i<MAXMOJISUU_kaiwa;i++){
		kaesistr[i]=0;
	}
	for (i=0;i<MAXFILESUU;i++){
		filesize_kaiwadata[i]=0;
	}
	for (i=0;i<MAX_PATH;i++){
		temp_filename[i]=0;
	}

	FILE *fp;
while(1){
	if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
	Sleep(1);

/*
////////////////////////////////////////////////////////////////////
///////////////////////////debug////////////////////////////////////
{
int i_debug;
unsigned char temp_char=0;//右シフト符号対策
ClearDrawScreen();
DrawFormatString(20,0,CRGREEN,"ループ冒頭 id_hanasite=%d,id_kikite=%d\n",id_hanasite,id_kikite);
DrawFormatString(20,32,CRGREEN,"type_hanasite=%d,type_kikite=%d\n",type_hanasite,type_kikite);
//DrawFormatString(20,48,CRGREEN,"day_kaiwa=%d(何日目-1の値)\n",day_kaiwa);
//DrawFormatString(20,48,CRGREEN,"%d日目\n",day_kaiwa+1);
if ((wrikisidata[0].sumoflag & b10000000)==b10000000){
	DrawString(20,48+16,"sumoflag1=1 今日勝った\n",CRGREEN);
}else{
	DrawString(20,48+16,"sumoflag1=0 今日勝ってはいない\n",CRGREEN);
}
if ((wrikisidata[0].sumoflag & b01000000)==b01000000){
	DrawString(20,48+32,"sumoflag2=1 今日負けた\n",CRGREEN);
}else{
	DrawString(20,48+32,"sumoflag2=0 今日負けてはいない\n",CRGREEN);
}
if ((wrikisidata[0].sumoflag & b00100000)==b00100000){
	DrawString(20,48+48,"sumoflag3=1 休場中\n",CRGREEN);
}else{
	DrawString(20,48+48,"sumoflag3=0 休場中ではない\n",CRGREEN);
}
if ((wrikisidata[0].sumoflag & b00010000)==b00010000){
	DrawString(20,48+64,"sumoflag4=1 勝ち注射した\n",CRGREEN);
}else{
	DrawString(20,48+64,"sumoflag4=0 勝ち注射してない\n",CRGREEN);
}
if ((wrikisidata[0].sumoflag & b00001000)==b00001000){
	DrawString(20,48+80,"sumoflag5=1 負け注射した\n",CRGREEN);
}else{
	DrawString(20,48+80,"sumoflag5=0 負け注射してない\n",CRGREEN);
}
temp_char=wrikisidata[0].suu_winlost & 0xf0;
temp_char=temp_char>>4;
DrawFormatString(20,48+96,CRGREEN,"win=%d\n",temp_char);
DrawFormatString(20,48+112,CRGREEN,"lost=%d\n",wrikisidata[0].suu_winlost & 0x0f);
temp_char=wrikisidata[0].nokoribansuu & 0xf0;
temp_char=temp_char>>4;
DrawFormatString(20,48+128,CRGREEN,"nokoribansuu=%d\n",temp_char);
DrawFormatString(20,48+144,CRGREEN,"jflag=%d\n",jflag);
ScreenFlip();
WaitKey();
}
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
*/

	if (id_hanasite >= AISUU ){//人間が話し手なら要入力
		kaiwa_main_hyoji();
		//会話入力
		if (mode_kaiwa<=10){
			mode_kaiwa=10;//会話入力待ち
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
			loop_inputstr:
			kaeri=KeyInputString( 180 , 440 , 50 , inputstr , TRUE ) ;
			if (kaeri==-1){//エラー
				mode_kaiwa=1;return;
			}
			if (kaeri==2){//ＥＳＣキーによるキャンセル
				mode_kaiwa=2;
				return;
			}
			if (inputstr[0]==0){
////////////////////////////////////////////////////////////////////
///////////////////////////debug////////////////////////////////////
/*
{
int i_debug;
ClearDrawScreen();
DrawFormatString(0,0,CRGREEN,"ＥＮＴＥＲのみ検出\n kaiwacount=%d \n studyflag=%d",kaiwacount,studyflag);
ScreenFlip();
WaitKey();
}
*/
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

				if (kaiwacount>0 && mode_kaiwa!=9){
					studyflag=1;
////////////////////////////////////////////////////////////////////
///////////////////////////debug////////////////////////////////////
/*
{
int i_debug;
ClearDrawScreen();
DrawFormatString(0,0,CRGREEN,"studyflag立てた直後\n kaiwacount=%d \n studyflag=%d",kaiwacount,studyflag);
ScreenFlip();
WaitKey();
}
*/
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

					mode_kaiwa=10;
					kaiwa_main_hyoji();
					goto loop_inputstr;
				}else{
					//開始直後は相手の会話はデータにもともと残らない
					//空でもstudyせずに再入力
					goto loop_inputstr;
				}
			}
			//ひらがなチェック
			if (check_hiragana(inputstr)!=1){
				//ひらがなでないのが混じってたら再入力をうながす
				mode_kaiwa=9;
				kaiwa_main_hyoji();
				goto loop_inputstr;
			}
			mode_kaiwa=15;//会話入力完了
		}

		if (mode_kaiwa==15){
			kaiwa_main_hyoji();

			//表情入力
			mode_kaiwa=20;//表情入力待ち
		    // 入力された数字を取得
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける 
			while(1){
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){Sleep(1);}
				if (CheckHitKey_test( KEY_INPUT_ESCAPE)==1){
					mode_kaiwa=8;
					kaiwa_main_hyoji();
					goto loop_inputstr;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD0)==1 || CheckHitKey_test(KEY_INPUT_0)==1){
					kaeri=0;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD1)==1 || CheckHitKey_test(KEY_INPUT_1)==1){
					kaeri=1;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD2)==1 || CheckHitKey_test(KEY_INPUT_2)==1){
					kaeri=2;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD3)==1 || CheckHitKey_test(KEY_INPUT_3)==1){
					kaeri=3;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD4)==1 || CheckHitKey_test(KEY_INPUT_4)==1){
					kaeri=4;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD5)==1 || CheckHitKey_test(KEY_INPUT_5)==1){
					kaeri=5;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD6)==1 || CheckHitKey_test(KEY_INPUT_6)==1){
					kaeri=6;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD7)==1 || CheckHitKey_test(KEY_INPUT_7)==1){
					kaeri=7;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD8)==1 || CheckHitKey_test(KEY_INPUT_8)==1){
					kaeri=8;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD9)==1 || CheckHitKey_test(KEY_INPUT_9)==1){
					kaeri=9;
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode_kaiwa=1;
					return ;	// エラーが起きたらループから抜ける
				}
				Sleep(1);
			}
			hyoujounum=kaeri;
			mode_kaiwa=25;//表情入力完了
		}
		if (mode_kaiwa==25){
			//kaiwa_main_hyoji();
			mode_kaiwa=30;//語尾上げ処理待ち
/*
			//語尾にクエスチョンマークで語尾上げフラグ付加処理
			int i;
			int nagasa_inputstr=0;
			char kiridasistr[3];
			for (i=0;i<3;i++){
				kiridasistr[i]=0;
			}
			nagasa_inputstr=strlen(inputstr);
			strncpy( kiridasistr , inputstr+nagasa_inputstr-2 , 2 );
			kiridasistr[2]=0;
			if (strcmp(kiridasistr,"？")==0){
				gobiageflag=1;
			}else{
				gobiageflag=0;
			}
*/
			mode_kaiwa=35;//語尾上げ処理完了
		}
		if (studyflag!=1){
			//kaiwastrに代入
			memcpy(kaiwastr , inputstr , sizeof(char)*MAXMOJISUU_kaiwa);
			//表示用変数に代入
			for (i=KAKOHYOJISUU-1;i>0;i--){
				memcpy(kako_str[i], kako_str[i-1], sizeof(char)*MAXMOJISUU_kaiwa);
				kako_hyoujounum[i]=kako_hyoujounum[i-1];
				kako_id_hanasite[i]=kako_id_hanasite[i-1];
			}
			memcpy(kako_str[0], kaiwastr, sizeof(char)*MAXMOJISUU_kaiwa);
			kako_hyoujounum[0]=hyoujounum;
			kako_id_hanasite[0]=id_hanasite;
		}else{//study
			//kaiwastrに代入
			memcpy(kaiwastr , inputstr , sizeof(char)*MAXMOJISUU_kaiwa);
			//表示用変数に上書き
			memcpy(kako_str[0], kaiwastr, sizeof(char)*MAXMOJISUU_kaiwa);
			kako_hyoujounum[0]=hyoujounum;
			kako_id_hanasite[0]=id_hanasite;

			FILE *fp;
			//前回までの記録ファイルを読み込む
			//各連番ファイルのサイズ取得
			for (i=0;i<MAXFILESUU;i++){
				filesize_kaiwadata[i]=0;
			}
			for (i=0;i<MAXFILESUU;i++){
				sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",i+1);
				filesize_kaiwadata[i]=Getfilesize(temp_filename);
				if (filesize_kaiwadata[i]<0) break;
				if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
			}
			filesuu_kaiwadata=i;
			//ファイル(上書き可能)オープン
			sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",filesuu_kaiwadata);
			fp = fopen(temp_filename,"r+b");
			if (fp == NULL){ClearDrawScreen();DrawFormatString(100,200,CRRED,"%sのファイルオープンに失敗",temp_filename);ScreenFlip();mode_kaiwa=1;return;}
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
			//ファイル終端の１個前に移動
			fseek(fp,-size_1data,SEEK_END);
			//////////////////強制上書き/////////////////////////////
			fwrite(&id_kikite,sizeof(id_hanasite),1,fp);//発言者ID///studyなので入れ替えてる
			fwrite(&hyoujounum,sizeof(hyoujounum),1,fp);
			fwrite(kaiwastr,sizeof(kaiwastr),1,fp);
			fwrite(&kaiwabundanflag,sizeof(kaiwabundanflag),1,fp);
			fwrite(&studyflag,sizeof(studyflag),1,fp);
			fwrite(&day_kaiwa,sizeof(day_kaiwa),1,fp);
			fwrite(&jflag,sizeof(jflag),1,fp);
			if (id_kikite<AISUU && id_kikite>=0){//発言者ID///studyなので入れ替えてる
				fwrite(&aikaiwadata[id_kikite].type,sizeof(aikaiwadata[0].type),1,fp);
			}else if (id_kikite<=10009 && id_kikite>=10000){
				fwrite(&humankaiwadata[id_kikite-10000].type,sizeof(aikaiwadata[0].type),1,fp);
			}else{
				temp_char=0;
				fwrite(&type_kikite,sizeof(aikaiwadata[0].type),1,fp);
			}
			if (wrikisidata[0].wrikisiid<RIKISISUU && wrikisidata[0].wrikisiid>=0){
				fwrite(&wrikisidata[0].sumoflag,sizeof(wrikisidata[0].sumoflag),1,fp);
				fwrite(&wrikisidata[0].suu_winlost,sizeof(wrikisidata[0].suu_winlost),1,fp);
				fwrite(&wrikisidata[0].nokoribansuu,sizeof(wrikisidata[0].nokoribansuu),1,fp);
			}else{
				temp_char=0;
				fwrite(&temp_char,sizeof(wrikisidata[0].sumoflag),1,fp);
				fwrite(&temp_char,sizeof(wrikisidata[0].suu_winlost),1,fp);
				fwrite(&temp_char,sizeof(wrikisidata[0].nokoribansuu),1,fp);
			}

			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
			//クローズ
			fclose(fp);
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}


			ClearDrawScreen();
			DrawString(200,200,"学習完了！！\n何事もなかったかのように会話を続行願います",CRWHITE);
			ScreenFlip();
			WaitKey();
			
		}
	}else{//AIが話し手なら要計算
		//会話を受けてのAIの処理をここに記述
		//
		//①と②ではAIの発言内容を決定する(kaesistrとする)	
		//話しかけてきた者(id_kikite)と同じ者の発言で、
		//今回の発言と同じようなことを過去に言っていないかを検索し、
		//同じような発言に対して、相手がどんな返しをすれば、
		//話しかけてきた者(id_kikite)が快く思うのかを学習して発言内容を決定
		//
		//①話しかけてきた者(id_kikite)と同じ者の発言で、同じようなことを過去に言っていないかを検索し、
		//話しかけてきた者(id_kikite)の現在の発言であるtarget_kaiwastrと
		//過去の発言であるlast_kaiwastr[any]のうちの話しかけてきた者(id_kikite)が発言したlast_kaiwastr[any]を
		//似ている度で点数化して、点数の高い発言を序列化してピックアップ
		//そのピックアップする際に、ついでにlast_kaiwastr[0]に対する返しであるlast_kaiwastr[-1]
		//や、そのlast_kaiwastr[-1]に対する返しであるlast_hyoujounum[-2]による好感度点数
		//も序列化データに含ませる
		//([-1]や[-2]→実際にアクセスするときは、１つ先が[1]、２つ先が[0]になるように2つずらすので、
		//直近の発言は[2]になる)

		int i,ii,iii;
		int dameflag=0;
		int fukasaloopsuu=0;
		int loopkaisisuu=0;
		//何個目のデータファイルを読み取っているのかの番号
		int yomitorifilenum=0;
		long temp_ichijouhou=0;
		long temp2_ichijouhou=0;
		//last_yomitorifilenum=0;//面倒だから却下→データを先までSEEKで見に行くときにファイル番号が変わったりしたときの備え
		//データ読み取りの際の保持する必要のないゴミデータ受け皿
		char temp_char=0;
		short int temp_shortint=0;
		char temp_kaiwastr[MAXMOJISUU_kaiwa];
		//過去データ読み取り後の似ている度比較点数保存
		int tensuu_fukasagoto[KENSAKUFUKASA];
		//過去データ読み取り用変数
		short int last_id_hanasite[KENSAKUFUKASA];
		char last_hyoujounum[KENSAKUFUKASA];
		char last_kaiwastr[KENSAKUFUKASA][MAXMOJISUU_kaiwa];
		char last_kaiwabundanflag[KENSAKUFUKASA];
		char last_studyflag[KENSAKUFUKASA];
		char last_day[KENSAKUFUKASA];
		char last_jflag[KENSAKUFUKASA];
		char last_hanasite_type[KENSAKUFUKASA];
		char last_wrikisi_sumoflag[KENSAKUFUKASA];
		char last_wrikisi_suu_winlost[KENSAKUFUKASA];
		char last_wrikisi_nokoribansuu[KENSAKUFUKASA];

		//序列化用変数
		char joretuka_last_inputstr[KENSAKUHOJISUU][MAXMOJISUU_kaiwa];
		char joretuka_last_kaesistr[KENSAKUHOJISUU][MAXMOJISUU_kaiwa];
		char joretuka_temp_hyoujounum[KENSAKUHOJISUU];
		int joretuka_tensuu[KENSAKUHOJISUU];

		//比較軸（例えば直近の人間の発言）
		short int target_id_hanasite=0;
		char target_hyoujounum=0;
		char target_kaiwastr[MAXMOJISUU_kaiwa];
		char target_kaiwabundanflag=0;
		char target_studyflag=0;
		char target_day=0;
		char target_jflag=0;
		char target_hanasite_type=0;
		char target_wrikisi_sumoflag=0;
		char target_wrikisi_suu_winlost=0;
		char target_wrikisi_nokoribansuu=0;
		
		if (katati_kaiwa==1 && kaiwacount>0){
			kaiwa_main_hyoji();
		}

		if (katati_kaiwa==1 && kaiwacount>0){
			//会話確認
			if (mode_kaiwa<=10){
			loop_AIinputstr:
				kaeri=KeyInputString( 180 , 440 , 50 , inputstr , TRUE ) ;
				if (kaeri==-1){//エラー
					mode_kaiwa=1;return;
				}
				if (kaeri==2){//ＥＳＣキーによるキャンセル
					mode_kaiwa=2;
					return;
				}
				if (studyflag!=1 && inputstr[0]==0 && mode_kaiwa!=9){
					//ENTERで確認ＯＫならmode10で何もしない
					mode_kaiwa=10;
				}else if (inputstr[0]==0){
					goto loop_AIinputstr;
				}else{
					//ひらがなチェック
					if (check_hiragana(inputstr)!=1){
						//ひらがなでないのが混じってたら再入力をうながす
						mode_kaiwa=9;
						kaiwa_main_hyoji();
						goto loop_AIinputstr;
					}
					studyflag=1;
					mode_kaiwa=15;//会話修正入力完了、表情入力へ
				}
			}
			if (mode_kaiwa==15){
				kaiwa_main_hyoji();
				//表情入力
				mode_kaiwa=20;//表情入力待ち
			    // 入力された数字を取得
				if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける 
				while(1){
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){Sleep(1);}
					if (CheckHitKey_test( KEY_INPUT_ESCAPE)==1){
						mode_kaiwa=8;
						kaiwa_main_hyoji();
						goto loop_AIinputstr;
					}
					if (CheckHitKey_test(KEY_INPUT_NUMPAD0)==1 || CheckHitKey_test(KEY_INPUT_0)==1){
						kaeri=0;
						break;
					}
					if (CheckHitKey_test(KEY_INPUT_NUMPAD1)==1 || CheckHitKey_test(KEY_INPUT_1)==1){
						kaeri=1;
						break;
					}
					if (CheckHitKey_test(KEY_INPUT_NUMPAD2)==1 || CheckHitKey_test(KEY_INPUT_2)==1){
						kaeri=2;
						break;
					}
					if (CheckHitKey_test(KEY_INPUT_NUMPAD3)==1 || CheckHitKey_test(KEY_INPUT_3)==1){
						kaeri=3;
						break;
					}
					if (CheckHitKey_test(KEY_INPUT_NUMPAD4)==1 || CheckHitKey_test(KEY_INPUT_4)==1){
						kaeri=4;
						break;
					}
					if (CheckHitKey_test(KEY_INPUT_NUMPAD5)==1 || CheckHitKey_test(KEY_INPUT_5)==1){
						kaeri=5;
						break;
					}
					if (CheckHitKey_test(KEY_INPUT_NUMPAD6)==1 || CheckHitKey_test(KEY_INPUT_6)==1){
						kaeri=6;
						break;
					}
					if (CheckHitKey_test(KEY_INPUT_NUMPAD7)==1 || CheckHitKey_test(KEY_INPUT_7)==1){
						kaeri=7;
						break;
					}
					if (CheckHitKey_test(KEY_INPUT_NUMPAD8)==1 || CheckHitKey_test(KEY_INPUT_8)==1){
						kaeri=8;
						break;
					}
					if (CheckHitKey_test(KEY_INPUT_NUMPAD9)==1 || CheckHitKey_test(KEY_INPUT_9)==1){
						kaeri=9;
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 )
					{
						mode_kaiwa=1;
						return ;	// エラーが起きたらループから抜ける
					}
					Sleep(1);
				}
				hyoujounum=kaeri;
				mode_kaiwa=25;//表情入力完了
			}
			if (mode_kaiwa==25){
				//kaiwa_main_hyoji();
				mode_kaiwa=30;//語尾上げ処理待ち
/*
				//語尾にクエスチョンマークで語尾上げフラグ付加処理
				int i;
				int nagasa_inputstr=0;
				char kiridasistr[3];
				for (i=0;i<3;i++){
					kiridasistr[i]=0;
				}
				nagasa_inputstr=strlen(inputstr);
				strncpy( kiridasistr , inputstr+nagasa_inputstr-2 , 2 );
				kiridasistr[2]=0;
				if (strcmp(kiridasistr,"？")==0){
					gobiageflag=1;
				}else{
					gobiageflag=0;
				}
*/
				mode_kaiwa=35;//語尾上げ処理完了
			}
			if (mode_kaiwa==35){
				//上書き修正
				//kaiwastrに代入
				memcpy(kaiwastr , inputstr , sizeof(char)*MAXMOJISUU_kaiwa);
				//表示用変数に上書き
				memcpy(kako_str[0], kaiwastr, sizeof(char)*MAXMOJISUU_kaiwa);
				kako_hyoujounum[0]=hyoujounum;
				kako_id_hanasite[0]=id_hanasite;

				FILE *fp;
				//前回までの記録ファイルを読み込む
				//各連番ファイルのサイズ取得
				for (i=0;i<MAXFILESUU;i++){
					filesize_kaiwadata[i]=0;
				}
				for (i=0;i<MAXFILESUU;i++){
					sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",i+1);
					filesize_kaiwadata[i]=Getfilesize(temp_filename);
					if (filesize_kaiwadata[i]<0) break;
					if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
				}
				filesuu_kaiwadata=i;
				//ファイル(上書き可能)オープン
				sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",filesuu_kaiwadata);
				fp = fopen(temp_filename,"r+b");
				if (fp == NULL){ClearDrawScreen();DrawFormatString(100,200,CRRED,"%sのファイルオープンに失敗",temp_filename);ScreenFlip();mode_kaiwa=1;return;}
				if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
				//ファイル終端の１個前に移動
				fseek(fp,-size_1data,SEEK_END);
				//////////////////強制上書き/////////////////////////////
				fwrite(&kako_id_hanasite[0],sizeof(id_hanasite),1,fp);//発言者ID///studyなので入れ替えてる
				fwrite(&hyoujounum,sizeof(hyoujounum),1,fp);
				fwrite(kaiwastr,sizeof(kaiwastr),1,fp);
				fwrite(&kaiwabundanflag,sizeof(kaiwabundanflag),1,fp);
				fwrite(&studyflag,sizeof(studyflag),1,fp);
				fwrite(&day_kaiwa,sizeof(day_kaiwa),1,fp);
				fwrite(&jflag,sizeof(jflag),1,fp);
				if (kako_id_hanasite[0]<AISUU && kako_id_hanasite[0]>=0){//発言者ID///studyなので入れ替えてる
					fwrite(&aikaiwadata[kako_id_hanasite[0]].type,sizeof(aikaiwadata[0].type),1,fp);
				}else if (kako_id_hanasite[0]<=10009 && kako_id_hanasite[0]>=10000){
					fwrite(&humankaiwadata[kako_id_hanasite[0]-10000].type,sizeof(aikaiwadata[0].type),1,fp);
				}else{
					temp_char=0;
					fwrite(&type_kikite,sizeof(aikaiwadata[0].type),1,fp);
				}
				if (wrikisidata[0].wrikisiid<RIKISISUU && wrikisidata[0].wrikisiid>=0){
					fwrite(&wrikisidata[0].sumoflag,sizeof(wrikisidata[0].sumoflag),1,fp);
					fwrite(&wrikisidata[0].suu_winlost,sizeof(wrikisidata[0].suu_winlost),1,fp);
					fwrite(&wrikisidata[0].nokoribansuu,sizeof(wrikisidata[0].nokoribansuu),1,fp);
				}else{
					temp_char=0;
					fwrite(&temp_char,sizeof(wrikisidata[0].sumoflag),1,fp);
					fwrite(&temp_char,sizeof(wrikisidata[0].suu_winlost),1,fp);
					fwrite(&temp_char,sizeof(wrikisidata[0].nokoribansuu),1,fp);
				}
				if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
				//クローズ
				fclose(fp);
				if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
				//studyflagとoumugaesiflagをリセット
				mode_kaiwa=10;
				studyflag=0;
				oumugaesiflag=0;
				/*
				ClearDrawScreen();
				DrawString(200,200,"学習完了！！\n何事もなかったかのように会話を続行願います",CRWHITE);
				ScreenFlip();
				WaitKey();
				*/
			}
		}

		////////////////////////////////////////////////////////////
		for (i=0;i<MAXMOJISUU_kaiwa;i++){
			//kaesistr[i]=0;
			temp_kaiwastr[i]=0;//ゴミデータ受け皿
			target_kaiwastr[i]=0;
		}

		//前回までの記録ファイルを読み込む
		//各連番ファイルのサイズ取得
		for (i=0;i<MAXFILESUU;i++){
			filesize_kaiwadata[i]=0;
		}
		for (i=0;i<MAXFILESUU;i++){
			sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",i+1);
			filesize_kaiwadata[i]=Getfilesize(temp_filename);
			if (filesize_kaiwadata[i]<0) break;
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
		}
		filesuu_kaiwadata=i;
		//ファイル読み込みループ前初期化
		yomikomicount=0;
	sounyuukaisuu=0;
	okikaekaisuu=0;
		for (i=0;i<KENSAKUFUKASA;i++){
			tensuu_fukasagoto[i]=0;
			last_id_hanasite[i]=0;
			last_hyoujounum[i]=0;
			last_kaiwabundanflag[i]=0;
			last_studyflag[i]=0;
			last_day[i]=0;
			last_jflag[i]=0;
			last_hanasite_type[i]=0;
			last_wrikisi_sumoflag[i]=0;
			last_wrikisi_suu_winlost[i]=0;
			last_wrikisi_nokoribansuu[i]=0;
			for (ii=0;ii<MAXMOJISUU_kaiwa;ii++){
				last_kaiwastr[i][ii]=0;
			}

		}
		for (i=0;i<KENSAKUHOJISUU;i++){
			joretuka_temp_hyoujounum[i]=0;
			joretuka_tensuu[i]=0;
			for (ii=0;ii<MAXMOJISUU_kaiwa;ii++){
				joretuka_last_inputstr[i][ii]=0;
				joretuka_last_kaesistr[i][ii]=0;
			}
		}
		if (katati_kaiwa==1 && kaiwacount==0){
			int kaeri=0;
			//AI同志の会話の最初のきっかけのひとこと入力
		loop_saishostr:
			ClearDrawScreen();
			DrawString(10,64,"全角で25文字以内で最初の一言だけお願いします\n全角疑問符「？」を最後に付けると質問調になります。",CRWHITE);
			DrawString(10,136,"会話を入力後ENTERで確定\nESCキーでMENUに戻る",CRWHITE);
			ScreenFlip();
			kaeri=KeyInputString( 180 , 440 , 50 , target_kaiwastr , TRUE ) ;
			if (kaeri==-1){//エラー
				mode_kaiwa=1;return;
			}
			if (kaeri==2){//ＥＳＣキーによるキャンセル
				mode_kaiwa=2;
				return;
			}
			if (target_kaiwastr[0]==0){
				//ENTER何もしない
				goto loop_saishostr;
			}else{
				//ひらがなチェック
				if (check_hiragana(target_kaiwastr)!=1){
					//ひらがなでないのが混じってたら再入力をうながす
					ClearDrawScreen();
					DrawString(200,200,"利用できない文字が混ざっているようです",CRWHITE);
					ScreenFlip();
					WaitKey();
					goto loop_saishostr;
				}
			}
			ClearDrawScreen();
			DrawString(10,64,"最初の一言の表情をお願いします",CRWHITE);
			DrawString(10,136,"数字を入力願います\nESCキーで戻る",CRWHITE);
			for (i=0;i<HYOUJOUSHURUISUU-1;i++){
				DrawFormatString(10,175+i*16,CRWHITE,"%d→%s",i,str_hyoujou[i]);
			}
			ScreenFlip();
			//表情入力
		    // 入力された数字を取得
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける 
			while(1){
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){Sleep(1);}
				if (CheckHitKey_test( KEY_INPUT_ESCAPE)==1){
					goto loop_saishostr;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD0)==1 || CheckHitKey_test(KEY_INPUT_0)==1){
					kaeri=0;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD1)==1 || CheckHitKey_test(KEY_INPUT_1)==1){
					kaeri=1;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD2)==1 || CheckHitKey_test(KEY_INPUT_2)==1){
					kaeri=2;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD3)==1 || CheckHitKey_test(KEY_INPUT_3)==1){
					kaeri=3;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD4)==1 || CheckHitKey_test(KEY_INPUT_4)==1){
					kaeri=4;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD5)==1 || CheckHitKey_test(KEY_INPUT_5)==1){
					kaeri=5;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD6)==1 || CheckHitKey_test(KEY_INPUT_6)==1){
					kaeri=6;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD7)==1 || CheckHitKey_test(KEY_INPUT_7)==1){
					kaeri=7;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD8)==1 || CheckHitKey_test(KEY_INPUT_8)==1){
					kaeri=8;
					break;
				}
				if (CheckHitKey_test(KEY_INPUT_NUMPAD9)==1 || CheckHitKey_test(KEY_INPUT_9)==1){
					kaeri=9;
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode_kaiwa=1;
					return ;	// エラーが起きたらループから抜ける
				}
				Sleep(1);
			}
			target_hyoujounum=kaeri;
			{
/*
				//語尾にクエスチョンマークで語尾上げフラグ付加処理
				int i;
				int nagasa_target_kaiwastr=0;
				char kiridasistr[3];
				for (i=0;i<3;i++){
					kiridasistr[i]=0;
				}
				nagasa_target_kaiwastr=strlen(target_kaiwastr);
				strncpy( kiridasistr , target_kaiwastr+nagasa_target_kaiwastr-2 , 2 );
				kiridasistr[2]=0;
				if (strcmp(kiridasistr,"？")==0){
					target_gobiageflag=1;
				}else{
					target_gobiageflag=0;
				}
*/
			}
		}else{//通常の場合(AI同志の会話で最初の一言を人間に発してもらう場合以外)
			//まずは軸となるべき直近の発言を読み込んでtarget_に代入
			sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",filesuu_kaiwadata);
			fp = fopen(temp_filename,"rb");
			if (fp == NULL){ClearDrawScreen();DrawFormatString(100,200,CRRED,"%sのファイルオープンに失敗",temp_filename);ScreenFlip();mode_kaiwa=1;return;}
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
			//最後のデータにファイルポインタを移動させる
			fseek(fp,-size_1data,SEEK_END);
			fpendflag=fread(&target_id_hanasite,sizeof(id_hanasite),1,fp);
			if (fpendflag == 0) {ClearDrawScreen();DrawFormatString(100,200,CRRED,"%sのファイル読込に失敗",temp_filename);ScreenFlip();mode_kaiwa=1;return;}
			fread(&target_hyoujounum,sizeof(hyoujounum),1,fp);
			fread(target_kaiwastr,sizeof(kaiwastr),1,fp);
			fread(&target_kaiwabundanflag,sizeof(kaiwabundanflag),1,fp);
			fread(&target_studyflag,sizeof(studyflag),1,fp);
			fread(&target_day,sizeof(day_kaiwa),1,fp);
			fread(&target_jflag,sizeof(jflag),1,fp);
			fread(&target_hanasite_type,sizeof(aikaiwadata[0].type),1,fp);
			fread(&target_wrikisi_sumoflag,sizeof(wrikisidata[0].sumoflag),1,fp);
			fread(&target_wrikisi_suu_winlost,sizeof(wrikisidata[0].suu_winlost),1,fp);
			fread(&target_wrikisi_nokoribansuu,sizeof(wrikisidata[0].nokoribansuu),1,fp);
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
			//クローズ
			fclose(fp);
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
		}
////debug//////////////////////////
/*FILE *fpcsv;
fpcsv = fopen("debug_kaiwa.txt","a");
fprintf(fpcsv,"\n\n■target_kaiwastr=\n「%s」\n",target_kaiwastr);
*/
		//ここから実際の検索
		//ファイル(読込)オープン
		for (yomitorifilenum=0;yomitorifilenum<filesuu_kaiwadata;yomitorifilenum++){
			sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",yomitorifilenum+1);
			fp = fopen(temp_filename,"rb");
			if (fp == NULL){ClearDrawScreen();DrawFormatString(100,200,CRRED,"%sのファイルオープンに失敗",temp_filename);ScreenFlip();mode_kaiwa=1;return;}
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
			//ファイル終端まで読込
			while(1){
				fpendflag=fread(&last_id_hanasite[0],sizeof(id_hanasite),1,fp);
				if (fpendflag == 0) break;
				fread(&last_hyoujounum[0],sizeof(hyoujounum),1,fp);
				fread(last_kaiwastr[0],sizeof(kaiwastr),1,fp);
				fread(&last_kaiwabundanflag[0],sizeof(kaiwabundanflag),1,fp);
				fread(&last_studyflag[0],sizeof(studyflag),1,fp);
				fread(&last_day[0],sizeof(day_kaiwa),1,fp);
				fread(&last_jflag[0],sizeof(jflag),1,fp);
				fread(&last_hanasite_type[0],sizeof(aikaiwadata[0].type),1,fp);
				fread(&last_wrikisi_sumoflag[0],sizeof(wrikisidata[0].sumoflag),1,fp);
				fread(&last_wrikisi_suu_winlost[0],sizeof(wrikisidata[0].suu_winlost),1,fp);
				fread(&last_wrikisi_nokoribansuu[0],sizeof(wrikisidata[0].nokoribansuu),1,fp);
				if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
//fprintf(fpcsv,"\n候補「%s」\n",last_kaiwastr[1]);

				//とりあえず何でもＯＫあとは減点方式
				chouseipoint=0;
				chouseipoint_warizan=1;
				//聞き手が発言者となっているデータだったらＯＫ
				//さらに各種状況フラグも一致しているかどうか確認
				if (last_id_hanasite[2]!=id_kikite){
					//ver4.03beta002から少し関係をなくした
					//chouseipoint_warizan=2;
//fprintf(fpcsv,"last_id_hanasite[2](%d)!=id_kikite()%d\n",last_id_hanasite[2],id_kikite);
				}
				//さらに二つ先のデータまでみて,
				//1つ先の発言者[1]が、現在の話し相手であるid_kikiteではないことと
				//2つ先の発言者[0]が、現在の話し相手であるid_kikiteになってるかと
				//1つ先と2つ先に会話分断フラグが立ってないか要チェック
				//ただstudyflagがたってたらいずれもＯＫ
				//なお、1つ先の発言が最近の発言と同じ場合も排除(しつこく同じことを言ったり聞いたりしないようにするため)
				//dameflag=0;
				lastdatazurasisuu=0;
				if (last_id_hanasite[1]==id_kikite){
//fprintf(fpcsv,"last_id_hanasite[1]==id_kikite\n");
					//ver4.03beta002から少し関係をなくした
					//chouseipoint-=1000000;
				}
				if (last_id_hanasite[0]!=id_kikite){
//fprintf(fpcsv,"last_id_hanasite[0](%d)!=id_kikite(%d)\n",last_id_hanasite[0],id_kikite);
					//ver4.03beta002から少し関係なくした
					//chouseipoint-=1000000;
				}

				//(ver4.03beta002から新設)
				//1つ先の発言者が、id_hanasiteではなかったら減点
				if (last_id_hanasite[1]!=id_hanasite){
					chouseipoint_warizan=10;
				}

				//重複チェック
				for (iii=0;iii<KAKOHYOJISUU;iii++){
					if (strcmp(last_kaiwastr[1],kako_str[iii])==0){//一致した場合
//fprintf(fpcsv,"重複チェック\n");
						chouseipoint-=1000000;
						break;
					}
				}
				//if (last_studyflag[1]!=1 && last_kaiwabundanflag[1]==1){
				if (last_kaiwabundanflag[1]==1){
//fprintf(fpcsv,"last_studyflag[1]!=1 && last_kaiwabundanflag[1]==1\n");
					chouseipoint-=1000000;
				}
//				if (last_studyflag[0]!=1 && last_kaiwabundanflag[0]==1){
//fprintf(fpcsv,"last_studyflag[0](%d)!=1 && last_kaiwabundanflag[0](%d)==1\n",last_studyflag[0],last_kaiwabundanflag[0]);
//					chouseipoint-=1000000;
//				}
				///////////////////////AIに与える情報により各種状況が同じかどうかチェック//////////////////
				///////////////////////ここでは発言候補となる[1]について////////////
				///////////jflagにて分岐/////////
				if (jflag==0){//世間話
					//jflagとtypeのみチェック
					if (last_jflag[1]!=jflag){
						//一般会話に相撲の話を持ち込まれては困るので
//fprintf(fpcsv,"last_jflag[1]!=jflag\n");
						chouseipoint-=1000000;
					}
					if (last_hanasite_type[1]!=aikaiwadata[id_hanasite].type){
//fprintf(fpcsv,"last_hanasite_type[1]!=aikaiwadata[id_hanasite].type\n");
						chouseipoint-=1000000;
					}
				}else if (jflag>=2 && jflag<=15){//ランダム天気会話、ユーザー定義
					//jflagとtypeのみチェック
					if (last_jflag[1]!=0 && last_jflag[1]!=jflag){//世間話はＯＫ
						//一般会話に相撲の話を持ち込まれては困るので
//fprintf(fpcsv,"last_jflag[1]!=jflag\n");
						chouseipoint-=1000000;
					}
					if (last_hanasite_type[1]!=aikaiwadata[id_hanasite].type){
//fprintf(fpcsv,"last_hanasite_type[1]!=aikaiwadata[id_hanasite].type\n");
						chouseipoint-=1000000;
					}
				}else if (jflag==1){//下記のすべての情報をAIに与える
					if (last_jflag[1]!=jflag){
						//相撲会話時に世間話は多少混ざってもいいでしょ→やっぱりダメ
//fprintf(fpcsv,"last_jflag[1]!=jflag\n");
						chouseipoint-=1000000;

					}else{
						if (last_hanasite_type[1]!=aikaiwadata[id_hanasite].type){
//fprintf(fpcsv,"last_hanasite_type[1]!=aikaiwadata[id_hanasite].type\n");
							chouseipoint-=1000000;
						}
						if (last_wrikisi_sumoflag[1]!=wrikisidata[0].sumoflag){
//fprintf(fpcsv,"last_wrikisi_sumoflag[1]!=aikaiwadata[id_hanasite].sumoflag\n");
							chouseipoint-=1;
						}
						if (last_wrikisi_suu_winlost[1]!=wrikisidata[0].suu_winlost){
//fprintf(fpcsv,"last_wrikisi_suu_winlost[1]!=aikaiwadata[id_hanasite].suu_winlost\n");
							chouseipoint-=1;
						}
						if (last_wrikisi_nokoribansuu[1]!=wrikisidata[0].nokoribansuu){
//fprintf(fpcsv,"last_wrikisi_nokoribansuu[1]!=aikaiwadata[id_hanasite].nokoribansuu\n");
							chouseipoint-=1;
						}
					}
				}

				yomikomicount++;
				lastdatazurasisuu=2;

				///////////////////////////////////////////////////////////
				if (yomikomicount<=2){//最初の読込では何もしない
				}else{
					//今回の発言・表情(target_)と過去の発言・表情との似ている度比較
					//先ほど２発言先を[0]に格納したので、比較すべき最初の過去の発言は[2]に格納されている
					tensuu_fukasagoto[lastdatazurasisuu]=
					tensuu_niteirudo(
						target_kaiwastr,last_kaiwastr[lastdatazurasisuu],
						target_hyoujounum,last_hyoujounum[lastdatazurasisuu]
					);
					for (fukasaloopsuu=lastdatazurasisuu;fukasaloopsuu<KENSAKUFUKASA-1;fukasaloopsuu++){
						tensuu_fukasagoto[fukasaloopsuu+1]=
						tensuu_niteirudo(
							last_kaiwastr[fukasaloopsuu],last_kaiwastr[fukasaloopsuu+1],
							last_hyoujounum[fukasaloopsuu],last_hyoujounum[fukasaloopsuu+1]
						);
					}
					//総合点数積算
					//会話分断フラグが途中であったらそれ以降は加算しない
					tensuu=0;
					for (fukasaloopsuu=lastdatazurasisuu;fukasaloopsuu<KENSAKUFUKASA-1;fukasaloopsuu++){
						//あくまでつながりを確認するので直近の発言の点数の方が大事だから補正
						if (fukasaloopsuu>lastdatazurasisuu){
							if (tensuu_fukasagoto[fukasaloopsuu]>tensuu_fukasagoto[fukasaloopsuu-1]){
								tensuu_fukasagoto[fukasaloopsuu]=tensuu_fukasagoto[fukasaloopsuu-1];
							}
						}
						tensuu+=tensuu_fukasagoto[fukasaloopsuu];
						if (last_kaiwabundanflag[fukasaloopsuu]==1) break;
					}

					//dameflagもとい減点方式による調整ポイント加味
					if (chouseipoint==-1){//少しの状況違い
						tensuu=(int)(tensuu/100)+1;
					}else if (chouseipoint==-2){//少しの状況違い
						tensuu=(int)(tensuu/10000)+1;
					}else if (chouseipoint<=-3 && chouseipoint>=-10){//
						tensuu-=1000000;
					}else{
						tensuu+=chouseipoint;
					}
					if (tensuu>0){
						tensuu=(int)(tensuu/chouseipoint_warizan)+1;
					}
					//AIの表情の好みによる調整
					if (tensuu>=0){
						tensuu*=aikaiwadata[id_hanasite].hyoujou_konomi[last_hyoujounum[0]];
					}else{
						//そのまま
					}
//fprintf(fpcsv,"↑のtensuuは%d,chouseipointは%d\n",tensuu,chouseipoint);

					//ピックアップした序列化データ内の点数以上の点数だったらデータ挿入
					for (ii=0;ii<KENSAKUHOJISUU;ii++){
						if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
						if (joretuka_tensuu[ii]<=tensuu){//点数以上だったら
							//全く同じ返しすなわちlast_kaiwastr[1]が序列化データのなかにあったら置き換える
							okikaeflag=0;
							for (iii=0;iii<KENSAKUHOJISUU;iii++){
								if (strcmp(joretuka_last_kaesistr[iii],last_kaiwastr[1])==0){//一致した場合
									if (iii>ii){//挿入すべき順位より下に同じstrがあるのならその順位を潰してずらす
										for (iiii=iii;iiii>ii;iiii--){
											joretuka_tensuu[iiii]=joretuka_tensuu[iiii-1];
											joretuka_temp_hyoujounum[iiii]=joretuka_temp_hyoujounum[iiii-1];
											memcpy(joretuka_last_inputstr[iiii] , joretuka_last_inputstr[iiii-1] , sizeof(char)*MAXMOJISUU_kaiwa);
											memcpy(joretuka_last_kaesistr[iiii] , joretuka_last_kaesistr[iiii-1] , sizeof(char)*MAXMOJISUU_kaiwa);
										}
										joretuka_tensuu[ii]=tensuu;
										joretuka_temp_hyoujounum[ii]=last_hyoujounum[0];
										memcpy(joretuka_last_inputstr[ii] , last_kaiwastr[2] , sizeof(char)*MAXMOJISUU_kaiwa);
										memcpy(joretuka_last_kaesistr[ii] , last_kaiwastr[1] , sizeof(char)*MAXMOJISUU_kaiwa);
										okikaeflag=1;
										memcpy(okikaestr , last_kaiwastr[1] , sizeof(char)*MAXMOJISUU_kaiwa);
//fprintf(fpcsv,"↑は%d位に挿入。下の順位である%d位に同じstrがあった、その順位を潰してずらした\n",ii,iii);
										break;
									}else if (iii==ii){//挿入すべき所と同順位に同じstrがあるのならそこに上書き
										joretuka_tensuu[ii]=tensuu;
										joretuka_temp_hyoujounum[ii]=last_hyoujounum[0];
										memcpy(joretuka_last_inputstr[ii] , last_kaiwastr[2] , sizeof(char)*MAXMOJISUU_kaiwa);
										memcpy(joretuka_last_kaesistr[ii] , last_kaiwastr[1] , sizeof(char)*MAXMOJISUU_kaiwa);
										okikaeflag=1;
										memcpy(okikaestr , last_kaiwastr[1] , sizeof(char)*MAXMOJISUU_kaiwa);
//fprintf(fpcsv,"↑は%d位に挿入。同順位である%d位に同じstrがあった、その順位に上書きした\n",ii,iii);
										break;
									}else{//挿入すべきところより上の順位にあったら何もしない
										okikaeflag=1;//置き換えたはいないけど下の処理で挿入させないため
//fprintf(fpcsv,"↑は%d位の点数以上だったが同じstrが上の順位にすでにあったからパスした\n",ii);
										break;
									}
	okikaekaisuu++;
								}
							}
							//おなじlast_kaesistrがなかったらデータ挿入
							if (okikaeflag==0){
	sounyuukaisuu++;
								for (iii=KENSAKUHOJISUU-1;iii>ii;iii--){
									joretuka_tensuu[iii]=joretuka_tensuu[iii-1];
									joretuka_temp_hyoujounum[iii]=joretuka_temp_hyoujounum[iii-1];
									memcpy(joretuka_last_inputstr[iii] , joretuka_last_inputstr[iii-1] , sizeof(char)*MAXMOJISUU_kaiwa);
									memcpy(joretuka_last_kaesistr[iii] , joretuka_last_kaesistr[iii-1] , sizeof(char)*MAXMOJISUU_kaiwa);
								}
								joretuka_tensuu[ii]=tensuu;
								joretuka_temp_hyoujounum[ii]=last_hyoujounum[0];
								memcpy(joretuka_last_inputstr[ii] , last_kaiwastr[2] , sizeof(char)*MAXMOJISUU_kaiwa);
								memcpy(joretuka_last_kaesistr[ii] , last_kaiwastr[1] , sizeof(char)*MAXMOJISUU_kaiwa);
//fprintf(fpcsv,"↑は%d位に挿入。\n",ii,iii);
								break;
							}
						}
					}
				}
				//前のやり取りとして残す
				for (ii=KENSAKUFUKASA-1;ii>0;ii--){
					last_id_hanasite[ii]=last_id_hanasite[ii-1];
					last_hyoujounum[ii]=last_hyoujounum[ii-1];
					memcpy(last_kaiwastr[ii], last_kaiwastr[ii-1], sizeof(char)*MAXMOJISUU_kaiwa);
					last_kaiwabundanflag[ii]=last_kaiwabundanflag[ii-1];
					last_studyflag[ii]=last_studyflag[ii-1];
					last_day[ii]=last_day[ii-1];
					last_jflag[ii]=last_jflag[ii-1];
					last_hanasite_type[ii]=last_hanasite_type[ii-1];
					last_wrikisi_sumoflag[ii]=last_wrikisi_sumoflag[ii-1];
					last_wrikisi_suu_winlost[ii]=last_wrikisi_suu_winlost[ii-1];
					last_wrikisi_nokoribansuu[ii]=last_wrikisi_nokoribansuu[ii-1];

				}

			}
			//クローズ
			fclose(fp);
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
		}

/////////////debug_kaiwa.csv/////////
//fclose(fpcsv);
//////////////////////////////

		//②　①で作った序列化データをさらにAIの表情の好みも加味し点数化し、
		//一番点数の高い返しであるlast_kaiwastr[1]をkaesistrとする
		//AIの表情の好みと序列化データの文章似ている度をかけ合わせて点数化
		//→①の処理の途中で好みもかけ合わせてしまいましたので形だけになった
		{
			int i;
			int max_tensuu=0;
			int max_i=0;
			int temp_tensuu[KENSAKUHOJISUU];
			for (i=0;i<KENSAKUHOJISUU;i++){
				temp_tensuu[i]=0;
			}
			for (i=0;i<KENSAKUHOJISUU;i++){
//				temp_tensuu[i] = aikaiwadata[id_hanasite].hyoujou_konomi[joretuka_temp_hyoujounum[i]] * joretuka_tensuu[i];
				temp_tensuu[i] = joretuka_tensuu[i];
			}

			//点数の一番高いのをkaesistrとする
			max_tensuu=-999999999;
			max_i=0;
			for (i=0;i<KENSAKUHOJISUU;i++){
				if (temp_tensuu[i]>max_tensuu){
					max_tensuu=temp_tensuu[i];
					max_i=i;
				}
			}


////////////////////////////////////////////////////////////////////
///////////////////////////debug////////////////////////////////////
/*
{
int i_debug;
ClearDrawScreen();
DrawFormatString(0,0,CRGREEN,"debug点数表示直前\n\nkako_hyoujounum[1]=%d\nkako_hyoujounum[0]=%d",kako_hyoujounum[1],kako_hyoujounum[0]);
DrawFormatString(0,460,CRGREEN,"oumugaesiflag=%d,studyflag=%d,id_hanasite=%d,id_kikite=%d",oumugaesiflag,studyflag,id_hanasite,id_kikite);
ScreenFlip();
WaitKey();
}
*/
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
///////////////////////////debug////////////////////////////////////
/*
{
int i_debug;
ClearDrawScreen();
DrawFormatString(0,0,CRGREEN,"max_i=%d",max_i);
//for (i_debug=0;i_debug<KENSAKUHOJISUU;i_debug++){
for (i_debug=0;i_debug<6;i_debug++){
DrawFormatString(0,50+i_debug*60,CRGREEN,"temp_tensuu=%d\njoretuka_last_kaesistr=\n%s",temp_tensuu[i_debug],joretuka_last_kaesistr[i_debug]);
}
ScreenFlip();
WaitKey();
}
*/
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


			//////kaesistr決定
			memcpy(kaesistr , joretuka_last_kaesistr[max_i] , sizeof(char)*MAXMOJISUU_kaiwa);
			oumugaesiflag=0;
			if (strlen(kaesistr)==0){//空欄なら
				memcpy(kaesistr , target_kaiwastr , sizeof(char)*MAXMOJISUU_kaiwa);
				oumugaesiflag=1;
			}
		}

////////////////////////////////////////////////////////////////////
///////////////////////////debug////////////////////////////////////
/*
{
int i_debug;
ClearDrawScreen();
DrawFormatString(0,0,CRGREEN,"oumugaesiflagが立つべき直後\n\nkako_hyoujounum[1]=%d\nkako_hyoujounum[0]=%d",kako_hyoujounum[1],kako_hyoujounum[0]);
DrawFormatString(0,460,CRGREEN,"oumugaesiflag=%d,studyflag=%d,id_hanasite=%d,id_kikite=%d",oumugaesiflag,studyflag,id_hanasite,id_kikite);
ScreenFlip();
WaitKey();
}
*/
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

		//③と④ではAIの表情を決定する(kaesihyoujounumとする)
		//直近の相手の発言であるtarget_kaiwastrと同じような発言・表情を過去にしていないかを検索し、
		//同じような発言・表情に対して人間はどんな表情をするのかを学習(真似)して表情を決定
		//
		//③直近の相手の発言であるtarget_kaiwastrと同じこともしくは似たようなことを過去に言っていないか
		//過去の発言(last_kaiwastr[any])のうち、
		//発言者は誰でもよいのでlast_kaiwastr[any]を似ている度点数化して点数の高い発言
		//を序列化してピックアップ
		//(ただし、last_kaiwastr[any]の返しであるlast_kaiwastr[any-1]の発言者が人間である場合に限る)
		//そのピックアップする際に、ついでにlast_kaiwastr[any]に対する返しである
		//last_hyoujounum[any-1]も序列化データに含ませる

		//前回までの記録ファイルを読み込む
		//各連番ファイルのサイズ取得
		for (i=0;i<MAXFILESUU;i++){
			filesize_kaiwadata[i]=0;
		}
		for (i=0;i<MAXFILESUU;i++){
			sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",i+1);
			filesize_kaiwadata[i]=Getfilesize(temp_filename);
			if (filesize_kaiwadata[i]<0) break;
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
		}
		filesuu_kaiwadata=i;
		//ファイル読み込みループ前初期化
		yomikomicount=0;
	sounyuukaisuu=0;
	okikaekaisuu=0;
		for (i=0;i<KENSAKUFUKASA;i++){
			tensuu_fukasagoto[i]=0;
			last_id_hanasite[i]=0;
			last_hyoujounum[i]=0;
			last_kaiwabundanflag[i]=0;
			last_studyflag[i]=0;
			last_day[i]=0;
			last_jflag[i]=0;
			last_hanasite_type[i]=0;
			last_wrikisi_sumoflag[i]=0;
			last_wrikisi_suu_winlost[i]=0;
			last_wrikisi_nokoribansuu[i]=0;
			for (ii=0;ii<MAXMOJISUU_kaiwa;ii++){
				last_kaiwastr[i][ii]=0;
			}

		}
		for (i=0;i<KENSAKUHOJISUU;i++){
			joretuka_temp_hyoujounum[i]=0;joretuka_temp_hyoujounum[i]=10;//AI専用のわからん表情
			joretuka_tensuu[i]=0;
			for (ii=0;ii<MAXMOJISUU_kaiwa;ii++){
				joretuka_last_inputstr[i][ii]=0;
				joretuka_last_kaesistr[i][ii]=0;
			}
		}


		//ファイル(読込)オープン
		for (yomitorifilenum=0;yomitorifilenum<filesuu_kaiwadata;yomitorifilenum++){
			sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",yomitorifilenum+1);
			fp = fopen(temp_filename,"rb");
			if (fp == NULL){ClearDrawScreen();DrawFormatString(100,200,CRRED,"%sのファイルオープンに失敗",temp_filename);ScreenFlip();mode_kaiwa=1;return;}
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
			//ファイル終端まで読込
			while(1){
				fpendflag=fread(&last_id_hanasite[0],sizeof(id_hanasite),1,fp);
				if (fpendflag == 0) break;
				fread(&last_hyoujounum[0],sizeof(hyoujounum),1,fp);
				fread(last_kaiwastr[0],sizeof(kaiwastr),1,fp);
				fread(&last_kaiwabundanflag[0],sizeof(kaiwabundanflag),1,fp);
				fread(&last_studyflag[0],sizeof(studyflag),1,fp);
				fread(&last_day[0],sizeof(day_kaiwa),1,fp);
				fread(&last_jflag[0],sizeof(jflag),1,fp);
				fread(&last_hanasite_type[0],sizeof(aikaiwadata[0].type),1,fp);
				fread(&last_wrikisi_sumoflag[0],sizeof(wrikisidata[0].sumoflag),1,fp);
				fread(&last_wrikisi_suu_winlost[0],sizeof(wrikisidata[0].suu_winlost),1,fp);
				fread(&last_wrikisi_nokoribansuu[0],sizeof(wrikisidata[0].nokoribansuu),1,fp);
				if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}


				//発言者は誰でも仮ＯＫ
				chouseipoint=0;
				//さらに表情を真似する対象である1つ先のデータ[0]まで読んで,
				//参考にする表情の発言者[0]が、人間であること→4.03より関係なしに変更
				//相撲会話の時は参考にする表情の直前の発言[1]がAIであること→4.03より関係なしに変更
				//さらに会話分断フラグが立ってないか要チェック
				//ただしstudy済みなら復活ＯＫ
				//dameflag=0;

				if (last_id_hanasite[0]<AISUU && last_id_hanasite[0]>=0){
					//chouseipoint-=1000000;
					//ver4.03より関係なしに変更
				}
				if (last_jflag[1]==1 && last_id_hanasite[1]>=AISUU){
					//chouseipoint-=1000000;
					//ver4.03より関係なしに変更
				}
				//if (last_kaiwabundanflag[0]==1 && last_studyflag[0]!=1){
				if (last_kaiwabundanflag[0]==1){
					chouseipoint-=1000000;
				}
				///////////////////////AIに与える情報により各種状況が同じかどうかチェック//////////////////
				///////////////////////ここでは[0]よりも参考にする表情の直前の発言[1]を重視////////////
				///////////jflagにて分岐/////////
				if (jflag==0){//世間話
					//jflagのみチェック
					if (last_jflag[1]!=jflag){
						//一般会話に相撲の話を持ち込まれては困るので
						chouseipoint-=1000000;
					}
				}else if (jflag>=2 && jflag<=15){//ランダム天気会話、ユーザー定義
					//jflagのみチェック
					if (last_jflag[1]!=0 && last_jflag[1]!=jflag){
						//一般会話に相撲の話を持ち込まれては困るので
						chouseipoint-=1000000;
					}
				}else if (jflag==1){//下記のすべての情報をAIに与える
					if (last_jflag[1]!=jflag){
						//相撲会話時に世間話は多少混ざってもいいでしょ
						chouseipoint-=1000000;
					}else{
						if (last_hanasite_type[1]!=aikaiwadata[id_hanasite].type){
							chouseipoint-=1000000;
						}
						if (last_wrikisi_sumoflag[1]!=wrikisidata[0].sumoflag){
							chouseipoint-=1;
						}
						if (last_wrikisi_suu_winlost[1]!=wrikisidata[0].suu_winlost){
							chouseipoint-=1;
						}
						if (last_wrikisi_nokoribansuu[1]!=wrikisidata[0].nokoribansuu){
							chouseipoint-=1;
						}
					}
				}

				yomikomicount++;
				lastdatazurasisuu=1;

				///////////////////////////////////////////////////////////
				if (yomikomicount<=1){//最初の読込では何もしない
				}else{
					//今回の発言・表情(target_)と過去の発言・表情との似ている度比較
					//先ほど1発言先を[0]に格納したので、今回の比較対象の過去の発言は[1]に格納されている
					tensuu_fukasagoto[lastdatazurasisuu]=
					tensuu_niteirudo(
						target_kaiwastr,last_kaiwastr[lastdatazurasisuu],
						target_hyoujounum,last_hyoujounum[lastdatazurasisuu]
					);
					for (fukasaloopsuu=lastdatazurasisuu;fukasaloopsuu<KENSAKUFUKASA-1;fukasaloopsuu++){
						tensuu_fukasagoto[fukasaloopsuu+1]=
						tensuu_niteirudo(
							last_kaiwastr[fukasaloopsuu],last_kaiwastr[fukasaloopsuu+1],
							last_hyoujounum[fukasaloopsuu],last_hyoujounum[fukasaloopsuu+1]
						);
					}
					//総合点数積算
					//会話分断フラグが途中であったらそれ以降は加算しない
					tensuu=0;
					for (fukasaloopsuu=lastdatazurasisuu;fukasaloopsuu<KENSAKUFUKASA-1;fukasaloopsuu++){
						//あくまでつながりを確認するので直近の発言の点数の方が大事だから補正
						if (fukasaloopsuu>lastdatazurasisuu){
							if (tensuu_fukasagoto[fukasaloopsuu]>tensuu_fukasagoto[fukasaloopsuu-1]){
								tensuu_fukasagoto[fukasaloopsuu]=tensuu_fukasagoto[fukasaloopsuu-1];
							}
						}
						tensuu+=tensuu_fukasagoto[fukasaloopsuu];
						if (last_kaiwabundanflag[fukasaloopsuu]==1) break;
					}

					//dameflagもとい調整ポイント
					if (chouseipoint==-1){//少しの状況違い
						tensuu=(int)(tensuu/100)+1;
					}else if (chouseipoint==-2){//少しの状況違い
						tensuu=(int)(tensuu/10000)+1;
					}else if (chouseipoint<=-3 && chouseipoint>=-10){//
						tensuu-=1000000;
					}else{
						tensuu+=chouseipoint;
					}

					//ピックアップした序列化データ内の点数以上の点数だったらデータ挿入
					for (ii=0;ii<KENSAKUHOJISUU;ii++){
						if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
						if (joretuka_tensuu[ii]<=tensuu){
	sounyuukaisuu++;
							for (iii=KENSAKUHOJISUU-1;iii>ii;iii--){
								joretuka_tensuu[iii]=joretuka_tensuu[iii-1];
								joretuka_temp_hyoujounum[iii]=joretuka_temp_hyoujounum[iii-1];
								memcpy(joretuka_last_inputstr[iii] , joretuka_last_inputstr[iii-1] , sizeof(char)*MAXMOJISUU_kaiwa);
								memcpy(joretuka_last_kaesistr[iii] , joretuka_last_kaesistr[iii-1] , sizeof(char)*MAXMOJISUU_kaiwa);
							}
							joretuka_tensuu[ii]=tensuu;
							joretuka_temp_hyoujounum[ii]=last_hyoujounum[0];
							memcpy(joretuka_last_inputstr[ii] , last_kaiwastr[2] , sizeof(char)*MAXMOJISUU_kaiwa);
							memcpy(joretuka_last_kaesistr[ii] , last_kaiwastr[1] , sizeof(char)*MAXMOJISUU_kaiwa);
							break;
						}
					}
				}
				//前のやり取りとして残す
				for (ii=KENSAKUFUKASA-1;ii>0;ii--){
					last_id_hanasite[ii]=last_id_hanasite[ii-1];
					last_hyoujounum[ii]=last_hyoujounum[ii-1];
					memcpy(last_kaiwastr[ii], last_kaiwastr[ii-1], sizeof(char)*MAXMOJISUU_kaiwa);
					last_kaiwabundanflag[ii]=last_kaiwabundanflag[ii-1];
					last_studyflag[ii]=last_studyflag[ii-1];
					last_day[ii]=last_day[ii-1];
					last_jflag[ii]=last_jflag[ii-1];
					last_hanasite_type[ii]=last_hanasite_type[ii-1];
					last_wrikisi_sumoflag[ii]=last_wrikisi_sumoflag[ii-1];
					last_wrikisi_suu_winlost[ii]=last_wrikisi_suu_winlost[ii-1];
					last_wrikisi_nokoribansuu[ii]=last_wrikisi_nokoribansuu[ii-1];
				}
			}
			//クローズ
			fclose(fp);
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
		}


////////////////////////////////////////////////////////////////////
///////////////////////////debug////////////////////////////////////
/*
{
int i_debug;
ClearDrawScreen();
for (i_debug=0;i_debug<6;i_debug++){
DrawFormatString(0,50+i_debug*60,CRGREEN,"joretuka_temp_hyoujounum[]=%d\n",joretuka_temp_hyoujounum[i_debug]);
}
ScreenFlip();
WaitKey();
}
*/
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


		//④　③で作った序列化データのうちで
		//target_strと一番似ている度の高いlast_kaiwastr[]
		//に対する返事の表情であるtemp_hyoujounumをkaesihyoujounumとする
		kaesihyoujounum=joretuka_temp_hyoujounum[0];
		//kaesikaiwabundanflagはおうむ返し処理をするかしないかのところで決定している

		//記録用代入代入
		hyoujounum=kaesihyoujounum;
		kaiwabundanflag=kaesikaiwabundanflag;
		memcpy(kaiwastr , kaesistr , sizeof(char)*MAXMOJISUU_kaiwa);

		//表示用変数に代入
		for (i=KAKOHYOJISUU-1;i>0;i--){
			memcpy(kako_str[i], kako_str[i-1], sizeof(char)*MAXMOJISUU_kaiwa);
			kako_hyoujounum[i]=kako_hyoujounum[i-1];
			kako_id_hanasite[i]=kako_id_hanasite[i-1];
		}
		memcpy(kako_str[0], kaiwastr, sizeof(char)*MAXMOJISUU_kaiwa);
		kako_hyoujounum[0]=hyoujounum;
		kako_id_hanasite[0]=id_hanasite;

	}//発言処理のおわり括弧

	//ここから人間・ＡＩ共通処理
	if (studyflag!=1){
		//ファイル記録処理
		{
			//書き込み処理
			//ファイルサイズ確認して連番ファイルを作成する必要がある
			//各連番ファイルのサイズ取得
			for (ii=0;ii<MAXFILESUU;ii++){
				sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",ii);
				filesize_kaiwadata[ii]=Getfilesize(temp_filename);
				if (filesize_kaiwadata[ii]<0) break;
				if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
			}
			//ファイル(追記)オープン
			for (ii=0;ii<MAXFILESUU;ii++){
				if (filesize_kaiwadata[ii]<=maxfilesize){
					sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",ii+1);
					fp = fopen(temp_filename,"ab");
					if (fp == NULL){ClearDrawScreen();DrawFormatString(100,200,CRRED,"%sのファイルオープンに失敗",temp_filename);ScreenFlip();mode_kaiwa=1;return;}
					break;
				}
				if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
			}
			//////////////////書き込み/////////////////////////////
			//書込み前処理

			//書込み
			fwrite(&id_hanasite,sizeof(id_hanasite),1,fp);//発言者ID
			fwrite(&hyoujounum,sizeof(hyoujounum),1,fp);
			fwrite(kaiwastr,sizeof(kaiwastr),1,fp);
			fwrite(&kaiwabundanflag,sizeof(kaiwabundanflag),1,fp);
			fwrite(&studyflag,sizeof(studyflag),1,fp);
			fwrite(&day_kaiwa,sizeof(day_kaiwa),1,fp);
			fwrite(&jflag,sizeof(jflag),1,fp);
			if (id_hanasite<AISUU && id_hanasite>=0){
				fwrite(&aikaiwadata[id_hanasite].type,sizeof(aikaiwadata[0].type),1,fp);
			}else if (id_hanasite<=10009 && id_hanasite>=10000){
				fwrite(&humankaiwadata[id_hanasite-10000].type,sizeof(aikaiwadata[0].type),1,fp);
			}else{
				temp_char=0;
				fwrite(&type_hanasite,sizeof(aikaiwadata[0].type),1,fp);
			}
			if (wrikisidata[0].wrikisiid<RIKISISUU && wrikisidata[0].wrikisiid>=0){
				fwrite(&wrikisidata[0].sumoflag,sizeof(wrikisidata[0].sumoflag),1,fp);
				fwrite(&wrikisidata[0].suu_winlost,sizeof(wrikisidata[0].suu_winlost),1,fp);
				fwrite(&wrikisidata[0].nokoribansuu,sizeof(wrikisidata[0].nokoribansuu),1,fp);
			}else{
				temp_char=0;
				fwrite(&temp_char,sizeof(wrikisidata[0].sumoflag),1,fp);
				fwrite(&temp_char,sizeof(wrikisidata[0].suu_winlost),1,fp);
				fwrite(&temp_char,sizeof(wrikisidata[0].nokoribansuu),1,fp);
			}
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
			//クローズ
			fclose(fp);
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
		}

	////////////////////////////////////////////////////////////////////
	///////////////////////////debug////////////////////////////////////
	/*
	{
	int i_debug;
	ClearDrawScreen();
	DrawFormatString(0,0,CRGREEN,"交代処理前 id_hanasite=%d \n id_kikite=%d",id_hanasite,id_kikite);
	ScreenFlip();
	WaitKey();
	}
	*/
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

		//ターン交代
		{
			short int temp_id=0;
			char temp_type=0;
			if (katati_kaiwa==0){
				temp_id=id_hanasite;
				id_hanasite=id_kikite;
				id_kikite=temp_id;
				temp_type=type_hanasite;
				type_hanasite=type_kikite;
				type_kikite=temp_type;
			}else if (katati_kaiwa==1){
				temp_id=id_hanasite;
				id_hanasite=id_kikite;
				id_kikite=nextspeaking_heya(id_hanasite,rikisidata[id_hanasite].heyaid);
				type_hanasite=aikaiwadata[id_hanasite].type;
				type_kikite=aikaiwadata[id_kikite].type;
			}
	////////////////////////////////////////////////////////////////////
	///////////////////////////debug////////////////////////////////////
	/*
	{
	int i_debug;
	ClearDrawScreen();
	DrawFormatString(0,0,CRGREEN,"交代処理後 id_hanasite=%d \n id_kikite=%d",id_hanasite,id_kikite);
	ScreenFlip();
	WaitKey();
	}
	*/
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

			kaiwabundanflag=0;
			kaiwacount++;
			mode_kaiwa=10;//会話入力待ち
			//おうむ返しを行わせている場合にはstudyflagたてる
			if (oumugaesiflag==1){
				studyflag=1;
				//oumugaesiflag=0;
			}
		}
	}else{//学習させた場合(ちなみにkatati_kaiwaが1の場合はAI処理冒頭での修正入力完了後にstudyflagは0に戻すのでここには来ない)
		studyflag=0;
		oumugaesiflag=0;
		kaiwabundanflag=0;
		//kaiwacount++;
		mode_kaiwa=10;//会話入力待ち
	}

////////////////////////////////////////////////////////////////////
///////////////////////////debug////////////////////////////////////
/*
{
int i_debug;
ClearDrawScreen();
DrawFormatString(0,0,CRGREEN,"whileループ終端直前前\n\nkako_hyoujounum[1]=%d\nkako_hyoujounum[0]=%d",kako_hyoujounum[1],kako_hyoujounum[0]);
DrawFormatString(0,460,CRGREEN,"oumugaesiflag=%d,studyflag=%d,id_hanasite=%d,id_kikite=%d",oumugaesiflag,studyflag,id_hanasite,id_kikite);
ScreenFlip();
WaitKey();
}
*/
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


	}//whileループ終端
}


