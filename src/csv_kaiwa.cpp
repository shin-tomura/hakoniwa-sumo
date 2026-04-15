#include "DxLib.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include "define.h"


extern struct ai_data aikaiwadata[AISUU];//AIごとの個性のデータ
extern struct human_data humankaiwadata[HUMANSUU];//AIごとの個性のデータ
extern struct wrikisi_data wrikisidata[1];//話題対象力士データ

extern char str_hyoujou[HYOUJOUSHURUISUU][21];
extern char str_jflag[jflagSHURUISUU][21];
extern char str_type[typeSHURUISUU][21];
extern char str_human[HUMANSUU][21];

extern char day_kaiwa;//場所中の何日目か
extern char jflag;//会話の周りの状況フラグ
			//0→ごくごく一般的な会話状況、2～10はランダム天気
			//11～15→ユーザー定義
			//1→小相撲関連な会話状況→aikaiwadata[].sumoflagのフラグ状況を参照する
extern short int id_hanasite;//話し手
extern short int id_kikite;//聞き手
extern char type_hanasite;//話し手の言葉タイプ
extern char type_kikite;//聞き手の言葉タイプ
extern char studyflag;

extern int mode_kaiwa;//1：終了フラグ、2：ゲーム準備処理完了フラグ、
		//9:会話入力からやり直し
		//10:会話入力待ち
		//15:会話入力完了
		//20:表情入力待ち
		//25:表情入力完了
extern long maxfilesize;//本番用
extern int filesuu_kaiwadata;
extern char kaiwabundanflag;//ゲーム立ち上げ後は前のやり取りとはつながらないので、それをわからせるため
extern char kaiwastr[MAXMOJISUU_kaiwa];//記録する際の発言
extern char hyoujounum;
extern char kaesihyoujounum;


extern int mode;
extern int FontHandle12;
extern long maxfilesize;//本番用
extern int get_mouseclick(int x1,int y1,int x2,int y2);//座標(x1,y1)と(x2,y2)に囲まれたところで
extern char namestring[RIKISISUU][12];//(力士IDごとの四股名,全角５文字まで)四股名
extern struct rikisi_data rikisidata[RIKISISUU];//力士データ用構造体変数708人分用意
extern long Getfilesize(char name[]);//返り値が0は存在するけどファイルサイズ0、-1→エラー、-2→存在無し
extern int check_hiragana(char checkstr[]);

void csv_kaiwa_read(void);
void editstr_jflag(char x);
void editstr_type(char x);
void editstr_human(char x);
void edit_type(void);
void edit_rikisiaidata(int x);
void csvinput_kaiwa(void);
void csvoutput_kaiwa(void);


void editstr_jflag(char x)
{
	char temp_string[21];
	int kaeri;
	int i;
	for (i=0;i<21;i++){
		temp_string[i]=0;
	}
	ClearDrawScreen();
	DrawBox(0,0,639,479,CRBACK,TRUE);
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
	DrawFormatStringToHandle(260,6,CRWHITE,FontHandle12,"jflag=%dの会話周辺状況名称変更画面",x);
	DrawFormatString(187,417-16,CRGREEN,"%s",str_jflag[x]);
	DrawString(187,417,"の名称を変更します。(全角10文字以内)",CRGREEN);
	DrawString(187,433,"ENTERキーで確定、ESCキーでキャンセルです。",CRGREEN);
	DrawString(187,449,"新しい状況名＞",CRGREEN);
	ScreenFlip() ;//裏画面を表画面にコピー
	while(1){
	kaeri=KeyInputString( 310 , 449 , 20 , temp_string , TRUE );
		if (kaeri==2){
			break;
		}
		if (strncmp(temp_string,"\0",1)!=0){
			strcpy(str_jflag[x],temp_string);
			//csvファイル上書き
			FILE *fp;
			fp = fopen("kaiwadata/str_jflag.csv","w");
			for (i=0;i<jflagSHURUISUU;i++){
				fprintf(fp,"%s\n",str_jflag[i]);
			}
			fprintf(fp,"※1番上の行が状況フラグ0、一番下の行が15、11～15はユーザー定義\n");
			fprintf(fp,"全角換算10文字以内\n");
			fclose(fp);
			break;
		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){
			mode=1;
			return ;	// エラーが発生したらループを抜ける
		}
		Sleep(1);
	}
	return;
}
void editstr_type(char x)
{
	char temp_string[21];
	int kaeri;
	int i;
	for (i=0;i<21;i++){
		temp_string[i]=0;
	}
	ClearDrawScreen();
	DrawBox(0,0,639,479,CRBACK,TRUE);
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
	DrawFormatStringToHandle(260,6,CRWHITE,FontHandle12,"type=%dの言葉タイプ名称変更画面",x);
	DrawFormatString(187,417-16,CRGREEN,"%s",str_type[x]);
	DrawString(187,417,"の名称を変更します。(全角10文字以内)",CRGREEN);
	DrawString(187,433,"ENTERキーで確定、ESCキーでキャンセルです。",CRGREEN);
	DrawString(187,449,"新しい言葉名＞",CRGREEN);
	ScreenFlip() ;//裏画面を表画面にコピー
	while(1){
	kaeri=KeyInputString( 310 , 449 , 20 , temp_string , TRUE );
		if (kaeri==2){
			break;
		}
		if (strncmp(temp_string,"\0",1)!=0){
			strcpy(str_type[x],temp_string);
			//csvファイル上書き
			FILE *fp;
			fp = fopen("kaiwadata/str_type.csv","w");
			for (i=0;i<typeSHURUISUU;i++){
				fprintf(fp,"%s\n",str_type[i]);
			}
			fprintf(fp,"※1番上の行がtypeID0、一番下の行がtypeID9、1～9はユーザー定義\n");
			fprintf(fp,"全角換算10文字以内\n");
			fclose(fp);
			break;
		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){
			mode=1;
			return ;	// エラーが発生したらループを抜ける
		}
		Sleep(1);
	}
	return;
}
void editstr_human(char x)
{
	char temp_string[21];
	int kaeri;
	int i;
	for (i=0;i<21;i++){
		temp_string[i]=0;
	}
	ClearDrawScreen();
	DrawBox(0,0,639,479,CRBACK,TRUE);
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
	DrawFormatStringToHandle(260,6,CRWHITE,FontHandle12,"id=%dの人間(あなた)の名称変更画面",x+10000);
	DrawString(187,417-104,"※AIは名前自体を認識することはありませんが、",CRWHITE);
	DrawString(187,417-88,"IDで別人であることは認識します",CRWHITE);
	DrawFormatString(187,417-16,CRGREEN,"%s",str_human[x]);
	DrawString(187,417,"の名称を変更します。(全角10文字以内)",CRGREEN);
	DrawString(187,433,"ENTERキーで確定、ESCキーでキャンセルです。",CRGREEN);
	DrawString(187,449,"新しいお名前＞",CRGREEN);
	ScreenFlip() ;//裏画面を表画面にコピー
	while(1){
	kaeri=KeyInputString( 310 , 449 , 20 , temp_string , TRUE );
		if (kaeri==2){
			break;
		}
		if (strncmp(temp_string,"\0",1)!=0){
			strcpy(str_human[x],temp_string);
			//csvファイル上書き
			FILE *fp;
			fp = fopen("kaiwadata/str_human.csv","w");
			for (i=0;i<HUMANSUU;i++){
				fprintf(fp,"%s\n",str_human[i]);
			}
			fprintf(fp,"※1番上の行がID10000、一番下の行がID10009\n");
			fprintf(fp,"全角換算10文字以内\n");
			fclose(fp);
			break;
		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){
			mode=1;
			return ;	// エラーが発生したらループを抜ける
		}
		Sleep(1);
	}
	return;
}

