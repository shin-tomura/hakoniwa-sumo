#include "DxLib.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include "define.h"

extern int A_saikoui;//Ａカテの条件
extern int A_sanyakuzaiisuu;
extern int A_makuutizaiisuu;
extern int B_saikoui;//Ｂカテの条件
extern int B_makuutizaiisuu;
extern int B_jyuuryouzaiisuu;
extern int C_makuutizaiisuu;//Ｃカテの条件
extern int C_jyuuryouzaiisuu;

extern int G_age;
extern int G_rikisiid;
extern char G_sikona[12];
extern int G_category;
extern int G_shuumeizumitosiyoriid;

extern char namestring_riji[10][21];
extern int checkname(char name[]);
extern int FontHandle16;
extern int FontHandle12;
extern void video(int ID,int ID2,int YEAR,int MONTH,char ID_NAMESTRING[],char ID2_NAMESTRING[]);
extern int get_mouseclick_rlist(int x);//画面右のリスト上でクリックされたら1を返す、

extern int page_kyuujou;
extern char kyuujoustring[RIKISISUU][21];//全角10文字以内
extern int heya_tosiyorisuu[HEYASUU];
extern int heyasuu_genzon;
extern struct tosiyori_data tosiyoridata[TOSIYORISUU];
extern struct itimon_data itimondata[ITIMONSUU];
extern struct heya_data heyadata[HEYASUU];
extern void sikona_kouhosuu(void);
extern void sikona_c(void);
extern void sikonahenkan(void);
extern int skipmode;//0:全部の取り組みの詳細を表示
extern int skipyear;//skipmode==2のときの指定年
extern int skipmonth;//skipmode==2のときの指定月
extern int myheyaid;//プレイヤーの運営する相撲部屋ID
extern int superrikisisuu[10];//引数1＞朝青龍の数
extern int CheckHitKey_test(int);
extern void ikuseihousin(void);
extern int retire_yokoduna_win1;//引退条件
extern int retire_yokoduna_win2;
extern int retire_yokoduna_win3;
extern int retire_oozeki_banduke1;
extern int retire_oozeki_banduke2;
extern int retire_oozeki_banduke3;
extern int retire_oozeki_win1;
extern int retire_oozeki_win2;
extern int retire_oozeki_win3;
extern int sanyakuijouzaiisuu[RIKISISUU];
extern int makuutiijouzaiisuu[RIKISISUU];
extern int juuryouijouzaiisuu[RIKISISUU];
extern int shozokurikisisuu[HEYASUU];//部屋IDごとの所属力士数
extern void gameover(int);
extern void game_main_backscreen(void);//基本ゲーム画面表示ルーチン
extern int hometownstring_used[SICHOUSONSUU];//2544市町村ごとの通算使用回数
extern int retiresuu_total;//引退力士トータル
extern long filesize_retire[RETIREMAXFILESUU];//引退力士ファイルの各連番のファイルサイズ
extern long Getfilesize(char name[]);//返り値が0は存在するけどファイルサイズ0、-1→エラー、-2→存在無し
extern long maxfilesize;
extern char filename[31];
extern void draw_buttonF_mouse(void);//カーソルがのっているとき用のメニューボタンFの表示ルーチン
extern int rikisiid_used;//使用した通算力士ID数
extern char rinnemode;//0デフォルト、1輪廻力士の四股名を変えない
extern char sikonamode;//0デフォルト、1出身地紐つけ解除のみ、2
extern int heyabetu_sichousonid[HEYASUU];
extern int ikuseipattern[RIKISISUU];//育成方針
extern int ikuseiboost[RIKISISUU];//育成ブースト
extern int ikuseibunbo[RIKISISUU];//育成分母(0では割れないので0にはしないこと)
extern char tanshuku_hometown[RIKISISUU][7];
extern char sakusenname[RIKISISUU][32];//力士別の作戦名
extern int nouryoku_total[RIKISISUU];
extern int nouryoku_total_max[RIKISISUU];
extern void rikisidatahyoji_main(int x,int yokozure);
extern struct jouken_data joukendata[RIKISISUU];//構造体変数力士数分用意
extern struct jouken_data joukendata_temp_higasi;//構造体変数力士数分用意
extern struct jouken_data joukendata_temp_nisi;//構造体変数力士数分用意
extern struct jouken_data2 joukendata2[RIKISISUU];//構造体変数力士数分用意
extern struct jouken_data2 joukendata2_temp_higasi;//構造体変数力士数分用意
extern struct jouken_data2 joukendata2_temp_nisi;//構造体変数力士数分用意
extern void ikuseihousin_shori(int);
extern int scout_housin;
extern struct keiko_data keikodata[RIKISISUU];//構造体変数力士数分用意
extern struct kako_data kakodata[RIKISISUU];//構造体変数力士数分用意
extern int seiseki_sentaku_page[RIKISISUU];//力士IDごとの右タブ成績表示の表示ページ
extern int seiseki_max_page[RIKISISUU];//力士IDごとの上記の最大ページ数
extern int keikoryou_boost;
extern int bandukejunid[RIKISISUU];
extern int rikisibetu_bandukejunid[RIKISISUU][RIKISISUU];//力士情報画面右リスト力士別タブ選択時の番付順ID
extern int rinne_bandukejunid[RIKISISUU];//取り組み見るフラグがたっている力士の中での番付順の力士ID
extern int torimi_bandukejunid[RIKISISUU];//取り組み見るフラグがたっている力士の中での番付順の力士ID
extern int heyabandukejunid[HEYASUU][20];//部屋ごとの番付順の力士ID、
extern int rinnesuu;//取組見るフラグがたっている力士の数
extern int rikisibetusuu[RIKISISUU];//各力士IDごとの力士別タブ選択時の右リストに表示すべき力士数
extern int rikisibetu_sentaku_id[RIKISISUU];//士別ページに表示する力士のID
extern int rikisibetu_sentaku_page[RIKISISUU];
extern int rikisibetu_sentaku_num[RIKISISUU];
extern int torimisuu;//取組見るフラグがたっている力士の数
extern int rikisisentaku_page;//力士情報画面で表示されているページの番号
extern int rikisisentaku_num;//力士情報画面で選択された力士のリスのト番号
extern int rikisisentaku_id;//選択された力士ID
extern int torimi_rikisisentaku_page;//力士情報画面で選択された取見リストページ
extern int torimi_rikisisentaku_num;//力士情報画面で選択された取見リスト番号
extern int rinne_rikisisentaku_page;//力士情報画面で選択された取見リストページ
extern int rinne_rikisisentaku_num;//力士情報画面で選択された取見リスト番号
extern int rikisisentaku_id;//選択された力士ID
extern int bandukejun_or_jiheyaflag;//力士情報画面左リスト表示切替、0＞番付順、1＞自部屋力士、2＞取り組み見る力士
extern int rikisisentaku_num_jiheya;//力士情報画面で選択された力士のリスト番号(自部屋分)


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
extern int menuflag;//1:初期画面へ
			//2:相撲部屋表示
			//3:力士能力値表示
			//4:番付表示
			//5:記録台帳表示
			//6:ニュース表示
			//7:進め
extern long filesize_retire[RETIREMAXFILESUU];//引退力士ファイルの各連番のファイルサイズ
extern long filesize_retire_jiheya[RETIREMAXFILESUU];//ちなみに引退力士一人当たりは4460バイト
extern long filesize_retire_saikoui[RETIREMAXFILESUU];
extern int maxyearcsv;
extern long maxfilesize;//本番用
extern int retire_sentaku_category;
extern int retire_sentaku_page;
extern int retiresuu_total;//引退力士トータル
extern int retiresuu_saikoui;
extern int retiresuu_jiheya;
extern int all_retiresentaku_page;
extern int saikoui_retiresentaku_page;
extern int jiheya_retiresentaku_page;
extern int retirerikisisentaku_num_all;
extern int retirerikisisentaku_num_saikoui;
extern int retirerikisisentaku_num_jiheya;
//extern void retirerikisi_hyoji(long,long,long);
extern long kensaku_retirerikisi(long);
extern void draw_buttonkensakuLEFT(void);//メニューボタンAの表示ルーチン
extern void draw_buttonkensakuLEFT_mouse(void);//カーソルがのっているとき用のメニューボタンAの表示ルーチン
extern void buttonkensakuLEFT_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonkensakuLEFT(void);//メニューボタンAをクリックしたら1を返し、そうでなければ0をかえす
extern int get_mouseclick_list(int x);//画面左のリスト上でクリックされたら1を返す、
extern int jumppage_kiroku(void);
extern int r_torikumi_or_seisekiflag;//引退力士情報画面右リストの表示切替フラグ、1＞過去20場所の成績
extern char wazapattern_string[WAZAPATTERNSUU][32];//技パターンの名称
extern int r_hyojikirikaeflag;//引退力士情報画面メイン画面の表示切替フラグ
extern char normal_bashostring[6][7];//最長「名古屋」の3文字分

extern long size_r_rikisibetu;//r_rikisibetu.datの一場所当たりの記録サイズ

int page_intaigo;

long id_retirerikisi(int,long);//詳細引退力士画面上から通算力士IDを渡して位置情報を返す

//簡易ビデオ
int nowhyoji_torikumitab_year;
char nowhyoji_torikumitab_month;
int nowhyoji_torikumitab_ID;
int nowhyoji_torikumitab_ID2[15];
char nowhyoji_torikumitab_namestring[12];
char nowhyoji_torikumitab_namestring2[15][12];
int nowhyoji_sibetutab_year[15];
char nowhyoji_sibetutab_month[15];
int nowhyoji_sibetutab_ID;
int nowhyoji_sibetutab_ID2;
char nowhyoji_sibetutab_namestring[12];
char nowhyoji_sibetutab_namestring2[12];

//右タブ成績用
int nowhyoji_seisekitab_year[18];
char nowhyoji_seisekitab_month[18];

//右タブ取組用
int hyoji_torikumi_year=0;
int hyoji_torikumi_month=0;
int torikumi_rikisiid=0;
int torikumi_year=0;
int torikumi_month=0;
char torikumi_aitekonbashonamestring[15][12];
int torikumi_aiteid[15];
int torikumi_aitekonbashorikisiid[15];
int torikumi_watasikonbashorikisiid[15];
int torikumi_turncountkonbasho[15];//初日から15日目までの(0～14)取組の所要ターン数
char torikumi_kimaritekonbasho[15][9];//初日から15日目まで(0～14)の決まり手string
char torikumi_winkonbasho[15];//初日から15日目まで(0～14)で、勝ちなら1が入る
char torikumi_lostkonbasho[15];////初日から15日目まで(0～14)で、負けなら1が入る


void retirerikisi_new(int hyojiheyaid);//引数はプレイヤーの部屋の代わりに表示する部屋のID
void retirerikisi_hyoji(long ichijouhou,long ichijouhou_jiheya,long ichijouhou_saikoui);
void r_savehsr(void);
char namestring_save[12];//savehsr用のためだけに作った

struct rikisi_data r_rikisidata[RIKISISUU];
struct tosiyori_data r_tosiyoridata[TOSIYORISUU];
struct itimon_data r_itimondata[ITIMONSUU];
struct heya_data r_heyadata[HEYASUU];
int temp_sanyakuijouzaiisuu=0;
int temp_makuutiijouzaiisuu=0;
int temp_juuryouijouzaiisuu=0;
int temp_stamina_natural_kakosaikou=0;
int temp_binshousei_natural_kakosaikou=0;
char r_heyastring[HEYASUU][12];//(54部屋分,全角５文字まで)相撲部屋
int gyousuu=0;
int hyoji_tosiyoriid_chokuzen=0;
int hyoji_month_chokuzen=0;
int hyoji_shozokuheyaid_chokuzen=0;
int hyoji_shozokuitimonid_chokuzen=0;
int hyoji_sishouflag_chokuzen=0;
int hyoji_rijiflag_chokuzen=0;
int hyoji_keishousha_rikisiid_chokuzen=0;
int hyoji_keishousha_tosiyoriid_chokuzen=0;
int year_tosiyori=0;
int month_tosiyori=0;
int kakunin_rikisiid=0;
char kakunin_namestring[12];
int kakunin_wintotal=0;
int kakunin_losttotal=0;
int kakikomizumiflag=0;
int page_r_sibetu_main=0;
int page_r_sibetu_tab=0;
int temp_taisensuu=0;
int temp_taisensuu_main=0;
int r_sibetu_rikisiid=0;
int r_sibetu_wintotal=0;
int r_sibetu_losttotal=0;
char r_sibetu_namestring[12];
int nyuuryokuti=0;
int	pagenomihenkouflag_r_mainsibetu=0;

	int temp_rikisiid;
	int temp_rikisiid2;
	char temp_list_namestring[20][12];
	char temp_namestring[12];
	char temp_hometownstring[28];
	char temp_heyastring[12];
	char temp_heyaid;
	int temp_hatudohyo_year;
	char temp_hatudohyo_month;
	int temp_retire_year;
	int temp_retire_month;
	char temp_jikosaiko_bandukenameid;
	char temp_jikosaiko_bandukesuuji;
	int temp_makuuti_win;
	int temp_makuuti_lost;
	int temp_kiroku_yuushoukaisuu;
	int temp_kinbosisuu;
	int temp_shukunshousuu;
	int temp_kantoushousuu;
	int temp_ginoushousuu;
	int temp_wintotal;
	int temp_losttotal;
	int temp_kiroku_renshou;
	int temp_kiroku_renpai;
	char temp_kako_yuushouflag[180];
	char temp_kako_bandukehigasiornisi[180];
	char temp_kako_bandukenameid[180];
	char temp_kako_bandukesuuji[180];
	char temp_kako_win[180];
	char temp_kako_lost[180];
	char temp_jikosaiko_tournament;
	int temp_yuushoukaisuu_tournament;
	int temp_age;

long kyuujou_kirokusuu_long;
long tempsize_kyuujou;
//int kyuujou_kirokusuu;
long kyuujou_kirokusuu;
int kyuujou_rikisiid;
int kyuujou_year;
int kyuujou_month;
char kyuujou_bandukenameid;
char kyuujou_bandukesuuji;
int kyuujou_yasumi;
char kyuujou_kyuujoustring[21];
int kyuujou_yasumi_total;
int kyuujou_yasumi_total_makuuti;


int kensaku_kakotorikumihyoji(void);

