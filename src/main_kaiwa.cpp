#include "DxLib.h"
#include <stdio.h>
#include <string.h>
#include "define.h"
#include "sub_kaiwa.h"


char katati_kaiwa;//0→人間と力士AIの会話、1→力士AIと力士AIの会話
extern int shozokurikisisuu[HEYASUU];//部屋IDごとの所属力士数
extern char heyastring[HEYASUU][12];//(54部屋分,全角５文字まで)相撲部屋

//登場人物は人間・ＡＩ合わせて合計32768人、IDは0～707が力士のAI、708～999一般AI，1000～32767人間
//プロトタイプでは人間(入力者)は10000、相手方仮想人間が10001～3
struct ai_data aikaiwadata[AISUU];//AIごとの個性のデータ
struct human_data humankaiwadata[HUMANSUU];//AIごとの個性のデータ
struct wrikisi_data wrikisidata[1];//話題対象力士データ

char str_jflag[jflagSHURUISUU][21];
char str_type[typeSHURUISUU][21];
char str_human[HUMANSUU][21];

//状況フラグ
char day_kaiwa=0;//場所中の何日目か
char jflag=0;//会話の周りの状況フラグ
			//0→ごくごく一般的な会話状況、2～10はランダム天気
			//11～15→ユーザー定義
			//1→小相撲関連な会話状況→aikaiwadata[].sumoflagのフラグ状況を参照する
			
short int id_hanasite;//話し手
short int id_kikite;//聞き手

char type_hanasite;//話し手の言葉タイプ
char type_kikite;//聞き手の言葉タイプ

char studyflag=0;

int kaiwacount=0;

char kako_str[KAKOHYOJISUU][MAXMOJISUU_kaiwa];//表示用
char kako_hyoujounum[KAKOHYOJISUU];
int kako_id_hanasite[KAKOHYOJISUU];//AI同志の会話の表示用

int mode_kaiwa=0;//1：終了フラグ、2：ゲーム準備処理完了フラグ、
		//9:会話入力からやり直し
		//10:会話入力待ち
		//15:会話入力完了
		//20:表情入力待ち
		//25:表情入力完了

/////////////////////////////////
extern int rikisisentaku_id;
extern int day;
extern char kyuujouflag[RIKISISUU];//1で休場
extern char kyuujoumode;
extern int kyuujoukonbasho[RIKISISUU][15];//今場所の何日目に休場したかrikisidata[].winkonbasho[]みたいなもん
extern struct rikisi_data rikisidata[RIKISISUU];//力士データ用構造体変数708人分用意
//extern rikisidata[RIKISISUU];//力士データ用構造体変数708人分用意


/////////////////////////////////
extern int mode;
extern void game_main_backscreen(void);//基本ゲーム画面表示ルーチン
extern void rikisidatahyoji(int x);//引数として渡された力士IDの能力値等詳細を表示するルーチン
extern char namestring[RIKISISUU][12];//(力士IDごとの四股名,全角５文字まで)四股名

extern int get_mouseclick(int x1,int y1,int x2,int y2);//座標(x1,y1)と(x2,y2)に囲まれたところで
												//クリックしたかどうか
												//当該座標上でクリックしたなら１を返し、
												//そうでなければ、0を返す
extern int MouseInput ;//マウス入力用
extern int MouseX,MouseY;//マウス座標取得用
extern int FontHandle16;
extern int FontHandle12;
extern long maxfilesize;//本番用
//long maxfilesize=1024;//debug用
int filesuu_kaiwadata=0;
char kaiwabundanflag=0;//ゲーム立ち上げ後は前のやり取りとはつながらないので、それをわからせるため
char kaesikaiwabundanflag=0;
char inputstr[ MAXMOJISUU_kaiwa ] ;//人間の発言
char kaesistr[MAXMOJISUU_kaiwa];//AIの発言
char kaiwastr[MAXMOJISUU_kaiwa];//記録する際の発言
char hyoujounum=0;
char kaesihyoujounum=0;
char oumugaesiflag=0;

char str_hyoujou[HYOUJOUSHURUISUU][21];

void kaiwa_start(void);
void kaiwa_main_hyoji(void);
void kaiwa_main(void);//ゲームメインルーチン
int nextspeaking_heya(int now_hanasite,int heyaid);//現在のid_hanasiteを除いて次の話し手(聞き手)を決定させるルーチン

extern long Getfilesize(char name[]);//返り値が0は存在するけどファイルサイズ0、-1→エラー、-2→存在無し

extern int CheckHitKey_test(int a);