void csv_kaiwa_read(void)
{

	int i,ii,totalbytesuu,mojibytesuu,breakflag;
	char temp_str_hyoujou[HYOUJOUSHURUISUU][21];
	char temp_str_jflag[jflagSHURUISUU][21];
	char temp_str_type[typeSHURUISUU][21];
	char temp_str_human[HUMANSUU][21];
	int temp_id=0;
	char temp_string_suu[101];
	char ch=0;
	int kazu=0;
	int count=0;

	for (i=0;i<101;i++){
		temp_string_suu[i]=0;
	}
	for (i=0;i<HYOUJOUSHURUISUU;i++){
		for (ii=0;ii<21;ii++){
			temp_str_hyoujou[i][ii]=0;
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (i=0;i<jflagSHURUISUU;i++){
		for (ii=0;ii<21;ii++){
			temp_str_jflag[i][ii]=0;
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (i=0;i<typeSHURUISUU;i++){
		for (ii=0;ii<21;ii++){
			temp_str_type[i][ii]=0;
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (i=0;i<HUMANSUU;i++){
		for (ii=0;ii<21;ii++){
			temp_str_human[i][ii]=0;
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

	/////////////hyoujoustr////////////////
	////変換処理//////////////////////
	FILE *fpsikona;
	FILE *fpsikona2;
	//////////////////////
	fpsikona = fopen("kaiwadata/str_hyoujou.csv","rb");
	if( fpsikona == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "kaiwadata/str_hyoujou.csvが見つかりません" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		mode=1;
		return ;
	}else{
		fpsikona2 = fopen("kaiwadata/str_hyoujou.dat","wb");
		if( fpsikona2 == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "kaiwadata/str_hyoujou.datファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1;
			return ;
		}
		mojibytesuu=0;
		totalbytesuu=0;
		breakflag=0;
		while(1)
		{
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (totalbytesuu>=HYOUJOUSHURUISUU*21){//フラグ種類数×20バイト(全角10文字分)だけどデータ的に21バイト
				ch=0x00;
				fseek(fpsikona2,-1,SEEK_CUR);
				fwrite(&ch,sizeof(ch),1,fpsikona2);
				break;
			}
			mojibytesuu=0;
			while(1){
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (mojibytesuu>=20){
					ch=0x00;
					fwrite(&ch,sizeof(ch),1,fpsikona2);
					fseek(fpsikona,+1,SEEK_CUR);
					totalbytesuu++;
					break;
				}else{
					if (fread(&ch,sizeof(ch),1,fpsikona)>=1){
						if (ch==0x0d){
							ch=0x00;
							for (i=mojibytesuu;i<21;i++){//21バイトにするため
								fwrite(&ch,sizeof(ch),1,fpsikona2);
								totalbytesuu++;
							}
							break;
						}else if(ch==0x0a){

						}else{
							fwrite(&ch,sizeof(ch),1,fpsikona2);
							mojibytesuu++;
							totalbytesuu++;
						}
					}else{
						breakflag=1;
						break;
					}
				}
			}
			if (breakflag==1) break;
		}
		fclose(fpsikona);
		fclose(fpsikona2);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		/////変換処理ここまで/////
		//四股名読み込み//////
		FILE *fp;
		fp = fopen("kaiwadata/str_hyoujou.dat","rb");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "kaiwadata/str_hyoujou.datをつくる処理をしたはずなのにファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1;
			return ;		
		}
		//ここから読み込み
		fread(temp_str_hyoujou,sizeof(temp_str_hyoujou),1,fp);
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (i=0;i<HYOUJOUSHURUISUU;i++){
			for (ii=0;ii<21;ii++){
				str_hyoujou[i][ii]=0;
			}
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		for (i=0;i<HYOUJOUSHURUISUU;i++){
			strcpy(str_hyoujou[i],temp_str_hyoujou[i]);
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}

	/////////////jflag////////////////
	////変換処理//////////////////////
	//FILE *fpsikona;
	//FILE *fpsikona2;
	//////////////////////
	fpsikona = fopen("kaiwadata/str_jflag.csv","rb");
	if( fpsikona == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "kaiwadata/str_jflag.csvが見つかりません" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		mode=1;
		return ;
	}else{
		fpsikona2 = fopen("kaiwadata/str_jflag.dat","wb");
		if( fpsikona2 == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "kaiwadata/str_jflag.datファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1;
			return ;
		}
		mojibytesuu=0;
		totalbytesuu=0;
		breakflag=0;
		while(1)
		{
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (totalbytesuu>=jflagSHURUISUU*21){//16種類のフラグ×20バイト(全角10文字分)だけどデータ的に21バイト
				ch=0x00;
				fseek(fpsikona2,-1,SEEK_CUR);
				fwrite(&ch,sizeof(ch),1,fpsikona2);
				break;
			}
			mojibytesuu=0;
			while(1){
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (mojibytesuu>=20){
					ch=0x00;
					fwrite(&ch,sizeof(ch),1,fpsikona2);
					fseek(fpsikona,+1,SEEK_CUR);
					totalbytesuu++;
					break;
				}else{
					if (fread(&ch,sizeof(ch),1,fpsikona)>=1){
						if (ch==0x0d){
							ch=0x00;
							for (i=mojibytesuu;i<21;i++){//21バイトにするため
								fwrite(&ch,sizeof(ch),1,fpsikona2);
								totalbytesuu++;
							}
							break;
						}else if(ch==0x0a){

						}else{
							fwrite(&ch,sizeof(ch),1,fpsikona2);
							mojibytesuu++;
							totalbytesuu++;
						}
					}else{
						breakflag=1;
						break;
					}
				}
			}
			if (breakflag==1) break;
		}
		fclose(fpsikona);
		fclose(fpsikona2);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		/////変換処理ここまで/////
		//四股名読み込み//////
		FILE *fp;
		fp = fopen("kaiwadata/str_jflag.dat","rb");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "kaiwadata/str_jflag.datをつくる処理をしたはずなのにファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1;
			return ;		
		}
		//ここから読み込み
		fread(temp_str_jflag,sizeof(temp_str_jflag),1,fp);
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (i=0;i<jflagSHURUISUU;i++){
			for (ii=0;ii<21;ii++){
				str_jflag[i][ii]=0;
			}
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		for (i=0;i<jflagSHURUISUU;i++){
			strcpy(str_jflag[i],temp_str_jflag[i]);
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}

	/////////////type////////////////
	////変換処理//////////////////////
	//FILE *fpsikona;
	//FILE *fpsikona2;
	//////////////////////
	fpsikona = fopen("kaiwadata/str_type.csv","rb");
	if( fpsikona == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "kaiwadata/str_type.csvが見つかりません" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		mode=1;
		return ;
	}else{
		fpsikona2 = fopen("kaiwadata/str_type.dat","wb");
		if( fpsikona2 == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "kaiwadata/str_type.datファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1;
			return ;
		}
		mojibytesuu=0;
		totalbytesuu=0;
		breakflag=0;
		while(1)
		{
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (totalbytesuu>=typeSHURUISUU*21){//フラグ種類数×20バイト(全角10文字分)だけどデータ的に21バイト
				ch=0x00;
				fseek(fpsikona2,-1,SEEK_CUR);
				fwrite(&ch,sizeof(ch),1,fpsikona2);
				break;
			}
			mojibytesuu=0;
			while(1){
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (mojibytesuu>=20){
					ch=0x00;
					fwrite(&ch,sizeof(ch),1,fpsikona2);
					fseek(fpsikona,+1,SEEK_CUR);
					totalbytesuu++;
					break;
				}else{
					if (fread(&ch,sizeof(ch),1,fpsikona)>=1){
						if (ch==0x0d){
							ch=0x00;
							for (i=mojibytesuu;i<21;i++){//21バイトにするため
								fwrite(&ch,sizeof(ch),1,fpsikona2);
								totalbytesuu++;
							}
							break;
						}else if(ch==0x0a){

						}else{
							fwrite(&ch,sizeof(ch),1,fpsikona2);
							mojibytesuu++;
							totalbytesuu++;
						}
					}else{
						breakflag=1;
						break;
					}
				}
			}
			if (breakflag==1) break;
		}
		fclose(fpsikona);
		fclose(fpsikona2);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		/////変換処理ここまで/////
		//四股名読み込み//////
		FILE *fp;
		fp = fopen("kaiwadata/str_type.dat","rb");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "kaiwadata/str_type.datをつくる処理をしたはずなのにファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1;
			return ;		
		}
		//ここから読み込み
		fread(temp_str_type,sizeof(temp_str_type),1,fp);
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (i=0;i<typeSHURUISUU;i++){
			for (ii=0;ii<21;ii++){
				str_type[i][ii]=0;
			}
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		for (i=0;i<typeSHURUISUU;i++){
			strcpy(str_type[i],temp_str_type[i]);
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}

	/////////////str_human////////////////
	////変換処理//////////////////////
	//FILE *fpsikona;
	//FILE *fpsikona2;
	//////////////////////
	fpsikona = fopen("kaiwadata/str_human.csv","rb");
	if( fpsikona == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "kaiwadata/str_human.csvが見つかりません" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		mode=1;
		return ;
	}else{
		fpsikona2 = fopen("kaiwadata/str_human.dat","wb");
		if( fpsikona2 == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "kaiwadata/str_human.datファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1;
			return ;
		}
		mojibytesuu=0;
		totalbytesuu=0;
		breakflag=0;
		while(1)
		{
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (totalbytesuu>=HUMANSUU*21){//フラグ種類数×20バイト(全角10文字分)だけどデータ的に21バイト
				ch=0x00;
				fseek(fpsikona2,-1,SEEK_CUR);
				fwrite(&ch,sizeof(ch),1,fpsikona2);
				break;
			}
			mojibytesuu=0;
			while(1){
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (mojibytesuu>=20){
					ch=0x00;
					fwrite(&ch,sizeof(ch),1,fpsikona2);
					fseek(fpsikona,+1,SEEK_CUR);
					totalbytesuu++;
					break;
				}else{
					if (fread(&ch,sizeof(ch),1,fpsikona)>=1){
						if (ch==0x0d){
							ch=0x00;
							for (i=mojibytesuu;i<21;i++){//21バイトにするため
								fwrite(&ch,sizeof(ch),1,fpsikona2);
								totalbytesuu++;
							}
							break;
						}else if(ch==0x0a){

						}else{
							fwrite(&ch,sizeof(ch),1,fpsikona2);
							mojibytesuu++;
							totalbytesuu++;
						}
					}else{
						breakflag=1;
						break;
					}
				}
			}
			if (breakflag==1) break;
		}
		fclose(fpsikona);
		fclose(fpsikona2);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		/////変換処理ここまで/////
		//四股名読み込み//////
		FILE *fp;
		fp = fopen("kaiwadata/str_human.dat","rb");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "kaiwadata/str_human.datをつくる処理をしたはずなのにファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1;
			return ;		
		}
		//ここから読み込み
		fread(temp_str_human,sizeof(temp_str_human),1,fp);
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (i=0;i<HUMANSUU;i++){
			for (ii=0;ii<21;ii++){
				str_human[i][ii]=0;
			}
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		for (i=0;i<HUMANSUU;i++){
			strcpy(str_human[i],temp_str_human[i]);
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}


	///////////////////////////////////////////
	/////////aikaiwadata読込////////////
	///////////////////////////////////////////
	//読み込み
	FILE *fpcsv;
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	fpcsv = fopen("kaiwadata/aikaiwadata.csv","r");
	if( fpcsv == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "kaiwadata/aikaiwadata.csvファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		mode=1;
		return ;		
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}else{
		kazu=0;
		while(1) 
		{
			for (ii=0;ii<101;ii++){
				temp_string_suu[ii]=0;
			}
			for (ii=0;ii<100;ii++){
				ch = fgetc(fpcsv);
				if (ch == EOF){break;}
				if(ch == '\n' || ch == ','){
					break;
				}else{
					if(ch=='0'){
						strcat(temp_string_suu,"0");
					}else if(ch=='1'){
						strcat(temp_string_suu,"1");
					}else if(ch=='2'){
						strcat(temp_string_suu,"2");
					}else if(ch=='3'){
						strcat(temp_string_suu,"3");
					}else if(ch=='4'){
						strcat(temp_string_suu,"4");
					}else if(ch=='5'){
						strcat(temp_string_suu,"5");
					}else if(ch=='6'){
						strcat(temp_string_suu,"6");
					}else if(ch=='7'){
						strcat(temp_string_suu,"7");
					}else if(ch=='8'){
						strcat(temp_string_suu,"8");
					}else if(ch=='9'){
						strcat(temp_string_suu,"9");
					//}else if(ch=='-'){
					//	strcat(temp_string_suu,"-");
					}
				}
			}
			if (ch == EOF){break;}
			if (kazu>=28){
				if (kazu%14==0){
					temp_id=atoi(temp_string_suu);
					if (temp_id>=AISUU || temp_id<0){
						temp_id=0;
					}
				}else if(kazu%14==1){
					aikaiwadata[temp_id].sekkyokusei=atoi(temp_string_suu);
				}else if(kazu%14==2){
					aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=atoi(temp_string_suu);
					if (aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]<=0){
						aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=1;
					}
				}else if(kazu%14==3){
					aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=atoi(temp_string_suu);
					if (aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]<=0){
						aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=1;
					}
				}else if(kazu%14==4){
					aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=atoi(temp_string_suu);
					if (aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]<=0){
						aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=1;
					}
				}else if(kazu%14==5){
					aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=atoi(temp_string_suu);
					if (aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]<=0){
						aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=1;
					}
				}else if(kazu%14==6){
					aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=atoi(temp_string_suu);
					if (aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]<=0){
						aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=1;
					}
				}else if(kazu%14==7){
					aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=atoi(temp_string_suu);
					if (aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]<=0){
						aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=1;
					}
				}else if(kazu%14==8){
					aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=atoi(temp_string_suu);
					if (aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]<=0){
						aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=1;
					}
				}else if(kazu%14==9){
					aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=atoi(temp_string_suu);
					if (aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]<=0){
						aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=1;
					}
				}else if(kazu%14==10){
					aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=atoi(temp_string_suu);
					if (aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]<=0){
						aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=1;
					}
				}else if(kazu%14==11){
					aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=atoi(temp_string_suu);
					if (aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]<=0){
						aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=1;
					}
				}else if(kazu%14==12){
					aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=atoi(temp_string_suu);
					if (aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]<=0){
						aikaiwadata[temp_id].hyoujou_konomi[(kazu%14)-2]=1;
					}
				}else if(kazu%14==13){
					aikaiwadata[temp_id].type=atoi(temp_string_suu);
					if (aikaiwadata[temp_id].type<0){
						aikaiwadata[temp_id].type=0;
					}
					if (aikaiwadata[temp_id].type>=typeSHURUISUU){
						aikaiwadata[temp_id].type=0;
					}
				}
			}
			kazu++;

			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		fclose(fpcsv);
	}

	///////////////////////////////////////////
	/////////humankaiwadata読込////////////
	///////////////////////////////////////////
	//読み込み
	//FILE *fpcsv;
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	fpcsv = fopen("kaiwadata/humankaiwadata.csv","r");
	if( fpcsv == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "kaiwadata/humankaiwadata.csvファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		mode=1;
		return ;		
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}else{
		kazu=0;
		while(1) 
		{
			for (ii=0;ii<101;ii++){
				temp_string_suu[ii]=0;
			}
			for (ii=0;ii<100;ii++){
				ch = fgetc(fpcsv);
				if (ch == EOF){break;}
				if(ch == '\n' || ch == ','){
					break;
				}else{
					if(ch=='0'){
						strcat(temp_string_suu,"0");
					}else if(ch=='1'){
						strcat(temp_string_suu,"1");
					}else if(ch=='2'){
						strcat(temp_string_suu,"2");
					}else if(ch=='3'){
						strcat(temp_string_suu,"3");
					}else if(ch=='4'){
						strcat(temp_string_suu,"4");
					}else if(ch=='5'){
						strcat(temp_string_suu,"5");
					}else if(ch=='6'){
						strcat(temp_string_suu,"6");
					}else if(ch=='7'){
						strcat(temp_string_suu,"7");
					}else if(ch=='8'){
						strcat(temp_string_suu,"8");
					}else if(ch=='9'){
						strcat(temp_string_suu,"9");
					//}else if(ch=='-'){
					//	strcat(temp_string_suu,"-");
					}
				}
			}
			if (ch == EOF){break;}
			if (kazu>=0 && kazu<HUMANSUU){
				humankaiwadata[kazu].type=atoi(temp_string_suu);
			}

			kazu++;

			if (kazu>=HUMANSUU) break;

			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		fclose(fpcsv);
	}


	return;
}

void edit_type(void)
{
	int i;
	///////////////////type編集画面/////////////////////////
loop_typehenshuu:
	ClearDrawScreen();
	DrawString(200,5,"言葉タイプ名称編集画面",CRWHITE);
	for (i=0;i<typeSHURUISUU;i++){
		DrawFormatString(10,88+i*16,CRGREEN,"%s",str_type[humankaiwadata[i].type]);
	}


	DrawString(10,30,"戻る",CRGREEN);

	DrawString(0,413-16,"名称をクリックで名称を変更できます、",CRWHITE);

	ScreenFlip();

	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける 
	while(1){
		while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
		while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){Sleep(1);}

		if (get_mouseclick(10,30,10+80,30+16)==1){
			return;
		}
		for (i=0;i<typeSHURUISUU;i++){
			if (get_mouseclick(10,88+i*16,10+200,88+i*16+16)==1){
				editstr_type(humankaiwadata[i].type);
				WaitTimer(200);
				goto loop_typehenshuu;
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

	return;
}

void edit_rikisiaidata(int x)
{
	struct ai_data temp_aikaiwadata;//AIごとの個性のデータ
	int i,ii;
	int rikisi_front_edit;
	int x1_gazou;
	int y1_gazou;
	int x2_gazou;
	int y2_gazou;
	int x3_gazou;
	int y3_gazou;
	int x4_gazou;
	int y4_gazou;
	int shukushou_tate_gazou;
	int shukushou_yoko_gazou;
	int chousei_x;
	int chousei_y;
	char temp_filename[MAX_PATH];
	for (i=0;i<MAX_PATH;i++){
		temp_filename[i]=0;
	}

	temp_aikaiwadata=aikaiwadata[x];
	///////////////////力士AIの性格・言葉タイプ編集/////////////////////////
loop_aihenshuu:
	ClearDrawScreen();
	DrawFormatString(10,5,CRWHITE,"%s (画像ID %d)の性格・言葉タイプ編集画面",namestring[x],x);
	DrawString(10,30,"戻る(確定)",CRGREEN);
	DrawString(200,30,"戻る(キャンセル)",CRGREEN);

	//力士画像表示
	chousei_x=150;
	chousei_y=-200;
	sprintf(temp_filename,"rikisigraph/rikisi%d.png\0",x);
	rikisi_front_edit = LoadGraph( temp_filename ) ;
	shukushou_tate_gazou=(int)(220-rikisidata[x].sinchou)*2/3;
	shukushou_yoko_gazou=(int)((250-rikisidata[x].taijuu)/2);
	if (shukushou_tate_gazou<0){shukushou_tate_gazou=0;}
	if (shukushou_yoko_gazou<0){shukushou_yoko_gazou=0;}
	x1_gazou=387-32+chousei_x;
	y1_gazou=239+shukushou_tate_gazou+chousei_y;
	x2_gazou=x1_gazou+128-shukushou_yoko_gazou;
	y2_gazou=y1_gazou;
	x3_gazou=x2_gazou;
	y3_gazou=y1_gazou+128-shukushou_tate_gazou;
	x4_gazou=x1_gazou;
	y4_gazou=y3_gazou;
	DrawModiGraph(x1_gazou,y1_gazou ,	x2_gazou,y2_gazou , x3_gazou,y3_gazou , x4_gazou,y4_gazou , rikisi_front_edit , TRUE ) ;


	i=0;
	DrawString(10,88+i*20,"喜び",CRWHITE);
	DrawFormatString(200,88+i*20,CRGREEN,"%d",aikaiwadata[x].hyoujou_konomi[i]);i++;
	DrawString(10,88+i*20,"怒り",CRWHITE);
	DrawFormatString(200,88+i*20,CRGREEN,"%d",aikaiwadata[x].hyoujou_konomi[i]);i++;
	DrawString(10,88+i*20,"冷笑",CRWHITE);
	DrawFormatString(200,88+i*20,CRGREEN,"%d",aikaiwadata[x].hyoujou_konomi[i]);i++;
	DrawString(10,88+i*20,"励まし",CRWHITE);
	DrawFormatString(200,88+i*20,CRGREEN,"%d",aikaiwadata[x].hyoujou_konomi[i]);i++;
	DrawString(10,88+i*20,"真剣",CRWHITE);
	DrawFormatString(200,88+i*20,CRGREEN,"%d",aikaiwadata[x].hyoujou_konomi[i]);i++;
	DrawString(10,88+i*20,"泣く",CRWHITE);
	DrawFormatString(200,88+i*20,CRGREEN,"%d",aikaiwadata[x].hyoujou_konomi[i]);i++;
	DrawString(10,88+i*20,"不安",CRWHITE);
	DrawFormatString(200,88+i*20,CRGREEN,"%d",aikaiwadata[x].hyoujou_konomi[i]);i++;
	DrawString(10,88+i*20,"暗い",CRWHITE);
	DrawFormatString(200,88+i*20,CRGREEN,"%d",aikaiwadata[x].hyoujou_konomi[i]);i++;
	DrawString(10,88+i*20,"笑顔",CRWHITE);
	DrawFormatString(200,88+i*20,CRGREEN,"%d",aikaiwadata[x].hyoujou_konomi[i]);i++;
	DrawString(10,88+i*20,"渋い",CRWHITE);
	DrawFormatString(200,88+i*20,CRGREEN,"%d",aikaiwadata[x].hyoujou_konomi[i]);i++;

	DrawString(10,88+11*20,"言葉タイプ",CRWHITE);
	if (aikaiwadata[x].type>=0 && aikaiwadata[x].type<typeSHURUISUU){
		DrawFormatString(200,88+11*20,CRGREEN,"%s (typeID %d)",str_type[aikaiwadata[x].type],aikaiwadata[x].type);
	}

	DrawFormatStringToHandle(0,350,CRWHITE,FontHandle12,"※性格は、%sが会話相手のどんな表情を見たいのかをあらわし、\n数字が多いほうが見たい表情、少ないほうが見たくない表情になります",namestring[x]);

	DrawString(0,413-32,"緑文字・数字を左右クリックで変更できます",CRWHITE);

	DrawFormatString(0,413,CRWHITE,"※画像は「rikisigraph」フォルダの中の「rikisi%d.png」",x);

	DrawStringToHandle(0,413+18,"※ここでの変更が全てのゲームの同じ画像IDの力士にも影響を与えてしまう\n欠陥を抱えています",CRWHITE,FontHandle12);

	ScreenFlip();

	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける 
	while(1){
		while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
		while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){Sleep(1);}
		if (get_mouseclick(200,30,200+80,30+16)==1){//元に戻す
			aikaiwadata[x]=temp_aikaiwadata;
			WaitTimer(200);
			return;
		}
		if (get_mouseclick(10,30,10+80,30+16)==1){//戻る
			//csvファイル上書き
			FILE *fp;
			fp = fopen("kaiwadata/aikaiwadata.csv","w");
			fprintf(fp,"※３列目から１２列目は各ＡＩが会話相手のどんな表情を見るのが好きなのかを表します(1～20),,,,,,,,,,,,,\n");
			fprintf(fp,"ＡＩの画像ＩＤ,積極性,喜び,怒り,冷笑,励まし,真剣な,泣く,不安,暗い,笑顔,渋い,データ未発見表情,言葉タイプ\n");
			for (i=0;i<AISUU;i++){
				fprintf(fp,"%d,%d"
				,i
				,aikaiwadata[i].sekkyokusei);
				for (ii=0;ii<HYOUJOUSHURUISUU;ii++){
					fprintf(fp,",%d"
					,aikaiwadata[i].hyoujou_konomi[ii]);
				}
				fprintf(fp,",%d\n"
				,aikaiwadata[i].type);
			}
			fclose(fp);
			WaitTimer(200);
			return;
		}
		if (get_mouseclick(200,88+11*20,200+200,88+11*20+16)==1){
			if (aikaiwadata[x].type<typeSHURUISUU-1){
				aikaiwadata[x].type++;
			}else{
				aikaiwadata[x].type=0;
			}
			WaitTimer(200);
			goto loop_aihenshuu;
		}
		if (get_mouseclick(200,88+11*20,200+200,88+11*20+16)==2){
			if (aikaiwadata[x].type>0){
				aikaiwadata[x].type--;
			}else{
				aikaiwadata[x].type=typeSHURUISUU-1;
			}
			WaitTimer(200);
			goto loop_aihenshuu;
		}
		for (i=0;i<HYOUJOUSHURUISUU-1;i++){
			if (get_mouseclick(200,88+i*20,200+200,88+i*20+16)==1){
				if (aikaiwadata[x].hyoujou_konomi[i]<20){
					aikaiwadata[x].hyoujou_konomi[i]++;
				}else{
					aikaiwadata[x].hyoujou_konomi[i]=1;
				}
				goto loop_aihenshuu;
			}
			if (get_mouseclick(200,88+i*20,200+200,88+i*20+16)==2){
				if (aikaiwadata[x].hyoujou_konomi[i]>1){
					aikaiwadata[x].hyoujou_konomi[i]--;
				}else{
					aikaiwadata[x].hyoujou_konomi[i]=20;
				}
				WaitTimer(200);
				goto loop_aihenshuu;
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
	return;
}


void csvinput_kaiwa(void)
{
	int i,ii,mojibytesuu,breakflag;
	char temp_string_suu[1001];
	char ch=0;
	int kazu=0;
	char errflag=0;
	long fpendflag=0;
	short int temp_shortint=0;
	short int temp_hanasiteid=0;
	short int last_hanasiteid=0;
	char temp_hyoujounum=0;
	char temp_char=0;
	char last_type=0;
	char temp_type=0;
	char temp_bundanflag=0;
	char temp_kaiwastr[MAXMOJISUU_kaiwa];
	int nagasa_inputstr=0;
	char kiridasistr[3];
	long filesize_kaiwadata[MAXFILESUU];
	char temp_filename[MAX_PATH];
	for (i=0;i<MAXFILESUU;i++){
		filesize_kaiwadata[i]=0;
	}
	for (i=0;i<MAX_PATH;i++){
		temp_filename[i]=0;
	}
	for (i=0;i<3;i++){
		kiridasistr[i]=0;
	}

	for (i=0;i<1001;i++){
		temp_string_suu[i]=0;
	}
	for (i=0;i<MAXMOJISUU_kaiwa;i++){
		temp_kaiwastr[i]=0;
	}

	//確認画面
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString(200,5,"会話データ一斉入力確認画面",CRWHITE);
	DrawString(187,100,"この機能も検証不十分です",CRRED);
	DrawString(187,120,"不具合のリスクをご承知のうえご利用ください",CRRED);
	DrawString(187,137,"(場合によっては今までの会話データが完全に",CRRED);
	DrawString(187,154,"使い物にならなくなる可能性もあります)",CRRED);
	DrawString(187,180,"念のため、kaiwadata>kaiwadata数字.datの",CRWHITE);
	DrawString(187,200,"バックアップを取ってから利用されることを",CRWHITE);
	DrawString(187,220,"おすすめします",CRWHITE);
	DrawString(187,260,"また、一連の会話ごとでの読込をおすすめします",CRWHITE);
	DrawString(187,280,"(一連の会話の最初の発言にはフラグを立てているため)",CRWHITE);
	DrawString(187,369+16,"input>kaiwa.csvの内容で会話データの読み込みを",CRWHITE);
	DrawString(187,369+32,"試みますがよろしいですか？",CRWHITE);
	//DrawString(187,369+48,"本当に上書きしてもよろしいですか",CRWHITE);
	DrawString(187,369+64,"下の緑色の文字をクリックして選択してください",CRWHITE);
	DrawString(187,369+80,"　　　読み込む　　　　キャンセル",CRGREEN);
	ScreenFlip();
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1){
		if (get_mouseclick(187,369+80,187+16*9,369+96)){
			break;
		}
		if (get_mouseclick(187+16*10,369+80,187+16*18,369+96)){
			return;
		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){
			mode=1;
			return ;	// エラーが発生したらループを抜ける
		}
		Sleep(1);
	}


	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawBox(0,0,639,479,CRBACK,TRUE);
	DrawString( 250 , 240 - 32 , "会話データ入力中です" , CRWHITE );
	DrawString( 250 , 272 - 32 , "お待ちください" , CRWHITE );
	//DrawString( 250 , 304 - 32 , "Hit any key" , CRWHITE );
	ScreenFlip() ;//裏画面を表画面にコピー

	///////////////////////////////////////////
	/////////一斉入力用input/kaiwa.csv読込////////////
	///////////////////////////////////////////
	//読み込み
	FILE *fp_moto;
	FILE *fp_temp1;
	FILE *fp_temp2;
	FILE *fp_temp3;

	//////////////////////数字である１列目と３列目をバイナリファイルに変換//////////////
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	fp_moto = fopen("input/kaiwa.csv","r");
	if( fp_moto == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "input/kaiwa.csvファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		mode=1;
		return ;		
	}else{
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		fp_temp1 = fopen("input/kaiwa_temp1.dat","wb");
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		fp_temp3 = fopen("input/kaiwa_temp3.dat","wb");
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		kazu=0;
		while(1) 
		{
			if (kazu%3==1){
				for (ii=0;ii<10000;ii++){
					ch = fgetc(fp_moto);
					if (ch == EOF){break;}
					if(ch==0x0a || ch==0x2c){
						break;
					}
				}
			}else{
				for (ii=0;ii<1001;ii++){
					temp_string_suu[ii]=0;
				}
				for (ii=0;ii<1000;ii++){
					ch = fgetc(fp_moto);
					if (ch == EOF){break;}
					if(ch==0x0a || ch==0x2c){
						break;
					}else{
						if(ch=='0'){
							strcat(temp_string_suu,"0");
						}else if(ch=='1'){
							strcat(temp_string_suu,"1");
						}else if(ch=='2'){
							strcat(temp_string_suu,"2");
						}else if(ch=='3'){
							strcat(temp_string_suu,"3");
						}else if(ch=='4'){
							strcat(temp_string_suu,"4");
						}else if(ch=='5'){
							strcat(temp_string_suu,"5");
						}else if(ch=='6'){
							strcat(temp_string_suu,"6");
						}else if(ch=='7'){
							strcat(temp_string_suu,"7");
						}else if(ch=='8'){
							strcat(temp_string_suu,"8");
						}else if(ch=='9'){
							strcat(temp_string_suu,"9");
						//}else if(ch=='-'){
						//	strcat(temp_string_suu,"-");
						}
					}
				}
			}
			if (ch == EOF){break;}
			if (kazu>=15){
				if (kazu%3==0){
					temp_shortint=atoi(temp_string_suu);
					if ((temp_shortint>=0 && temp_shortint<AISUU)
					|| (temp_shortint>=10000 && temp_shortint<10010)
					){

						fwrite(&temp_shortint,sizeof(temp_shortint),1,fp_temp1);
					}else{
						ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
						DrawFormatString( 0 , 240 - 32 ,CRWHITE, "何一つデータ入力はしていません\ninput/kaiwa.csvの一列目の%d行目の読み取りに失敗" , (int)(kazu/3)+1 );
						DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
						ScreenFlip() ;//裏画面を表画面にコピー
						WaitKey();
						return ;		
					}
				}
				if (kazu%3==2){
					temp_char=atoi(temp_string_suu);
					if ((temp_char>=0 && temp_char<HYOUJOUSHURUISUU-1)
					){
						fwrite(&temp_char,sizeof(temp_char),1,fp_temp3);
					}else{
						ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
						DrawFormatString( 0 , 240 - 32 ,CRWHITE, "何一つデータ入力はしていません\ninput/kaiwa.csvの三列目の%d行目の読み取りに失敗" , (int)(kazu/3)+1 );
						DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
						ScreenFlip() ;//裏画面を表画面にコピー
						WaitKey();
						return ;		
					}
				}
				if (kazu%3==1){
				}

			}

			kazu++;
			if (kazu>1000000*3+15) break;//一応100万件まで

			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			Sleep(1);
		}
		fclose(fp_moto);
		fclose(fp_temp1);
		fclose(fp_temp3);
	}

	//////////////////////文字列である２列目をバイナリファイルに変換//////////////
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	fp_temp2 = fopen("input/kaiwa_temp2.dat","wb");
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	fp_moto = fopen("input/kaiwa.csv","rb");
	if( fp_moto == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "input/kaiwa.csvファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		mode=1;
		return ;		
	}else{
		kazu=0;
		breakflag=0;
		while(1) 
		{
			if (kazu>=15 && kazu%3==1){
				mojibytesuu=0;
				breakflag=0;
				mojibytesuu=0;
				while(1){
					if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (mojibytesuu>=MAXMOJISUU_kaiwa-1){
						ch=0x00;
						fwrite(&ch,sizeof(ch),1,fp_temp2);
						break;
					}else{
						if (fread(&ch,sizeof(ch),1,fp_moto)>=1){
							if (ch == '\n' || ch == ','){
								ch=0x00;
								for (i=mojibytesuu;i<MAXMOJISUU_kaiwa;i++){//MAXMOJISUU_kaiwaバイトにするため
									fwrite(&ch,sizeof(ch),1,fp_temp2);
								}
								break;
							}else{
								fwrite(&ch,sizeof(ch),1,fp_temp2);
								mojibytesuu++;
							}
						}else{
							breakflag=1;
							break;
						}
					}
				}
			}else{
				for (ii=0;ii<10000;ii++){
					if (fread(&ch,sizeof(ch),1,fp_moto)>=1){
						if (ch == '\n' || ch == ','){
							break;
						}
					}else{
						break;
					}
				}
			}
			//バイナリ読込の場合どうなるかわからなかったので二つのループ出る文
			if (breakflag==1) break;
			if (ch == EOF){break;}

			kazu++;
			if (kazu>1000000*3+15) break;//一応100万件まで
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			Sleep(1);
		}
		fclose(fp_moto);
		fclose(fp_temp2);
	}

	/////変換処理ここまで/////

	///////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////各バイナリファイルを読み込みながらkaiwadata%d.datに追記//////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	fp_temp1 = fopen("input/kaiwa_temp1.dat","rb");
	// オープンできなかったらここで終了
	if( fp_temp1 == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "input/kaiwa_temp1.datをつくる処理をしたはずなのにファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return ;		
	}
	fp_temp2 = fopen("input/kaiwa_temp2.dat","rb");
	// オープンできなかったらここで終了
	if( fp_temp2 == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "input/kaiwa_temp2.datをつくる処理をしたはずなのにファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return ;		
	}
	fp_temp3 = fopen("input/kaiwa_temp3.dat","rb");
	// オープンできなかったらここで終了
	if( fp_temp3 == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "input/kaiwa_temp3.datをつくる処理をしたはずなのにファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return ;		
	}
	//書き込み処理
	//ファイルサイズ確認して連番ファイルを作成する必要がある
	//各連番ファイルのサイズ取得
	for (ii=0;ii<MAXFILESUU;ii++){
		sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",ii);
		filesize_kaiwadata[ii]=Getfilesize(temp_filename);
		if (filesize_kaiwadata[ii]<0) break;
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//ファイル(追記)オープン
	for (ii=0;ii<MAXFILESUU;ii++){
		if (filesize_kaiwadata[ii]<=maxfilesize){
			sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",ii+1);
			fp_moto = fopen(temp_filename,"ab");
			if (fp_moto == NULL){ClearDrawScreen();DrawFormatString(100,200,CRRED,"%sのファイルオープンに失敗",temp_filename);ScreenFlip();return;}
			break;
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

	//ファイル終端までループ
	kazu=0;
	last_hanasiteid=-1;
	last_type=0;
	errflag=0;
	while(1){
		fpendflag=fread(&temp_hanasiteid,sizeof(temp_hanasiteid),1,fp_temp1);//発言者ID
		if (fpendflag == 0) break;
		fpendflag=fread(&temp_hyoujounum,sizeof(temp_hyoujounum),1,fp_temp3);//表情num
		if (fpendflag == 0) errflag=3;
		fpendflag=fread(temp_kaiwastr,sizeof(temp_kaiwastr),1,fp_temp2);
		if (fpendflag == 0) errflag=2;

		//ここで全角チェック
		if (check_hiragana(temp_kaiwastr)!=1){
			errflag=1;
		}
		//ここで？語尾上げチェック
/*
		nagasa_inputstr=strlen(temp_kaiwastr);
		strncpy( kiridasistr , temp_kaiwastr+nagasa_inputstr-2 , 2 );
		kiridasistr[2]=0;
		if (strcmp(kiridasistr,"？")==0){
			temp_gobiageflag=1;
		}else{
			temp_gobiageflag=0;
		}
*/
		//ここで最初の書き込みのみ分断フラグ
		if (kazu==0){
			temp_bundanflag=1;
		}else{
			temp_bundanflag=0;
		}
		//話し手側言葉タイプtemp_type
		if (temp_hanasiteid<AISUU && temp_hanasiteid>=0){
			temp_type=aikaiwadata[temp_hanasiteid].type;
		}else if (temp_hanasiteid>=10000 && temp_hanasiteid<10010){
			temp_type=humankaiwadata[temp_hanasiteid-10000].type;
		}else{
			errflag=1;//エラーやけどしょうがない
		}

		if (errflag==1){//改行後EOFでerrflag2,3でも引っかかるからこうした
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawFormatString( 0 , 0,CRRED , "%d件目の全角チェックかIDでひっかかりました" , kazu+1 );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			break;
		}
		if (errflag>0) break;
		//ここから書き込み
		fwrite(&temp_hanasiteid,sizeof(temp_hanasiteid),1,fp_moto);//発言者ID
		fwrite(&temp_hyoujounum,sizeof(temp_hyoujounum),1,fp_moto);
		fwrite(temp_kaiwastr,sizeof(temp_kaiwastr),1,fp_moto);
		fwrite(&temp_bundanflag,sizeof(temp_bundanflag),1,fp_moto);
		//全部study済みにしてしまえ
		temp_char=1;
		fwrite(&temp_char,sizeof(temp_char),1,fp_moto);//studyflag
		//day_kaiwaは関係ないけど0にしてみた
		temp_char=0;
		fwrite(&temp_char,sizeof(temp_char),1,fp_moto);//day_kaiwa
		//jflagは一般会話の0
		temp_char=0;
		fwrite(&temp_char,sizeof(temp_char),1,fp_moto);//jflag
		//話し手側言葉タイプ
		fwrite(&temp_type,sizeof(temp_type),1,fp_moto);//話し手id_hanasiteの言葉タイプ
		//話題対象力士フラグは一般会話に関係ないので全部0
		temp_char=0;
		fwrite(&temp_char,sizeof(temp_char),1,fp_moto);
		fwrite(&temp_char,sizeof(temp_char),1,fp_moto);
		fwrite(&temp_char,sizeof(temp_char),1,fp_moto);

		//last_に代入
		last_hanasiteid=temp_hanasiteid;
		last_type=temp_type;
		
		kazu++;
		if (kazu>1000000) break;//一応100万件まで

		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		Sleep(1);
	}
	fclose(fp_moto);
	fclose(fp_temp1);
	fclose(fp_temp2);
	fclose(fp_temp3);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString( 250 , 272-64,CRGREEN , "%d件の読み取り完了" , kazu );
	DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();

	return;
}

void csvoutput_kaiwa(void)
{
	int i;
	long fpendflag=0;
	short int temp_shortint=0;
	char temp_char=0;
	char temp_hyoujounum=0;
	char temp_kaiwastr[MAXMOJISUU_kaiwa];
	char temp_filename[MAX_PATH];
	for (i=0;i<MAX_PATH;i++){
		temp_filename[i]=0;
	}
	for (i=0;i<MAXMOJISUU_kaiwa;i++){
		temp_kaiwastr[i]=0;
	}
	FILE *fpcsv;
	FILE *fp;
	fpcsv = fopen("output/kaiwa.csv","w");
	fprintf(fpcsv,"一般的な会話(話題選択画面の0)のみ登録できます。6行目から読み込みます。,,\n");
	fprintf(fpcsv,"※１列目→半角数字。AIは力士画像を右クリックして表示される画像の番号部分、人間は10000～10009,,\n");
	fprintf(fpcsv,"※2列目→会話中に使用できる文字は限られています。一応読み込み時にそのチェックをかけます。,,\n");
	fprintf(fpcsv,"※3列目→半角数字で0か1。喜びは0、怒りは1、冷笑は2、励ましは3、真剣は4、泣くは5、不安は6、暗いは7、笑顔は8、渋いは9,,\n");
//	fprintf(fpcsv,"画像IDもしくは人間ID,発言(全角でしかも２５文字以内),表情\n");
fprintf(fpcsv,"画像IDもしくは人間ID,発言(全角でしかも２５文字以内),表情,jflag\n");

temp_shortint=0;
		sprintf(temp_filename,"kaiwadata/kaiwadata%d.dat\0",temp_shortint+1);
		fp = fopen(temp_filename,"rb");
		if (fp == NULL){ClearDrawScreen();DrawFormatString(100,200,CRRED,"%sのファイルオープンに失敗",temp_filename);ScreenFlip();mode_kaiwa=1;return;}
		if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
		//ファイル終端まで読込
		while(1){
			fpendflag=fread(&temp_shortint,sizeof(id_hanasite),1,fp);
			if (fpendflag == 0) break;

	fprintf(fpcsv,"%d,",temp_shortint);

			fread(&temp_hyoujounum,sizeof(hyoujounum),1,fp);
			fread(temp_kaiwastr,sizeof(kaiwastr),1,fp);

	fprintf(fpcsv,"%s,",temp_kaiwastr);
//	fprintf(fpcsv,"%d\n",temp_hyoujounum);
fprintf(fpcsv,"%d,",temp_hyoujounum);

			fread(&temp_char,sizeof(kaiwabundanflag),1,fp);
			fread(&temp_char,sizeof(studyflag),1,fp);
			fread(&temp_char,sizeof(day_kaiwa),1,fp);
			fread(&temp_char,sizeof(jflag),1,fp);

fprintf(fpcsv,"%d\n",temp_char);

			fread(&temp_char,sizeof(aikaiwadata[0].type),1,fp);
			fread(&temp_char,sizeof(wrikisidata[0].sumoflag),1,fp);
			fread(&temp_char,sizeof(wrikisidata[0].suu_winlost),1,fp);
			fread(&temp_char,sizeof(wrikisidata[0].nokoribansuu),1,fp);
			if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
		}

	fclose(fp);

	fclose(fpcsv);


	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	//DrawFormatString( 250 , 272-64,CRGREEN , "%d件の読み取り完了" , kazu );
	DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();

	return;
}