int kensaku_kakotorikumihyoji(void){
	int i,nyuuryokuti,kakoyear,kakomonth;

	while(1){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawBox(0,0,639,479,CRBACK,TRUE);
		DrawString(210,0,"過去の取組表示年月直接入力画面",CRWHITE);
		//DrawFormatString(0,64,CRWHITE,"現在%d年%d月です。",year,month);
		DrawString(0,443,"まず年を入力してください。なお、0で戻れます。",CRGREEN);
		DrawString(0,459,"数字を入力してENTERキーを押してください。＞",CRGREEN);
		ScreenFlip() ;//裏画面を表画面にコピー
			nyuuryokuti= KeyInputNumber( 520 , 459 , year , 0 , FALSE );
		if (nyuuryokuti==0){
			return 0;
		}else if (nyuuryokuti>year || (nyuuryokuti==year && month<3) || nyuuryokuti<GANNEN){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawBox(0,0,639,479,CRBACK,TRUE);
			DrawString(0,443,"ありえない数字です。",CRWHITE);
			DrawString(0,459,"Hit any key",CRWHITE);
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
		}else{
			kakoyear=nyuuryokuti;
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawBox(0,0,639,479,CRBACK,TRUE);
			DrawString(210,0,"過去の取組表示年月直接入力画面",CRWHITE);
			//DrawFormatString(0,64,CRWHITE,"現在%d年%d月です。",year,month);
			DrawFormatString(0,80,CRWHITE,"%d年の何場所を指定しますか。",kakoyear);
			for (i=0;i<6;i++){
				DrawFormatString(0,112+i*32,CRWHITE,"%d %s場所",i+1,normal_bashostring[i]);
			}
			DrawString(0,443,"次に場所名を数字で選択してください。なお、0で戻れます。",CRGREEN);
			DrawString(0,459,"数字を入力してENTERキーを押してください。＞",CRGREEN);
			ScreenFlip() ;//裏画面を表画面にコピー
			nyuuryokuti= KeyInputNumber( 436 , 459 , 6 , 0 , FALSE );
			if (nyuuryokuti==0){
				return 0;
			}else if ((kakoyear==year) && ((nyuuryokuti*2-1)>=month)){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawBox(0,0,639,479,CRBACK,TRUE);
				DrawString(0,443,"この月は指定できません。",CRWHITE);
				DrawString(0,459,"Hit any key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				return 0;
			}else{
				kakomonth=nyuuryokuti*2-1;
				return kakoyear*12+kakomonth;
			}
		}
		// メッセージ処理
		if( ProcessMessage() == -1 )
		{
			mode=1;
			return 0;
		}
		Sleep(1);
	}
}

void retirerikisi_hyoji(long ichijouhou,long ichijouhou_jiheya,long ichijouhou_saikoui)
{
char jiyuustr[22];
char jiyuustr_riji[22];
//char hyoji_shozoku_heyaid_chokuzen=0;
char hyoji_heyaid_tuusan_chokuzen=0;
char hyoji_heyastring_chokuzen[12];
char hyoji_itimonstring_chokuzen[12];
char deruflag=0;
long bsize_shozoku=0;
long bsize_tosiyori=0;
int year_shozoku=0;
int month_shozoku=0;
int shozoku_rikisiid[RIKISISUU];
char shozoku_heyaid[RIKISISUU];

	int nowrenban=0;
	int nowrenban2=0;
	char yomikomiokflag=0;
	char yomikomiokflag2=0;
	long temp_ichijouhou=0;
	long sumifilesize_retire=0;
	long temp_size=0;
	int i,ii;
	int yearhosei;

	char jinbouhyojiflag=0;

	char temp_filename[MAX_PATH];
	char temp_filename2[MAX_PATH];

	char temp_heyastring2[12];
	int gyousuu_max=0;
	int hyoji_month_2mae=0;//2が月前にする用
	int hyoji_year_2mae=0;//2が月前にする用

	FILE *fp;
	FILE *fp2;
	FILE *fp_temp;

	//しばらくお待ちください表示
	ClearDrawScreen();
	DrawString(100,300,"表示準備中です",CRWHITE);
	DrawString(100,350,"しばらくお待ちください",CRWHITE);
	ScreenFlip();
	for (i=0;i<22;i++){
		jiyuustr[i];
		jiyuustr_riji[i];
	}
	for (i=0;i<12;i++){
		hyoji_heyastring_chokuzen[i];
		hyoji_itimonstring_chokuzen[i];
	}
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
		temp_filename2[i]=0;
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
		temp_heyastring2[i]=0;
	}
	for (i=0;i<28;i++){
		temp_hometownstring[i]=0;
	}

	temp_size=
			sizeof(rikisidata[0].rikisiid)+
			sizeof(namestring[rikisidata[0].nameid])+
			sizeof(hometownstring[rikisidata[0].hometownid])+
			sizeof(heyastring[rikisidata[0].heyaid])+
			sizeof(rikisidata[0].heyaid)+
			sizeof(rikisidata[0].hatudohyo_year)+
			sizeof(rikisidata[0].hatudohyo_month)+
			sizeof(year)+
			sizeof(month)+
			sizeof(rikisidata[0].jikosaiko_bandukenameid)+
			sizeof(rikisidata[0].jikosaiko_bandukesuuji)+
			sizeof(rikisidata[0].makuuti_win)+
			sizeof(rikisidata[0].makuuti_lost)+
			sizeof(rikisidata[0].kiroku_yuushoukaisuu)+
			sizeof(rikisidata[0].kinbosisuu)+
			sizeof(rikisidata[0].shukunshousuu)+
			sizeof(rikisidata[0].kantoushousuu)+
			sizeof(rikisidata[0].ginoushousuu)+
			sizeof(rikisidata[0].wintotal)+
			sizeof(rikisidata[0].losttotal)+
			sizeof(rikisidata[0].kiroku_renshou)+
			sizeof(rikisidata[0].kiroku_renpai)+
			sizeof(rikisidata[0].kako_yuushouflag)+
			sizeof(rikisidata[0].kako_bandukehigasiornisi)+
			sizeof(rikisidata[0].kako_bandukenameid)+
			sizeof(rikisidata[0].kako_bandukesuuji)+
			sizeof(rikisidata[0].kako_win)+
			sizeof(rikisidata[0].kako_lost)+
			sizeof(rikisidata[0].jikosaiko_tournament)+
			sizeof(rikisidata[0].yuushoukaisuu_tournament)+
			sizeof(rikisidata[0].age);


	if (retire_sentaku_category==0){//全部表示
		retirerikisisentaku_num_all=(int)(ichijouhou/temp_size);
		all_retiresentaku_page=(int)(retirerikisisentaku_num_all/20);
		temp_ichijouhou=((int)(retirerikisisentaku_num_all/20))*temp_size*20;
		//リスト表示用読み込み
		for (i=0;i<20;i++){
			if (all_retiresentaku_page+1==(int)((retiresuu_total+19)/20) && retirerikisisentaku_num_all%20!=0 && i-1>(retiresuu_total-1)%20){
				break;
			}
			//ファイルオープン
			sumifilesize_retire=0;
			for (ii=0;ii<RETIREMAXFILESUU;ii++){
				if (ii==0){
					if (filesize_retire[ii]>=temp_ichijouhou+i*temp_size+temp_size){
						strcpy(temp_filename,"data/dat/retirerikisi.dat\0");
						fp = fopen(temp_filename,"rb");
						if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗1" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
						break;
					}else{
						sumifilesize_retire+=filesize_retire[ii];
					}
				}else{
					if (filesize_retire[ii]>=temp_ichijouhou+i*temp_size+temp_size-sumifilesize_retire){
						sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",ii+1);
						fp = fopen(temp_filename,"rb");
						if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗2" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
						break;
					}else{
						sumifilesize_retire+=filesize_retire[ii];
					}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			//位置情報補正
			fseek(fp,temp_ichijouhou+i*temp_size-sumifilesize_retire,SEEK_SET );
			//ここからリスト表示用読み込み
			fread(&temp_rikisiid,sizeof(temp_rikisiid),1,fp);
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
			fclose(fp);
			strcpy(temp_list_namestring[i],temp_namestring);

			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}
		//メイン表示用読み込み
		//ファイルオープン
		sumifilesize_retire=0;
		for (ii=0;ii<RETIREMAXFILESUU;ii++){
			if (ii==0){
				if (filesize_retire[ii]>=ichijouhou+temp_size){
					strcpy(temp_filename,"data/dat/retirerikisi.dat\0");
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗3" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
					break;
				}else{
					sumifilesize_retire+=filesize_retire[ii];
				}
			}else{
				if (filesize_retire[ii]>=ichijouhou+temp_size-sumifilesize_retire){
					sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",ii+1);
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗4" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
					break;
				}else{
					sumifilesize_retire+=filesize_retire[ii];
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		//位置情報補正
		fseek(fp,ichijouhou-sumifilesize_retire,SEEK_SET );
		//ここからメイン表示用読み込み
		fread(&temp_rikisiid,sizeof(temp_rikisiid),1,fp);
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
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}


	if (retire_sentaku_category==1 && retiresuu_jiheya>0){//自部屋表示
		retirerikisisentaku_num_jiheya=(int)(ichijouhou_jiheya/temp_size);
		jiheya_retiresentaku_page=(int)(retirerikisisentaku_num_jiheya/20);
		temp_ichijouhou=((int)(retirerikisisentaku_num_jiheya/20))*temp_size*20;
		//リスト表示用読み込み
		for (i=0;i<20;i++){
			if (jiheya_retiresentaku_page+1==(int)((retiresuu_jiheya+19)/20) && retirerikisisentaku_num_jiheya%20!=0 && i-1>(retiresuu_jiheya-1)%20){
				break;
			}
			//ファイルオープン
			sumifilesize_retire=0;
			for (ii=0;ii<RETIREMAXFILESUU;ii++){
				if (ii==0){
					if (filesize_retire_jiheya[ii]>=temp_ichijouhou+i*temp_size+temp_size){
						strcpy(temp_filename,"data/dat/retirerikisi_jiheya.dat\0");
						fp = fopen(temp_filename,"rb");
						if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗5" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
						break;
					}else{
						sumifilesize_retire+=filesize_retire_jiheya[ii];
					}
				}else{
					if (filesize_retire_jiheya[ii]>=temp_ichijouhou+i*temp_size+temp_size-sumifilesize_retire){
						sprintf(temp_filename,"data/dat/retirerikisi_jiheya%d.dat\0",ii+1);
						fp = fopen(temp_filename,"rb");
						if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗6" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
						break;
					}else{
						sumifilesize_retire+=filesize_retire_jiheya[ii];
					}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			//位置情報補正
			fseek(fp,temp_ichijouhou+i*temp_size-sumifilesize_retire,SEEK_SET );
			//ここからリスト表示用読み込み
			fread(&temp_rikisiid,sizeof(temp_rikisiid),1,fp);
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
			fclose(fp);
			strcpy(temp_list_namestring[i],temp_namestring);

			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}
		//メイン表示用読み込み
		//ファイルオープン
		sumifilesize_retire=0;
		for (ii=0;ii<RETIREMAXFILESUU;ii++){
			if (ii==0){
				if (filesize_retire_jiheya[ii]>=ichijouhou_jiheya+temp_size){
					strcpy(temp_filename,"data/dat/retirerikisi_jiheya.dat\0");
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗7" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
					break;
				}else{
					sumifilesize_retire+=filesize_retire_jiheya[ii];
				}
			}else{
				if (filesize_retire_jiheya[ii]>=ichijouhou_jiheya+temp_size-sumifilesize_retire){
					sprintf(temp_filename,"data/dat/retirerikisi_jiheya%d.dat\0",ii+1);
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗8" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
					break;
				}else{
					sumifilesize_retire+=filesize_retire_jiheya[ii];
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		//位置情報補正
		fseek(fp,ichijouhou_jiheya-sumifilesize_retire,SEEK_SET );
		//ここからメイン表示用読み込み
		fread(&temp_rikisiid,sizeof(temp_rikisiid),1,fp);
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
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

	if (retire_sentaku_category==2 && retiresuu_saikoui>0){//最高位順表示
		retirerikisisentaku_num_saikoui=(int)(ichijouhou_saikoui/temp_size);
		saikoui_retiresentaku_page=(int)(retirerikisisentaku_num_saikoui/20);
		temp_ichijouhou=((int)(retirerikisisentaku_num_saikoui/20))*temp_size*20;
		//リスト表示用読み込み
		for (i=0;i<20;i++){
			if (saikoui_retiresentaku_page+1==(int)((retiresuu_saikoui+19)/20) && retirerikisisentaku_num_saikoui%20!=0 && i-1>(retiresuu_saikoui-1)%20){
				break;
			}
			//ファイルオープン
			sumifilesize_retire=0;
			for (ii=0;ii<RETIREMAXFILESUU;ii++){
				if (ii==0){
					if (filesize_retire_saikoui[ii]>=temp_ichijouhou+i*temp_size+temp_size){
						strcpy(temp_filename,"data/dat/retirerikisi_saikoui.dat\0");
						fp = fopen(temp_filename,"rb");
						if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗9" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
						break;
					}else{
						sumifilesize_retire+=filesize_retire_saikoui[ii];
					}
				}else{
					if (filesize_retire_saikoui[ii]>=temp_ichijouhou+i*temp_size+temp_size-sumifilesize_retire){
						sprintf(temp_filename,"data/dat/retirerikisi_saikoui%d.dat\0",ii+1);
						fp = fopen(temp_filename,"rb");
						if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗10" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
						break;
					}else{
						sumifilesize_retire+=filesize_retire_saikoui[ii];
					}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			//位置情報補正
			fseek(fp,temp_ichijouhou+i*temp_size-sumifilesize_retire,SEEK_SET );
			//ここからリスト表示用読み込み
			fread(&temp_rikisiid,sizeof(temp_rikisiid),1,fp);
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
			fclose(fp);
			strcpy(temp_list_namestring[i],temp_namestring);

			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}
		//メイン表示用読み込み
		//ファイルオープン
		sumifilesize_retire=0;
		for (ii=0;ii<RETIREMAXFILESUU;ii++){
			if (ii==0){
				if (filesize_retire_saikoui[ii]>=ichijouhou_saikoui+temp_size){
					strcpy(temp_filename,"data/dat/retirerikisi_saikoui.dat\0");
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗11" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
					break;
				}else{
					sumifilesize_retire+=filesize_retire_saikoui[ii];
				}
			}else{
				if (filesize_retire_saikoui[ii]>=ichijouhou_saikoui+temp_size-sumifilesize_retire){
					sprintf(temp_filename,"data/dat/retirerikisi_saikoui%d.dat\0",ii+1);
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗12" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
					break;
				}else{
					sumifilesize_retire+=filesize_retire_saikoui[ii];
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		//位置情報補正
		fseek(fp,ichijouhou_saikoui-sumifilesize_retire,SEEK_SET );
		//ここからメイン表示用読み込み
		fread(&temp_rikisiid,sizeof(temp_rikisiid),1,fp);
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
		//クローズ
		fclose(fp);
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

	if( ProcessMessage() == -1 ){mode=1;return ;}

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
			if( ProcessMessage() == -1 ){mode=1;return ;}
		}
	}
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}

	tempsize_kyuujou=sizeof(int)*4+sizeof(char)*2+sizeof(kyuujoustring[0]);

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
			fread(kyuujou_kyuujoustring,sizeof(kyuujoustring[0]),1,fp);
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
	DrawBox(3,76,183,475,CRTAB,TRUE);
	if (retire_sentaku_category==0){//全幕内経験者+自部屋表示
		DrawBox(3,60,62,76,CRTAB,TRUE);
	}else if(retire_sentaku_category==1){//自部屋表示
		DrawBox(63,60,126,76,CRTAB,TRUE);
	}else{//最高位順表示
		DrawBox(127,60,183,76,CRTAB,TRUE);
	}

	//右リストバック
	DrawBox(465,60,636,365,CRTAB,TRUE);

	if (r_torikumi_or_seisekiflag==0){
		DrawBox(rx1[0]-10,ry1[0],rx1[0]-10+34*1,ry1[0]+16,CRTAB,TRUE);
	}else if (r_torikumi_or_seisekiflag==1){
		DrawBox(rx1[0]-10+34*1,ry1[0],rx1[0]-10+34*2,ry1[0]+16,CRTAB,TRUE);
	}else if (r_torikumi_or_seisekiflag==2){
		DrawBox(rx1[0]-10+34*2,ry1[0],rx1[0]-10+34*3,ry1[0]+16,CRTAB,TRUE);
	}else if (r_torikumi_or_seisekiflag==3){
		DrawBox(rx1[0]-10+34*3,ry1[0],rx1[0]-10+34*4,ry1[0]+16,CRTAB,TRUE);
	}else if (r_torikumi_or_seisekiflag==4){
		DrawBox(rx1[0]-10+34*4,ry1[0],rx1[0]-10+34*5,ry1[0]+16,CRTAB,TRUE);
	}
	//右リスト枠表示
	DrawBox(464,44,639,367,CRKEIJIBANOFF,FALSE);//右リスト部分
	DrawBox(463,43,639,367,CRKEIJIBANOFF,FALSE);//右リスト部分

	DrawString(187,450,"←左リスト頁指定",CRGREEN);//ver2.39での変更（追加）
	if (r_hyojikirikaeflag==0){
		DrawString(187,387,"記録概要",CRWHITE);
	}else{
		DrawString(187,387,"記録概要",CRGREEN);
	}
	if (r_hyojikirikaeflag==1){
		DrawString(187+80,387,"能力値",CRWHITE);
	}else{
		DrawString(187+80,387,"能力値",CRGREEN);
	}
	if (r_hyojikirikaeflag==2){
		DrawString(187+80+80,387,"引退後",CRWHITE);
	}else{
		DrawString(187+80+80,387,"引退後",CRGREEN);
	}
	if (r_hyojikirikaeflag==3){
		DrawString(187+80+80+80,387,"力士別",CRWHITE);
	}else{
		DrawString(187+80+80+80,387,"力士別",CRGREEN);
	}
	if (r_hyojikirikaeflag==4){
		DrawString(187+80+80+80+80,387,"休場歴",CRWHITE);
	}else{
		DrawString(187+80+80+80+80,387,"休場歴",CRGREEN);
	}
	if (r_hyojikirikaeflag==5){
		DrawString(187+80+80+80+80+80,387,"所属歴",CRWHITE);
	}else{
		DrawString(187+80+80+80+80+80,387,"所属歴",CRGREEN);
	}

	///////////////メイン画面の最上段に通算部屋IDも表示するためだけにtosiyori.dat読み込み////////////

	bsize_shozoku=sizeof(year)+sizeof(month)+(sizeof(rikisidata[0].rikisiid)+sizeof(rikisidata[0].heyaid))*RIKISISUU;
	bsize_tosiyori=sizeof(year)+sizeof(month)+sizeof(r_tosiyoridata)+sizeof(r_itimondata)+sizeof(r_heyadata)+sizeof(r_heyastring);

	//読み込む年月は記録タイミングの問題で一つ先にしてあるので注意
	nowrenban=(int)( ((temp_retire_year-1)*6+(int)(temp_retire_month/2)+1)/((int)(maxfilesize/bsize_tosiyori)+1) );
	if (nowrenban==0){
		strcpy(temp_filename,"data/dat/tosiyori.dat\0");
		fp2 = fopen(temp_filename,"rb");
		if( fp2 == NULL ){
			fclose(fp2);
			DrawFormatString( 187 , 369+48 ,CRWHITE, "メイン最上段用tosiyori.datファイルオープンに失敗(ban%d)" , nowrenban );
		}
	}else{
		sprintf(temp_filename,"data/dat/tosiyori%d.dat\0",nowrenban+1);
		fp2 = fopen(temp_filename,"rb");
		if( fp2 == NULL ){
			fclose(fp2);
			DrawFormatString( 187 , 369+48 ,CRWHITE, "メイン最上段用tosiyori.datファイルオープンに失敗(ban%d)" , nowrenban );
		}
	}
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//読み込む年月は記録タイミングの問題で一つ先にしてあるので注意
	fseek(fp2,
		bsize_tosiyori*( ((temp_retire_year-1)*6+(int)(temp_retire_month/2)+1)-nowrenban*((int)(maxfilesize/bsize_tosiyori)+1) ),
		SEEK_SET);
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	if(fread(&year_tosiyori,sizeof(year_tosiyori),1,fp2)<1){//EOFor読み取り失敗
		fclose(fp2);
		DrawFormatString( 187 , 369+48 ,CRWHITE, "メイン最上段用tosiyori.datファイル読込に失敗(ban%d)" , nowrenban );
	}
	fread(&month_tosiyori,sizeof(month_tosiyori),1,fp2);
	fread(r_tosiyoridata,sizeof(r_tosiyoridata),1,fp2);
	fread(r_itimondata,sizeof(r_itimondata),1,fp2);
	fread(r_heyadata,sizeof(r_heyadata),1,fp2);
	fread(r_heyastring,sizeof(r_heyastring),1,fp2);
	fclose(fp2);
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける


	///////////////////////////////////////////////////////
//左リスト表示数0の時のエラー回避if文
if (retire_sentaku_category==0 || (retire_sentaku_category==1 && retiresuu_jiheya>0) || (retire_sentaku_category==2 && retiresuu_saikoui>0)){

	////////////////年寄編集襲名者を引退力士から選ぶ画面用グローバル変数/////////////////////
	G_age=temp_age+(temp_retire_year-year);
	G_rikisiid=temp_rikisiid;
	strcpy(G_sikona,temp_namestring);

	///////////////////////メイン画面（共通表示）16p////////////////////////
			DrawFormatString(187,24,CRWHITE,"%s(ID %d) %s部屋(ID %d (%d))",
			temp_namestring,
			temp_rikisiid,
			temp_heyastring,
			temp_heyaid,
			r_heyadata[temp_heyaid].heyaid_tuusan);
			DrawFormatString(187,44,CRWHITE,"%s出身",
			temp_hometownstring);
			DrawFormatString(187,64,CRWHITE,"%4d年%d月初土俵  %4d年%d月引退",
			temp_hatudohyo_year,
			temp_hatudohyo_month,
			temp_retire_year,
			temp_retire_month);
			for (i=0;i<TOSIYORISUU;i++){
				if (tosiyoridata[i].rikisiid==temp_rikisiid){
					DrawFormatString(187,84,CRWHITE,"引退年齢 %d才(現在%d才)",
					temp_age,tosiyoridata[i].age);
					break;
				}
			}
			if (i==TOSIYORISUU){
				DrawFormatString(187,84,CRWHITE,"引退年齢 %d才",
				temp_age);
			}
	////////////////////////////////////////////////////////////////////////////

	/////////////////////メイン画面（概要表示）/////////////////////////////////
	/////////////////////////////////////////////////////////////////////////）
	if (r_hyojikirikaeflag==0){
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
		G_shuumeizumitosiyoriid=-1;
		for (i=0;i<TOSIYORISUU;i++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}
			if (tosiyoridata[i].rikisiid==temp_rikisiid && tosiyoridata[i].shozokuheyaid!=-1){
				DrawFormatString(187,344,CRWHITE,"人望 %d (年寄%s)",tosiyoridata[i].jinbou,tosiyoridata[i].namestring);
				jinbouhyojiflag=1;
				G_shuumeizumitosiyoriid=i;
				break;
			}
		}
		if (jinbouhyojiflag==0){
			DrawString(187,344,"人望なし(廃業)",CRWHITE);
		}
	}
	//////////////////////////////////////////////////////////////////////
}//左リスト表示数0の時のエラー回避if文閉じ括弧
	///////////////////////メイン画面（共通表示）12p////////////////////////
	//SetFontSize( 12 ) ;
	//if( ProcessMessage() == -1 ){mode=1;return ;}
	DrawStringToHandle(rx1[0]-10+3,ry1[0]+3,"取組",CRWHITE,FontHandle12);
	DrawStringToHandle(rx1[0]-10+34*1+3,ry1[0]+3,"成績",CRWHITE,FontHandle12);
	DrawStringToHandle(rx1[0]-10+34*2+3,ry1[0]+3,"士別",CRWHITE,FontHandle12);
	DrawStringToHandle(rx1[0]-10+34*3+3,ry1[0]+3,"記録",CRWHITE,FontHandle12);
	DrawStringToHandle(rx1[0]-10+34*4+3,ry1[0]+3,"決手",CRWHITE,FontHandle12);
	DrawStringToHandle(230,5,"　　　　　　　引退力士",CRWHITE,FontHandle12);
	DrawStringToHandle(3+4,60+3,"全部屋",CRWHITE,FontHandle12);
	DrawStringToHandle(3+4+60,60+3,"当部屋",CRWHITE,FontHandle12);
	DrawStringToHandle(3+4+70+50,60+3,"最高位順",CRWHITE,FontHandle12);
	if (retire_sentaku_category==2){
		DrawStringToHandle(187,369,"※最高位順では当部屋の関取経験者のみがリストアップされます",CRWHITE,FontHandle12);
	}
	DrawStringToHandle(187,369+61,"※メイン画面最上段の所属部屋は引退時のものです",CRWHITE,FontHandle12);
	////////////////////////////////////////////////////////////////////
//左リスト表示数0の時のエラー回避if文
if (retire_sentaku_category==0 || (retire_sentaku_category==1 && retiresuu_jiheya>0) || (retire_sentaku_category==2 && retiresuu_saikoui>0)){
	//////////////////////////////////////////////////////////////////////
	//////////////左リスト表示///////////////////////////////////////////
	if (retire_sentaku_category==0){//全部表示
		DrawFormatStringToHandle(3,78,CRBLACK,FontHandle12,"%d／%dページ",all_retiresentaku_page+1,(int)((retiresuu_total+19)/20));
	}
	if (retire_sentaku_category==1 && retiresuu_jiheya>0){//自部屋表示
		DrawFormatStringToHandle(3,78,CRBLACK,FontHandle12,"%d／%dページ",jiheya_retiresentaku_page+1,(int)((retiresuu_jiheya+19)/20));
	}
	if (retire_sentaku_category==2 && retiresuu_saikoui>0){//最高位順表示
		DrawFormatStringToHandle(3,78,CRBLACK,FontHandle12,"%d／%dページ",saikoui_retiresentaku_page+1,(int)((retiresuu_saikoui+19)/20));
	}
	if (retire_sentaku_category==0 || (retire_sentaku_category==1 && retiresuu_jiheya>0) || (retire_sentaku_category==2 && retiresuu_saikoui>0)){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//左リスト表示
		if (retire_sentaku_category==0){//全部表示
			DrawBox(x1[(retirerikisisentaku_num_all%20)*2],y1[(retirerikisisentaku_num_all%20)*2],x1[(retirerikisisentaku_num_all%20)*2]+180,y1[(retirerikisisentaku_num_all%20)*2]+17,CRKEIJIBANON,TRUE);//クリックしたところを強調
			for(i=0;i<20;i++){
				if (i+all_retiresentaku_page*20<retiresuu_total){
					DrawFormatStringToHandle(x1[i*2],y1[i*2],CRBLACK,FontHandle12,"%s",temp_list_namestring[i]);
				}
			}
		}
		if (retire_sentaku_category==1 && retiresuu_jiheya>0){//自部屋表示
			DrawBox(x1[(retirerikisisentaku_num_jiheya%20)*2],y1[(retirerikisisentaku_num_jiheya%20)*2],x1[(retirerikisisentaku_num_jiheya%20)*2]+180,y1[(retirerikisisentaku_num_jiheya%20)*2]+17,CRKEIJIBANON,TRUE);//クリックしたところを強調
			for(i=0;i<20;i++){
				if (i+jiheya_retiresentaku_page*20<retiresuu_jiheya){
					DrawFormatStringToHandle(x1[i*2],y1[i*2],CRBLACK,FontHandle12,"%s",temp_list_namestring[i]);
				}
			}
		}
		if (retire_sentaku_category==2 && retiresuu_saikoui>0){//最高位順表示
			DrawBox(x1[(retirerikisisentaku_num_saikoui%20)*2],y1[(retirerikisisentaku_num_saikoui%20)*2],x1[(retirerikisisentaku_num_saikoui%20)*2]+180,y1[(retirerikisisentaku_num_saikoui%20)*2]+17,CRKEIJIBANON,TRUE);//クリックしたところを強調
			for(i=0;i<20;i++){
				if (i+saikoui_retiresentaku_page*20<retiresuu_saikoui){
					DrawFormatStringToHandle(x1[i*2],y1[i*2],CRBLACK,FontHandle12,"%s",temp_list_namestring[i]);
				}
			}
		}

	}
	///////////////////////////////////////////////////////////////////
	////////////////r_kiroku.dat読み込み///////////////////////////////////
	nowrenban=0;
	yomikomiokflag=0;
	//オープンするファイルの選択
	while(nowrenban<RETIREMAXFILESUU){//
		if (yomikomiokflag==0){
			//ファイルオープン
			if (nowrenban==0){
				strcpy(temp_filename,"data/dat/r_kiroku.dat\0");
				fp = fopen(temp_filename,"rb");
				if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawStringToHandle( 250 , 240 - 32 , "sub_retirerikisi_new~r_kiroku.datファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );DrawStringToHandle( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );ScreenFlip();WaitKey();mode=1;return;}
			}else{
				sprintf(temp_filename,"data/dat/r_kiroku%d.dat\0",nowrenban+1);
				fp = fopen(temp_filename,"rb");
				if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawStringToHandle( 250 , 240 - 32 , "sub_retirerikisi_new~r_kiroku%d.datファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );DrawStringToHandle( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );ScreenFlip();WaitKey();mode=1;return;}
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//ここからメイン表示用読み込み
		yomikomiokflag=0;
		if(fread(&r_rikisidata[0].rikisiid,sizeof(r_rikisidata[0].rikisiid),1,fp)<1){//EOFor読み取り失敗
			nowrenban++;
			fclose(fp);
		}else{
			yomikomiokflag=1;
			fread(&r_rikisidata[0],sizeof(rikisidata[0]),1,fp);
			fread(&temp_sanyakuijouzaiisuu,sizeof(temp_sanyakuijouzaiisuu),1,fp);
			fread(&temp_makuutiijouzaiisuu,sizeof(temp_makuutiijouzaiisuu),1,fp);
			fread(&temp_juuryouijouzaiisuu,sizeof(temp_juuryouijouzaiisuu),1,fp);
			fread(&temp_stamina_natural_kakosaikou,sizeof(temp_stamina_natural_kakosaikou),1,fp);
			fread(&temp_binshousei_natural_kakosaikou,sizeof(temp_binshousei_natural_kakosaikou),1,fp);

			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (r_rikisidata[0].rikisiid==temp_rikisiid && yomikomiokflag==1){
			break;
		}

	}
	//ファイルクローズ
	fclose(fp);
//////////////////////////////////////

////////////////////////////////////////////////////////
///////////////////////////メイン画面潜在能力値表示（潜在能力をもとに）////////////////////
	if (r_hyojikirikaeflag==1){
		for (i=0;i<12;i++){
			namestring_save[i]=0;
		}
		strcpy(namestring_save,temp_namestring);//r_savehsr用
		DrawStringToHandle(330,330,"能力値ファイル出力",CRGREEN,FontHandle12);
		DrawStringToHandle(187,404,"※潜在能力値の表示です。ご了承ください。",CRWHITE,FontHandle12);
		DrawStringToHandle(187,422-6,"※敏捷性とスタミナは潜在能力からの推測値です。",CRWHITE,FontHandle12);
		DrawBox(187,84,464,84+16,CRBACK,TRUE);
		DrawFormatStringToHandle(187,84,CRWHITE,FontHandle16,"引退年齢 %d才",
		temp_age);
		DrawFormatStringToHandle(310,86,CRWHITE,FontHandle12,"%s",
		wazapattern_string[r_rikisidata[0].motiwazapattern[0]]
		);
		r_rikisidata[0].binshousei=60-(int)((r_rikisidata[0].sinchou_max-159)/2)-(int)((r_rikisidata[0].taijuu_max-69)/5)+temp_binshousei_natural_kakosaikou;
		if ( ((int)(((169-r_rikisidata[0].sinchou_max)*(-3))/2)+140) < r_rikisidata[0].taijuu_max ){
			r_rikisidata[0].binshousei-=(r_rikisidata[0].taijuu_max-((int)(((169-r_rikisidata[0].sinchou_max)*(-3))/2)+140))*2;
		}
		if (r_rikisidata[0].binshousei<10) r_rikisidata[0].binshousei=10;
		if (r_rikisidata[0].binshousei>99) r_rikisidata[0].binshousei=99;
		r_rikisidata[0].stamina=80+temp_stamina_natural_kakosaikou+r_rikisidata[0].binshousei;


		DrawFormatStringToHandle(187,104,CRWHITE,FontHandle12,"身長　 %3d",
		r_rikisidata[0].sinchou_max
		);
		DrawFormatStringToHandle(187,120,CRWHITE,FontHandle12,"体重　 %3d",
		r_rikisidata[0].taijuu_max
		);
	DrawFormatStringToHandle(187,136,CRWHITE,FontHandle12,"積極性 %3d",
	r_rikisidata[0].sekkyokusei
	);
	DrawFormatStringToHandle(187,152,CRWHITE,FontHandle12,"敏捷性 %3d",
	r_rikisidata[0].binshousei
	);
		//DrawStringToHandle(187,152,"敏捷性",CRWHITE,FontHandle12);
		DrawFormatStringToHandle(187,168,CRWHITE,FontHandle12,"突進力 %3d",
		r_rikisidata[0].tossinryoku_max
		);
		DrawFormatStringToHandle(187,184,CRWHITE,FontHandle12,"蹴る力 %3d",
		r_rikisidata[0].kerutikara_max
		);
		DrawFormatStringToHandle(187,200,CRWHITE,FontHandle12,"右腕力 %3d",
		r_rikisidata[0].migiwanryoku_max
		);
		DrawFormatStringToHandle(187,216,CRWHITE,FontHandle12,"左腕力 %3d",
		r_rikisidata[0].hidariwanryoku_max
		);
		DrawFormatStringToHandle(187,232,CRWHITE,FontHandle12,"バラン %3d",
		r_rikisidata[0].balance_max
		);
		DrawFormatStringToHandle(187,248,CRWHITE,FontHandle12,"立会術 %3d",
		r_rikisidata[0].tatiaigijutu_max
		);
		DrawFormatStringToHandle(187,264,CRWHITE,FontHandle12,"突き　 %3d",
		r_rikisidata[0].tuki_max
		);
		DrawFormatStringToHandle(187,280,CRWHITE,FontHandle12,"右脇堅 %3d",
		r_rikisidata[0].migiwakikatasa_max
		);
		DrawFormatStringToHandle(187,296,CRWHITE,FontHandle12,"左脇堅 %3d",
		r_rikisidata[0].hidariwakikatasa_max
		);
		DrawFormatStringToHandle(187,312,CRWHITE,FontHandle12,"あてが %3d",
		r_rikisidata[0].ategai_max
		);
		DrawFormatStringToHandle(187,328,CRWHITE,FontHandle12,"右返し %3d",
		r_rikisidata[0].migikaesi_max
		);
		DrawFormatStringToHandle(187,344,CRWHITE,FontHandle12,"左返し %3d",
		r_rikisidata[0].hidarikaesi_max
		);
		DrawFormatStringToHandle(287,104,CRWHITE,FontHandle12,"右絞り %3d",
		r_rikisidata[0].migisibori_max
		);
		DrawFormatStringToHandle(287,120,CRWHITE,FontHandle12,"左絞り %3d",
		r_rikisidata[0].hidarisibori_max
		);
		DrawFormatStringToHandle(287,136,CRWHITE,FontHandle12,"右抱込 %3d",
		r_rikisidata[0].migikakaekomi_max
		);
		DrawFormatStringToHandle(287,152,CRWHITE,FontHandle12,"左抱込 %3d",
		r_rikisidata[0].hidarikakaekomi_max
		);
		DrawFormatStringToHandle(287,168,CRWHITE,FontHandle12,"ひきつ %3d",
		r_rikisidata[0].hikituke_max
		);
		DrawFormatStringToHandle(287,184,CRWHITE,FontHandle12,"右握力 %3d",
		r_rikisidata[0].migiakuryoku_max
		);
		DrawFormatStringToHandle(287,200,CRWHITE,FontHandle12,"左握力 %3d",
		r_rikisidata[0].hidariakuryoku_max
		);
	DrawFormatStringToHandle(287,216,CRWHITE,FontHandle12,"スタミ %3d",
	r_rikisidata[0].stamina
	);
	//DrawStringToHandle(287,216,"スタミ",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(287,232,CRWHITE,FontHandle12,"根性　 %3d",
	r_rikisidata[0].konjou
	);
		DrawFormatStringToHandle(287,248,CRWHITE,FontHandle12,"粘り　 %3d",
		r_rikisidata[0].nebari_max
		);
		DrawFormatStringToHandle(287,264,CRWHITE,FontHandle12,"足運び %3d",
		r_rikisidata[0].asihakobi_max
		);
	DrawFormatStringToHandle(287,280,CRWHITE,FontHandle12,"柔軟性 %3d",
	r_rikisidata[0].juunansei
	);
	DrawFormatStringToHandle(287,296,CRWHITE,FontHandle12,"頑固　 %3d",
	100-r_rikisidata[0].zunou
	);
		DrawFormatStringToHandle(387,104,CRWHITE,FontHandle12,"右上投 %3d",
		r_rikisidata[0].migiuwatenage_max
		);
		DrawFormatStringToHandle(387,120,CRWHITE,FontHandle12,"左上投 %3d",
		r_rikisidata[0].hidariuwatenage_max
		);
		DrawFormatStringToHandle(387,136,CRWHITE,FontHandle12,"右下投 %3d",
		r_rikisidata[0].migisitatenage_max
		);
		DrawFormatStringToHandle(387,152,CRWHITE,FontHandle12,"左下投 %3d",
		r_rikisidata[0].hidarisitatenage_max
		);
		DrawFormatStringToHandle(387,168,CRWHITE,FontHandle12,"右小投 %3d",
		r_rikisidata[0].migikotenage_max
		);
		DrawFormatStringToHandle(387,184,CRWHITE,FontHandle12,"左小投 %3d",
		r_rikisidata[0].hidarikotenage_max
		);
		DrawFormatStringToHandle(387,200,CRWHITE,FontHandle12,"右掬投 %3d",
		r_rikisidata[0].migisukuinage_max
		);
		DrawFormatStringToHandle(387,216,CRWHITE,FontHandle12,"左掬投 %3d",
		r_rikisidata[0].hidarisukuinage_max
		);
	}
///////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
///////////////////////////メイン画面引退後表示////////////////////
	if (r_hyojikirikaeflag==2){
		int count_debug=0;
		//int rijihyojihoseihituyougyousuu=0;
	///////////////////////////////////////////////////////////////////
	////////////////tosiyori.dat読み込みながら表示///////////////////////////////////
			DrawBox(463,43,639,367,CRBACK,TRUE);//右リスト部分黒塗りつぶし(文字が右にはみ出すので)
			DrawStringToHandle( 187 , 369+35 , "※所属年月、事由、年寄名(所有状況)、一門名、部屋名の順の表示です" , CRWHITE ,FontHandle12);
			nowrenban=0;
			yomikomiokflag=0;
			gyousuu=0;
			gyousuu_max=14;
			hyoji_month_chokuzen=0;
			hyoji_tosiyoriid_chokuzen=0;hyoji_tosiyoriid_chokuzen=-1;
			hyoji_shozokuheyaid_chokuzen=0;hyoji_shozokuheyaid_chokuzen=-1;
			hyoji_shozokuitimonid_chokuzen=0;hyoji_shozokuitimonid_chokuzen=-1;
			hyoji_sishouflag_chokuzen=0;	//hyoji_sishouflag_chokuzen=-1;
			hyoji_rijiflag_chokuzen=0;hyoji_rijiflag_chokuzen=-1;
			hyoji_keishousha_rikisiid_chokuzen=0;hyoji_keishousha_rikisiid_chokuzen=-1;
			hyoji_keishousha_tosiyoriid_chokuzen=0;hyoji_keishousha_tosiyoriid_chokuzen=-1;
			year_tosiyori=0;
			month_tosiyori=0;
			strcpy(hyoji_heyastring_chokuzen,"");
			strcpy(hyoji_itimonstring_chokuzen,"");
			strcpy(jiyuustr,"");
			strcpy(jiyuustr_riji,"");


			//nowrenban=(int)( ((year_shozoku-1)*6+(int)(month_shozoku/2))/((int)(maxfilesize/bsize_tosiyori)+1) );
			nowrenban=(int)( ((temp_retire_year-1)*6+(int)(temp_retire_month/2))/((int)(maxfilesize/bsize_tosiyori)+1) );
			if (nowrenban==0){
				strcpy(temp_filename,"data/dat/tosiyori.dat\0");
				fp = fopen(temp_filename,"rb");
				if( fp == NULL ){
					fclose(fp);
					DrawFormatStringToHandle( 187 , 369+48 ,CRWHITE,FontHandle12, "メイン引退後のtosiyori.datファイルオープンに失敗(ban%d)" , nowrenban );
				}
			}else{
				sprintf(temp_filename,"data/dat/tosiyori%d.dat\0",nowrenban+1);
				fp = fopen(temp_filename,"rb");
				if( fp == NULL ){
					fclose(fp);
					DrawFormatStringToHandle( 187 , 369+48 ,CRWHITE,FontHandle12, "メイン引退後のtosiyori.datファイルオープンに失敗(ban%d)" , nowrenban );
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (temp_retire_year==1 && temp_retire_month==1){
				fseek(fp,
					bsize_tosiyori*( ((temp_retire_year-1)*6+(int)(temp_retire_month/2))-nowrenban*((int)(maxfilesize/bsize_tosiyori)+1) ),
					SEEK_SET);
			}else{
				fseek(fp,
					bsize_tosiyori*( ((temp_retire_year-1)*6+(int)(temp_retire_month/2)-1)-nowrenban*((int)(maxfilesize/bsize_tosiyori)+1) ),
					SEEK_SET);
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			yomikomiokflag=1;
			//オープンするファイルの選択
			while(nowrenban<RETIREMAXFILESUU){//
				if (yomikomiokflag==0){
					//ファイルオープン
					if (nowrenban==0){
						strcpy(temp_filename,"data/dat/tosiyori.dat\0");
						fp = fopen(temp_filename,"rb");
						if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawStringToHandle( 250 , 240 - 32 , "sub_retirerikisi_new~tosiyori.datファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );DrawStringToHandle( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );ScreenFlip();WaitKey();mode=1;return;}
					}else{
						sprintf(temp_filename,"data/dat/tosiyori%d.dat\0",nowrenban+1);
						fp = fopen(temp_filename,"rb");
						if( fp == NULL ){
							fclose(fp);
							break;
						}
					}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				//ここからメイン表示用読み込み
				yomikomiokflag=0;
				if(fread(&year_tosiyori,sizeof(year_tosiyori),1,fp)<1){//EOFor読み取り失敗
					nowrenban++;
					fclose(fp);
				}else{
					yomikomiokflag=1;
					fread(&month_tosiyori,sizeof(month_tosiyori),1,fp);
					fread(r_tosiyoridata,sizeof(r_tosiyoridata),1,fp);
					fread(r_itimondata,sizeof(r_itimondata),1,fp);
					fread(r_heyadata,sizeof(r_heyadata),1,fp);
					fread(r_heyastring,sizeof(r_heyastring),1,fp);
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (month_tosiyori==1){
					hyoji_month_2mae=11;
					hyoji_year_2mae=year_tosiyori-1;
				}else{
					hyoji_month_2mae=month_tosiyori-2;
					hyoji_year_2mae=year_tosiyori;
				}
				if (yomikomiokflag==1 && temp_retire_year*12+temp_retire_month-1<=year_tosiyori*12+month_tosiyori){
					//rijihyojihoseihituyougyousuu=0;
					for (i=0;i<TOSIYORISUU;i++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (r_tosiyoridata[i].rikisiid==temp_rikisiid
						&& r_tosiyoridata[i].shozokuheyaid>=0 && r_tosiyoridata[i].shozokuheyaid<HEYASUU
						&& r_tosiyoridata[i].shozokuitimonid>=0 && r_tosiyoridata[i].shozokuitimonid<ITIMONSUU){
							if (hyoji_tosiyoriid_chokuzen==i 
							&& hyoji_month_chokuzen+2==year_tosiyori*12+month_tosiyori
							&& hyoji_shozokuheyaid_chokuzen==r_tosiyoridata[i].shozokuheyaid
							&& hyoji_shozokuitimonid_chokuzen==r_tosiyoridata[i].shozokuitimonid
							&& hyoji_sishouflag_chokuzen==r_tosiyoridata[i].sishouflag
							//&& (hyoji_rijiflag_chokuzen==r_tosiyoridata[i].rijiflag || (hyoji_rijiflag_chokuzen!=r_tosiyoridata[i].rijiflag && r_tosiyoridata[i].rijiflag==0) )
							//&& (r_tosiyoridata[i].rijiflag==0 || (year_tosiyori%2==0 || month_tosiyori!=3))
							&& month_tosiyori!=3
							&& hyoji_keishousha_rikisiid_chokuzen==r_tosiyoridata[i].keishousha_rikisiid
							&& hyoji_keishousha_tosiyoriid_chokuzen==r_tosiyoridata[i].keishousha_tosiyoriid
							&& strcmp(hyoji_heyastring_chokuzen,r_heyastring[r_tosiyoridata[i].shozokuheyaid])==0
							&& strcmp(hyoji_itimonstring_chokuzen,r_itimondata[r_tosiyoridata[i].shozokuitimonid].namestring)==0
							){
								//何も表示しない
								
								hyoji_tosiyoriid_chokuzen=i;
								hyoji_month_chokuzen=year_tosiyori*12+month_tosiyori;
								hyoji_shozokuheyaid_chokuzen=r_tosiyoridata[i].shozokuheyaid;
								hyoji_shozokuitimonid_chokuzen=r_tosiyoridata[i].shozokuitimonid;
								hyoji_sishouflag_chokuzen=r_tosiyoridata[i].sishouflag;
								hyoji_rijiflag_chokuzen=r_tosiyoridata[i].rijiflag;
								hyoji_keishousha_rikisiid_chokuzen=r_tosiyoridata[i].keishousha_rikisiid;
								hyoji_keishousha_tosiyoriid_chokuzen=r_tosiyoridata[i].keishousha_tosiyoriid;
								strcpy(hyoji_heyastring_chokuzen,r_heyastring[r_tosiyoridata[i].shozokuheyaid]);
								strcpy(hyoji_itimonstring_chokuzen,r_itimondata[r_tosiyoridata[i].shozokuitimonid].namestring);
								
								break;
							}else{
//////////debug
/*
DrawFormatStringToHandle(187,250+count_debug*15,CRRED,FontHandle12,"%d年%d月場所後 年寄ID直前=%d i=%d 力士ID=%d 理事=%d",
hyoji_year_2mae,hyoji_month_2mae,hyoji_tosiyoriid_chokuzen,i,r_tosiyoridata[i].rikisiid,r_tosiyoridata[i].rijiflag
);
count_debug++;
*/
/////////////

								if (hyoji_tosiyoriid_chokuzen!=i){
									if (hyoji_sishouflag_chokuzen!=r_tosiyoridata[i].sishouflag){
										if (r_tosiyoridata[i].sishouflag==1){
											strcpy(jiyuustr,"部屋継承襲名");
										}else{
											strcpy(jiyuustr,"師匠→部屋付襲名");
										}
									}else{
										if (i>=300 && i<TOSIYORISUU){
											strcpy(jiyuustr,"期限");
										}else{
											strcpy(jiyuustr,"襲名");
										}
									}
								}else if (hyoji_shozokuheyaid_chokuzen!=r_tosiyoridata[i].shozokuheyaid){
									if (r_tosiyoridata[i].sishouflag==1){
										strcpy(jiyuustr,"独立");
									}else{
										strcpy(jiyuustr,"移籍");
									}
								}else if (hyoji_shozokuitimonid_chokuzen!=r_tosiyoridata[i].shozokuitimonid){
									strcpy(jiyuustr,"一門移籍");
								}else if (hyoji_sishouflag_chokuzen!=r_tosiyoridata[i].sishouflag){
									if (r_tosiyoridata[i].sishouflag==1){
										strcpy(jiyuustr,"部屋継承(名変)");
									}else{
										strcpy(jiyuustr,"部屋付に降格");
									}
								}else if (hyoji_keishousha_rikisiid_chokuzen!=r_tosiyoridata[i].keishousha_rikisiid){
									strcpy(jiyuustr,"所有変更");
								}else if (hyoji_keishousha_tosiyoriid_chokuzen!=r_tosiyoridata[i].keishousha_tosiyoriid){
									strcpy(jiyuustr,"所有変更");
								}else if (strcmp(hyoji_heyastring_chokuzen,r_heyastring[r_tosiyoridata[i].shozokuheyaid])!=0){
									if (strcmp(hyoji_itimonstring_chokuzen,r_itimondata[r_tosiyoridata[i].shozokuitimonid].namestring)!=0){
										strcpy(jiyuustr,"部屋名一門名変更");
									}else{
										strcpy(jiyuustr,"部屋名変更");
									}
								}else if (strcmp(hyoji_itimonstring_chokuzen,r_itimondata[r_tosiyoridata[i].shozokuitimonid].namestring)!=0){
									strcpy(jiyuustr,"一門名変更");
								}else{
									strcpy(jiyuustr,"");
								}
								if ((r_tosiyoridata[i].rijiflag&0x0f)>0 && (r_tosiyoridata[i].rijiflag&0x0f)<11){
									strcpy(jiyuustr_riji,namestring_riji[(r_tosiyoridata[i].rijiflag&0x0f)-1]);
								}else{
									if ((r_tosiyoridata[i].rijiflag&0x0f)==11){
										strcpy(jiyuustr_riji,"副理事");
									}else if ((r_tosiyoridata[i].rijiflag&0x0f)==12){
										strcpy(jiyuustr_riji,"役員待遇委員");
									}else if ((r_tosiyoridata[i].rijiflag&0x0f)==13){
										strcpy(jiyuustr_riji,"委員");
									}else if ((r_tosiyoridata[i].rijiflag&0x0f)==14){
										strcpy(jiyuustr_riji,"主任");
									}else{
										strcpy(jiyuustr_riji,"平年寄");
									}
								}
								//ここで表示
								if (hyoji_tosiyoriid_chokuzen!=i 
								|| hyoji_month_chokuzen+2!=year_tosiyori*12+month_tosiyori
								|| hyoji_shozokuheyaid_chokuzen!=r_tosiyoridata[i].shozokuheyaid
								|| hyoji_shozokuitimonid_chokuzen!=r_tosiyoridata[i].shozokuitimonid
								|| hyoji_sishouflag_chokuzen!=r_tosiyoridata[i].sishouflag
								//&& r_tosiyoridata[i].rijiflag==0
								|| hyoji_keishousha_rikisiid_chokuzen!=r_tosiyoridata[i].keishousha_rikisiid
								|| hyoji_keishousha_tosiyoriid_chokuzen!=r_tosiyoridata[i].keishousha_tosiyoriid
								|| strcmp(hyoji_heyastring_chokuzen,r_heyastring[r_tosiyoridata[i].shozokuheyaid])!=0
								|| strcmp(hyoji_itimonstring_chokuzen,r_itimondata[r_tosiyoridata[i].shozokuitimonid].namestring)!=0
								){
									if (gyousuu<(page_intaigo+1)*gyousuu_max && gyousuu>=page_intaigo*gyousuu_max){
										if (r_tosiyoridata[i].sishouflag==1){
											if (r_tosiyoridata[i].keishousha_rikisiid!=-1 || r_tosiyoridata[i].keishousha_tosiyoriid!=-1){
												DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%2d月場所後 %s %s(指名済)  %s一門 %s部屋師匠",
												hyoji_year_2mae,hyoji_month_2mae,jiyuustr,r_tosiyoridata[i].namestring,r_itimondata[r_tosiyoridata[i].shozokuitimonid].namestring,
												r_heyastring[r_tosiyoridata[i].shozokuheyaid]
												);
											}else{
												DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%2d月場所後 %s %s  %s一門 %s部屋師匠",
												hyoji_year_2mae,hyoji_month_2mae,jiyuustr,r_tosiyoridata[i].namestring,r_itimondata[r_tosiyoridata[i].shozokuitimonid].namestring,
												r_heyastring[r_tosiyoridata[i].shozokuheyaid]
												);
											}
										}else if (r_tosiyoridata[i].keishousha_rikisiid!=-1 || r_tosiyoridata[i].keishousha_tosiyoriid!=-1){
											DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%2d月場所後 %s %s(借株)  %s一門 %s部屋付き",
											hyoji_year_2mae,hyoji_month_2mae,jiyuustr,r_tosiyoridata[i].namestring,r_itimondata[r_tosiyoridata[i].shozokuitimonid].namestring,
											r_heyastring[r_tosiyoridata[i].shozokuheyaid]
											);
										}else{
											DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%2d月場所後 %s %s  %s一門 %s部屋付き",
											hyoji_year_2mae,hyoji_month_2mae,jiyuustr,r_tosiyoridata[i].namestring,r_itimondata[r_tosiyoridata[i].shozokuitimonid].namestring,
											r_heyastring[r_tosiyoridata[i].shozokuheyaid]
											);
										}
										//rijihyojihoseihituyougyousuu=1;
									}
									gyousuu++;
								}
								if ((r_tosiyoridata[i].rijiflag&0x0f)>0 && (r_tosiyoridata[i].rijiflag&0x0f)<11
									&& year_tosiyori%2==1){
									//if (gyousuu-rijihyojihoseihituyougyousuu<(page_intaigo+1)*gyousuu_max && gyousuu-rijihyojihoseihituyougyousuu>=page_intaigo*gyousuu_max){
									if (gyousuu<(page_intaigo+1)*gyousuu_max && gyousuu>=page_intaigo*gyousuu_max){
										DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%2d月場所後 理事選出 %s",
										hyoji_year_2mae,hyoji_month_2mae,jiyuustr_riji);
									}
									gyousuu++;
								}else if ((r_tosiyoridata[i].rijiflag&0x0f)==11
									&& year_tosiyori%2==1){
									//if (gyousuu-rijihyojihoseihituyougyousuu<(page_intaigo+1)*gyousuu_max && gyousuu-rijihyojihoseihituyougyousuu>=page_intaigo*gyousuu_max){
									if (gyousuu<(page_intaigo+1)*gyousuu_max && gyousuu>=page_intaigo*gyousuu_max){
										DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%2d月場所後 選出 %s",
										hyoji_year_2mae,hyoji_month_2mae,jiyuustr_riji);
									}
									gyousuu++;
								}else if ((hyoji_rijiflag_chokuzen&0x0f)!=(r_tosiyoridata[i].rijiflag&0x0f)){
									//if (gyousuu-rijihyojihoseihituyougyousuu<(page_intaigo+1)*gyousuu_max && gyousuu-rijihyojihoseihituyougyousuu>=page_intaigo*gyousuu_max){
									if (gyousuu<(page_intaigo+1)*gyousuu_max && gyousuu>=page_intaigo*gyousuu_max){

/*
if (temp_rikisiid==74 && hyoji_year_2mae==41 && hyoji_month_2mae==1){
	DrawBox(187,450,639,479,CRBACK,TRUE);
	DrawFormatStringToHandle(187,450,CRWHITE,FontHandle12,"gyousuu=%d rijihyojihoseihituyougyousuu=%d",
	gyousuu,rijihyojihoseihituyougyousuu);
	DrawFormatStringToHandle(187,464,CRWHITE,FontHandle12,"page_intaigo=%d gyousuu_max=%d",
	page_intaigo,gyousuu_max);

}
*/
										DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%2d月場所後 %s",
										hyoji_year_2mae,hyoji_month_2mae,jiyuustr_riji);
									}
									gyousuu++;
								}
								hyoji_tosiyoriid_chokuzen=i;
								hyoji_month_chokuzen=year_tosiyori*12+month_tosiyori;
								hyoji_shozokuheyaid_chokuzen=r_tosiyoridata[i].shozokuheyaid;
								hyoji_shozokuitimonid_chokuzen=r_tosiyoridata[i].shozokuitimonid;
								hyoji_sishouflag_chokuzen=r_tosiyoridata[i].sishouflag;
								hyoji_rijiflag_chokuzen=r_tosiyoridata[i].rijiflag;
								hyoji_keishousha_rikisiid_chokuzen=r_tosiyoridata[i].keishousha_rikisiid;
								hyoji_keishousha_tosiyoriid_chokuzen=r_tosiyoridata[i].keishousha_tosiyoriid;
								strcpy(hyoji_heyastring_chokuzen,r_heyastring[r_tosiyoridata[i].shozokuheyaid]);
								strcpy(hyoji_itimonstring_chokuzen,r_itimondata[r_tosiyoridata[i].shozokuitimonid].namestring);
								break;
							}
						}
					}
					if (yomikomiokflag==1 
					&& hyoji_month_chokuzen!=year_tosiyori*12+month_tosiyori
					&& temp_retire_year*12+temp_retire_month+1<=year_tosiyori*12+month_tosiyori){//年寄データにない場合
						if (gyousuu<(page_intaigo+1)*gyousuu_max && gyousuu>=page_intaigo*gyousuu_max){
							if (temp_age+year_tosiyori-temp_retire_year>=60){
								DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%2d月場所後 退職(%d才)",
								hyoji_year_2mae,hyoji_month_2mae,
								temp_age+year_tosiyori-temp_retire_year
								);
							}else{
								DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%2d月場所後 廃業(%d才)",
								hyoji_year_2mae,hyoji_month_2mae,
								temp_age+year_tosiyori-temp_retire_year
								);
							}
						}
						break;
					}
				}
			}
			//ファイルクローズ
			fclose(fp);
			DrawFormatStringToHandle(200,170+12*15,CRGREEN,FontHandle12,"前頁　%dページ　次頁",page_intaigo+1);

	}
////////////////////////////////////////////////////////
///////////////////////////メイン画面士別戦績表示////////////////////
	if (r_hyojikirikaeflag==3){
		//////////////////////////////////////////////////////
		if (pagenomihenkouflag_r_mainsibetu!=1){
			//////////まずは表示用一時ファイル作成////////////////
			nowrenban=0;
			yomikomiokflag=0;
			//一時記録ファイル読み書きオープン
			fp_temp = fopen("data/temp_sibetu.dat","w+b");
			//w+bでは右の文はいらないはず if( fp_temp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawStringToHandle( 250 , 240 - 32 , "一時ファイル引退メイン士別表示sub_retirerikisi_new~temp_sibetu.datファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );DrawStringToHandle( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );ScreenFlip();WaitKey();mode=1;return;}
			//オープンするファイルの選択
			while(nowrenban<RETIREMAXFILESUU){//
				if (yomikomiokflag==0){
					//ファイルオープン
					if (nowrenban==0){
						strcpy(temp_filename,"data/dat/r_rikisibetu.dat\0");
						fp = fopen(temp_filename,"rb");
						if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawStringToHandle( 250 , 240 - 32 , "引退メイン士別表示sub_retirerikisi_new~r_rikisibetu.datファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );DrawStringToHandle( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );ScreenFlip();WaitKey();mode=1;return;}
					}else{
						sprintf(temp_filename,"data/dat/r_rikisibetu%d.dat\0",nowrenban+1);
						fp = fopen(temp_filename,"rb");
						if( fp == NULL ){
							fclose(fp);
							break;
						}
					}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				//ここからメイン表示用読み込み
				yomikomiokflag=0;
				if(fread(&torikumi_rikisiid,sizeof(torikumi_rikisiid),1,fp)<1){//EOFor読み取り失敗
					nowrenban++;
					fclose(fp);
				}else{
					yomikomiokflag=1;
					fread(&torikumi_year,sizeof(torikumi_year),1,fp);
					fread(&torikumi_month,sizeof(torikumi_month),1,fp);
					fread(torikumi_watasikonbashorikisiid,sizeof(torikumi_watasikonbashorikisiid),1,fp);
					fread(torikumi_aiteid,sizeof(torikumi_aiteid),1,fp);
					fread(torikumi_aitekonbashorikisiid,sizeof(torikumi_aitekonbashorikisiid),1,fp);
					fread(torikumi_aitekonbashonamestring,sizeof(torikumi_aitekonbashonamestring),1,fp);
					fread(torikumi_winkonbasho,sizeof(torikumi_winkonbasho),1,fp);
					fread(torikumi_lostkonbasho,sizeof(torikumi_lostkonbasho),1,fp);
					fread(torikumi_kimaritekonbasho,sizeof(torikumi_kimaritekonbasho),1,fp);
					fread(torikumi_turncountkonbasho,sizeof(torikumi_turncountkonbasho),1,fp);
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (yomikomiokflag==1 && temp_retire_year*12+temp_retire_month<torikumi_year*12+torikumi_month){
					break;
				}
				if (yomikomiokflag==1 && temp_retire_year*12+temp_retire_month>=torikumi_year*12+torikumi_month
				&& temp_hatudohyo_year*12+temp_hatudohyo_month<=torikumi_year*12+torikumi_month){
					if (torikumi_rikisiid==temp_rikisiid){
						//一時ファイルに記録
						for (i=0;i<15;i++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							kakikomizumiflag=0;
							fseek(fp_temp,0,SEEK_SET );//ファイル先頭に
							while(1){
								if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								//新規IDなのか書込済みIDなのか確認
								if(fread(&kakunin_rikisiid,sizeof(kakunin_rikisiid),1,fp_temp)<1){//EOFor読み取り失敗
									break;
								}else{
									fread(kakunin_namestring,sizeof(kakunin_namestring),1,fp_temp);
									fread(&kakunin_wintotal,sizeof(kakunin_wintotal),1,fp_temp);
									fread(&kakunin_losttotal,sizeof(kakunin_losttotal),1,fp_temp);
									fread(temp_heyastring2,sizeof(temp_heyastring2),1,fp_temp);
								}
								if (torikumi_aitekonbashorikisiid[i]==kakunin_rikisiid){
									kakikomizumiflag=1;
									break;
								}
							}
							//対戦相手が新規IDの場合
							if (kakikomizumiflag==0){
								if (torikumi_aitekonbashorikisiid[i]>=0){//勝利の女神も除外
									//新規ID分書き込み
									fseek(fp_temp,0,SEEK_END );
									fwrite(&torikumi_aitekonbashorikisiid[i],sizeof(torikumi_aitekonbashorikisiid[i]),1,fp_temp);
									fwrite(torikumi_aitekonbashonamestring[i],sizeof(torikumi_aitekonbashonamestring[i]),1,fp_temp);
									if (torikumi_winkonbasho[i]==1){
										kakunin_wintotal=1;
										fwrite(&kakunin_wintotal,sizeof(kakunin_wintotal),1,fp_temp);
									}else{
										kakunin_wintotal=0;
										fwrite(&kakunin_wintotal,sizeof(kakunin_wintotal),1,fp_temp);
									}
									if (torikumi_lostkonbasho[i]==1){
										kakunin_losttotal=1;
										fwrite(&kakunin_losttotal,sizeof(kakunin_losttotal),1,fp_temp);
									}else{
										kakunin_losttotal=0;
										fwrite(&kakunin_losttotal,sizeof(kakunin_losttotal),1,fp_temp);
									}
									nowrenban2=0;
									yomikomiokflag2=0;
									if (torikumi_aiteid[i]>=0 && torikumi_aiteid[i]<RIKISISUU 
									&& rikisidata[torikumi_aiteid[i]].rikisiid==torikumi_aitekonbashorikisiid[i]){
										//現役力士
										strcpy(temp_heyastring2,heyastring[rikisidata[torikumi_aiteid[i]].heyaid]);
										fwrite(temp_heyastring2,sizeof(temp_heyastring2),1,fp_temp);
									}else{
										while(nowrenban2<RETIREMAXFILESUU){//
											if (yomikomiokflag2==0){
												//ファイルオープン
												if (nowrenban2==0){
													strcpy(temp_filename2,"data/dat/retirerikisi.dat\0");
													fp2 = fopen(temp_filename2,"rb");
													if( fp2 == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawStringToHandle( 250 , 240 - 32 , "ファイルオープンに失敗1" , GetColor(255,255,255),FontHandle12 );DrawStringToHandle( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );ScreenFlip();WaitKey();mode=1;return ;}
												}else{
													sprintf(temp_filename2,"data/dat/retirerikisi%d.dat\0",nowrenban2+1);
													fp2 = fopen(temp_filename2,"rb");
													if( fp2 == NULL ){
														//引退力士で引退記録してない力士はここまで来ちゃうと思う
														fclose(fp2);
														strcpy(temp_heyastring2,"？？？\0");
														fwrite(temp_heyastring2,sizeof(temp_heyastring2),1,fp_temp);
														break;
													}
												}
											}
											//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
											//ここから部屋表示用だけに読み込み
											yomikomiokflag2=0;
											if(fread(&temp_rikisiid2,sizeof(temp_rikisiid2),1,fp2)<1){//EOFor読み取り失敗
												nowrenban2++;
												fclose(fp2);
											}else{
												yomikomiokflag2=1;
												if (temp_rikisiid2==torikumi_aitekonbashorikisiid[i]){
													fseek(fp2,sizeof(namestring[0])+sizeof(hometownstring[0]),SEEK_CUR );
													//ここで引退時の部屋名読み込みと一時ファイルへ書き込み
													fread(temp_heyastring2,sizeof(temp_heyastring2),1,fp2);
													fwrite(temp_heyastring2,sizeof(temp_heyastring2),1,fp_temp);
													fclose(fp2);
													break;
												}else{
													fseek(fp2,temp_size-sizeof(temp_rikisiid),SEEK_CUR );
												}
												//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
											}
											if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										}
									}
								}
								if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							//対戦相手が書込済みIDの場合
							}else{

								//勝敗数を積み上げるためいったん読み込み
								fseek(fp_temp,-(sizeof(int)*3+sizeof(kakunin_namestring)+sizeof(heyastring[0])),SEEK_CUR );
								fread(&kakunin_rikisiid,sizeof(kakunin_rikisiid),1,fp_temp);
								fread(kakunin_namestring,sizeof(kakunin_namestring),1,fp_temp);
								fread(&kakunin_wintotal,sizeof(kakunin_wintotal),1,fp_temp);
								fread(&kakunin_losttotal,sizeof(kakunin_losttotal),1,fp_temp);
								fread(temp_heyastring2,sizeof(temp_heyastring2),1,fp_temp);
								if (torikumi_winkonbasho[i]==1){
									kakunin_wintotal++;
								}
								if (torikumi_lostkonbasho[i]==1){
									kakunin_losttotal++;
								}
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								//更新後の情報を書き込み
								fseek(fp_temp,-(sizeof(int)*3+sizeof(kakunin_namestring)+sizeof(heyastring[0])),SEEK_CUR );
								fwrite(&kakunin_rikisiid,sizeof(kakunin_rikisiid),1,fp_temp);
								fwrite(kakunin_namestring,sizeof(kakunin_namestring),1,fp_temp);
								fwrite(&kakunin_wintotal,sizeof(kakunin_wintotal),1,fp_temp);
								fwrite(&kakunin_losttotal,sizeof(kakunin_losttotal),1,fp_temp);
								fwrite(temp_heyastring2,sizeof(temp_heyastring2),1,fp_temp);
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							}
						}
					}
				}
			}
			fclose(fp_temp);
			fclose(fp);
			fclose(fp2);
		}
		//////////////////////////////////////////////////////
		//////////表示用一時ファイルを読み込みながら表示////////////////
		//一時記録ファイル読み込みオープン
		fp_temp = fopen("data/temp_sibetu.dat","rb");
		if( fp_temp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawStringToHandle( 250 , 240 - 32 , "一時ファイル引退メイン士別表示sub_retirerikisi_new~temp_sibetu.datファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );DrawStringToHandle( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );ScreenFlip();WaitKey();mode=1;return;}
		gyousuu=0;
		temp_taisensuu_main=0;
		while(1){
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if(fread(&kakunin_rikisiid,sizeof(kakunin_rikisiid),1,fp_temp)<1){//EOFor読み取り失敗
				break;
			}else{
				fread(kakunin_namestring,sizeof(kakunin_namestring),1,fp_temp);
				fread(&kakunin_wintotal,sizeof(kakunin_wintotal),1,fp_temp);
				fread(&kakunin_losttotal,sizeof(kakunin_losttotal),1,fp_temp);
				fread(temp_heyastring2,sizeof(temp_heyastring2),1,fp_temp);
				//ここで表示
				if (temp_taisensuu_main<(page_r_sibetu_main+1)*15 && temp_taisensuu_main>=page_r_sibetu_main*15){
					DrawFormatStringToHandle(187,110+gyousuu*16,CRWHITE,FontHandle12,"%3d勝%3d敗",
					kakunin_wintotal,
					kakunin_losttotal);
					DrawFormatStringToHandle(187+12*6,110+gyousuu*16,CRWHITE,FontHandle12,"%s(%s)ID:%d",
					kakunin_namestring,
					temp_heyastring2,
					kakunin_rikisiid);
					gyousuu++;
				}
				temp_taisensuu_main++;
			}
		}
		fclose(fp_temp);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (temp_taisensuu_main>15){
			DrawFormatStringToHandle(200,170+12*15,CRGREEN,FontHandle12,"前頁　%d／%d頁　次頁　　　←頁指定",page_r_sibetu_main+1,(int)((temp_taisensuu_main-1)/15)+1);
		}
	}
///////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
///////////////////////////メイン画面休場歴表示////////////////////
	if (r_hyojikirikaeflag==4){
		///////////休場数読込//////////////////////
		strcpy(temp_filename,"data/dat/r_kyuujou_index.dat");
		fp = fopen(temp_filename,"rb");
		if( fp == NULL ){
			//ここにエラー処理
			ClearDrawScreen();
			DrawFormatStringToHandle(187,369,CRWHITE,FontHandle12,"%sのオープン失敗",temp_filename);
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
				if( ProcessMessage() == -1 ){mode=1;return ;}
			}
		}
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}

		tempsize_kyuujou=sizeof(int)*4+sizeof(char)*2+sizeof(kyuujoustring[0]);

		strcpy(temp_filename,"data/dat/r_kyuujou.dat");
		fp = fopen(temp_filename,"rb");
		if( fp == NULL ){
			//ここにエラー処理
			ClearDrawScreen();
			DrawFormatStringToHandle(187,369,CRWHITE,FontHandle12,"%sのオープン失敗",temp_filename);
			ScreenFlip();
			WaitKey();
			mode=1;return ;
		}else{
			fseek(fp,tempsize_kyuujou*kyuujou_kirokusuu_long,SEEK_SET );
			kyuujou_yasumi_total=0;
			kyuujou_yasumi_total_makuuti=0;
			gyousuu=0;
			gyousuu_max=12;
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
				fread(kyuujou_kyuujoustring,sizeof(kyuujoustring[0]),1,fp);
				kyuujou_yasumi_total+=kyuujou_yasumi;
				if (kyuujou_bandukenameid<=4){
					kyuujou_yasumi_total_makuuti+=kyuujou_yasumi;
				}
				//ここから表示
				if (gyousuu<(page_kyuujou+1)*gyousuu_max && gyousuu>=page_kyuujou*gyousuu_max){
					if (kyuujou_bandukesuuji!=0){
						DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,
						"%d年%d月 %s%d %d休 %s",
						kyuujou_year,kyuujou_month,
						bandukenamestring[kyuujou_bandukenameid],kyuujou_bandukesuuji,
						kyuujou_yasumi,kyuujou_kyuujoustring
						);
					}else{
						DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,
						"%d年%d月 %s %d休 %s",
						kyuujou_year,kyuujou_month,
						bandukenamestring[kyuujou_bandukenameid],
						kyuujou_yasumi,kyuujou_kyuujoustring
						);
					}
				}
				gyousuu++;
				//if( ProcessMessage() == -1 ){mode=1;return ;}
			}
		}
		fclose(fp);
		/////////休場数読込ここまで//////////////////
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		DrawFormatStringToHandle(200,170+12*15,CRGREEN,FontHandle12,"前頁　%dページ　次頁",page_kyuujou+1);
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
//////////////////////////////////////////////////////
///////////////////////////メイン画面所属歴(現役時)表示////////////////////
	if (r_hyojikirikaeflag==5){
	///////////////////////////////////////////////////////////////////
	////////////////tosiyori.datとshozoku.datを読み込みながら表示///////////////////////////////////
		DrawBox(463,43,639,367,CRBACK,TRUE);//右リスト部分黒塗りつぶし(文字が右にはみ出すので)
		DrawStringToHandle( 187 , 369+35 , "※所属年月、事由、一門名、部屋名 部屋ID(通算部屋ID)の順の表示です" , CRWHITE ,FontHandle12);
		nowrenban=0;
		nowrenban=-1;
		gyousuu=0;
		year_shozoku=0;
		month_shozoku=0;
		//hyoji_shozoku_heyaid_chokuzen=-1;
		hyoji_heyaid_tuusan_chokuzen=-1;
		strcpy(hyoji_heyastring_chokuzen,"");
		strcpy(hyoji_itimonstring_chokuzen,"");
		hyoji_month_chokuzen=-1;
		for(i=0;i<RIKISISUU;i++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			shozoku_rikisiid[i]=0;
			shozoku_heyaid[i]=0;
		}
		//所属ファイルオープン
		strcpy(temp_filename,"data/dat/shozoku.dat\0");
		fp = fopen(temp_filename,"rb");
		if( fp == NULL ){
			DrawStringToHandle( 187 , 369+48, "sub_retirerikisi_new~shozoku.datファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );
			fclose(fp);
		}else{
			fseek(fp,
				bsize_shozoku*( (temp_hatudohyo_year-1)*6+(int)(temp_hatudohyo_month/2) ),
				SEEK_SET);
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			//ここからループ
			while(1){//
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				//ここからメイン表示用読み込み
				if(fread(&year_shozoku,sizeof(year_shozoku),1,fp)<1){//EOFor読み取り失敗
					fclose(fp);
					if (nowrenban!=-1){
						fclose(fp2);
					}

//DrawFormatStringToHandle( 187, 369-60 ,CRWHITE, "↓初土俵%d年%d月とのtemp_hatudohyo" ,temp_hatudohyo_year,temp_hatudohyo_month);
//DrawFormatStringToHandle( 187, 369-40 ,CRWHITE, "%d年%d月　year_shozokuの読込失敗でループ抜け" ,year_shozoku,month_shozoku);

					//ファイル末端と引退年月が重なる場合もありうるので以下のメッセージはコメントアウト
					//DrawStringToHandle( 187 , 369+48 , "shozoku.datの年の読込に失敗(コメントアウト予定)" , CRWHITE );
					break;
				}
				fread(&month_shozoku,sizeof(month_shozoku),1,fp);
				for(i=0;i<RIKISISUU;i++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					fread(&shozoku_rikisiid[i],sizeof(rikisidata[0].rikisiid),1,fp);
					fread(&shozoku_heyaid[i],sizeof(rikisidata[0].heyaid),1,fp);
				}
				//引退後年月の読込
				if (temp_retire_year*12+temp_retire_month<year_shozoku*12+month_shozoku){
					fclose(fp);
					fclose(fp2);

//DrawFormatStringToHandle( 187, 369-60 ,CRWHITE, "↓引退%d年%d月とのtemp_retire" ,temp_retire_year,temp_retire_month);
//DrawFormatStringToHandle( 187, 369-40 ,CRWHITE, "%d年%d月　引退後年月の読込でループ抜け" ,year_shozoku,month_shozoku);

					break;
				}
				//必要に応じて年寄ファイル再オープン
				if (nowrenban<(int)( ((year_shozoku-1)*6+(int)(month_shozoku/2))/((int)(maxfilesize/bsize_tosiyori)+1) ) ){
					if (nowrenban!=-1){
						fclose(fp2);
					}
					nowrenban=(int)( ((year_shozoku-1)*6+(int)(month_shozoku/2))/((int)(maxfilesize/bsize_tosiyori)+1) );
					if (nowrenban==0){
						strcpy(temp_filename,"data/dat/tosiyori.dat\0");
						fp2 = fopen(temp_filename,"rb");
						if( fp2 == NULL ){
							fclose(fp);
							fclose(fp2);
							DrawFormatStringToHandle( 187 , 369+48 ,CRWHITE,FontHandle12, "shozoku.datは読み込めてるのにtosiyori.datファイルオープンに失敗(ban%d)" , nowrenban );
							break;
						}
					}else{
						sprintf(temp_filename,"data/dat/tosiyori%d.dat\0",nowrenban+1);
						fp2 = fopen(temp_filename,"rb");
						if( fp2 == NULL ){
							fclose(fp);
							fclose(fp2);
							DrawFormatStringToHandle( 187 , 369+48 ,CRWHITE,FontHandle12, "shozoku.datは読み込めてるのにtosiyori.datファイルオープンに失敗(ban%d)" , nowrenban );
							break;
						}
					}
					if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					fseek(fp2,
						bsize_tosiyori*( ((temp_hatudohyo_year-1)*6+(int)(temp_hatudohyo_month/2))-nowrenban*((int)(maxfilesize/bsize_tosiyori)+1) ),
						SEEK_SET);
					if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				if(fread(&year_tosiyori,sizeof(year_tosiyori),1,fp2)<1){//EOFor読み取り失敗
					fclose(fp);
					fclose(fp2);
					DrawFormatStringToHandle( 187 , 369+48 ,CRWHITE,FontHandle12, "shozoku.datは読み込めてるのにtosiyori.datファイル読込に失敗(ban%d)" , nowrenban );
					break;
				}
				fread(&month_tosiyori,sizeof(month_tosiyori),1,fp2);
				fread(r_tosiyoridata,sizeof(r_tosiyoridata),1,fp2);
				fread(r_itimondata,sizeof(r_itimondata),1,fp2);
				fread(r_heyadata,sizeof(r_heyadata),1,fp2);
				fread(r_heyastring,sizeof(r_heyastring),1,fp2);
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				//ここから表示
				deruflag=0;
				for(i=0;i<RIKISISUU;i++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (shozoku_rikisiid[i]==temp_rikisiid
					){
/////////
//DrawBox(187,369-20,639,367,CRBACK,TRUE);
//DrawFormatStringToHandle( 187, 369-20 ,CRWHITE, "%d年%d月%d通過　部屋ID%d" ,year_tosiyori,month_tosiyori, temp_rikisiid,shozoku_heyaid[i] );
/////////
						for (ii=0;ii<TOSIYORISUU;ii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							if (r_tosiyoridata[ii].shozokuheyaid==shozoku_heyaid[i]){
								//ここに前回表示時と同じ状況でないかどうかの判断文
								if (hyoji_heyaid_tuusan_chokuzen!=r_heyadata[shozoku_heyaid[i]].heyaid_tuusan
								|| strcmp(hyoji_heyastring_chokuzen,r_heyastring[shozoku_heyaid[i]])!=0
								|| strcmp(hyoji_itimonstring_chokuzen,r_itimondata[r_tosiyoridata[ii].shozokuitimonid].namestring)!=0
								|| (year_shozoku==temp_retire_year && month_shozoku==temp_retire_month)
								){
									//ここに入門、部屋名変更、部屋移籍(新設や消滅の場合)、一門名変更なのかの区別if文
									if (year_shozoku==temp_hatudohyo_year && month_shozoku==temp_hatudohyo_month && year_shozoku==temp_retire_year && month_shozoku==temp_retire_month){
										if (shozoku_heyaid[i]!=temp_heyaid){
											DrawStringToHandle( 187 , 369+48 , "※この力士は部屋新設・消滅に伴う移籍直後に引退",CRRED ,FontHandle12);
											strcpy(jiyuustr," 入門移籍引退");
										}else{
											strcpy(jiyuustr," 入門引退");
										}
										hyoji_month_2mae=month_shozoku;
										hyoji_year_2mae=year_shozoku;
									}else if (year_shozoku==temp_hatudohyo_year && month_shozoku==temp_hatudohyo_month){
										strcpy(jiyuustr," 入門");
										hyoji_month_2mae=month_shozoku;
										hyoji_year_2mae=year_shozoku;
									}else if (year_shozoku==temp_retire_year && month_shozoku==temp_retire_month){
										if (shozoku_heyaid[i]!=temp_heyaid){
											DrawStringToHandle( 187 , 369+48 , "※この力士は部屋新設・消滅に伴う移籍直後に引退",CRRED ,FontHandle12);
											strcpy(jiyuustr,"場所後 移籍引退");
										}else{
											strcpy(jiyuustr,"場所後 引退");
										}
										hyoji_month_2mae=month_shozoku;
										hyoji_year_2mae=year_shozoku;
									}else if (hyoji_heyaid_tuusan_chokuzen!=r_heyadata[shozoku_heyaid[i]].heyaid_tuusan){
										strcpy(jiyuustr,"場所後 移籍");
										if (month_shozoku==1){
											hyoji_month_2mae=11;
											hyoji_year_2mae=year_shozoku-1;
										}else{
											hyoji_month_2mae=month_shozoku-2;
											hyoji_year_2mae=year_shozoku;
										}
									}else if (strcmp(hyoji_heyastring_chokuzen,r_heyastring[shozoku_heyaid[i]])!=0){
										strcpy(jiyuustr,"場所後 部屋名変更");
										if (month_shozoku==1){
											hyoji_month_2mae=11;
											hyoji_year_2mae=year_shozoku-1;
										}else{
											hyoji_month_2mae=month_shozoku-2;
											hyoji_year_2mae=year_shozoku;
										}
									}else if (strcmp(hyoji_itimonstring_chokuzen,r_itimondata[r_tosiyoridata[ii].shozokuitimonid].namestring)!=0){
										strcpy(jiyuustr,"場所後 一門名変更");
										if (month_shozoku==1){
											hyoji_month_2mae=11;
											hyoji_year_2mae=year_shozoku-1;
										}else{
											hyoji_month_2mae=month_shozoku-2;
											hyoji_year_2mae=year_shozoku;
										}
									}
									DrawFormatStringToHandle(187,104+gyousuu*16,CRWHITE,FontHandle12,"%d年%2d月%s %s一門 %s部屋 ID%d(%d)",
									hyoji_year_2mae,hyoji_month_2mae,
									jiyuustr,
									r_itimondata[r_tosiyoridata[ii].shozokuitimonid].namestring,
									r_heyastring[shozoku_heyaid[i]],
									shozoku_heyaid[i],
									r_heyadata[shozoku_heyaid[i]].heyaid_tuusan
									);
									gyousuu++;
									//hyoji_shozoku_heyaid_chokuzen=shozoku_heyaid[i];
									hyoji_heyaid_tuusan_chokuzen=r_heyadata[shozoku_heyaid[i]].heyaid_tuusan;
									strcpy(hyoji_heyastring_chokuzen,r_heyastring[shozoku_heyaid[i]]);
									strcpy(hyoji_itimonstring_chokuzen,r_itimondata[r_tosiyoridata[ii].shozokuitimonid].namestring);
									hyoji_month_chokuzen=year_shozoku*12+month_shozoku;
									deruflag=1;
									break;
								}
							}
						}
						if (deruflag==1){
							break;
						}
					}
				}
			}
		}
	}
////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////
////////////////////取組タブ分表示/////////////////////////
	if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5
	&& r_torikumi_or_seisekiflag==0){//右取組タブ
		////////////////r_rikisibetu.dat読み込み///////////////////////////////////
		//表示する年月を初土俵年月～引退年月の間にする
		if (hyoji_torikumi_year*12+hyoji_torikumi_month<temp_hatudohyo_year*12+temp_hatudohyo_month){
			hyoji_torikumi_year=temp_hatudohyo_year;
			hyoji_torikumi_month=temp_hatudohyo_month;
		}
		if (hyoji_torikumi_year*12+hyoji_torikumi_month>temp_retire_year*12+temp_retire_month){
			hyoji_torikumi_year=temp_retire_year;
			hyoji_torikumi_month=temp_retire_month;
		}
		//オープンするファイルの選択

		nowrenban=(int)( ((hyoji_torikumi_year-1)*6+(int)(hyoji_torikumi_month/2))/((int)(maxfilesize/size_r_rikisibetu)+1) );
		//ファイルオープン
		if (nowrenban==0){
			strcpy(temp_filename,"data/dat/r_rikisibetu.dat\0");
			fp = fopen(temp_filename,"rb");
			if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawStringToHandle( 250 , 240 - 32 , "sub_retirerikisi_new~r_rikisibetu.datファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );DrawStringToHandle( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );ScreenFlip();WaitKey();mode=1;return;}
		}else{
			sprintf(temp_filename,"data/dat/r_rikisibetu%d.dat\0",nowrenban+1);
			fp = fopen(temp_filename,"rb");
			if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawStringToHandle( 250 , 240 - 32 , "sub_retirerikisi_new~r_rikisibetu%d.datファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );DrawStringToHandle( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );ScreenFlip();WaitKey();mode=1;return;}
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//ここから表示用読み込み
		fseek(fp,
			size_r_rikisibetu*( ((hyoji_torikumi_year-1)*6+(int)(hyoji_torikumi_month/2))-nowrenban*((int)(maxfilesize/size_r_rikisibetu)+1) ),
			SEEK_SET);
		for (i=0;i<RIKISISUU;i++){
			fread(&torikumi_rikisiid,sizeof(torikumi_rikisiid),1,fp);
			fread(&torikumi_year,sizeof(torikumi_year),1,fp);
			fread(&torikumi_month,sizeof(torikumi_month),1,fp);
			fread(torikumi_watasikonbashorikisiid,sizeof(torikumi_watasikonbashorikisiid),1,fp);
			fread(torikumi_aiteid,sizeof(torikumi_aiteid),1,fp);
			fread(torikumi_aitekonbashorikisiid,sizeof(torikumi_aitekonbashorikisiid),1,fp);
			fread(torikumi_aitekonbashonamestring,sizeof(torikumi_aitekonbashonamestring),1,fp);
			fread(torikumi_winkonbasho,sizeof(torikumi_winkonbasho),1,fp);
			fread(torikumi_lostkonbasho,sizeof(torikumi_lostkonbasho),1,fp);
			fread(torikumi_kimaritekonbasho,sizeof(torikumi_kimaritekonbasho),1,fp);
			fread(torikumi_turncountkonbasho,sizeof(torikumi_turncountkonbasho),1,fp);
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (torikumi_rikisiid==temp_rikisiid){
				//ファイルクローズ
				fclose(fp);
				break;
			}
		}

////////////////////
DrawFormatStringToHandle( 189 , 465 , CRWHITE,FontHandle12,"%d年%d月分を表示のつもりで%d年%d月分を読込(検証用表示%dban)" ,hyoji_torikumi_year,hyoji_torikumi_month, torikumi_year,torikumi_month,nowrenban );
////////////////////
//簡易ビデオ表示用
nowhyoji_torikumitab_year=torikumi_year;
nowhyoji_torikumitab_month=torikumi_month;
nowhyoji_torikumitab_ID=torikumi_rikisiid;
//nowhyoji_torikumitab_ID2[]
strcpy(nowhyoji_torikumitab_namestring,temp_namestring);
//nowhyoji_torikumitab_namestring2[]
//video(nowhyoji_torikumitab_ID,nowhyoji_torikumitab_ID2[],nowhyoji_torikumitab_year,nowhyoji_torikumitab_month,nowhyoji_torikumitab_namestring,nowhyoji_torikumitab_namestring2[]);

		DrawStringToHandle(rx1[34]-8,ry1[34],"決まり手を",CRWHITE,FontHandle12);
		DrawStringToHandle(rx1[36]-8,ry1[36],"左クリックで士別タブへ",CRWHITE,FontHandle12);
		DrawStringToHandle(rx1[38]-8,ry1[38],"右クリックで取組概要へ",CRWHITE,FontHandle12);

		DrawFormatStringToHandle(rx1[2],ry1[2],CRGREEN,FontHandle12,"%d年%s場所(検索)",
		hyoji_torikumi_year,
		normal_bashostring[(int)(hyoji_torikumi_month/2)]
		);
		for (i=0;i<15;i++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (torikumi_rikisiid==torikumi_watasikonbashorikisiid[i]){
				if (torikumi_winkonbasho[i]==1){
					//簡易ビデオ表示用
					nowhyoji_torikumitab_ID2[i]=torikumi_aitekonbashorikisiid[i];
					strcpy(nowhyoji_torikumitab_namestring2[i],torikumi_aitekonbashonamestring[i]);
					//ver2.43で修正「勝利の女神」
					//現役力士で通算力士ID(aitekonbashorikisiid)が999の力士の表示を正しく表示できるようにした
					if (torikumi_aiteid[i]==999){
						DrawFormatStringToHandle(rx1[i*2+4]-10,ry1[i*2+4],CRBLACK,FontHandle12,"%2d 勝利の女神",
						i+1);
					}else if (rikisidata[torikumi_aiteid[i]].rikisiid==torikumi_aitekonbashorikisiid[i]){//取組相手の通算力士IDが同じなら引退してないからクリックして飛べるように緑文字にする
						//DrawFormatStringToHandle(rx1[i*2+4]-10,ry1[i*2+4],CRGREEN,FontHandle12,"%2d %s",
						DrawFormatStringToHandle(rx1[i*2+4]-10,ry1[i*2+4],CRBLACK,FontHandle12,"%2d %s",
						i+1,torikumi_aitekonbashonamestring[i]);
					}else{
						DrawFormatStringToHandle(rx1[i*2+4]-10,ry1[i*2+4],CRGREEN,FontHandle12,"%2d %s",
						i+1,torikumi_aitekonbashonamestring[i]);
					}
					DrawBox( rx1[i*2+5],ry1[i*2+5] , 636,ry1[i*2+5]+12 , CRTAB , TRUE) ;
					DrawStringToHandle(rx1[i*2+5],ry1[i*2+5],"●",GetColor(255,255,255),FontHandle12);
					DrawFormatStringToHandle(rx1[i*2+5],ry1[i*2+5],CRBLACK,FontHandle12,"　%s%2d",torikumi_kimaritekonbasho[i],torikumi_turncountkonbasho[i]);
				}else if (torikumi_lostkonbasho[i]==1){
					//簡易ビデオ表示用
					nowhyoji_torikumitab_ID2[i]=torikumi_aitekonbashorikisiid[i];
					strcpy(nowhyoji_torikumitab_namestring2[i],torikumi_aitekonbashonamestring[i]);
					if (rikisidata[torikumi_aiteid[i]].rikisiid==torikumi_aitekonbashorikisiid[i]){//取組相手の通算力士IDが同じなら引退してないからクリックして飛べるように緑文字にする
						//DrawFormatStringToHandle(rx1[i*2+4]-10,ry1[i*2+4],CRGREEN,FontHandle12,"%2d %s",
						DrawFormatStringToHandle(rx1[i*2+4]-10,ry1[i*2+4],CRBLACK,FontHandle12,"%2d %s",
						i+1,torikumi_aitekonbashonamestring[i]);
					}else{
						DrawFormatStringToHandle(rx1[i*2+4]-10,ry1[i*2+4],CRGREEN,FontHandle12,"%2d %s",
						i+1,torikumi_aitekonbashonamestring[i]);
					}
					DrawBox( rx1[i*2+5],ry1[i*2+5] , 636,ry1[i*2+5]+12 , CRTAB , TRUE) ;
					DrawFormatStringToHandle(rx1[i*2+5],ry1[i*2+5],CRBLACK,FontHandle12,"●%s%2d",torikumi_kimaritekonbasho[i],torikumi_turncountkonbasho[i]);
				}
			}
		}
	}
/////////////////////////////////////////////////////////
////////////////////成績タブ分表示///////////////////
	if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5
	&& r_torikumi_or_seisekiflag==1){//右成績タブ
		yearhosei=(temp_retire_year*12+temp_retire_month);
		for (i=0;i<18;i++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (temp_kako_bandukehigasiornisi[i+retire_sentaku_page*18]!=-1){
				nowhyoji_seisekitab_year[i]=((int)((yearhosei-(i+retire_sentaku_page*18)*2)/12));
				nowhyoji_seisekitab_month[i]=(((int)((temp_retire_month+3)/2)-i+4+18)%6)*2+1;
				DrawFormatStringToHandle(rx1[i*2+4]-10,ry1[i*2+4],CRBLACK,FontHandle12,"%02d%s",
				((int)((yearhosei-(i+retire_sentaku_page*18)*2)/12))%100,tanshuku_bashostring[((int)((temp_retire_month+3)/2)-i+4+18)%6]);
				if (temp_kako_bandukehigasiornisi[i+retire_sentaku_page*18]==1 ){
					DrawStringToHandle(rx1[i*2+4]+20,ry1[i*2+4],"東",CRBLACK,FontHandle12);
				}else{
					DrawStringToHandle(rx1[i*2+4]+20,ry1[i*2+4],"西",CRBLACK,FontHandle12);
				}
				if (temp_kako_bandukesuuji[i+retire_sentaku_page*18]!=0){
					DrawFormatStringToHandle(rx1[i*2+4]+32,ry1[i*2+4],CRBLACK,FontHandle12,"%s%3d",
					bandukenamestring[temp_kako_bandukenameid[i+retire_sentaku_page*18]],
					temp_kako_bandukesuuji[i+retire_sentaku_page*18]);
				}else{
					DrawFormatStringToHandle(rx1[i*2+4]+32,ry1[i*2+4],CRBLACK,FontHandle12,"%s",
					bandukenamestring[temp_kako_bandukenameid[i+retire_sentaku_page*18]]);
				}
				if (temp_kako_bandukenameid[i+retire_sentaku_page*18]<=5 && (temp_kako_win[i+retire_sentaku_page*18]+temp_kako_lost[i+retire_sentaku_page*18])<15){
					DrawFormatStringToHandle(rx1[i*2+5]+22,ry1[i*2+5],CRGREEN,FontHandle12,"%2d－%2d-%d",
					temp_kako_win[i+retire_sentaku_page*18],temp_kako_lost[i+retire_sentaku_page*18],15-(temp_kako_win[i+retire_sentaku_page*18]+temp_kako_lost[i+retire_sentaku_page*18]));
				}else if (temp_kako_bandukenameid[i+retire_sentaku_page*18]>5 && (temp_kako_win[i+retire_sentaku_page*18]+temp_kako_lost[i+retire_sentaku_page*18])<7){
					DrawFormatStringToHandle(rx1[i*2+5]+22,ry1[i*2+5],CRGREEN,FontHandle12,"%2d－%2d-%d",
					temp_kako_win[i+retire_sentaku_page*18],temp_kako_lost[i+retire_sentaku_page*18],7-(temp_kako_win[i+retire_sentaku_page*18]+temp_kako_lost[i+retire_sentaku_page*18]));
				}else{
					DrawFormatStringToHandle(rx1[i*2+5]+22,ry1[i*2+5],CRGREEN,FontHandle12,"%2d－%2d",
					temp_kako_win[i+retire_sentaku_page*18],temp_kako_lost[i+retire_sentaku_page*18]);
				}
				if (temp_kako_yuushouflag[i+retire_sentaku_page*18]==1){
					DrawStringToHandle(622,ry1[i*2+5],"優",CRBLACK,FontHandle12);
				}
			}
		}
		DrawFormatStringToHandle(rx1[2]+76,ry1[2]+3,CRWHITE,FontHandle12,"%2d/%d頁",
		retire_sentaku_page+1,
		(int)(((temp_retire_year*12+temp_retire_month)-(temp_hatudohyo_year*12+temp_hatudohyo_month)+2)/2/18)+1
		);
	}
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
////////////////////士別タブ分表示/////////////////////////
	if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5
	&& r_torikumi_or_seisekiflag==2){//右士別タブ
		////////////////r_rikisibetu.dat読み込みながら表示///////////////////////////////////
		nowrenban=0;
		yomikomiokflag=0;
		temp_taisensuu=0;
		gyousuu=0;
		r_sibetu_wintotal=0;
		r_sibetu_losttotal=0;
		//オープンするファイルの選択
		while(nowrenban<RETIREMAXFILESUU){//
			if (yomikomiokflag==0){
				//ファイルオープン
				if (nowrenban==0){
					strcpy(temp_filename,"data/dat/r_rikisibetu.dat\0");
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawStringToHandle( 250 , 240 - 32 , "sub_retirerikisi_new~r_rikisibetu.datファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );DrawStringToHandle( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );ScreenFlip();WaitKey();mode=1;return;}
				}else{
					sprintf(temp_filename,"data/dat/r_rikisibetu%d.dat\0",nowrenban+1);
					fp = fopen(temp_filename,"rb");
					break;
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			//ここから表示用読み込み
			yomikomiokflag=0;
			if(fread(&torikumi_rikisiid,sizeof(torikumi_rikisiid),1,fp)<1){//EOFor読み取り失敗
				nowrenban++;
				fclose(fp);
			}else{
				yomikomiokflag=1;
				fread(&torikumi_year,sizeof(torikumi_year),1,fp);
				fread(&torikumi_month,sizeof(torikumi_month),1,fp);
				fread(torikumi_watasikonbashorikisiid,sizeof(torikumi_watasikonbashorikisiid),1,fp);
				fread(torikumi_aiteid,sizeof(torikumi_aiteid),1,fp);
				fread(torikumi_aitekonbashorikisiid,sizeof(torikumi_aitekonbashorikisiid),1,fp);
				fread(torikumi_aitekonbashonamestring,sizeof(torikumi_aitekonbashonamestring),1,fp);
				fread(torikumi_winkonbasho,sizeof(torikumi_winkonbasho),1,fp);
				fread(torikumi_lostkonbasho,sizeof(torikumi_lostkonbasho),1,fp);
				fread(torikumi_kimaritekonbasho,sizeof(torikumi_kimaritekonbasho),1,fp);
				fread(torikumi_turncountkonbasho,sizeof(torikumi_turncountkonbasho),1,fp);
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (yomikomiokflag==1 && temp_retire_year*12+temp_retire_month<torikumi_year*12+torikumi_month){
				break;
			}
			if (torikumi_rikisiid==temp_rikisiid && yomikomiokflag==1 
			&& temp_retire_year*12+temp_retire_month>=torikumi_year*12+torikumi_month
			&& temp_hatudohyo_year*12+temp_hatudohyo_month<=torikumi_year*12+torikumi_month){
				for (i=0;i<15;i++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (r_sibetu_rikisiid==torikumi_aitekonbashorikisiid[i]){
						strcpy(r_sibetu_namestring,torikumi_aitekonbashonamestring[i]);
						if (torikumi_winkonbasho[i]==1){
							if (temp_taisensuu<(page_r_sibetu_tab+1)*15 && temp_taisensuu>=page_r_sibetu_tab*15){
								//簡易ビデオ表示用
								nowhyoji_sibetutab_year[gyousuu]=torikumi_year;
	 							nowhyoji_sibetutab_month[gyousuu]=torikumi_month;

								DrawFormatStringToHandle(rx1[gyousuu*2+10]-10,ry1[gyousuu*2+10],CRBLACK,FontHandle12,"%d年%s場所",
								torikumi_year,
								tanshuku_bashostring[(int)(torikumi_month/2)]);
								DrawStringToHandle(rx1[gyousuu*2+11],ry1[gyousuu*2+11],"●",GetColor(255,255,255),FontHandle12);
								DrawFormatStringToHandle(rx1[gyousuu*2+11],ry1[gyousuu*2+11],CRWHITE,FontHandle12,"　%s%2d",
								torikumi_kimaritekonbasho[i],torikumi_turncountkonbasho[i]);
								gyousuu++;
							}
							temp_taisensuu++;
							r_sibetu_wintotal++;
						}else if (torikumi_lostkonbasho[i]==1){
							if (temp_taisensuu<(page_r_sibetu_tab+1)*15 && temp_taisensuu>=page_r_sibetu_tab*15){
								//簡易ビデオ表示用
								nowhyoji_sibetutab_year[gyousuu]=torikumi_year;
	 							nowhyoji_sibetutab_month[gyousuu]=torikumi_month;

								DrawFormatStringToHandle(rx1[gyousuu*2+10]-10,ry1[gyousuu*2+10],CRBLACK,FontHandle12,"%d年%s場所",
								torikumi_year,
								tanshuku_bashostring[(int)(torikumi_month/2)]);
								DrawStringToHandle(rx1[gyousuu*2+11],ry1[gyousuu*2+11],"●",CRBLACK,FontHandle12);
								DrawFormatStringToHandle(rx1[gyousuu*2+11],ry1[gyousuu*2+11],CRBLACK,FontHandle12,"●%s%2d",
								torikumi_kimaritekonbasho[i],torikumi_turncountkonbasho[i]);
								gyousuu++;
							}
							temp_taisensuu++;
							r_sibetu_losttotal++;
						}
					}
				}
			}
		}
		fclose(fp);
		//簡易ビデオ
		strcpy(nowhyoji_sibetutab_namestring,temp_namestring);
		strcpy(nowhyoji_sibetutab_namestring2,r_sibetu_namestring);
		nowhyoji_sibetutab_ID=temp_rikisiid;
		nowhyoji_sibetutab_ID2=r_sibetu_rikisiid;

		DrawStringToHandle(rx1[2]-8,ry1[2],"対",CRBLACK,FontHandle12);
		DrawFormatStringToHandle(rx1[2]+8,ry1[2],CRBLACK,FontHandle12,"%s",
		r_sibetu_namestring);
		DrawFormatStringToHandle(rx1[4]+8,ry1[4],CRBLACK,FontHandle12,"ID:%d",
		r_sibetu_rikisiid);
		DrawFormatStringToHandle(rx1[6]-8,ry1[6],CRBLACK,FontHandle12,"通算%3d勝%3d負",
		r_sibetu_wintotal,
		r_sibetu_losttotal);
		DrawFormatStringToHandle(rx1[5]+30,ry1[5]+3,CRWHITE,FontHandle12,"%2d/%d頁",
		page_r_sibetu_tab+1,
		(int)(temp_taisensuu/15)+1
		);
		DrawStringToHandle(rx1[8],ry1[8],"IDで検索",CRGREEN,FontHandle12);
		DrawStringToHandle(rx1[6]-8,460,"決まり手を右クリックで概要",CRWHITE,FontHandle12);
	}
/////////////////////////////////////////////////////////
///////////////////////////////////////////
////////////////////記録タブ分表示///////////////
	if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5
	&& r_torikumi_or_seisekiflag==3){//右成績タブ


			////////////////年寄編集襲名者を引退力士から選ぶ画面用グローバル変数/////////////////////
			//Aカテ要件
			if (r_rikisidata[0].jikosaiko_bandukenameid<=A_saikoui || temp_sanyakuijouzaiisuu>=A_sanyakuzaiisuu || temp_makuutiijouzaiisuu>=A_makuutizaiisuu){
				if (r_rikisidata[0].jikosaiko_bandukenameid==0){
					G_category=5;
				}else if (r_rikisidata[0].jikosaiko_bandukenameid==1){
					G_category=6;
				}else{
					G_category=1;
				}
			//Bカテ要件
			}else if (r_rikisidata[0].jikosaiko_bandukenameid<=B_saikoui || temp_makuutiijouzaiisuu>=B_makuutizaiisuu || temp_juuryouijouzaiisuu>=B_jyuuryouzaiisuu){
				G_category=2;
			//Cカテ要件
			}else if (temp_makuutiijouzaiisuu>=C_makuutizaiisuu || temp_juuryouijouzaiisuu>=C_jyuuryouzaiisuu){
				G_category=3;
			}else{
				G_category=0;
			}


			//Aカテ要件
			if (r_rikisidata[0].jikosaiko_bandukenameid<=A_saikoui || temp_sanyakuijouzaiisuu>=A_sanyakuzaiisuu || temp_makuutiijouzaiisuu>=A_makuutizaiisuu){
				DrawStringToHandle(rx1[2],ry1[2]+2,"年寄襲名要件 Ａ達成",CRBLACK,FontHandle12);
			//Bカテ要件
			}else if (r_rikisidata[0].jikosaiko_bandukenameid<=B_saikoui || temp_makuutiijouzaiisuu>=B_makuutizaiisuu || temp_juuryouijouzaiisuu>=B_jyuuryouzaiisuu){
				DrawStringToHandle(rx1[2],ry1[2]+2,"年寄襲名要件 Ｂ達成",CRBLACK,FontHandle12);
			//Cカテ要件
			}else if (temp_makuutiijouzaiisuu>=C_makuutizaiisuu || temp_juuryouijouzaiisuu>=C_jyuuryouzaiisuu){
				DrawStringToHandle(rx1[2],ry1[2]+2,"年寄襲名要件 Ｃ達成",CRBLACK,FontHandle12);
			}else{
				//DrawStringToHandle(rx1[2],ry1[2]+2,"ランク －",CRBLACK,FontHandle12);
			}

			DrawStringToHandle(rx1[4],ry1[4],"幕内最高優勝",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[5],ry1[5],CRBLACK,FontHandle12,"%6d回",r_rikisidata[0].kiroku_yuushoukaisuu);
			DrawStringToHandle(rx1[6],ry1[6],"初土俵",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[7],ry1[7],CRBLACK,FontHandle12,"%d年%d月",r_rikisidata[0].hatudohyo_year,r_rikisidata[0].hatudohyo_month);
			DrawStringToHandle(rx1[8],ry1[8],"三役以上在位",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[9],ry1[9],CRBLACK,FontHandle12,"%6d場所",temp_sanyakuijouzaiisuu);
			DrawStringToHandle(rx1[10],ry1[10],"幕内以上在位",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[11],ry1[11],CRBLACK,FontHandle12,"%6d場所",temp_makuutiijouzaiisuu);
			DrawStringToHandle(rx1[12],ry1[12],"十両以上在位",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[13],ry1[13],CRBLACK,FontHandle12,"%6d場所",temp_juuryouijouzaiisuu);
			DrawStringToHandle(rx1[14],ry1[14],"幕内勝ち星数",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[15],ry1[15],CRBLACK,FontHandle12,"%6d勝",r_rikisidata[0].makuuti_win);
			DrawStringToHandle(rx1[16],ry1[16],"金星数",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[17],ry1[17],CRBLACK,FontHandle12,"%6d個",r_rikisidata[0].kinbosisuu);
			DrawStringToHandle(rx1[18],ry1[18],"殊勲賞受賞回数",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[19],ry1[19],CRBLACK,FontHandle12,"%6d回",r_rikisidata[0].shukunshousuu);
			DrawStringToHandle(rx1[20],ry1[20],"敢闘賞受賞回数",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[21],ry1[21],CRBLACK,FontHandle12,"%6d回",r_rikisidata[0].kantoushousuu);
			DrawStringToHandle(rx1[22],ry1[22],"技能賞受賞回数",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[23],ry1[23],CRBLACK,FontHandle12,"%6d回",r_rikisidata[0].ginoushousuu);
			DrawStringToHandle(rx1[24],ry1[24],"最高位",CRBLACK,FontHandle12);
			if (r_rikisidata[0].jikosaiko_bandukesuuji>1 ){
				DrawFormatStringToHandle(rx1[25],ry1[25],CRBLACK,FontHandle12,"%s%d枚目",
				bandukenamestring[r_rikisidata[0].jikosaiko_bandukenameid],
				r_rikisidata[0].jikosaiko_bandukesuuji
				);
			}else if (r_rikisidata[0].jikosaiko_bandukesuuji==1 ){
				DrawFormatStringToHandle(rx1[25],ry1[25],CRBLACK,FontHandle12,"%s筆頭",
				bandukenamestring[r_rikisidata[0].jikosaiko_bandukenameid]
				);
			}else{
				DrawFormatStringToHandle(rx1[25],ry1[25],CRBLACK,FontHandle12,"%s",
				bandukenamestring[r_rikisidata[0].jikosaiko_bandukenameid]
				);
			}
			DrawStringToHandle(rx1[26],ry1[26],"通算出場回数",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[27],ry1[27],CRBLACK,FontHandle12,"%6d回",r_rikisidata[0].wintotal+r_rikisidata[0].losttotal);
			DrawStringToHandle(rx1[28],ry1[28],"通算勝ち星数",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[29],ry1[29],CRBLACK,FontHandle12,"%6d勝",r_rikisidata[0].wintotal);
			DrawStringToHandle(rx1[30],ry1[30],"最多連勝",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[31],ry1[31],CRBLACK,FontHandle12,"%6d連勝",r_rikisidata[0].kiroku_renshou);
			DrawStringToHandle(rx1[32],ry1[32],"最多連敗",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[33],ry1[33],CRBLACK,FontHandle12,"%6d連敗",r_rikisidata[0].kiroku_renpai);
			DrawStringToHandle(rx1[34],ry1[34],"ガチ杯最高",CRBLACK,FontHandle12);
			if (r_rikisidata[0].jikosaiko_tournament==0){
				DrawStringToHandle(rx1[35],ry1[35],"未出場",CRBLACK,FontHandle12);
			}else if (r_rikisidata[0].jikosaiko_tournament<=6){
				DrawFormatStringToHandle(rx1[35],ry1[35],CRBLACK,FontHandle12,"%2d回戦進出",r_rikisidata[0].jikosaiko_tournament);
			}else if(r_rikisidata[0].jikosaiko_tournament==7){
				DrawStringToHandle(rx1[35],ry1[35],"準々決勝進出",CRBLACK,FontHandle12);
			}else if(r_rikisidata[0].jikosaiko_tournament==8){
				DrawStringToHandle(rx1[35],ry1[35],"準決勝進出",CRBLACK,FontHandle12);
			}else if(r_rikisidata[0].jikosaiko_tournament==9){
				DrawStringToHandle(rx1[35],ry1[35],"決勝進出",CRBLACK,FontHandle12);
			}else{
				DrawFormatStringToHandle(rx1[35],ry1[35],CRBLACK,FontHandle12,"優勝%2d回",r_rikisidata[0].yuushoukaisuu_tournament);
			}
	}
//////////////////////////////////////////////////
/////////////決手タブ表示////////////////////////
	if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5
	&& r_torikumi_or_seisekiflag==4){//右成績タブ
			DrawStringToHandle(rx1[4],ry1[4],"突き出し",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[5],ry1[5],CRBLACK,FontHandle12,"%3d％",r_rikisidata[0].wazaritu_tukidasi);
			DrawFormatStringToHandle(rx1[5]+45,ry1[5],CRBLACK,FontHandle12,"%4d",r_rikisidata[0].wazaritu_tukidasisuu);
			DrawStringToHandle(rx1[6],ry1[6],"寄り切り",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[7],ry1[7],CRBLACK,FontHandle12,"%3d％",r_rikisidata[0].wazaritu_yorikiri);
			DrawFormatStringToHandle(rx1[7]+45,ry1[7],CRBLACK,FontHandle12,"%4d",r_rikisidata[0].wazaritu_yorikirisuu);
			DrawStringToHandle(rx1[8],ry1[8],"右上手投",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[9],ry1[9],CRBLACK,FontHandle12,"%3d％",r_rikisidata[0].wazaritu_migiuwatenage);
			DrawFormatStringToHandle(rx1[9]+45,ry1[9],CRBLACK,FontHandle12,"%4d",r_rikisidata[0].wazaritu_migiuwatenagesuu);
			DrawStringToHandle(rx1[10],ry1[10],"左上手投",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[11],ry1[11],CRBLACK,FontHandle12,"%3d％",r_rikisidata[0].wazaritu_hidariuwatenage);
			DrawFormatStringToHandle(rx1[11]+45,ry1[11],CRBLACK,FontHandle12,"%4d",r_rikisidata[0].wazaritu_hidariuwatenagesuu);
			DrawStringToHandle(rx1[12],ry1[12],"右下手投",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[13],ry1[13],CRBLACK,FontHandle12,"%3d％",r_rikisidata[0].wazaritu_migisitatenage);
			DrawFormatStringToHandle(rx1[13]+45,ry1[13],CRBLACK,FontHandle12,"%4d",r_rikisidata[0].wazaritu_migisitatenagesuu);
			DrawStringToHandle(rx1[14],ry1[14],"左下手投",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[15],ry1[15],CRBLACK,FontHandle12,"%3d％",r_rikisidata[0].wazaritu_hidarisitatenage);
			DrawFormatStringToHandle(rx1[15]+45,ry1[15],CRBLACK,FontHandle12,"%4d",r_rikisidata[0].wazaritu_hidarisitatenagesuu);
			DrawStringToHandle(rx1[16],ry1[16],"右小手投",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[17],ry1[17],CRBLACK,FontHandle12,"%3d％",r_rikisidata[0].wazaritu_migikotenage);
			DrawFormatStringToHandle(rx1[17]+45,ry1[17],CRBLACK,FontHandle12,"%4d",r_rikisidata[0].wazaritu_migikotenagesuu);
			DrawStringToHandle(rx1[18],ry1[18],"左小手投",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[19],ry1[19],CRBLACK,FontHandle12,"%3d％",r_rikisidata[0].wazaritu_hidarikotenage);
			DrawFormatStringToHandle(rx1[19]+45,ry1[19],CRBLACK,FontHandle12,"%4d",r_rikisidata[0].wazaritu_hidarikotenagesuu);
			DrawStringToHandle(rx1[20],ry1[20],"右掬い投",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[21],ry1[21],CRBLACK,FontHandle12,"%3d％",r_rikisidata[0].wazaritu_migisukuinage);
			DrawFormatStringToHandle(rx1[21]+45,ry1[21],CRBLACK,FontHandle12,"%4d",r_rikisidata[0].wazaritu_migisukuinagesuu);
			DrawStringToHandle(rx1[22],ry1[22],"左掬い投",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[23],ry1[23],CRBLACK,FontHandle12,"%3d％",r_rikisidata[0].wazaritu_hidarisukuinage);
			DrawFormatStringToHandle(rx1[23]+45,ry1[23],CRBLACK,FontHandle12,"%4d",r_rikisidata[0].wazaritu_hidarisukuinagesuu);
			DrawStringToHandle(rx1[24],ry1[24],"その他　",CRBLACK,FontHandle12);
			DrawFormatStringToHandle(rx1[25],ry1[25],CRBLACK,FontHandle12,"%3d％",r_rikisidata[0].wazaritu_sonota);
			DrawFormatStringToHandle(rx1[25]+45,ry1[25],CRBLACK,FontHandle12,"%4d",r_rikisidata[0].wazaritu_sonotasuu);
	}
	/////////////////////////////////////////
}//左リスト表示数0の時のエラー回避if文閉じ括弧
//////////////////////////////////////////////////////////

	draw_buttonkensakuLEFT();
	if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5
	&& r_torikumi_or_seisekiflag<=2){//右タブが取組か成績か士別
		draw_buttonUPFAST();
		draw_buttonDOWNFAST();
	}
	draw_buttonUP();
	draw_buttonDOWN();

	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//SetFontSize( 16 ) ;
	//if( ProcessMessage() == -1 ){mode=1;return ;}


	DrawString(x2[0]-16,y1[0]-70,"戻る",CRGREEN);

//	ScreenFlip();
	

	return;
}


void retirerikisi_new(int hyojiheyaid)
{
	long moto_ichijouhou=0;
	int kensakukekka_kakotorikumi=0;
	int n=0;
	long sumifilesize_retire=0;
	long sumifilesize_retire_saikoui=0;
	long sumifilesize_retire_jiheya=0;
	int renban_retire=0;
	int renban_retire_jiheya=0;
	int renban_retire_saikoui=0;
	long sumifilesize=0;
	long ichijouhou=0;
	long ichijouhou_jiheya=0;
	long ichijouhou_saikoui=0;
	long temp_ichijouhou=0;
	long temp_size;
	int i,ii,iii,count,temp_suu;
	int yokodunasuu=0,yokodunasuu_wsumi=0;
	int oozekisuu=0,oozekisuu_wsumi=0;
	int sekiwakesuu=0,sekiwakesuu_wsumi=0;
	int komusubisuu=0,komusubisuu_wsumi=0;
	int juuryousuu[20];
	int juuryousuu_wsumi[20];
	int maegasirasuu2=0;
	int maegasirasuu[20];
	int maegasirasuu_wsumi[20];
	char temp_filename[MAX_PATH];
	char defdir[MAX_PATH];

	if (mode==0){
		menuflag=1;
		return;
	}

	//しばらくお待ちください表示
	ClearDrawScreen();
	DrawString(100,300,"表示準備中です",CRWHITE);
	DrawString(100,350,"しばらくお待ちください",CRWHITE);
	ScreenFlip();

	pagenomihenkouflag_r_mainsibetu=0;

	for (i=0;i<MAX_PATH;i++){
		temp_filename[i]=0;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (i=0;i<20;i++){
		for (ii=0;ii<12;ii++){
			temp_list_namestring[i][ii]=0;
		}
		maegasirasuu[i]=0;
		maegasirasuu_wsumi[i]=0;
		juuryousuu[i]=0;
		juuryousuu_wsumi[i]=0;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (i=0;i<12;i++){
		temp_namestring[i]=0;
		temp_heyastring[i]=0;
	}
	for (i=0;i<28;i++){
		temp_hometownstring[i]=0;
	}
	

	if (mode==0){
		menuflag=1;
		return;
	}

	if (retiresuu_total<1){
		ClearDrawScreen();
		DrawBox(0,0,639,479,CRBACK,TRUE);
		DrawString(0,0,"該当力士は一人もいません。",CRWHITE);
		DrawString(270,220,"Hit any key",CRWHITE);
		ScreenFlip();
		WaitKey();
		return;
	}
	
	for (i=0;i<RETIREMAXFILESUU;i++){
		filesize_retire[i]=0;
		filesize_retire_jiheya[i]=0;
		filesize_retire_saikoui[i]=0;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

	for (i=0;i<180;i++){
		temp_kako_yuushouflag[i]=0;
		temp_kako_bandukehigasiornisi[i]=0;
		temp_kako_bandukenameid[i]=0;
		temp_kako_bandukesuuji[i]=0;
		temp_kako_win[i]=0;
		temp_kako_lost[i]=0;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

	retire_sentaku_category=2;
	page_r_sibetu_main=0;

	temp_size=
		sizeof(rikisidata[0].rikisiid)+
		sizeof(namestring[rikisidata[0].nameid])+
		sizeof(hometownstring[rikisidata[0].hometownid])+
		sizeof(heyastring[rikisidata[0].heyaid])+
		sizeof(rikisidata[0].heyaid)+
		sizeof(rikisidata[0].hatudohyo_year)+
		sizeof(rikisidata[0].hatudohyo_month)+
		sizeof(year)+
		sizeof(month)+
		sizeof(rikisidata[0].jikosaiko_bandukenameid)+
		sizeof(rikisidata[0].jikosaiko_bandukesuuji)+
		sizeof(rikisidata[0].makuuti_win)+
		sizeof(rikisidata[0].makuuti_lost)+
		sizeof(rikisidata[0].kiroku_yuushoukaisuu)+
		sizeof(rikisidata[0].kinbosisuu)+
		sizeof(rikisidata[0].shukunshousuu)+
		sizeof(rikisidata[0].kantoushousuu)+
		sizeof(rikisidata[0].ginoushousuu)+
		sizeof(rikisidata[0].wintotal)+
		sizeof(rikisidata[0].losttotal)+
		sizeof(rikisidata[0].kiroku_renshou)+
		sizeof(rikisidata[0].kiroku_renpai)+
		sizeof(rikisidata[0].kako_yuushouflag)+
		sizeof(rikisidata[0].kako_bandukehigasiornisi)+
		sizeof(rikisidata[0].kako_bandukenameid)+
		sizeof(rikisidata[0].kako_bandukesuuji)+
		sizeof(rikisidata[0].kako_win)+
		sizeof(rikisidata[0].kako_lost)+
		sizeof(rikisidata[0].jikosaiko_tournament)+
		sizeof(rikisidata[0].yuushoukaisuu_tournament)+
		sizeof(rikisidata[0].age);

	ichijouhou=(retiresuu_total-1)*temp_size;
	ichijouhou_jiheya=0;
	ichijouhou_saikoui=0;

	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//各連番ファイルのサイズ取得
	for (i=0;i<RETIREMAXFILESUU;i++){
		if (i==0){
			strcpy(temp_filename,"data/dat/retirerikisi.dat\0");
			filesize_retire[i]=Getfilesize(temp_filename);
		}else{
			sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",i+1);
			filesize_retire[i]=Getfilesize(temp_filename);
			if (filesize_retire[i]<0) break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	FILE *fp;
	FILE *fp_w;

	//自部屋順用参照ファイル作成
		//自部屋順ファイル初期化
		fp_w = fopen("data/dat/retirerikisi_jiheya.dat","wb");
		if( fp_w == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawBox(0,0,639,479,CRBACK,TRUE);
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1;
			return ;
		}
		fclose(fp_w);
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (i=0;i<RETIREMAXFILESUU;i++){
			sprintf(temp_filename,"data/dat/retirerikisi_jiheya%d.dat\0",i+2);
			if (DeleteFile(temp_filename)==0){//失敗すなわち存在しなければ
				break;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}

	////////ここからループ////////////////////////
		ii=0;sumifilesize_retire=0;sumifilesize_retire_jiheya=0;
		renban_retire=0;
		renban_retire_jiheya=0;
		retiresuu_jiheya=0;
		for (i=0;i<retiresuu_total;i++){
			//引退順ファイル(読込)オープン
			if (renban_retire==0){
				if (filesize_retire[renban_retire]>=((i+1)*temp_size)){
					strcpy(temp_filename,"data/dat/retirerikisi.dat\0");
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
				}else{
					sumifilesize_retire+=filesize_retire[renban_retire];
					renban_retire++;
					if (filesize_retire[renban_retire]<=0) break;//あっちゃいけないけどね
					sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",renban_retire+1);
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
				}
			}else{
				if (filesize_retire[renban_retire] >= ( (i+1)*temp_size-sumifilesize_retire) ){
					sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",renban_retire+1);
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
				}else{
					sumifilesize_retire+=filesize_retire[renban_retire];
					renban_retire++;
					if (filesize_retire[renban_retire]<=0) break;//あっちゃいけないけどね
					sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",renban_retire+1);
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			//引退順ファイル位置情報
			temp_ichijouhou=i*temp_size-sumifilesize_retire;
			fseek( fp,temp_ichijouhou+sizeof(rikisidata[0].rikisiid)+sizeof(namestring[rikisidata[0].nameid])+sizeof(hometownstring[rikisidata[0].hometownid])+sizeof(heyastring[rikisidata[0].heyaid]),SEEK_SET );
			fread(&temp_heyaid,sizeof(rikisidata[0].heyaid),1,fp);
//			if (hyojiheyaid==-1 || temp_heyaid==hyojiheyaid){
			if (temp_heyaid==hyojiheyaid){
				//引退順ファイル読込
				fseek( fp,temp_ichijouhou,SEEK_SET );
				fread(&temp_rikisiid,sizeof(temp_rikisiid),1,fp);
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
				//自部屋引退ファイル(追記)オープン
				if (renban_retire_jiheya==0){
					if (maxfilesize>=((retiresuu_jiheya+1)*temp_size)){
						strcpy(temp_filename,"data/dat/retirerikisi_jiheya.dat\0");
						fp_w = fopen(temp_filename,"ab");
					}else{
						filesize_retire_jiheya[renban_retire_jiheya]=retiresuu_jiheya*temp_size;
						sumifilesize_retire_jiheya+=filesize_retire_jiheya[renban_retire_jiheya];
						renban_retire_jiheya++;
						sprintf(temp_filename,"data/dat/retirerikisi_jiheya%d.dat\0",renban_retire_jiheya+1);
						fp_w = fopen(temp_filename,"ab");
					}
				}else{
					if (maxfilesize >= ( (retiresuu_jiheya+1)*temp_size-sumifilesize_retire_jiheya) ){
						sprintf(temp_filename,"data/dat/retirerikisi_jiheya%d.dat\0",renban_retire_jiheya+1);
						fp_w = fopen(temp_filename,"ab");
					}else{
						filesize_retire_jiheya[renban_retire_jiheya]=retiresuu_jiheya*temp_size-sumifilesize_retire_jiheya;
						sumifilesize_retire_jiheya+=filesize_retire_jiheya[renban_retire_jiheya];
						renban_retire_jiheya++;
						sprintf(temp_filename,"data/dat/retirerikisi_jiheya%d.dat\0",renban_retire_jiheya+1);
						fp_w = fopen(temp_filename,"ab");
					}
				}
				//自部屋ファイル位置情報
				temp_ichijouhou=retiresuu_jiheya*temp_size-sumifilesize_retire_jiheya;
				fseek( fp_w,temp_ichijouhou,SEEK_SET );
				//自部屋ファイル書込
				fwrite(&temp_rikisiid,sizeof(temp_rikisiid),1,fp_w);
				fwrite(temp_namestring,sizeof(namestring[rikisidata[0].nameid]),1,fp_w);
				fwrite(temp_hometownstring,sizeof(hometownstring[rikisidata[0].hometownid]),1,fp_w);
				fwrite(temp_heyastring,sizeof(heyastring[rikisidata[0].heyaid]),1,fp_w);
				fwrite(&temp_heyaid,sizeof(rikisidata[0].heyaid),1,fp_w);
				fwrite(&temp_hatudohyo_year,sizeof(rikisidata[0].hatudohyo_year),1,fp_w);
				fwrite(&temp_hatudohyo_month,sizeof(rikisidata[0].hatudohyo_month),1,fp_w);
				fwrite(&temp_retire_year,sizeof(year),1,fp_w);
				fwrite(&temp_retire_month,sizeof(month),1,fp_w);
				fwrite(&temp_jikosaiko_bandukenameid,sizeof(rikisidata[0].jikosaiko_bandukenameid),1,fp_w);
				fwrite(&temp_jikosaiko_bandukesuuji,sizeof(rikisidata[0].jikosaiko_bandukesuuji),1,fp_w);
				fwrite(&temp_makuuti_win,sizeof(rikisidata[0].makuuti_win),1,fp_w);
				fwrite(&temp_makuuti_lost,sizeof(rikisidata[0].makuuti_lost),1,fp_w);
				fwrite(&temp_kiroku_yuushoukaisuu,sizeof(rikisidata[0].kiroku_yuushoukaisuu),1,fp_w);
				fwrite(&temp_kinbosisuu,sizeof(rikisidata[0].kinbosisuu),1,fp_w);
				fwrite(&temp_shukunshousuu,sizeof(rikisidata[0].shukunshousuu),1,fp_w);
				fwrite(&temp_kantoushousuu,sizeof(rikisidata[0].kantoushousuu),1,fp_w);
				fwrite(&temp_ginoushousuu,sizeof(rikisidata[0].ginoushousuu),1,fp_w);
				fwrite(&temp_wintotal,sizeof(rikisidata[0].wintotal),1,fp_w);
				fwrite(&temp_losttotal,sizeof(rikisidata[0].losttotal),1,fp_w);
				fwrite(&temp_kiroku_renshou,sizeof(rikisidata[0].kiroku_renshou),1,fp_w);
				fwrite(&temp_kiroku_renpai,sizeof(rikisidata[0].kiroku_renpai),1,fp_w);
				fwrite(temp_kako_yuushouflag,sizeof(rikisidata[0].kako_yuushouflag),1,fp_w);
				fwrite(temp_kako_bandukehigasiornisi,sizeof(rikisidata[0].kako_bandukehigasiornisi),1,fp_w);
				fwrite(temp_kako_bandukenameid,sizeof(rikisidata[0].kako_bandukenameid),1,fp_w);
				fwrite(temp_kako_bandukesuuji,sizeof(rikisidata[0].kako_bandukesuuji),1,fp_w);
				fwrite(temp_kako_win,sizeof(rikisidata[0].kako_win),1,fp_w);
				fwrite(temp_kako_lost,sizeof(rikisidata[0].kako_lost),1,fp_w);
				fwrite(&temp_jikosaiko_tournament,sizeof(rikisidata[0].jikosaiko_tournament),1,fp_w);
				fwrite(&temp_yuushoukaisuu_tournament,sizeof(rikisidata[0].yuushoukaisuu_tournament),1,fp_w);
				fwrite(&temp_age,sizeof(rikisidata[0].age),1,fp_w);
				//クローズ
				fclose(fp_w);
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				//カウント
				retiresuu_jiheya++;
			}
			//クローズ
			fclose(fp);
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}

	//最高位順用参照ファイル作成
		//最高位順ファイル初期化
		fp_w = fopen("data/dat/retirerikisi_saikoui.dat","wb");
		if( fp_w == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawBox(0,0,639,479,CRBACK,TRUE);
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1;
			return ;
		}
		fclose(fp_w);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (i=0;i<RETIREMAXFILESUU;i++){
			sprintf(temp_filename,"data/dat/retirerikisi_saikoui%d.dat\0",i+2);
			if (DeleteFile(temp_filename)==0){//失敗すなわち存在しなければ
				break;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		///ランダムアクセス用のダミーファイルを作成するための横綱数とかをカウントするため用のファイルオープン
		//retiresuu_totalまで一人一人横綱数から前頭数までカウント→無理やり十両まで
		ii=0;sumifilesize_retire=0;
		renban_retire=0;
		retiresuu_saikoui=0;
		for (i=0;i<retiresuu_total;i++){
			//引退順ファイル(読込)オープン
			if (renban_retire==0){
				if (filesize_retire[renban_retire]>=((i+1)*temp_size)){
					strcpy(temp_filename,"data/dat/retirerikisi.dat\0");
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
				}else{
					sumifilesize_retire+=filesize_retire[renban_retire];
					renban_retire++;
					if (filesize_retire[renban_retire]<=0) break;//あっちゃいけないけどね
					sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",renban_retire+1);
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
				}
			}else{
				if (filesize_retire[renban_retire] >= ( (i+1)*temp_size-sumifilesize_retire) ){
					sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",renban_retire+1);
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
				}else{
					sumifilesize_retire+=filesize_retire[renban_retire];
					renban_retire++;
					if (filesize_retire[renban_retire]<=0) break;//あっちゃいけないけどね
					sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",renban_retire+1);
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
				}
			}
			//引退順ファイル位置情報
			temp_ichijouhou=i*temp_size-sumifilesize_retire;
			fseek( fp,temp_ichijouhou+sizeof(rikisidata[0].rikisiid)+sizeof(namestring[rikisidata[0].nameid])+sizeof(hometownstring[rikisidata[0].hometownid])+sizeof(heyastring[rikisidata[0].heyaid]),SEEK_SET );
			fread(&temp_heyaid,sizeof(rikisidata[0].heyaid),1,fp);
			if (hyojiheyaid==-1 || temp_heyaid==hyojiheyaid){

				fseek( fp,temp_ichijouhou,SEEK_SET );
				//読み込み
				fread(&temp_rikisiid,sizeof(temp_rikisiid),1,fp);
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
				if (temp_jikosaiko_bandukenameid==0){//横綱
					retiresuu_saikoui++;
					yokodunasuu++;
				}
				if (temp_jikosaiko_bandukenameid==1){//大関
					retiresuu_saikoui++;
					oozekisuu++;
				}
				if (temp_jikosaiko_bandukenameid==2){//関脇
					retiresuu_saikoui++;
					sekiwakesuu++;
				}
				if (temp_jikosaiko_bandukenameid==3){//小結
					retiresuu_saikoui++;
					komusubisuu++;
				}
				if (temp_jikosaiko_bandukenameid==4){//前頭
					retiresuu_saikoui++;
					for (ii=1;ii<20;ii++){
						if (temp_jikosaiko_bandukesuuji==ii){
							maegasirasuu[ii]++;
							maegasirasuu2++;
						}
					}
				}
				if (temp_jikosaiko_bandukenameid==5){//十両
					retiresuu_saikoui++;
					for (ii=1;ii<20;ii++){
						if (temp_jikosaiko_bandukesuuji==ii){
							juuryousuu[ii]++;
						}
					}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			fclose(fp);
		}
		//最高位順ファイルをランダムアクセスに備えいったんダミーとして作成
		ii=0;sumifilesize_retire_saikoui=0;
		renban_retire_saikoui=0;
		for (i=0;i<retiresuu_saikoui;i++){
			//最高位順ファイルオープン
			if (renban_retire_saikoui==0){
				if (maxfilesize>=((i+1)*temp_size)){
					strcpy(temp_filename,"data/dat/retirerikisi_saikoui.dat\0");
					fp_w = fopen(temp_filename,"ab");
				}else{
					filesize_retire_saikoui[renban_retire_saikoui]=retiresuu_saikoui*temp_size;
					sumifilesize_retire_saikoui=i*temp_size;
					renban_retire_saikoui++;
					sprintf(temp_filename,"data/dat/retirerikisi_saikoui%d.dat\0",renban_retire_saikoui+1);
					fp_w = fopen(temp_filename,"ab");
				}
			}else{
				if (maxfilesize >= ( (i+1)*temp_size-sumifilesize_retire_saikoui) ){
					sprintf(temp_filename,"data/dat/retirerikisi_saikoui%d.dat\0",renban_retire_saikoui+1);
					fp_w = fopen(temp_filename,"ab");
				}else{
					filesize_retire_saikoui[renban_retire_saikoui]=retiresuu_saikoui*temp_size-sumifilesize_retire_saikoui;
					sumifilesize_retire_saikoui=i*temp_size;
					renban_retire_saikoui++;
					sprintf(temp_filename,"data/dat/retirerikisi_saikoui%d.dat\0",renban_retire_saikoui+1);
					fp_w = fopen(temp_filename,"ab");
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			//最高位ファイル位置情報
			temp_ichijouhou=i*temp_size-sumifilesize_retire_saikoui;
			fseek( fp_w,temp_ichijouhou,SEEK_SET );
			fwrite(&temp_rikisiid,sizeof(temp_rikisiid),1,fp_w);
			fwrite(temp_namestring,sizeof(namestring[rikisidata[0].nameid]),1,fp_w);
			fwrite(temp_hometownstring,sizeof(hometownstring[rikisidata[0].hometownid]),1,fp_w);
			fwrite(temp_heyastring,sizeof(heyastring[rikisidata[0].heyaid]),1,fp_w);
			fwrite(&temp_heyaid,sizeof(rikisidata[0].heyaid),1,fp_w);
			fwrite(&temp_hatudohyo_year,sizeof(rikisidata[0].hatudohyo_year),1,fp_w);
			fwrite(&temp_hatudohyo_month,sizeof(rikisidata[0].hatudohyo_month),1,fp_w);
			fwrite(&temp_retire_year,sizeof(year),1,fp_w);
			fwrite(&temp_retire_month,sizeof(month),1,fp_w);
			fwrite(&temp_jikosaiko_bandukenameid,sizeof(rikisidata[0].jikosaiko_bandukenameid),1,fp_w);
			fwrite(&temp_jikosaiko_bandukesuuji,sizeof(rikisidata[0].jikosaiko_bandukesuuji),1,fp_w);
			fwrite(&temp_makuuti_win,sizeof(rikisidata[0].makuuti_win),1,fp_w);
			fwrite(&temp_makuuti_lost,sizeof(rikisidata[0].makuuti_lost),1,fp_w);
			fwrite(&temp_kiroku_yuushoukaisuu,sizeof(rikisidata[0].kiroku_yuushoukaisuu),1,fp_w);
			fwrite(&temp_kinbosisuu,sizeof(rikisidata[0].kinbosisuu),1,fp_w);
			fwrite(&temp_shukunshousuu,sizeof(rikisidata[0].shukunshousuu),1,fp_w);
			fwrite(&temp_kantoushousuu,sizeof(rikisidata[0].kantoushousuu),1,fp_w);
			fwrite(&temp_ginoushousuu,sizeof(rikisidata[0].ginoushousuu),1,fp_w);
			fwrite(&temp_wintotal,sizeof(rikisidata[0].wintotal),1,fp_w);
			fwrite(&temp_losttotal,sizeof(rikisidata[0].losttotal),1,fp_w);
			fwrite(&temp_kiroku_renshou,sizeof(rikisidata[0].kiroku_renshou),1,fp_w);
			fwrite(&temp_kiroku_renpai,sizeof(rikisidata[0].kiroku_renpai),1,fp_w);
			fwrite(temp_kako_yuushouflag,sizeof(rikisidata[0].kako_yuushouflag),1,fp_w);
			fwrite(temp_kako_bandukehigasiornisi,sizeof(rikisidata[0].kako_bandukehigasiornisi),1,fp_w);
			fwrite(temp_kako_bandukenameid,sizeof(rikisidata[0].kako_bandukenameid),1,fp_w);
			fwrite(temp_kako_bandukesuuji,sizeof(rikisidata[0].kako_bandukesuuji),1,fp_w);
			fwrite(temp_kako_win,sizeof(rikisidata[0].kako_win),1,fp_w);
			fwrite(temp_kako_lost,sizeof(rikisidata[0].kako_lost),1,fp_w);
			fwrite(&temp_jikosaiko_tournament,sizeof(rikisidata[0].jikosaiko_tournament),1,fp_w);
			fwrite(&temp_yuushoukaisuu_tournament,sizeof(rikisidata[0].yuushoukaisuu_tournament),1,fp_w);
			fwrite(&temp_age,sizeof(rikisidata[0].age),1,fp_w);
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			fclose(fp_w);
		}
		//最高位順連番ファイルのサイズ取得
		for (ii=0;ii<RETIREMAXFILESUU;ii++){
			if (ii==0){
				strcpy(temp_filename,"data/dat/retirerikisi_saikoui.dat\0");
				filesize_retire_saikoui[ii]=Getfilesize(temp_filename);
			}else{
				sprintf(temp_filename,"data/dat/retirerikisi_saikoui%d.dat\0",ii+1);
				filesize_retire_saikoui[ii]=Getfilesize(temp_filename);
				if (filesize_retire_saikoui[ii]<0) break;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}

		//引退順ファイルを先頭から読み、前頭以上であれば最高位順ファイルにランダムアクセスで書込み
		ii=0;sumifilesize_retire=0;sumifilesize_retire_saikoui=0;
		renban_retire=0;renban_retire_saikoui=0;
		for (i=0;i<retiresuu_total;i++){
			//引退順ファイル(読込)オープン
			if (renban_retire==0){
				if (filesize_retire[renban_retire]>=((i+1)*temp_size)){
					strcpy(temp_filename,"data/dat/retirerikisi.dat\0");
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
				}else{
					sumifilesize_retire+=filesize_retire[renban_retire];
					renban_retire++;
					if (filesize_retire[renban_retire]<=0) break;//あっちゃいけないけどね
					sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",renban_retire+1);
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
				}
			}else{
				if (filesize_retire[renban_retire] >= ( (i+1)*temp_size-sumifilesize_retire) ){
					sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",renban_retire+1);
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
				}else{
					sumifilesize_retire+=filesize_retire[renban_retire];
					renban_retire++;
					if (filesize_retire[renban_retire]<=0) break;//あっちゃいけないけどね
					sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",renban_retire+1);
					fp = fopen(temp_filename,"rb");
					if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return ;}
				}
			}
			//引退順ファイル位置情報
			temp_ichijouhou=i*temp_size-sumifilesize_retire;
			fseek( fp,temp_ichijouhou+sizeof(rikisidata[0].rikisiid)+sizeof(namestring[rikisidata[0].nameid])+sizeof(hometownstring[rikisidata[0].hometownid])+sizeof(heyastring[rikisidata[0].heyaid]),SEEK_SET );
			fread(&temp_heyaid,sizeof(rikisidata[0].heyaid),1,fp);
			fseek( fp,temp_ichijouhou+sizeof(rikisidata[0].rikisiid)+sizeof(namestring[rikisidata[0].nameid])+sizeof(hometownstring[rikisidata[0].hometownid])+sizeof(heyastring[rikisidata[0].heyaid])+sizeof(rikisidata[0].heyaid)+sizeof(rikisidata[0].hatudohyo_year)+sizeof(rikisidata[0].hatudohyo_month)+sizeof(year)+sizeof(month),SEEK_SET );
			fread(&temp_jikosaiko_bandukenameid,sizeof(rikisidata[0].jikosaiko_bandukenameid),1,fp);
			fread(&temp_jikosaiko_bandukesuuji,sizeof(rikisidata[0].jikosaiko_bandukesuuji),1,fp);
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (temp_jikosaiko_bandukenameid<6 && (temp_heyaid==hyojiheyaid || hyojiheyaid==-1)){//無理やり5を6にした
				//引退順ファイル読込
				fseek( fp,temp_ichijouhou,SEEK_SET );
				fread(&temp_rikisiid,sizeof(temp_rikisiid),1,fp);
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
				//最高位順ファイル書込の前に基本位置情報取得
				if (temp_jikosaiko_bandukenameid==0){
					temp_ichijouhou=yokodunasuu_wsumi*temp_size;
					yokodunasuu_wsumi++;
				}
				if (temp_jikosaiko_bandukenameid==1){
					temp_ichijouhou=(yokodunasuu+oozekisuu_wsumi)*temp_size;
					oozekisuu_wsumi++;
				}
				if (temp_jikosaiko_bandukenameid==2){
					temp_ichijouhou=(yokodunasuu+oozekisuu+sekiwakesuu_wsumi)*temp_size;
					sekiwakesuu_wsumi++;
				}
				if (temp_jikosaiko_bandukenameid==3){
					temp_ichijouhou=(yokodunasuu+oozekisuu+sekiwakesuu+komusubisuu_wsumi)*temp_size;
					komusubisuu_wsumi++;
				}
				if (temp_jikosaiko_bandukenameid==4){
					temp_suu=0;
					for (ii=1;ii<20;ii++){
						if (temp_jikosaiko_bandukesuuji==ii){
							for (iii=1;iii<ii;iii++){
								temp_suu+=maegasirasuu[iii];
							}
							temp_suu+=maegasirasuu_wsumi[ii];
							maegasirasuu_wsumi[ii]++;
						}
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					}
					temp_ichijouhou=(yokodunasuu+oozekisuu+sekiwakesuu+komusubisuu+temp_suu)*temp_size;
				}
				if (temp_jikosaiko_bandukenameid==5){
					temp_suu=0;
					for (ii=1;ii<20;ii++){
						if (temp_jikosaiko_bandukesuuji==ii){
							for (iii=1;iii<ii;iii++){
								temp_suu+=juuryousuu[iii];
							}
							temp_suu+=juuryousuu_wsumi[ii];
							juuryousuu_wsumi[ii]++;
						}
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					}
					temp_ichijouhou=(yokodunasuu+oozekisuu+sekiwakesuu+komusubisuu+maegasirasuu2+temp_suu)*temp_size;
				}
				//temp_ichijouhou補正＋ファイルオープン
				sumifilesize_retire_saikoui=0;
				for (ii=0;ii<RETIREMAXFILESUU;ii++){
					if (ii==0){
						if (filesize_retire_saikoui[ii]>=temp_ichijouhou+temp_size){
							strcpy(temp_filename,"data/dat/retirerikisi_saikoui.dat\0");
							fp_w = fopen(temp_filename,"rb+");
							break;
						}else{
							sumifilesize_retire_saikoui+=filesize_retire_saikoui[ii];
						}
					}else{
						if (filesize_retire_saikoui[ii]>=temp_ichijouhou+temp_size-sumifilesize_retire_saikoui){
							sprintf(temp_filename,"data/dat/retirerikisi_saikoui%d.dat\0",ii+1);
							fp_w = fopen(temp_filename,"rb+");
							break;
						}else{
							sumifilesize_retire_saikoui+=filesize_retire_saikoui[ii];
						}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				temp_ichijouhou-=sumifilesize_retire_saikoui;
			
				//位置設定
				fseek(fp_w,temp_ichijouhou,SEEK_SET );
				//最高位順ファイル書込み
				fwrite(&temp_rikisiid,sizeof(temp_rikisiid),1,fp_w);
				fwrite(temp_namestring,sizeof(namestring[rikisidata[0].nameid]),1,fp_w);
				fwrite(temp_hometownstring,sizeof(hometownstring[rikisidata[0].hometownid]),1,fp_w);
				fwrite(temp_heyastring,sizeof(heyastring[rikisidata[0].heyaid]),1,fp_w);
				fwrite(&temp_heyaid,sizeof(rikisidata[0].heyaid),1,fp_w);
				fwrite(&temp_hatudohyo_year,sizeof(rikisidata[0].hatudohyo_year),1,fp_w);
				fwrite(&temp_hatudohyo_month,sizeof(rikisidata[0].hatudohyo_month),1,fp_w);
				fwrite(&temp_retire_year,sizeof(year),1,fp_w);
				fwrite(&temp_retire_month,sizeof(month),1,fp_w);
				fwrite(&temp_jikosaiko_bandukenameid,sizeof(rikisidata[0].jikosaiko_bandukenameid),1,fp_w);
				fwrite(&temp_jikosaiko_bandukesuuji,sizeof(rikisidata[0].jikosaiko_bandukesuuji),1,fp_w);
				fwrite(&temp_makuuti_win,sizeof(rikisidata[0].makuuti_win),1,fp_w);
				fwrite(&temp_makuuti_lost,sizeof(rikisidata[0].makuuti_lost),1,fp_w);
				fwrite(&temp_kiroku_yuushoukaisuu,sizeof(rikisidata[0].kiroku_yuushoukaisuu),1,fp_w);
				fwrite(&temp_kinbosisuu,sizeof(rikisidata[0].kinbosisuu),1,fp_w);
				fwrite(&temp_shukunshousuu,sizeof(rikisidata[0].shukunshousuu),1,fp_w);
				fwrite(&temp_kantoushousuu,sizeof(rikisidata[0].kantoushousuu),1,fp_w);
				fwrite(&temp_ginoushousuu,sizeof(rikisidata[0].ginoushousuu),1,fp_w);
				fwrite(&temp_wintotal,sizeof(rikisidata[0].wintotal),1,fp_w);
				fwrite(&temp_losttotal,sizeof(rikisidata[0].losttotal),1,fp_w);
				fwrite(&temp_kiroku_renshou,sizeof(rikisidata[0].kiroku_renshou),1,fp_w);
				fwrite(&temp_kiroku_renpai,sizeof(rikisidata[0].kiroku_renpai),1,fp_w);
				fwrite(temp_kako_yuushouflag,sizeof(rikisidata[0].kako_yuushouflag),1,fp_w);
				fwrite(temp_kako_bandukehigasiornisi,sizeof(rikisidata[0].kako_bandukehigasiornisi),1,fp_w);
				fwrite(temp_kako_bandukenameid,sizeof(rikisidata[0].kako_bandukenameid),1,fp_w);
				fwrite(temp_kako_bandukesuuji,sizeof(rikisidata[0].kako_bandukesuuji),1,fp_w);
				fwrite(temp_kako_win,sizeof(rikisidata[0].kako_win),1,fp_w);
				fwrite(temp_kako_lost,sizeof(rikisidata[0].kako_lost),1,fp_w);
				fwrite(&temp_jikosaiko_tournament,sizeof(rikisidata[0].jikosaiko_tournament),1,fp_w);
				fwrite(&temp_yuushoukaisuu_tournament,sizeof(rikisidata[0].yuushoukaisuu_tournament),1,fp_w);
				fwrite(&temp_age,sizeof(rikisidata[0].age),1,fp_w);
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				//クローズ
				fclose(fp_w);
			}
			//クローズ
			fclose(fp);
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}


	//自部屋順ファイルのサイズ取得(全部と最高位順はここより前の位置で取得済み)
	for (i=0;i<RETIREMAXFILESUU;i++){
		if (i==0){
			strcpy(temp_filename,"data/dat/retirerikisi_jiheya.dat\0");
			filesize_retire_jiheya[i]=Getfilesize(temp_filename);
		}else{
			sprintf(temp_filename,"data/dat/retirerikisi_jiheya%d.dat\0",i+1);
			filesize_retire_jiheya[i]=Getfilesize(temp_filename);
			if (filesize_retire_jiheya[i]<0) break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
		
	retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();

	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//GetKeys();
		if (r_hyojikirikaeflag==1){
			if (get_mouseclick(330,330,330+105,342)==1 ){
				//今のディレクトリ取得
				GetCurrentDirectory(MAX_PATH, defdir);
				//力士ファイル保存ルーチン呼び出し
				r_savehsr();
				//カレントディレクトリ元に戻す
				SetCurrentDirectory(defdir);
				pagenomihenkouflag_r_mainsibetu=1;
				retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
				WaitTimer(150);
			}
		}
		if (r_hyojikirikaeflag==2){
			if (get_mouseclick(200,170+12*15,200+24,170+12*15+12)==1 ){
				if (page_intaigo>0){
					page_intaigo--;
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if (get_mouseclick(296,170+12*15,296+24,170+12*15+12)==1 ){
				if (page_intaigo<99){
					page_intaigo++;
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
		}
		if (r_hyojikirikaeflag==4){
			if (get_mouseclick(200,170+12*15,200+24,170+12*15+12)==1 ){
				if (page_kyuujou>0){
					page_kyuujou--;
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if (get_mouseclick(296,170+12*15,296+24,170+12*15+12)==1 ){
				if (page_kyuujou<99){
					page_kyuujou++;
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
		}
		if (r_hyojikirikaeflag==3){
			//メイン画面士別表示の頁数指定
			if (get_mouseclick(296+12*5,170+12*15,296+12*5+12*5,170+12*15+12)==1 ){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(187,417,"頁数を入力してください。",CRWHITE);
				DrawString(187,433,"数字で入力後ENTERキーで確定、ESCでキャンセルです。",CRWHITE);
				DrawString(187,449,"　　　　　　頁数＞",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				nyuuryokuti = KeyInputNumber( 342 , 449 , 10000000 , 1 , TRUE );
				if (nyuuryokuti!=10000000+1){
					if ((int)((temp_taisensuu_main-1)/15)+1<nyuuryokuti){
						page_r_sibetu_main=(int)((temp_taisensuu_main-1)/15);
					}else{
						page_r_sibetu_main=nyuuryokuti-1;
					}
				}
				pagenomihenkouflag_r_mainsibetu=1;
				retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
				WaitTimer(150);
			}
			//メイン画面士別表示の頁数減少
			if (get_mouseclick(200,170+12*15,200+24,170+12*15+12)==1 ){
				if (page_r_sibetu_main>0){
					page_r_sibetu_main--;
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			//メイン画面士別表示の頁数増加
			if (get_mouseclick(296,170+12*15,296+24,170+12*15+12)==1 ){
				if (page_r_sibetu_main< (int)((temp_taisensuu_main-1)/15)){
					page_r_sibetu_main++;
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
		}
		if (get_mouseclick(187,387,187+64,387+16)==1 && r_hyojikirikaeflag!=0){
			r_hyojikirikaeflag=0;
			pagenomihenkouflag_r_mainsibetu=1;
			retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
			WaitTimer(150);
		}
		if (get_mouseclick(187+80,387,187+80+64,387+16)==1 && r_hyojikirikaeflag!=1){
			r_hyojikirikaeflag=1;
			pagenomihenkouflag_r_mainsibetu=1;
			retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
			WaitTimer(150);
		}
		if (get_mouseclick(187+80+80,387,187+80+80+64,387+16)==1 && r_hyojikirikaeflag!=2){
			r_hyojikirikaeflag=2;
			pagenomihenkouflag_r_mainsibetu=1;
			retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
			WaitTimer(150);
		}
		if (get_mouseclick(187+80+80+80,387,187+80+80+80+64,387+16)==1 && r_hyojikirikaeflag!=3){
			r_hyojikirikaeflag=3;
			pagenomihenkouflag_r_mainsibetu=0;
			retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
			WaitTimer(150);
		}
		if (get_mouseclick(187+80+80+80+80,387,187+80+80+80+80+64,387+16)==1 && r_hyojikirikaeflag!=4){
			r_hyojikirikaeflag=4;
			pagenomihenkouflag_r_mainsibetu=1;
			retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
			WaitTimer(150);
		}
		if (get_mouseclick(187+80+80+80+80+80,387,639,387+16)==1 && r_hyojikirikaeflag!=5){
			r_hyojikirikaeflag=5;
			pagenomihenkouflag_r_mainsibetu=1;
			retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
			WaitTimer(150);
		}
		if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5){
			if (get_mouseclick(rx1[0]-10+34*0,ry1[0],rx1[0]-10+34*1-1,ry1[0]+16)==1 && r_torikumi_or_seisekiflag!=0){
				r_torikumi_or_seisekiflag=0;
				pagenomihenkouflag_r_mainsibetu=1;
				retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
				WaitTimer(150);
			}
			if (get_mouseclick(rx1[0]-10+34*1,ry1[0],rx1[0]-10+34*2-1,ry1[0]+16)==1 && r_torikumi_or_seisekiflag!=1){
				r_torikumi_or_seisekiflag=1;
				pagenomihenkouflag_r_mainsibetu=1;
				retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
				WaitTimer(150);
			}
			if (get_mouseclick(rx1[0]-10+34*2,ry1[0],rx1[0]-10+34*3-1,ry1[0]+16)==1 && r_torikumi_or_seisekiflag!=2){
				r_torikumi_or_seisekiflag=2;
				pagenomihenkouflag_r_mainsibetu=1;
				retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
				WaitTimer(150);
			}
			if (get_mouseclick(rx1[0]-10+34*3,ry1[0],rx1[0]-10+34*4-1,ry1[0]+16)==1 && r_torikumi_or_seisekiflag!=3){
				r_torikumi_or_seisekiflag=3;
				pagenomihenkouflag_r_mainsibetu=1;
				retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
				WaitTimer(150);
			}
			if (get_mouseclick(rx1[0]-10+34*4,ry1[0],rx1[0]-10+34*5-1,ry1[0]+16)==1 && r_torikumi_or_seisekiflag!=4){
				r_torikumi_or_seisekiflag=4;
				pagenomihenkouflag_r_mainsibetu=1;
				retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
				WaitTimer(150);
			}
		}
		if (get_mouseclick(3,56,62,78)==1 && retire_sentaku_category!=0){
			retire_sentaku_category=0;
			pagenomihenkouflag_r_mainsibetu=0;
			retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
			WaitTimer(150);
		}
		if (get_mouseclick(63,56,126,78)==1 && retire_sentaku_category!=1){
			retire_sentaku_category=1;
			pagenomihenkouflag_r_mainsibetu=0;
			retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
			WaitTimer(150);
		}
		if (get_mouseclick(127,56,183,78)==1 && retire_sentaku_category!=2){
			retire_sentaku_category=2;
			pagenomihenkouflag_r_mainsibetu=0;
			retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
			WaitTimer(150);
		}
		if (get_mouseclick_buttonkensakuLEFT() == 1){//左リスト検索ボタンをクリック
			ichijouhou=kensaku_retirerikisi(ichijouhou);
			if (ichijouhou==-1){
				return;
			}
			retire_sentaku_category=0;
			pagenomihenkouflag_r_mainsibetu=0;
			retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
			WaitTimer(150);
		}
		if (retire_sentaku_category==0){
			if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
				if (ichijouhou>=temp_size){
					ichijouhou-=temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if( CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
				if (ichijouhou<(retiresuu_total-1)*temp_size){
					ichijouhou+=temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			for (i=0;i<20;i++){
				if (i+all_retiresentaku_page*20<retiresuu_total){
					if (get_mouseclick_list(i*2) || get_mouseclick_list(i*2+1)){
						ichijouhou=(all_retiresentaku_page*20+i)*temp_size;
						pagenomihenkouflag_r_mainsibetu=0;
						retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
						WaitTimer(150);
					}
				}
			}
			if (get_mouseclick(187,450,340,466)==1){//ver2.39での変更（追加）ページ指定
				n=jumppage_kiroku();
				if (n!=2147483646+1){
					if (n<1) n=1;
					if (n>(int)((retiresuu_total-1)/20)+1) n=(int)((retiresuu_total-1)/20)+1;
					all_retiresentaku_page=n-1;
					ichijouhou=20*all_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
				}
			}
			if (all_retiresentaku_page>0){
				if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
					all_retiresentaku_page--;
					ichijouhou=20*all_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if (all_retiresentaku_page<(int)((retiresuu_total-1)/20)){
				if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
					all_retiresentaku_page++;
					ichijouhou=20*all_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5
			&& r_torikumi_or_seisekiflag==1){//右成績タブ
				if (retire_sentaku_page>0){
					if (get_mouseclick_buttonUPFAST() == 1){//右リストUPボタンをクリック
						retire_sentaku_page--;
						pagenomihenkouflag_r_mainsibetu=1;
						retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
						WaitTimer(150);
					}
				}
				if (retire_sentaku_page<9){
					if (get_mouseclick_buttonDOWNFAST() == 1){//右リストDOWNボタンをクリック
						retire_sentaku_page++;
						pagenomihenkouflag_r_mainsibetu=1;
						retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
						WaitTimer(150);
					}
				}
			}
			if (get_mouseclick(x1[0],y1[0]-70,x2[1],y1[0]-70+16) == 1){//メニューボタンGをクリックでループから抜け次へ進む
				return;
				//menuflag=1;
				//break;
			}
		}
		if (retire_sentaku_category==1){
			if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
				if (ichijouhou_jiheya>=temp_size){
					ichijouhou_jiheya-=temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if( CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
				if (ichijouhou_jiheya<(retiresuu_jiheya-1)*temp_size){
					ichijouhou_jiheya+=temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			for (i=0;i<20;i++){
				if (i+jiheya_retiresentaku_page*20<retiresuu_jiheya){
					if (get_mouseclick_list(i*2) || get_mouseclick_list(i*2+1)){
						ichijouhou_jiheya=(jiheya_retiresentaku_page*20+i)*temp_size;
						pagenomihenkouflag_r_mainsibetu=0;
						retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
						WaitTimer(150);
					}
				}
			}
			if (get_mouseclick(187,450,340,466)==1){//ver2.39での変更（追加）ページ指定
				n=jumppage_kiroku();
				if (n!=2147483646+1){
					if (n<1) n=1;
					if (n>(int)((retiresuu_jiheya-1)/20)+1) n=(int)((retiresuu_jiheya-1)/20)+1;
					jiheya_retiresentaku_page=n-1;
					ichijouhou_jiheya=20*jiheya_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
				}
			}
			if (jiheya_retiresentaku_page>0){
				if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
					jiheya_retiresentaku_page--;
					ichijouhou_jiheya=20*jiheya_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if (jiheya_retiresentaku_page<(int)((retiresuu_jiheya-1)/20)){
				if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
					jiheya_retiresentaku_page++;
					ichijouhou_jiheya=20*jiheya_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5
			&& r_torikumi_or_seisekiflag==1){//右成績タブ
				if (retire_sentaku_page>0){
					if (get_mouseclick_buttonUPFAST() == 1){//右リストUPボタンをクリック
						retire_sentaku_page--;
						pagenomihenkouflag_r_mainsibetu=1;
						retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
						WaitTimer(150);
					}
				}
				if (retire_sentaku_page<9){
					if (get_mouseclick_buttonDOWNFAST() == 1){//右リストDOWNボタンをクリック
						retire_sentaku_page++;
						pagenomihenkouflag_r_mainsibetu=1;
						retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
						WaitTimer(150);
					}
				}
			}
			if (get_mouseclick(x1[0],y1[0]-70,x2[1],y1[0]-70+16) == 1){//メニューボタンGをクリックでループから抜け次へ進む
				return;
				//menuflag=1;
				//break;
			}
		}
		if (retire_sentaku_category==2){
			if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
				if (ichijouhou_saikoui>=temp_size){
					ichijouhou_saikoui-=temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if( CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
				if (ichijouhou_saikoui<(retiresuu_saikoui-1)*temp_size){
					ichijouhou_saikoui+=temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			for (i=0;i<20;i++){
				//if( ProcessMessage() == -1 ){mode=1;return ;}
				if (i+saikoui_retiresentaku_page*20<retiresuu_saikoui){
					if (get_mouseclick_list(i*2) || get_mouseclick_list(i*2+1)){
						ichijouhou_saikoui=(saikoui_retiresentaku_page*20+i)*temp_size;
						pagenomihenkouflag_r_mainsibetu=0;
						retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
						WaitTimer(150);
					}
				}
			}
			if (get_mouseclick(187,450,340,466)==1){//ver2.39での変更（追加）ページ指定
				n=jumppage_kiroku();
				if (n!=2147483646+1){
					if (n<1) n=1;
					if (n>(int)((retiresuu_saikoui-1)/20)+1) n=(int)((retiresuu_saikoui-1)/20)+1;
					saikoui_retiresentaku_page=n-1;
					ichijouhou_saikoui=20*saikoui_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
				}
			}
			if (saikoui_retiresentaku_page>0){
				if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
					saikoui_retiresentaku_page--;
					ichijouhou_saikoui=20*saikoui_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if (saikoui_retiresentaku_page<(int)((retiresuu_saikoui-1)/20)){
				if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
					saikoui_retiresentaku_page++;
					ichijouhou_saikoui=20*saikoui_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5
			&& r_torikumi_or_seisekiflag==1){//右成績タブ
				if (retire_sentaku_page>0){
					if (get_mouseclick_buttonUPFAST() == 1){//右リストUPボタンをクリック
						retire_sentaku_page--;
						pagenomihenkouflag_r_mainsibetu=1;
						retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
						WaitTimer(150);
					}
				}
				if (retire_sentaku_page<9){
					if (get_mouseclick_buttonDOWNFAST() == 1){//右リストDOWNボタンをクリック
						retire_sentaku_page++;
						pagenomihenkouflag_r_mainsibetu=1;
						retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
						WaitTimer(150);
					}
				}
			}
			if (get_mouseclick(x1[0],y1[0]-70,x2[1],y1[0]-70+16) == 1){//メニューボタンGをクリックでループから抜け次へ進む
				return;
				//menuflag=1;
				//break;
			}
		}
		//右取組タブ
		if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5
		&& r_torikumi_or_seisekiflag==0){
			for (i=0;i<15;i++){
				//if( ProcessMessage() == -1 ){mode=1;return ;}
				if(get_mouseclick_rlist(i*2+4) == 1){//右リスト上の四股名(取組相手)を左クリック
					moto_ichijouhou=ichijouhou;
					ichijouhou=id_retirerikisi(nowhyoji_torikumitab_ID2[i],ichijouhou);
					if (ichijouhou==moto_ichijouhou){
						break;
					}else{
						retire_sentaku_category=0;
						pagenomihenkouflag_r_mainsibetu=0;
						retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
						WaitTimer(150);
					}
				}
			}
			for (i=0;i<15;i++){
				//if( ProcessMessage() == -1 ){mode=1;return ;}
				if(get_mouseclick_rlist(i*2+5) == 1){//右リスト上の決まり手を左クリック
					r_sibetu_rikisiid=nowhyoji_torikumitab_ID2[i];
					r_torikumi_or_seisekiflag=2;
					page_r_sibetu_tab=0;
					pagenomihenkouflag_r_mainsibetu=0;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			for (i=0;i<15;i++){
				//if( ProcessMessage() == -1 ){mode=1;return ;}
				if(get_mouseclick_rlist(i*2+5) == 2){//右リスト上の決まり手を右クリック
					video(nowhyoji_torikumitab_ID,nowhyoji_torikumitab_ID2[i],nowhyoji_torikumitab_year,nowhyoji_torikumitab_month,nowhyoji_torikumitab_namestring,nowhyoji_torikumitab_namestring2[i]);
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			//右取組タブ頁指定
			if (get_mouseclick(rx1[2],ry1[2],rx2[2],ry2[2])==1){
				kensakukekka_kakotorikumi=kensaku_kakotorikumihyoji();
				if (kensakukekka_kakotorikumi>=1){
					hyoji_torikumi_year=(int)(kensakukekka_kakotorikumi/12);
					hyoji_torikumi_month=kensakukekka_kakotorikumi%12;
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}else{
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if (hyoji_torikumi_year*12+hyoji_torikumi_month>temp_hatudohyo_year*12+temp_hatudohyo_month){
				//if (get_mouseclick_buttonUPFAST() == 1){//右リストUPボタンをクリック
				if (get_mouseclick_buttonDOWNFAST() == 1){//右リストDOWNボタンをクリック
					hyoji_torikumi_month-=2;
					if (hyoji_torikumi_month<1){
						hyoji_torikumi_month=11;
						hyoji_torikumi_year--;
					}
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if (hyoji_torikumi_year*12+hyoji_torikumi_month<temp_retire_year*12+temp_retire_month){
				//if (get_mouseclick_buttonDOWNFAST() == 1){//右リストDOWNボタンをクリック
				if (get_mouseclick_buttonUPFAST() == 1){//右リストUPボタンをクリック
					hyoji_torikumi_month+=2;
					if (hyoji_torikumi_month>12){
						hyoji_torikumi_month=1;
						hyoji_torikumi_year++;
					}
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
		}
		//右成績タブ
		if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5
		&& r_torikumi_or_seisekiflag==1){//右成績タブ
			for (i=0;i<18;i++){
				//if( ProcessMessage() == -1 ){mode=1;return ;}
				if(get_mouseclick_rlist(i*2+4) == 1 || get_mouseclick_rlist(i*2+5) == 1){//右リスト上の勝敗部分を左クリック
					r_torikumi_or_seisekiflag=0;
					hyoji_torikumi_month=nowhyoji_seisekitab_month[i];
					hyoji_torikumi_year=nowhyoji_seisekitab_year[i];
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
		}
		//右士別タブ
		if (r_hyojikirikaeflag!=2 && r_hyojikirikaeflag!=5
		&& r_torikumi_or_seisekiflag==2){
			//簡易ビデオ
			for (i=0;i<15;i++){
				//if( ProcessMessage() == -1 ){mode=1;return ;}
				if(get_mouseclick_rlist(i*2+11) == 2){//右リスト上の決まり手を右クリック
					video(nowhyoji_sibetutab_ID,nowhyoji_sibetutab_ID2,nowhyoji_sibetutab_year[i],nowhyoji_sibetutab_month[i],nowhyoji_sibetutab_namestring,nowhyoji_sibetutab_namestring2);
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if (get_mouseclick(rx1[8],ry1[8],rx2[8],ry2[8]) == 1){//ID検索
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(187,417-16,"検索したい力士のIDを入力してください。",CRWHITE);
				DrawString(187,417,"ここでは現役引退両方とも検索します。",CRWHITE);
				DrawString(187,433,"数字で入力後ENTERキーで確定、ESCでキャンセルです。",CRWHITE);
				DrawString(187,449,"検索したい力士ID＞",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				nyuuryokuti = KeyInputNumber( 342 , 449 , 2147483646 , 0 , TRUE );
				if (nyuuryokuti!=2147483647){
					r_sibetu_rikisiid=nyuuryokuti;
				}
				pagenomihenkouflag_r_mainsibetu=0;
				retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
				WaitTimer(150);
			}
			if (page_r_sibetu_tab>0){
				if (get_mouseclick_buttonUPFAST() == 1){//右リストUPボタンをクリック
					page_r_sibetu_tab--;
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
			if (page_r_sibetu_tab<((int)(temp_taisensuu-1)/15)){
				if (get_mouseclick_buttonDOWNFAST() == 1){//右リストDOWNボタンをクリック
					page_r_sibetu_tab++;
					pagenomihenkouflag_r_mainsibetu=1;
					retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);ScreenFlip();
					WaitTimer(150);
				}
			}
		}


		// メッセージ処理
		if( ProcessMessage() == -1 )
		{
			mode=1;
			return;	// エラーが起きたらループから抜ける
		}
		Sleep(1);
	}
			
	return;
}

long id_retirerikisi(int ID,long MOTOICHIJOUHOU)
{
	int i;
	int nowrenban=0;
	char yomikomiokflag=0;
	char temp_filename[MAX_PATH];
	int temp_id_kensaku=0;
	long temp_size=0;
	long ichijouhou[101];

	for (i=0;i<101;i++){
		ichijouhou[i]=0;
		//if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
	}
	for (i=0;i<MAX_PATH;i++){
		temp_filename[i]=0;
		//if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
	}
	temp_size=
			(sizeof(rikisidata[0].rikisiid)+
			sizeof(namestring[rikisidata[0].nameid])+
			sizeof(hometownstring[rikisidata[0].hometownid])+
			sizeof(heyastring[rikisidata[0].heyaid])+
			sizeof(rikisidata[0].heyaid)+
			sizeof(rikisidata[0].hatudohyo_year)+
			sizeof(rikisidata[0].hatudohyo_month)+
			sizeof(year)+
			sizeof(month)+
			sizeof(rikisidata[0].jikosaiko_bandukenameid)+
			sizeof(rikisidata[0].jikosaiko_bandukesuuji)+
			sizeof(rikisidata[0].makuuti_win)+
			sizeof(rikisidata[0].makuuti_lost)+
			sizeof(rikisidata[0].kiroku_yuushoukaisuu)+
			sizeof(rikisidata[0].kinbosisuu)+
			sizeof(rikisidata[0].shukunshousuu)+
			sizeof(rikisidata[0].kantoushousuu)+
			sizeof(rikisidata[0].ginoushousuu)+
			sizeof(rikisidata[0].wintotal)+
			sizeof(rikisidata[0].losttotal)+
			sizeof(rikisidata[0].kiroku_renshou)+
			sizeof(rikisidata[0].kiroku_renpai)+
			sizeof(rikisidata[0].kako_yuushouflag)+
			sizeof(rikisidata[0].kako_bandukehigasiornisi)+
			sizeof(rikisidata[0].kako_bandukenameid)+
			sizeof(rikisidata[0].kako_bandukesuuji)+
			sizeof(rikisidata[0].kako_win)+
			sizeof(rikisidata[0].kako_lost)+
			sizeof(rikisidata[0].jikosaiko_tournament)+
			sizeof(rikisidata[0].yuushoukaisuu_tournament)+
			sizeof(rikisidata[0].age));

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
				if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "main~retirerikisi.datファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return-1;}
			}else{
				sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",nowrenban+1);
				fp = fopen(temp_filename,"rb");
				if( fp == NULL ){
					break;
				}
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
		//ここから表示用読み込み
		yomikomiokflag=0;
		if(fread(&temp_id_kensaku,sizeof(rikisidata[0].rikisiid),1,fp)<1){//EOFor読み取り失敗
			nowrenban++;
			fclose(fp);
		}else{
			yomikomiokflag=1;
			fseek(fp, temp_size-sizeof(rikisidata[0].rikisiid), SEEK_CUR );
			//if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
		}
		//if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
		if (ID==temp_id_kensaku && yomikomiokflag==1){
			ichijouhou[0]=ftell(fp)-temp_size;
			fclose(fp);
			return ichijouhou[0];
		}
	}
	//ファイルクローズ
	fclose(fp);
	return MOTOICHIJOUHOU;
}

void r_savehsr(void){
	HANDLE hSearch;
	WIN32_FIND_DATA fd;
	int InputHandle ;
	int i,ii,count,filecount,k;
	int owariflag=0;
	int prikisi=0;
	int kaeri;
	char temp_st[30][2];
	char temp_string[32];
	char yfilename[20][MAX_PATH+1];
	char sentakufilename[MAX_PATH+1];
	int yrikisi[20];
	int sinkiflag;
	strcpy(sentakufilename,"\0");
	strcpy(temp_string,"\0");
	for (i=0;i<30;i++){
		strcpy(temp_st[i],"\0");
	}
	if (SetCurrentDirectory("user_rikisi")==FALSE){
		CreateDirectory("user_rikisi", NULL);
	}

	// キー入力ハンドルを作る(キャンセルあり全角文字有り数値入力じゃなし)
	InputHandle = MakeKeyInput( 30 , TRUE , FALSE , FALSE ) ;
	// 作成したキー入力ハンドルをアクティブにする
	SetActiveKeyInput( InputHandle ) ;
	SetKeyInputString( namestring_save, InputHandle ) ;

	hSearch = FindFirstFile( _T("r_*.hsr"), &fd );
	if( hSearch != INVALID_HANDLE_VALUE )
	{
		FindClose( hSearch );
		while(1){
			hSearch = FindFirstFile( _T("r_*.hsr"), &fd );
			// 20づつファイルを列挙する
			count=0;
			filecount=0;
			for (i=0;i<20;i++){
				strcpy(yfilename[i],"\0");
				yrikisi[i]=0;
			}
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
			//SetFontSize( 12 ) ;
			DrawStringToHandle(260,6,"能力値ファイル保存画面",CRWHITE,FontHandle12);
			//SetFontSize(16);
			if (filecount>=prikisi*20 && filecount<prikisi*20+20){
				//一つ目のファイル表示
				strcpy(yfilename[count],fd.cFileName);
				yrikisi[count]=24+16*count;
				DrawFormatString(187,yrikisi[count],GetColor(0,255,0),"%s",yfilename[count]);
				count++;
			}
			filecount++;
			while( TRUE )
			{
				if( !FindNextFile( hSearch, &fd ) )
				{
					if( GetLastError() == ERROR_NO_MORE_FILES )
					{
						//DrawString(400,440,"無事終了",GetColor(0,255,0));
						break;
					}
					else
					{
						//DrawString(400,440,"なんかエラー",GetColor(0,255,0));
						break;
					}
				}
				// 列挙されたファイル名を表示
				if (filecount>=prikisi*20 && filecount<prikisi*20+20){
					strcpy(yfilename[count],fd.cFileName);
					yrikisi[count]=24+16*count;
					DrawFormatString(187,yrikisi[count],GetColor(0,255,0),"%s",yfilename[count]);
					count++;
				}
				filecount++;
				if( ProcessMessage() == -1 )
				{
					mode=1;
					return ;	// エラーが起きたらループから抜ける
				}
			}
			FindClose( hSearch );
			DrawFormatString(187,369,GetColor(255,255,255),"%d/%dページ",prikisi+1,(int)((filecount-1)/20)+1);
			DrawString(187,369+16,"ファイル名を入力して下さい。",CRWHITE);
			DrawString(187,369+32,"ENTERキーで確定です。(全角15文字以内)",CRWHITE);
			DrawString(187,369+48,"ECSキーでキャンセル",CRWHITE);
			DrawString(187,369+64,"保存名＞r_",CRWHITE);
			DrawString(600,369+64,".hsr",CRWHITE);
			if (filecount>20){
				DrawString(411,369,"↑↓でページ移動",GetColor(255,255,255));
			}
			ScreenFlip();
			// キー入力終了待ちループ
			// (ProcessMessageをループごとに行う)
			kaeri=0;
			while(1)
			{
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
				DrawFormatString(187,369,GetColor(255,255,255),"%d/%dページ",prikisi+1,(int)((filecount-1)/20)+1);
				DrawString(187,369+16,"ファイル名を入力して下さい。",CRWHITE);
				DrawString(187,369+32,"ENTERキーで確定です。(全角15文字以内)",CRWHITE);
				DrawString(187,369+48,"ECSキーでキャンセル",CRWHITE);
				DrawString(187,369+64,"保存名＞r_",CRWHITE);
				DrawString(600,369+64,".hsr",CRWHITE);
				if (filecount>20){
					DrawString(411,369,"↑↓でページ移動",GetColor(255,255,255));
				}
				for (i=0;i<count;i++){
					DrawFormatString(187,yrikisi[i],GetColor(0,255,0),"%s",yfilename[i]);
				}
				// 入力が終了している場合は終了
				kaeri=CheckKeyInput( InputHandle );
				if( kaeri== -1 ) break ;
				if( kaeri== 1 ){
					GetKeyInputString( temp_string , InputHandle ) ;
					if (strncmp(temp_string,"\0",1)!=0){
						strcpy(sentakufilename,"r_");
						strcat(sentakufilename,temp_string);
						if (checkname(sentakufilename)!=0){
							owariflag=0;
							kaeri=0;
							DeleteKeyInput( InputHandle ) ;
							InputHandle = MakeKeyInput( 30 , TRUE , FALSE , FALSE ) ;
							// 作成したキー入力ハンドルをアクティブにする
							SetActiveKeyInput( InputHandle ) ;
							SetKeyInputString( namestring_save, InputHandle ) ;
							ClearDrawScreen();
						}else{
							strcat(sentakufilename,".hsr");
							//すでに同じ名前のファイルがないかチェック
							owariflag=1;
							hSearch = FindFirstFile( _T("r_*.hsr"), &fd );
							if( hSearch == INVALID_HANDLE_VALUE )
							{
							}else{
								strcpy(yfilename[0],fd.cFileName);
								if (strcmp(yfilename[0],sentakufilename)==0){
									owariflag=2;
								}
								while( TRUE )
								{
									if( !FindNextFile( hSearch, &fd ) )
									{
										if( GetLastError() == ERROR_NO_MORE_FILES )
										{
											//DrawString(400,440,"無事終了",GetColor(0,255,0));
											break;
										}else{
											//DrawString(400,440,"なんかエラー",GetColor(0,255,0));
											break;
										}
									}
									strcpy(yfilename[0],fd.cFileName);
									if (strcmp(yfilename[0],sentakufilename)==0){
										owariflag=2;
										break;
									}
									if( ProcessMessage() == -1 )
									{
										mode=1;
										return ;	// エラーが起きたらループから抜ける
									}
								}
								if (owariflag==2){
									ClearDrawScreen() ;
									DrawBox(0,0,640,480,CRLINE,TRUE);//大枠描画
									DrawBox(3,3,637,477,CRBACK,TRUE);
									DrawBox(0,21,187,480,CRLINE,TRUE);
									DrawBox(3,24,184,477,CRBACK,TRUE);
									DrawBox(184,21,640,369,CRLINE,TRUE);
									DrawBox(187,24,637,366,CRBACK,TRUE);
									DrawBox(184,366,640,480,CRLINE,TRUE);
									DrawBox(187,369,637,477,CRBACK,TRUE);
									DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分
									//SetFontSize( 12 ) ;
									DrawStringToHandle(260,6,"能力値ファイル保存画面",CRWHITE,FontHandle12);
									//SetFontSize(16);
									DrawFormatString(187,369,CRRED,"%s",sentakufilename);
									DrawString(187,369+16,"と同じファイル名が存在します",CRRED);
									DrawString(187,369+32,"上書きしますか",CRWHITE);
									DrawString(x1[4],y1[4],"上書きする",CRGREEN);
									DrawString(x1[8],y1[8],"キャンセル",CRGREEN);
									ScreenFlip();
									while(1){
										if (get_mouseclick_list(4) || get_mouseclick_list(5)){
											owariflag=1;
											break;
										}
										if (get_mouseclick_list(8) || get_mouseclick_list(9)){
											owariflag=0;
											kaeri=0;
											DeleteKeyInput( InputHandle ) ;
											InputHandle = MakeKeyInput( 30 , TRUE , FALSE , FALSE ) ;
											// 作成したキー入力ハンドルをアクティブにする
											SetActiveKeyInput( InputHandle ) ;
											SetKeyInputString( namestring_save, InputHandle ) ;
											ClearDrawScreen();
											break;
										}
										Sleep(1);
										if( ProcessMessage() == -1 )
										{
											mode=1;
											return ;	// エラーが起きたらループから抜ける
										}
									}
								}
								break;
							}
						}
					}else{
						kaeri=0;
						DeleteKeyInput( InputHandle ) ;
						InputHandle = MakeKeyInput( 30 , TRUE , FALSE , FALSE ) ;
						// 作成したキー入力ハンドルをアクティブにする
						SetActiveKeyInput( InputHandle ) ;
						SetKeyInputString( namestring_save, InputHandle ) ;
						ClearDrawScreen();
					}
				}
				if( kaeri == 2 ){
					return ;
				}
				// 入力モードを描画
				DrawKeyInputModeString( 640 , 480 ) ; 
				// 入力途中の文字列を描画
				DrawKeyInputString( 280 , 369+48+16 , InputHandle ) ;
				// 裏画面の内容を表画面に反映させる
				ScreenFlip() ;
				for (i=0;i<count;i++){
					if (get_mouseclick(187,yrikisi[i],637,yrikisi[i]+16)==1){
						for (ii=0;ii<30;ii++){
							if (strncmp(yfilename[i]+ii+2,".",1)!=0){
								strncpy(temp_string+ii,yfilename[i]+ii+2,1);
							}else{
								break;
							}
						}
						strncpy(temp_string+ii,"\0",1);
						DeleteKeyInput( InputHandle ) ;
						InputHandle = MakeKeyInput( 30 , TRUE , FALSE , FALSE ) ;
						// 作成したキー入力ハンドルをアクティブにする
						SetActiveKeyInput( InputHandle ) ;
						SetKeyInputString( temp_string, InputHandle ) ;
						ClearDrawScreen();
					}
				}
				if (CheckHitKey_test(KEY_INPUT_DOWN)==1){
					if (prikisi<(int)((filecount-1)/20)){
						prikisi++;
						break;
					}
				}
				if (CheckHitKey_test(KEY_INPUT_UP)==1){
					if (prikisi>0){
						prikisi--;
						break;
					}
				}
				Sleep(1);
				if( ProcessMessage() == -1 ){
					mode=1;
					break ;	// エラーが発生したらループを抜ける
				}
			}
			if (owariflag==1){
				break;
			}
			Sleep(1);
			if( ProcessMessage() == -1 )
			{
				mode=1;
				return ;	// エラーが起きたらループから抜ける
			}
		}
		if( ProcessMessage() == -1 )
		{
			mode=1;
			return ;	// エラーが起きたらループから抜ける
		}
	}else{//ファイルがもともとなくて新規保存確定の場合
		FindClose( hSearch );
		ClearDrawScreen() ;
		DrawBox(0,0,640,480,CRLINE,TRUE);//大枠描画
		DrawBox(3,3,637,477,CRBACK,TRUE);
		DrawBox(0,21,187,480,CRLINE,TRUE);
		DrawBox(3,24,184,477,CRBACK,TRUE);
		DrawBox(184,21,640,369,CRLINE,TRUE);
		DrawBox(187,24,637,366,CRBACK,TRUE);
		DrawBox(184,366,640,480,CRLINE,TRUE);
		DrawBox(187,369,637,477,CRBACK,TRUE);
		DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分
//		SetFontSize( 12 ) ;
		DrawStringToHandle(260,6,"能力値ファイル保存画面",CRWHITE,FontHandle12);
//		SetFontSize(16);
		DrawString(187,369+16,"ファイル名を入力して下さい。",CRWHITE);
		DrawString(187,369+32,"ENTERキーで確定です。(全角15文字以内)",CRWHITE);
		DrawString(187,369+48,"ECSキーでキャンセル",CRWHITE);
		DrawString(187,369+64,"保存名＞r_",CRWHITE);
		DrawString(600,369+64,".hsr",CRWHITE);
		ScreenFlip();
		kaeri=0;
		while(1)
		{
			ClearDrawScreen() ;
			DrawBox(0,0,640,480,CRLINE,TRUE);//大枠描画
			DrawBox(3,3,637,477,CRBACK,TRUE);
			DrawBox(0,21,187,480,CRLINE,TRUE);
			DrawBox(3,24,184,477,CRBACK,TRUE);
			DrawBox(184,21,640,369,CRLINE,TRUE);
			DrawBox(187,24,637,366,CRBACK,TRUE);
			DrawBox(184,366,640,480,CRLINE,TRUE);
			DrawBox(187,369,637,477,CRBACK,TRUE);
			DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分
	//		SetFontSize( 12 ) ;
			DrawStringToHandle(260,6,"能力値ファイル保存画面",CRWHITE,FontHandle12);
	//		SetFontSize(16);
			DrawString(187,369+16,"ファイル名入力して下さい。",CRWHITE);
			DrawString(187,369+32,"ENTERキーで確定です。(全角15文字以内)",CRWHITE);
			DrawString(187,369+48,"ECSキーでキャンセル",CRWHITE);
			DrawString(187,369+64,"保存名＞r_",CRWHITE);
			DrawString(600,369+64,".hsr",CRWHITE);
			// 入力が終了している場合は終了
			kaeri=CheckKeyInput( InputHandle );
			if( kaeri== -1 ) break ;
			if( kaeri== 1 ){
				GetKeyInputString( temp_string , InputHandle ) ;
				if (strncmp(temp_string,"\0",1)!=0){
					strcpy(sentakufilename,"r_");
					strcat(sentakufilename,temp_string);
					if (checkname(sentakufilename)!=0){
						kaeri=0;
						DeleteKeyInput( InputHandle ) ;
						InputHandle = MakeKeyInput( 30 , TRUE , FALSE , FALSE ) ;
						// 作成したキー入力ハンドルをアクティブにする
						SetActiveKeyInput( InputHandle ) ;
						SetKeyInputString( namestring_save, InputHandle ) ;
						ClearDrawScreen();
					}else{
						strcat(sentakufilename,".hsr");
						break;
					}
				}else{
					kaeri=0;
					DeleteKeyInput( InputHandle ) ;
					InputHandle = MakeKeyInput( 30 , TRUE , FALSE , FALSE ) ;
					// 作成したキー入力ハンドルをアクティブにする
					SetActiveKeyInput( InputHandle ) ;
					SetKeyInputString( namestring_save, InputHandle ) ;
					ClearDrawScreen();
				}
			}
			if( kaeri == 2 ){
				return ;
			}
			// 入力モードを描画
			DrawKeyInputModeString( 640 , 480 ) ; 
			// 入力途中の文字列を描画
			DrawKeyInputString( 280 , 369+48+16 , InputHandle ) ;
			// 裏画面の内容を表画面に反映させる
			ScreenFlip() ;
			Sleep(1);
			if( ProcessMessage() == -1 )
			{
				mode=1;
				return ;	// エラーが起きたらループから抜ける
			}
		}
		if( ProcessMessage() == -1 )
		{
			mode=1;
			return ;	// エラーが起きたらループから抜ける
		}
	}
	
	// 用済みのインプットハンドルを削除する
	DeleteKeyInput( InputHandle ) ;

	//保存処理
	FILE *fp;
/*
	////////////////r_kiroku.dat読み込み///////////////////////////////////
	nowrenban=0;
	yomikomiokflag=0;
	//オープンするファイルの選択
	while(nowrenban<RETIREMAXFILESUU){//
		if (yomikomiokflag==0){
			//ファイルオープン
			if (nowrenban==0){
				strcpy(temp_filename,"data/dat/r_kiroku.dat\0");
				fp = fopen(temp_filename,"rb");
				if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawStringToHandle( 250 , 240 - 32 , "sub_retirerikisi_new~r_kiroku.datファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );DrawStringToHandle( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );ScreenFlip();WaitKey();mode=1;return;}
			}else{
				sprintf(temp_filename,"data/dat/r_kiroku%d.dat\0",nowrenban+1);
				fp = fopen(temp_filename,"rb");
				if( fp == NULL ){ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawStringToHandle( 250 , 240 - 32 , "sub_retirerikisi_new~r_kiroku%d.datファイルオープンに失敗" , GetColor(255,255,255),FontHandle12 );DrawStringToHandle( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255),FontHandle12 );ScreenFlip();WaitKey();mode=1;return;}
			}
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//ここからメイン表示用読み込み
		yomikomiokflag=0;
		if(fread(&r_rikisidata[0].rikisiid,sizeof(r_rikisidata[0].rikisiid),1,fp)<1){//EOFor読み取り失敗
			nowrenban++;
			fclose(fp);
		}else{
			yomikomiokflag=1;
			fread(&r_rikisidata[0],sizeof(rikisidata[0]),1,fp);
			fread(&temp_sanyakuijouzaiisuu,sizeof(temp_sanyakuijouzaiisuu),1,fp);
			fread(&temp_makuutiijouzaiisuu,sizeof(temp_makuutiijouzaiisuu),1,fp);
			fread(&temp_juuryouijouzaiisuu,sizeof(temp_juuryouijouzaiisuu),1,fp);
			fread(&temp_stamina_natural_kakosaikou,sizeof(temp_stamina_natural_kakosaikou),1,fp);
			fread(&temp_binshousei_natural_kakosaikou,sizeof(temp_binshousei_natural_kakosaikou),1,fp);

			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (r_rikisidata[0].rikisiid==ID && yomikomiokflag==1){
			break;
		}

	}
	//ファイルクローズ
	fclose(fp);
	//敏捷性とスタミナ代入
	r_rikisidata[0].binshousei=60-(int)((r_rikisidata[0].sinchou_max-159)/2)-(int)((r_rikisidata[0].taijuu_max-69)/5)+temp_binshousei_natural_kakosaikou;
	if ( ((int)(((169-r_rikisidata[0].sinchou_max)*(-3))/2)+140) < r_rikisidata[0].taijuu_max ){
		r_rikisidata[0].binshousei-=(r_rikisidata[0].taijuu_max-((int)(((169-r_rikisidata[0].sinchou_max)*(-3))/2)+140))*2;
	}
	if (r_rikisidata[0].binshousei<10) r_rikisidata[0].binshousei=10;
	if (r_rikisidata[0].binshousei>99) r_rikisidata[0].binshousei=99;
	r_rikisidata[0].stamina=80+temp_stamina_natural_kakosaikou+r_rikisidata[0].binshousei;
//////////////////////////////////////
*/
	//能力値ファイル保存
	//オープン
	fp = fopen(sentakufilename,"wb");//カレントディレクトリを変更してるのでこの相対パスでいいと思う
	if( fp == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawBox(0,0,639,479,CRBACK,TRUE);
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , CRWHITE );
		DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return ;
	}
	fwrite(&r_rikisidata[0].sinchou_max,sizeof(rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].taijuu_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].sekkyokusei,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].binshousei,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].tossinryoku_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].kerutikara_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migiwanryoku_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidariwanryoku_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].balance_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].tatiaigijutu_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].tuki_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migiwakikatasa_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidariwakikatasa_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].ategai_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migikaesi_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidarikaesi_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migisibori_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidarisibori_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migikakaekomi_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidarikakaekomi_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hikituke_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migiakuryoku_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidariakuryoku_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].stamina,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].konjou,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].nebari_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].asihakobi_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].juunansei,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].zunou,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migiuwatenage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidariuwatenage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migisitatenage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidarisitatenage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migikotenage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidarikotenage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migisukuinage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidarisukuinage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].sinchou_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].taijuu_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&temp_binshousei_natural_kakosaikou,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].tossinryoku_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].kerutikara_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migiwanryoku_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidariwanryoku_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].balance_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].tatiaigijutu_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].tuki_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migiwakikatasa_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidariwakikatasa_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].ategai_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migikaesi_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidarikaesi_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migisibori_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidarisibori_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migikakaekomi_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidarikakaekomi_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hikituke_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migiakuryoku_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidariakuryoku_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&temp_stamina_natural_kakosaikou,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].nebari_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].asihakobi_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migiuwatenage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidariuwatenage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migisitatenage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidarisitatenage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migikotenage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidarikotenage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].migisukuinage_max,sizeof(r_rikisidata[0].sinchou),1,fp);
	fwrite(&r_rikisidata[0].hidarisukuinage_max,sizeof(r_rikisidata[0].sinchou),1,fp);

	//クローズ
	fclose(fp);

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
//SetFontSize( 12 ) ;
DrawStringToHandle(260,6,"能力値ファイル保存画面",CRWHITE,FontHandle12);
//SetFontSize(16);
	DrawString(187,369,"ファイル名",GetColor(255,255,255));
	DrawFormatString(187,369+16,CRWHITE,"%s",sentakufilename);
	DrawString(187,369+32,"で保存しました",GetColor(255,255,255));
	DrawString(187,369+48,"Hit any key",GetColor(255,255,255));
	ScreenFlip();
	WaitKey();
		
	return;
}