void kaiwa_start(void)
{
	char temp_char=0;
	int i,ii;
	int win[RIKISISUU];
	int lost[RIKISISUU];
	int yasumi[RIKISISUU];
	for (i=0;i<RIKISISUU;i++){
		win[i]=0;
		lost[i]=0;
		yasumi[i]=0;
	}
	if (mode_kaiwa==1){
		return;
	}


////////////////////////////////////////////////////////////////////
///////////////////////////debug////////////////////////////////////
/*
{
int i;
FILE *fpdebug;
fpdebug = fopen("debug_chuusha2.txt","w");
fprintf(fpdebug,"画像クリックの直後\n\n");
for (i=0;i<RIKISISUU;i++){
	if (rikisidata[i].yao_win==1){
		fprintf(fpdebug,"画像ID= %3d　は本当の注射勝ち\n",i);
	}
}
fprintf(fpdebug,"\n\n");
for (i=0;i<RIKISISUU;i++){
	if (rikisidata[i].yaowinkonbasho[day-11]==1 && rikisidata[i].yao_win!=1){
		fprintf(fpdebug,"画像ID= %3d　はyaowinkonbashoだけ注射勝ちに…\n",i);
	}
}
fclose(fpdebug);
}
*/
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////




	//ここに初期化処理を書く
	for (i=0;i<MAXMOJISUU_kaiwa;i++){
		inputstr[i]=0;//人間の発言
		kaesistr[i]=0;//AIの発言
		kaiwastr[i]=0;//記録する際の発言
	}
	for (i=0;i<KAKOHYOJISUU;i++){
		for (ii=0;ii<MAXMOJISUU_kaiwa;ii++){
			kako_str[i][ii]=0;
		}
		kako_hyoujounum[i]=0;
		kako_id_hanasite[i]=0;
	}
/*
	///////////////////katati_kaiwa選択画面/////////////////////////
	ClearDrawScreen();
	DrawString(10,5,"会話の形を教えてください",CRWHITE);
	i=0;
	DrawFormatString(10,88+i*16,CRWHITE,"%d→あなたと%sとの１対１の会話",i,namestring[rikisisentaku_id]);i++;

	if (shozokurikisisuu[rikisidata[rikisisentaku_id].heyaid]>=2){
		DrawFormatString(10,88+i*16,CRWHITE,"%d→",i);
		DrawFormatString(40,88+i*16,CRWHITE,"%sの所属する部屋の力士全員で雑談",namestring[rikisisentaku_id]);i++;
	}else{
		DrawFormatString(10,88+i*16,CRGRAY,"%d→",i);
		DrawFormatString(40,88+i*16,CRGRAY,"%sの所属する部屋の力士全員で雑談(選択不可)",namestring[rikisisentaku_id]);i++;
	}

	//DrawString(450,300,"言葉タイプ名称編集",CRGREEN);

	DrawString(10,300,"数字キーを押して選択してください\nＥＳＣキーで戻る",CRWHITE);
	//DrawString(0,413,"言葉タイプを左右クリックで適用する言葉タイプを変更できます",CRWHITE);

	ScreenFlip();

	if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける 
	while(1){
		while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
		while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){Sleep(1);}
		if (CheckHitKey_test( KEY_INPUT_ESCAPE)==1){
			return;
		}
		if (CheckHitKey_test(KEY_INPUT_NUMPAD0)==1 || CheckHitKey_test(KEY_INPUT_0)==1){
			katati_kaiwa=0;
			break;
		}
		if (shozokurikisisuu[rikisidata[rikisisentaku_id].heyaid]>=2){
			if (CheckHitKey_test(KEY_INPUT_NUMPAD1)==1 || CheckHitKey_test(KEY_INPUT_1)==1){
				katati_kaiwa=1;
				break;
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
	///////////////////////////////////////////////////////////
*/
katati_kaiwa=0;
	if (katati_kaiwa==0){
		///////////////////人間のID選択画面/////////////////////////
	loop_whoareyou:
		ClearDrawScreen();
		DrawString(10,5,"あなたは誰なのかを教えていただけますか？",CRWHITE);
		DrawString(10,66,"あなたの名前　　　　　　　　適用言葉タイプ",CRWHITE);
		for (i=0;i<HUMANSUU;i++){
			DrawFormatString(10,88+i*16,CRWHITE,"%d→",i);
			DrawFormatString(40,88+i*16,CRGREEN,"%s",str_human[i]);
		}
		for (i=0;i<typeSHURUISUU;i++){
			DrawFormatString(250,88+i*16,CRGREEN,"%s (typeID %d)",str_type[humankaiwadata[i].type],humankaiwadata[i].type);
		}

		DrawStringToHandle(0,350,"※言葉タイプは、性別による言葉使いの違いなどを想定しました。",CRWHITE,FontHandle12);

		DrawString(450,300,"言葉タイプ名称編集",CRGREEN);

		DrawString(10,300,"数字キーを押してスタートできます\nＥＳＣキーで戻る",CRWHITE);
		DrawString(0,413-16,"名前をクリックであなたの名前を変更できます、",CRWHITE);
		DrawString(0,413,"言葉タイプを左右クリックで適用する言葉タイプを変更できます",CRWHITE);
		DrawString(0,413+32,"※AIは言葉タイプが同じ過去データの中から発言を決定します",CRWHITE);

		ScreenFlip();

		if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける 
		while(1){
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){Sleep(1);}
			if (get_mouseclick(450,300,450+160,300+16)==1){
				edit_type();
				WaitTimer(200);
				goto loop_whoareyou;
			}
			for (i=0;i<HUMANSUU;i++){
				if (get_mouseclick(10,88+i*16,10+200,88+i*16+16)==1){
					editstr_human(i);
					WaitTimer(200);
					goto loop_whoareyou;
				}
			}
			for (i=0;i<typeSHURUISUU;i++){
				if (get_mouseclick(250,88+i*16,250+200,88+i*16+16)==1){
					if (humankaiwadata[i].type<typeSHURUISUU-1){
						humankaiwadata[i].type++;
					}else{
						humankaiwadata[i].type=0;
					}
					//humanのタイプを上書き保存humankaiwadata.csv

					//csvファイル上書き
					FILE *fp;
					fp = fopen("kaiwadata/humankaiwadata.csv","w");
					for (i=0;i<HUMANSUU;i++){
						fprintf(fp,"%d\n",humankaiwadata[i].type);
					}
					fprintf(fp,"※一番上の行が人間ID10000の言葉タイプID、一番下の行が人間ID10009の言葉タイプID\n");
					fclose(fp);
					WaitTimer(200);
					goto loop_whoareyou;
				}
				if (get_mouseclick(250,88+i*16,250+200,88+i*16+16)==2){
					if (humankaiwadata[i].type>0){
						humankaiwadata[i].type--;
					}else{
						humankaiwadata[i].type=typeSHURUISUU-1;
					}
					//humanのタイプを上書き保存humankaiwadata.csv

					//csvファイル上書き
					FILE *fp;
					fp = fopen("kaiwadata/humankaiwadata.csv","w");
					for (i=0;i<HUMANSUU;i++){
						fprintf(fp,"%d\n",humankaiwadata[i].type);
					}
					fprintf(fp,"※一番上の行が人間ID10000の言葉タイプID、一番下の行が人間ID10009の言葉タイプID\n");
					fclose(fp);
					WaitTimer(200);
					goto loop_whoareyou;
				}
			}
			if (CheckHitKey_test( KEY_INPUT_ESCAPE)==1){
				return;
			}
			if (CheckHitKey_test(KEY_INPUT_NUMPAD0)==1 || CheckHitKey_test(KEY_INPUT_0)==1){
				id_hanasite=10000;
				break;
			}
			if (CheckHitKey_test(KEY_INPUT_NUMPAD1)==1 || CheckHitKey_test(KEY_INPUT_1)==1){
				id_hanasite=10001;
				break;
			}
			if (CheckHitKey_test(KEY_INPUT_NUMPAD2)==1 || CheckHitKey_test(KEY_INPUT_2)==1){
				id_hanasite=10002;
				break;
			}
			if (CheckHitKey_test(KEY_INPUT_NUMPAD3)==1 || CheckHitKey_test(KEY_INPUT_3)==1){
				id_hanasite=10003;
				break;
			}
			if (CheckHitKey_test(KEY_INPUT_NUMPAD4)==1 || CheckHitKey_test(KEY_INPUT_4)==1){
				id_hanasite=10004;
				break;
			}
			if (CheckHitKey_test(KEY_INPUT_NUMPAD5)==1 || CheckHitKey_test(KEY_INPUT_5)==1){
				id_hanasite=10005;
				break;
			}
			if (CheckHitKey_test(KEY_INPUT_NUMPAD6)==1 || CheckHitKey_test(KEY_INPUT_6)==1){
				id_hanasite=10006;
				break;
			}
			if (CheckHitKey_test(KEY_INPUT_NUMPAD7)==1 || CheckHitKey_test(KEY_INPUT_7)==1){
				id_hanasite=10007;
				break;
			}
			if (CheckHitKey_test(KEY_INPUT_NUMPAD8)==1 || CheckHitKey_test(KEY_INPUT_8)==1){
				id_hanasite=10008;
				break;
			}
			if (CheckHitKey_test(KEY_INPUT_NUMPAD9)==1 || CheckHitKey_test(KEY_INPUT_9)==1){
				id_hanasite=10009;
				break;
			}

			// メッセージ処理
			if( ProcessMessage() == -1 )
			{
				mode=1;
				return ;	// エラーが起きたらループから抜ける
			}
			Sleep(1);
		}
		///////////////////////////////////////////////////////////
	}

	if (katati_kaiwa==0){
		//話題対象力士ID
		wrikisidata[0].wrikisiid=rikisisentaku_id;
		//最初のターンは人間からにしてみた
		//id_hanasiteは決定済み
		id_kikite=rikisisentaku_id;//話を聞いている方のAIのID
		type_hanasite=humankaiwadata[id_hanasite-10000].type;//言葉タイプ
		type_kikite=aikaiwadata[rikisisentaku_id].type;//言葉タイプ
	}else if (katati_kaiwa==1){
		//話題対象力士ID
		wrikisidata[0].wrikisiid=-1;
		//最初のターンのid_hanasite決定
		id_hanasite=rikisisentaku_id;//とりあえず最初のid_hanasiteは画像をクリックされた力士
		//最初のターンのid_kikite決定
		id_kikite=nextspeaking_heya(id_hanasite,rikisidata[rikisisentaku_id].heyaid);//現在のid_hanasiteを除いて決定させるルーチン
		type_hanasite=aikaiwadata[id_hanasite].type;//言葉タイプ
		type_kikite=aikaiwadata[id_kikite].type;//言葉タイプ
	}
	kaiwabundanflag=1;//AIに前のやり取りとは話がつながらないよ、というのを教えるフラグ
	kaesikaiwabundanflag=0;
	kaiwacount=0;
	studyflag=0;


	//ai_hyoujou_konomiはあんまり大きくするとtensuuがオーバーフローするかも
	//掛け算するのでプラスにすべき、0もダメ
	//AIの性格が出る部分
	//csv_kaiwa.cppのvoid csv_kaiwa_read(void)ルーチンの中で
	//「aikaiwadate.csv」を読み込んでいる
/*
	for (i=0;i<AISUU;i++){
		aikaiwadata[i].hyoujou_konomi[0]=20;//うれしそうな表情・感動・ときめき
		aikaiwadata[i].hyoujou_konomi[1]=2;//怒り
		aikaiwadata[i].hyoujou_konomi[2]=3;//冷笑・軽蔑
		aikaiwadata[i].hyoujou_konomi[3]=15;//励ますしぐさ
		aikaiwadata[i].hyoujou_konomi[4]=11;//真剣な表情
		aikaiwadata[i].hyoujou_konomi[5]=2;//泣く(悲しみや痛み)
		aikaiwadata[i].hyoujou_konomi[6]=4;//不安そうな表情
		aikaiwadata[i].hyoujou_konomi[7]=5;//暗い表情
		aikaiwadata[i].hyoujou_konomi[8]=15;//笑顔
		aikaiwadata[i].hyoujou_konomi[9]=8;//渋い表情
		aikaiwadata[i].hyoujou_konomi[10]=1;//AI専用、AIがデータから表情を見つけられなかったとき
	}
*/

	//力士IDごとの今場所の成績検索
	for (i=0;i<RIKISISUU;i++){
		if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
		for (ii=0;ii<15;ii++){
			if (rikisidata[i].winkonbasho[ii]==1){
				win[i]++;
			}else if (rikisidata[i].lostkonbasho[ii]==1){
				lost[i]++;
			}
		}
	}
	//休場分加算
	for (i=0;i<RIKISISUU;i++){
		if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
		for (ii=0;ii<15;ii++){
			if (kyuujoukonbasho[i][ii]==1){
				if (rikisidata[i].bandukenameid<=5){
					if ( (win[i]+lost[i]+yasumi[i])<15 ){
						yasumi[i]++;
					}
				}else{/*幕下以下はどのようにカウントしたらよいかわからんのでとりあえず千秋楽での表示だけカウント
					if (ii==0 || ii==3 || ii==6 || ii==9 || ii==11 || ii==13 || ii==14){
						yasumi[i]++;
					}*/
					if ( (day-11)==14 ){
						if ( (win[i]+lost[i]+yasumi[i])<7 ){
							yasumi[i]++;
						}
					}
				}
			}
		}
	}

	//day_kaiwa
	day_kaiwa=day-11;


	if (katati_kaiwa==0){
		//sumoflag
		wrikisidata[0].sumoflag=0;
		//sumoflag左から1番目
		//今日の勝ちフラグ
		if (rikisidata[wrikisidata[0].wrikisiid].winkonbasho[day_kaiwa]==1){
			wrikisidata[0].sumoflag |= b10000000;
		}
		//sumoflag左から2番目
		//今日の負けフラグ
		if (rikisidata[wrikisidata[0].wrikisiid].lostkonbasho[day_kaiwa]==1){
			wrikisidata[0].sumoflag |= b01000000;
		}

		//sumoflag左から3番目
		//休場フラグ
		if (kyuujoumode==1){
			if (kyuujouflag[wrikisidata[0].wrikisiid]==1){
				wrikisidata[0].sumoflag |= b00100000;
			}
		}

		//sumoflag左から4番目
		//注射勝ちフラグ
		if (rikisidata[wrikisidata[0].wrikisiid].yaowinkonbasho[day_kaiwa]==1){
			wrikisidata[0].sumoflag |= b00010000;
		}

		//sumoflag左から5番目
		//注射負けフラグ
		if (rikisidata[wrikisidata[0].wrikisiid].aitekonbasho[day_kaiwa]!=-1
		 && rikisidata[wrikisidata[0].wrikisiid].aitekonbasho[day_kaiwa]!=999){ //取組が組まれている日で
			if (rikisidata[rikisidata[wrikisidata[0].wrikisiid].aitekonbasho[day_kaiwa]].yaowinkonbasho[day_kaiwa]==1){
				wrikisidata[0].sumoflag |= b00001000;
			}
		}

		//suu_winlost
		wrikisidata[0].suu_winlost=0;
		//今場所の勝ち星数(上位4ビット)
		temp_char=win[wrikisidata[0].wrikisiid];
		wrikisidata[0].suu_winlost |= (temp_char & 0x0f);
		wrikisidata[0].suu_winlost=wrikisidata[0].suu_winlost<<4;
		//今場所の負け星数(下位4ビット)
		temp_char=lost[wrikisidata[0].wrikisiid];
		wrikisidata[0].suu_winlost |= (temp_char & 0x0f);

		//nokoribansuu
		wrikisidata[0].nokoribansuu=0;
		//今場所の残りの番数(上位4ビット)
		if (rikisidata[wrikisidata[0].wrikisiid].bandukenameid<=5){
			temp_char=15-win[wrikisidata[0].wrikisiid]-lost[wrikisidata[0].wrikisiid]-yasumi[wrikisidata[0].wrikisiid];
		}else{
			temp_char=7-win[wrikisidata[0].wrikisiid]-lost[wrikisidata[0].wrikisiid]-yasumi[wrikisidata[0].wrikisiid];
		}
/*
////////////////////////////////////////////////////////////////////
///////////////////////////debug////////////////////////////////////
{
int i_dubug=0;
ClearDrawScreen();
DrawFormatString(0,0+i_dubug*16,CRWHITE,"残り番数temp_char=%d",temp_char);i_dubug++;
DrawFormatString(0,0+i_dubug*16,CRWHITE,"win=%d",win[wrikisidata[0].wrikisiid]);i_dubug++;
DrawFormatString(0,0+i_dubug*16,CRWHITE,"lost=%d",lost[wrikisidata[0].wrikisiid]);i_dubug++;
DrawFormatString(0,0+i_dubug*16,CRWHITE,"yasumi=%d",yasumi[wrikisidata[0].wrikisiid]);i_dubug++;
DrawFormatString(0,0+i_dubug*16,CRWHITE,"sumoflag=%d",wrikisidata[0].sumoflag);i_dubug++;
DrawFormatString(0,0+i_dubug*16,CRWHITE,"相手注射win=%d",rikisidata[rikisidata[wrikisidata[0].wrikisiid].aitekonbasho[day_kaiwa]].yaowinkonbasho[day_kaiwa]);i_dubug++;
DrawFormatString(0,0+i_dubug*16,CRWHITE,"day_kaiwa=%d",day_kaiwa);i_dubug++;
ScreenFlip();
WaitKey();
}
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
*/
		wrikisidata[0].nokoribansuu |= (temp_char & 0x0f);
		wrikisidata[0].nokoribansuu=wrikisidata[0].nokoribansuu<<4;
	}


loop_wadaisettei:
	/////////////jflagと話題設定フラグ//////////////
	ClearDrawScreen();
	DrawString(300,5,"話題設定画面",CRWHITE);
	DrawString(10,24,"どんな話をしますか？",CRWHITE);
	DrawString(10,40,"0→誰とでもどんな状況でも話せるような内容の話",CRWHITE);
	if (katati_kaiwa==0){
		DrawString(10,56,"1→この力士の今場所・当日の成績についての話",CRWHITE);
	}
	DrawString(10,72,"2→ランダム天気会話",CRWHITE);
	for (i=0;i<5;i++){
		DrawFormatString(10,88+i*16,CRWHITE,"%d→",i+3);
		DrawFormatString(40,88+i*16,CRGREEN,"%s",str_jflag[i+11]);
	}


	DrawString(10,200,"数字キーを押してください\nＥＳＣキーで戻る",CRWHITE);
	DrawString(10,250,"3～7をクリックで話題の名称を変更できます",CRWHITE);
	if (katati_kaiwa==0){
		DrawString(10,413,"なお、1を選んでも情報から推測できない内容、",CRWHITE);
		DrawString(10,413+16,"たとえば、番付や決まり手、取組内容の話は理解できません。",CRWHITE);
		DrawString(10,413+32,"一方、勝ち越し・負け越しは推測可能！？",CRWHITE);
	}

	if (katati_kaiwa==0){
		i++;
		DrawString(10,240+i*16,"1を選んだ場合は以下の情報がAIに与えられます",CRWHITE);i++;
		DrawString(10,240+i*16,"■本日の勝ち負け(注射・休場の情報も含む)",CRWHITE);i++;
		DrawString(10,240+i*16,"■今場所の勝ち数・負け数・残り番数",CRWHITE);i++;
		//DrawString(0,135+i*16,"■場所中の何日目か",CRWHITE);i++;
	}
	ScreenFlip();

	if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}// エラーが起きたらループから抜ける
	while(1){
		while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
		while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){Sleep(1);}
		for (i=0;i<5;i++){
			if (get_mouseclick(10,88+i*16,170,88+i*16+16)==1){
				editstr_jflag(i+11);
				WaitTimer(200);
				goto loop_wadaisettei;
			}
		}
		if (CheckHitKey_test( KEY_INPUT_ESCAPE)==1){
			return;
		}
		if (CheckHitKey_test(KEY_INPUT_NUMPAD0)==1 || CheckHitKey_test(KEY_INPUT_0)==1){
			jflag=0;
			break;
		}
		if (katati_kaiwa==0){
			if (CheckHitKey_test(KEY_INPUT_NUMPAD1)==1 || CheckHitKey_test(KEY_INPUT_1)==1){
				jflag=1;
				break;
			}
		}
		if (CheckHitKey_test(KEY_INPUT_NUMPAD2)==1 || CheckHitKey_test(KEY_INPUT_2)==1){
			jflag=GetRand(8)+2;
			break;
		}
		if (CheckHitKey_test(KEY_INPUT_NUMPAD3)==1 || CheckHitKey_test(KEY_INPUT_3)==1){
			jflag=11;
			break;
		}
		if (CheckHitKey_test(KEY_INPUT_NUMPAD4)==1 || CheckHitKey_test(KEY_INPUT_4)==1){
			jflag=12;
			break;
		}
		if (CheckHitKey_test(KEY_INPUT_NUMPAD5)==1 || CheckHitKey_test(KEY_INPUT_5)==1){
			jflag=13;
			break;
		}
		if (CheckHitKey_test(KEY_INPUT_NUMPAD6)==1 || CheckHitKey_test(KEY_INPUT_6)==1){
			jflag=14;
			break;
		}
		if (CheckHitKey_test(KEY_INPUT_NUMPAD7)==1 || CheckHitKey_test(KEY_INPUT_7)==1){
			jflag=15;
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
	///////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
///////////////////////////debug////////////////////////////////////
if (jflag==1){
	int i_debug;
	unsigned char temp_char=0;//右シフト用いているのでunsigned必須
	ClearDrawScreen();
	DrawString(20,0,"確認画面(Hit Any Key)",CRWHITE);
	if ((wrikisidata[0].sumoflag & b10000000)==b10000000){
		DrawString(20,48+16,"今日勝った\n",CRWHITE);
	}else{
		DrawString(20,48+16,"今日勝ってはいない\n",CRWHITE);
	}
	if ((wrikisidata[0].sumoflag & b01000000)==b01000000){
		DrawString(20,48+32,"今日負けた\n",CRWHITE);
	}else{
		DrawString(20,48+32,"今日負けてはいない\n",CRWHITE);
	}
	if ((wrikisidata[0].sumoflag & b00100000)==b00100000){
		DrawString(20,48+48,"休場中\n",CRWHITE);
	}else{
		DrawString(20,48+48,"休場中ではない\n",CRWHITE);
	}
	if ((wrikisidata[0].sumoflag & b00010000)==b00010000){
		DrawString(20,48+64,"勝ち注射した\n",CRWHITE);
	}else{
		DrawString(20,48+64,"勝ち注射してない\n",CRWHITE);
	}
	if ((wrikisidata[0].sumoflag & b00001000)==b00001000){
		DrawString(20,48+80,"負け注射した\n",CRWHITE);
	}else{
		DrawString(20,48+80,"負け注射してない\n",CRWHITE);
	}
	temp_char=0;
	temp_char=wrikisidata[0].suu_winlost & 0xf0;
	temp_char=temp_char>>4;
	DrawFormatString(20,48+96,CRWHITE,"%d勝\n",temp_char);
	DrawFormatString(20,48+112,CRWHITE,"%d敗\n",wrikisidata[0].suu_winlost & 0x0f);
	temp_char=0;
	temp_char=wrikisidata[0].nokoribansuu & 0xf0;
	temp_char=temp_char>>4;
	DrawFormatString(20,48+128,CRWHITE,"残り%d番\n",temp_char);
	//DrawFormatString(20,48+144,CRWHITE,"jflag=%d\n",jflag);
	DrawString(0,413,"以上の状況すべてが合致する過去の会話データから優先して、\nAIが発言内容を決定します",CRWHITE);
	DrawString(0,413+32,"全てが合致するデータがない場合、似た状況から探す努力は一応します。",CRWHITE);
	//DrawString(0,413+48,"★が少ないほどデータを引っ張れますが、状況不一致な発言をしやすいです",CRWHITE);
	ScreenFlip();
	WaitKey();
}
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
/*
FILE *fpcsv;
fpcsv = fopen("debug_kaiwa.txt","w");
fclose(fpcsv);
*/
	mode_kaiwa=2;
	kaiwa_main();

	if (mode_kaiwa==1) mode=1;
	return;
}


void kaiwa_main_hyoji(void)//
{
	int i;
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

	unsigned char temp_char=0;
	char temp_filename[MAX_PATH];
	for (i=0;i<MAX_PATH;i++){
		temp_filename[i]=0;
	}

	ClearDrawScreen();

	if (katati_kaiwa==0){
	//力士画像表示
		chousei_x=150;
		chousei_y=-200;
		sprintf(temp_filename,"rikisigraph/rikisi%d.png\0",rikisisentaku_id);
		rikisi_front_edit = LoadGraph( temp_filename ) ;
		shukushou_tate_gazou=(int)(220-rikisidata[rikisisentaku_id].sinchou)*2/3;
		shukushou_yoko_gazou=(int)((250-rikisidata[rikisisentaku_id].taijuu)/2);
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
		if (jflag==1){
			if ((wrikisidata[0].sumoflag & b10000000)==b10000000){
				DrawStringToHandle(10,5,"今日勝った",CRWHITE,FontHandle12);
			}
			if ((wrikisidata[0].sumoflag & b01000000)==b01000000){
				DrawStringToHandle(10,5,"今日負けた",CRWHITE,FontHandle12);
			}
			if ((wrikisidata[0].sumoflag & b00010000)==b00010000){
				DrawStringToHandle(100,5,"勝ち注射した",CRWHITE,FontHandle12);
			}
			if ((wrikisidata[0].sumoflag & b00001000)==b00001000){
				DrawStringToHandle(100,5,"負け注射した",CRWHITE,FontHandle12);
			}
			if ((wrikisidata[0].sumoflag & b00100000)==b00100000){
				DrawStringToHandle(10,5,"休場中",CRWHITE,FontHandle12);
			}
			temp_char=0;
			temp_char=wrikisidata[0].suu_winlost & 0xf0;
			temp_char=temp_char>>4;
			DrawFormatStringToHandle(10,25,CRWHITE,FontHandle12,"%d勝%d敗",temp_char,wrikisidata[0].suu_winlost & 0x0f);
			temp_char=0;
			temp_char=wrikisidata[0].nokoribansuu & 0xf0;
			temp_char=temp_char>>4;
			DrawFormatStringToHandle(10,45,CRWHITE,FontHandle12,"残り%d番\n",temp_char);
		}else{
			DrawStringToHandle(10,30,"このゲームの世界を離れて会話を楽しんでください♪",CRWHITE,FontHandle12);
		}
		DrawFormatString(200,5,CRWHITE,"%sとの会話画面(%s)",namestring[rikisisentaku_id],str_jflag[jflag]);
		if (mode_kaiwa==2){//話しかけた最初
			//strcpy(kako_str[0],"ごっつあんです");
			kako_hyoujounum[0]=8;
			kako_id_hanasite[0]=-1;
			DrawString(10,64,"全角で25文字以内で会話してね！！",CRWHITE);
			DrawString(10,136,"会話を入力後ENTERで確定\nESCキーでMENUに戻る",CRWHITE);
			//DrawFormatString( 200, 350, CRWHITE, "AI：%s\n『%s』", str_hyoujou[kako_hyoujounum[0]],kako_str[0] ) ;

		}
		if (mode_kaiwa==10){//会話入力
////////////////////////////////////////////////////////////////////
///////////////////////////debug////////////////////////////////////
/*
{
int i_debug;
ClearDrawScreen();
DrawFormatString(0,0,CRGREEN,"会話入力画面\noumugaesiflag=%d\nstudyflag=%d",oumugaesiflag,studyflag);
ScreenFlip();
WaitKey();
}
*/
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

			if (studyflag==1){
				if (oumugaesiflag==1){
					DrawString(10,64,"ＡＩが教えてほしいそうです",CRWHITE);
				}else{
					DrawString(10,64,"ＡＩ学習モードです",CRWHITE);
				}
				DrawFormatString( 10, 88, CRWHITE, "先ほどのあなたの発言『%s』\nに対する模範的な返答を教えてあげてください", kako_str[1] ) ;
			}else{
				DrawString(10,64,"全角文字で２５文字以内で会話してね！！",CRWHITE);
				DrawString(10,80,"直前のＡＩの発言を指導するには、\n何も入力せずそのままＥＮＴＥＲ",CRWHITE);
			}
			DrawString(10,152,"全角文字で会話を入力後ＥＮＴＥＲで確定\nＥＳＣキーでＭＥＮＵに戻る",CRWHITE);
			if (studyflag==1){
				DrawFormatString( 180, 340, CRWHITE, "あなた：%s\n『%s』", str_hyoujou[kako_hyoujounum[1]],kako_str[1] ) ;
			}else{
				DrawFormatString( 180, 340, CRWHITE, "あなた：%s\n『%s』", str_hyoujou[kako_hyoujounum[1]],kako_str[1] ) ;
				DrawFormatString( 180, 390, CRWHITE, "ＡＩ：%s\n『%s』", str_hyoujou[kako_hyoujounum[0]],kako_str[0] ) ;
			}
		}
		if (mode_kaiwa==8){//会話再入力
			DrawString(10,136,"会話を再入力後ＥＮＴＥＲで確定\nＥＳＣキーでＭＥＮＵに戻る",CRWHITE);
			if (kaiwacount!=0){
				DrawFormatString( 200, 390, CRWHITE, "ＡＩ：%s\n『%s』", str_hyoujou[kako_hyoujounum[0]],kako_str[0] ) ;
			}
		}

		if (mode_kaiwa==9){//会話入力後のひらがなチェックで引っかかった場合の再入力
			DrawFormatString(10,64,CRWHITE,"『%s』\nには利用できない文字が混じってるみたい",inputstr);
			DrawString(10,136,"全角２５文字で会話を再入力後ＥＮＴＥＲで確定\nＥＳＣキーでMENUに戻る",CRWHITE);
		}
		if (mode_kaiwa==15){//会話入力後の表情入力
			if (studyflag==1){
				DrawFormatString(10,64,CRWHITE,"『%s』\nを言う時の模範的な表情を教えてあげてください",inputstr);
			}else{
				DrawFormatString(10,64,CRWHITE,"『%s』\nを言う時のあなたの表情を教えてね！！",inputstr);
			}
			DrawString(10,136,"数字キーを押してください\nＥＳＣキーで入力からやり直し",CRWHITE);
			for (i=0;i<HYOUJOUSHURUISUU-1;i++){
				DrawFormatString(10,175+i*16,CRWHITE,"%d→%s",i,str_hyoujou[i]);
			}
			if (studyflag!=1){
				if (kaiwacount==0){
					DrawFormatString( 180, 415, CRWHITE, "あなた：\n『%s』", inputstr ) ;
				}else{
					DrawFormatString( 180, 340, CRWHITE, "ＡＩ：%s\n『%s』", str_hyoujou[kako_hyoujounum[0]],kako_str[0] ) ;
					DrawFormatString( 180, 415, CRWHITE, "あなた：\n『%s』", inputstr ) ;
				}
			}
		}
	}else if (katati_kaiwa==1){
		DrawFormatString(50,5,CRWHITE,"%s部屋の力士たちの会話画面(%s)",heyastring[rikisidata[rikisisentaku_id].heyaid],str_jflag[jflag]);
		if (mode_kaiwa==10){//会話確認
			if (studyflag==1){
				if (oumugaesiflag==1){
					if (kako_id_hanasite[0]<RIKISISUU && kako_id_hanasite[0]>=0){
						DrawFormatString(10,64, CRWHITE, "%d %sが教えてほしいそうです",kaiwacount,namestring[kako_id_hanasite[0]]);
					}else{
						DrawString(10,64,"ＡＩが教えてほしいそうです",CRWHITE);
					}
				}else{
					DrawString(10,64,"ＡＩ学習モードです",CRWHITE);
				}
				if (kaiwacount==1){
					DrawString( 10, 88, "先ほどの発言に対する模範的な返答を教えてあげてください", CRWHITE ) ;
				}else{
					DrawFormatString( 10, 88, CRWHITE, "先ほどの発言『%s』\nに対する模範的な返答を教えてあげてください", kako_str[1] ) ;
				}
			}else{
				DrawString(10,64,"確認ＯＫなら何も入力せずそのままＥＮＴＥＲ",CRWHITE);
				DrawString(10,80,"直前のＡＩの発言を修正指導するには、\n全角文字で会話を入力後ＥＮＴＥＲで確定",CRWHITE);
			}
			DrawString(10,152,"ＥＳＣキーでＭＥＮＵに戻る",CRWHITE);
			if (kako_id_hanasite[0]<RIKISISUU && kako_id_hanasite[0]>=0){
				if (kaiwacount==1){
					//DrawFormatString( 180, 340, CRWHITE, "%s：%s\n『%s』", namestring[kako_id_hanasite[0]],str_hyoujou[kako_hyoujounum[1]],kako_str[1] ) ;
				}else{
					DrawFormatString( 180, 340, CRWHITE, "%s：%s\n『%s』", namestring[kako_id_hanasite[1]],str_hyoujou[kako_hyoujounum[1]],kako_str[1] ) ;
				}
			}
			if (studyflag!=1){
				if (kako_id_hanasite[0]<RIKISISUU && kako_id_hanasite[0]>=0){
					DrawFormatString( 180, 390, CRWHITE, "%s：%s\n『%s』", namestring[kako_id_hanasite[0]],str_hyoujou[kako_hyoujounum[0]],kako_str[0] ) ;
				}
			}
		}
		if (mode_kaiwa==9){//会話入力後のひらがなチェックで引っかかった場合の再入力
			DrawFormatString(10,64,CRWHITE,"『%s』\nには利用できない文字が混じってるみたい",inputstr);
			DrawString(10,136,"全角２５文字で会話を再入力後ＥＮＴＥＲで確定\nＥＳＣキーでMENUに戻る",CRWHITE);
		}
		if (mode_kaiwa==15){//会話入力後の表情入力
			DrawFormatString(10,64,CRWHITE,"『%s』\nを言う時の模範的な表情を教えてあげてください",inputstr);
			DrawString(10,136,"数字キーを押してください\nＥＳＣキーで入力からやり直し",CRWHITE);
			for (i=0;i<HYOUJOUSHURUISUU-1;i++){
				DrawFormatString(10,175+i*16,CRWHITE,"%d→%s",i,str_hyoujou[i]);
			}
		}

	}

	ScreenFlip();
	return;
}


void kaiwa_main(void)//ゲームメインルーチン
{
	hyoujounum=8;//愛想笑
	kaesihyoujounum=8;//愛想笑
	if (mode_kaiwa==1){
		return;
	}


	// ループ
	while(1)//ゲーム中のメインループ
	{
		// メッセージ処理
		if( ProcessMessage() == -1 ){mode_kaiwa=1;return ;}
		Sleep(1);
		if (mode_kaiwa==1) return;

		////会話処理/////////
		kaiwa();
		if (mode_kaiwa==2 || mode_kaiwa==1) return;


	}//ゲーム中のメインループ終端
}

int nextspeaking_heya(int now_hanasite,int heyaid)//現在のid_hanasiteを除いて決定させるルーチン
{
	int i,r;
	int next_hanasite=0;
	int sekkyokusei_total=0;
	int temp_sekkyokusei_total=0;

	for (i=0;i<RIKISISUU;i++){
		if (rikisidata[i].heyaid==rikisidata[now_hanasite].heyaid 
		&& i!=now_hanasite){
			sekkyokusei_total+=aikaiwadata[i].sekkyokusei;
		}
	}
	r=GetRand(sekkyokusei_total-1);
	for (i=0;i<RIKISISUU;i++){
		if (rikisidata[i].heyaid==rikisidata[now_hanasite].heyaid 
		&& i!=now_hanasite){
			temp_sekkyokusei_total+=aikaiwadata[i].sekkyokusei;
			if (temp_sekkyokusei_total>r){
				next_hanasite=i;
				break;
			}
		}
	}
	return next_hanasite;
}