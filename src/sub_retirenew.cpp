#include "DxLib.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include "define.h"

extern char tukedasi_sanndanmeflag;

extern int Rand_normal(int x,int heikin,int sigma_nyuuryoku);
extern int randommode;
extern int heikin_sinchou;
extern int sigma_sinchou;
extern int heikin_taijuu;
extern int sigma_taijuu;
extern int heikin_binshousei;
extern int sigma_binshousei;
extern int heikin_stamina;
extern int sigma_stamina;
extern int heikin_zunou;
extern int sigma_zunou;
extern int heikin_sonota;
extern int sigma_sonota;


extern int FontHandle12;

extern char AIheyaflag[HEYASUU];//1→成長型AI、2→deepAI

extern int lastkeiko_year[RIKISISUU];
extern int lastkeiko_month[RIKISISUU];
extern int lastkeiko_day[RIKISISUU];
extern char lastkeiko_aitenamestring[RIKISISUU][12];

extern char *aidata;//動的メモリ
extern char *aidata_tatiai;//動的メモリ
extern unsigned short int *rbetuwdata_kouka;
extern unsigned short int *rbetuwdata_bosuu;
extern unsigned short int *rbetutdata_kouka;
extern unsigned short int *rbetutdata_bosuu;

extern char memorykakuchouflag;//力士別の技データまでもメモリに乗せる場合は1
extern char memoryfusokuflag;//動的メモリを使わない場合1
extern char shokiti_superrikisiflag;
extern int aikeikosuu[RIKISISUU][RIKISISUU];//取組・稽古両方合わせた過去の力士別対戦数
extern int kobetu_sikiiti[RIKISISUU];//トータルデータを使うか個別データを使うのかの閾値
extern int shokiti_kobetu_sikiiti;

extern long aidata_fichi[22][5][2][2][2][2][4];//aidataのファイル記録位置
									//技ＩＤ	四つ	自分右廻し	自分左廻し	相手右廻し	相手左廻し	上体比較
									//上体は0→自分の方が高い、１→同じ、2→自分の方が低い
extern char getdatafrombit(char bytedata,char amari);//バイトデータから2bitの値を取り出す関数
										//aidataに記録されているのは2bitずつなので
										//上記fichi/4の位置の2bitの値を0~3の値で返す関数
extern char setdatatobit(char bytedata,char amari,char setdata);//bytedataのamariの位置の2ビットにsetdataの値をセット

extern int wazadata_kouka_seme[22][RIKISISUU][5];//効果(+127～-127)
extern int wazadata_bosuu_seme[22][RIKISISUU][5];//効果(+127～-127)
extern int tatiaidata_kouka_seme[RIKISISUU][20];//どの立ち合いが勝利に結びついたか
extern int tatiaidata_bosuu_seme[RIKISISUU][20];//どの立ち合いが勝利に結びついたか
extern short int lastwazadata_kouka_seme[22][RIKISISUU][5];//
extern short int lastwazadata_bosuu_seme[22][RIKISISUU][5];//
extern short int lasttatiaidata_kouka_seme[RIKISISUU][20];//どの立ち合いが勝利に結びついたか
extern short int lasttatiaidata_bosuu_seme[RIKISISUU][20];//どの立ち合いが勝利に結びついたか

extern int itimonid_used;
extern char namestring_riji[10][21];
extern char maxmode;
extern int intaisuu;
extern int intairikisikonbasho[RIKISISUU];
extern char kyuujouflag[RIKISISUU];
extern char heyadokuritumode;//0新設消滅無し、1新設消滅有り
extern char namestring_choufukucheck[RIKISISUU][12];//重複チェック用、のノ乃を除いた四股名
extern int jinbou_rikisi[RIKISISUU];//人望
extern void keiko_nakami_com(int x);
extern int tukedasiid;
extern int binshousei_natural_kakosaikou[RIKISISUU];//引退力士表示で必要なのでしょうがなく
extern int stamina_natural_kakosaikou[RIKISISUU];//引退力士表示で必要なのでしょうがなく
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
extern int retire_yokoduna_lost1;//引退条件
extern int retire_yokoduna_lost2;
extern int retire_yokoduna_lost3;
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
extern int heyaid_used;//使用した通算部屋ID数
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

extern int page_oyakata_itimon;

extern int kabusouba(void);
extern int A_saikoui;//Ａカテの条件
extern int A_sanyakuzaiisuu;
extern int A_makuutizaiisuu;
extern int B_saikoui;//Ｂカテの条件
extern int B_makuutizaiisuu;
extern int B_jyuuryouzaiisuu;
extern int C_makuutizaiisuu;//Ｃカテの条件
extern int C_jyuuryouzaiisuu;


void nouryokuhyoji(int x,int yokozure);

void retirerikisidata_rikisiid(int x);
int retirerikisidata_retireage=0;
int retirerikisidata_jikosaikoubandukenameid=0;
int retirerikisidata_jikosaikoubandukesuuji=0;


extern int AIkotenagesukuinage_shokitizeroflag;//AI評価の初期値のうち小手投げと掬い投げだけは0(D)にするフラグ（他はB）、今まではＤだったけどver4.05beta010から変更


void retirenew(void)
{
char debug_char=0;
char rinneflag_sinchou=0;
char rinneflag_taijuu=0;
char rinneflag_sekkyokusei=0;
char rinneflag_binshousei=0;
char rinneflag_tossinryoku=0;
char rinneflag_kerutikara=0;
char rinneflag_migiwanryoku=0;
char rinneflag_hidariwanryoku=0;
char rinneflag_balance=0;
char rinneflag_tatiaigijutu=0;
char rinneflag_tuki=0;
char rinneflag_migiwakikatasa=0;
char rinneflag_hidariwakikatasa=0;
char rinneflag_ategai=0;
char rinneflag_migikaesi=0;
char rinneflag_hidarikaesi=0;
char rinneflag_migisibori=0;
char rinneflag_hidarisibori=0;
char rinneflag_migikakaekomi=0;
char rinneflag_hidarikakaekomi=0;
char rinneflag_hikituke=0;
char rinneflag_migiakuryoku=0;
char rinneflag_hidariakuryoku=0;
char rinneflag_stamina=0;
char rinneflag_konjou=0;
char rinneflag_nebari=0;
char rinneflag_asihakobi=0;
char rinneflag_juunansei=0;
char rinneflag_zunou=0;
char rinneflag_migiuwatenage=0;
char rinneflag_hidariuwatenage=0;
char rinneflag_migisitatenage=0;
char rinneflag_hidarisitatenage=0;
char rinneflag_migikotenage=0;
char rinneflag_hidarikotenage=0;
char rinneflag_migisukuinage=0;
char rinneflag_hidarisukuinage=0;

	char taishokuzumiflag=0;
	char joutosakiketteiflag=0;
	char simeizumiflag=0;
	int heyaid_dokuritusaki=0;
	int heyaid_dokuritumoto=0;
	char mitizuresuu=0;
	char count_mitizuresuu=0;
	int dokuritumoto_sishouid=0;
	int sishouid=0;
	int heyatukiid=0;

	char kirokuhituyouflag_tosiyoriid[TOSIYORISUU];//年寄画面用のファイルに記録が必要な年寄
	char heyameihenkouzumiflag=0;
	char koukeishaflag=0;
	char kabushutokuzumiflag=0;
	int temp_jinbou=0;
	int temp_tosiyoriid=0;
	int temp_rikisinonarabekaeyou[RIKISISUU];
	int jinboujun_rikisiid[RIKISISUU];
	int temp_narabekaeyou[TOSIYORISUU];//並べ替え用に並べ替えたい要素を入れる変数
	int jinboujun_tosiyoriid[TOSIYORISUU];
	int kakuritu_hiragana_no=0;
	int kakuritu_katakana_no=0;
	int kakuritu_kanji_no=0;
	int ransuu_kakuritu_no=0;
	
	int ransuu_mae=0;
	int ransuu_ato=0;
	int ransuu_mid=0;
	int ransuu_kakuritu=0;
	char temp_string_kakuritu[301];
	char ch;
	int kazu=0;
	int kakuritu_heya_mid=0;//部屋別冠文字+mid
	int kakuritu_heya_ato=0;//部屋別冠文字+ato
	int	kakuritu_heya_mid_ato=0;//部屋別冠文字+mid+ato
	int	kakuritu_mae_heya=0;//mae+部屋別文字
	int	kakuritu_mid_heya=0;//mid+部屋別文字
	int	kakuritu_mae_mid_heya=0;//mae+mid+部屋別文字
	int	kakuritu_mae_mid=0;//mae+mid
	int	kakuritu_mae_ato=0;//mae+ato
	int	kakuritu_mae_mid_ato=0;//mae+mid+ato
	int	kakuritu_mid_ato=0;//mid+ato

	char choufukuflag=0;
	int choufukukaisuu=0;



	int itidai_tosiyoriid,shutoku_tosiyoriid,shuumei_tosiyoriid;

	int nagasa_namestring=0;
	
	long temp_size=0;
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
	int rikisi_front_temp;
	int yokozure=0;
	int starttime=0;
	int owariflag;
	int star_itayo;
	int r;
	int rr;
	int i;
	int ii;
	int iii;
	int iiii;
	int iiiii;
	int win;
	int lost;
	int count;
	int countname;
	int counthometown=0;
	int countheya=0;
	int retireflag;
	int retiresuu=0;
	int siganshasuu_myheya=0;
	int filter_nouryoku_total_max;
	int scoutmoney=0;
	int SPoint ;	// 選択カーソルの位置
	int SenntakuNum ;
//	int backup_keikoryou_sekkyokusei;
//	int backup_keikoryou_konjou;
//	int backup_keikoryou_nebari;
	char temp_namestring_mid[SICHOUSONSUU][9];
	char temp_namestring_ato[SICHOUSONSUU][5];
	char temp_namestring_mae[SICHOUSONSUU][5];
	char temp_namestring_heyabetu[108][5];
	int temp_nameid[RIKISISUU];
	int hoketuflag;
	char temp_filename[MAX_PATH];
	char temp_str_name[12];
	char tosiyoriiruflag[HEYASUU];
	int temp_rikisiid=0;
	int temp_year=0;
	int temp_month=0;
	char temp_bandukenameid=0;
	char temp_bandukesuuji=0;
	int temp_yasumi=0;
	int kirokusuu=0;
	char temp_kyuujoustring[21];

	FILE *fp;
	FILE *fpcsv;
	//FILE *fpdebug;

///////debug//////
/*
fpdebug = fopen("debug_souba.csv","a");
fprintf(fpdebug,"%d年%d月,%d\n",year,month,kabusouba());
fclose(fpdebug);
*/
//////////////////
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (i=0;i<HEYASUU;i++){
		tosiyoriiruflag[i]=0;
	}
	for (i=0;i<MAX_PATH;i++){
		temp_filename[i]=0;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (i=0;i<12;i++){
		temp_str_name[i]=0;
	}
	for (i=0;i<TOSIYORISUU;i++){
		kirokuhituyouflag_tosiyoriid[i]=0;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (i=0;i<301;i++){
		temp_string_kakuritu[i]=0;
	}
	for (i=0;i<21;i++){
		temp_kyuujoustring[i]=0;
	}
	for (i=0;i<SICHOUSONSUU;i++){
		for (ii=0;ii<9;ii++){
			temp_namestring_mid[i][ii]=0;
		}
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (i=0;i<SICHOUSONSUU;i++){
		for (ii=0;ii<5;ii++){
			temp_namestring_ato[i][ii]=0;
			temp_namestring_mae[i][ii]=0;
		}
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (i=0;i<108;i++){
		for (ii=0;ii<5;ii++){
			temp_namestring_heyabetu[i][ii]=0;
		}
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (i=0;i<RIKISISUU;i++){
		temp_nameid[i]=0;
	}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//輪廻させる能力値の読込
	strcpy(temp_filename,"data/rinnenouryoku.csv");
	fpcsv = fopen(temp_filename,"r");
	if( fpcsv == NULL ){
		fclose(fpcsv);
		fpcsv = fopen(temp_filename,"w");
		fprintf(fpcsv,"輪廻させる能力値を選択\n");
		fprintf(fpcsv,"0で輪廻させない1で輪廻させる\n");
		fprintf(fpcsv,"身長\n");
		fprintf(fpcsv,"0\n");
		fprintf(fpcsv,"体重\n");
		fprintf(fpcsv,"0\n");
		fprintf(fpcsv,"積極性\n");
		fprintf(fpcsv,"0\n");
		fprintf(fpcsv,"敏捷性\n");
		fprintf(fpcsv,"0\n");
		fprintf(fpcsv,"突進力\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"蹴る力\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"右腕力\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"左腕力\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"バラン\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"立会術\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"突き\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"右脇堅\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"左脇堅\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"あてが\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"右返し\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"左返し\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"右絞り\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"左絞り\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"右抱込\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"左抱込\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"ひきつ\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"右握力\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"左握力\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"スタミ\n");
		fprintf(fpcsv,"0\n");
		fprintf(fpcsv,"根性\n");
		fprintf(fpcsv,"0\n");
		fprintf(fpcsv,"粘り\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"足運び\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"柔軟性\n");
		fprintf(fpcsv,"0\n");
		fprintf(fpcsv,"頑固\n");
		fprintf(fpcsv,"0\n");
		fprintf(fpcsv,"右上投\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"左上投\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"右下投\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"左下投\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"右小投\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"左小投\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"右掬投\n");
		fprintf(fpcsv,"1\n");
		fprintf(fpcsv,"左掬投\n");
		fprintf(fpcsv,"1\n");
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		fclose(fpcsv);
		fpcsv = fopen(temp_filename,"r");
	}
	kazu=0;
	ch=0;ch=1;
	while(1) 
	{
		for (ii=0;ii<301;ii++){
			temp_string_kakuritu[ii]=0;
		}
		if (ch == EOF){break;}
		for (ii=0;ii<30;ii++){
			ch = fgetc(fpcsv);
			if (ch == EOF){break;}
			if(ch == '\n'){
				break;
			}else{
				if(ch=='0'){
					strcat(temp_string_kakuritu,"0");
				}else if(ch=='1'){
					strcat(temp_string_kakuritu,"1");
				}else if(ch=='2'){
					strcat(temp_string_kakuritu,"2");
				}else if(ch=='3'){
					strcat(temp_string_kakuritu,"3");
				}else if(ch=='4'){
					strcat(temp_string_kakuritu,"4");
				}else if(ch=='5'){
					strcat(temp_string_kakuritu,"5");
				}else if(ch=='6'){
					strcat(temp_string_kakuritu,"6");
				}else if(ch=='7'){
					strcat(temp_string_kakuritu,"7");
				}else if(ch=='8'){
					strcat(temp_string_kakuritu,"8");
				}else if(ch=='9'){
					strcat(temp_string_kakuritu,"9");
				}
			}
		}
		if(kazu==3){
			rinneflag_sinchou=atoi(temp_string_kakuritu);
		}else if(kazu==5){
			rinneflag_taijuu=atoi(temp_string_kakuritu);
		}else if(kazu==7){
			rinneflag_sekkyokusei=atoi(temp_string_kakuritu);
		}else if(kazu==9){
			rinneflag_binshousei=atoi(temp_string_kakuritu);
		}else if(kazu==11){
			rinneflag_tossinryoku=atoi(temp_string_kakuritu);
		}else if(kazu==13){
			rinneflag_kerutikara=atoi(temp_string_kakuritu);
		}else if(kazu==15){
			rinneflag_migiwanryoku=atoi(temp_string_kakuritu);
		}else if(kazu==17){
			rinneflag_hidariwanryoku=atoi(temp_string_kakuritu);
		}else if(kazu==19){
			rinneflag_balance=atoi(temp_string_kakuritu);
		}else if(kazu==21){
			rinneflag_tatiaigijutu=atoi(temp_string_kakuritu);
		}else if(kazu==23){
			rinneflag_tuki=atoi(temp_string_kakuritu);
		}else if(kazu==25){
			rinneflag_migiwakikatasa=atoi(temp_string_kakuritu);
		}else if(kazu==27){
			rinneflag_hidariwakikatasa=atoi(temp_string_kakuritu);
		}else if(kazu==29){
			rinneflag_ategai=atoi(temp_string_kakuritu);
		}else if(kazu==31){
			rinneflag_migikaesi=atoi(temp_string_kakuritu);
		}else if(kazu==33){
			rinneflag_hidarikaesi=atoi(temp_string_kakuritu);
		}else if(kazu==35){
			rinneflag_migisibori=atoi(temp_string_kakuritu);
		}else if(kazu==37){
			rinneflag_hidarisibori=atoi(temp_string_kakuritu);
		}else if(kazu==39){
			rinneflag_migikakaekomi=atoi(temp_string_kakuritu);
		}else if(kazu==41){
			rinneflag_hidarikakaekomi=atoi(temp_string_kakuritu);
		}else if(kazu==43){
			rinneflag_hikituke=atoi(temp_string_kakuritu);
		}else if(kazu==45){
			rinneflag_migiakuryoku=atoi(temp_string_kakuritu);
		}else if(kazu==47){
			rinneflag_hidariakuryoku=atoi(temp_string_kakuritu);
		}else if(kazu==49){
			rinneflag_stamina=atoi(temp_string_kakuritu);
		}else if(kazu==51){
			rinneflag_konjou=atoi(temp_string_kakuritu);
		}else if(kazu==53){
			rinneflag_nebari=atoi(temp_string_kakuritu);
		}else if(kazu==55){
			rinneflag_asihakobi=atoi(temp_string_kakuritu);
		}else if(kazu==57){
			rinneflag_juunansei=atoi(temp_string_kakuritu);
		}else if(kazu==59){
			rinneflag_zunou=atoi(temp_string_kakuritu);
		}else if(kazu==61){
			rinneflag_migiuwatenage=atoi(temp_string_kakuritu);
		}else if(kazu==63){
			rinneflag_hidariuwatenage=atoi(temp_string_kakuritu);
		}else if(kazu==65){
			rinneflag_migisitatenage=atoi(temp_string_kakuritu);
		}else if(kazu==67){
			rinneflag_hidarisitatenage=atoi(temp_string_kakuritu);
		}else if(kazu==69){
			rinneflag_migikotenage=atoi(temp_string_kakuritu);
		}else if(kazu==71){
			rinneflag_hidarikotenage=atoi(temp_string_kakuritu);
		}else if(kazu==73){
			rinneflag_migisukuinage=atoi(temp_string_kakuritu);
		}else if(kazu==75){
			rinneflag_hidarisukuinage=atoi(temp_string_kakuritu);
		}
		kazu++;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	fclose(fpcsv);
	if( ProcessMessage() == -1 ){mode=1;return ;}

////////debug/////
/*
strcpy(temp_filename,"debug_rinnenouryoku.csv");
fpcsv = fopen(temp_filename,"w");
fprintf(fpcsv,"%d\n",rinneflag_sinchou);
fprintf(fpcsv,"%d\n",rinneflag_taijuu);
fprintf(fpcsv,"%d\n",rinneflag_sekkyokusei);
fprintf(fpcsv,"%d\n",rinneflag_binshousei);
fprintf(fpcsv,"%d\n",rinneflag_tossinryoku);
fprintf(fpcsv,"%d\n",rinneflag_kerutikara);
fprintf(fpcsv,"%d\n",rinneflag_migiwanryoku);
fprintf(fpcsv,"%d\n",rinneflag_hidariwanryoku);
fprintf(fpcsv,"%d\n",rinneflag_balance);
fprintf(fpcsv,"%d\n",rinneflag_tatiaigijutu);
fprintf(fpcsv,"%d\n",rinneflag_tuki);
fprintf(fpcsv,"%d\n",rinneflag_migiwakikatasa);
fprintf(fpcsv,"%d\n",rinneflag_hidariwakikatasa);
fprintf(fpcsv,"%d\n",rinneflag_ategai);
fprintf(fpcsv,"%d\n",rinneflag_migikaesi);
fprintf(fpcsv,"%d\n",rinneflag_hidarikaesi);
fprintf(fpcsv,"%d\n",rinneflag_migisibori);
fprintf(fpcsv,"%d\n",rinneflag_hidarisibori);
fprintf(fpcsv,"%d\n",rinneflag_migikakaekomi);
fprintf(fpcsv,"%d\n",rinneflag_hidarikakaekomi);
fprintf(fpcsv,"%d\n",rinneflag_hikituke);
fprintf(fpcsv,"%d\n",rinneflag_migiakuryoku);
fprintf(fpcsv,"%d\n",rinneflag_hidariakuryoku);
fprintf(fpcsv,"%d\n",rinneflag_stamina);
fprintf(fpcsv,"%d\n",rinneflag_konjou);
fprintf(fpcsv,"%d\n",rinneflag_nebari);
fprintf(fpcsv,"%d\n",rinneflag_asihakobi);
fprintf(fpcsv,"%d\n",rinneflag_juunansei);
fprintf(fpcsv,"%d\n",rinneflag_zunou);
fprintf(fpcsv,"%d\n",rinneflag_migiuwatenage);
fprintf(fpcsv,"%d\n",rinneflag_hidariuwatenage);
fprintf(fpcsv,"%d\n",rinneflag_migisitatenage);
fprintf(fpcsv,"%d\n",rinneflag_hidarisitatenage);
fprintf(fpcsv,"%d\n",rinneflag_migikotenage);
fprintf(fpcsv,"%d\n",rinneflag_hidarikotenage);
fprintf(fpcsv,"%d\n",rinneflag_migisukuinage);
fprintf(fpcsv,"%d\n",rinneflag_hidarisukuinage);
fprintf(fpcsv,"kazu=%d\n",kazu);
fclose(fpcsv);
*/
/////////////////




/*banduke_hyojijunbiルーチンの中でやることにした
////////所属データ定期記録///////shozoku.dat//ファイルサイズ小さいはずなので分割しない
	//ファイルオープン
	strcpy(temp_filename,"data/dat/shozoku.dat\0");
	fp = fopen(temp_filename,"ab");
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//ここから書き込み
	fwrite(&year,sizeof(year),1,fp);
	fwrite(&month,sizeof(month),1,fp);
	for (i=0;i<RIKISISUU;i++){
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		fwrite(&rikisidata[i].rikisiid,sizeof(rikisidata[i].rikisiid),1,fp);
		fwrite(&rikisidata[i].heyaid,sizeof(rikisidata[i].heyaid),1,fp);
	}
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
////////////////////////////////////////////////////////


/////////////年寄画面表示専用ファイル書き込み(1年1月のみの処理、定期処理はこのルーチンのおしり)/////////////
if (year==1 && month==1){
	for (i=0;i<106;i++){
		//if (kirokuhituyouflag_tosiyoriid[i]==1){
			sprintf(temp_filename,"data/dat/hyoji_tosiyori%d.dat\0",i);
			fp = fopen(temp_filename,"ab");
			fwrite(&year,sizeof(year),1,fp);
			fwrite(&month,sizeof(month),1,fp);
			fwrite(&tosiyoridata[i].rikisiid,sizeof(tosiyoridata[i].rikisiid),1,fp);
			fwrite(tosiyoridata[i].sikona,sizeof(tosiyoridata[i].sikona),1,fp);
			fwrite(&tosiyoridata[i].keishousha_rikisiid,sizeof(tosiyoridata[i].keishousha_rikisiid),1,fp);
			if (tosiyoridata[i].keishousha_rikisiid>=0){
				fwrite(namestring[tosiyoridata[i].keishousha_rikisiid],sizeof(namestring[tosiyoridata[i].keishousha_rikisiid]),1,fp);
			}else{
				fwrite(namestring[0],sizeof(namestring[0]),1,fp);//ダミーで入れておいた、表示するときはkeishousha_rikisiidが-1かどうかで判断すべき
			}
			fwrite(&tosiyoridata[i].shozokuitimonid,sizeof(tosiyoridata[i].shozokuitimonid),1,fp);
			if (tosiyoridata[i].shozokuitimonid>=0){
				fwrite(itimondata[tosiyoridata[i].shozokuitimonid].namestring,sizeof(itimondata[tosiyoridata[i].shozokuitimonid].namestring),1,fp);
			}else{
				fwrite(itimondata[0].namestring,sizeof(itimondata[0].namestring),1,fp);//ダミー
			}
			fwrite(&tosiyoridata[i].shozokuheyaid,sizeof(tosiyoridata[i].shozokuheyaid),1,fp);
			if (tosiyoridata[i].shozokuheyaid>=0){
				fwrite(heyastring[tosiyoridata[i].shozokuheyaid],sizeof(heyastring[tosiyoridata[i].shozokuheyaid]),1,fp);
			}else{
				fwrite(heyastring[0],sizeof(heyastring[0]),1,fp);//ダミー
			}
			fwrite(&tosiyoridata[i].sishouflag,sizeof(tosiyoridata[i].sishouflag),1,fp);
			fwrite(&tosiyoridata[i].keishousha_tosiyoriid,sizeof(tosiyoridata[i].keishousha_tosiyoriid),1,fp);
			if (tosiyoridata[i].keishousha_tosiyoriid>=0){
				fwrite(tosiyoridata[tosiyoridata[i].keishousha_tosiyoriid].namestring,sizeof(tosiyoridata[tosiyoridata[i].keishousha_tosiyoriid].namestring),1,fp);
			}else{
				fwrite(tosiyoridata[0].namestring,sizeof(tosiyoridata[0].namestring),1,fp);//ダミー
			}
			fclose(fp);
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//}
	}
}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
	////////年寄データ定期記録///////tosiyori.dat//α039よりお尻から冒頭に移したけど大丈夫かな？
	//各連番ファイルのサイズ取得
	for (ii=0;ii<RETIREMAXFILESUU;ii++){
		if (ii==0){
			strcpy(temp_filename,"data/dat/tosiyori.dat\0");
			filesize_retire[ii]=Getfilesize(temp_filename);
		}else{
			sprintf(temp_filename,"data/dat/tosiyori%d.dat\0",ii+1);
			filesize_retire[ii]=Getfilesize(temp_filename);
			if (filesize_retire[ii]<0) break;
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//ファイルオープン
	for (ii=0;ii<RETIREMAXFILESUU;ii++){
		if (ii==0){
			if (filesize_retire[ii]<=maxfilesize){
				strcpy(temp_filename,"data/dat/tosiyori.dat\0");
				fp = fopen(temp_filename,"ab");
				break;
			}
		}else{
			if (filesize_retire[ii]<=maxfilesize){
				sprintf(temp_filename,"data/dat/tosiyori%d.dat\0",ii+1);
				fp = fopen(temp_filename,"ab");
				break;
			}
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//ここから書き込み
	fwrite(&year,sizeof(year),1,fp);
	fwrite(&month,sizeof(month),1,fp);
	fwrite(tosiyoridata,sizeof(tosiyoridata),1,fp);
	fwrite(itimondata,sizeof(itimondata),1,fp);
	fwrite(heyadata,sizeof(heyadata),1,fp);
	fwrite(heyastring,sizeof(heyastring),1,fp);

	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
////////////////////////////////////////////////////////
*/



/////年寄引退などの年寄関連処理////年寄一括処理///////////////////////////////////////////////////////////
	//力士が一人以上いる部屋数確認→shozokurikisisuu[部屋ＩＤ]
	heyasuu_genzon=0;//年寄が一人以上在籍している部屋数を確認
	//部屋ごとの年寄数確認
	for (i=0;i<HEYASUU;i++){
		heya_tosiyorisuu[i]=0;
		for (ii=0;ii<TOSIYORISUU;ii++){
			if (tosiyoridata[ii].shozokuheyaid==i){
				heya_tosiyorisuu[i]++;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		if (heya_tosiyorisuu[i]>0){
			heyasuu_genzon++;
		}
	}

	//人望順力士IDを検索
	//バブルソート
	for (iii=0;iii<RIKISISUU;iii++){
		temp_rikisinonarabekaeyou[iii]=0;
		temp_rikisinonarabekaeyou[iii]=jinbou_rikisi[iii];
		jinboujun_rikisiid[iii]=0;
		jinboujun_rikisiid[iii]=iii;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (iii = 0;iii < RIKISISUU - 1;iii++) {
		for (ii = 0;ii < RIKISISUU - 1;ii++) {
			if (temp_rikisinonarabekaeyou[ii + 1] > temp_rikisinonarabekaeyou[ii]) {
				temp_rikisiid = temp_rikisinonarabekaeyou[ii];
				temp_rikisinonarabekaeyou[ii] = temp_rikisinonarabekaeyou[ii + 1];
				temp_rikisinonarabekaeyou[ii + 1] = temp_rikisiid;
				temp_rikisiid = jinboujun_rikisiid[ii];
				jinboujun_rikisiid[ii] = jinboujun_rikisiid[ii+1];
				jinboujun_rikisiid[ii+1] = temp_rikisiid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}

	//現役力士継承者指名処理
	//Aカテ要件成就力士
	for (i=0;i<RIKISISUU;i++){
		temp_rikisiid=i;	//このループの最後で逆代入
		i=jinboujun_rikisiid[i];
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//Aカテ要件
		if (rikisidata[i].jikosaiko_bandukenameid<=A_saikoui || sanyakuijouzaiisuu[i]>=A_sanyakuzaiisuu || makuutiijouzaiisuu[i]>=A_makuutizaiisuu){
			kabushutokuzumiflag=0;//株取得済みの力士かどうか確認
			for (ii=0;ii<106;ii++){//株取得済み力士かどうか確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].keishousha_rikisiid==i){
					//if (tosiyoridata[ii].shozokuheyaid!=rikisidata[i].heyaid || (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid && tosiyoridata[ii].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
						kabushutokuzumiflag=1;
					//}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			//まだ継承者がいないなら所属部屋の師匠から継承者指名してもらう処理、他の株をすでに取得していたら手放す処理も同時に
			for (ii=0;ii<106;ii++){//まだ継承者指名してない師匠か確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid 
				&& tosiyoridata[ii].sishouflag==1 
				&& tosiyoridata[ii].keishousha_rikisiid==-1 
				&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
					if(tosiyoridata[ii].age >= 60 
					&& rikisidata[i].age_roukastart<rikisidata[i].age){//ここに老化開始年齢と師匠の引退年齢との比較による絞込み
						tosiyoridata[ii].keishousha_rikisiid=i;
						kabushutokuzumiflag=1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才)が師匠の%s(%d才)親方から後継者として指名される\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が師匠の%s(%d才)親方から後継者として指名される",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						//他の株を取得していたら手放す処理
						for (iii=0;iii<106;iii++){
							if (tosiyoridata[iii].keishousha_rikisiid==i 
							&& iii!=ii){
								tosiyoridata[iii].keishousha_rikisiid=-1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[iii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%sは保有していた年寄株%sを手放す\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%sは保有していた年寄株%sを手放す",
heyastring[rikisidata[i].heyaid],
namestring[i],
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								//現役力士取得処理
								{
									int temp_rikisiid=0;
									char a_kabushutokuzumiflag=0;
									int ia=0;
									int iia=0;
									int warikomi_yuushourikisiflag=0;
									int warikomi_jinbou=0;
									char temp_string_kakuritu[301];
									char ch=0;
									int kazu=0;
									for (iia=0;iia<301;iia++){
										temp_string_kakuritu[iia]=0;
									}
									FILE *fpcsv;
									if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									strcpy(temp_filename,"data/warikomisisuu.csv");
									fpcsv = fopen(temp_filename,"r");
									if( fpcsv == NULL ){
										fclose(fpcsv);
										fpcsv = fopen(temp_filename,"w");
										fprintf(fpcsv,"現役力士一門内株取得に一門外優勝力士を割り込ませるか、(1だと割り込み)\n");
										fprintf(fpcsv,"0\n");
										fprintf(fpcsv,"現役力士一門内株取得に人望で一門外力士を割込み(下の値以上だと割り込み)\n");
										fprintf(fpcsv,"10000\n");
										if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										fclose(fpcsv);
										fpcsv = fopen(temp_filename,"r");
									}
									kazu=0;
									ch=1;
									while(1) 
									{
										for (iia=0;iia<301;iia++){
											temp_string_kakuritu[iia]=0;
										}
										if (ch == EOF){break;}
										for (iia=0;iia<300;iia++){
											ch = fgetc(fpcsv);
											if (ch == EOF){break;}
											if(ch == '\n'){
												break;
											}else{
												if(ch=='0'){
													strcat(temp_string_kakuritu,"0");
												}else if(ch=='1'){
													strcat(temp_string_kakuritu,"1");
												}else if(ch=='2'){
													strcat(temp_string_kakuritu,"2");
												}else if(ch=='3'){
													strcat(temp_string_kakuritu,"3");
												}else if(ch=='4'){
													strcat(temp_string_kakuritu,"4");
												}else if(ch=='5'){
													strcat(temp_string_kakuritu,"5");
												}else if(ch=='6'){
													strcat(temp_string_kakuritu,"6");
												}else if(ch=='7'){
													strcat(temp_string_kakuritu,"7");
												}else if(ch=='8'){
													strcat(temp_string_kakuritu,"8");
												}else if(ch=='9'){
													strcat(temp_string_kakuritu,"9");
												}
											}
										}
										if (kazu==1){
											warikomi_yuushourikisiflag=atoi(temp_string_kakuritu);
										}else if(kazu==3){
											warikomi_jinbou=atoi(temp_string_kakuritu);
										}
										kazu++;
										//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									}
									fclose(fpcsv);
									if( ProcessMessage() == -1 ){mode=1;return ;}
									for (ia=0;ia<RIKISISUU;ia++){
										temp_rikisiid=ia;	//このループの最後で逆代入
										ia=jinboujun_rikisiid[ia];
										//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										//Aカテ・Ｂカテ要件
										if (rikisidata[ia].jikosaiko_bandukenameid<=B_saikoui || makuutiijouzaiisuu[ia]>=B_makuutizaiisuu || juuryouijouzaiisuu[ia]>=B_jyuuryouzaiisuu){
											a_kabushutokuzumiflag=0;//株取得済みの力士かどうか確認
											for (iia=0;iia<106;iia++){//株取得済み力士かどうか確認
												//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
												if (tosiyoridata[iia].keishousha_rikisiid==ia){
													//if (tosiyoridata[iia].shozokuheyaid!=rikisidata[ia].heyaid || (tosiyoridata[iia].shozokuheyaid==rikisidata[ia].heyaid && tosiyoridata[iia].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
														a_kabushutokuzumiflag=1;
													//}
												}
												//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
											}
											//一門内で空き名跡あれば取得処理
											if (a_kabushutokuzumiflag!=1){
												char rikisi_itimonid=0;
												for (iia=0;iia<TOSIYORISUU;iia++){
													if (rikisidata[ia].heyaid==tosiyoridata[iia].shozokuheyaid){
														rikisi_itimonid=tosiyoridata[iia].shozokuitimonid;
														break;
													}
												}
												if (tosiyoridata[ii].shozokuitimonid==rikisi_itimonid){
													//相場確認
													int kabuka=0;
													kabuka=kabusouba();
													if (kabuka<=heyadata[rikisidata[ia].heyaid].hpoint){
														heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
														tosiyoridata[iii].keishousha_rikisiid=ia;
														a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(一門優先処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
														break;
													}else{
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"相場が%dpなので%s部屋の%s(%d才)は年寄株%sを取得できず(一門優先処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
													}
												}
											}
											//優勝経験力士割り込み処理、空き名跡あれば取得処理
											if (a_kabushutokuzumiflag!=1
												&& warikomi_yuushourikisiflag==1
												&& rikisidata[ia].kiroku_yuushoukaisuu>0){//優勝経験あるなら
												//相場確認
												int kabuka=0;
												kabuka=kabusouba()*2;
												heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
												tosiyoridata[iii].keishousha_rikisiid=ia;
												a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(優勝経験力士割り込み処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
												break;
											}
											//人望高い力士割り込み処理、空き名跡あれば取得処理
											if (a_kabushutokuzumiflag!=1
												&& warikomi_jinbou<=jinbou_rikisi[ia]){
												//相場確認
												int kabuka=0;
												kabuka=kabusouba()*2;
												heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
												tosiyoridata[iii].keishousha_rikisiid=ia;
												a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(人望%d以上の力士なので割り込み処理 data/warikomisisuu.csv)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring,
warikomi_jinbou);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
												break;
											}
										}
										ia=temp_rikisiid;	//正常にループをさせるために元に戻す
									}
								}
								//現役力士で取得者なければ借株主が取得
								if (tosiyoridata[iii].keishousha_rikisiid==-1 && tosiyoridata[iii].shozokuheyaid!=-1){
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の元%sの%s親方は借株状態を解消するため完全取得(一門内現役力士で取得者なかったため)\n",
heyastring[tosiyoridata[iii].shozokuheyaid],
tosiyoridata[iii].sikona,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の元%sの%s親方は借株状態を解消するため完全取得",
heyastring[tosiyoridata[iii].shozokuheyaid],
tosiyoridata[iii].sikona,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								}
								break;
							}
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
						break;
					}
				}
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			//所属部屋の部屋付親方から年寄株を譲渡してもらう処理、他の株をすでに取得していたら手放す処理も同時に
			if (kabushutokuzumiflag!=1){
				for (ii=0;ii<106;ii++){//まだ年寄株譲渡してない師匠か確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid 
					&& tosiyoridata[ii].sishouflag==0 
					&& tosiyoridata[ii].keishousha_rikisiid==-1 
					&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						if(tosiyoridata[ii].age >= 60 
						&& rikisidata[i].age_roukastart<rikisidata[i].age){//ここに老化開始年齢と師匠の引退年齢との比較による絞込み
							tosiyoridata[ii].keishousha_rikisiid=i;
							kabushutokuzumiflag=1;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s部屋の%s(%d才)が部屋付の%s(%d才)親方から年寄株%sを譲渡される\n",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	rikisidata[i].age,
	tosiyoridata[ii].namestring,
	tosiyoridata[ii].age,
	tosiyoridata[ii].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が部屋付の%s(%d才)親方から年寄株%sを譲渡される",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	rikisidata[i].age,
	tosiyoridata[ii].namestring,
	tosiyoridata[ii].age,
	tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							//他の株を取得していたら手放す処理
							for (iii=0;iii<106;iii++){
								if (tosiyoridata[iii].keishousha_rikisiid==i 
								&& iii!=ii){
									tosiyoridata[iii].keishousha_rikisiid=-1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[iii]=1;
//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s部屋の%sは保有していた年寄株%sを手放す\n",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	tosiyoridata[iii].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%sは保有していた年寄株%sを手放す",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
									//現役力士取得処理
									{
										int temp_rikisiid=0;
										char a_kabushutokuzumiflag=0;
										int ia=0;
										int iia=0;
										int warikomi_yuushourikisiflag=0;
										int warikomi_jinbou=0;
										char temp_string_kakuritu[301];
										char ch=0;
										int kazu=0;
										for (iia=0;iia<301;iia++){
											temp_string_kakuritu[iia]=0;
										}
										FILE *fpcsv;
										if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										strcpy(temp_filename,"data/warikomisisuu.csv");
										fpcsv = fopen(temp_filename,"r");
										if( fpcsv == NULL ){
											fclose(fpcsv);
											fpcsv = fopen(temp_filename,"w");
											fprintf(fpcsv,"現役力士一門内株取得に一門外優勝力士を割り込ませるか、(1だと割り込み)\n");
											fprintf(fpcsv,"0\n");
											fprintf(fpcsv,"現役力士一門内株取得に人望で一門外力士を割込み(下の値以上だと割り込み)\n");
											fprintf(fpcsv,"10000\n");
											if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
											fclose(fpcsv);
											fpcsv = fopen(temp_filename,"r");
										}
										kazu=0;
										ch=1;
										while(1) 
										{
											for (iia=0;iia<301;iia++){
												temp_string_kakuritu[iia]=0;
											}
											if (ch == EOF){break;}
											for (iia=0;iia<300;iia++){
												ch = fgetc(fpcsv);
												if (ch == EOF){break;}
												if(ch == '\n'){
													break;
												}else{
													if(ch=='0'){
														strcat(temp_string_kakuritu,"0");
													}else if(ch=='1'){
														strcat(temp_string_kakuritu,"1");
													}else if(ch=='2'){
														strcat(temp_string_kakuritu,"2");
													}else if(ch=='3'){
														strcat(temp_string_kakuritu,"3");
													}else if(ch=='4'){
														strcat(temp_string_kakuritu,"4");
													}else if(ch=='5'){
														strcat(temp_string_kakuritu,"5");
													}else if(ch=='6'){
														strcat(temp_string_kakuritu,"6");
													}else if(ch=='7'){
														strcat(temp_string_kakuritu,"7");
													}else if(ch=='8'){
														strcat(temp_string_kakuritu,"8");
													}else if(ch=='9'){
														strcat(temp_string_kakuritu,"9");
													}
												}
											}
											if (kazu==1){
												warikomi_yuushourikisiflag=atoi(temp_string_kakuritu);
											}else if(kazu==3){
												warikomi_jinbou=atoi(temp_string_kakuritu);
											}
											kazu++;
											//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										}
										fclose(fpcsv);
										if( ProcessMessage() == -1 ){mode=1;return ;}
										for (ia=0;ia<RIKISISUU;ia++){
											temp_rikisiid=ia;	//このループの最後で逆代入
											ia=jinboujun_rikisiid[ia];
											//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
											//Aカテ・Ｂカテ要件
											if (rikisidata[ia].jikosaiko_bandukenameid<=B_saikoui || makuutiijouzaiisuu[ia]>=B_makuutizaiisuu || juuryouijouzaiisuu[ia]>=B_jyuuryouzaiisuu){
												a_kabushutokuzumiflag=0;//株取得済みの力士かどうか確認
												for (iia=0;iia<106;iia++){//株取得済み力士かどうか確認
													//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
													if (tosiyoridata[iia].keishousha_rikisiid==ia){
														//if (tosiyoridata[iia].shozokuheyaid!=rikisidata[ia].heyaid || (tosiyoridata[iia].shozokuheyaid==rikisidata[ia].heyaid && tosiyoridata[iia].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
															a_kabushutokuzumiflag=1;
														//}
													}
													//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
												}
												//一門内で空き名跡あれば取得処理
												if (kabushutokuzumiflag!=1){
													char rikisi_itimonid=0;
													for (iia=0;iia<TOSIYORISUU;iia++){
														if (rikisidata[ia].heyaid==tosiyoridata[iia].shozokuheyaid){
															rikisi_itimonid=tosiyoridata[iia].shozokuitimonid;
															break;
														}
													}
													if (tosiyoridata[ii].shozokuitimonid==rikisi_itimonid){
														//相場確認
														int kabuka=0;
														kabuka=kabusouba();
														if (kabuka<=heyadata[rikisidata[ia].heyaid].hpoint){
															heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
															tosiyoridata[iii].keishousha_rikisiid=ia;
															a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(一門優先処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
															break;
														}else{
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"相場が%dpなので%s部屋の%s(%d才)は年寄株%sを取得できず(一門優先処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
														}
													}
												}
												//優勝経験力士割り込み処理、空き名跡あれば取得処理
												if (a_kabushutokuzumiflag!=1
													&& warikomi_yuushourikisiflag==1
													&& rikisidata[ia].kiroku_yuushoukaisuu>0){//優勝経験あるなら
													//相場確認
													int kabuka=0;
													kabuka=kabusouba()*2;
													heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
													tosiyoridata[iii].keishousha_rikisiid=ia;
													a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(優勝経験力士割り込み処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
													break;
												}
												//人望高い力士割り込み処理、空き名跡あれば取得処理
												if (a_kabushutokuzumiflag!=1
													&& warikomi_jinbou<=jinbou_rikisi[ia]){
													//相場確認
													int kabuka=0;
													kabuka=kabusouba()*2;
													heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
													tosiyoridata[iii].keishousha_rikisiid=ia;
													a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(人望%d以上の力士なので割り込み処理 data/warikomisisuu.csv)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring,
warikomi_jinbou);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
													break;
												}
											}
											ia=temp_rikisiid;	//正常にループをさせるために元に戻す
										}
									}
									//現役力士で取得者なければ借株主が取得
									if (tosiyoridata[iii].keishousha_rikisiid==-1 && tosiyoridata[iii].shozokuheyaid!=-1){
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の元%sの%s親方は借株状態を解消するため完全取得(一門内現役力士で取得者なかったため)\n",
heyastring[tosiyoridata[iii].shozokuheyaid],
tosiyoridata[iii].sikona,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の元%sの%s親方は借株状態を解消するため完全取得",
heyastring[tosiyoridata[iii].shozokuheyaid],
tosiyoridata[iii].sikona,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
									}
									break;
								}
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							}
							break;
						}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
		//Bカテ要件
		}else if (rikisidata[i].jikosaiko_bandukenameid<=B_saikoui || makuutiijouzaiisuu[i]>=B_makuutizaiisuu || juuryouijouzaiisuu[i]>=B_jyuuryouzaiisuu){
			kabushutokuzumiflag=0;//株取得済みの力士かどうか確認
			for (ii=0;ii<106;ii++){//株取得済み力士かどうか確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].keishousha_rikisiid==i){
					//if (tosiyoridata[ii].shozokuheyaid!=rikisidata[i].heyaid || (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid && tosiyoridata[ii].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
						kabushutokuzumiflag=1;
						break;
					//}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			//まだ継承者がいないなら所属部屋の師匠から継承者指名してもらう処理、他の株をすでに取得していたら手放す処理も同時に
			for (ii=0;ii<106;ii++){//まだ継承者指名してない師匠か確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid 
				&& tosiyoridata[ii].sishouflag==1 
				&& tosiyoridata[ii].keishousha_rikisiid==-1 
				&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
					if(tosiyoridata[ii].age >= 60 
					&& rikisidata[i].age_roukastart<rikisidata[i].age){//ここに老化開始年齢と師匠の引退年齢との比較による絞込み
						tosiyoridata[ii].keishousha_rikisiid=i;
						kabushutokuzumiflag=1;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才)が師匠の%s(%d才)親方から後継者として指名される\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が師匠の%s(%d才)親方から後継者として指名される",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						//他の株を取得していたら手放す処理
						for (iii=0;iii<106;iii++){
							if (tosiyoridata[iii].keishousha_rikisiid==i 
							&& iii!=ii){
								tosiyoridata[iii].keishousha_rikisiid=-1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[iii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%sは保有していた年寄株%sを手放す\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%sは保有していた年寄株%sを手放す",
heyastring[rikisidata[i].heyaid],
namestring[i],
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								//現役力士取得処理
								{
									int temp_rikisiid=0;
									char a_kabushutokuzumiflag=0;
									int ia=0;
									int iia=0;
									int warikomi_yuushourikisiflag=0;
									int warikomi_jinbou=0;
									char temp_string_kakuritu[301];
									char ch=0;
									int kazu=0;
									for (iia=0;iia<301;iia++){
										temp_string_kakuritu[iia]=0;
									}
									FILE *fpcsv;
									if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									strcpy(temp_filename,"data/warikomisisuu.csv");
									fpcsv = fopen(temp_filename,"r");
									if( fpcsv == NULL ){
										fclose(fpcsv);
										fpcsv = fopen(temp_filename,"w");
										fprintf(fpcsv,"現役力士一門内株取得に一門外優勝力士を割り込ませるか、(1だと割り込み)\n");
										fprintf(fpcsv,"0\n");
										fprintf(fpcsv,"現役力士一門内株取得に人望で一門外力士を割込み(下の値以上だと割り込み)\n");
										fprintf(fpcsv,"10000\n");
										if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										fclose(fpcsv);
										fpcsv = fopen(temp_filename,"r");
									}
									kazu=0;
									ch=1;
									while(1) 
									{
										for (iia=0;iia<301;iia++){
											temp_string_kakuritu[iia]=0;
										}
										if (ch == EOF){break;}
										for (iia=0;iia<300;iia++){
											ch = fgetc(fpcsv);
											if (ch == EOF){break;}
											if(ch == '\n'){
												break;
											}else{
												if(ch=='0'){
													strcat(temp_string_kakuritu,"0");
												}else if(ch=='1'){
													strcat(temp_string_kakuritu,"1");
												}else if(ch=='2'){
													strcat(temp_string_kakuritu,"2");
												}else if(ch=='3'){
													strcat(temp_string_kakuritu,"3");
												}else if(ch=='4'){
													strcat(temp_string_kakuritu,"4");
												}else if(ch=='5'){
													strcat(temp_string_kakuritu,"5");
												}else if(ch=='6'){
													strcat(temp_string_kakuritu,"6");
												}else if(ch=='7'){
													strcat(temp_string_kakuritu,"7");
												}else if(ch=='8'){
													strcat(temp_string_kakuritu,"8");
												}else if(ch=='9'){
													strcat(temp_string_kakuritu,"9");
												}
											}
										}
										if (kazu==1){
											warikomi_yuushourikisiflag=atoi(temp_string_kakuritu);
										}else if(kazu==3){
											warikomi_jinbou=atoi(temp_string_kakuritu);
										}
										kazu++;
										//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									}
									fclose(fpcsv);
									if( ProcessMessage() == -1 ){mode=1;return ;}
									for (ia=0;ia<RIKISISUU;ia++){
										temp_rikisiid=ia;	//このループの最後で逆代入
										ia=jinboujun_rikisiid[ia];
										//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										//Aカテ・Ｂカテ要件
										if (rikisidata[ia].jikosaiko_bandukenameid<=B_saikoui || makuutiijouzaiisuu[ia]>=B_makuutizaiisuu || juuryouijouzaiisuu[ia]>=B_jyuuryouzaiisuu){
											a_kabushutokuzumiflag=0;//株取得済みの力士かどうか確認
											for (iia=0;iia<106;iia++){//株取得済み力士かどうか確認
												//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
												if (tosiyoridata[iia].keishousha_rikisiid==ia){
													//if (tosiyoridata[iia].shozokuheyaid!=rikisidata[ia].heyaid || (tosiyoridata[iia].shozokuheyaid==rikisidata[ia].heyaid && tosiyoridata[iia].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
														a_kabushutokuzumiflag=1;
													//}
												}
												//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
											}
											//一門内で空き名跡あれば取得処理
											if (a_kabushutokuzumiflag!=1){
												char rikisi_itimonid=0;
												for (iia=0;iia<TOSIYORISUU;iia++){
													if (rikisidata[ia].heyaid==tosiyoridata[iia].shozokuheyaid){
														rikisi_itimonid=tosiyoridata[iia].shozokuitimonid;
														break;
													}
												}
												if (tosiyoridata[ii].shozokuitimonid==rikisi_itimonid){
													//相場確認
													int kabuka=0;
													kabuka=kabusouba();
													if (kabuka<=heyadata[rikisidata[ia].heyaid].hpoint){
														heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
														tosiyoridata[iii].keishousha_rikisiid=ia;
														a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(一門優先処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
														break;
													}else{
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"相場が%dpなので%s部屋の%s(%d才)は年寄株%sを取得できず(一門優先処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
													}
												}
											}
											//優勝経験力士割り込み処理、空き名跡あれば取得処理
											if (a_kabushutokuzumiflag!=1
												&& warikomi_yuushourikisiflag==1
												&& rikisidata[ia].kiroku_yuushoukaisuu>0){//優勝経験あるなら
												//相場確認
												int kabuka=0;
												kabuka=kabusouba()*2;
												heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
												tosiyoridata[iii].keishousha_rikisiid=ia;
												a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(優勝経験力士割り込み処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
												break;
											}
											//人望高い力士割り込み処理、空き名跡あれば取得処理
											if (a_kabushutokuzumiflag!=1
												&& warikomi_jinbou<=jinbou_rikisi[ia]){
												//相場確認
												int kabuka=0;
												kabuka=kabusouba()*2;
												heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
												tosiyoridata[iii].keishousha_rikisiid=ia;
												a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(人望%d以上の力士なので割り込み処理 data/warikomisisuu.csv)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring,
warikomi_jinbou);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
												break;
											}
										}
										ia=temp_rikisiid;	//正常にループをさせるために元に戻す
									}
								}
								//現役力士で取得者なければ借株主が取得
								if (tosiyoridata[iii].keishousha_rikisiid==-1 && tosiyoridata[iii].shozokuheyaid!=-1){
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の元%sの%s親方は借株状態を解消するため完全取得(一門内現役力士で取得者なかったため)\n",
heyastring[tosiyoridata[iii].shozokuheyaid],
tosiyoridata[iii].sikona,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の元%sの%s親方は借株状態を解消するため完全取得",
heyastring[tosiyoridata[iii].shozokuheyaid],
tosiyoridata[iii].sikona,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								}
								break;
							}
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
						break;
					}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			//所属部屋の部屋付親方から年寄株を譲渡してもらう処理、他の株をすでに取得していたら手放す処理も同時に
			if (kabushutokuzumiflag!=1){
				for (ii=0;ii<106;ii++){//まだ年寄株譲渡してない師匠か確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid 
					&& tosiyoridata[ii].sishouflag==0 
					&& tosiyoridata[ii].keishousha_rikisiid==-1 
					&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						if(tosiyoridata[ii].age >= 60 
						&& rikisidata[i].age_roukastart<rikisidata[i].age){//ここに老化開始年齢と師匠の引退年齢との比較による絞込み
							tosiyoridata[ii].keishousha_rikisiid=i;
							kabushutokuzumiflag=1;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s部屋の%s(%d才)が部屋付の%s(%d才)親方から年寄株%sを譲渡される\n",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	rikisidata[i].age,
	tosiyoridata[ii].namestring,
	tosiyoridata[ii].age,
	tosiyoridata[ii].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が部屋付の%s(%d才)親方から年寄株%sを譲渡される",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	rikisidata[i].age,
	tosiyoridata[ii].namestring,
	tosiyoridata[ii].age,
	tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							//他の株を取得していたら手放す処理
							for (iii=0;iii<106;iii++){
								if (tosiyoridata[iii].keishousha_rikisiid==i 
								&& iii!=ii){
									tosiyoridata[iii].keishousha_rikisiid=-1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[iii]=1;
//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s部屋の%sは保有していた年寄株%sを手放す\n",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	tosiyoridata[iii].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%sは保有していた年寄株%sを手放す",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
									//現役力士取得処理
									{
										int temp_rikisiid=0;
										char a_kabushutokuzumiflag=0;
										int ia=0;
										int iia=0;
										int warikomi_yuushourikisiflag=0;
										int warikomi_jinbou=0;
										char temp_string_kakuritu[301];
										char ch=0;
										int kazu=0;
										for (iia=0;iia<301;iia++){
											temp_string_kakuritu[iia]=0;
										}
										FILE *fpcsv;
										if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										strcpy(temp_filename,"data/warikomisisuu.csv");
										fpcsv = fopen(temp_filename,"r");
										if( fpcsv == NULL ){
											fclose(fpcsv);
											fpcsv = fopen(temp_filename,"w");
											fprintf(fpcsv,"現役力士一門内株取得に一門外優勝力士を割り込ませるか、(1だと割り込み)\n");
											fprintf(fpcsv,"0\n");
											fprintf(fpcsv,"現役力士一門内株取得に人望で一門外力士を割込み(下の値以上だと割り込み)\n");
											fprintf(fpcsv,"10000\n");
											if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
											fclose(fpcsv);
											fpcsv = fopen(temp_filename,"r");
										}
										kazu=0;
										ch=1;
										while(1) 
										{
											for (iia=0;iia<301;iia++){
												temp_string_kakuritu[iia]=0;
											}
											if (ch == EOF){break;}
											for (iia=0;iia<300;iia++){
												ch = fgetc(fpcsv);
												if (ch == EOF){break;}
												if(ch == '\n'){
													break;
												}else{
													if(ch=='0'){
														strcat(temp_string_kakuritu,"0");
													}else if(ch=='1'){
														strcat(temp_string_kakuritu,"1");
													}else if(ch=='2'){
														strcat(temp_string_kakuritu,"2");
													}else if(ch=='3'){
														strcat(temp_string_kakuritu,"3");
													}else if(ch=='4'){
														strcat(temp_string_kakuritu,"4");
													}else if(ch=='5'){
														strcat(temp_string_kakuritu,"5");
													}else if(ch=='6'){
														strcat(temp_string_kakuritu,"6");
													}else if(ch=='7'){
														strcat(temp_string_kakuritu,"7");
													}else if(ch=='8'){
														strcat(temp_string_kakuritu,"8");
													}else if(ch=='9'){
														strcat(temp_string_kakuritu,"9");
													}
												}
											}
											if (kazu==1){
												warikomi_yuushourikisiflag=atoi(temp_string_kakuritu);
											}else if(kazu==3){
												warikomi_jinbou=atoi(temp_string_kakuritu);
											}
											kazu++;
											//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										}
										fclose(fpcsv);
										if( ProcessMessage() == -1 ){mode=1;return ;}
										for (ia=0;ia<RIKISISUU;ia++){
											temp_rikisiid=ia;	//このループの最後で逆代入
											ia=jinboujun_rikisiid[ia];
											//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
											//Aカテ・Ｂカテ要件
											if (rikisidata[ia].jikosaiko_bandukenameid<=B_saikoui || makuutiijouzaiisuu[ia]>=B_makuutizaiisuu || juuryouijouzaiisuu[ia]>=B_jyuuryouzaiisuu){
												a_kabushutokuzumiflag=0;//株取得済みの力士かどうか確認
												for (iia=0;iia<106;iia++){//株取得済み力士かどうか確認
													//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
													if (tosiyoridata[iia].keishousha_rikisiid==ia){
														//if (tosiyoridata[iia].shozokuheyaid!=rikisidata[ia].heyaid || (tosiyoridata[iia].shozokuheyaid==rikisidata[ia].heyaid && tosiyoridata[iia].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
															a_kabushutokuzumiflag=1;
														//}
													}
													//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
												}
												//一門内で空き名跡あれば取得処理
												if (a_kabushutokuzumiflag!=1){
													char rikisi_itimonid=0;
													for (iia=0;iia<TOSIYORISUU;iia++){
														if (rikisidata[ia].heyaid==tosiyoridata[iia].shozokuheyaid){
															rikisi_itimonid=tosiyoridata[iia].shozokuitimonid;
															break;
														}
													}
													if (tosiyoridata[ii].shozokuitimonid==rikisi_itimonid){
														//相場確認
														int kabuka=0;
														kabuka=kabusouba();
														if (kabuka<=heyadata[rikisidata[ia].heyaid].hpoint){
															heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
															tosiyoridata[iii].keishousha_rikisiid=ia;
															a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(一門優先処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
															break;
														}else{
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"相場が%dpなので%s部屋の%s(%d才)は年寄株%sを取得できず(一門優先処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
														}
													}
												}
												//優勝経験力士割り込み処理、空き名跡あれば取得処理
												if (a_kabushutokuzumiflag!=1
													&& warikomi_yuushourikisiflag==1
													&& rikisidata[ia].kiroku_yuushoukaisuu>0){//優勝経験あるなら
													//相場確認
													int kabuka=0;
													kabuka=kabusouba()*2;
													heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
													tosiyoridata[iii].keishousha_rikisiid=ia;
													a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(優勝経験力士割り込み処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
													break;
												}
												//人望高い力士割り込み処理、空き名跡あれば取得処理
												if (a_kabushutokuzumiflag!=1
													&& warikomi_jinbou<=jinbou_rikisi[ia]){
													//相場確認
													int kabuka=0;
													kabuka=kabusouba()*2;
													heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
													tosiyoridata[iii].keishousha_rikisiid=ia;
													a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(人望%d以上の力士なので割り込み処理 data/warikomisisuu.csv)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring,
warikomi_jinbou);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
													break;
												}
											}
											ia=temp_rikisiid;	//正常にループをさせるために元に戻す
										}
									}
									//現役力士で取得者なければ借株主が取得
									if (tosiyoridata[iii].keishousha_rikisiid==-1 && tosiyoridata[iii].shozokuheyaid!=-1){
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の元%sの%s親方は借株状態を解消するため完全取得(一門内現役力士で取得者なかったため)\n",
heyastring[tosiyoridata[iii].shozokuheyaid],
tosiyoridata[iii].sikona,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の元%sの%s親方は借株状態を解消するため完全取得",
heyastring[tosiyoridata[iii].shozokuheyaid],
tosiyoridata[iii].sikona,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
									}
									break;
								}
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							}
							break;
						}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
		//Cカテ要件
		}else if (makuutiijouzaiisuu[i]>=C_makuutizaiisuu || juuryouijouzaiisuu[i]>=C_jyuuryouzaiisuu){
			//まだ継承者がいないなら所属部屋の師匠から継承者指名してもらう処理
			for (ii=0;ii<106;ii++){//まだ継承者指名してない師匠か確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid 
				&& tosiyoridata[ii].sishouflag==1 
				&& tosiyoridata[ii].keishousha_rikisiid==-1 
				&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
					if(tosiyoridata[ii].age >= 60 
					&& rikisidata[i].age_roukastart<rikisidata[i].age){//ここに老化開始年齢と師匠の引退年齢との比較による絞込み
						tosiyoridata[ii].keishousha_rikisiid=i;
						kabushutokuzumiflag=1;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才)が師匠の%s(%d才)親方から後継者として指名される\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が師匠の%s(%d才)親方から後継者として指名される",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						//他の株を取得していたら手放す処理（Cカテだからないとは思うけど念のため）
						for (iii=0;iii<106;iii++){
							if (tosiyoridata[iii].keishousha_rikisiid==i 
							&& iii!=ii){
								tosiyoridata[iii].keishousha_rikisiid=-1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[iii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%sは保有していた年寄株%sを手放す\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%sは保有していた年寄株%sを手放す",
heyastring[rikisidata[i].heyaid],
namestring[i],
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								//現役力士取得処理
								{
									int temp_rikisiid=0;
									char a_kabushutokuzumiflag=0;
									int ia=0;
									int iia=0;
									int warikomi_yuushourikisiflag=0;
									int warikomi_jinbou=0;
									char temp_string_kakuritu[301];
									char ch=0;
									int kazu=0;
									for (iia=0;iia<301;iia++){
										temp_string_kakuritu[iia]=0;
									}
									FILE *fpcsv;
									if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									strcpy(temp_filename,"data/warikomisisuu.csv");
									fpcsv = fopen(temp_filename,"r");
									if( fpcsv == NULL ){
										fclose(fpcsv);
										fpcsv = fopen(temp_filename,"w");
										fprintf(fpcsv,"現役力士一門内株取得に一門外優勝力士を割り込ませるか、(1だと割り込み)\n");
										fprintf(fpcsv,"0\n");
										fprintf(fpcsv,"現役力士一門内株取得に人望で一門外力士を割込み(下の値以上だと割り込み)\n");
										fprintf(fpcsv,"10000\n");
										if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										fclose(fpcsv);
										fpcsv = fopen(temp_filename,"r");
									}
									kazu=0;
									ch=1;
									while(1) 
									{
										for (iia=0;iia<301;iia++){
											temp_string_kakuritu[iia]=0;
										}
										if (ch == EOF){break;}
										for (iia=0;iia<300;iia++){
											ch = fgetc(fpcsv);
											if (ch == EOF){break;}
											if(ch == '\n'){
												break;
											}else{
												if(ch=='0'){
													strcat(temp_string_kakuritu,"0");
												}else if(ch=='1'){
													strcat(temp_string_kakuritu,"1");
												}else if(ch=='2'){
													strcat(temp_string_kakuritu,"2");
												}else if(ch=='3'){
													strcat(temp_string_kakuritu,"3");
												}else if(ch=='4'){
													strcat(temp_string_kakuritu,"4");
												}else if(ch=='5'){
													strcat(temp_string_kakuritu,"5");
												}else if(ch=='6'){
													strcat(temp_string_kakuritu,"6");
												}else if(ch=='7'){
													strcat(temp_string_kakuritu,"7");
												}else if(ch=='8'){
													strcat(temp_string_kakuritu,"8");
												}else if(ch=='9'){
													strcat(temp_string_kakuritu,"9");
												}
											}
										}
										if (kazu==1){
											warikomi_yuushourikisiflag=atoi(temp_string_kakuritu);
										}else if(kazu==3){
											warikomi_jinbou=atoi(temp_string_kakuritu);
										}
										kazu++;
										//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									}
									fclose(fpcsv);
									if( ProcessMessage() == -1 ){mode=1;return ;}
									for (ia=0;ia<RIKISISUU;ia++){
										temp_rikisiid=ia;	//このループの最後で逆代入
										ia=jinboujun_rikisiid[ia];
										//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										//Aカテ・Ｂカテ要件
										if (rikisidata[ia].jikosaiko_bandukenameid<=B_saikoui || makuutiijouzaiisuu[ia]>=B_makuutizaiisuu || juuryouijouzaiisuu[ia]>=B_jyuuryouzaiisuu){
											a_kabushutokuzumiflag=0;//株取得済みの力士かどうか確認
											for (iia=0;iia<106;iia++){//株取得済み力士かどうか確認
												//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
												if (tosiyoridata[iia].keishousha_rikisiid==ia){
													//if (tosiyoridata[iia].shozokuheyaid!=rikisidata[ia].heyaid || (tosiyoridata[iia].shozokuheyaid==rikisidata[ia].heyaid && tosiyoridata[iia].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
														a_kabushutokuzumiflag=1;
													//}
												}
												//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
											}
											//一門内で空き名跡あれば取得処理
											if (a_kabushutokuzumiflag!=1){
												char rikisi_itimonid=0;
												for (iia=0;iia<TOSIYORISUU;iia++){
													if (rikisidata[ia].heyaid==tosiyoridata[iia].shozokuheyaid){
														rikisi_itimonid=tosiyoridata[iia].shozokuitimonid;
														break;
													}
												}
												if (tosiyoridata[ii].shozokuitimonid==rikisi_itimonid){
													//相場確認
													int kabuka=0;
													kabuka=kabusouba();
													if (kabuka<=heyadata[rikisidata[ia].heyaid].hpoint){
														heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
														tosiyoridata[iii].keishousha_rikisiid=ia;
														a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(一門優先処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
														break;
													}else{
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"相場が%dpなので%s部屋の%s(%d才)は年寄株%sを取得できず(一門優先処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
													}
												}
											}
											//優勝経験力士割り込み処理、空き名跡あれば取得処理
											if (a_kabushutokuzumiflag!=1
												&& warikomi_yuushourikisiflag==1
												&& rikisidata[ia].kiroku_yuushoukaisuu>0){//優勝経験あるなら
												//相場確認
												int kabuka=0;
												kabuka=kabusouba()*2;
												heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
												tosiyoridata[iii].keishousha_rikisiid=ia;
												a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(優勝経験力士割り込み処理)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
												break;
											}
											//人望高い力士割り込み処理、空き名跡あれば取得処理
											if (a_kabushutokuzumiflag!=1
												&& warikomi_jinbou<=jinbou_rikisi[ia]){
												//相場確認
												int kabuka=0;
												kabuka=kabusouba()*2;
												heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
												tosiyoridata[iii].keishousha_rikisiid=ia;
												a_kabushutokuzumiflag=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(人望%d以上の力士なので割り込み処理 data/warikomisisuu.csv)\n",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring,
warikomi_jinbou);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[ia].heyaid],
namestring[ia],
rikisidata[ia].age,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
												break;
											}
										}
										ia=temp_rikisiid;	//正常にループをさせるために元に戻す
									}
								}
								//現役力士で取得者なければ借株主が取得
								if (tosiyoridata[iii].keishousha_rikisiid==-1 && tosiyoridata[iii].shozokuheyaid!=-1){
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の元%sの%s親方は借株状態を解消するため完全取得(一門内現役力士で取得者なかったため)\n",
heyastring[tosiyoridata[iii].shozokuheyaid],
tosiyoridata[iii].sikona,
tosiyoridata[iii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の元%sの%s親方は借株状態を解消するため完全取得",
heyastring[tosiyoridata[iii].shozokuheyaid],
tosiyoridata[iii].sikona,
tosiyoridata[iii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								}
								break;
							}
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
						break;
					}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
		}
		i=temp_rikisiid;	//正常にループをさせるために元に戻す
	}

	//人望順年寄IDを検索
	//バブルソート
	for (i=0;i<TOSIYORISUU;i++){
		temp_narabekaeyou[i]=0;
		temp_narabekaeyou[i]=tosiyoridata[i].jinbou;
		jinboujun_tosiyoriid[i]=0;
		jinboujun_tosiyoriid[i]=i;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (i = 0;i < TOSIYORISUU - 1;i++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}


	//年寄定年処理
	//年寄最後の一人の場合は、部屋数が38までなら部屋をつぶせる
	//for (i=0;i<TOSIYORISUU;i++){
	//for (i=0;i<106;i++){
	for (i=0;i<300;i++){//期間限定一代年寄は除く
if (i<106 || i>=200){//106～199は使用しないので
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//定年
		if (tosiyoridata[i].age>=TOSIYORI_RETIREAGE && tosiyoridata[i].shozokuheyaid>=0){
			//年寄2人以上いる部屋
			if (heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]>1){
				//もし定年退職年寄が師匠で通常年寄（功績顕著一代年寄でない）なら
				if (tosiyoridata[i].sishouflag==1 && i<106){
					//継承者指名の年寄（主に一代年寄かな）がいたらその年寄に年寄株を譲り師匠になってもらう処理
					if (tosiyoridata[i].keishousha_tosiyoriid!=-1){
						for (ii=0;ii<TOSIYORISUU;ii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							if (tosiyoridata[i].keishousha_tosiyoriid==ii){
								heya_tosiyorisuu[tosiyoridata[ii].shozokuheyaid]--;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋師匠で元%sの%s親方(%d才)が退職。\n元%sの%s親方(%d才)が%s部屋を継承\n",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
tosiyoridata[i].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋師匠で元%sの%s親方(%d才)が退職。",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
DrawFormatString(0,369+16,CRWHITE,"元%sの%s親方(%d才)が%s部屋を継承",
//heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
tosiyoridata[i].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								tosiyoridata[ii].shozokuheyaid=-1;
								//tosiyoridata[ii].shozokuitimonid=-1;
								tosiyoridata[i].age=tosiyoridata[ii].age;
								if (tosiyoridata[ii].category>=4){//一代年寄ならAカテクリアしているので
									tosiyoridata[i].category=1;
								}else{
									tosiyoridata[i].category=tosiyoridata[ii].category;
								}
								tosiyoridata[i].startyear=year;
								//tosiyoridata[i].shozokuheyaidはそのまま
								//tosiyoridata[i].shozokuitimonidもそのまま
								tosiyoridata[i].jinbou=tosiyoridata[ii].jinbou;
								tosiyoridata[i].rijiflag=tosiyoridata[ii].rijiflag;
								tosiyoridata[i].rikisiid=tosiyoridata[ii].rikisiid;
								strcpy(tosiyoridata[i].sikona,tosiyoridata[ii].sikona);
								tosiyoridata[i].sishouflag=1;
								//tosiyoridata[i].namestirngはもちろんそのまま
								tosiyoridata[i].keishousha_tosiyoriid=-1;
								tosiyoridata[i].keishousha_rikisiid=-1;
								//リセット処理	
								tosiyoridata[ii].age=0;
								tosiyoridata[ii].category=0;
								tosiyoridata[ii].startyear=0;
								tosiyoridata[ii].rikisiid=-1;
								strcpy(tosiyoridata[ii].sikona,"\0");
								tosiyoridata[ii].sishouflag=0;
								if (ii>=200){
									strcpy(tosiyoridata[ii].namestring,"\0");
								}
								tosiyoridata[ii].jinbou=0;
								tosiyoridata[ii].rijiflag=0;
								//tosiyoridata[ii].keishousha_rikisiid=-1;
								//tosiyoridata[ii].keishousha_tosiyoriid=-1;
								break;
							}
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
					//継承者指名の現役力士がいたら、とりあえず定年延長で逃げることにした
					}else if (tosiyoridata[i].keishousha_rikisiid!=-1){

//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋師匠で元%sの%s親方(%d才)は定年延長(継承者指名の現役力士引退待ち)\n",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
//tosiyoridata[ii].sikona,
//tosiyoridata[ii].namestring,
//tosiyoridata[i].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋師匠で元%sの%s親方(%d才)は定年延長(継承者指名の現役力士引退待ち)",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
//tosiyoridata[ii].sikona,
//tosiyoridata[ii].namestring,
//tosiyoridata[i].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
					//継承者指名なければ部屋付を師匠に
					}else{
						//人望順年寄IDを検索
						//バブルソート
						for (iii=0;iii<TOSIYORISUU;iii++){
							temp_narabekaeyou[iii]=0;
							temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
							jinboujun_tosiyoriid[iii]=0;
							jinboujun_tosiyoriid[iii]=iii;
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
						for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
							for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
								if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
									temp_tosiyoriid = temp_narabekaeyou[ii];
									temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
									temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
									temp_tosiyoriid = jinboujun_tosiyoriid[ii];
									jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
									jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
								}
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							}
						}
						//部屋付を師匠にする処理
						taishokuzumiflag=0;
						for (ii=0;ii<TOSIYORISUU;ii++){
							heyatukiid=jinboujun_tosiyoriid[ii];
						//for (ii=0;ii<106;ii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							if (i!=heyatukiid && tosiyoridata[i].shozokuheyaid==tosiyoridata[heyatukiid].shozokuheyaid 
							//&& tosiyoridata[heyatukiid].keishousha_rikisiid==-1 //レンタル年寄も参戦することにしたのでコメントアウト
							&& (tosiyoridata[heyatukiid].category<=2 || tosiyoridata[heyatukiid].category>=5)
							&& (heyatukiid<106 || heyatukiid>=300) ){//通常年寄か期間限定一代年寄の昇格
								heya_tosiyorisuu[tosiyoridata[heyatukiid].shozokuheyaid]--;
								taishokuzumiflag=1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[heyatukiid]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋師匠で元%sの%s親方(%d才)が退職。\n元%sの%s親方(%d才)が%s部屋を継承\n",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[heyatukiid].sikona,
tosiyoridata[heyatukiid].namestring,
tosiyoridata[heyatukiid].age,
tosiyoridata[i].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋師匠で元%sの%s親方(%d才)が退職。",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
DrawFormatString(0,369+16,CRWHITE,"元%sの%s親方(%d才)が%s部屋を継承",
//heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[heyatukiid].sikona,
tosiyoridata[heyatukiid].namestring,
tosiyoridata[heyatukiid].age,
tosiyoridata[i].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								tosiyoridata[heyatukiid].shozokuheyaid=-1;
								//tosiyoridata[heyatukiid].shozokuitimonid=-1;
								tosiyoridata[i].age=tosiyoridata[heyatukiid].age;
								if (tosiyoridata[heyatukiid].category>=4){//一代年寄ならAカテクリアしているので
									tosiyoridata[i].category=1;
								}else{
									tosiyoridata[i].category=tosiyoridata[heyatukiid].category;
								}
								tosiyoridata[i].startyear=year;
								//tosiyoridata[i].shozokuheyaidはそのまま
								//tosiyoridata[i].shozokuitimonidもそのまま
								tosiyoridata[i].jinbou=tosiyoridata[heyatukiid].jinbou;
								tosiyoridata[i].rijiflag=tosiyoridata[heyatukiid].rijiflag;
								tosiyoridata[i].rikisiid=tosiyoridata[heyatukiid].rikisiid;
								strcpy(tosiyoridata[i].sikona,tosiyoridata[heyatukiid].sikona);
								tosiyoridata[i].sishouflag=1;
								//tosiyoridata[i].namestirngはもちろんそのまま
								//tosiyoridata[i].keishousha_tosiyoriidそのまま-1
								//tosiyoridata[i].keishousha_rikisiidそのまま-1
								//リセット処理	
								tosiyoridata[heyatukiid].age=0;
								tosiyoridata[heyatukiid].category=0;
								tosiyoridata[heyatukiid].startyear=0;
								tosiyoridata[heyatukiid].rikisiid=-1;
								strcpy(tosiyoridata[heyatukiid].sikona,"\0");
								tosiyoridata[heyatukiid].sishouflag=0;
								if (heyatukiid>=200){
									strcpy(tosiyoridata[heyatukiid].namestring,"\0");
								}
								tosiyoridata[heyatukiid].jinbou=0;
								tosiyoridata[heyatukiid].rijiflag=0;
								//tosiyoridata[heyatukiid].keishousha_rikisiid=-1;
								//tosiyoridata[heyatukiid].keishousha_tosiyoriid=-1;
								break;
							}else if (i!=heyatukiid && tosiyoridata[i].shozokuheyaid==tosiyoridata[heyatukiid].shozokuheyaid 
							&& heyatukiid>=200 && heyatukiid<300){//功績顕著の昇格+部屋名変更
								heya_tosiyorisuu[tosiyoridata[heyatukiid].shozokuheyaid]--;
								taishokuzumiflag=1;
	//記録必要フラグ書込み/////////////
	kirokuhituyouflag_tosiyoriid[i]=1;
	kirokuhituyouflag_tosiyoriid[heyatukiid]=1;
	for (iiiii=0;iiiii<TOSIYORISUU;iiiii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}
		if (tosiyoridata[i].shozokuheyaid==tosiyoridata[iiiii].shozokuheyaid){
			kirokuhituyouflag_tosiyoriid[iiiii]=1;
		}
	}
	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s部屋師匠で元%sの%s親方(%d才)が退職。\n元%sの%s親方(%d才)が部屋を継承、部屋名を%s部屋に変更\n",
	heyastring[tosiyoridata[i].shozokuheyaid],
	tosiyoridata[i].sikona,
	tosiyoridata[i].namestring,
	tosiyoridata[i].age,
	tosiyoridata[heyatukiid].sikona,
	tosiyoridata[heyatukiid].namestring,
	tosiyoridata[heyatukiid].age,
	tosiyoridata[heyatukiid].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋師匠で元%sの%s親方(%d才)が退職。",
	heyastring[tosiyoridata[i].shozokuheyaid],
	tosiyoridata[i].sikona,
	tosiyoridata[i].namestring,
	tosiyoridata[i].age);
	DrawFormatString(0,369+16,CRWHITE,"元%sの%s親方(%d才)が部屋を継承、部屋名を%s部屋に変更",
	//heyastring[tosiyoridata[i].shozokuheyaid],
	tosiyoridata[heyatukiid].sikona,
	tosiyoridata[heyatukiid].namestring,
	tosiyoridata[heyatukiid].age,
	tosiyoridata[heyatukiid].namestring);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	}
	//////////////////////////////////////////////////////////////
								if (itimondata[tosiyoridata[i].shozokuitimonid].shuheyaid==tosiyoridata[i].shozokuheyaid){
									//一門名も変更→人望比較で一門主を決めなおした方が良いと思う
									//引退師匠が主部屋の師匠（一門主）でもあったら同門のなかから人望の一番高い師匠を一門主にする
									//功績顕著一代の昇格の場合、一門の看板を守るため、功績顕著一代を返上することにしたver3.12
									//strcpy(itimondata[tosiyoridata[heyatukiid].shozokuitimonid].namestring,tosiyoridata[temp_tosiyoriid].namestring);
									//itimondata[tosiyoridata[heyatukiid].shozokuitimonid].shuheyaid=tosiyoridata[temp_tosiyoriid].shozokuheyaid;
//ここver3.12で記録必要フラグ書込み内容の変更必要かも
	//記録必要フラグ書込み/////////////
	kirokuhituyouflag_tosiyoriid[i]=1;
	kirokuhituyouflag_tosiyoriid[heyatukiid]=1;
	/*for (iiiii=0;iiiii<TOSIYORISUU;iiiii++){
		if( ProcessMessage() == -1 ){mode=1;return ;}
		if (tosiyoridata[i].shozokuitimonid==tosiyoridata[iiiii].shozokuitimonid){
			kirokuhituyouflag_tosiyoriid[iiiii]=1;
		}
	}*/
	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	//fprintf(fp,"%s一門は名称を%s一門に変更しました\n",
	fprintf(fp,"しようかと思いましたが、一門の看板を守るため、%sを取得襲名し、一代年寄%sを返上しました\n",
	tosiyoridata[i].namestring,
	tosiyoridata[heyatukiid].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString(0,369,"しようかと思いましたが、一門の看板を守るため、",CRWHITE);
	DrawFormatString(0,369+16,CRWHITE,"%sを取得襲名し、一代年寄%sを返上しました",
	tosiyoridata[i].namestring,
	tosiyoridata[heyatukiid].namestring);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	}
	//////////////////////////////////////////////////////////////
									tosiyoridata[heyatukiid].shozokuheyaid=-1;
									//tosiyoridata[heyatukiid].shozokuitimonid=-1;
									tosiyoridata[i].age=tosiyoridata[heyatukiid].age;
									if (tosiyoridata[heyatukiid].category>=4){//一代年寄ならAカテクリアしているので
										tosiyoridata[i].category=1;
									}else{
										tosiyoridata[i].category=tosiyoridata[heyatukiid].category;
									}
									tosiyoridata[i].startyear=year;
									//tosiyoridata[i].shozokuheyaidはそのまま
									//tosiyoridata[i].shozokuitimonidもそのまま
									tosiyoridata[i].jinbou=tosiyoridata[heyatukiid].jinbou;
									tosiyoridata[i].rijiflag=tosiyoridata[heyatukiid].rijiflag;
									tosiyoridata[i].rikisiid=tosiyoridata[heyatukiid].rikisiid;
									strcpy(tosiyoridata[i].sikona,tosiyoridata[heyatukiid].sikona);
									tosiyoridata[i].sishouflag=1;
									//tosiyoridata[i].namestirngはもちろんそのまま
									//tosiyoridata[i].keishousha_tosiyoriidそのまま-1
									//tosiyoridata[i].keishousha_rikisiidそのまま-1
									//リセット処理	
									tosiyoridata[heyatukiid].age=0;
									tosiyoridata[heyatukiid].category=0;
									tosiyoridata[heyatukiid].startyear=0;
									tosiyoridata[heyatukiid].rikisiid=-1;
									strcpy(tosiyoridata[heyatukiid].sikona,"\0");
									tosiyoridata[heyatukiid].sishouflag=0;
									if (heyatukiid>=200){
										strcpy(tosiyoridata[heyatukiid].namestring,"\0");
									}
									tosiyoridata[heyatukiid].jinbou=0;
									tosiyoridata[heyatukiid].rijiflag=0;
									//tosiyoridata[heyatukiid].keishousha_rikisiid=-1;
									//tosiyoridata[heyatukiid].keishousha_tosiyoriid=-1;
									break;
								}else{
									heyameihenkouzumiflag=1;
									strcpy(heyastring[tosiyoridata[i].shozokuheyaid],tosiyoridata[heyatukiid].namestring);
									tosiyoridata[heyatukiid].sishouflag=1;
									tosiyoridata[i].shozokuheyaid=-1;
									//tosiyoridata[i].shozokuitimonid=-1;
									//リセット処理	
									tosiyoridata[i].age=0;
									tosiyoridata[i].category=0;
									tosiyoridata[i].startyear=0;
									tosiyoridata[i].rikisiid=-1;
									strcpy(tosiyoridata[i].sikona,"\0");
									tosiyoridata[i].sishouflag=0;
									if (i>=200){
										strcpy(tosiyoridata[i].namestring,"\0");
									}
									tosiyoridata[i].jinbou=0;
									tosiyoridata[i].rijiflag=0;
									tosiyoridata[i].keishousha_rikisiid=-1;
									tosiyoridata[i].keishousha_tosiyoriid=-1;
									break;
								}
							}
						}
						if (taishokuzumiflag==0){
	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%sの退職処理で想定外の困ったなぁで定年延長(部屋付がCカテしかいない可能性)\n",
	tosiyoridata[i].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%sの退職処理で想定外の困ったなぁで定年延長(部屋付がCカテしかいない可能性)",
	tosiyoridata[i].namestring);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	}
	//////////////////////////////////////////////////////////////
						}
					}
				//もし定年退職年寄が師匠で功績顕著一代年寄なら
				}else if (tosiyoridata[i].sishouflag==1 && i>=200 && i<300){
					//部屋付がAかBカテ通常年寄か功績顕著一代年寄なら年寄名跡の変更による部屋名の変更という扱い？
						//人望順年寄IDを検索
						//バブルソート
					for (iii=0;iii<TOSIYORISUU;iii++){
						temp_narabekaeyou[iii]=0;
						temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
						jinboujun_tosiyoriid[iii]=0;
						jinboujun_tosiyoriid[iii]=iii;
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					}
					for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
						for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
							if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
								temp_tosiyoriid = temp_narabekaeyou[ii];
								temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
								temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
								temp_tosiyoriid = jinboujun_tosiyoriid[ii];
								jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
								jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
							}
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
					}
					heyameihenkouzumiflag=0;
					for (ii=0;ii<TOSIYORISUU;ii++){
						heyatukiid=jinboujun_tosiyoriid[ii];
					//for (ii=0;ii<106;ii++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (i!=heyatukiid && tosiyoridata[i].shozokuheyaid==tosiyoridata[heyatukiid].shozokuheyaid 
						&& tosiyoridata[heyatukiid].keishousha_rikisiid==-1 //α023で部屋名の変更を伴う場合はやっぱりレンタル年寄は除くことにした
						&& (tosiyoridata[heyatukiid].category==1 || tosiyoridata[heyatukiid].category==2  || tosiyoridata[heyatukiid].category==4)
						&& (heyatukiid<106 || (heyatukiid>=200 && heyatukiid<300))){//通常年寄か功績顕著の昇格+部屋名変更
							heya_tosiyorisuu[tosiyoridata[heyatukiid].shozokuheyaid]--;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[heyatukiid]=1;
for (iiiii=0;iiiii<TOSIYORISUU;iiiii++){
	//if( ProcessMessage() == -1 ){mode=1;return ;}
	if (tosiyoridata[i].shozokuheyaid==tosiyoridata[iiiii].shozokuheyaid){
		kirokuhituyouflag_tosiyoriid[iiiii]=1;
	}
}
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋師匠で元%sの%s親方(%d才)が退職。\n元%sの%s親方(%d才)が部屋を継承、部屋名を%s部屋に変更\n",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[heyatukiid].sikona,
tosiyoridata[heyatukiid].namestring,
tosiyoridata[heyatukiid].age,
tosiyoridata[heyatukiid].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋師匠で元%sの%s親方(%d才)が退職。",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
DrawFormatString(0,369+16,CRWHITE,"元%sの%s親方(%d才)が部屋を継承、部屋名を%s部屋に変更",
//heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[heyatukiid].sikona,
tosiyoridata[heyatukiid].namestring,
tosiyoridata[heyatukiid].age,
tosiyoridata[heyatukiid].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							heyameihenkouzumiflag=1;
							strcpy(heyastring[tosiyoridata[i].shozokuheyaid],tosiyoridata[heyatukiid].namestring);
							tosiyoridata[heyatukiid].sishouflag=1;
							if (itimondata[tosiyoridata[i].shozokuitimonid].shuheyaid==tosiyoridata[i].shozokuheyaid){
								//一門名も変更→人望比較で一門主を決めなおした方が良いと思う
								//引退師匠が主部屋の師匠（一門主）でもあったら同門のなかから人望の一番高い師匠を一門主にする
								for (iii=0;iii<ITIMONSUU;iii++){
									//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									if (itimondata[iii].shuheyaid==tosiyoridata[heyatukiid].shozokuheyaid){
										temp_tosiyoriid=0;temp_tosiyoriid=-1;
										temp_jinbou=0;temp_jinbou=-999999;
										for (iiii=0;iiii<TOSIYORISUU;iiii++){
											//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
											if (tosiyoridata[iiii].shozokuitimonid==tosiyoridata[heyatukiid].shozokuitimonid 
												&& tosiyoridata[iiii].sishouflag==1
												&& iiii!=i){
												if (temp_jinbou<tosiyoridata[iiii].jinbou){
														temp_jinbou=tosiyoridata[iiii].jinbou;
														temp_tosiyoriid=iiii;
												}
											}
										}
										if (temp_tosiyoriid==-1){

//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s一門は名称を変更するかどうかの処理で想定外の困ったなぁ002\n",
tosiyoridata[i].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s一門は名称を変更するかどうかの処理で想定外の困ったなぁ",
tosiyoridata[i].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
										}else{
											strcpy(itimondata[tosiyoridata[heyatukiid].shozokuitimonid].namestring,tosiyoridata[temp_tosiyoriid].namestring);
											itimondata[tosiyoridata[heyatukiid].shozokuitimonid].shuheyaid=tosiyoridata[temp_tosiyoriid].shozokuheyaid;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[heyatukiid]=1;
for (iiiii=0;iiiii<TOSIYORISUU;iiiii++){
	//if( ProcessMessage() == -1 ){mode=1;return ;}
	if (tosiyoridata[i].shozokuitimonid==tosiyoridata[iiiii].shozokuitimonid){
		kirokuhituyouflag_tosiyoriid[iiiii]=1;
	}
}
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s一門は名称を%s一門に変更しました\n",
tosiyoridata[i].namestring,
tosiyoridata[temp_tosiyoriid].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s一門は名称を%s一門に変更しました",
tosiyoridata[i].namestring,
tosiyoridata[temp_tosiyoriid].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
										}
									}
								}
							}
							tosiyoridata[i].shozokuheyaid=-1;
							//tosiyoridata[i].shozokuitimonid=-1;
							//リセット処理	
							tosiyoridata[i].age=0;
							tosiyoridata[i].category=0;
							tosiyoridata[i].startyear=0;
							tosiyoridata[i].rikisiid=-1;
							strcpy(tosiyoridata[i].sikona,"\0");
							tosiyoridata[i].sishouflag=0;
							if (i>=200){
								strcpy(tosiyoridata[i].namestring,"\0");
							}
							tosiyoridata[i].jinbou=0;
							tosiyoridata[i].rijiflag=0;
							tosiyoridata[i].keishousha_rikisiid=-1;
							tosiyoridata[i].keishousha_tosiyoriid=-1;
							break;
						}
					}
					//師匠が功績顕著一代で部屋付が借株か期間限定一代しかいないなら
					//部屋数40以上なら部屋解散
					if (heyameihenkouzumiflag!=1){

//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"師匠が功績顕著一代で部屋付が借株か期間限定一代しかいないか、部屋数が少なすぎて処理できない(%s部屋師匠で元%sの%s親方(%d才)の退職処理をして部屋を解散したいところだが処理方法検討中です)\n",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"師匠が功績顕著一代で部屋付が借株か期間限定一代しかいないか、部屋数が少なすぎて処理できない(%s部屋師匠で",
heyastring[tosiyoridata[i].shozokuheyaid]);
DrawFormatString(0,369+16,CRWHITE,"元%sの%s親方(%d才)の退職処理をして部屋を解散したいところだが処理方法検討中)",
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
					}
				}else{//定年退職年寄がただの部屋付の場合
					if (i<106	//他に借株や期間限定一代年寄の部屋付親方がいたら譲渡して退職
						&& tosiyoridata[i].keishousha_rikisiid==-1
						&& tosiyoridata[i].keishousha_tosiyoriid==-1
					){
						//人望順年寄IDを検索
						//バブルソート
						for (iii=0;iii<TOSIYORISUU;iii++){
							temp_narabekaeyou[iii]=0;
							temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
							jinboujun_tosiyoriid[iii]=0;
							jinboujun_tosiyoriid[iii]=iii;
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
						for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
							for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
								if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
									temp_tosiyoriid = temp_narabekaeyou[ii];
									temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
									temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
									temp_tosiyoriid = jinboujun_tosiyoriid[ii];
									jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
									jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
								}
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							}
						}
						joutosakiketteiflag=0;
						for (ii=0;ii<TOSIYORISUU;ii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							temp_tosiyoriid=ii;
							ii=jinboujun_tosiyoriid[ii];
							if (tosiyoridata[ii].sishouflag==0
								&& i!=ii
								&& tosiyoridata[i].shozokuheyaid==tosiyoridata[ii].shozokuheyaid
								&& (tosiyoridata[ii].keishousha_rikisiid!=-1 || tosiyoridata[ii].keishousha_tosiyoriid!=-1 || ii>=300)
								&& tosiyoridata[ii].age<tosiyoridata[i].age
								&& tosiyoridata[ii].age<59//譲渡後の取得を避けるため
							){
								heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;
								joutosakiketteiflag=1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋付きで元%sの%s親方(%d才)が退職。\n同じ部屋で元%sの%s親方(%d才)が年寄株%sを取得、襲名\n",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
tosiyoridata[i].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋付きで元%sの%s親方(%d才)が退職。",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
DrawFormatString(0,369+16,CRWHITE,"同じ部屋で元%sの%s親方(%d才)が年寄株%sを取得、襲名",
//heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
tosiyoridata[i].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								tosiyoridata[ii].shozokuheyaid=-1;
								//tosiyoridata[ii].shozokuitimonid=-1;
								tosiyoridata[i].age=tosiyoridata[ii].age;
								if (tosiyoridata[ii].category>=4){//一代年寄ならAカテクリアしているので
									tosiyoridata[i].category=1;
								}else{
									tosiyoridata[i].category=tosiyoridata[ii].category;
								}
								tosiyoridata[i].startyear=year;
								//tosiyoridata[i].shozokuheyaidはそのまま
								//tosiyoridata[i].shozokuitimonidもそのまま
								tosiyoridata[i].jinbou=tosiyoridata[ii].jinbou;
								tosiyoridata[i].rijiflag=tosiyoridata[ii].rijiflag;
								tosiyoridata[i].rikisiid=tosiyoridata[ii].rikisiid;
								strcpy(tosiyoridata[i].sikona,tosiyoridata[ii].sikona);
								//tosiyoridata[i].sishouflag=;部屋付のままなのでコメントアウト
								//tosiyoridata[i].namestirngはもちろんそのまま
								//tosiyoridata[i].keishousha_tosiyoriidそのまま-1
								//tosiyoridata[i].keishousha_rikisiidそのまま-1
								//リセット処理	
								tosiyoridata[ii].age=0;
								tosiyoridata[ii].category=0;
								tosiyoridata[ii].startyear=0;
								tosiyoridata[ii].rikisiid=-1;
								strcpy(tosiyoridata[ii].sikona,"\0");
								tosiyoridata[ii].sishouflag=0;
								if (ii>=200){
									strcpy(tosiyoridata[ii].namestring,"\0");
								}
								tosiyoridata[ii].jinbou=0;
								tosiyoridata[ii].rijiflag=0;
								//tosiyoridata[ii].keishousha_rikisiid=-1;
								//tosiyoridata[ii].keishousha_tosiyoriid=-1;
								break;
							}
							ii=temp_tosiyoriid;
						}
						if (joutosakiketteiflag==0){//ただの退職処理
							heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;
	//記録必要フラグ書込み/////////////
	kirokuhituyouflag_tosiyoriid[i]=1;
	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s部屋付で元%sの%s親方(%d才)が退職\n",
	heyastring[tosiyoridata[i].shozokuheyaid],
	tosiyoridata[i].sikona,
	tosiyoridata[i].namestring,
	tosiyoridata[i].age);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋付で元%sの%s親方(%d才)が退職",
	heyastring[tosiyoridata[i].shozokuheyaid],
	tosiyoridata[i].sikona,
	tosiyoridata[i].namestring,
	tosiyoridata[i].age);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	}
	//////////////////////////////////////////////////////////////
							tosiyoridata[i].shozokuheyaid=-1;
							//tosiyoridata[i].shozokuitimonid=-1;
							//リセット処理	
							tosiyoridata[i].age=0;
							tosiyoridata[i].category=0;
							tosiyoridata[i].startyear=0;
							tosiyoridata[i].rikisiid=-1;
							strcpy(tosiyoridata[i].sikona,"\0");
							tosiyoridata[i].sishouflag=0;
							if (i>=200){
								strcpy(tosiyoridata[i].namestring,"\0");
							}
							tosiyoridata[i].jinbou=0;
							tosiyoridata[i].rijiflag=0;
							//tosiyoridata[i].keishousha_rikisiid=-1;
							//tosiyoridata[i].keishousha_tosiyoriid=-1;
						}
					}else{//ただの退職処理
						heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋付で元%sの%s親方(%d才)が退職\n",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋付で元%sの%s親方(%d才)が退職",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						tosiyoridata[i].shozokuheyaid=-1;
						//tosiyoridata[i].shozokuitimonid=-1;
						//リセット処理	
						tosiyoridata[i].age=0;
						tosiyoridata[i].category=0;
						tosiyoridata[i].startyear=0;
						tosiyoridata[i].rikisiid=-1;
						strcpy(tosiyoridata[i].sikona,"\0");
						tosiyoridata[i].sishouflag=0;
						if (i>=200){
							strcpy(tosiyoridata[i].namestring,"\0");
						}
						tosiyoridata[i].jinbou=0;
						tosiyoridata[i].rijiflag=0;
						//tosiyoridata[i].keishousha_rikisiid=-1;
						//tosiyoridata[i].keishousha_tosiyoriid=-1;

					}
				}
			//年寄が一人しかいない部屋
			}else{
				if (tosiyoridata[i].keishousha_tosiyoriid!=-1){//継承指名年寄いれば継承
					for (ii=0;ii<TOSIYORISUU;ii++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (tosiyoridata[i].keishousha_tosiyoriid==ii){
							heya_tosiyorisuu[tosiyoridata[ii].shozokuheyaid]--;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋師匠で元%sの%s親方(%d才)が退職。\n元%sの%s親方(%d才)が%s部屋を継承(年寄が一人しかいない部屋のはずなのでこんなことは起こらないはずなんだけど…)\n",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
tosiyoridata[i].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋師匠で元%sの%s親方(%d才)が退職。",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
DrawFormatString(0,369+16,CRWHITE,"元%sの%s親方(%d才)が%s部屋を継承",
//heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
tosiyoridata[i].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							tosiyoridata[ii].shozokuheyaid=-1;
							//tosiyoridata[ii].shozokuitimonid=-1;
							tosiyoridata[i].age=tosiyoridata[ii].age;
							if (tosiyoridata[ii].category>=4){//一代年寄ならAカテクリアしているので
								tosiyoridata[i].category=1;
							}else{
								tosiyoridata[i].category=tosiyoridata[ii].category;
							}
							tosiyoridata[i].startyear=year;
							//tosiyoridata[i].shozokuheyaidはそのまま
							//tosiyoridata[i].shozokuitimonidもそのまま
							tosiyoridata[i].jinbou=tosiyoridata[ii].jinbou;
							tosiyoridata[i].rijiflag=tosiyoridata[ii].rijiflag;
							tosiyoridata[i].rikisiid=tosiyoridata[ii].rikisiid;
							strcpy(tosiyoridata[i].sikona,tosiyoridata[ii].sikona);
							tosiyoridata[i].sishouflag=0;
							//tosiyoridata[i].namestirngはもちろんそのまま
							tosiyoridata[i].keishousha_tosiyoriid=-1;
							tosiyoridata[i].keishousha_rikisiid=-1;
							//リセット処理	
							tosiyoridata[ii].age=0;
							tosiyoridata[ii].category=0;
							tosiyoridata[ii].startyear=0;
							tosiyoridata[ii].rikisiid=-1;
							strcpy(tosiyoridata[ii].sikona,"\0");
							tosiyoridata[ii].sishouflag=0;
							if (ii>=200){
								strcpy(tosiyoridata[ii].namestring,"\0");
							}
							tosiyoridata[ii].jinbou=0;
							tosiyoridata[ii].rijiflag=0;
							//tosiyoridata[ii].keishousha_rikisiid=-1;
							//tosiyoridata[ii].keishousha_tosiyoriid=-1;
							break;
						}
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					}
				}else{//とりえず暫定で定年延長させて何もしない
					if (heyadokuritumode==1){//部屋の新設消滅モードＯＮの場合
						if (tosiyoridata[i].shozokuheyaid!=myheyaid && heyasuu_genzon>=40 && tosiyoridata[i].keishousha_rikisiid==-1 && tosiyoridata[i].keishousha_tosiyoriid==-1){
							//プレイヤーの部屋以外で継承者いない場合&&部屋数が40以上→部屋消滅処理
							//まずは年寄を退職処理、年寄データリセット
							heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋師匠で元%sの%s親方(%d才)が退職\n%s部屋は消滅します。\n",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
heyastring[tosiyoridata[i].shozokuheyaid]);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋師匠で元%sの%s親方(%d才)が退職。%s部屋は消滅します。",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
heyastring[tosiyoridata[i].shozokuheyaid]);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////

							//部屋名リセット
							strcpy(heyastring[tosiyoridata[i].shozokuheyaid],"\0");
							//一門主を変更する必要があれば変更する処理
							if (itimondata[tosiyoridata[i].shozokuitimonid].shuheyaid==tosiyoridata[i].shozokuheyaid){
								//一門名も変更→人望比較で一門主を決めなおした方が良いと思う
								//引退師匠が主部屋の師匠（一門主）でもあったら同門のなかから人望の一番高い師匠を一門主にする
								//一門の看板を守るため、名跡交換みたいにしてみたver3.12
								for (iii=0;iii<ITIMONSUU;iii++){
									//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									if (itimondata[iii].shuheyaid==tosiyoridata[i].shozokuheyaid){
										temp_tosiyoriid=0;temp_tosiyoriid=-1;
										temp_jinbou=0;temp_jinbou=-9999999;
										for (iiii=0;iiii<TOSIYORISUU;iiii++){
											//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
											if (tosiyoridata[iiii].shozokuitimonid==tosiyoridata[i].shozokuitimonid 
												&& tosiyoridata[iiii].sishouflag==1
												&& iiii!=i){
												if (temp_jinbou<tosiyoridata[iiii].jinbou){
														temp_jinbou=tosiyoridata[iiii].jinbou;
														temp_tosiyoriid=iiii;
												}
											}
										}
										if (temp_tosiyoriid==-1){//これは一門消滅だと思う

//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
//fprintf(fp,"%s一門は名称を変更するかどうかの処理で想定外の困ったなぁ\n",
fprintf(fp,"%s一門は消滅します\n",
tosiyoridata[i].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
//DrawFormatString(0,369,CRWHITE,"%s一門は名称を変更するかどうかの処理で想定外の困ったなぁ",
DrawFormatString(0,369,CRWHITE,"%s一門は消滅します",
tosiyoridata[i].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
											strcpy(itimondata[tosiyoridata[i].shozokuitimonid].namestring,"\0");
											itimondata[tosiyoridata[i].shozokuitimonid].shuheyaid=-1;
											tosiyoridata[i].shozokuheyaid=-1;
											//tosiyoridata[i].shozokuitimonid=-1;同じ一門優先処理があるため後でリセット
											//リセット処理	
											tosiyoridata[i].age=0;
											tosiyoridata[i].category=0;
											tosiyoridata[i].startyear=0;
											tosiyoridata[i].rikisiid=-1;
											strcpy(tosiyoridata[i].sikona,"\0");
											tosiyoridata[i].sishouflag=0;
											if (i>=200){
												strcpy(tosiyoridata[i].namestring,"\0");
											}
											tosiyoridata[i].jinbou=0;
											tosiyoridata[i].rijiflag=0;
											//tosiyoridata[i].keishousha_rikisiid=-1;
											//tosiyoridata[i].keishousha_tosiyoriid=-1;
											break;
										}else{
											if (i<106){//通常株なら名跡交換(株の取得)で一門の看板を守る
												//strcpy(itimondata[tosiyoridata[i].shozokuitimonid].namestring,tosiyoridata[temp_tosiyoriid].namestring);
												itimondata[tosiyoridata[i].shozokuitimonid].shuheyaid=tosiyoridata[temp_tosiyoriid].shozokuheyaid;
//ここver3.12で記録必要フラグ書込み内容の変更必要かも
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[temp_tosiyoriid]=1;
for (iiiii=0;iiiii<TOSIYORISUU;iiiii++){
	//if( ProcessMessage() == -1 ){mode=1;return ;}
	if (tosiyoridata[temp_tosiyoriid].shozokuheyaid==tosiyoridata[iiiii].shozokuheyaid){
		kirokuhituyouflag_tosiyoriid[iiiii]=1;
	}
}
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
//fprintf(fp,"%s一門は名称を%s一門に変更しました\n",
if (temp_tosiyoriid<106){
	fprintf(fp,"一門の看板を守るため、%sと%sは名跡交換。%s部屋は%s部屋に改称しました\n",
	tosiyoridata[i].namestring,
	tosiyoridata[temp_tosiyoriid].namestring,
	tosiyoridata[temp_tosiyoriid].namestring,
	tosiyoridata[i].namestring);
}else{
	fprintf(fp,"一門の看板を守るため、%sは%sを取得襲名し、一代年寄を返上。%s部屋は%s部屋に改称しました\n",
	tosiyoridata[temp_tosiyoriid].namestring,
	tosiyoridata[i].namestring,
	tosiyoridata[temp_tosiyoriid].namestring,
	tosiyoridata[i].namestring);
}
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
if (temp_tosiyoriid<106){
	DrawFormatString(0,369,CRWHITE,"一門の看板を守るため、%sと%sは名跡交換。",
	tosiyoridata[i].namestring,
	tosiyoridata[temp_tosiyoriid].namestring);
	DrawFormatString(0,369+16,CRWHITE,"%s部屋は%s部屋に改称しました",
	tosiyoridata[temp_tosiyoriid].namestring,
	tosiyoridata[i].namestring);
}else{
	DrawFormatString(0,369,CRWHITE,"一門の看板を守るため、%sは%sを取得襲名し、一代年寄を返上。",
	tosiyoridata[temp_tosiyoriid].namestring,
	tosiyoridata[i].namestring);
	DrawFormatString(0,369+16,CRWHITE,"%s部屋は%s部屋に改称しました",
	tosiyoridata[temp_tosiyoriid].namestring,
	tosiyoridata[i].namestring);
}
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
												strcpy(heyastring[tosiyoridata[temp_tosiyoriid].shozokuheyaid],tosiyoridata[i].namestring);
												tosiyoridata[i].age=tosiyoridata[temp_tosiyoriid].age;
												if (tosiyoridata[temp_tosiyoriid].category>=4){//一代年寄ならAカテクリアしているので
													tosiyoridata[i].category=1;
												}else{
													tosiyoridata[i].category=tosiyoridata[temp_tosiyoriid].category;
												}
												tosiyoridata[i].startyear=year;
												tosiyoridata[i].shozokuheyaid=tosiyoridata[temp_tosiyoriid].shozokuheyaid;
												//tosiyoridata[i].shozokuitimonidはそのまま
												tosiyoridata[i].jinbou=tosiyoridata[temp_tosiyoriid].jinbou;
												tosiyoridata[i].rijiflag=tosiyoridata[temp_tosiyoriid].rijiflag;
												tosiyoridata[i].rikisiid=tosiyoridata[temp_tosiyoriid].rikisiid;
												strcpy(tosiyoridata[i].sikona,tosiyoridata[temp_tosiyoriid].sikona);
												tosiyoridata[i].sishouflag=1;
												//tosiyoridata[i].namestirngはもちろんそのまま
												//下の4行は師匠の名跡交換に伴い後継者もそのまま移動
												tosiyoridata[i].keishousha_tosiyoriid=tosiyoridata[temp_tosiyoriid].keishousha_tosiyoriid;
												tosiyoridata[i].keishousha_rikisiid=tosiyoridata[temp_tosiyoriid].keishousha_rikisiid;
												tosiyoridata[temp_tosiyoriid].keishousha_rikisiid=-1;
												tosiyoridata[temp_tosiyoriid].keishousha_tosiyoriid=-1;
												//リセット処理	
												tosiyoridata[temp_tosiyoriid].shozokuheyaid=-1;
												//tosiyoridata[temp_tosiyoriid].shozokuitimonid=-1;
												tosiyoridata[temp_tosiyoriid].age=0;
												tosiyoridata[temp_tosiyoriid].category=0;
												tosiyoridata[temp_tosiyoriid].startyear=0;
												tosiyoridata[temp_tosiyoriid].rikisiid=-1;
												strcpy(tosiyoridata[temp_tosiyoriid].sikona,"\0");
												tosiyoridata[temp_tosiyoriid].sishouflag=0;
												if (temp_tosiyoriid>=200){
													strcpy(tosiyoridata[temp_tosiyoriid].namestring,"\0");
												}
												tosiyoridata[temp_tosiyoriid].jinbou=0;
												tosiyoridata[temp_tosiyoriid].rijiflag=0;
												break;
											}else{
												strcpy(itimondata[tosiyoridata[i].shozokuitimonid].namestring,tosiyoridata[temp_tosiyoriid].namestring);
												itimondata[tosiyoridata[i].shozokuitimonid].shuheyaid=tosiyoridata[temp_tosiyoriid].shozokuheyaid;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
for (iiiii=0;iiiii<TOSIYORISUU;iiiii++){
	//if( ProcessMessage() == -1 ){mode=1;return ;}
	if (tosiyoridata[i].shozokuitimonid==tosiyoridata[iiiii].shozokuitimonid){
		kirokuhituyouflag_tosiyoriid[iiiii]=1;
	}
}
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s一門は名称を%s一門に変更しました\n",
tosiyoridata[i].namestring,
tosiyoridata[temp_tosiyoriid].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s一門は名称を%s一門に変更しました",
tosiyoridata[i].namestring,
tosiyoridata[temp_tosiyoriid].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
												tosiyoridata[i].shozokuheyaid=-1;
												//tosiyoridata[i].shozokuitimonid=-1;同じ一門優先処理があるため後でリセット
												//リセット処理	
												tosiyoridata[i].age=0;
												tosiyoridata[i].category=0;
												tosiyoridata[i].startyear=0;
												tosiyoridata[i].rikisiid=-1;
												strcpy(tosiyoridata[i].sikona,"\0");
												tosiyoridata[i].sishouflag=0;
												if (i>=200){
													strcpy(tosiyoridata[i].namestring,"\0");
												}
												tosiyoridata[i].jinbou=0;
												tosiyoridata[i].rijiflag=0;
												//tosiyoridata[i].keishousha_rikisiid=-1;
												//tosiyoridata[i].keishousha_tosiyoriid=-1;
												break;
											}
										}
									}
								}
							}else{//一門主でないのでただの消滅処理の場合のリセット
								tosiyoridata[i].shozokuheyaid=-1;
								//tosiyoridata[i].shozokuitimonid=-1;同じ一門優先処理があるため後でリセット
								//リセット処理	
								tosiyoridata[i].age=0;
								tosiyoridata[i].category=0;
								tosiyoridata[i].startyear=0;
								tosiyoridata[i].rikisiid=-1;
								strcpy(tosiyoridata[i].sikona,"\0");
								tosiyoridata[i].sishouflag=0;
								if (i>=200){
									strcpy(tosiyoridata[i].namestring,"\0");
								}
								tosiyoridata[i].jinbou=0;
								tosiyoridata[i].rijiflag=0;
								//tosiyoridata[i].keishousha_rikisiid=-1;
								//tosiyoridata[i].keishousha_tosiyoriid=-1;
							}
							//一門主変更処理ここまで/////////////////////////

////////////
////////////力士を移動させる処理(年寄のいない部屋から他の部屋へ力士移動させる処理を改変し流用)//////////////////////////
////////////
	//部屋ごとに所属力士数を数える
	for (ii=0;ii<HEYASUU;ii++){
		shozokurikisisuu[ii]=0;
	}
	for (ii=0;ii<HEYASUU;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (iii=0;iii<RIKISISUU;iii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[iii].heyaid==ii){
				shozokurikisisuu[ii]++;
			}
		}
	}
	//部屋ごとの番付順力士IDを検索
	for (ii=0;ii<HEYASUU;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (iii=0;iii<20;iii++){
			heyabandukejunid[ii][iii]=-1;
		}
	}
	count=0;
	for (ii=0;ii<HEYASUU;ii++){//部屋ID
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (iii=0;iii<RIKISISUU;iii++){//番付順ID
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[bandukejunid[iii]].heyaid==ii){
				heyabandukejunid[ii][count]=bandukejunid[iii];
				count++;
			}
		}
		count=0;
	}
	//空き部屋確認＆力士部屋移動
	//空き部屋確認
	for (ii=0;ii<HEYASUU;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		tosiyoriiruflag[ii]=0;
		for (iii=0;iii<TOSIYORISUU;iii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (tosiyoridata[iii].shozokuheyaid==ii){
				tosiyoriiruflag[ii]=1;
				break;
			}
		}
	}
//debug書き込み/////////////////////////////////////////
fp = fopen("debuglog.txt","w");
for (ii=0;ii<HEYASUU;ii++){
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	fprintf(fp,"部屋ID%d所属人数　%2d人\n",ii,shozokurikisisuu[ii]);
}
fprintf(fp,"\n");
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
////////////////temp_dat初期化////////////////
fp = fopen("temp_dat.dat","w");
fclose(fp);
//////////////////////////////////////////////
	//ここで力士部屋移動処理(同じ一門)
	for (ii=0;ii<HEYASUU;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (tosiyoriiruflag[ii]==0){
			count=0;
			while (shozokurikisisuu[ii]>0){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (iiii=1;iiii<HEYASUU;iiii++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if(tosiyoriiruflag[iiii]==1){
						for (iii=0;iii<TOSIYORISUU;iii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							if (tosiyoridata[iii].shozokuheyaid==iiii 
								&& tosiyoridata[iii].shozokuitimonid==tosiyoridata[i].shozokuitimonid){
								while(shozokurikisisuu[iiii]<20){
									//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//debug書き込み/////////////////////////////////////////
		fp = fopen("debuglog.txt","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "debuglog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
		fprintf(fp,"同一門部屋ID%d→同一門部屋ID%d\n",ii,iiii);
		fprintf(fp,"%d→%d\n",shozokurikisisuu[ii],shozokurikisisuu[iiii]);
		fprintf(fp,"heyabandukejunid[%d][%d]\n",ii,count);
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}
		////////////////////////////////////////////////////////////
			
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%sは%s部屋の消滅に伴い%s部屋に移籍しました(同一門)\n",
namestring[heyabandukejunid[ii][count]],
heyastring[ii],
heyastring[iiii]);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
//temp_dat書き込み/////////////////////////////////////////
fp = fopen("temp_dat.dat","ab");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "temp_dat.datファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
//ここから書き込み
fwrite(&heyabandukejunid[ii][count],sizeof(heyabandukejunid[ii][count]),1,fp);//力士ID
fwrite(&iiii,sizeof(iiii),1,fp);//新部屋ID
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
									rikisidata[heyabandukejunid[ii][count]].heyaid=iiii;
									shozokurikisisuu[iiii]++;
									shozokurikisisuu[ii]--;
									count++;
		//debug書き込み/////////////////////////////////////////
		fp = fopen("debuglog.txt","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "debuglog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
		fprintf(fp,"同一門部屋ID%d→同一門部屋ID%d\n",ii,iiii);
		fprintf(fp,"%d→%d\n\n",shozokurikisisuu[ii],shozokurikisisuu[iiii]);
		//fprintf(fp,"heyabandukejunid[%d][%d]\n\n\n",ii,count);
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}
		////////////////////////////////////////////////////////////
									if (shozokurikisisuu[ii]==0){break;}
								}
							}
							if (shozokurikisisuu[ii]==0){break;}
						}
						if (shozokurikisisuu[ii]==0){break;}
					}
				}
				break;//同じ一門に限定してるからここで抜けさせないと無限ループになってしまうはずだから
			}
		}
	}


	//部屋ごとに所属力士数を数える
	for (ii=0;ii<HEYASUU;ii++){
		shozokurikisisuu[ii]=0;
	}
	for (ii=0;ii<HEYASUU;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (iii=0;iii<RIKISISUU;iii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[iii].heyaid==ii){
				shozokurikisisuu[ii]++;
			}
		}
	}
//debug書き込み/////////////////////////////////////////
fp = fopen("debuglog.txt","a");
for (ii=0;ii<HEYASUU;ii++){
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	fprintf(fp,"部屋ID%d所属人数　%2d人\n",ii,shozokurikisisuu[ii]);
}
fprintf(fp,"\n");
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////

	//部屋ごとの番付順力士IDを検索
	for (ii=0;ii<HEYASUU;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (iii=0;iii<20;iii++){
			heyabandukejunid[ii][iii]=-1;
		}
	}
	count=0;
	for (ii=0;ii<HEYASUU;ii++){//部屋ID
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (iii=0;iii<RIKISISUU;iii++){//番付順ID
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[bandukejunid[iii]].heyaid==ii){
				heyabandukejunid[ii][count]=bandukejunid[iii];
				count++;
			}
		}
		count=0;
	}


	//ここで力士部屋移動処理(一門関係なし)
	for (ii=0;ii<HEYASUU;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (tosiyoriiruflag[ii]==0){
			count=0;
			while (shozokurikisisuu[ii]>0){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (iiii=1;iiii<HEYASUU;iiii++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if(tosiyoriiruflag[iiii]==1){
						while(shozokurikisisuu[iiii]<20){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
//debug書き込み/////////////////////////////////////////
fp = fopen("debuglog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "debuglog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"部屋ID%d→部屋ID%d\n",ii,iiii);
fprintf(fp,"%d→%d\n",shozokurikisisuu[ii],shozokurikisisuu[iiii]);
fprintf(fp,"heyabandukejunid[%d][%d]\n",ii,count);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////

//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%sは%s部屋の消滅に伴い%s部屋に移籍しました(他一門)\n",
namestring[heyabandukejunid[ii][count]],
heyastring[ii],
heyastring[iiii]);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
//temp_dat書き込み/////////////////////////////////////////
fp = fopen("temp_dat.dat","ab");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "temp_dat.datファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
//ここから書き込み
fwrite(&heyabandukejunid[ii][count],sizeof(int),1,fp);//力士ID
fwrite(&iiii,sizeof(int),1,fp);//新部屋ID
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////

							rikisidata[heyabandukejunid[ii][count]].heyaid=iiii;
							shozokurikisisuu[iiii]++;
							shozokurikisisuu[ii]--;
							count++;

//debug書き込み/////////////////////////////////////////
fp = fopen("debuglog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "debuglog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"部屋ID%d→部屋ID%d\n",ii,iiii);
fprintf(fp,"%d→%d\n\n",shozokurikisisuu[ii],shozokurikisisuu[iiii]);
//fprintf(fp,"heyabandukejunid[%d][%d]\n\n\n",ii,count);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////

							if (shozokurikisisuu[ii]==0){break;}
						}
						if (shozokurikisisuu[ii]==0){break;}
					}
				}
			}
		}
	}
	//部屋ごとに所属力士数を数える
	for (ii=0;ii<HEYASUU;ii++){
		shozokurikisisuu[ii]=0;
	}
	for (ii=0;ii<HEYASUU;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (iii=0;iii<RIKISISUU;iii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[iii].heyaid==ii){
				shozokurikisisuu[ii]++;
			}
		}
	}
//debug書き込み/////////////////////////////////////////
fp = fopen("debuglog.txt","a");
for (ii=0;ii<HEYASUU;ii++){
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	fprintf(fp,"部屋ID%d所属人数　%2d人\n",ii,shozokurikisisuu[ii]);
}
fprintf(fp,"\n");
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////

	//部屋ごとの番付順力士IDを検索
	for (ii=0;ii<HEYASUU;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (iii=0;iii<20;iii++){
			heyabandukejunid[ii][iii]=-1;
		}
	}
	count=0;
	for (ii=0;ii<HEYASUU;ii++){//部屋ID
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (iii=0;iii<RIKISISUU;iii++){//番付順ID
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[bandukejunid[iii]].heyaid==ii){
				heyabandukejunid[ii][count]=bandukejunid[iii];
				count++;
			}
		}
		count=0;
	}
	heyasuu_genzon--;

//部屋移籍した力士を表示
//////////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
int temp_rikisiid=0;
int temp_heyaid_new=0;
int count=0;
//temp_dat読込/////////////////////////////////////////
fp = fopen("temp_dat.dat","rb");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "temp_dat.datファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawString(20,20,"部屋の消滅に伴い、以下の力士が移籍しました",CRWHITE);
//ここから読込
while(1){
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	if(fread(&temp_rikisiid,sizeof(int),1,fp)<1){//EOFor読み取り失敗
		break;
	}else{
		fread(&temp_heyaid_new,sizeof(int),1,fp);//新部屋ID
	}
	if (rikisidata[temp_rikisiid].bandukenameid<=3){
		DrawFormatString(20,40+count*20,CRWHITE,"%s %s  %s部屋",
		bandukenamestring[rikisidata[temp_rikisiid].bandukenameid],
		namestring[temp_rikisiid],
		heyastring[temp_heyaid_new]);
	}else{
		DrawFormatString(20,40+count*20,CRWHITE,"%s%d枚目 %s  %s部屋",
		bandukenamestring[rikisidata[temp_rikisiid].bandukenameid],
		rikisidata[temp_rikisiid].bandukesuuji,
		namestring[temp_rikisiid],
		heyastring[temp_heyaid_new]);
	}
	count++;
}
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
DrawString( 250 , 460 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
////////////////////////////////////////////////////////////
/*これいらないんじゃないかなぁということで3.13α009からコメントアウト
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s一門は名称を%s一門に変更しました",
tosiyoridata[i].namestring,
tosiyoridata[temp_tosiyoriid].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
*/
}
	//年寄一門ＩＤリセット（同じ一門優先処理があったため後回しにしていた）
	/*if (tosiyoridata[i].shozokuheyaid==-1){//名跡交換で一門の看板を守る処理をしていることがあるため留保
		//tosiyoridata[i].shozokuitimonid=-1;
	}*/
/////////////////////////////////////////////////////////////////////////
						}else{
							//継承者がいる場合か部屋数が40未満

//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋師匠で元%sの%s親方(%d才)はとりあえず定年延長(継承者指名の現役力士引退待ちor部屋数が40未満)、処理方法検討中\n",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋師匠で元%sの%s親方(%d才)はとりあえず定年延長",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
DrawString(0,369+16,"(継承者指名の現役力士引退待ちor部屋数が40未満)、処理方法検討中",CRWHITE
);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						}
					}else{//新設消滅ＯＦＦの場合

//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋師匠で元%sの%s親方(%d才)はとりあえず定年延長(継承者指名の現役力士引退待ちor部屋で唯一の親方)、処理方法検討中\n",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋師匠で元%sの%s親方(%d才)はとりあえず定年延長",
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age);
DrawString(0,369+16,"(継承者指名の現役力士引退待ちor部屋で唯一の親方)、処理方法検討中",CRWHITE
);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
					}
				}

			/*
				//部屋数が38以下なら定年延長
				if (heyasuu_genzon<=38){
					//定年延長なので何もしない
				//部屋数が39以上なら取り潰し処理
				}else{
					heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;
					heyasuu_genzon--;
					//ここから部屋吸収合併処理
				}
			*/
			}
		}
}
	}

	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}
	//同じ一門内での期間限定一代年寄の株取得襲名、レンタル取得襲名//////////////////////
	for (i=300;i<TOSIYORISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (tosiyoridata[i].category==5 || tosiyoridata[i].category==6 
		&& tosiyoridata[i].shozokuheyaid!=-1){
			kabushutokuzumiflag=0;
			for (ii=0;ii<106;ii++){//株取得済みかどうか確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].keishousha_tosiyoriid==i){
					//if (tosiyoridata[ii].shozokuheyaid!=rikisidata[i].heyaid || (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid && tosiyoridata[ii].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
						kabushutokuzumiflag=1;
					//}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			if (kabushutokuzumiflag!=1){//期間限定一代年寄の株取得、襲名
				for (ii=0;ii<106;ii++){//空き名跡確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].shozokuitimonid==tosiyoridata[i].shozokuitimonid
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						//heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;
						//heya_tosiyorisuu[tosiyoridata[ii].shozokuheyaid]++;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"期間限定一代年寄%s(%d才)が年寄株%sを取得、襲名(一門優先処理)\n",
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"期間限定一代年寄%s(%d才)が年寄株%sを取得、襲名",
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						kabushutokuzumiflag=1;
						tosiyoridata[ii].age=tosiyoridata[i].age;
						tosiyoridata[ii].category=1;//Ａカテの1
						tosiyoridata[ii].startyear=year;//+1必要かな？
						for (iii=0;iii<TOSIYORISUU;iii++){
							if (tosiyoridata[iii].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
								tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
								break;
							}
						}
						tosiyoridata[ii].shozokuheyaid=tosiyoridata[i].shozokuheyaid;
						strcpy(tosiyoridata[ii].sikona,tosiyoridata[i].sikona);
						tosiyoridata[ii].jinbou=tosiyoridata[i].jinbou;
						tosiyoridata[ii].rikisiid=tosiyoridata[i].rikisiid;
						tosiyoridata[ii].sishouflag=0;
						tosiyoridata[ii].rijiflag=tosiyoridata[i].rijiflag;
						tosiyoridata[ii].keishousha_rikisiid=-1;
						tosiyoridata[ii].keishousha_tosiyoriid=-1;
						tosiyoridata[i].shozokuheyaid=-1;
						//tosiyoridata[i].shozokuitimonid=-1;
						//リセット処理	
						tosiyoridata[i].age=0;
						tosiyoridata[i].category=0;
						tosiyoridata[i].startyear=0;
						tosiyoridata[i].rikisiid=-1;
						strcpy(tosiyoridata[i].sikona,"\0");
						tosiyoridata[i].sishouflag=0;
						if (i>=200){
							strcpy(tosiyoridata[i].namestring,"\0");
						}
						tosiyoridata[i].jinbou=0;
						tosiyoridata[i].rijiflag=0;
						tosiyoridata[i].keishousha_rikisiid=-1;
						tosiyoridata[i].keishousha_tosiyoriid=-1;

						break;
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
			if (kabushutokuzumiflag!=1){
				//期間限定一代年寄が期間ギリギリなら下のルーチンを復活させてもいいかもしれないけど
				//下のルーチンを復活させるならすでにレンタル済みかどうかの確認必要
				//sishouflag==0もくわえろ！！！！(レンタルと後継者との判断のため)
				for (ii=0;ii<106;ii++){//期間限定一代年寄のレンタル取得、襲名
					if (tosiyoridata[ii].shozokuheyaid==-1 
					&& (tosiyoridata[ii].keishousha_rikisiid!=-1 || tosiyoridata[ii].keishousha_tosiyoriid!=-1) 
					&& tosiyoridata[ii].sishouflag==0){
					if((tosiyoridata[i].category==5 && year-tosiyoridata[i].startyear>=5) //期間ギリギリの絞り
					|| (tosiyoridata[i].category==6 && year-tosiyoridata[i].startyear>=3)){
						//heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;
						//heya_tosiyorisuu[tosiyoridata[ii].shozokuheyaid]++;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"期間限定一代年寄%s(%d才)が年寄株%sをレンタルし襲名\n",
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"期間限定一代年寄%s(%d才)が年寄株%sをレンタルし襲名",
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						shutoku_tosiyoriid=ii;
						shuumei_tosiyoriid=ii;
						tosiyoridata[ii].age=tosiyoridata[i].age;
							tosiyoridata[ii].category=1;//Ａカテの1
						tosiyoridata[ii].startyear=year;//+1必要かな？
						for (iii=0;iii<TOSIYORISUU;iii++){
							if (tosiyoridata[iii].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
								tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
								break;
							}
						}
						tosiyoridata[ii].shozokuheyaid=tosiyoridata[i].shozokuheyaid;
						//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
						strcpy(tosiyoridata[ii].sikona,tosiyoridata[i].sikona);
						tosiyoridata[ii].jinbou=tosiyoridata[i].jinbou;
						tosiyoridata[ii].rikisiid=tosiyoridata[i].rikisiid;
						tosiyoridata[ii].sishouflag=0;
						tosiyoridata[ii].rijiflag=0;
						//tosiyoridata[ii].keishousha_rikisiidは留保ついたままでいいので
						//tosiyoridata[ii].keishousha_tosiyoriidは留保ついたままでいいので
						tosiyoridata[i].shozokuheyaid=-1;
						//tosiyoridata[i].shozokuitimonid=-1;
						//リセット処理	
						tosiyoridata[i].age=0;
						tosiyoridata[i].category=0;
						tosiyoridata[i].startyear=0;
						tosiyoridata[i].rikisiid=-1;
						strcpy(tosiyoridata[i].sikona,"\0");
						tosiyoridata[i].sishouflag=0;
						if (i>=200){
							strcpy(tosiyoridata[i].namestring,"\0");
						}
						tosiyoridata[i].jinbou=0;
						tosiyoridata[i].rijiflag=0;
						tosiyoridata[i].keishousha_rikisiid=-1;
						tosiyoridata[i].keishousha_tosiyoriid=-1;
						break;
					}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
		}
	}
	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}
	//一門無関係での期間限定一代年寄の株取得襲名、レンタル取得襲名//////////////////////
	for (i=300;i<TOSIYORISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (tosiyoridata[i].category==5 || tosiyoridata[i].category==6 
		&& tosiyoridata[i].shozokuheyaid!=-1){
			kabushutokuzumiflag=0;
			for (ii=0;ii<106;ii++){//株取得済みかどうか確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].keishousha_tosiyoriid==i){
					//if (tosiyoridata[ii].shozokuheyaid!=rikisidata[i].heyaid || (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid && tosiyoridata[ii].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
						kabushutokuzumiflag=1;
					//}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			if (kabushutokuzumiflag!=1){//期間限定一代年寄の株取得、襲名
				for (ii=0;ii<106;ii++){//空き名跡確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						//heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;
						//heya_tosiyorisuu[tosiyoridata[ii].shozokuheyaid]++;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"期間限定一代年寄%s(%d才)が年寄株%sを取得、襲名(一門無関係処理)\n",
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"期間限定一代年寄%s(%d才)が年寄株%sを取得、襲名",
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						kabushutokuzumiflag=1;
						tosiyoridata[ii].age=tosiyoridata[i].age;
						tosiyoridata[ii].category=1;//Ａカテの1
						tosiyoridata[ii].startyear=year;//+1必要かな？
						for (iii=0;iii<TOSIYORISUU;iii++){
							if (tosiyoridata[iii].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
								tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
								break;
							}
						}
						tosiyoridata[ii].shozokuheyaid=tosiyoridata[i].shozokuheyaid;
						strcpy(tosiyoridata[ii].sikona,tosiyoridata[i].sikona);
						tosiyoridata[ii].jinbou=tosiyoridata[i].jinbou;
						tosiyoridata[ii].rikisiid=tosiyoridata[i].rikisiid;
						tosiyoridata[ii].sishouflag=0;
						tosiyoridata[ii].rijiflag=tosiyoridata[i].rijiflag;
						tosiyoridata[ii].keishousha_rikisiid=-1;
						tosiyoridata[ii].keishousha_tosiyoriid=-1;
						tosiyoridata[i].shozokuheyaid=-1;
						//tosiyoridata[i].shozokuitimonid=-1;
						//リセット処理	
						tosiyoridata[i].age=0;
						tosiyoridata[i].category=0;
						tosiyoridata[i].startyear=0;
						tosiyoridata[i].rikisiid=-1;
						strcpy(tosiyoridata[i].sikona,"\0");
						tosiyoridata[i].sishouflag=0;
						if (i>=200){
							strcpy(tosiyoridata[i].namestring,"\0");
						}
						tosiyoridata[i].jinbou=0;
						tosiyoridata[i].rijiflag=0;
						tosiyoridata[i].keishousha_rikisiid=-1;
						tosiyoridata[i].keishousha_tosiyoriid=-1;

						break;
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
			if (kabushutokuzumiflag!=1){
				//期間限定一代年寄が期間ギリギリなら下のルーチンを復活させてもいいかもしれないけど
				//下のルーチンを復活させるならすでにレンタル済みかどうかの確認必要
				//sishouflag==0もくわえろ！！！！(レンタルと後継者との判断のため)
				for (ii=0;ii<106;ii++){//期間限定一代年寄のレンタル取得、襲名
					if (tosiyoridata[ii].shozokuheyaid==-1 
					&& (tosiyoridata[ii].keishousha_rikisiid!=-1 || tosiyoridata[ii].keishousha_tosiyoriid!=-1) 
					&& tosiyoridata[ii].sishouflag==0){
					if((tosiyoridata[i].category==5 && year-tosiyoridata[i].startyear>=5) //期間ギリギリの絞り
					|| (tosiyoridata[i].category==6 && year-tosiyoridata[i].startyear>=3)){
						//heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;
						//heya_tosiyorisuu[tosiyoridata[ii].shozokuheyaid]++;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"期間限定一代年寄%s(%d才)が年寄株%sをレンタルし襲名\n",
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"期間限定一代年寄%s(%d才)が年寄株%sをレンタルし襲名",
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						shutoku_tosiyoriid=ii;
						shuumei_tosiyoriid=ii;
						tosiyoridata[ii].age=tosiyoridata[i].age;
							tosiyoridata[ii].category=1;//Ａカテの1
						tosiyoridata[ii].startyear=year;//+1必要かな？
						for (iii=0;iii<TOSIYORISUU;iii++){
							if (tosiyoridata[iii].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
								tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
								break;
							}
						}
						tosiyoridata[ii].shozokuheyaid=tosiyoridata[i].shozokuheyaid;
						//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
						strcpy(tosiyoridata[ii].sikona,tosiyoridata[i].sikona);
						tosiyoridata[ii].jinbou=tosiyoridata[i].jinbou;
						tosiyoridata[ii].rikisiid=tosiyoridata[i].rikisiid;
						tosiyoridata[ii].sishouflag=0;
						tosiyoridata[ii].rijiflag=0;
						//tosiyoridata[ii].keishousha_rikisiidは留保ついたままでいいので
						//tosiyoridata[ii].keishousha_tosiyoriidは留保ついたままでいいので
						tosiyoridata[i].shozokuheyaid=-1;
						//tosiyoridata[i].shozokuitimonid=-1;
						//リセット処理	
						tosiyoridata[i].age=0;
						tosiyoridata[i].category=0;
						tosiyoridata[i].startyear=0;
						tosiyoridata[i].rikisiid=-1;
						strcpy(tosiyoridata[i].sikona,"\0");
						tosiyoridata[i].sishouflag=0;
						if (i>=200){
							strcpy(tosiyoridata[i].namestring,"\0");
						}
						tosiyoridata[i].jinbou=0;
						tosiyoridata[i].rijiflag=0;
						tosiyoridata[i].keishousha_rikisiid=-1;
						tosiyoridata[i].keishousha_tosiyoriid=-1;
						break;
					}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
		}
	}
	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}

//ver3.13α008で追加した一門優先レンタル株主の優先処理(運が良ければ力士の取得処理に優先させる)
{
	char kabushutokuzumiflag=0;
	int temp_tosiyoriid=0;
	int warikomi_karikabu=0;
	char temp_string_kakuritu[301];
	char ch=0;
	int kazu=0;
	for (ii=0;ii<301;ii++){
		temp_string_kakuritu[ii]=0;
	}
	FILE *fpcsv;
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	strcpy(temp_filename,"data/warikomisisuu_karikabu.csv");
	fpcsv = fopen(temp_filename,"r");
	if( fpcsv == NULL ){
		fclose(fpcsv);
		fpcsv = fopen(temp_filename,"w");
		fprintf(fpcsv,"x/10%の確率で現役力士株取得に優先して一門内借株主取得処理を行う、x=0～1000\n");
		fprintf(fpcsv,"100\n");
		fprintf(fpcsv,"なお、この処理は一人取得すると終了します\n");
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		fclose(fpcsv);
		fpcsv = fopen(temp_filename,"r");
	}
	kazu=0;
	ch=1;
	while(1) 
	{
		for (ii=0;ii<301;ii++){
			temp_string_kakuritu[ii]=0;
		}
		if (ch == EOF){break;}
		for (ii=0;ii<300;ii++){
			ch = fgetc(fpcsv);
			if (ch == EOF){break;}
			if(ch == '\n'){
				break;
			}else{
				if(ch=='0'){
					strcat(temp_string_kakuritu,"0");
				}else if(ch=='1'){
					strcat(temp_string_kakuritu,"1");
				}else if(ch=='2'){
					strcat(temp_string_kakuritu,"2");
				}else if(ch=='3'){
					strcat(temp_string_kakuritu,"3");
				}else if(ch=='4'){
					strcat(temp_string_kakuritu,"4");
				}else if(ch=='5'){
					strcat(temp_string_kakuritu,"5");
				}else if(ch=='6'){
					strcat(temp_string_kakuritu,"6");
				}else if(ch=='7'){
					strcat(temp_string_kakuritu,"7");
				}else if(ch=='8'){
					strcat(temp_string_kakuritu,"8");
				}else if(ch=='9'){
					strcat(temp_string_kakuritu,"9");
				}
			}
		}
		if (kazu==1){
			warikomi_karikabu=atoi(temp_string_kakuritu);
			if (warikomi_karikabu<0){
				warikomi_karikabu=0;
			}
		}
		kazu++;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	fclose(fpcsv);
	if( ProcessMessage() == -1 ){mode=1;return ;}
///////debug//////
/*
FILE *fpdebug;
fpdebug = fopen("debug_warikomi_karikabu.csv","w");
fprintf(fpdebug,"%d年%d月,%d\n",year,month,warikomi_karikabu);
fclose(fpdebug);
*/
//////////////////

	if (GetRand(999)<warikomi_karikabu){
		for (i=0;i<TOSIYORISUU;i++){
			temp_tosiyoriid=i;	//このループの最後で逆代入
			i=jinboujun_tosiyoriid[i];
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if ((tosiyoridata[i].keishousha_tosiyoriid!=-1 || tosiyoridata[i].keishousha_rikisiid!=-1)
			&& tosiyoridata[i].shozokuheyaid!=-1 
			&& tosiyoridata[i].sishouflag==0	//師匠フラグでレンタル年寄かそれとも継承者を指名した師匠なのかを区別できる
			&& tosiyoridata[i].age<59	//部屋付が弟子に譲渡後も内部的にはレンタル状態なので除外するために年齢制限
			&& i<106){
				kabushutokuzumiflag=0;
				for (ii=0;ii<106;ii++){//株取得済みかどうか確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].keishousha_tosiyoriid==i){
						//if (tosiyoridata[ii].shozokuheyaid!=rikisidata[i].heyaid || (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid && tosiyoridata[ii].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
							kabushutokuzumiflag=1;
						//}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				if (kabushutokuzumiflag!=1){
					for (ii=0;ii<106;ii++){//空き名跡確認
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (tosiyoridata[ii].shozokuheyaid==-1 
							&& tosiyoridata[ii].shozokuitimonid==tosiyoridata[i].shozokuitimonid
							&& tosiyoridata[ii].keishousha_rikisiid==-1 
							&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
							//heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;
							//heya_tosiyorisuu[tosiyoridata[ii].shozokuheyaid]++;

	//記録必要フラグ書込み/////////////
	kirokuhituyouflag_tosiyoriid[i]=1;
	kirokuhituyouflag_tosiyoriid[ii]=1;
	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"年寄株を借りていた元%sの%s親方(%d才)が年寄株%sを取得し襲名(data/warikomisisuu_karikabu.csv処理)\n",
	tosiyoridata[i].sikona,
	tosiyoridata[i].namestring,
	tosiyoridata[i].age,
	tosiyoridata[ii].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"年寄株を借りていた元%sの%s親方(%d才)が年寄株%sを取得し襲名",
	tosiyoridata[i].sikona,
	tosiyoridata[i].namestring,
	tosiyoridata[i].age,
	tosiyoridata[ii].namestring);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	}
	//////////////////////////////////////////////////////////////
							kabushutokuzumiflag=1;
							tosiyoridata[ii].age=tosiyoridata[i].age;
							tosiyoridata[ii].category=tosiyoridata[i].category;
							tosiyoridata[ii].startyear=year;//+1必要かな？
							for (iii=0;iii<TOSIYORISUU;iii++){
								if (tosiyoridata[iii].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
									tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
									break;
								}
							}
							tosiyoridata[ii].shozokuheyaid=tosiyoridata[i].shozokuheyaid;
							strcpy(tosiyoridata[ii].sikona,tosiyoridata[i].sikona);
							tosiyoridata[ii].jinbou=tosiyoridata[i].jinbou;
							tosiyoridata[ii].rikisiid=tosiyoridata[i].rikisiid;
							tosiyoridata[ii].sishouflag=0;
							tosiyoridata[ii].rijiflag=0;
							tosiyoridata[ii].keishousha_rikisiid=-1;
							tosiyoridata[ii].keishousha_tosiyoriid=-1;
							tosiyoridata[i].shozokuheyaid=-1;
							//tosiyoridata[i].shozokuitimonid=-1;
							//リセット処理	
							tosiyoridata[i].age=0;
							tosiyoridata[i].category=0;
							tosiyoridata[i].startyear=0;
							tosiyoridata[i].rikisiid=-1;
							strcpy(tosiyoridata[i].sikona,"\0");
							tosiyoridata[i].sishouflag=0;
							if (i>=200){
								strcpy(tosiyoridata[i].namestring,"\0");
							}
							tosiyoridata[i].jinbou=0;
							tosiyoridata[i].rijiflag=0;
							//tosiyoridata[i].keishousha_rikisiid=-1;
							//tosiyoridata[i].keishousha_tosiyoriid=-1;
							break;
						}
					}
					if (kabushutokuzumiflag==1){break;}//一人でも取得すればこの処理は終了させるため
				}
			}
			i=temp_tosiyoriid;	//正常にループをさせるために元に戻す
		}
	}
}
	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}
	//ver3.13で追加した一門優先処理、現役力士が同じ一門で手放した株があればまずはそれを取得する処理
{
	int warikomi_yuushourikisiflag=0;
	int warikomi_jinbou=0;
	char temp_string_kakuritu[301];
	char ch=0;
	int kazu=0;
	for (ii=0;ii<301;ii++){
		temp_string_kakuritu[ii]=0;
	}
	FILE *fpcsv;
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	strcpy(temp_filename,"data/warikomisisuu.csv");
	fpcsv = fopen(temp_filename,"r");
	if( fpcsv == NULL ){
		fclose(fpcsv);
		fpcsv = fopen(temp_filename,"w");
		fprintf(fpcsv,"現役力士一門内株取得に一門外優勝力士を割り込ませるか、(1だと割り込み)\n");
		fprintf(fpcsv,"0\n");
		fprintf(fpcsv,"現役力士一門内株取得に人望で一門外力士を割込み(下の値以上だと割り込み)\n");
		fprintf(fpcsv,"10000\n");
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		fclose(fpcsv);
		fpcsv = fopen(temp_filename,"r");
	}
	kazu=0;
	ch=1;
	while(1) 
	{
		for (ii=0;ii<301;ii++){
			temp_string_kakuritu[ii]=0;
		}
		if (ch == EOF){break;}
		for (ii=0;ii<300;ii++){
			ch = fgetc(fpcsv);
			if (ch == EOF){break;}
			if(ch == '\n'){
				break;
			}else{
				if(ch=='0'){
					strcat(temp_string_kakuritu,"0");
				}else if(ch=='1'){
					strcat(temp_string_kakuritu,"1");
				}else if(ch=='2'){
					strcat(temp_string_kakuritu,"2");
				}else if(ch=='3'){
					strcat(temp_string_kakuritu,"3");
				}else if(ch=='4'){
					strcat(temp_string_kakuritu,"4");
				}else if(ch=='5'){
					strcat(temp_string_kakuritu,"5");
				}else if(ch=='6'){
					strcat(temp_string_kakuritu,"6");
				}else if(ch=='7'){
					strcat(temp_string_kakuritu,"7");
				}else if(ch=='8'){
					strcat(temp_string_kakuritu,"8");
				}else if(ch=='9'){
					strcat(temp_string_kakuritu,"9");
				}
			}
		}
		if (kazu==1){
			warikomi_yuushourikisiflag=atoi(temp_string_kakuritu);
		}else if(kazu==3){
			warikomi_jinbou=atoi(temp_string_kakuritu);
		}
		kazu++;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	fclose(fpcsv);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	for (i=0;i<RIKISISUU;i++){
		temp_rikisiid=i;	//このループの最後で逆代入
		i=jinboujun_rikisiid[i];
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//Aカテ要件
		if (rikisidata[i].jikosaiko_bandukenameid<=A_saikoui || sanyakuijouzaiisuu[i]>=A_sanyakuzaiisuu || makuutiijouzaiisuu[i]>=A_makuutizaiisuu){
			kabushutokuzumiflag=0;//株取得済みの力士かどうか確認
			for (ii=0;ii<106;ii++){//株取得済み力士かどうか確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].keishousha_rikisiid==i){
					//if (tosiyoridata[ii].shozokuheyaid!=rikisidata[i].heyaid || (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid && tosiyoridata[ii].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
						kabushutokuzumiflag=1;
					//}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			//一門内で空き名跡あれば取得処理
			if (kabushutokuzumiflag!=1){
				char rikisi_itimonid=0;
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (rikisidata[i].heyaid==tosiyoridata[ii].shozokuheyaid){
						rikisi_itimonid=tosiyoridata[ii].shozokuitimonid;
						break;
					}
				}
				for (ii=0;ii<106;ii++){//空き名跡確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].shozokuitimonid==rikisi_itimonid
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						//相場確認
						int kabuka=0;
						kabuka=kabusouba();
						if (kabuka<=heyadata[rikisidata[i].heyaid].hpoint){
							heyadata[rikisidata[i].heyaid].hpoint-=kabuka;
							tosiyoridata[ii].keishousha_rikisiid=i;
							kabushutokuzumiflag=1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(一門優先処理)\n",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							break;
						}else{
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"相場が%dpなので%s部屋の%s(%d才)は年寄株%sを取得できず(一門優先処理)\n",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
							break;
						}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
			//優勝経験力士割り込み処理、空き名跡あれば取得処理
			if (kabushutokuzumiflag!=1
				&& warikomi_yuushourikisiflag==1
				&& rikisidata[i].kiroku_yuushoukaisuu>0){//優勝経験あるなら
				for (ii=0;ii<106;ii++){//空き名跡確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						//相場確認
						int kabuka=0;
						kabuka=kabusouba()*2;
						heyadata[rikisidata[i].heyaid].hpoint-=kabuka;
						tosiyoridata[ii].keishousha_rikisiid=i;
						kabushutokuzumiflag=1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(優勝経験力士割り込み処理)\n",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						break;
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
			//人望高い力士割り込み処理、空き名跡あれば取得処理
			if (kabushutokuzumiflag!=1
				&& warikomi_jinbou<=jinbou_rikisi[i]){
				for (ii=0;ii<106;ii++){//空き名跡確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						//相場確認
						int kabuka=0;
						kabuka=kabusouba()*2;
						heyadata[rikisidata[i].heyaid].hpoint-=kabuka;
						tosiyoridata[ii].keishousha_rikisiid=i;
						kabushutokuzumiflag=1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(人望%d以上の力士なので割り込み処理 data/warikomisisuu.csv)\n",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
warikomi_jinbou);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						break;
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
		//Bカテ要件
		}else if (rikisidata[i].jikosaiko_bandukenameid<=B_saikoui || makuutiijouzaiisuu[i]>=B_makuutizaiisuu || juuryouijouzaiisuu[i]>=B_jyuuryouzaiisuu){
			kabushutokuzumiflag=0;//株取得済みの力士かどうか確認
			for (ii=0;ii<106;ii++){//株取得済み力士かどうか確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].keishousha_rikisiid==i){
					//if (tosiyoridata[ii].shozokuheyaid!=rikisidata[i].heyaid || (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid && tosiyoridata[ii].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
						kabushutokuzumiflag=1;
						break;
					//}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			//一門内で空き名跡あれば取得処理
			if (kabushutokuzumiflag!=1){
				char rikisi_itimonid=0;
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (rikisidata[i].heyaid==tosiyoridata[ii].shozokuheyaid){
						rikisi_itimonid=tosiyoridata[ii].shozokuitimonid;
						break;
					}
				}
				for (ii=0;ii<106;ii++){//空き名跡確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].shozokuitimonid==rikisi_itimonid
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						//相場確認
						int kabuka=0;
						kabuka=kabusouba();
						if (kabuka<=heyadata[rikisidata[i].heyaid].hpoint){
							heyadata[rikisidata[i].heyaid].hpoint-=kabuka;
							tosiyoridata[ii].keishousha_rikisiid=i;
							kabushutokuzumiflag=1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(一門優先処理)\n",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							break;
						}else{
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"相場が%dpなので%s部屋の%s(%d才)は年寄株%sを取得できず(一門優先処理)\n",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
							break;
						}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
			//優勝経験力士割り込み処理、空き名跡あれば取得処理
			if (kabushutokuzumiflag!=1
				&& warikomi_yuushourikisiflag==1
				&& rikisidata[i].kiroku_yuushoukaisuu>0){//優勝経験あるなら
				for (ii=0;ii<106;ii++){//空き名跡確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						//相場確認
						int kabuka=0;
						kabuka=kabusouba()*2;
						heyadata[rikisidata[i].heyaid].hpoint-=kabuka;
						tosiyoridata[ii].keishousha_rikisiid=i;
						kabushutokuzumiflag=1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(優勝経験力士割り込み処理)\n",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						break;
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
			//人望高い力士割り込み処理、空き名跡あれば取得処理
			if (kabushutokuzumiflag!=1
				&& warikomi_jinbou<=jinbou_rikisi[i]){
				for (ii=0;ii<106;ii++){//空き名跡確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						//相場確認
						int kabuka=0;
						kabuka=kabusouba()*2;
						heyadata[rikisidata[i].heyaid].hpoint-=kabuka;
						tosiyoridata[ii].keishousha_rikisiid=i;
						kabushutokuzumiflag=1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(人望%d以上の力士なので割り込み処理 data/warikomisisuu.csv)\n",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
warikomi_jinbou);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						break;
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
		//Cカテ要件
		}else if (makuutiijouzaiisuu[i]>=C_makuutizaiisuu || juuryouijouzaiisuu[i]>=C_jyuuryouzaiisuu){
		}
		i=temp_rikisiid;	//正常にループをさせるために元に戻す
	}
}
	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}
	//ver3.13で追加した現役力士が一門優先処理の後の一門関係なく取得する処理
	for (i=0;i<RIKISISUU;i++){
		temp_rikisiid=i;	//このループの最後で逆代入
		i=jinboujun_rikisiid[i];
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//Aカテ要件
		if (rikisidata[i].jikosaiko_bandukenameid<=A_saikoui || sanyakuijouzaiisuu[i]>=A_sanyakuzaiisuu || makuutiijouzaiisuu[i]>=A_makuutizaiisuu){
			kabushutokuzumiflag=0;//株取得済みの力士かどうか確認
			for (ii=0;ii<106;ii++){//株取得済み力士かどうか確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].keishousha_rikisiid==i){
					//if (tosiyoridata[ii].shozokuheyaid!=rikisidata[i].heyaid || (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid && tosiyoridata[ii].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
						kabushutokuzumiflag=1;
					//}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			//一門無関係の空き名跡あれば取得処理
			if (kabushutokuzumiflag!=1){
				for (ii=0;ii<106;ii++){//空き名跡確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						//相場確認
						int kabuka=0;
						kabuka=kabusouba()*2;
						if (kabuka<=heyadata[rikisidata[i].heyaid].hpoint){
							heyadata[rikisidata[i].heyaid].hpoint-=kabuka;
							tosiyoridata[ii].keishousha_rikisiid=i;
							kabushutokuzumiflag=1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(一門無関係処理)\n",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							break;
						}else{
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"相場が%dpなので%s部屋の%s(%d才)は年寄株%sを取得できず(一門無関係処理)\n",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
							break;
						}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
		//Bカテ要件
		}else if (rikisidata[i].jikosaiko_bandukenameid<=B_saikoui || makuutiijouzaiisuu[i]>=B_makuutizaiisuu || juuryouijouzaiisuu[i]>=B_jyuuryouzaiisuu){
			kabushutokuzumiflag=0;//株取得済みの力士かどうか確認
			for (ii=0;ii<106;ii++){//株取得済み力士かどうか確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].keishousha_rikisiid==i){
					//if (tosiyoridata[ii].shozokuheyaid!=rikisidata[i].heyaid || (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid && tosiyoridata[ii].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
						kabushutokuzumiflag=1;
						break;
					//}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			//一門無関係の空き名跡あれば取得処理
			if (kabushutokuzumiflag!=1){
				for (ii=0;ii<106;ii++){//空き名跡確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						//相場確認
						int kabuka=0;
						kabuka=kabusouba()*2;
						if (kabuka<=heyadata[rikisidata[i].heyaid].hpoint){
							heyadata[rikisidata[i].heyaid].hpoint-=kabuka;
							tosiyoridata[ii].keishousha_rikisiid=i;
							kabushutokuzumiflag=1;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(一門無関係処理)\n",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							break;
						}else{
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"相場が%dpなので%s部屋の%s(%d才)は年寄株%sを取得できず(一門無関係処理)\n",
kabuka,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
							break;
						}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
		//Cカテ要件
		}else if (makuutiijouzaiisuu[i]>=C_makuutizaiisuu || juuryouijouzaiisuu[i]>=C_jyuuryouzaiisuu){
		}
		i=temp_rikisiid;	//正常にループをさせるために元に戻す
	}
	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}
	//レンタル年寄の一門優先の株取得、襲名
	//さらに貸主が年寄なら戻す処理も必要なのか？→一代年寄が保有してるとしか考えられないから必要ないんじゃないの？
	for (i=0;i<TOSIYORISUU;i++){
		temp_tosiyoriid=i;//ループの最後で戻す
		i=jinboujun_tosiyoriid[i];
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if ((tosiyoridata[i].keishousha_tosiyoriid!=-1 || tosiyoridata[i].keishousha_rikisiid!=-1)
		&& tosiyoridata[i].shozokuheyaid!=-1 
		&& tosiyoridata[i].sishouflag==0	//師匠フラグでレンタル年寄かそれとも継承者を指名した師匠なのかを区別できる
		&& tosiyoridata[i].age<59	//部屋付が弟子に譲渡後も内部的にはレンタル状態なので除外するために年齢制限
		&& i<106){
			kabushutokuzumiflag=0;
			for (ii=0;ii<106;ii++){//株取得済みかどうか確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].keishousha_tosiyoriid==i){
					//if (tosiyoridata[ii].shozokuheyaid!=rikisidata[i].heyaid || (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid && tosiyoridata[ii].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
						kabushutokuzumiflag=1;
					//}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			if (kabushutokuzumiflag!=1){
				for (ii=0;ii<106;ii++){//空き名跡確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].shozokuitimonid==tosiyoridata[i].shozokuitimonid
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						//heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;
						//heya_tosiyorisuu[tosiyoridata[ii].shozokuheyaid]++;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"年寄株を借りていた元%sの%s親方(%d才)が年寄株%sを取得し襲名(一門優先処理)\n",
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"年寄株を借りていた元%sの%s親方(%d才)が年寄株%sを取得し襲名",
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						kabushutokuzumiflag=1;
						tosiyoridata[ii].age=tosiyoridata[i].age;
						tosiyoridata[ii].category=tosiyoridata[i].category;
						tosiyoridata[ii].startyear=year;//+1必要かな？
						for (iii=0;iii<TOSIYORISUU;iii++){
							if (tosiyoridata[iii].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
								tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
								break;
							}
						}
						tosiyoridata[ii].shozokuheyaid=tosiyoridata[i].shozokuheyaid;
						strcpy(tosiyoridata[ii].sikona,tosiyoridata[i].sikona);
						tosiyoridata[ii].jinbou=tosiyoridata[i].jinbou;
						tosiyoridata[ii].rikisiid=tosiyoridata[i].rikisiid;
						tosiyoridata[ii].sishouflag=0;
						tosiyoridata[ii].rijiflag=0;
						tosiyoridata[ii].keishousha_rikisiid=-1;
						tosiyoridata[ii].keishousha_tosiyoriid=-1;
						tosiyoridata[i].shozokuheyaid=-1;
						//tosiyoridata[i].shozokuitimonid=-1;
						//リセット処理	
						tosiyoridata[i].age=0;
						tosiyoridata[i].category=0;
						tosiyoridata[i].startyear=0;
						tosiyoridata[i].rikisiid=-1;
						strcpy(tosiyoridata[i].sikona,"\0");
						tosiyoridata[i].sishouflag=0;
						if (i>=200){
							strcpy(tosiyoridata[i].namestring,"\0");
						}
						tosiyoridata[i].jinbou=0;
						tosiyoridata[i].rijiflag=0;
						//tosiyoridata[i].keishousha_rikisiid=-1;
						//tosiyoridata[i].keishousha_tosiyoriid=-1;
						break;
					}
				}
			}
		}
		i=temp_tosiyoriid;
	}
	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}
	//レンタル年寄の一門無関係の株取得、襲名
	//さらに貸主が年寄なら戻す処理も必要なのか？→一代年寄が保有してるとしか考えられないから必要ないんじゃないの？
	for (i=0;i<TOSIYORISUU;i++){
		temp_tosiyoriid=i;//ループの最後で戻す
		i=jinboujun_tosiyoriid[i];
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if ((tosiyoridata[i].keishousha_tosiyoriid!=-1 || tosiyoridata[i].keishousha_rikisiid!=-1)
		&& tosiyoridata[i].shozokuheyaid!=-1 
		&& tosiyoridata[i].sishouflag==0	//師匠フラグでレンタル年寄かそれとも継承者を指名した師匠なのかを区別できる
		&& tosiyoridata[i].age<59	//部屋付が弟子に譲渡後も内部的にはレンタル状態なので除外するために年齢制限
		&& i<106){
			kabushutokuzumiflag=0;
			for (ii=0;ii<106;ii++){//株取得済みかどうか確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].keishousha_tosiyoriid==i){
					//if (tosiyoridata[ii].shozokuheyaid!=rikisidata[i].heyaid || (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid && tosiyoridata[ii].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
						kabushutokuzumiflag=1;
					//}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			if (kabushutokuzumiflag!=1){
				for (ii=0;ii<106;ii++){//空き名跡確認
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
						//heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;
						//heya_tosiyorisuu[tosiyoridata[ii].shozokuheyaid]++;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"年寄株を借りていた元%sの%s親方(%d才)が年寄株%sを取得し襲名(一門無関係処理)\n",
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"年寄株を借りていた元%sの%s親方(%d才)が年寄株%sを取得し襲名",
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						kabushutokuzumiflag=1;
						tosiyoridata[ii].age=tosiyoridata[i].age;
						tosiyoridata[ii].category=tosiyoridata[i].category;
						tosiyoridata[ii].startyear=year;//+1必要かな？
						for (iii=0;iii<TOSIYORISUU;iii++){
							if (tosiyoridata[iii].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
								tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
								break;
							}
						}
						tosiyoridata[ii].shozokuheyaid=tosiyoridata[i].shozokuheyaid;
						strcpy(tosiyoridata[ii].sikona,tosiyoridata[i].sikona);
						tosiyoridata[ii].jinbou=tosiyoridata[i].jinbou;
						tosiyoridata[ii].rikisiid=tosiyoridata[i].rikisiid;
						tosiyoridata[ii].sishouflag=0;
						tosiyoridata[ii].rijiflag=0;
						tosiyoridata[ii].keishousha_rikisiid=-1;
						tosiyoridata[ii].keishousha_tosiyoriid=-1;
						tosiyoridata[i].shozokuheyaid=-1;
						//tosiyoridata[i].shozokuitimonid=-1;
						//リセット処理	
						tosiyoridata[i].age=0;
						tosiyoridata[i].category=0;
						tosiyoridata[i].startyear=0;
						tosiyoridata[i].rikisiid=-1;
						strcpy(tosiyoridata[i].sikona,"\0");
						tosiyoridata[i].sishouflag=0;
						if (i>=200){
							strcpy(tosiyoridata[i].namestring,"\0");
						}
						tosiyoridata[i].jinbou=0;
						tosiyoridata[i].rijiflag=0;
						//tosiyoridata[i].keishousha_rikisiid=-1;
						//tosiyoridata[i].keishousha_tosiyoriid=-1;
						break;
					}
				}
			}
		}
		i=temp_tosiyoriid;
	}
	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}

	//部屋付親方が継承者として指名を受ける処理
	for (i=0;i<TOSIYORISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		heyatukiid=jinboujun_tosiyoriid[i];
		if (tosiyoridata[heyatukiid].shozokuheyaid>=0
		&& tosiyoridata[heyatukiid].sishouflag==0
		&& tosiyoridata[heyatukiid].keishousha_rikisiid==-1 
		&& tosiyoridata[heyatukiid].keishousha_tosiyoriid==-1
		&& (heyatukiid<106 || (heyatukiid>=200 && heyatukiid<300)) 
		&& (tosiyoridata[heyatukiid].category<=2 || tosiyoridata[heyatukiid].category==4)
		){
			for (ii=0;ii<106;ii++){//まだ継承者指名してない師匠か確認
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (tosiyoridata[ii].shozokuheyaid==tosiyoridata[heyatukiid].shozokuheyaid 
				&& tosiyoridata[ii].sishouflag==1 
				&& tosiyoridata[ii].keishousha_rikisiid==-1 
				&& tosiyoridata[ii].keishousha_tosiyoriid==-1
				&& tosiyoridata[ii].age >= 59
				&& tosiyoridata[heyatukiid].age+5 < tosiyoridata[ii].age
				){
					sishouid=ii;
					tosiyoridata[sishouid].keishousha_tosiyoriid=heyatukiid;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[sishouid]=1;
//kirokuhituyouflag_tosiyoriid[heyatukiid]=1;//表示しようがないのでパス
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s親方(%d才)が師匠の%s(%d才)親方から後継者として指名される\n",
heyastring[tosiyoridata[heyatukiid].shozokuheyaid],
tosiyoridata[heyatukiid].namestring,
tosiyoridata[heyatukiid].age,
tosiyoridata[sishouid].namestring,
tosiyoridata[sishouid].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s親方(%d才)が師匠の%s(%d才)親方から後継者として指名される",
heyastring[tosiyoridata[heyatukiid].shozokuheyaid],
tosiyoridata[heyatukiid].namestring,
tosiyoridata[heyatukiid].age,
tosiyoridata[sishouid].namestring,
tosiyoridata[sishouid].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////

				}
			}
		}
	}


	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}
	//期間限定年寄の引退
	for (i=300;i<TOSIYORISUU;i++){
		if (tosiyoridata[i].shozokuheyaid!=-1 
		&& year-tosiyoridata[i].startyear>5 && tosiyoridata[i].category==5){//横綱期間限定一代年寄
			heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"期間限定一代年寄元横綱%s(%d才)が廃業\n",
tosiyoridata[i].namestring,
tosiyoridata[i].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"期間限定一代年寄元横綱%s(%d才)が廃業",
tosiyoridata[i].namestring,
tosiyoridata[i].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
			tosiyoridata[i].shozokuheyaid=-1;
			//tosiyoridata[i].shozokuitimonid=-1;
			//リセット処理	
			tosiyoridata[i].age=0;
			tosiyoridata[i].category=0;
			tosiyoridata[i].startyear=0;
			tosiyoridata[i].rikisiid=-1;
			strcpy(tosiyoridata[i].sikona,"\0");
			tosiyoridata[i].sishouflag=0;
			if (i>=200){
				strcpy(tosiyoridata[i].namestring,"\0");
			}
			tosiyoridata[i].jinbou=0;
			tosiyoridata[i].rijiflag=0;
			tosiyoridata[i].keishousha_rikisiid=-1;
			tosiyoridata[i].keishousha_tosiyoriid=-1;
		}else if(tosiyoridata[i].shozokuheyaid!=-1 
		&& year-tosiyoridata[i].startyear>3 && tosiyoridata[i].category==6){//大関期間限定一代年寄
			heya_tosiyorisuu[tosiyoridata[i].shozokuheyaid]--;

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"期間限定一代年寄元大関%s(%d才)が廃業\n",
tosiyoridata[i].namestring,
tosiyoridata[i].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"期間限定一代年寄元大関%s(%d才)が廃業",
tosiyoridata[i].namestring,
tosiyoridata[i].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
			tosiyoridata[i].shozokuheyaid=-1;
			//tosiyoridata[i].shozokuitimonid=-1;
			//リセット処理	
			tosiyoridata[i].age=0;
			tosiyoridata[i].category=0;
			tosiyoridata[i].startyear=0;
			tosiyoridata[i].rikisiid=-1;
			strcpy(tosiyoridata[i].sikona,"\0");
			tosiyoridata[i].sishouflag=0;
			if (i>=200){
				strcpy(tosiyoridata[i].namestring,"\0");
			}
			tosiyoridata[i].jinbou=0;
			tosiyoridata[i].rijiflag=0;
			tosiyoridata[i].keishousha_rikisiid=-1;
			tosiyoridata[i].keishousha_tosiyoriid=-1;
		}
	}

	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}

	if (heyadokuritumode==1){
	//年寄独立処理
		int tosiyoridokurituSisuu_kouseki_age1=0;
		int tosiyoridokurituSisuu_kouseki_sisuu_1=0;
		int tosiyoridokurituSisuu_kouseki_age2=0;
		int tosiyoridokurituSisuu_kouseki_sisuu_2=0;
		int tosiyoridokurituSisuu_Acate_age1=0;
		int tosiyoridokurituSisuu_Acate_sisuu_1=0;
		int tosiyoridokurituSisuu_Acate_age2=0;
		int tosiyoridokurituSisuu_Acate_sisuu_2=0;

		//独立指数ファイル読み込み(見つからなければ作成)
		FILE *fpcsv;
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		strcpy(temp_filename,"data/tosiyoridokuritusisuu.csv");
		fpcsv = fopen(temp_filename,"r");
		if( fpcsv == NULL ){
			fclose(fpcsv);
			fpcsv = fopen(temp_filename,"w");
			fprintf(fpcsv,"x才以下で(功績顕著一代年寄)\n");
			fprintf(fpcsv,"49\n");
			fprintf(fpcsv,"x/1000の確率\n");
			fprintf(fpcsv,"500\n");
			fprintf(fpcsv,"上の年齢を超えてx才以下で\n");
			fprintf(fpcsv,"55\n");
			fprintf(fpcsv,"x/1000の確率\n");
			fprintf(fpcsv,"10\n");
			fprintf(fpcsv,"x才以下で(Aカテ年寄)\n");
			fprintf(fpcsv,"49\n");
			fprintf(fpcsv,"x/1000の確率\n");
			fprintf(fpcsv,"50\n");
			fprintf(fpcsv,"上の年齢を超えてx才以下で\n");
			fprintf(fpcsv,"55\n");
			fprintf(fpcsv,"x/1000の確率\n");
			fprintf(fpcsv,"5\n");
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			fclose(fpcsv);
			fpcsv = fopen(temp_filename,"r");
		}
		kazu=0;
		ch=1;
		while(1) 
		{
			for (ii=0;ii<301;ii++){
				temp_string_kakuritu[ii]=0;
			}
			if (ch == EOF){break;}
			for (ii=0;ii<300;ii++){
				ch = fgetc(fpcsv);
				if (ch == EOF){break;}
				if(ch == '\n'){
					break;
				}else{
					if(ch=='0'){
						strcat(temp_string_kakuritu,"0");
					}else if(ch=='1'){
						strcat(temp_string_kakuritu,"1");
					}else if(ch=='2'){
						strcat(temp_string_kakuritu,"2");
					}else if(ch=='3'){
						strcat(temp_string_kakuritu,"3");
					}else if(ch=='4'){
						strcat(temp_string_kakuritu,"4");
					}else if(ch=='5'){
						strcat(temp_string_kakuritu,"5");
					}else if(ch=='6'){
						strcat(temp_string_kakuritu,"6");
					}else if(ch=='7'){
						strcat(temp_string_kakuritu,"7");
					}else if(ch=='8'){
						strcat(temp_string_kakuritu,"8");
					}else if(ch=='9'){
						strcat(temp_string_kakuritu,"9");
					}
				}
			}
			if (kazu==1){
				tosiyoridokurituSisuu_kouseki_age1=atoi(temp_string_kakuritu);
			}else if(kazu==3){
				tosiyoridokurituSisuu_kouseki_sisuu_1=atoi(temp_string_kakuritu);
			}else if(kazu==5){
				tosiyoridokurituSisuu_kouseki_age2=atoi(temp_string_kakuritu);
			}else if(kazu==7){
				tosiyoridokurituSisuu_kouseki_sisuu_2=atoi(temp_string_kakuritu);
			}else if(kazu==9){
				tosiyoridokurituSisuu_Acate_age1=atoi(temp_string_kakuritu);
			}else if(kazu==11){
				tosiyoridokurituSisuu_Acate_sisuu_1=atoi(temp_string_kakuritu);
			}else if(kazu==13){
				tosiyoridokurituSisuu_Acate_age2=atoi(temp_string_kakuritu);
			}else if(kazu==15){
				tosiyoridokurituSisuu_Acate_sisuu_2=atoi(temp_string_kakuritu);
			}
			kazu++;
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		fclose(fpcsv);
		if( ProcessMessage() == -1 ){mode=1;return ;}
		//念のため所属年寄数、所属力士数を再確認
		heyasuu_genzon=0;//年寄が一人以上在籍している部屋数を確認
		//部屋ごとの年寄数確認
		for (i=0;i<HEYASUU;i++){
			heya_tosiyorisuu[i]=0;
			for (ii=0;ii<TOSIYORISUU;ii++){
				if (tosiyoridata[ii].shozokuheyaid==i){
					heya_tosiyorisuu[i]++;
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			if (heya_tosiyorisuu[i]>0){
				heyasuu_genzon++;
			}
		}
		//部屋ごとに所属力士数を数える
		for (ii=0;ii<HEYASUU;ii++){
			shozokurikisisuu[ii]=0;
		}
		for (ii=0;ii<HEYASUU;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			for (iii=0;iii<RIKISISUU;iii++){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (rikisidata[iii].heyaid==ii){
					shozokurikisisuu[ii]++;
				}
			}
		}
		//部屋ごとの番付順力士IDを検索
		for (ii=0;ii<HEYASUU;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			for (iii=0;iii<20;iii++){
				heyabandukejunid[ii][iii]=-1;
			}
		}
		count=0;
		for (ii=0;ii<HEYASUU;ii++){//部屋ID
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			for (iii=0;iii<RIKISISUU;iii++){//番付順ID
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (rikisidata[bandukejunid[iii]].heyaid==ii){
					heyabandukejunid[ii][count]=bandukejunid[iii];
					count++;
				}
			}
			count=0;
		}
		//功績顕著一代年寄の独立
		for (i=200;i<300;i++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (tosiyoridata[i].shozokuheyaid>=0){
				if (heyasuu_genzon<HEYASUU
					&& shozokurikisisuu[tosiyoridata[i].shozokuheyaid]>=2
					&& tosiyoridata[i].sishouflag!=1
					&& (tosiyoridata[i].startyear+1)<year
					&& ( (tosiyoridata[i].age<=tosiyoridokurituSisuu_kouseki_age1 && GetRand(999)<tosiyoridokurituSisuu_kouseki_sisuu_1) || (tosiyoridata[i].age>tosiyoridokurituSisuu_kouseki_age1 && tosiyoridata[i].age<=tosiyoridokurituSisuu_kouseki_age2 && GetRand(999)<tosiyoridokurituSisuu_kouseki_sisuu_2) )
					//&& GetRand(99)<100	//debug用で100%の確率にした
				){
					//師匠から継承者指名受けていないか確認
					simeizumiflag=0;
					for (ii=0;ii<106;ii++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (i!=ii && tosiyoridata[i].shozokuheyaid==tosiyoridata[ii].shozokuheyaid
							&& tosiyoridata[ii].sishouflag==1){
							if (tosiyoridata[ii].keishousha_tosiyoriid==i){
								simeizumiflag=1;
								break;
							}
						}
					}
					if (simeizumiflag==0){
						//ここに独立の処理
						//新設部屋の部屋ID決定
						heyaid_dokuritumoto=tosiyoridata[i].shozokuheyaid;
						for (ii=0;ii<HEYASUU;ii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							if (heya_tosiyorisuu[ii]==0){
								heyaid_dokuritusaki=ii;
								break;
							}
						}
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"一代年寄%s(%d才)が%s部屋から独立し、%s部屋を立ち上げました\n",
tosiyoridata[i].namestring,
tosiyoridata[i].age,
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"一代年寄%s(%d才)が%s部屋から独立し、%s部屋を立ち上げました",
tosiyoridata[i].namestring,
tosiyoridata[i].age,
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						//年寄変数関連
						tosiyoridata[i].shozokuheyaid=heyaid_dokuritusaki;
						tosiyoridata[i].sishouflag=1;
						strcpy(heyastring[heyaid_dokuritusaki],tosiyoridata[i].namestring);
						//部屋関連変数
						heyadata[heyaid_dokuritusaki].heyaid_tuusan=heyaid_used;
						heyaid_used++;
						heyadata[heyaid_dokuritusaki].hpoint=GetRand(2000)+1000;
						//yaoflag;//八百長をやる部屋かどうかのフラグはいじらず
						for (ii=0;ii<HEYASUU;ii++){
							heyadata[heyaid_dokuritusaki].kpoint[ii]=0;
						}
						heyadata[heyaid_dokuritusaki].keikoryou=0;
					 	heyadata[heyaid_dokuritusaki].jikosaiko_bandukenameid=rikisidata[heyabandukejunid[heyaid_dokuritusaki][0]].bandukenameid;
						heyadata[heyaid_dokuritusaki].jikosaiko_bandukesuuji=rikisidata[heyabandukejunid[heyaid_dokuritusaki][0]].bandukesuuji;
						heyadata[heyaid_dokuritusaki].yuushoukaisuu=0;
						heyadata[heyaid_dokuritusaki].yokodunasuu=0;
						heyadata[heyaid_dokuritusaki].startyear=year;
						heyadata[heyaid_dokuritusaki].startmonth=month;
						//一緒に連れて行く力士の決定
						//まずは道連れ力士変数初期化
						mitizuresuu=0;
						count_mitizuresuu=0;
						dokuritumoto_sishouid=0;
						//番付の下から順に最低1人最高でも部屋の人数の1/4+1を連れて行く
						mitizuresuu=GetRand((int)(shozokurikisisuu[heyaid_dokuritumoto]/4))+1;
						//師匠から継承者指名受けている力士は除外するための下準備
						for (iii=0;iii<TOSIYORISUU;iii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							if (tosiyoridata[iii].shozokuheyaid==heyaid_dokuritumoto
								&& tosiyoridata[iii].sishouflag==1){
								dokuritumoto_sishouid=iii;
								break;
							}
						}
						for (ii=0;ii<shozokurikisisuu[heyaid_dokuritumoto];ii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							//師匠から継承者指名受けている力士は除外
							if (tosiyoridata[dokuritumoto_sishouid].keishousha_rikisiid!=heyabandukejunid[heyaid_dokuritumoto][shozokurikisisuu[heyaid_dokuritumoto]-1-ii]){
								rikisidata[heyabandukejunid[heyaid_dokuritumoto][shozokurikisisuu[heyaid_dokuritumoto]-1-ii]].heyaid=heyaid_dokuritusaki;
								count_mitizuresuu++;
							}
							if (count_mitizuresuu>=mitizuresuu){break;}
						}
						shozokurikisisuu[heyaid_dokuritumoto]-=mitizuresuu;
						shozokurikisisuu[heyaid_dokuritusaki]+=mitizuresuu;
						//念のため所属年寄数、所属力士数を再確認
						heyasuu_genzon=0;//年寄が一人以上在籍している部屋数を確認
						//部屋ごとの年寄数確認
						for (iii=0;iii<HEYASUU;iii++){
							heya_tosiyorisuu[iii]=0;
							for (ii=0;ii<TOSIYORISUU;ii++){
								if (tosiyoridata[ii].shozokuheyaid==iii){
									heya_tosiyorisuu[iii]++;
								}
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							}
							if (heya_tosiyorisuu[iii]>0){
								heyasuu_genzon++;
							}
						}
						//部屋ごとに所属力士数を数える
						for (ii=0;ii<HEYASUU;ii++){
							shozokurikisisuu[ii]=0;
						}
						for (ii=0;ii<HEYASUU;ii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							for (iii=0;iii<RIKISISUU;iii++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								if (rikisidata[iii].heyaid==ii){
									shozokurikisisuu[ii]++;
								}
							}
						}
						//部屋ごとの番付順力士IDを検索
						for (ii=0;ii<HEYASUU;ii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							for (iii=0;iii<20;iii++){
								heyabandukejunid[ii][iii]=-1;
							}
						}
						count=0;
						for (ii=0;ii<HEYASUU;ii++){//部屋ID
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							for (iii=0;iii<RIKISISUU;iii++){//番付順ID
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								if (rikisidata[bandukejunid[iii]].heyaid==ii){
									heyabandukejunid[ii][count]=bandukejunid[iii];
									count++;
								}
							}
							count=0;
						}
					}
				}
			}
		}
		//Ａカテの独立
		for (i=0;i<106;i++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (tosiyoridata[i].shozokuheyaid>=0){
				if (heyasuu_genzon<HEYASUU
					&& shozokurikisisuu[tosiyoridata[i].shozokuheyaid]>=2
					&& tosiyoridata[i].sishouflag!=1
					&& tosiyoridata[i].category==1
					&& tosiyoridata[i].keishousha_rikisiid==-1
					&& tosiyoridata[i].keishousha_tosiyoriid==-1
					&& (tosiyoridata[i].startyear+1)<year

					&& ( (tosiyoridata[i].age<=tosiyoridokurituSisuu_Acate_age1 && GetRand(999)<tosiyoridokurituSisuu_Acate_sisuu_1) || (tosiyoridata[i].age>tosiyoridokurituSisuu_Acate_age1 && tosiyoridata[i].age<=tosiyoridokurituSisuu_Acate_age2 && GetRand(999)<tosiyoridokurituSisuu_Acate_sisuu_2) )
					//ver3.14まで→&& ( ( (tosiyoridata[i].startyear+4)>=year && GetRand(99)<5 ) || ( !((tosiyoridata[i].startyear+4)>=year) && GetRand(99)<1 ) )
					//ver3.14まで→&& tosiyoridata[i].age<=49
					//&& GetRand(99)<100	//debug用で100%の確率にした
				){
					//師匠から継承者指名受けていないか確認
					simeizumiflag=0;
					for (ii=0;ii<106;ii++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (i!=ii && tosiyoridata[i].shozokuheyaid==tosiyoridata[ii].shozokuheyaid
							&& tosiyoridata[ii].sishouflag==1){
							if (tosiyoridata[ii].keishousha_tosiyoriid==i){
								simeizumiflag=1;
								break;
							}
						}
					}
					if (simeizumiflag==0){
						//ここに独立の処理
						//新設部屋の部屋ID決定
						heyaid_dokuritumoto=tosiyoridata[i].shozokuheyaid;
						for (ii=0;ii<HEYASUU;ii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							if (heya_tosiyorisuu[ii]==0){
								heyaid_dokuritusaki=ii;
								break;
							}
						}
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が%s部屋から独立し、%s部屋を立ち上げました\n",
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が%s部屋から独立し、%s部屋を立ち上げました",
tosiyoridata[i].sikona,
tosiyoridata[i].namestring,
tosiyoridata[i].age,
heyastring[tosiyoridata[i].shozokuheyaid],
tosiyoridata[i].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						//年寄変数関連
						tosiyoridata[i].shozokuheyaid=heyaid_dokuritusaki;
						tosiyoridata[i].sishouflag=1;
						strcpy(heyastring[heyaid_dokuritusaki],tosiyoridata[i].namestring);
						//部屋関連変数
						heyadata[heyaid_dokuritusaki].heyaid_tuusan=heyaid_used;
						heyaid_used++;
						heyadata[heyaid_dokuritusaki].hpoint=GetRand(2000)+1000;
						//yaoflag;//八百長をやる部屋かどうかのフラグはいじらず
						for (ii=0;ii<HEYASUU;ii++){
							heyadata[heyaid_dokuritusaki].kpoint[ii]=0;
						}
						heyadata[heyaid_dokuritusaki].keikoryou=0;
					 	heyadata[heyaid_dokuritusaki].jikosaiko_bandukenameid=rikisidata[heyabandukejunid[heyaid_dokuritusaki][0]].bandukenameid;
						heyadata[heyaid_dokuritusaki].jikosaiko_bandukesuuji=rikisidata[heyabandukejunid[heyaid_dokuritusaki][0]].bandukesuuji;
						heyadata[heyaid_dokuritusaki].yuushoukaisuu=0;
						heyadata[heyaid_dokuritusaki].yokodunasuu=0;
						heyadata[heyaid_dokuritusaki].startyear=year;
						heyadata[heyaid_dokuritusaki].startmonth=month;
						//一緒に連れて行く力士の決定
						//まずは道連れ力士変数初期化
						mitizuresuu=0;
						count_mitizuresuu=0;
						dokuritumoto_sishouid=0;
						//番付の下から順に最低1人最高でも部屋の人数の1/4+1を連れて行く
						mitizuresuu=GetRand((int)(shozokurikisisuu[heyaid_dokuritumoto]/4))+1;
						//師匠から継承者指名受けている力士は除外するための下準備
						for (iii=0;iii<TOSIYORISUU;iii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							if (tosiyoridata[iii].shozokuheyaid==heyaid_dokuritumoto
								&& tosiyoridata[iii].sishouflag==1){
								dokuritumoto_sishouid=iii;
								break;
							}
						}
						for (ii=0;ii<shozokurikisisuu[heyaid_dokuritumoto];ii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							//師匠から継承者指名受けている力士は除外
							if (tosiyoridata[dokuritumoto_sishouid].keishousha_rikisiid!=heyabandukejunid[heyaid_dokuritumoto][shozokurikisisuu[heyaid_dokuritumoto]-1-ii]){
								rikisidata[heyabandukejunid[heyaid_dokuritumoto][shozokurikisisuu[heyaid_dokuritumoto]-1-ii]].heyaid=heyaid_dokuritusaki;
								count_mitizuresuu++;
							}
							if (count_mitizuresuu>=mitizuresuu){break;}
						}
						shozokurikisisuu[heyaid_dokuritumoto]-=mitizuresuu;
						shozokurikisisuu[heyaid_dokuritusaki]+=mitizuresuu;
						//念のため所属年寄数、所属力士数を再確認
						heyasuu_genzon=0;//年寄が一人以上在籍している部屋数を確認
						//部屋ごとの年寄数確認
						for (iii=0;iii<HEYASUU;iii++){
							heya_tosiyorisuu[iii]=0;
							for (ii=0;ii<TOSIYORISUU;ii++){
								if (tosiyoridata[ii].shozokuheyaid==iii){
									heya_tosiyorisuu[iii]++;
								}
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							}
							if (heya_tosiyorisuu[iii]>0){
								heyasuu_genzon++;
							}
						}
						//部屋ごとに所属力士数を数える
						for (ii=0;ii<HEYASUU;ii++){
							shozokurikisisuu[ii]=0;
						}
						for (ii=0;ii<HEYASUU;ii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							for (iii=0;iii<RIKISISUU;iii++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								if (rikisidata[iii].heyaid==ii){
									shozokurikisisuu[ii]++;
								}
							}
						}
						//部屋ごとの番付順力士IDを検索
						for (ii=0;ii<HEYASUU;ii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							for (iii=0;iii<20;iii++){
								heyabandukejunid[ii][iii]=-1;
							}
						}
						count=0;
						for (ii=0;ii<HEYASUU;ii++){//部屋ID
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							for (iii=0;iii<RIKISISUU;iii++){//番付順ID
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								if (rikisidata[bandukejunid[iii]].heyaid==ii){
									heyabandukejunid[ii][count]=bandukejunid[iii];
									count++;
								}
							}
							count=0;
						}
					}
				}
			}
		}

		{//一門独立合流処理はじまり/////////////////
			int suu_itimon=0;
			int suu_heyasuu_itimon[ITIMONSUU];
			int dokuritusakiid_itimon=0;
			char dameflag=0;
			int dokuritusuu=0;
			char dokurituflag_tosiyori[TOSIYORISUU];
			char temp_string_kakuritu[301];
			char ch=0;
			int kazu=0;
			int itimondokurituSisuu_2ika=0;
			int itimondokurituSisuu_3=0;
			int itimondokurituSisuu_4=0;
			int itimondokurituSisuu_5=0;
			int itimondokurituSisuu_6=0;
			int itimondokurituSisuu_7=0;
			int itimondokurituSisuu_8=0;
			int itimondokurituSisuu_9=0;
			int itimondokurituSisuu_10ijou=0;
			int itimondokurituSisuu_ketudan=0;
			int itimondokurituSisuu_heyatuki=0;
			for (ii=0;ii<301;ii++){
				temp_string_kakuritu[ii]=0;
			}
			for (i=0;i<TOSIYORISUU;i++){
				dokurituflag_tosiyori[i]=0;
			}
			for (i=0;i<ITIMONSUU;i++){
				suu_heyasuu_itimon[i]=0;
			}
			//指数ファイル読み込み(見つからなければ作成)
			FILE *fpcsv;
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			strcpy(temp_filename,"data/itimondokuritusisuu.csv");
			fpcsv = fopen(temp_filename,"r");
			if( fpcsv == NULL ){
				fclose(fpcsv);
				fpcsv = fopen(temp_filename,"w");
				fprintf(fpcsv,"独立指数(一門数2以下の場合、初期値300、大きいほど新一門創立の可能性高くなる。最大10000)\n");
				fprintf(fpcsv,"300\n");
				fprintf(fpcsv,"独立指数(一門数3の場合、初期値200)\n");
				fprintf(fpcsv,"200\n");
				fprintf(fpcsv,"独立指数(一門数4の場合、初期値200)\n");
				fprintf(fpcsv,"200\n");
				fprintf(fpcsv,"独立指数(一門数5の場合、初期値100)\n");
				fprintf(fpcsv,"100\n");
				fprintf(fpcsv,"独立指数(一門数6の場合、初期値50)\n");
				fprintf(fpcsv,"50\n");
				fprintf(fpcsv,"独立指数(一門数7の場合、初期値10)\n");
				fprintf(fpcsv,"10\n");
				fprintf(fpcsv,"独立指数(一門数8の場合、初期値1)\n");
				fprintf(fpcsv,"1\n");
				fprintf(fpcsv,"独立指数(一門数9の場合、初期値1)\n");
				fprintf(fpcsv,"1\n");
				fprintf(fpcsv,"独立指数(一門数10以上の場合、初期値1)\n");
				fprintf(fpcsv,"1\n");
				fprintf(fpcsv,"独立決断指数(部屋単位で新一門に加わろうとする指数、初期値13、小さいほど新一門に加わりやすい。なお、３部屋以上集まらないと新一門不成立)\n");
				fprintf(fpcsv,"13\n");
				fprintf(fpcsv,"独立決断指数(部屋単位で加わらなくても部屋付の親方が個別に新一門に加わろうと決断する指数、初期値40、小さいほど新一門に加入しやすくなる)\n");
				fprintf(fpcsv,"40\n");
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				fclose(fpcsv);
				if( ProcessMessage() == -1 ){mode=1;return ;}
				fpcsv = fopen(temp_filename,"r");
			}
			kazu=0;
			ch=1;
			while(1) 
			{
				for (ii=0;ii<301;ii++){
					temp_string_kakuritu[ii]=0;
				}
				if (ch == EOF){break;}
				for (ii=0;ii<300;ii++){
					ch = fgetc(fpcsv);
					if (ch == EOF){break;}
					if(ch == '\n'){
						break;
					}else{
						if(ch=='0'){
							strcat(temp_string_kakuritu,"0");
						}else if(ch=='1'){
							strcat(temp_string_kakuritu,"1");
						}else if(ch=='2'){
							strcat(temp_string_kakuritu,"2");
						}else if(ch=='3'){
							strcat(temp_string_kakuritu,"3");
						}else if(ch=='4'){
							strcat(temp_string_kakuritu,"4");
						}else if(ch=='5'){
							strcat(temp_string_kakuritu,"5");
						}else if(ch=='6'){
							strcat(temp_string_kakuritu,"6");
						}else if(ch=='7'){
							strcat(temp_string_kakuritu,"7");
						}else if(ch=='8'){
							strcat(temp_string_kakuritu,"8");
						}else if(ch=='9'){
							strcat(temp_string_kakuritu,"9");
						}
					}
				}
				if (kazu==1){
					itimondokurituSisuu_2ika=atoi(temp_string_kakuritu);
				}else if(kazu==3){
					itimondokurituSisuu_3=atoi(temp_string_kakuritu);
				}else if(kazu==5){
					itimondokurituSisuu_4=atoi(temp_string_kakuritu);
				}else if(kazu==7){
					itimondokurituSisuu_5=atoi(temp_string_kakuritu);
				}else if(kazu==9){
					itimondokurituSisuu_6=atoi(temp_string_kakuritu);
				}else if(kazu==11){
					itimondokurituSisuu_7=atoi(temp_string_kakuritu);
				}else if(kazu==13){
					itimondokurituSisuu_8=atoi(temp_string_kakuritu);
				}else if(kazu==15){
					itimondokurituSisuu_9=atoi(temp_string_kakuritu);
				}else if(kazu==17){
					itimondokurituSisuu_10ijou=atoi(temp_string_kakuritu);
				}else if(kazu==19){
					itimondokurituSisuu_ketudan=atoi(temp_string_kakuritu);
				}else if(kazu==21){
					itimondokurituSisuu_heyatuki=atoi(temp_string_kakuritu);
				}
				kazu++;
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			fclose(fpcsv);
			if( ProcessMessage() == -1 ){mode=1;return ;}

	/////////////debug//////////////
/*			strcpy(temp_filename,"data/itimondokuritusisuu_debug.csv");
				fpcsv = fopen(temp_filename,"w");
				fprintf(fpcsv,"独立指数(一門数2以下の場合、初期値300、大きいほど新一門創立の可能性高くなる)\n");
				fprintf(fpcsv,"%d\n",itimondokurituSisuu_2ika);
				fprintf(fpcsv,"独立指数(一門数3の場合、初期値200)\n");
				fprintf(fpcsv,"%d\n",itimondokurituSisuu_3);
				fprintf(fpcsv,"独立指数(一門数4の場合、初期値200)\n");
				fprintf(fpcsv,"%d\n",itimondokurituSisuu_4);
				fprintf(fpcsv,"独立指数(一門数5の場合、初期値100)\n");
				fprintf(fpcsv,"%d\n",itimondokurituSisuu_5);
				fprintf(fpcsv,"独立指数(一門数6の場合、初期値50)\n");
				fprintf(fpcsv,"%d\n",itimondokurituSisuu_6);
				fprintf(fpcsv,"独立指数(一門数7の場合、初期値10)\n");
				fprintf(fpcsv,"%d\n",itimondokurituSisuu_7);
				fprintf(fpcsv,"独立指数(一門数8の場合、初期値1)\n");
				fprintf(fpcsv,"%d\n",itimondokurituSisuu_8);
				fprintf(fpcsv,"独立指数(一門数9の場合、初期値1)\n");
				fprintf(fpcsv,"%d\n",itimondokurituSisuu_9);
				fprintf(fpcsv,"独立指数(一門数10以上の場合、初期値1)\n");
				fprintf(fpcsv,"%d\n",itimondokurituSisuu_10ijou);
				fprintf(fpcsv,"独立決断指数(各部屋の師匠が新一門に加わろうと決断する指数、初期値13、小さいほど新一門に加入しやすくなる)\n");
				fprintf(fpcsv,"%d\n",itimondokurituSisuu_ketudan);
				fprintf(fpcsv,"独立決断指数(師匠が加わろうとしていなくても部屋付の親方が個別に新一門に加わろうと決断する指数、初期値40、小さいほど新一門に加入しやすくなる)\n");
				fprintf(fpcsv,"%d\n",itimondokurituSisuu_heyatuki);
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				fclose(fpcsv);
*/


		//一門独立(一門からの離脱)処理
			//一門数の確認
			suu_itimon=0;
			for (i=0;i<ITIMONSUU;i++){
				if (itimondata[i].shuheyaid!=-1){
					suu_itimon++;
				}
			}
			//ここから独立検討
			if (suu_itimon<ITIMONSUU){
				//独立先一門IDの決定
				for (i=0;i<ITIMONSUU;i++){
					if (itimondata[i].shuheyaid==-1){
						dokuritusakiid_itimon=i;
						break;
					}
				}
				//一門数5以下の場合、高い確率で独立
				/*if ((suu_itimon<6 && GetRand(9999)<100)
					|| (suu_itimon==6 && GetRand(9999)<50)
					|| (suu_itimon==7 && GetRand(9999)<10)
					|| (suu_itimon>7 && GetRand(9999)<1)){
				*/
				if ((suu_itimon<3 && GetRand(9999)<itimondokurituSisuu_2ika)
					|| (suu_itimon==3 && GetRand(9999)<itimondokurituSisuu_3)
					|| (suu_itimon==4 && GetRand(9999)<itimondokurituSisuu_4)
					|| (suu_itimon==5 && GetRand(9999)<itimondokurituSisuu_5)
					|| (suu_itimon==6 && GetRand(9999)<itimondokurituSisuu_6)
					|| (suu_itimon==7 && GetRand(9999)<itimondokurituSisuu_7)
					|| (suu_itimon==8 && GetRand(9999)<itimondokurituSisuu_8)
					|| (suu_itimon==9 && GetRand(9999)<itimondokurituSisuu_9)
					|| (suu_itimon>9 && GetRand(9999)<itimondokurituSisuu_10ijou)){
					dokuritusuu=0;
					for (i=0;i<TOSIYORISUU;i++){
						dokurituflag_tosiyori[i]=0;
					}
					for (i=0;i<TOSIYORISUU;i++){
						if (tosiyoridata[i].shozokuheyaid!=-1
							&& tosiyoridata[i].sishouflag==1
							//&& GetRand(15)<1/////////////////ここのrand内の数字が肝
							&& GetRand(itimondokurituSisuu_ketudan)<1/////////////////ここのrand内の数字が肝
						){
							dameflag=0;
							for (ii=0;ii<ITIMONSUU;ii++){
								if (itimondata[ii].shuheyaid==tosiyoridata[i].shozokuheyaid){
									dameflag=1;
									break;
								}
							}
							if (dameflag==0){//仮独立処理
								dokurituflag_tosiyori[i]=1;
								dokuritusuu++;
								for (ii=0;ii<TOSIYORISUU;ii++){
									if (tosiyoridata[i].shozokuheyaid==tosiyoridata[ii].shozokuheyaid){
										dokurituflag_tosiyori[ii]=1;
									}
								}
							}
						}
					}
					//本独立処理
					if (dokuritusuu>2){//dokuritusuuが3部屋以上だったら本処理
						//一門主の決定
						//人望の一番高い師匠を一門主にする
						temp_tosiyoriid=0;temp_tosiyoriid=-1;
						temp_jinbou=0;temp_jinbou=-999999;
						for (i=0;i<TOSIYORISUU;i++){
							if (dokurituflag_tosiyori[i]==1
								&& tosiyoridata[i].sishouflag==1){
								if (temp_jinbou<tosiyoridata[i].jinbou){
									temp_jinbou=tosiyoridata[i].jinbou;
									temp_tosiyoriid=i;
								}
							}
						}
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s親方は新たな一門を立ち上げました\n",
tosiyoridata[temp_tosiyoriid].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s親方は新たな一門を立ち上げました",
tosiyoridata[temp_tosiyoriid].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						//代入処理
						itimondata[dokuritusakiid_itimon].shuheyaid=temp_tosiyoriid;
						strcpy(itimondata[dokuritusakiid_itimon].namestring,tosiyoridata[temp_tosiyoriid].namestring);
						itimondata[dokuritusakiid_itimon].itimonid_tuusan=itimonid_used;
						itimonid_used++;
						itimondata[dokuritusakiid_itimon].startyear=year;
						itimondata[dokuritusakiid_itimon].startmonth=month;
						for (i=0;i<TOSIYORISUU;i++){
							if (dokurituflag_tosiyori[i]==1){
								tosiyoridata[i].shozokuitimonid=dokuritusakiid_itimon;
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
if (i!=temp_tosiyoriid && tosiyoridata[i].sishouflag==1){
	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s部屋は%s親方に同調し、新たな一門に加わりました\n",
	heyastring[tosiyoridata[i].shozokuheyaid],
	tosiyoridata[temp_tosiyoriid].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋は%s親方に同調し、新たな一門に加わりました",
	heyastring[tosiyoridata[i].shozokuheyaid],
	tosiyoridata[temp_tosiyoriid].namestring);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	}
	//////////////////////////////////////////////////////////////
}
							}
						}
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						//部屋付で同調する親方を追加
						for (i=0;i<TOSIYORISUU;i++){
							dameflag=0;
							for (ii=0;ii<TOSIYORISUU;ii++){
								if (tosiyoridata[ii].keishousha_tosiyoriid==i){
									dameflag=1;
								}
							}
							if (dokurituflag_tosiyori[i]==0
							&& tosiyoridata[i].sishouflag==0
							&& tosiyoridata[i].shozokuheyaid!=-1
							&& tosiyoridata[i].keishousha_rikisiid==-1
							&& tosiyoridata[i].keishousha_tosiyoriid==-1
							&& dameflag!=1
							//&& GetRand(40)<1){//////////この確率も重要
							&& GetRand(itimondokurituSisuu_heyatuki)<1){//////////この確率も重要
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[i]=1;
if (i!=temp_tosiyoriid){
	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s部屋の%s親方は%s親方の動きに同調し、%s部屋に移籍しました\n",
	heyastring[tosiyoridata[i].shozokuheyaid],
	tosiyoridata[i].namestring,
	tosiyoridata[temp_tosiyoriid].namestring,
	heyastring[tosiyoridata[temp_tosiyoriid].shozokuheyaid]);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋の%s親方は%s親方の動きに同調し、%s部屋に移籍しました",
	heyastring[tosiyoridata[i].shozokuheyaid],
	tosiyoridata[i].namestring,
	tosiyoridata[temp_tosiyoriid].namestring,
	heyastring[tosiyoridata[temp_tosiyoriid].shozokuheyaid]);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	}
	//////////////////////////////////////////////////////////////
}
								tosiyoridata[i].shozokuitimonid=dokuritusakiid_itimon;
								tosiyoridata[i].shozokuheyaid=tosiyoridata[temp_tosiyoriid].shozokuheyaid;
							}
						}
					}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
		//一門合流処理
			/*
			//一門数の確認
			suu_itimon=0;
			for (i=0;i<ITIMONSUU;i++){
				if (itimondata[i].shuheyaid!=-1){
					suu_itimon++;
				}
			}
			//各一門ごとの所属部屋数確認
			for (i=0;i<ITIMONSUU;i++){
				suu_heyasuu_itimon[i]=0;
			}
			for (i=0;i<TOSIYORISUU;i++){
				if (tosiyoridata[i].sishouflag==1){
					suu_heyasuu_itimon[tosiyoridata[i].shozokuitimonid]++;
				}
			}
			//一門数が3以上の場合に合流処理発動
			//1部屋の一門は高い確率で合流処理
			for (i=0;i<ITIMONSUU;i++){
				if (suu_heyasuu_itimon[i]==1
					&& GetRand(0)<1){//この確率で調整
					


				}
			}
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			*/
		//部屋合併処理
			/*
			//各部屋ごとの所属力士数確認

			//各部屋ごとの所属関取数確認

			//各部屋ごとの年寄数確認

			//１年３月以降設立で設立後30年以上経過しているか
			//ゲーム開始時から設立されている場合で、？？？

			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			*/
		}//一門独立合流処理終わり////////////////////
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	}	//部屋独立モードＯＮの場合のif文の終端//

/*	4.01beta014から年をとる処理をgame_mainルーチンにもっていってみた
	九州場所で引退した力士の年齢重複加算対策
	if (month>=11){
		for (i=0;i<TOSIYORISUU;i++){
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (tosiyoridata[i].shozokuheyaid!=-1){
				tosiyoridata[i].age++;
			}
		}
	}
*/
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける



////////////////////////////////年寄関連処理ここまで//////////////////

/////四股名データ変換処理
sikona_c();
sikona_kouhosuu();
sikonahenkan();


if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	fp = fopen("data/namestring_mid.dat","rb");
	// オープンできなかったらここで終了
	if( fp == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		mode=1;
		return ;
	}
	fread(temp_namestring_mid,sizeof(temp_namestring_mid),1,fp);
	//クローズ
	fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	fp = fopen("data/namestring_mae.dat","rb");
	// オープンできなかったらここで終了
	if( fp == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		mode=1;
		return ;
	}
	fread(temp_namestring_mae,sizeof(temp_namestring_mae),1,fp);
	//クローズ
	fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	fp = fopen("data/namestring_ato.dat","rb");
	// オープンできなかったらここで終了
	if( fp == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		mode=1;
		return ;
	}
	fread(temp_namestring_ato,sizeof(temp_namestring_ato),1,fp);
	//クローズ
	fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	fp = fopen("data/heyabetu/namestring_heyabetu.dat","rb");
	// オープンできなかったらここで終了
	if( fp == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		mode=1;
		return ;
	}
	fread(temp_namestring_heyabetu,sizeof(temp_namestring_heyabetu),1,fp);
	//クローズ
	fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける


//	backup_keikoryou_sekkyokusei=rikisidata[heyabandukejunid[myheyaid][0]].keikoryou_sekkyokusei;
//	backup_keikoryou_konjou=rikisidata[heyabandukejunid[myheyaid][0]].keikoryou_konjou;
//	backup_keikoryou_nebari=rikisidata[heyabandukejunid[myheyaid][0]].keikoryou_nebari;
	
//	for (i=0;i<SICHOUSONSUU;i++){
//		counthometown=counthometown+hometownstring_used[i];//満遍なく各出身地を使うため
//	}
//	for (i=0;i<HEYASUU;i++){
//		countheya=countheya+heyastring_used[i];//所属部屋が満遍なく
//	}

	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////

	count=0;
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}
		if (rikisidata[i].heyaid==myheyaid) count++;
	}
	if (count<20 && heyadata[myheyaid].hpoint>=100
	 && superrikisisuu[2]!=2){
		//スカウトにかけるお金を決定
		SPoint = 0 ;
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
		DrawStringToHandle(300,5,"スカウト活動決定画面",CRWHITE,FontHandle12);
		//SetFontSize( 16 ) ;
		//DrawString(370,24,"ＭＥＮＵ",CRWHITE);
		i=0;
		DrawString(350,50+i*24,"金の卵を探す 100ｐ消費 (Y)",CRGREEN);i++;
		DrawString(350,50+i*24,"経験者を探す 200ｐ消費 (M)",CRGREEN);i++;
		DrawString(350,50+i*24,"今回は見送る(ENTER)",CRGREEN);i++;
		DrawString(187,369,"緑色の文字をクリックして",CRWHITE);
		DrawString(187,369+16,"スカウト活動を行うかを決定してください",CRWHITE);
		ScreenFlip();

		// ループ
		while(1)
		{
			// キー入力待ち(これを入れないと一気にカーソルがすっ飛んじゃう)
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){Sleep(1);}
			//キー入力に応じて処理
			if(get_mouseclick(200,50,637,50+16) || CheckHitKey_test( KEY_INPUT_Y )){
				SPoint=0;
				break;
			}
			if(get_mouseclick(200,50+24,637,50+24+16) || CheckHitKey_test( KEY_INPUT_M )){
				SPoint=1;
				break;
			}
			if(get_mouseclick(200,50+24+24,637,50+24+24+16) || CheckHitKey_test( KEY_INPUT_NUMPADENTER ) || CheckHitKey_test( KEY_INPUT_RETURN )){
				SPoint=2;
				break;
			}
			// メッセージ処理
			if( ProcessMessage() == -1 ){
				mode=1;
				break ;	// エラーが発生したらループを抜ける
			}
			Sleep(1);
		}//ループの終わり
		ClearDrawScreen();
		DrawString(100,100,"しばらくお待ちください",CRWHITE);
		ScreenFlip();

		// 項目に応じた処理を行う
		switch(SPoint){
		case 0:
			scoutmoney=100;
			filter_nouryoku_total_max=0;
			if (superrikisisuu[2]==1){
				ikuseihousin();
			}
			break;
		case 1:
			scoutmoney=200;
			tukedasi_sanndanmeflag=GetRand(1);
			filter_nouryoku_total_max=0;
			if (superrikisisuu[2]==1){
				ikuseihousin();
			}
			break;
		case 2:
			scoutmoney=0;
			break;
		}
	}else{
		scoutmoney=0;
	}
	
	//部屋のお金をスカウト費用分減らす	
	heyadata[myheyaid].hpoint-=scoutmoney;
	
	}//////////////////////////////////////////////////////
	//一人当たりのサイズ
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

	//引退力士決定/////////////////////////////////////
	intaisuu=0;//スキップ画面で「引」表示用
	for (i=0;i<RIKISISUU;i++){
		hoketuflag=0;
		if (retiresuu > 15){//一場所ごとの最大引退人数16人
//		if (retiresuu > 24){//一場所ごとの最大引退人数16人
			break;
		}
		retireflag=0;
		win=0;
		lost=0;
		for (ii=0;ii<15;ii++){
			if (rikisidata[i].winkonbasho[ii]==1){
				win++;
			}else if(rikisidata[i].lostkonbasho[ii]==1){
				lost++;
			}
		}
//if (rikisidata[i].bandukenameid==1){
//ClearDrawScreen();DrawFormatString(0,390,CRGREEN,"win%d kako_win[0]%d kako_win[1]%d",win,rikisidata[i].kako_win[0],rikisidata[i].kako_win[1]);ScreenFlip();WaitKey();
//}




		if (rikisidata[i].age>=DEATHAGE) retireflag=1;
//		if (rikisidata[i].age>=21) retireflag=1;
		if (rikisidata[i].age>23 && rikisidata[i].bandukenameid==9) retireflag=1;
		if (rikisidata[i].age>28 && rikisidata[i].bandukenameid>6 && lost>win) retireflag=1;
		if (rikisidata[i].age>29 && rikisidata[i].bandukenameid==6 && lost>win) retireflag=1;
		if (rikisidata[i].age>34 && lost>win && rikisidata[i].kako_lost[1]>rikisidata[i].kako_win[1] ) retireflag=1;
////////
		if (rikisidata[i].jikosaiko_bandukenameid==0){
			if (rikisidata[i].age>rikisidata[i].age_roukastart && retire_yokoduna_lost1<=lost && retire_yokoduna_lost1<=rikisidata[i].kako_lost[1]) retireflag=1;
			if (rikisidata[i].age>rikisidata[i].age_roukastart && retire_yokoduna_lost2<=lost) retireflag=1;
		}
		if (rikisidata[i].bandukenameid==0 && retire_yokoduna_lost3<=lost) retireflag=1; 
		if (rikisidata[i].jikosaiko_bandukenameid==1){
			if (rikisidata[i].age>rikisidata[i].age_roukastart && rikisidata[i].bandukenameid>=retire_oozeki_banduke1 && retire_oozeki_win1>=win && retire_oozeki_win1>=rikisidata[i].kako_win[1]) retireflag=1;
			if (rikisidata[i].age>rikisidata[i].age_roukastart && rikisidata[i].bandukenameid>=retire_oozeki_banduke2 && retire_oozeki_win2>=win) retireflag=1;
			if (rikisidata[i].bandukenameid>=retire_oozeki_banduke3 && retire_oozeki_win3>=win) retireflag=1; 
		}
///////
		if (rikisidata[i].jikosaiko_bandukenameid==2){
			if (rikisidata[i].age>rikisidata[i].age_roukastart && rikisidata[i].bandukenameid>3 && lost>win) retireflag=1;
		}
		if (rikisidata[i].jikosaiko_bandukenameid==3){
			if (rikisidata[i].age>rikisidata[i].age_roukastart && rikisidata[i].bandukenameid>4 && lost>win) retireflag=1;
		}
		if (rikisidata[i].jikosaiko_bandukenameid==4){
			if (rikisidata[i].age>rikisidata[i].age_roukastart && rikisidata[i].bandukenameid>4  && lost>win) retireflag=1;
		}
		if (rikisidata[i].jikosaiko_bandukenameid==5){
			if (rikisidata[i].age>rikisidata[i].age_roukastart && rikisidata[i].bandukenameid>5  && lost>win) retireflag=1;
		}
		if (rikisidata[i].jikosaiko_bandukenameid==6){
			if (rikisidata[i].age>rikisidata[i].age_roukastart && rikisidata[i].bandukenameid>6  && lost>win) retireflag=1;
		}
		if (rikisidata[i].jikosaiko_bandukenameid==7){
			if (rikisidata[i].age>rikisidata[i].age_roukastart && lost>win) retireflag=1;
		}
		if (rikisidata[i].jikosaiko_bandukenameid==8){
			if (rikisidata[i].age>rikisidata[i].age_roukastart && lost>win) retireflag=1;
		}
		if (rikisidata[i].jikosaiko_bandukenameid==9){
			if (rikisidata[i].age>rikisidata[i].age_roukastart && lost>win) retireflag=1;
		}
		
		if (retireflag==1){
			retiresuu++;

			intairikisikonbasho[intaisuu]=i;
			intaisuu++;
			
			rikisidata[i].retirekonbasho=1;
			if (shozokurikisisuu[rikisidata[i].heyaid]==1){
				if (rikisidata[i].heyaid==myheyaid){
					if (superrikisisuu[2]==2){
						gameover(i);
						return;
					}
					if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
						ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
						game_main_backscreen();//基本ゲーム画面表示ルーチン
						DrawString(187,369,"入門志願者がいたようです。",CRWHITE);
						DrawString(187,369+16,"Hit Any Key",CRWHITE);
						ScreenFlip() ;//裏画面を表画面にコピー
						WaitKey();
					}
					hoketuflag=2;//
				}else{
					hoketuflag=1;
				}
			}
			hometownstring_used[rikisidata[i].hometownid]=0;
			shozokurikisisuu[rikisidata[i].heyaid]--;
			//引退力士のデータを保存するルーチン
			//if (rikisidata[i].jikosaiko_bandukenameid<=5 
			// || rikisidata[i].heyaid==myheyaid){//関取経験者か自部屋力士のみと思ったけど全部にしちゃった
			if (1){//引退力士全部にしちゃいました
				retiresuu_total++;

				//ファイルオープン
				FILE *fp;
				FILE *fp2;
				//各連番ファイルのサイズ取得
				for (ii=0;ii<RETIREMAXFILESUU;ii++){
					if (ii==0){
						strcpy(temp_filename,"data/dat/r_kyuujou.dat\0");
						filesize_retire[ii]=Getfilesize(temp_filename);
					}else{
						sprintf(temp_filename,"data/dat/r_kyuujou%d.dat\0",ii+1);
						filesize_retire[ii]=Getfilesize(temp_filename);
						if (filesize_retire[ii]<0) break;
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				//引退力士用休場ファイル(追記)オープン
				for (ii=0;ii<RETIREMAXFILESUU;ii++){
					if (ii==0){
						if (filesize_retire[ii]<=maxfilesize){
							strcpy(temp_filename,"data/dat/r_kyuujou.dat\0");
							fp = fopen(temp_filename,"ab");
							break;
						}
					}else{
						if (filesize_retire[ii]<=maxfilesize){
							sprintf(temp_filename,"data/dat/r_kyuujou%d.dat\0",ii+1);
							fp = fopen(temp_filename,"ab");
							break;
						}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				//今回引退力士の休場ファイルオープン
				sprintf(temp_filename,"data/dat/kyuujou%d.dat\0",i);
				fp2 = fopen(temp_filename,"rb");
				kirokusuu=0;
				while(1){
					if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					//休場ファイル読み込み
					if(fread(&temp_rikisiid,sizeof(int),1,fp2)<1){//EOFor読み取り失敗
						fclose(fp2);
						fclose(fp);
						//indexファイル追記処理
						strcpy(temp_filename,"data/dat/r_kyuujou_index.dat\0");
						fp = fopen(temp_filename,"ab");
						fwrite(&temp_rikisiid,sizeof(int),1,fp);
						fwrite(&kirokusuu,sizeof(int),1,fp);
						fclose(fp);
						break;
					}
					fread(&temp_year,sizeof(int),1,fp2);
					fread(&temp_month,sizeof(int),1,fp2);
					fread(&temp_bandukenameid,sizeof(char),1,fp2);
					fread(&temp_bandukesuuji,sizeof(char),1,fp2);
					fread(&temp_yasumi,sizeof(int),1,fp2);
					fread(&temp_kyuujoustring,sizeof(temp_kyuujoustring),1,fp2);
					//休場ファイルへ追記
					fwrite(&temp_rikisiid,sizeof(int),1,fp);
					fwrite(&temp_year,sizeof(int),1,fp);
					fwrite(&temp_month,sizeof(int),1,fp);
					fwrite(&temp_bandukenameid,sizeof(char),1,fp);
					fwrite(&temp_bandukesuuji,sizeof(char),1,fp);
					fwrite(&temp_yasumi,sizeof(int),1,fp);
					fwrite(temp_kyuujoustring,sizeof(temp_kyuujoustring),1,fp);
					kirokusuu++;
				}
				//引退力士の休場ファイル初期化
				sprintf(temp_filename,"data/dat/kyuujou%d.dat\0",i);
				fp = fopen(temp_filename,"wb");
				fclose(fp);
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

				////ver2まででも使っていたファイルretirerikisi.dat
				//各連番ファイルのサイズ取得
				for (ii=0;ii<RETIREMAXFILESUU;ii++){
					if (ii==0){
						strcpy(temp_filename,"data/dat/retirerikisi.dat\0");
						filesize_retire[ii]=Getfilesize(temp_filename);
					}else{
						sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",ii+1);
						filesize_retire[ii]=Getfilesize(temp_filename);
						if (filesize_retire[ii]<0) break;
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				//引退順ファイル(追記)オープン
				for (ii=0;ii<RETIREMAXFILESUU;ii++){
					if (ii==0){
						if (filesize_retire[ii]<=maxfilesize){
							strcpy(temp_filename,"data/dat/retirerikisi.dat\0");
							fp = fopen(temp_filename,"ab");
							break;
						}
					}else{
						if (filesize_retire[ii]<=maxfilesize){
							sprintf(temp_filename,"data/dat/retirerikisi%d.dat\0",ii+1);
							fp = fopen(temp_filename,"ab");
							break;
						}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				//ここから書き込み
				fwrite(&rikisidata[i].rikisiid,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(namestring[rikisidata[i].nameid],sizeof(namestring[rikisidata[i].nameid]),1,fp);
				fwrite(hometownstring[rikisidata[i].hometownid],sizeof(hometownstring[rikisidata[i].hometownid]),1,fp);
				fwrite(heyastring[rikisidata[i].heyaid],sizeof(heyastring[rikisidata[i].heyaid]),1,fp);
				fwrite(&rikisidata[i].heyaid,sizeof(rikisidata[i].heyaid),1,fp);
				fwrite(&rikisidata[i].hatudohyo_year,sizeof(rikisidata[i].hatudohyo_year),1,fp);
				fwrite(&rikisidata[i].hatudohyo_month,sizeof(rikisidata[i].hatudohyo_month),1,fp);
				fwrite(&year,sizeof(year),1,fp);
				fwrite(&month,sizeof(month),1,fp);
				fwrite(&rikisidata[i].jikosaiko_bandukenameid,sizeof(rikisidata[i].jikosaiko_bandukenameid),1,fp);
				fwrite(&rikisidata[i].jikosaiko_bandukesuuji,sizeof(rikisidata[i].jikosaiko_bandukesuuji),1,fp);
				fwrite(&rikisidata[i].makuuti_win,sizeof(rikisidata[i].makuuti_win),1,fp);
				fwrite(&rikisidata[i].makuuti_lost,sizeof(rikisidata[i].makuuti_lost),1,fp);
				fwrite(&rikisidata[i].kiroku_yuushoukaisuu,sizeof(rikisidata[i].kiroku_yuushoukaisuu),1,fp);
				fwrite(&rikisidata[i].kinbosisuu,sizeof(rikisidata[i].kinbosisuu),1,fp);
				fwrite(&rikisidata[i].shukunshousuu,sizeof(rikisidata[i].shukunshousuu),1,fp);
				fwrite(&rikisidata[i].kantoushousuu,sizeof(rikisidata[i].kantoushousuu),1,fp);
				fwrite(&rikisidata[i].ginoushousuu,sizeof(rikisidata[i].ginoushousuu),1,fp);
				fwrite(&rikisidata[i].wintotal,sizeof(rikisidata[i].wintotal),1,fp);
				fwrite(&rikisidata[i].losttotal,sizeof(rikisidata[i].losttotal),1,fp);
				fwrite(&rikisidata[i].kiroku_renshou,sizeof(rikisidata[i].kiroku_renshou),1,fp);
				fwrite(&rikisidata[i].kiroku_renpai,sizeof(rikisidata[i].kiroku_renpai),1,fp);
				fwrite(rikisidata[i].kako_yuushouflag,sizeof(rikisidata[i].kako_yuushouflag),1,fp);
				fwrite(rikisidata[i].kako_bandukehigasiornisi,sizeof(rikisidata[i].kako_bandukehigasiornisi),1,fp);
				fwrite(rikisidata[i].kako_bandukenameid,sizeof(rikisidata[i].kako_bandukenameid),1,fp);
				fwrite(rikisidata[i].kako_bandukesuuji,sizeof(rikisidata[i].kako_bandukesuuji),1,fp);
				fwrite(rikisidata[i].kako_win,sizeof(rikisidata[i].kako_win),1,fp);
				fwrite(rikisidata[i].kako_lost,sizeof(rikisidata[i].kako_lost),1,fp);
				fwrite(&rikisidata[i].jikosaiko_tournament,sizeof(rikisidata[i].jikosaiko_tournament),1,fp);
				fwrite(&rikisidata[i].yuushoukaisuu_tournament,sizeof(rikisidata[i].yuushoukaisuu_tournament),1,fp);
				fwrite(&rikisidata[i].age,sizeof(rikisidata[i].age),1,fp);
				//クローズ
				fclose(fp);
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

				////////記録タブ用///////r_kiroku.dat
				//各連番ファイルのサイズ取得
				for (ii=0;ii<RETIREMAXFILESUU;ii++){
					if (ii==0){
						strcpy(temp_filename,"data/dat/r_kiroku.dat\0");
						filesize_retire[ii]=Getfilesize(temp_filename);
					}else{
						sprintf(temp_filename,"data/dat/r_kiroku%d.dat\0",ii+1);
						filesize_retire[ii]=Getfilesize(temp_filename);
						if (filesize_retire[ii]<0) break;
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				//ファイルオープン
				//r_kirokuファイルオープン
				for (ii=0;ii<RETIREMAXFILESUU;ii++){
					if (ii==0){
						if (filesize_retire[ii]<=maxfilesize){
							strcpy(temp_filename,"data/dat/r_kiroku.dat\0");
							fp = fopen(temp_filename,"ab");
							break;
						}
					}else{
						if (filesize_retire[ii]<=maxfilesize){
							sprintf(temp_filename,"data/dat/r_kiroku%d.dat\0",ii+1);
							fp = fopen(temp_filename,"ab");
							break;
						}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				//ここから書き込み
				fwrite(&rikisidata[i].rikisiid,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i],sizeof(rikisidata[i]),1,fp);
				/*
				fwrite(&rikisidata[i].kiroku_yuushoukaisuu,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].hatudohyo_year,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].hatudohyo_month,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].makuuti_win,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].kinbosisuu,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].shukunshousuu,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].kantoushousuu,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].ginoushousuu,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].jikosaiko_bandukenameid,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].jikosaiko_bandukesuuji,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].wintotal,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].losttotal,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].wintotal,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].kiroku_renshou,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].kiroku_renpai,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].jikosaiko_tournament,sizeof(rikisidata[i].rikisiid),1,fp);
				fwrite(&rikisidata[i].yuushoukaisuu_tournament,sizeof(rikisidata[i].rikisiid),1,fp);
				*/
				fwrite(&sanyakuijouzaiisuu[i],sizeof(sanyakuijouzaiisuu[i]),1,fp);
				fwrite(&makuutiijouzaiisuu[i],sizeof(makuutiijouzaiisuu[i]),1,fp);
				fwrite(&juuryouijouzaiisuu[i],sizeof(juuryouijouzaiisuu[i]),1,fp);
				fwrite(&stamina_natural_kakosaikou[i],sizeof(stamina_natural_kakosaikou[i]),1,fp);
				fwrite(&binshousei_natural_kakosaikou[i],sizeof(binshousei_natural_kakosaikou[i]),1,fp);

				//クローズ
				fclose(fp);
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

			}
			
/////////引退力士イベントログ記録（元十両以上）
if (rikisidata[i].jikosaiko_bandukenameid<6){
	char akikabusuu=0;
	char ryuuhosuu=0;
	//空き名跡数検索
	akikabusuu=0;ryuuhosuu=0;
	for (ii=0;ii<106;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (tosiyoridata[ii].shozokuheyaid==-1){
			akikabusuu++;
			if (tosiyoridata[ii].keishousha_rikisiid>=0 || tosiyoridata[ii].keishousha_tosiyoriid>=0){
				ryuuhosuu++;
			}
		}
	}
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才、最高位%s)が引退",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
bandukenamestring[rikisidata[i].jikosaiko_bandukenameid]);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (rikisidata[i].jikosaiko_bandukenameid<=A_saikoui || sanyakuijouzaiisuu[i]>=A_sanyakuzaiisuu || makuutiijouzaiisuu[i]>=A_makuutizaiisuu){
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp," Ａカテ要件クリア 人望%d 空き株%d(うち所有者あり%d)\n",
jinbou_rikisi[i],
akikabusuu,
ryuuhosuu);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
}else if (rikisidata[i].jikosaiko_bandukenameid<=B_saikoui || makuutiijouzaiisuu[i]>=B_makuutizaiisuu || juuryouijouzaiisuu[i]>=B_jyuuryouzaiisuu){
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp," Ｂカテ要件クリア 人望%d 空き株%d(うち所有者あり%d)\n",
jinbou_rikisi[i],
akikabusuu,
ryuuhosuu);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
}else{
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
bandukenamestring[rikisidata[i].jikosaiko_bandukenameid]);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
}
}
			//3.00年寄襲名判断/////////////年寄関連引退力士発生ごとの処理///////
			itidai_tosiyoriid=0;itidai_tosiyoriid=-1;
			shutoku_tosiyoriid=0;shutoku_tosiyoriid=-1;
			shuumei_tosiyoriid=0;shuumei_tosiyoriid=-1;
			//Ａカテ
//			if (rikisidata[i].jikosaiko_bandukenameid<=4){//debug用
			if (rikisidata[i].jikosaiko_bandukenameid<=A_saikoui || sanyakuijouzaiisuu[i]>=A_sanyakuzaiisuu || makuutiijouzaiisuu[i]>=A_makuutizaiisuu){
				//優勝回数20回以上横綱の一代年寄襲名
//				if (1){//debug用
				if (rikisidata[i].kiroku_yuushoukaisuu>=20){
					koukeishaflag=0;
					for (ii=0;ii<106;ii++){//継承指名済みか確認、継承済みなら一代年寄は襲名しない
						if (tosiyoridata[ii].keishousha_rikisiid==i
						&& tosiyoridata[ii].sishouflag==1){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が退職。\n後継者指名を受けていた%s部屋の%s(%d才)が年寄%sを襲名\nなお、功績顕著一代年寄の話もありましたが、断った模様です。\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が退職。後継者指名を受けていた",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"%s部屋の%s(%d才)が年寄%sを襲名。なお、功績顕著一代年寄の話もありましたが、断った模様です",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							koukeishaflag=1;
							shutoku_tosiyoriid=ii;
							shuumei_tosiyoriid=ii;
							tosiyoridata[ii].age=rikisidata[i].age;
							tosiyoridata[ii].category=1;//Ａカテの1
							tosiyoridata[ii].startyear=year;//+1必要かな？
							for (iii=0;iii<TOSIYORISUU;iii++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}
								if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
									tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
									break;
								}
							}
							tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
							//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
							strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
							tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
							//tosiyoridata[ii].sishouflagはいじらない
							tosiyoridata[ii].jinbou=jinbou_rikisi[i];
							tosiyoridata[ii].rijiflag=0;
							tosiyoridata[ii].keishousha_rikisiid=-1;
							tosiyoridata[ii].keishousha_tosiyoriid=-1;
							break;
						}
					}
					if (koukeishaflag==0){
						for (ii=200;ii<300;ii++){
							if (tosiyoridata[ii].shozokuheyaid==-1){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s部屋の%s(%d才)が功績顕著一代年寄%sを襲名\n",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	rikisidata[i].age,
	namestring[i]);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が功績顕著一代年寄%sを襲名",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	rikisidata[i].age,
	namestring[i]);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								itidai_tosiyoriid=ii;
								tosiyoridata[ii].age=rikisidata[i].age;
								//tosiyoridata[ii].category=5;//期間限定一代年寄の5
								tosiyoridata[ii].category=4;//功績一代の4
								tosiyoridata[ii].startyear=year;//+1必要かな？
								for (iii=0;iii<TOSIYORISUU;iii++){
									//if( ProcessMessage() == -1 ){mode=1;return ;}
									if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
										tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
										break;
									}
								}
								tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
								strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
								strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
								tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
								tosiyoridata[ii].sishouflag=0;
								tosiyoridata[ii].jinbou=jinbou_rikisi[i];
								tosiyoridata[ii].rijiflag=0;
								tosiyoridata[ii].keishousha_rikisiid=-1;
								tosiyoridata[ii].keishousha_tosiyoriid=-1;
								break;
							}
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
						//さらに空名跡取得済みなら力士名義から年寄名義に書き換え改め手放す処理
						for (ii=0;ii<106;ii++){
							if (tosiyoridata[ii].keishousha_rikisiid==i){
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%sは保有していた年寄株%sを手放す\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%sは保有していた年寄株%sを手放す",
heyastring[rikisidata[i].heyaid],
namestring[i],
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								tosiyoridata[ii].keishousha_rikisiid=-1;
								//現役力士取得処理
								{
									int temp_rikisiid=0;
									char a_kabushutokuzumiflag=0;
									int ia=0;
									int iia=0;
									int warikomi_yuushourikisiflag=0;
									int warikomi_jinbou=0;
									char temp_string_kakuritu[301];
									char ch=0;
									int kazu=0;
									for (iia=0;iia<301;iia++){
										temp_string_kakuritu[iia]=0;
									}
									FILE *fpcsv;
									if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									strcpy(temp_filename,"data/warikomisisuu.csv");
									fpcsv = fopen(temp_filename,"r");
									if( fpcsv == NULL ){
										fclose(fpcsv);
										fpcsv = fopen(temp_filename,"w");
										fprintf(fpcsv,"現役力士一門内株取得に一門外優勝力士を割り込ませるか、(1だと割り込み)\n");
										fprintf(fpcsv,"0\n");
										fprintf(fpcsv,"現役力士一門内株取得に人望で一門外力士を割込み(下の値以上だと割り込み)\n");
										fprintf(fpcsv,"10000\n");
										if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										fclose(fpcsv);
										fpcsv = fopen(temp_filename,"r");
									}
									kazu=0;
									ch=1;
									while(1) 
									{
										for (iia=0;iia<301;iia++){
											temp_string_kakuritu[iia]=0;
										}
										if (ch == EOF){break;}
										for (iia=0;iia<300;iia++){
											ch = fgetc(fpcsv);
											if (ch == EOF){break;}
											if(ch == '\n'){
												break;
											}else{
												if(ch=='0'){
													strcat(temp_string_kakuritu,"0");
												}else if(ch=='1'){
													strcat(temp_string_kakuritu,"1");
												}else if(ch=='2'){
													strcat(temp_string_kakuritu,"2");
												}else if(ch=='3'){
													strcat(temp_string_kakuritu,"3");
												}else if(ch=='4'){
													strcat(temp_string_kakuritu,"4");
												}else if(ch=='5'){
													strcat(temp_string_kakuritu,"5");
												}else if(ch=='6'){
													strcat(temp_string_kakuritu,"6");
												}else if(ch=='7'){
													strcat(temp_string_kakuritu,"7");
												}else if(ch=='8'){
													strcat(temp_string_kakuritu,"8");
												}else if(ch=='9'){
													strcat(temp_string_kakuritu,"9");
												}
											}
										}
										if (kazu==1){
											warikomi_yuushourikisiflag=atoi(temp_string_kakuritu);
										}else if(kazu==3){
											warikomi_jinbou=atoi(temp_string_kakuritu);
										}
										kazu++;
										//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									}
									fclose(fpcsv);
									if( ProcessMessage() == -1 ){mode=1;return ;}
									for (ia=0;ia<RIKISISUU;ia++){
										temp_rikisiid=ia;	//このループの最後で逆代入
										ia=jinboujun_rikisiid[ia];
										//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
										//Aカテ・Ｂカテ要件
										if (rikisidata[ia].jikosaiko_bandukenameid<=B_saikoui || makuutiijouzaiisuu[ia]>=B_makuutizaiisuu || juuryouijouzaiisuu[ia]>=B_jyuuryouzaiisuu){
											a_kabushutokuzumiflag=0;//株取得済みの力士かどうか確認
											if (ia==i){//功績顕著の本人のIDはパス
												a_kabushutokuzumiflag=1;
											}
											for (iia=0;iia<106;iia++){//株取得済み力士かどうか確認
												//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
												if (tosiyoridata[iia].keishousha_rikisiid==ia){
													//if (tosiyoridata[iia].shozokuheyaid!=rikisidata[ia].heyaid || (tosiyoridata[iia].shozokuheyaid==rikisidata[ia].heyaid && tosiyoridata[iia].sishouflag!=1)){//要は師匠から継承者指名を受けている場合もkeishousha_rikisiidに入っているから
														a_kabushutokuzumiflag=1;
													//}
												}
												//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
											}
											//一門内で空き名跡あれば取得処理
											if (a_kabushutokuzumiflag!=1){
												char rikisi_itimonid=0;
												char a_rikisi_itimonid=0;
												for (iia=0;iia<TOSIYORISUU;iia++){
													if (rikisidata[ia].heyaid==tosiyoridata[iia].shozokuheyaid){
														rikisi_itimonid=tosiyoridata[iia].shozokuitimonid;
														break;
													}
												}
												for (iia=0;iia<TOSIYORISUU;iia++){
													if (rikisidata[i].heyaid==tosiyoridata[iia].shozokuheyaid){
														a_rikisi_itimonid=tosiyoridata[iia].shozokuitimonid;
														break;
													}
												}
												if (a_rikisi_itimonid==rikisi_itimonid){
													//相場確認
													int kabuka=0;
													kabuka=kabusouba();
													if (kabuka<=heyadata[rikisidata[ia].heyaid].hpoint){
														heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
														tosiyoridata[ii].keishousha_rikisiid=ia;
														a_kabushutokuzumiflag=1;
								//eventlog書き込み/////////////////////////////////////////
								fp = fopen("data/eventlog.txt","a");
								// オープンできなかったらここで終了
								if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
								fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(一門優先処理)\n",
								kabuka,
								heyastring[rikisidata[ia].heyaid],
								namestring[ia],
								rikisidata[ia].age,
								tosiyoridata[ii].namestring);
								//クローズ
								fclose(fp);
								if( ProcessMessage() == -1 ){mode=1;return ;}
								////////////////////////////////////////////////////////////
								if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
								ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
								DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
								kabuka,
								heyastring[rikisidata[ia].heyaid],
								namestring[ia],
								rikisidata[ia].age,
								tosiyoridata[ii].namestring);
								DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
								ScreenFlip() ;//裏画面を表画面にコピー
								WaitKey();
								}
								//////////////////////////////////////////////////////////////
														break;
													}else{
								//eventlog書き込み/////////////////////////////////////////
								fp = fopen("data/eventlog.txt","a");
								// オープンできなかったらここで終了
								if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
								fprintf(fp,"相場が%dpなので%s部屋の%s(%d才)は年寄株%sを取得できず(一門優先処理)\n",
								kabuka,
								heyastring[rikisidata[ia].heyaid],
								namestring[ia],
								rikisidata[ia].age,
								tosiyoridata[ii].namestring);
								//クローズ
								fclose(fp);
								if( ProcessMessage() == -1 ){mode=1;return ;}
								////////////////////////////////////////////////////////////
													}
												}
											}
											//優勝経験力士割り込み処理、空き名跡あれば取得処理
											if (a_kabushutokuzumiflag!=1
												&& warikomi_yuushourikisiflag==1
												&& rikisidata[ia].kiroku_yuushoukaisuu>0){//優勝経験あるなら
												//相場確認
												int kabuka=0;
												kabuka=kabusouba()*2;
												heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
												tosiyoridata[ii].keishousha_rikisiid=ia;
												a_kabushutokuzumiflag=1;
								//eventlog書き込み/////////////////////////////////////////
								fp = fopen("data/eventlog.txt","a");
								// オープンできなかったらここで終了
								if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
								fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(優勝経験力士割り込み処理)\n",
								kabuka,
								heyastring[rikisidata[ia].heyaid],
								namestring[ia],
								rikisidata[ia].age,
								tosiyoridata[ii].namestring);
								//クローズ
								fclose(fp);
								if( ProcessMessage() == -1 ){mode=1;return ;}
								////////////////////////////////////////////////////////////
								if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
								ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
								DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
								kabuka,
								heyastring[rikisidata[ia].heyaid],
								namestring[ia],
								rikisidata[ia].age,
								tosiyoridata[ii].namestring);
								DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
								ScreenFlip() ;//裏画面を表画面にコピー
								WaitKey();
								}
								//////////////////////////////////////////////////////////////
												break;
											}
											//人望高い力士割り込み処理、空き名跡あれば取得処理
											if (a_kabushutokuzumiflag!=1
												&& warikomi_jinbou<=jinbou_rikisi[ia]){
												//相場確認
												int kabuka=0;
												kabuka=kabusouba()*2;
												heyadata[rikisidata[ia].heyaid].hpoint-=kabuka;
												tosiyoridata[ii].keishousha_rikisiid=ia;
												a_kabushutokuzumiflag=1;
								//eventlog書き込み/////////////////////////////////////////
								fp = fopen("data/eventlog.txt","a");
								// オープンできなかったらここで終了
								if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
								fprintf(fp,"%dpで%s部屋の%s(%d才)が年寄株%sを取得(人望%d以上の力士なので割り込み処理 data/warikomisisuu.csv)\n",
								kabuka,
								heyastring[rikisidata[ia].heyaid],
								namestring[ia],
								rikisidata[ia].age,
								tosiyoridata[ii].namestring,
								warikomi_jinbou);
								//クローズ
								fclose(fp);
								if( ProcessMessage() == -1 ){mode=1;return ;}
								////////////////////////////////////////////////////////////
								if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
								ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
								DrawFormatString(0,369,CRWHITE,"%dpで%s部屋の%s(%d才)が年寄株%sを取得",
								kabuka,
								heyastring[rikisidata[ia].heyaid],
								namestring[ia],
								rikisidata[ia].age,
								tosiyoridata[ii].namestring);
								DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
								ScreenFlip() ;//裏画面を表画面にコピー
								WaitKey();
								}
								//////////////////////////////////////////////////////////////
												break;
											}
										}
										ia=temp_rikisiid;	//正常にループをさせるために元に戻す
									}
								}
								if (tosiyoridata[ii].keishousha_rikisiid==-1 && tosiyoridata[ii].shozokuheyaid!=-1){
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の元%sの%s親方は借株状態を解消するため完全取得(一門内現役力士で取得者なかったため)\n",
heyastring[tosiyoridata[ii].shozokuheyaid],
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の元%sの%s親方は借株状態を解消するため完全取得",
heyastring[tosiyoridata[ii].shozokuheyaid],
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								}
								break;
							}
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
						/*//さらに空名跡取得できたら取得(取得のみ)
						if (shutoku_tosiyoriid==-1){
							for (ii=0;ii<106;ii++){
								if (tosiyoridata[ii].shozokuheyaid==-1 
									&& tosiyoridata[ii].keishousha_rikisiid==-1 
									&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s部屋の%sは年寄株%sも取得\n",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	tosiyoridata[ii].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
									shutoku_tosiyoriid=ii;
									tosiyoridata[ii].keishousha_tosiyoriid=itidai_tosiyoriid;
									break;
								}
								if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							}
						}*/
					}
				}else{//功績顕著一代年寄襲名ならなかった場合(普通のAカテということ）
					//後継者指名もしくは取得済み株を襲名
					//中継ぎ登板親方だったりしたら元に戻る処理もした方が良いのでは？←この意味不明？？？
					for (ii=0;ii<106;ii++){
						if (tosiyoridata[ii].keishousha_rikisiid==i){
							//if (tosiyoridata[ii].shozokuheyaid!=-1){
							if (tosiyoridata[ii].sishouflag==1){//師匠フラグで後継者指名か判断

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が退職。\n後継者指名を受けていた%s部屋の%s(%d才)が年寄%sを襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が退職。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"後継者指名を受けていた%s部屋の%s(%d才)が年寄%sを襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							}else{
								if (tosiyoridata[ii].shozokuheyaid==-1){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								}else{
									if (tosiyoridata[ii].age>=60){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が退職\n%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が退職",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
									}else{
//ver3.11で借株人生を送れるようにしようとした部分
										char saikarikabuflag=0;
										for (iii=0;iii<106;iii++){//再レンタル取得、襲名
											if (tosiyoridata[iii].shozokuheyaid==-1 
											&& (tosiyoridata[iii].keishousha_rikisiid!=-1 || tosiyoridata[iii].keishousha_tosiyoriid!=-1) 
											&& tosiyoridata[iii].sishouflag==0){
//画面表示、イベントログ書込みと再レンタル処理のみ
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[iii]=1;
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が借りていた株を返却\n%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名\n元%sは年寄株%s(所有力士%s(%d才))をレンタルし再襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
tosiyoridata[ii].sikona,
tosiyoridata[iii].namestring,
namestring[tosiyoridata[iii].keishousha_rikisiid],
rikisidata[tosiyoridata[iii].keishousha_rikisiid].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が借りていた株を返却。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawFormatString(0,369+32,CRWHITE,"元%sは年寄株%s(所有力士%s(%d才))をレンタルし再襲名",
tosiyoridata[ii].sikona,
tosiyoridata[iii].namestring,
namestring[tosiyoridata[iii].keishousha_rikisiid],
rikisidata[tosiyoridata[iii].keishousha_rikisiid].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
												saikarikabuflag=1;
												tosiyoridata[iii].age=tosiyoridata[ii].age;
												tosiyoridata[iii].category=tosiyoridata[ii].category;
												tosiyoridata[iii].startyear=year;//+1必要かな？
												for (iiii=0;iiii<TOSIYORISUU;iiii++){
													if (tosiyoridata[iiii].shozokuheyaid==tosiyoridata[ii].shozokuheyaid){
														tosiyoridata[iii].shozokuitimonid=tosiyoridata[iiii].shozokuitimonid;
														break;
													}
												}
												tosiyoridata[iii].shozokuheyaid=tosiyoridata[ii].shozokuheyaid;
												strcpy(tosiyoridata[iii].sikona,tosiyoridata[ii].sikona);
												tosiyoridata[iii].jinbou=tosiyoridata[ii].jinbou;
												tosiyoridata[iii].rikisiid=tosiyoridata[ii].rikisiid;
												tosiyoridata[iii].sishouflag=0;
												tosiyoridata[iii].rijiflag=0;
												//tosiyoridata[iii].keishousha_rikisiidは留保ついたままでいいので
												//tosiyoridata[iii].keishousha_tosiyoriidは留保ついたままでいいので
												break;
											}
										}
										if (saikarikabuflag!=1){
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が借りていた株を返却するため廃業\n%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が借りていた株を返却するため廃業。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
										}
									}
								}
							}
							shutoku_tosiyoriid=ii;
							shuumei_tosiyoriid=ii;
							tosiyoridata[ii].age=rikisidata[i].age;
							tosiyoridata[ii].category=1;//Ａカテの1
							tosiyoridata[ii].startyear=year;//+1必要かな？
							for (iii=0;iii<TOSIYORISUU;iii++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}
								if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
									tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
									break;
								}
							}
							tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
							//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
							strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
							tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
							//tosiyoridata[ii].sishouflagはいじらない
							tosiyoridata[ii].jinbou=jinbou_rikisi[i];
							tosiyoridata[ii].rijiflag=0;
							tosiyoridata[ii].keishousha_rikisiid=-1;
							tosiyoridata[ii].keishousha_tosiyoriid=-1;
							break;
						}
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					}
					//空名跡取得襲名
					/*if (shutoku_tosiyoriid==-1){//
						char rikisi_itimonid=0;
						for (ii=0;ii<TOSIYORISUU;ii++){
							if (rikisidata[i].heyaid==tosiyoridata[ii].shozokuheyaid){
								rikisi_itimonid=tosiyoridata[ii].shozokuitimonid;
								break;
							}
						}
						for (ii=0;ii<106;ii++){
							if (tosiyoridata[ii].shozokuheyaid==-1 
							&& tosiyoridata[ii].shozokuitimonid==rikisi_itimonid
							&& tosiyoridata[ii].keishousha_rikisiid==-1 
							&& tosiyoridata[ii].keishousha_tosiyoriid==-1){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才)が年寄株%sを取得、襲名(一門優先処理)\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が年寄株%sを取得、襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								shutoku_tosiyoriid=ii;
								shuumei_tosiyoriid=ii;
								tosiyoridata[ii].age=rikisidata[i].age;
								tosiyoridata[ii].category=1;//Ａカテの1
								tosiyoridata[ii].startyear=year;//+1必要かな？
								for (iii=0;iii<TOSIYORISUU;iii++){
									if( ProcessMessage() == -1 ){mode=1;return ;}
									if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
										tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
										break;
									}
								}
								tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
								//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
								strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
								tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
								tosiyoridata[ii].sishouflag=0;
								tosiyoridata[ii].jinbou=jinbou_rikisi[i];
								tosiyoridata[ii].rijiflag=0;
								tosiyoridata[ii].keishousha_rikisiid=-1;
								tosiyoridata[ii].keishousha_tosiyoriid=-1;
								break;
							}
							if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
					}*/

					//ここに老化開始年齢が高めに設定されていることが原因で
					//要件をクリアしているにもかかわらず継承者指名・譲渡処理を受けられなかった力士を救済する処理
					//ただし、親方が継承者指名処理・譲渡処理を始める年齢（60才）以上の場合に限る
					if (shutoku_tosiyoriid==-1){
						for (ii=0;ii<106;ii++){//まだ継承者指名してない親方か確認
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							if (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid 
							//&& tosiyoridata[ii].sishouflag==1 
							&& tosiyoridata[ii].keishousha_rikisiid==-1 
							&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
								if(tosiyoridata[ii].age >= 60){
									if (tosiyoridata[ii].sishouflag==1){
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が退職。\n後継者指名を受けた%s部屋の%s(%d才)が%s部屋を継承、襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が退職。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"後継者指名を受けた%s部屋の%s(%d才)が%s部屋を継承、襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
									}else{
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が退職。\n年寄株を譲渡された%s部屋の%s(%d才)が%sを襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が退職。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"年寄株を譲渡された%s部屋の%s(%d才)が%s襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////

									}
									shutoku_tosiyoriid=ii;
									shuumei_tosiyoriid=ii;
									tosiyoridata[ii].age=rikisidata[i].age;
									tosiyoridata[ii].category=1;//Ａカテの1
									tosiyoridata[ii].startyear=year;//+1必要かな？
									for (iii=0;iii<TOSIYORISUU;iii++){
										//if( ProcessMessage() == -1 ){mode=1;return ;}
										if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
											tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
											break;
										}
									}
									tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
									//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
									strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
									tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
									//tosiyoridata[ii].sishouflagはいじらない
									tosiyoridata[ii].jinbou=jinbou_rikisi[i];
									tosiyoridata[ii].rijiflag=0;
									tosiyoridata[ii].keishousha_rikisiid=-1;
									tosiyoridata[ii].keishousha_tosiyoriid=-1;
									break;
								}
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							}
						}
					}
					if (shutoku_tosiyoriid==-1){//名跡取得できなくても横綱大関で期間限定になれるなら期間限定になる処理
						for (ii=300;ii<TOSIYORISUU;ii++){
							if (tosiyoridata[ii].shozokuheyaid==-1 
							&& rikisidata[i].jikosaiko_bandukenameid<2){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才)が期間限定一代年寄%sを襲名\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
namestring[i]);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が期間限定一代年寄%sを襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
namestring[i]);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								itidai_tosiyoriid=ii;
								tosiyoridata[ii].age=rikisidata[i].age;
								if (rikisidata[i].jikosaiko_bandukenameid==0){
									tosiyoridata[ii].category=5;//期間５年限定一代年寄元横綱の5
								}else{
									tosiyoridata[ii].category=6;//期間３年限定一代年寄元大関の6
								}
								tosiyoridata[ii].startyear=year;//+1必要かな？
								for (iii=0;iii<TOSIYORISUU;iii++){
									//if( ProcessMessage() == -1 ){mode=1;return ;}
									if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
										tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
										break;
									}
								}
								tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
								strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
								strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
								tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
								tosiyoridata[ii].sishouflag=0;
								tosiyoridata[ii].jinbou=jinbou_rikisi[i];
								tosiyoridata[ii].rijiflag=0;
								tosiyoridata[ii].keishousha_rikisiid=-1;
								tosiyoridata[ii].keishousha_tosiyoriid=-1;
								break;
							}
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
					}
				}
				if(itidai_tosiyoriid==-1 
				&& shutoku_tosiyoriid==-1 
				&& shuumei_tosiyoriid==-1
				){//ここまでで年寄襲名できていない場合、レンタルを模索する(keishousha_に留保あるやつ)
					for (ii=0;ii<106;ii++){
						if (tosiyoridata[ii].shozokuheyaid==-1 &&
						(tosiyoridata[ii].keishousha_rikisiid!=-1 //留保してていいので
						|| tosiyoridata[ii].keishousha_tosiyoriid!=-1) //留保してていいので
						&& tosiyoridata[ii].sishouflag==0
						){
							if(tosiyoridata[ii].keishousha_rikisiid!=-1){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才)が年寄株%s(所有力士%s(%d才))をレンタルし襲名\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
namestring[tosiyoridata[ii].keishousha_rikisiid],
rikisidata[tosiyoridata[ii].keishousha_rikisiid].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が年寄株%s(所有力士%s(%d才))をレンタルし襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
namestring[tosiyoridata[ii].keishousha_rikisiid],
rikisidata[tosiyoridata[ii].keishousha_rikisiid].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							}else{

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才)が年寄株%s(所有年寄%s(%d才))をレンタルし襲名\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
tosiyoridata[tosiyoridata[ii].keishousha_tosiyoriid].namestring,
tosiyoridata[tosiyoridata[ii].keishousha_tosiyoriid].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が年寄株%s(所有年寄%s(%d才))をレンタルし襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
tosiyoridata[tosiyoridata[ii].keishousha_tosiyoriid].namestring,
tosiyoridata[tosiyoridata[ii].keishousha_tosiyoriid].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							}
							shutoku_tosiyoriid=ii;
							shuumei_tosiyoriid=ii;
							tosiyoridata[ii].age=rikisidata[i].age;
							tosiyoridata[ii].category=1;//Ａカテの1
							tosiyoridata[ii].startyear=year;//+1必要かな？
							for (iii=0;iii<TOSIYORISUU;iii++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}
								if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
									tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
									break;
								}
							}
							tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
							//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
							strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
							tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
							tosiyoridata[ii].sishouflag=0;
							tosiyoridata[ii].jinbou=jinbou_rikisi[i];
							tosiyoridata[ii].rijiflag=0;
							//tosiyoridata[ii].keishousha_rikisiidは留保ついたままでいいので
							//tosiyoridata[ii].keishousha_tosiyoriidは留保ついたままでいいので
							break;
						}
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					}
				}
			//Bカテ
			}else if (rikisidata[i].jikosaiko_bandukenameid<=B_saikoui || makuutiijouzaiisuu[i]>=B_makuutizaiisuu || juuryouijouzaiisuu[i]>=B_jyuuryouzaiisuu){
				//後継者指名もしくは取得済み株を襲名
				//中継ぎ登板親方だったりしたら元に戻る処理もした方が良いのでは？
				for (ii=0;ii<106;ii++){
					if (tosiyoridata[ii].keishousha_rikisiid==i){
						if (tosiyoridata[ii].sishouflag==1){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が退職。\n後継者指名を受けていた%s部屋の%s(%d才)が年寄%sを襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が退職。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"後継者指名を受けていた%s部屋の%s(%d才)が年寄%sを襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						}else{
							if (tosiyoridata[ii].shozokuheyaid==-1){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								}else{
									if (tosiyoridata[ii].age>=60){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が退職\n%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が退職。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
									}else{
//ver3.11で借株人生を送れるようにしようとした部分
										char saikarikabuflag=0;
										for (iii=0;iii<106;iii++){//再レンタル取得、襲名
											if (tosiyoridata[iii].shozokuheyaid==-1 
											&& (tosiyoridata[iii].keishousha_rikisiid!=-1 || tosiyoridata[iii].keishousha_tosiyoriid!=-1) 
											&& tosiyoridata[iii].sishouflag==0){
//画面表示、イベントログ書込みと再レンタル処理のみ
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[iii]=1;
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が借りていた株を返却\n%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名\n元%sは年寄株%s(所有力士%s(%d才))をレンタルし再襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
tosiyoridata[ii].sikona,
tosiyoridata[iii].namestring,
namestring[tosiyoridata[iii].keishousha_rikisiid],
rikisidata[tosiyoridata[iii].keishousha_rikisiid].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が借りていた株を返却。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawFormatString(0,369+32,CRWHITE,"元%sは年寄株%s(所有力士%s(%d才))をレンタルし再襲名",
tosiyoridata[ii].sikona,
tosiyoridata[iii].namestring,
namestring[tosiyoridata[iii].keishousha_rikisiid],
rikisidata[tosiyoridata[iii].keishousha_rikisiid].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
												saikarikabuflag=1;
												tosiyoridata[iii].age=tosiyoridata[ii].age;
												tosiyoridata[iii].category=tosiyoridata[ii].category;
												tosiyoridata[iii].startyear=year;//+1必要かな？
												for (iiii=0;iiii<TOSIYORISUU;iiii++){
													if (tosiyoridata[iiii].shozokuheyaid==tosiyoridata[ii].shozokuheyaid){
														tosiyoridata[iii].shozokuitimonid=tosiyoridata[iiii].shozokuitimonid;
														break;
													}
												}
												tosiyoridata[iii].shozokuheyaid=tosiyoridata[ii].shozokuheyaid;
												strcpy(tosiyoridata[iii].sikona,tosiyoridata[ii].sikona);
												tosiyoridata[iii].jinbou=tosiyoridata[ii].jinbou;
												tosiyoridata[iii].rikisiid=tosiyoridata[ii].rikisiid;
												tosiyoridata[iii].sishouflag=0;
												tosiyoridata[iii].rijiflag=0;
												//tosiyoridata[iii].keishousha_rikisiidは留保ついたままでいいので
												//tosiyoridata[iii].keishousha_tosiyoriidは留保ついたままでいいので
												break;
											}
										}
										if (saikarikabuflag!=1){
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が借りていた株を返却するため廃業\n%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が借りていた株を返却するため廃業。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"%s部屋の%s(%d才)がすでに取得していた年寄%sを襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
										}
									}
								}
							}
						shutoku_tosiyoriid=ii;
						shuumei_tosiyoriid=ii;
						tosiyoridata[ii].age=rikisidata[i].age;
						tosiyoridata[ii].category=2;//Bカテの2
						tosiyoridata[ii].startyear=year;//+1必要かな？
						for (iii=0;iii<TOSIYORISUU;iii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}
							if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
								tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
								break;
							}
						}
						tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
						//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
						strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
						tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
						//tosiyoridata[ii].sishouflagはいじらない
						tosiyoridata[ii].jinbou=jinbou_rikisi[i];
						tosiyoridata[ii].rijiflag=0;
						tosiyoridata[ii].keishousha_rikisiid=-1;
						tosiyoridata[ii].keishousha_tosiyoriid=-1;
						break;
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				//空名跡取得襲名
				/*if (shutoku_tosiyoriid==-1){//
					char rikisi_itimonid=0;
					for (ii=0;ii<TOSIYORISUU;ii++){
						if (rikisidata[i].heyaid==tosiyoridata[ii].shozokuheyaid){
							rikisi_itimonid=tosiyoridata[ii].shozokuitimonid;
							break;
						}
					}
					for (ii=0;ii<106;ii++){
						if (tosiyoridata[ii].shozokuheyaid==-1 
						&& tosiyoridata[ii].shozokuitimonid==rikisi_itimonid
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才)が年寄株%sを取得、襲名(一門優先処理)\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が年寄株%sを取得、襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							shutoku_tosiyoriid=ii;
							shuumei_tosiyoriid=ii;
							tosiyoridata[ii].age=rikisidata[i].age;
							tosiyoridata[ii].category=2;//Bカテの2
							tosiyoridata[ii].startyear=year;//+1必要かな？
							for (iii=0;iii<TOSIYORISUU;iii++){
								if( ProcessMessage() == -1 ){mode=1;return ;}
								if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
									tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
									break;
								}
							}
							tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
							//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
							strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
							tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
							tosiyoridata[ii].sishouflag=0;
							tosiyoridata[ii].jinbou=jinbou_rikisi[i];
							tosiyoridata[ii].rijiflag=0;
							tosiyoridata[ii].keishousha_rikisiid=-1;
							tosiyoridata[ii].keishousha_tosiyoriid=-1;
							break;
						}
						if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					}
				}*/

				//ここに老化開始年齢が高めに設定されていることが原因で
				//要件をクリアしているにもかかわらず継承者指名・譲渡処理を受けられなかった力士を救済する処理
				//ただし、親方が継承者指名処理・譲渡処理を始める年齢（60才）以上の場合に限る
				if (shutoku_tosiyoriid==-1){
					for (ii=0;ii<106;ii++){//まだ継承者指名してない親方か確認
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid 
						//&& tosiyoridata[ii].sishouflag==1 
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
							if(tosiyoridata[ii].age >= 60){
								if (tosiyoridata[ii].sishouflag==1){
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が退職。\n後継者指名を受けた%s部屋の%s(%d才)が%s部屋を継承、襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が退職。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"後継者指名を受けた%s部屋の%s(%d才)が%s部屋を継承、襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								}else{
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が退職。\n年寄株を譲渡された%s部屋の%s(%d才)が%sを襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が退職。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"年寄株を譲渡された%s部屋の%s(%d才)が%s襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////

								}
								shutoku_tosiyoriid=ii;
								shuumei_tosiyoriid=ii;
								tosiyoridata[ii].age=rikisidata[i].age;
								tosiyoridata[ii].category=2;//Ｂカテの2
								tosiyoridata[ii].startyear=year;//+1必要かな？
								for (iii=0;iii<TOSIYORISUU;iii++){
									//if( ProcessMessage() == -1 ){mode=1;return ;}
									if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
										tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
										break;
									}
								}
								tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
								//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
								strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
								tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
								//tosiyoridata[ii].sishouflagはいじらない
								tosiyoridata[ii].jinbou=jinbou_rikisi[i];
								tosiyoridata[ii].rijiflag=0;
								tosiyoridata[ii].keishousha_rikisiid=-1;
								tosiyoridata[ii].keishousha_tosiyoriid=-1;
								break;
							}
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
					}
				}

				if(itidai_tosiyoriid==-1 
				&& shutoku_tosiyoriid==-1 
				&& shuumei_tosiyoriid==-1
				){//ここまでで年寄襲名できていない場合、レンタルを模索する(keishousha_に留保あるやつ)
					for (ii=0;ii<106;ii++){
						if (tosiyoridata[ii].shozokuheyaid==-1 &&
						( tosiyoridata[ii].keishousha_rikisiid!=-1 //留保してていいので
						|| tosiyoridata[ii].keishousha_tosiyoriid!=-1) //留保してていいので
						&& tosiyoridata[ii].sishouflag==0
						){
							if (tosiyoridata[ii].keishousha_rikisiid!=-1){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才)が年寄株%s(所有者現役力士%s(%d才))をレンタルし襲名\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
namestring[tosiyoridata[ii].keishousha_rikisiid],
rikisidata[tosiyoridata[ii].keishousha_rikisiid].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が年寄株%s(所有者現役力士%s(%d才))をレンタルし襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
namestring[tosiyoridata[ii].keishousha_rikisiid],
rikisidata[tosiyoridata[ii].keishousha_rikisiid].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							}else{

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋の%s(%d才)が年寄株%s(所有者年寄%s(%d才))をレンタルし襲名\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
tosiyoridata[tosiyoridata[ii].keishousha_tosiyoriid].namestring,
tosiyoridata[tosiyoridata[ii].keishousha_tosiyoriid].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"%s部屋の%s(%d才)が年寄株%s(所有者年寄%s(%d才))をレンタルし襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring,
tosiyoridata[tosiyoridata[ii].keishousha_tosiyoriid].namestring,
tosiyoridata[tosiyoridata[ii].keishousha_tosiyoriid].age);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
							}
							shutoku_tosiyoriid=ii;
							shuumei_tosiyoriid=ii;
							tosiyoridata[ii].age=rikisidata[i].age;
							tosiyoridata[ii].category=2;//Bカテの2
							tosiyoridata[ii].startyear=year;//+1必要かな？
							for (iii=0;iii<TOSIYORISUU;iii++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}
								if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
									tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
									break;
								}
							}
							tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
							//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
							strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
							tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
							tosiyoridata[ii].sishouflag=0;
							tosiyoridata[ii].jinbou=jinbou_rikisi[i];
							tosiyoridata[ii].rijiflag=0;
							//tosiyoridata[ii].keishousha_rikisiidは留保ついたままでいいので
							//tosiyoridata[ii].keishousha_tosiyoriidは留保ついたままでいいので
							break;
						}
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					}
				}
			//Cカテ
			}else if (makuutiijouzaiisuu[i]>=C_makuutizaiisuu || juuryouijouzaiisuu[i]>=C_jyuuryouzaiisuu){
				//後継者指名株を襲名
				//中継ぎ登板親方だったりしたら元に戻る処理もした方が良いのでは？
				for (ii=0;ii<106;ii++){
					if (tosiyoridata[ii].keishousha_rikisiid==i){

//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が退職。\n後継者指名を受けていた%s部屋の%s(%d才)が年寄%sを襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が退職。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"後継者指名を受けていた%s部屋の%s(%d才)が年寄%sを襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
						shutoku_tosiyoriid=ii;
						shuumei_tosiyoriid=ii;
						tosiyoridata[ii].age=rikisidata[i].age;
						tosiyoridata[ii].category=3;//Cカテの3
						tosiyoridata[ii].startyear=year;//+1必要かな？
						for (iii=0;iii<TOSIYORISUU;iii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}
							if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
								tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
								break;
							}
						}
						tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
						//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
						strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
						tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
						//tosiyoridata[ii].sishouflagはいじらない、Cカテは師匠からしか後継者指名でなれないから1のはず
						tosiyoridata[ii].jinbou=jinbou_rikisi[i];
						tosiyoridata[ii].rijiflag=0;
						tosiyoridata[ii].keishousha_rikisiid=-1;
						tosiyoridata[ii].keishousha_tosiyoriid=-1;
						break;
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}

				//ここに老化開始年齢が高めに設定されていることが原因で
				//要件をクリアしているにもかかわらず継承者指名・譲渡処理を受けられなかった力士を救済する処理
				//ただし、親方が継承者指名処理・譲渡処理を始める年齢（60才）以上の場合に限る
				if (shutoku_tosiyoriid==-1){
					for (ii=0;ii<106;ii++){//まだ継承者指名してない親方か確認
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (tosiyoridata[ii].shozokuheyaid==rikisidata[i].heyaid 
						&& tosiyoridata[ii].sishouflag==1 
						&& tosiyoridata[ii].keishousha_rikisiid==-1 
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1){
							if(tosiyoridata[ii].age >= 60){
//記録必要フラグ書込み/////////////
kirokuhituyouflag_tosiyoriid[ii]=1;
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"元%sの%s親方(%d才)が退職。\n後継者指名を受けた%s部屋の%s(%d才)が%s部屋を継承、襲名\n",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age,
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawFormatString(0,369,CRWHITE,"元%sの%s親方(%d才)が退職。",
tosiyoridata[ii].sikona,
tosiyoridata[ii].namestring,
tosiyoridata[ii].age);
DrawFormatString(0,369+16,CRWHITE,"後継者指名を受けた%s部屋の%s(%d才)が%s部屋を継承、襲名",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age,
tosiyoridata[ii].namestring);
DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
}
//////////////////////////////////////////////////////////////
								shutoku_tosiyoriid=ii;
								shuumei_tosiyoriid=ii;
								tosiyoridata[ii].age=rikisidata[i].age;
								tosiyoridata[ii].category=3;//Ｃカテの3
								tosiyoridata[ii].startyear=year;//+1必要かな？
								for (iii=0;iii<TOSIYORISUU;iii++){
									//if( ProcessMessage() == -1 ){mode=1;return ;}
									if (tosiyoridata[iii].shozokuheyaid==rikisidata[i].heyaid){
										tosiyoridata[ii].shozokuitimonid=tosiyoridata[iii].shozokuitimonid;
										break;
									}
								}
								tosiyoridata[ii].shozokuheyaid=rikisidata[i].heyaid;
								//strcpy(tosiyoridata[ii].namestring,namestring[rikisidata[i].nameid]);
								strcpy(tosiyoridata[ii].sikona,namestring[rikisidata[i].nameid]);
								tosiyoridata[ii].rikisiid=rikisidata[i].rikisiid;
								//tosiyoridata[ii].sishouflagはいじらない
								tosiyoridata[ii].jinbou=jinbou_rikisi[i];
								tosiyoridata[ii].rijiflag=0;
								tosiyoridata[ii].keishousha_rikisiid=-1;
								tosiyoridata[ii].keishousha_tosiyoriid=-1;
								break;
							}
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
					}
				}

			}


			

	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
				//引退のお知らせ表示
	if (rikisidata[i].torikumimiruflag==1 || rikisidata[i].heyaid==myheyaid || rikisidata[i].jikosaiko_bandukenameid<5 || juuryouijouzaiisuu[i]>=20){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				game_main_backscreen();//基本ゲーム画面表示ルーチン

			DrawFormatString(187,24,CRWHITE,"%s",
			namestring[i]);
			DrawFormatString(187,40,CRWHITE,"%s出身 %s部屋",
			hometownstring[rikisidata[i].hometownid],
			heyastring[rikisidata[i].heyaid]);
			DrawFormatString(187,56,CRWHITE,"%4d年%d月初土俵  %4d年%d月引退",
			rikisidata[i].hatudohyo_year,
			rikisidata[i].hatudohyo_month,
			year,
			month);
			DrawFormatString(187,72,CRWHITE,"引退年齢%d才",
			rikisidata[i].age);
			DrawString(187,88,"自己最高位",CRWHITE);
			if (rikisidata[i].jikosaiko_bandukesuuji>1 ){
				DrawFormatString(187+112,88,CRWHITE,"%s%d枚目",
				bandukenamestring[rikisidata[i].jikosaiko_bandukenameid],
				rikisidata[i].jikosaiko_bandukesuuji
				);
			}else if (rikisidata[i].jikosaiko_bandukesuuji==1 ){
				DrawFormatString(187+112,88,CRWHITE,"%s筆頭",
				bandukenamestring[rikisidata[i].jikosaiko_bandukenameid]
				);
			}else{
				DrawFormatString(187+112,88,CRWHITE,"%s",
				bandukenamestring[rikisidata[i].jikosaiko_bandukenameid]
				);
			}
			DrawFormatString(187,104,CRWHITE,"通算 %d勝%d敗",
			rikisidata[i].wintotal,
			rikisidata[i].losttotal);
			DrawFormatString(187,120,CRWHITE,"幕内通算 %d勝%d敗",
			rikisidata[i].makuuti_win,
			rikisidata[i].makuuti_lost);
			DrawFormatString(187,136,CRWHITE,"幕内最高優勝 %d回",
			rikisidata[i].kiroku_yuushoukaisuu);
			DrawFormatString(187,152,CRWHITE,"金星数 %d個",
			rikisidata[i].kinbosisuu);
			DrawFormatString(187,168,CRWHITE,"殊勲賞受賞 %d回",
			rikisidata[i].shukunshousuu);
			DrawFormatString(187,184,CRWHITE,"敢闘賞受賞 %d回",
			rikisidata[i].kantoushousuu);
			DrawFormatString(187,200,CRWHITE,"技能賞受賞 %d回",
			rikisidata[i].ginoushousuu);
			DrawFormatString(187,216,CRWHITE,"最多連勝 %d連勝",
			rikisidata[i].kiroku_renshou);
			DrawFormatString(187,232,CRWHITE,"最多連敗 %d連敗",
			rikisidata[i].kiroku_renpai);
			DrawString(187,248,"ガチンコ杯最高",CRWHITE);
			if (rikisidata[i].jikosaiko_tournament==0){
				DrawString(187+128,248,"未出場",CRWHITE);
			}else if (rikisidata[i].jikosaiko_tournament<=6){
				DrawFormatString(187+128,248,CRWHITE,"%6d回戦進出",rikisidata[i].jikosaiko_tournament);
			}else if(rikisidata[i].jikosaiko_tournament==7){
				DrawString(187+128,248,"準々決勝進出",CRWHITE);
			}else if(rikisidata[i].jikosaiko_tournament==8){
				DrawString(187+128,248,"準決勝進出",CRWHITE);
			}else if(rikisidata[i].jikosaiko_tournament==9){
				DrawString(187+128,248,"決勝進出",CRWHITE);
			}else{
				DrawFormatString(187+128,248,CRWHITE,"優勝%6d回",rikisidata[i].yuushoukaisuu_tournament);
			}
			DrawFormatString(187,264,CRWHITE,"三役以上 %d場所",
			sanyakuijouzaiisuu[i]);
			DrawFormatString(187,280,CRWHITE,"幕内以上 %d場所",
			makuutiijouzaiisuu[i]);
			DrawFormatString(187,296,CRWHITE,"十両以上 %d場所",
			juuryouijouzaiisuu[i]);

		shukushou_tate_gazou=(int)(220-rikisidata[i].sinchou)*2/3;
		shukushou_yoko_gazou=(int)((250-rikisidata[i].taijuu)/2);
		if (shukushou_tate_gazou<0){shukushou_tate_gazou=0;}
		if (shukushou_yoko_gazou<0){shukushou_yoko_gazou=0;}
		x1_gazou=387-32;
		y1_gazou=239+shukushou_tate_gazou;
		x2_gazou=x1_gazou+128-shukushou_yoko_gazou;
		y2_gazou=y1_gazou;
		x3_gazou=x2_gazou;
		y3_gazou=y1_gazou+128-shukushou_tate_gazou;
		x4_gazou=x1_gazou;
		y4_gazou=y3_gazou;
		sprintf(filename,"rikisigraph/rikisi%d.png\0",i);
		rikisi_front_temp = LoadGraph( filename ) ;
		DrawModiGraph(x1_gazou+yokozure,y1_gazou ,	x2_gazou+yokozure,y2_gazou , x3_gazou+yokozure,y3_gazou , x4_gazou+yokozure,y4_gazou , rikisi_front_temp , TRUE ) ;

				DrawFormatString(187,369,CRWHITE,"%s部屋の%sが",heyastring[rikisidata[i].heyaid],namestring[rikisidata[i].nameid]);
				DrawString(187,369+16,"引退を表明しました。",CRWHITE);
				DrawString(187,369+80,"Hit any key",CRWHITE);
		if (rikisidata[i].heyaid==myheyaid){
					draw_buttonF_mouse();
					ScreenFlip();
					WaitKey();
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					game_main_backscreen();//基本ゲーム画面表示ルーチン
			DrawFormatString(187,24,CRWHITE,"%s",
			namestring[i]);
			DrawFormatString(187,40,CRWHITE,"%s出身 %s部屋",
			hometownstring[rikisidata[i].hometownid],
			heyastring[rikisidata[i].heyaid]);
			DrawFormatString(187,56,CRWHITE,"%4d年%d月初土俵  %4d年%d月引退",
			rikisidata[i].hatudohyo_year,
			rikisidata[i].hatudohyo_month,
			year,
			month);
			DrawFormatString(187,72,CRWHITE,"引退年齢%d才",
			rikisidata[i].age);
			DrawString(187,88,"自己最高位",CRWHITE);
			if (rikisidata[i].jikosaiko_bandukesuuji>1 ){
				DrawFormatString(187+112,88,CRWHITE,"%s%d枚目",
				bandukenamestring[rikisidata[i].jikosaiko_bandukenameid],
				rikisidata[i].jikosaiko_bandukesuuji
				);
			}else if (rikisidata[i].jikosaiko_bandukesuuji==1 ){
				DrawFormatString(187+112,88,CRWHITE,"%s筆頭",
				bandukenamestring[rikisidata[i].jikosaiko_bandukenameid]
				);
			}else{
				DrawFormatString(187+112,88,CRWHITE,"%s",
				bandukenamestring[rikisidata[i].jikosaiko_bandukenameid]
				);
			}
			DrawFormatString(187,104,CRWHITE,"通算 %d勝%d敗",
			rikisidata[i].wintotal,
			rikisidata[i].losttotal);
			DrawFormatString(187,120,CRWHITE,"幕内通算 %d勝%d敗",
			rikisidata[i].makuuti_win,
			rikisidata[i].makuuti_lost);
			DrawFormatString(187,136,CRWHITE,"幕内最高優勝 %d回",
			rikisidata[i].kiroku_yuushoukaisuu);
			DrawFormatString(187,152,CRWHITE,"金星数 %d個",
			rikisidata[i].kinbosisuu);
			DrawFormatString(187,168,CRWHITE,"殊勲賞受賞 %d回",
			rikisidata[i].shukunshousuu);
			DrawFormatString(187,184,CRWHITE,"敢闘賞受賞 %d回",
			rikisidata[i].kantoushousuu);
			DrawFormatString(187,200,CRWHITE,"技能賞受賞 %d回",
			rikisidata[i].ginoushousuu);
			DrawFormatString(187,216,CRWHITE,"最多連勝 %d連勝",
			rikisidata[i].kiroku_renshou);
			DrawFormatString(187,232,CRWHITE,"最多連敗 %d連敗",
			rikisidata[i].kiroku_renpai);
			DrawString(187,248,"ガチンコ杯最高",CRWHITE);
			if (rikisidata[i].jikosaiko_tournament==0){
				DrawString(187+128,248,"未出場",CRWHITE);
			}else if (rikisidata[i].jikosaiko_tournament<=6){
				DrawFormatString(187+128,248,CRWHITE,"%6d回戦進出",rikisidata[i].jikosaiko_tournament);
			}else if(rikisidata[i].jikosaiko_tournament==7){
				DrawString(187+128,248,"準々決勝進出",CRWHITE);
			}else if(rikisidata[i].jikosaiko_tournament==8){
				DrawString(187+128,248,"準決勝進出",CRWHITE);
			}else if(rikisidata[i].jikosaiko_tournament==9){
				DrawString(187+128,248,"決勝進出",CRWHITE);
			}else{
				DrawFormatString(187+128,248,CRWHITE,"優勝%6d回",rikisidata[i].yuushoukaisuu_tournament);
			}
			DrawFormatString(187,264,CRWHITE,"三役以上 %d場所",
			sanyakuijouzaiisuu[i]);
			DrawFormatString(187,280,CRWHITE,"幕内以上 %d場所",
			makuutiijouzaiisuu[i]);
			DrawFormatString(187,296,CRWHITE,"十両以上 %d場所",
			juuryouijouzaiisuu[i]);
			DrawModiGraph(x1_gazou+yokozure,y1_gazou ,	x2_gazou+yokozure,y2_gazou , x3_gazou+yokozure,y3_gazou , x4_gazou+yokozure,y4_gazou , rikisi_front_temp , TRUE ) ;
					DrawFormatString(187,369,CRWHITE,"%sもついに引退するそうです。",namestring[rikisidata[i].nameid]);
					DrawFormatString(187,369+16,CRWHITE,"%sの新たな人生の始まりを祝福しましょう。",namestring[rikisidata[i].nameid]);
					DrawString(187,369+80,"Hit any key",CRWHITE);
		}

		if (itidai_tosiyoriid!=-1 || shutoku_tosiyoriid!=-1 || shuumei_tosiyoriid!=-1){//3.00一代年寄
			draw_buttonF_mouse();
			ScreenFlip();
			WaitKey();
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			game_main_backscreen();//基本ゲーム画面表示ルーチン
			DrawFormatString(187,24,CRWHITE,"%s",
			namestring[i]);
			DrawFormatString(187,40,CRWHITE,"%s出身 %s部屋",
			hometownstring[rikisidata[i].hometownid],
			heyastring[rikisidata[i].heyaid]);
			DrawFormatString(187,56,CRWHITE,"%4d年%d月初土俵  %4d年%d月引退",
			rikisidata[i].hatudohyo_year,
			rikisidata[i].hatudohyo_month,
			year,
			month);
			DrawFormatString(187,72,CRWHITE,"引退年齢%d才",
			rikisidata[i].age);
			DrawString(187,88,"自己最高位",CRWHITE);
			if (rikisidata[i].jikosaiko_bandukesuuji>1 ){
				DrawFormatString(187+112,88,CRWHITE,"%s%d枚目",
				bandukenamestring[rikisidata[i].jikosaiko_bandukenameid],
				rikisidata[i].jikosaiko_bandukesuuji
				);
			}else if (rikisidata[i].jikosaiko_bandukesuuji==1 ){
				DrawFormatString(187+112,88,CRWHITE,"%s筆頭",
				bandukenamestring[rikisidata[i].jikosaiko_bandukenameid]
				);
			}else{
				DrawFormatString(187+112,88,CRWHITE,"%s",
				bandukenamestring[rikisidata[i].jikosaiko_bandukenameid]
				);
			}
			DrawFormatString(187,104,CRWHITE,"通算 %d勝%d敗",
			rikisidata[i].wintotal,
			rikisidata[i].losttotal);
			DrawFormatString(187,120,CRWHITE,"幕内通算 %d勝%d敗",
			rikisidata[i].makuuti_win,
			rikisidata[i].makuuti_lost);
			DrawFormatString(187,136,CRWHITE,"幕内最高優勝 %d回",
			rikisidata[i].kiroku_yuushoukaisuu);
			DrawFormatString(187,152,CRWHITE,"金星数 %d個",
			rikisidata[i].kinbosisuu);
			DrawFormatString(187,168,CRWHITE,"殊勲賞受賞 %d回",
			rikisidata[i].shukunshousuu);
			DrawFormatString(187,184,CRWHITE,"敢闘賞受賞 %d回",
			rikisidata[i].kantoushousuu);
			DrawFormatString(187,200,CRWHITE,"技能賞受賞 %d回",
			rikisidata[i].ginoushousuu);
			DrawFormatString(187,216,CRWHITE,"最多連勝 %d連勝",
			rikisidata[i].kiroku_renshou);
			DrawFormatString(187,232,CRWHITE,"最多連敗 %d連敗",
			rikisidata[i].kiroku_renpai);
			DrawString(187,248,"ガチンコ杯最高",CRWHITE);
			if (rikisidata[i].jikosaiko_tournament==0){
				DrawString(187+128,248,"未出場",CRWHITE);
			}else if (rikisidata[i].jikosaiko_tournament<=6){
				DrawFormatString(187+128,248,CRWHITE,"%6d回戦進出",rikisidata[i].jikosaiko_tournament);
			}else if(rikisidata[i].jikosaiko_tournament==7){
				DrawString(187+128,248,"準々決勝進出",CRWHITE);
			}else if(rikisidata[i].jikosaiko_tournament==8){
				DrawString(187+128,248,"準決勝進出",CRWHITE);
			}else if(rikisidata[i].jikosaiko_tournament==9){
				DrawString(187+128,248,"決勝進出",CRWHITE);
			}else{
				DrawFormatString(187+128,248,CRWHITE,"優勝%6d回",rikisidata[i].yuushoukaisuu_tournament);
			}
			DrawFormatString(187,264,CRWHITE,"三役以上 %d場所",
			sanyakuijouzaiisuu[i]);
			DrawFormatString(187,280,CRWHITE,"幕内以上 %d場所",
			makuutiijouzaiisuu[i]);
			DrawFormatString(187,296,CRWHITE,"十両以上 %d場所",
			juuryouijouzaiisuu[i]);
			DrawModiGraph(x1_gazou+yokozure,y1_gazou ,	x2_gazou+yokozure,y2_gazou , x3_gazou+yokozure,y3_gazou , x4_gazou+yokozure,y4_gazou , rikisi_front_temp , TRUE ) ;
			if (itidai_tosiyoriid!=-1){
				DrawFormatString(187,369,CRWHITE,"%sは一代年寄%sを襲名しました。",namestring[rikisidata[i].nameid],tosiyoridata[itidai_tosiyoriid].namestring);
			}
			if (shuumei_tosiyoriid!=-1){
				DrawFormatString(187,369,CRWHITE,"%sは年寄%sを襲名しました。",namestring[rikisidata[i].nameid],tosiyoridata[shuumei_tosiyoriid].namestring);
			}
			if (itidai_tosiyoriid!=-1 && shutoku_tosiyoriid!=-1){
				DrawFormatString(187,369+16,CRWHITE,"%sは同時に年寄株%sを取得しました。",namestring[rikisidata[i].nameid],tosiyoridata[shutoku_tosiyoriid].namestring);
			}
			DrawString(187,369+80,"Hit any key",CRWHITE);
		}

				draw_buttonF_mouse();
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
	}
	}//////////////////////////////////////////////////////////////

				//ここから新弟子のデータ作成
				//力士通算ID代入
				jinbou_rikisi[i]=0;
				rikisidata[i].rikisiid=rikisiid_used;
				rikisiid_used++;
//四股名ルーチン2.50
if (sikonamode==0){
				//乱数で四股名と出身地と所属部屋を決定
				while(1){
					if (hoketuflag==1){
						ii=rikisidata[i].heyaid;
					}else{
						ii=GetRand(HEYASUU-2)+1;
//						ii=GetRand(HEYASUU-3)+2;//0人テスト
					}
					r=heyabetu_sichousonid[ii-1]+GetRand(heyabetu_sichousonid[ii]-heyabetu_sichousonid[ii-1]-1);
					if (shozokurikisisuu[ii]<20 && hometownstring_used[r]==0){
						owariflag=1;
					}else{
						if (shozokurikisisuu[ii]<20){
							while(1){
								if (r==heyabetu_sichousonid[ii-1]+(heyabetu_sichousonid[ii]-heyabetu_sichousonid[ii-1]-1)){
									r=heyabetu_sichousonid[ii-1];
								}else{
									r++;
								}
								if (hometownstring_used[r]==0){
									owariflag=1;
									break;
								}
							}
						}else{
							owariflag=0;
						}
					}
					if (owariflag==1){
						rikisidata[i].heyaid=ii;
						rikisidata[i].hometownid=r;
						temp_nameid[i]=r*SIKONA_ATO+GetRand(SIKONA_ATO-1);
						rikisidata[i].nameid=i;
						shozokurikisisuu[ii]++;
						hometownstring_used[r]++;
						break;
					}
					// メッセージ処理
					//if( ProcessMessage() == -1 )
					//{
					//	 mode=1;
					//	 return ;	// エラーが発生したらループを抜ける
					//}
				}
}else if(sikonamode==1){//四股名b紐付け解除しただけバージョン
				while(1){
					if (hoketuflag==1){
						ii=rikisidata[i].heyaid;
					}else{
						ii=GetRand(HEYASUU-2)+1;
					}
					//r=heyabetu_sichousonid[ii-1]+GetRand(heyabetu_sichousonid[ii]-heyabetu_sichousonid[ii-1]-1);
					r=GetRand(SICHOUSONSUU-1);
					//if (shozokurikisisuu[ii]<20 && hometownstring_used[r]==0){
					if (shozokurikisisuu[ii]<20){
						owariflag=1;
//					}else{
//						if (shozokurikisisuu[ii]<20){
//							while(1){
//								if (r==heyabetu_sichousonid[ii-1]+(heyabetu_sichousonid[ii]-heyabetu_sichousonid[ii-1]-1)){
//									r=heyabetu_sichousonid[ii-1];
//								}else{
//									r++;
//								}
//								if (hometownstring_used[r]==0){
//									owariflag=1;
//									break;
//								}
//							}
//						}else{
//							owariflag=0;
//						}
					}
					if (owariflag==1){
						rikisidata[i].heyaid=ii;
						rikisidata[i].hometownid=r;
						//temp_nameid[i]=r*SIKONA_ATO+GetRand(SIKONA_ATO-1);
						temp_nameid[i]=GetRand(SICHOUSONSUU-1)*SIKONA_ATO+GetRand(SIKONA_ATO-1);
						rikisidata[i].nameid=i;
						shozokurikisisuu[ii]++;
						hometownstring_used[r]++;
						break;
					}
					// メッセージ処理
					//if( ProcessMessage() == -1 )
					//{
					//	 mode=1;
					//	 return ;	// エラーが発生したらループを抜ける
					//}
				}
}else{//四股名c この部分はbと一緒で後の最終確定で変更させる
				//空き部屋確認
				for (ii=0;ii<HEYASUU;ii++){
					if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					tosiyoriiruflag[ii]=0;
					for (iii=0;iii<TOSIYORISUU;iii++){
						if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (tosiyoridata[iii].shozokuheyaid==ii){
							tosiyoriiruflag[ii]=1;
							break;
						}
					}
				}
				owariflag=0;
				while(1){
					if (hoketuflag==1){
						ii=rikisidata[i].heyaid;
					}else{
						while(1){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							ii=GetRand(HEYASUU-2)+1;
							if(tosiyoriiruflag[ii]==1){break;}//親方いない部屋ならループさせ続ける
						}
					}
					r=GetRand(SICHOUSONSUU-1);
					if (shozokurikisisuu[ii]<20){
						owariflag=1;
					}
					if (owariflag==1){
						rikisidata[i].heyaid=ii;
						rikisidata[i].hometownid=r;
						rikisidata[i].nameid=i;
						shozokurikisisuu[ii]++;
						break;
					}
					// メッセージ処理
					//if( ProcessMessage() == -1 )
					//{
					//	 mode=1;
					//	 return ;	// エラーが発生したらループを抜ける
					//}
				}


}

if (hoketuflag==2){//
	shozokurikisisuu[rikisidata[i].heyaid]--;
	rikisidata[i].heyaid=myheyaid;
	shozokurikisisuu[myheyaid]++;
	//最後の弟子に引退されて代わりに来る弟子は育成ブーストしない
	ikuseiboost[i]=1;
	ikuseibunbo[i]=1;
}
				//力士IDごとの短縮表示用出身地作成
				strncpy(tanshuku_hometown[i],hometownstring[rikisidata[i].hometownid],6);
				tanshuku_hometown[i][6]='\0';
				if (rinnemode==0 || rikisidata[i].rinneflag==0){//輪廻力士の四股名も他の力士と同じ方法で決定する場合
									//なお、rinnemodeが1だと輪廻力士の四股名は不変
					//四股名最終確定
					if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					sprintf(temp_filename,"data/heyabetu/sikonakakuritu%d.csv\0",rikisidata[i].heyaid);
					fpcsv = fopen(temp_filename,"r");
					if( fpcsv == NULL ){
						fclose(fpcsv);
						fpcsv = fopen(temp_filename,"w");
										fprintf(fpcsv,"部屋別文字+mid\n");
										fprintf(fpcsv,"10\n");
										fprintf(fpcsv,"部屋別文字+ato\n");
										fprintf(fpcsv,"10\n");
										fprintf(fpcsv,"部屋別文字+mid+ato\n");
										fprintf(fpcsv,"10\n");
										fprintf(fpcsv,"mae+部屋別文字\n");
										fprintf(fpcsv,"0\n");
										fprintf(fpcsv,"mid+部屋別文字\n");
										fprintf(fpcsv,"0\n");
										fprintf(fpcsv,"mae+mid+部屋別文字\n");
										fprintf(fpcsv,"0\n");
										fprintf(fpcsv,"mae+mid\n");
										fprintf(fpcsv,"20\n");
										fprintf(fpcsv,"mae+ato\n");
										fprintf(fpcsv,"20\n");
										fprintf(fpcsv,"mae+mid+ato\n");
										fprintf(fpcsv,"10\n");
										fprintf(fpcsv,"mid+ato\n");
										fprintf(fpcsv,"20\n");
										fprintf(fpcsv,"の\n");
										fprintf(fpcsv,"0\n");
										fprintf(fpcsv,"ノ\n");
										fprintf(fpcsv,"45\n");
										fprintf(fpcsv,"乃\n");
										fprintf(fpcsv,"0\n");
						
						fclose(fpcsv);
						if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						fpcsv = fopen(temp_filename,"r");
					}
					kazu=0;
					ch=0;ch=1;
					while(1) 
					{
						for (ii=0;ii<301;ii++){
							temp_string_kakuritu[ii]=0;
						}
						if (ch == EOF){break;}
						for (ii=0;ii<30;ii++){
							ch = fgetc(fpcsv);
							if (ch == EOF){break;}
							if(ch == '\n'){
								break;
							}else{
								if(ch=='0'){
									strcat(temp_string_kakuritu,"0");
								}else if(ch=='1'){
									strcat(temp_string_kakuritu,"1");
								}else if(ch=='2'){
									strcat(temp_string_kakuritu,"2");
								}else if(ch=='3'){
									strcat(temp_string_kakuritu,"3");
								}else if(ch=='4'){
									strcat(temp_string_kakuritu,"4");
								}else if(ch=='5'){
									strcat(temp_string_kakuritu,"5");
								}else if(ch=='6'){
									strcat(temp_string_kakuritu,"6");
								}else if(ch=='7'){
									strcat(temp_string_kakuritu,"7");
								}else if(ch=='8'){
									strcat(temp_string_kakuritu,"8");
								}else if(ch=='9'){
									strcat(temp_string_kakuritu,"9");
								}
							}
						}
						if (kazu==1){
							kakuritu_heya_mid=atoi(temp_string_kakuritu);
						}else if(kazu==3){
							kakuritu_heya_ato=atoi(temp_string_kakuritu);
						}else if(kazu==5){
							kakuritu_heya_mid_ato=atoi(temp_string_kakuritu);
						}else if(kazu==7){
							kakuritu_mae_heya=atoi(temp_string_kakuritu);
						}else if(kazu==9){
							kakuritu_mid_heya=atoi(temp_string_kakuritu);
						}else if(kazu==11){
							kakuritu_mae_mid_heya=atoi(temp_string_kakuritu);
						}else if(kazu==13){
							kakuritu_mae_mid=atoi(temp_string_kakuritu);
						}else if(kazu==15){
							kakuritu_mae_ato=atoi(temp_string_kakuritu);
						}else if(kazu==17){
							kakuritu_mae_mid_ato=atoi(temp_string_kakuritu);
						}else if(kazu==19){
							kakuritu_mid_ato=atoi(temp_string_kakuritu);
						}else if(kazu==21){
							kakuritu_hiragana_no=atoi(temp_string_kakuritu);
						}else if(kazu==23){
							kakuritu_katakana_no=atoi(temp_string_kakuritu);
						}else if(kazu==25){
							kakuritu_kanji_no=atoi(temp_string_kakuritu);
						}
						kazu++;
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					}
					fclose(fpcsv);
					if( ProcessMessage() == -1 ){mode=1;return ;}
					//for (i=0;i<RIKISISUU;i++){
					if (sikonamode==2){//四股名c
						choufukukaisuu=0;
						while(1){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							ransuu_mae=GetRand(SICHOUSONSUU-1);
							ransuu_ato=GetRand(SICHOUSONSUU-1);
							ransuu_mid=GetRand(SICHOUSONSUU-1);
							ransuu_kakuritu=GetRand(99);
							ransuu_kakuritu_no=GetRand(99);
							if (ransuu_kakuritu<kakuritu_heya_mid){//前に部屋別冠文字+mid
								if (GetRand(1)==0){
									nagasa_namestring=strlen(temp_namestring_mid[ransuu_mid])+strlen(temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
									if (nagasa_namestring>10){
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strncat(namestring[i],temp_namestring_mid[ransuu_mid],4);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}else if(nagasa_namestring<9){//「の」「ノ」「乃」
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
										if (ransuu_kakuritu_no<kakuritu_hiragana_no){
											strcat(namestring[i],"の");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no){
											strcat(namestring[i],"ノ");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no+kakuritu_kanji_no){
											strcat(namestring[i],"乃");
										}
										strcat(namestring[i],temp_namestring_mid[ransuu_mid]);
										strcat(namestring_choufukucheck[i],temp_namestring_mid[ransuu_mid]);
									}else{
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strcat(namestring[i],temp_namestring_mid[ransuu_mid]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}
								}else{
									nagasa_namestring=strlen(temp_namestring_mid[ransuu_mid])+strlen(temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
									if (nagasa_namestring>10){
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strncat(namestring[i],temp_namestring_mid[ransuu_mid],4);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}else if(nagasa_namestring<9){//「の」「ノ」「乃」
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
										if (ransuu_kakuritu_no<kakuritu_hiragana_no){
											strcat(namestring[i],"の");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no){
											strcat(namestring[i],"ノ");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no+kakuritu_kanji_no){
											strcat(namestring[i],"乃");
										}
										strcat(namestring[i],temp_namestring_mid[ransuu_mid]);
										strcat(namestring_choufukucheck[i],temp_namestring_mid[ransuu_mid]);
									}else{
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strcat(namestring[i],temp_namestring_mid[ransuu_mid]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}
								}
							}else if (ransuu_kakuritu<kakuritu_heya_mid+kakuritu_heya_ato){//前に部屋別冠文字+ato
								if (GetRand(1)==0){
									nagasa_namestring=strlen(temp_namestring_ato[ransuu_ato])+strlen(temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
									if (nagasa_namestring>10){
										//strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										//strncat(namestring[i],temp_namestring_ato[temp_nameid[i]%SIKONA_ATO],(10-strlen(temp_namestring_ato[temp_nameid[i]%SIKONA_ATO]))-(nagasa_namestring-10));
									}else if(nagasa_namestring<9){//「の」「ノ」「乃」
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
										if (ransuu_kakuritu_no<kakuritu_hiragana_no){
											strcat(namestring[i],"の");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no){
											strcat(namestring[i],"ノ");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no+kakuritu_kanji_no){
											strcat(namestring[i],"乃");
										}
										strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
										strcat(namestring_choufukucheck[i],temp_namestring_ato[ransuu_ato]);
									}else{
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}
								}else{
									nagasa_namestring=strlen(temp_namestring_ato[ransuu_ato])+strlen(temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
									if (nagasa_namestring>10){
										//strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										//strncat(namestring[i],temp_namestring_ato[temp_nameid[i]%SIKONA_ATO],(10-strlen(temp_namestring_ato[temp_nameid[i]%SIKONA_ATO]))-(nagasa_namestring-10));
									}else if(nagasa_namestring<9){//「の」「ノ」「乃」
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
										if (ransuu_kakuritu_no<kakuritu_hiragana_no){
											strcat(namestring[i],"の");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no){
											strcat(namestring[i],"ノ");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no+kakuritu_kanji_no){
											strcat(namestring[i],"乃");
										}
										strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
										strcat(namestring_choufukucheck[i],temp_namestring_ato[ransuu_ato]);
									}else{
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}
								}
							}else if (ransuu_kakuritu<kakuritu_heya_mid+kakuritu_heya_ato+kakuritu_heya_mid_ato){//前に部屋別冠文字+mid+ato
								if (GetRand(1)==0){
									nagasa_namestring=strlen(temp_namestring_mid[ransuu_mid])+strlen(temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
									if (nagasa_namestring>6){
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strncat(namestring[i],temp_namestring_mid[ransuu_mid],2);
										strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}else{
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strcat(namestring[i],temp_namestring_mid[ransuu_mid]);
										strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}
								}else{
									nagasa_namestring=strlen(temp_namestring_mid[ransuu_mid])+strlen(temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
									if (nagasa_namestring>6){
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strncat(namestring[i],temp_namestring_mid[ransuu_mid],2);
										strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}else{
										strcpy(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strcat(namestring[i],temp_namestring_mid[ransuu_mid]);
										strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}
								}
							}else if (ransuu_kakuritu<kakuritu_heya_mid+kakuritu_heya_ato+kakuritu_heya_mid_ato+kakuritu_mae_heya){//mae+部屋別
								if (GetRand(1)==0){
									nagasa_namestring=strlen(temp_namestring_mae[ransuu_mae])+strlen(temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
									if (nagasa_namestring>10){
										strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
										strncat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0],4);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}else if(nagasa_namestring<9){//「の」「ノ」「乃」
										strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
										if (ransuu_kakuritu_no<kakuritu_hiragana_no){
											strcat(namestring[i],"の");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no){
											strcat(namestring[i],"ノ");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no+kakuritu_kanji_no){
											strcat(namestring[i],"乃");
										}
										strcat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strcat(namestring_choufukucheck[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
									}else{
										strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
										strcat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}
								}else{
									nagasa_namestring=strlen(temp_namestring_mae[ransuu_mae])+strlen(temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
									if (nagasa_namestring>10){
										strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
										strncat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1],4);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}else if(nagasa_namestring<9){//「の」「ノ」「乃」
										strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
										if (ransuu_kakuritu_no<kakuritu_hiragana_no){
											strcat(namestring[i],"の");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no){
											strcat(namestring[i],"ノ");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no+kakuritu_kanji_no){
											strcat(namestring[i],"乃");
										}
										strcat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strcat(namestring_choufukucheck[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
									}else{
										strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
										strcat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}
								}
							}else if (ransuu_kakuritu<kakuritu_heya_mid+kakuritu_heya_ato+kakuritu_heya_mid_ato+kakuritu_mae_heya+kakuritu_mid_heya){//mid+部屋別
								if (GetRand(1)==0){
									nagasa_namestring=strlen(temp_namestring_mid[ransuu_mid])+strlen(temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
									if (nagasa_namestring>10){
										strcpy(namestring[i],temp_namestring_mid[ransuu_mid]);
										strncat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0],4);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}else if(nagasa_namestring<9){//「の」「ノ」「乃」
										strcpy(namestring[i],temp_namestring_mid[ransuu_mid]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
										if (ransuu_kakuritu_no<kakuritu_hiragana_no){
											strcat(namestring[i],"の");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no){
											strcat(namestring[i],"ノ");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no+kakuritu_kanji_no){
											strcat(namestring[i],"乃");
										}
										strcat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strcat(namestring_choufukucheck[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
									}else{
										strcpy(namestring[i],temp_namestring_mid[ransuu_mid]);
										strcat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}
								}else{
									nagasa_namestring=strlen(temp_namestring_mid[ransuu_mid])+strlen(temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
									if (nagasa_namestring>10){
										strcpy(namestring[i],temp_namestring_mid[ransuu_mid]);
										strncat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1],4);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}else if(nagasa_namestring<9){//「の」「ノ」「乃」
										strcpy(namestring[i],temp_namestring_mid[ransuu_mid]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
										if (ransuu_kakuritu_no<kakuritu_hiragana_no){
											strcat(namestring[i],"の");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no){
											strcat(namestring[i],"ノ");
										}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no+kakuritu_kanji_no){
											strcat(namestring[i],"乃");
										}
										strcat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strcat(namestring_choufukucheck[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
									}else{
										strcpy(namestring[i],temp_namestring_mid[ransuu_mid]);
										strcat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}
								}
							}else if (ransuu_kakuritu<kakuritu_heya_mid+kakuritu_heya_ato+kakuritu_heya_mid_ato+kakuritu_mae_heya+kakuritu_mid_heya+kakuritu_mae_mid_heya){//mae+mid+部屋別
								if (GetRand(1)==0){
									nagasa_namestring=strlen(temp_namestring_mae[ransuu_mae])+strlen(temp_namestring_mid[ransuu_mid]);
									if (nagasa_namestring>6){
										strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
										strncat(namestring[i],temp_namestring_mid[ransuu_mid],2);
										strcat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}else{
										strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
										strcat(namestring[i],temp_namestring_mid[ransuu_mid]);
										strcat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+0]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}
								}else{
									nagasa_namestring=strlen(temp_namestring_mae[ransuu_mae])+strlen(temp_namestring_mid[ransuu_mid]);
									if (nagasa_namestring>6){
										strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
										strncat(namestring[i],temp_namestring_mid[ransuu_mid],2);
										strcat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}else{
										strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
										strcat(namestring[i],temp_namestring_mid[ransuu_mid]);
										strcat(namestring[i],temp_namestring_heyabetu[rikisidata[i].heyaid*2+1]);
										strcpy(namestring_choufukucheck[i],namestring[i]);
									}
								}
							}else if (ransuu_kakuritu<kakuritu_heya_mid+kakuritu_heya_ato+kakuritu_heya_mid_ato+kakuritu_mae_heya+kakuritu_mid_heya+kakuritu_mae_mid_heya+kakuritu_mae_mid){//mae+mid
								nagasa_namestring=strlen(temp_namestring_mid[ransuu_mid])+strlen(temp_namestring_mae[ransuu_mae]);
								if (nagasa_namestring>10){
									strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
									strncat(namestring[i],temp_namestring_mid[ransuu_mid],4);
									strcpy(namestring_choufukucheck[i],namestring[i]);
								}else if(nagasa_namestring<9){//「の」「ノ」「乃」
									strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
									strcpy(namestring_choufukucheck[i],namestring[i]);
									if (ransuu_kakuritu_no<kakuritu_hiragana_no){
										strcat(namestring[i],"の");
									}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no){
										strcat(namestring[i],"ノ");
									}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no+kakuritu_kanji_no){
										strcat(namestring[i],"乃");
									}
									strcat(namestring[i],temp_namestring_mid[ransuu_mid]);
									strcat(namestring_choufukucheck[i],temp_namestring_mid[ransuu_mid]);
								}else{
									strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
									strcat(namestring[i],temp_namestring_mid[ransuu_mid]);
									strcpy(namestring_choufukucheck[i],namestring[i]);
								}
							}else if (ransuu_kakuritu<kakuritu_heya_mid+kakuritu_heya_ato+kakuritu_heya_mid_ato+kakuritu_mae_heya+kakuritu_mid_heya+kakuritu_mae_mid_heya+kakuritu_mae_mid+kakuritu_mae_ato){//mae+ato
								nagasa_namestring=strlen(temp_namestring_ato[ransuu_ato])+strlen(temp_namestring_mae[ransuu_mae]);
								if (nagasa_namestring>10){
									//strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
									//strncat(namestring[i],temp_namestring_mid[ransuu_mid],4);
								}else if(nagasa_namestring<9){//「の」「ノ」「乃」
									strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
									strcpy(namestring_choufukucheck[i],namestring[i]);
									if (ransuu_kakuritu_no<kakuritu_hiragana_no){
										strcat(namestring[i],"の");
									}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no){
										strcat(namestring[i],"ノ");
									}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no+kakuritu_kanji_no){
										strcat(namestring[i],"乃");
									}
									strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
									strcat(namestring_choufukucheck[i],temp_namestring_ato[ransuu_ato]);
								}else{
									strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
									strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
									strcpy(namestring_choufukucheck[i],namestring[i]);
								}
							}else if (ransuu_kakuritu<kakuritu_heya_mid+kakuritu_heya_ato+kakuritu_heya_mid_ato+kakuritu_mae_heya+kakuritu_mid_heya+kakuritu_mae_mid_heya+kakuritu_mae_mid+kakuritu_mae_ato+kakuritu_mae_mid_ato){//mae+mid+ato
								for (ii=1;ii<54;ii++){
									if (rikisidata[i].hometownid>=heyabetu_sichousonid[ii-1] && rikisidata[i].hometownid<=heyabetu_sichousonid[ii-1]+(heyabetu_sichousonid[ii]-heyabetu_sichousonid[ii-1]-1)){
										break;
									}
								}
								nagasa_namestring=strlen(temp_namestring_mae[ransuu_mae])+strlen(temp_namestring_mid[ransuu_mid]);
								if (nagasa_namestring>6){
									strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
									strncat(namestring[i],temp_namestring_mid[ransuu_mid],2);
									strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
									strcpy(namestring_choufukucheck[i],namestring[i]);
								}else{
									strcpy(namestring[i],temp_namestring_mae[ransuu_mae]);
									strcat(namestring[i],temp_namestring_mid[ransuu_mid]);
									strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
									strcpy(namestring_choufukucheck[i],namestring[i]);
								}
							}else{//mid+ato
								nagasa_namestring=strlen(temp_namestring_mid[ransuu_mid])+strlen(temp_namestring_ato[ransuu_ato]);
								if (nagasa_namestring>10){
									strncpy(namestring[i],temp_namestring_mid[ransuu_mid],2);
									strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
									strcpy(namestring_choufukucheck[i],namestring[i]);
								}else if(nagasa_namestring<9){//「の」「ノ」「乃」
									strcpy(namestring[i],temp_namestring_mid[ransuu_mid]);
									strcpy(namestring_choufukucheck[i],namestring[i]);
									if (ransuu_kakuritu_no<kakuritu_hiragana_no){
										strcat(namestring[i],"の");
									}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no){
										strcat(namestring[i],"ノ");
									}else if (ransuu_kakuritu_no<kakuritu_hiragana_no+kakuritu_katakana_no+kakuritu_kanji_no){
										strcat(namestring[i],"乃");
									}
									strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
									strcat(namestring_choufukucheck[i],temp_namestring_ato[ransuu_ato]);
								}else{
									strcpy(namestring[i],temp_namestring_mid[ransuu_mid]);
									strcat(namestring[i],temp_namestring_ato[ransuu_ato]);
									strcpy(namestring_choufukucheck[i],namestring[i]);
								}
							}
							//重複する四股名がないかチェック
							choufukuflag=0;
							for (ii=0;ii<RIKISISUU;ii++){//この文だけ初期ルーチンと違うので注意
								if (strcmp(namestring_choufukucheck[ii],namestring_choufukucheck[i]) == 0
								&& ii!=i){//←この部分がα005まで入ってなかったので事実上重複チェックが効かなかった
									choufukuflag=1;
/*
fp = fopen("debuglog.txt","a");
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
fprintf(fp,"\n");
fprintf(fp,"%d年%d月　重複と判断　ひっかかった重複確認用四股名=%s　重複確認用生成四股名=%s　生成四股名=%s\n",year,month,namestring_choufukucheck[ii],namestring_choufukucheck[i],namestring[i]);
fprintf(fp,"\n");
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
*/
									break;
								}
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							}
							if (choufukuflag==0){
								break;
							}
							choufukukaisuu++;
							if (choufukukaisuu>1000){//重複するのを前提に四股名ファイルをいじる可能性もあるので無限ループ回避
								choufukukaisuu=0;
								break;
							}
						}

					}else{//四股名ab
						if (GetRand(1)==0){
							strcpy(namestring[i],temp_namestring_mid[(int)(temp_nameid[i]/SIKONA_ATO)]);
							strcat(namestring[i],temp_namestring_ato[temp_nameid[i]%SIKONA_ATO]);
						}else{
							strcpy(namestring[i],temp_namestring_ato[temp_nameid[i]%SIKONA_ATO]);
							strcat(namestring[i],temp_namestring_mid[(int)(temp_nameid[i]/SIKONA_ATO)]);
						}
					}

					//}
				}
				//年寄関連変数初期化
				sanyakuijouzaiisuu[i]=0;
				makuutiijouzaiisuu[i]=0;
				juuryouijouzaiisuu[i]=0;
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (tosiyoridata[ii].keishousha_rikisiid==i){
						tosiyoridata[ii].keishousha_rikisiid=-1;
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				//年齢を代入
				rikisidata[i].age=15;
				//老化スタート年齢決定
				rikisidata[i].age_roukastart=28+GetRand(7);
				//
				rikisidata[i].hadoozekiflag=0;
				//初土俵年月
				if (month>10){
					rikisidata[i].hatudohyo_year=year+1;
					rikisidata[i].hatudohyo_month=1;
				}else{
					rikisidata[i].hatudohyo_year=year;
					rikisidata[i].hatudohyo_month=month+2;
				}
				//早熟フラグ
				if (GetRand(99)<10){
					rikisidata[i].soujukuflag=1;//早熟
				}else if(GetRand(99)<1){
					rikisidata[i].soujukuflag=2;//超早熟
				}else{
					rikisidata[i].soujukuflag=0;
				}


///////////////////////ここから得意型と能力値設定//////////
if (randommode==0){//従来モードなら



				//能力値を代入
if (rikisidata[i].rinneflag==0 || rinneflag_sinchou==0){
				if (GetRand(99)<10){
					rikisidata[i].sinchou_max=GetRand(25)+195;
				}else if(GetRand(99)<10){
					rikisidata[i].sinchou_max=GetRand(8)+170;
				}else{
					rikisidata[i].sinchou_max=GetRand(15)+179;
				}
}
				rikisidata[i].sinchou=GetRand(10)+160;
if (rikisidata[i].rinneflag==0 || rinneflag_taijuu==0){
				if (GetRand(99)<2){
					rikisidata[i].taijuu_max=GetRand(70)+180;
				}else{
					rikisidata[i].taijuu_max=GetRand(69)+110;
				}
}
				rikisidata[i].taijuu=GetRand(30)+70;
if (rikisidata[i].rinneflag==0 || rinneflag_zunou==0){
				rikisidata[i].zunou=GetRand(89)+10;
}

if (rikisidata[i].rinneflag==0 || rinneflag_sekkyokusei==0){
				rikisidata[i].sekkyokusei=GetRand(89)+10;
}

				rikisidata[i].stamina=GetRand(10)+10;
if (rikisidata[i].rinneflag==0 || rinneflag_konjou==0){
				rikisidata[i].konjou=GetRand(89)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_juunansei==0){
				rikisidata[i].juunansei=GetRand(89)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_binshousei==0){
				rikisidata[i].binshousei_natural=GetRand(30)+10;
}
				rikisidata[i].binshousei=60-(int)((rikisidata[i].sinchou-159)/2)-(int)((rikisidata[i].taijuu-69)/5)+rikisidata[i].binshousei_natural;
				if ( ((int)(((169-rikisidata[i].sinchou)*(-3))/2)+140) < rikisidata[i].taijuu ){
					rikisidata[i].binshousei-=(rikisidata[i].taijuu-((int)(((169-rikisidata[i].sinchou)*(-3))/2)+140))*2;
				}
				if (rikisidata[i].binshousei<10) rikisidata[i].binshousei=10;
				if (rikisidata[i].binshousei>99) rikisidata[i].binshousei=99;
if (rikisidata[i].rinneflag==0 || rinneflag_stamina==0){
				rikisidata[i].stamina_natural=GetRand(30);
}

				//以下はVer3.08までは輪廻させていたが、Ver3.09からは選べるようにした
if (rikisidata[i].rinneflag==0 || rinneflag_asihakobi==0){
				rikisidata[i].asihakobi_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_nebari==0){
				rikisidata[i].nebari_max=GetRand(69)+10;
}

				rikisidata[i].stamina=80+rikisidata[i].stamina_natural+rikisidata[i].binshousei;
				rikisidata[i].tossinryoku=GetRand(9)+1;
				rikisidata[i].kerutikara=GetRand(9)+100;
				rikisidata[i].migiwanryoku=GetRand(9)+1;
				rikisidata[i].hidariwanryoku=GetRand(9)+1;
				rikisidata[i].balance=GetRand(9)+1;
				rikisidata[i].tatiaigijutu=GetRand(9)+1;
				rikisidata[i].tuki=GetRand(9)+1;
				rikisidata[i].migiwakikatasa=GetRand(9)+1;
				rikisidata[i].hidariwakikatasa=GetRand(9)+1;
				rikisidata[i].ategai=GetRand(9)+1;
				rikisidata[i].migikaesi=GetRand(9)+1;
				rikisidata[i].hidarikaesi=GetRand(9)+1;
				rikisidata[i].migisibori=GetRand(9)+1;
				rikisidata[i].hidarisibori=GetRand(9)+1;
				rikisidata[i].migikakaekomi=GetRand(9)+1;
				rikisidata[i].hidarikakaekomi=GetRand(9)+1;
				rikisidata[i].hikituke=GetRand(9)+100;
				rikisidata[i].migiakuryoku=GetRand(9)+1;
				rikisidata[i].hidariakuryoku=GetRand(9)+1;
				rikisidata[i].migiuwatenage=GetRand(9)+1;
				rikisidata[i].hidariuwatenage=GetRand(9)+1;
				rikisidata[i].migisitatenage=GetRand(9)+1;
				rikisidata[i].hidarisitatenage=GetRand(9)+1;
				rikisidata[i].migikotenage=GetRand(9)+1;
				rikisidata[i].hidarikotenage=GetRand(9)+1;
				rikisidata[i].migisukuinage=GetRand(9)+1;
				rikisidata[i].hidarisukuinage=GetRand(9)+1;
				rikisidata[i].asihakobi=GetRand(9)+1;
				rikisidata[i].nebari=GetRand(9)+1;

if (rikisidata[i].rinneflag==0){
				if (rikisidata[i].sinchou_max>199 && GetRand(9)<5){
					rr=GetRand(99);
					if (rr<45){
						rikisidata[i].motiwazapattern[0]=14;
					}else if(rr<85){
						rikisidata[i].motiwazapattern[0]=15;
					}else if(rr<90){
						rikisidata[i].motiwazapattern[0]=16;
					}else if(rr<95){
						rikisidata[i].motiwazapattern[0]=17;
					}else{
						rikisidata[i].motiwazapattern[0]=18;
					}
				}else if (rikisidata[i].sinchou_max<176 && GetRand(9)<5){
					rr=GetRand(99);
					if (rr<45){
						rikisidata[i].motiwazapattern[0]=19;
					}else if(rr<85){
						rikisidata[i].motiwazapattern[0]=20;
					}else if(rr<90){
						rikisidata[i].motiwazapattern[0]=21;
					}else if(rr<95){
						rikisidata[i].motiwazapattern[0]=22;
					}else{
						rikisidata[i].motiwazapattern[0]=23;
					}
				}else{
					rr=GetRand(99);
					if (rr<5){
						rikisidata[i].motiwazapattern[0]=0;
					}else if(rr<10){
						rikisidata[i].motiwazapattern[0]=1;
					}else if(rr<15){
						rikisidata[i].motiwazapattern[0]=2;
					}else if(rr<20){
						rikisidata[i].motiwazapattern[0]=3;
					}else if(rr<38){
						rikisidata[i].motiwazapattern[0]=4;
					}else if(rr<54){
						rikisidata[i].motiwazapattern[0]=5;
					}else if(rr<56){
						rikisidata[i].motiwazapattern[0]=6;
					}else if(rr<58){
						rikisidata[i].motiwazapattern[0]=7;
					}else if(rr<60){
						rikisidata[i].motiwazapattern[0]=8;
					}else if(rr<78){
						rikisidata[i].motiwazapattern[0]=9;
					}else if(rr<94){
						rikisidata[i].motiwazapattern[0]=10;
					}else if(rr<96){
						rikisidata[i].motiwazapattern[0]=11;
					}else if(rr<98){
						rikisidata[i].motiwazapattern[0]=12;
					}else{
						rikisidata[i].motiwazapattern[0]=13;
					}
				}
				strcpy(sakusenname[i],"未定義");
				rikisidata[i].motiwazapattern_sentakuritu[0]=8;
				rikisidata[i].motitatiaipattern_sentakuritu[0]=1;
				rikisidata[i].motiwazapattern[1]=0;
				rikisidata[i].motiwazapattern_sentakuritu[1]=8;
				rikisidata[i].motitatiaipattern_sentakuritu[1]=1;
				rikisidata[i].motiwazapattern[2]=2;
				rikisidata[i].motiwazapattern_sentakuritu[2]=8;
				rikisidata[i].motitatiaipattern_sentakuritu[2]=1;
				rikisidata[i].motiwazapattern[3]=3;
				rikisidata[i].motiwazapattern_sentakuritu[3]=8;
				rikisidata[i].motitatiaipattern_sentakuritu[3]=1;
				rikisidata[i].motiwazapattern[4]=4;
				rikisidata[i].motiwazapattern_sentakuritu[4]=8;
				rikisidata[i].motitatiaipattern_sentakuritu[4]=1;
				if (rikisidata[i].motiwazapattern[0]<4){
					rikisidata[i].motitatiaipattern[0]=0;
					rikisidata[i].motitatiaipattern[1]=1;
					rikisidata[i].motitatiaipattern[2]=2;
					rikisidata[i].motitatiaipattern[3]=3;
					rikisidata[i].motitatiaipattern[4]=4;
				}else if(rikisidata[i].motiwazapattern[0]<9){
					rikisidata[i].motitatiaipattern[0]=4;
					rikisidata[i].motitatiaipattern[1]=5;
					rikisidata[i].motitatiaipattern[2]=6;
					rikisidata[i].motitatiaipattern[3]=7;
					rikisidata[i].motitatiaipattern[4]=4;
				}else if(rikisidata[i].motiwazapattern[0]<14){
					rikisidata[i].motitatiaipattern[0]=8;
					rikisidata[i].motitatiaipattern[1]=9;
					rikisidata[i].motitatiaipattern[2]=10;
					rikisidata[i].motitatiaipattern[3]=11;
					rikisidata[i].motitatiaipattern[4]=4;
				}else if(rikisidata[i].motiwazapattern[0]<19){
					rikisidata[i].motitatiaipattern[0]=12;
					rikisidata[i].motitatiaipattern[1]=13;
					rikisidata[i].motitatiaipattern[2]=14;
					rikisidata[i].motitatiaipattern[3]=15;
					rikisidata[i].motitatiaipattern[4]=4;
				}else{
					rikisidata[i].motitatiaipattern[0]=16;
					rikisidata[i].motitatiaipattern[1]=17;
					rikisidata[i].motitatiaipattern[2]=18;
					rikisidata[i].motitatiaipattern[3]=19;
					rikisidata[i].motitatiaipattern[4]=4;
				}
}//輪廻しない普通の力士の設定終わり

				//持ち技パターンから能力値MAXを設定
				if (rikisidata[i].motiwazapattern[0]==0){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==1){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==2){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==3){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==4){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(39)+40+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==5){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==6){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==7){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==8){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==9){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(39)+40+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==10){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==11){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==12){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==13){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(39)+40;
}
				}else if (rikisidata[i].motiwazapattern[0]==14){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(39)+40+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==15){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==16){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==17){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==18){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==19){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==20){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==21){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==22){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}else if (rikisidata[i].motiwazapattern[0]==23){
if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max=GetRand(69)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max=GetRand(69)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max=GetRand(19)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max=GetRand(39)+40;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max=GetRand(29)+10+100;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max=GetRand(29)+10;
}
if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max=GetRand(29)+10;
}
				}

		//力士データに幅を持たせる処理
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
					rikisidata[i].tossinryoku_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
					rikisidata[i].kerutikara_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
					rikisidata[i].migiwanryoku_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
					rikisidata[i].hidariwanryoku_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
					rikisidata[i].balance_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
					rikisidata[i].tatiaigijutu_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
					rikisidata[i].tuki_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
					rikisidata[i].migiwakikatasa_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
					rikisidata[i].hidariwakikatasa_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
					rikisidata[i].ategai_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
					rikisidata[i].migikaesi_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
					rikisidata[i].hidarikaesi_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
					rikisidata[i].migisibori_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
					rikisidata[i].hidarisibori_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
					rikisidata[i].migikakaekomi_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
					rikisidata[i].hidarikakaekomi_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
					rikisidata[i].hikituke_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
					rikisidata[i].migiakuryoku_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
					rikisidata[i].hidariakuryoku_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
					rikisidata[i].migiuwatenage_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
					rikisidata[i].hidariuwatenage_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
					rikisidata[i].migisitatenage_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
					rikisidata[i].hidarisitatenage_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
					rikisidata[i].migikotenage_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
					rikisidata[i].hidarikotenage_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
					rikisidata[i].migisukuinage_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
					rikisidata[i].hidarisukuinage_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_asihakobi==0){
					rikisidata[i].asihakobi_max+=20;
			}
		}
		if (GetRand(19)==0){
			if (rikisidata[i].rinneflag==0 || rinneflag_nebari==0){
					rikisidata[i].nebari_max+=20;
			}
		}

//従来モード能力値設定終わり
}else{//得意型と能力値無関係モード
	if (rikisidata[i].rinneflag==0){//輪廻しない普通の力士なら
		rikisidata[i].motiwazapattern[0]=GetRand(23);
		strcpy(sakusenname[i],"未定義");
		rikisidata[i].motiwazapattern_sentakuritu[0]=8;
		rikisidata[i].motitatiaipattern_sentakuritu[0]=1;
		rikisidata[i].motiwazapattern[1]=0;
		rikisidata[i].motiwazapattern_sentakuritu[1]=8;
		rikisidata[i].motitatiaipattern_sentakuritu[1]=1;
		rikisidata[i].motiwazapattern[2]=2;
		rikisidata[i].motiwazapattern_sentakuritu[2]=8;
		rikisidata[i].motitatiaipattern_sentakuritu[2]=1;
		rikisidata[i].motiwazapattern[3]=3;
		rikisidata[i].motiwazapattern_sentakuritu[3]=8;
		rikisidata[i].motitatiaipattern_sentakuritu[3]=1;
		rikisidata[i].motiwazapattern[4]=4;
		rikisidata[i].motiwazapattern_sentakuritu[4]=8;
		rikisidata[i].motitatiaipattern_sentakuritu[4]=1;
		if (rikisidata[i].motiwazapattern[0]<4){
			rikisidata[i].motitatiaipattern[0]=0;
			rikisidata[i].motitatiaipattern[1]=1;
			rikisidata[i].motitatiaipattern[2]=2;
			rikisidata[i].motitatiaipattern[3]=3;
			rikisidata[i].motitatiaipattern[4]=4;
		}else if(rikisidata[i].motiwazapattern[0]<9){
			rikisidata[i].motitatiaipattern[0]=4;
			rikisidata[i].motitatiaipattern[1]=5;
			rikisidata[i].motitatiaipattern[2]=6;
			rikisidata[i].motitatiaipattern[3]=7;
			rikisidata[i].motitatiaipattern[4]=4;
		}else if(rikisidata[i].motiwazapattern[0]<14){
			rikisidata[i].motitatiaipattern[0]=8;
			rikisidata[i].motitatiaipattern[1]=9;
			rikisidata[i].motitatiaipattern[2]=10;
			rikisidata[i].motitatiaipattern[3]=11;
			rikisidata[i].motitatiaipattern[4]=4;
		}else if(rikisidata[i].motiwazapattern[0]<19){
			rikisidata[i].motitatiaipattern[0]=12;
			rikisidata[i].motitatiaipattern[1]=13;
			rikisidata[i].motitatiaipattern[2]=14;
			rikisidata[i].motitatiaipattern[3]=15;
			rikisidata[i].motitatiaipattern[4]=4;
		}else{
			rikisidata[i].motitatiaipattern[0]=16;
			rikisidata[i].motitatiaipattern[1]=17;
			rikisidata[i].motitatiaipattern[2]=18;
			rikisidata[i].motitatiaipattern[3]=19;
			rikisidata[i].motitatiaipattern[4]=4;
		}
	}
	if(randommode==1){//能力値一様分布で得意型とは無関係
		//能力値を代入
		if (rikisidata[i].rinneflag==0 || rinneflag_sinchou==0){
			rikisidata[i].sinchou_max=GetRand(50)+170;
		}
		rikisidata[i].sinchou=GetRand(10)+160;
		if (rikisidata[i].rinneflag==0 || rinneflag_taijuu==0){
			rikisidata[i].taijuu_max=GetRand(140)+110;
		}
		rikisidata[i].taijuu=GetRand(30)+70;
		if (rikisidata[i].rinneflag==0 || rinneflag_zunou==0){
			rikisidata[i].zunou=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_sekkyokusei==0){
			rikisidata[i].sekkyokusei=GetRand(98)+1;
		}
		rikisidata[i].stamina=GetRand(10)+10;
		if (rikisidata[i].rinneflag==0 || rinneflag_konjou==0){
			rikisidata[i].konjou=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_juunansei==0){
			rikisidata[i].juunansei=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_binshousei==0){
			rikisidata[i].binshousei_natural=GetRand(39)+1;
		}
		rikisidata[i].binshousei=60-(int)((rikisidata[i].sinchou-159)/2)-(int)((rikisidata[i].taijuu-69)/5)+rikisidata[i].binshousei_natural;
		if ( ((int)(((169-rikisidata[i].sinchou)*(-3))/2)+140) < rikisidata[i].taijuu ){
			rikisidata[i].binshousei-=(rikisidata[i].taijuu-((int)(((169-rikisidata[i].sinchou)*(-3))/2)+140))*2;
		}
		if (rikisidata[i].binshousei<10) rikisidata[i].binshousei=10;
		if (rikisidata[i].binshousei>99) rikisidata[i].binshousei=99;
		if (rikisidata[i].rinneflag==0 || rinneflag_stamina==0){
			rikisidata[i].stamina_natural=GetRand(30);
		}
		//以下はVer3.08までは輪廻させていたが、Ver3.09からは選べるようにした
		if (rikisidata[i].rinneflag==0 || rinneflag_asihakobi==0){
			rikisidata[i].asihakobi_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_nebari==0){
			rikisidata[i].nebari_max=GetRand(98)+1;
		}
		rikisidata[i].stamina=80+rikisidata[i].stamina_natural+rikisidata[i].binshousei;
		rikisidata[i].tossinryoku=GetRand(9)+1;
		rikisidata[i].kerutikara=GetRand(9)+100;
		rikisidata[i].migiwanryoku=GetRand(9)+1;
		rikisidata[i].hidariwanryoku=GetRand(9)+1;
		rikisidata[i].balance=GetRand(9)+1;
		rikisidata[i].tatiaigijutu=GetRand(9)+1;
		rikisidata[i].tuki=GetRand(9)+1;
		rikisidata[i].migiwakikatasa=GetRand(9)+1;
		rikisidata[i].hidariwakikatasa=GetRand(9)+1;
		rikisidata[i].ategai=GetRand(9)+1;
		rikisidata[i].migikaesi=GetRand(9)+1;
		rikisidata[i].hidarikaesi=GetRand(9)+1;
		rikisidata[i].migisibori=GetRand(9)+1;
		rikisidata[i].hidarisibori=GetRand(9)+1;
		rikisidata[i].migikakaekomi=GetRand(9)+1;
		rikisidata[i].hidarikakaekomi=GetRand(9)+1;
		rikisidata[i].hikituke=GetRand(9)+100;
		rikisidata[i].migiakuryoku=GetRand(9)+1;
		rikisidata[i].hidariakuryoku=GetRand(9)+1;
		rikisidata[i].migiuwatenage=GetRand(9)+1;
		rikisidata[i].hidariuwatenage=GetRand(9)+1;
		rikisidata[i].migisitatenage=GetRand(9)+1;
		rikisidata[i].hidarisitatenage=GetRand(9)+1;
		rikisidata[i].migikotenage=GetRand(9)+1;
		rikisidata[i].hidarikotenage=GetRand(9)+1;
		rikisidata[i].migisukuinage=GetRand(9)+1;
		rikisidata[i].hidarisukuinage=GetRand(9)+1;
		rikisidata[i].asihakobi=GetRand(9)+1;
		rikisidata[i].nebari=GetRand(9)+1;
		if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
			rikisidata[i].tossinryoku_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
			rikisidata[i].kerutikara_max=GetRand(98)+1+100;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
			rikisidata[i].migiwanryoku_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
			rikisidata[i].hidariwanryoku_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
			rikisidata[i].balance_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
			rikisidata[i].tatiaigijutu_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
			rikisidata[i].tuki_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
			rikisidata[i].migiwakikatasa_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
			rikisidata[i].hidariwakikatasa_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
			rikisidata[i].ategai_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
			rikisidata[i].migikaesi_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
			rikisidata[i].hidarikaesi_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
			rikisidata[i].migisibori_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
			rikisidata[i].hidarisibori_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
			rikisidata[i].migikakaekomi_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
			rikisidata[i].hidarikakaekomi_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
			rikisidata[i].hikituke_max=GetRand(98)+1+100;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
			rikisidata[i].migiakuryoku_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
			rikisidata[i].hidariakuryoku_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
			rikisidata[i].migiuwatenage_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
			rikisidata[i].hidariuwatenage_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
			rikisidata[i].migisitatenage_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
			rikisidata[i].hidarisitatenage_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
			rikisidata[i].migikotenage_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
			rikisidata[i].hidarikotenage_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
			rikisidata[i].migisukuinage_max=GetRand(98)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
			rikisidata[i].hidarisukuinage_max=GetRand(98)+1;
		}
	}else{//randommode==2 能力値正規分布で得意型とは無関係
		//能力値を代入
		if (rikisidata[i].rinneflag==0 || rinneflag_sinchou==0){
			rikisidata[i].sinchou_max=Rand_normal(50,heikin_sinchou,sigma_sinchou)+170;
		}
		rikisidata[i].sinchou=GetRand(10)+160;
		if (rikisidata[i].rinneflag==0 || rinneflag_taijuu==0){
			rikisidata[i].taijuu_max=Rand_normal(140,heikin_taijuu,sigma_taijuu)+110;
		}
		rikisidata[i].taijuu=GetRand(30)+70;
		if (rikisidata[i].rinneflag==0 || rinneflag_zunou==0){
			rikisidata[i].zunou=Rand_normal(98,heikin_zunou,sigma_zunou)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_sekkyokusei==0){
			rikisidata[i].sekkyokusei=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		rikisidata[i].stamina=GetRand(10)+10;
		if (rikisidata[i].rinneflag==0 || rinneflag_konjou==0){
			rikisidata[i].konjou=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_juunansei==0){
			rikisidata[i].juunansei=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_binshousei==0){
			rikisidata[i].binshousei_natural=Rand_normal(39,heikin_binshousei,sigma_binshousei)+1;
		}
		rikisidata[i].binshousei=60-(int)((rikisidata[i].sinchou-159)/2)-(int)((rikisidata[i].taijuu-69)/5)+rikisidata[i].binshousei_natural;
		if ( ((int)(((169-rikisidata[i].sinchou)*(-3))/2)+140) < rikisidata[i].taijuu ){
			rikisidata[i].binshousei-=(rikisidata[i].taijuu-((int)(((169-rikisidata[i].sinchou)*(-3))/2)+140))*2;
		}
		if (rikisidata[i].binshousei<10) rikisidata[i].binshousei=10;
		if (rikisidata[i].binshousei>99) rikisidata[i].binshousei=99;
		if (rikisidata[i].rinneflag==0 || rinneflag_stamina==0){
			rikisidata[i].stamina_natural=Rand_normal(30,heikin_stamina,sigma_stamina);
		}
		//以下はVer3.08までは輪廻させていたが、Ver3.09からは選べるようにした
		if (rikisidata[i].rinneflag==0 || rinneflag_asihakobi==0){
			rikisidata[i].asihakobi_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_nebari==0){
			rikisidata[i].nebari_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		rikisidata[i].stamina=80+rikisidata[i].stamina_natural+rikisidata[i].binshousei;
		rikisidata[i].tossinryoku=GetRand(9)+1;
		rikisidata[i].kerutikara=GetRand(9)+100;
		rikisidata[i].migiwanryoku=GetRand(9)+1;
		rikisidata[i].hidariwanryoku=GetRand(9)+1;
		rikisidata[i].balance=GetRand(9)+1;
		rikisidata[i].tatiaigijutu=GetRand(9)+1;
		rikisidata[i].tuki=GetRand(9)+1;
		rikisidata[i].migiwakikatasa=GetRand(9)+1;
		rikisidata[i].hidariwakikatasa=GetRand(9)+1;
		rikisidata[i].ategai=GetRand(9)+1;
		rikisidata[i].migikaesi=GetRand(9)+1;
		rikisidata[i].hidarikaesi=GetRand(9)+1;
		rikisidata[i].migisibori=GetRand(9)+1;
		rikisidata[i].hidarisibori=GetRand(9)+1;
		rikisidata[i].migikakaekomi=GetRand(9)+1;
		rikisidata[i].hidarikakaekomi=GetRand(9)+1;
		rikisidata[i].hikituke=GetRand(9)+100;
		rikisidata[i].migiakuryoku=GetRand(9)+1;
		rikisidata[i].hidariakuryoku=GetRand(9)+1;
		rikisidata[i].migiuwatenage=GetRand(9)+1;
		rikisidata[i].hidariuwatenage=GetRand(9)+1;
		rikisidata[i].migisitatenage=GetRand(9)+1;
		rikisidata[i].hidarisitatenage=GetRand(9)+1;
		rikisidata[i].migikotenage=GetRand(9)+1;
		rikisidata[i].hidarikotenage=GetRand(9)+1;
		rikisidata[i].migisukuinage=GetRand(9)+1;
		rikisidata[i].hidarisukuinage=GetRand(9)+1;
		rikisidata[i].asihakobi=GetRand(9)+1;
		rikisidata[i].nebari=GetRand(9)+1;
		if (rikisidata[i].rinneflag==0 || rinneflag_tossinryoku==0){
			rikisidata[i].tossinryoku_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_kerutikara==0){
			rikisidata[i].kerutikara_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1+100;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migiwanryoku==0){
			rikisidata[i].migiwanryoku_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidariwanryoku==0){
			rikisidata[i].hidariwanryoku_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_balance==0){
			rikisidata[i].balance_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_tatiaigijutu==0){
			rikisidata[i].tatiaigijutu_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_tuki==0){
			rikisidata[i].tuki_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migiwakikatasa==0){
			rikisidata[i].migiwakikatasa_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidariwakikatasa==0){
			rikisidata[i].hidariwakikatasa_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_ategai==0){
			rikisidata[i].ategai_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migikaesi==0){
			rikisidata[i].migikaesi_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidarikaesi==0){
			rikisidata[i].hidarikaesi_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migisibori==0){
			rikisidata[i].migisibori_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidarisibori==0){
			rikisidata[i].hidarisibori_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migikakaekomi==0){
			rikisidata[i].migikakaekomi_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidarikakaekomi==0){
			rikisidata[i].hidarikakaekomi_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hikituke==0){
			rikisidata[i].hikituke_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1+100;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migiakuryoku==0){
			rikisidata[i].migiakuryoku_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidariakuryoku==0){
			rikisidata[i].hidariakuryoku_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migiuwatenage==0){
			rikisidata[i].migiuwatenage_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidariuwatenage==0){
			rikisidata[i].hidariuwatenage_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migisitatenage==0){
			rikisidata[i].migisitatenage_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidarisitatenage==0){
			rikisidata[i].hidarisitatenage_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migikotenage==0){
			rikisidata[i].migikotenage_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidarikotenage==0){
			rikisidata[i].hidarikotenage_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_migisukuinage==0){
			rikisidata[i].migisukuinage_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
		if (rikisidata[i].rinneflag==0 || rinneflag_hidarisukuinage==0){
			rikisidata[i].hidarisukuinage_max=Rand_normal(98,heikin_sonota,sigma_sonota)+1;
		}
	}
}//得意型と能力値設定終わり




				//能力値合計
				nouryoku_total[i]=rikisidata[i].sekkyokusei+
				rikisidata[i].stamina+
				rikisidata[i].konjou+
				rikisidata[i].nebari+
				rikisidata[i].binshousei+
				rikisidata[i].tossinryoku+
				rikisidata[i].kerutikara+
				rikisidata[i].migiwanryoku+
				rikisidata[i].hidariwanryoku+
				rikisidata[i].balance+
				rikisidata[i].tatiaigijutu+
				rikisidata[i].tuki+
				rikisidata[i].migiwakikatasa+
				rikisidata[i].hidariwakikatasa+
				rikisidata[i].ategai+
				rikisidata[i].migikaesi+
				rikisidata[i].hidarikaesi+
				rikisidata[i].migisibori+
				rikisidata[i].hidarisibori+
				rikisidata[i].migikakaekomi+
				rikisidata[i].hidarikakaekomi+
				rikisidata[i].hikituke+
				rikisidata[i].migiakuryoku+
				rikisidata[i].hidariakuryoku+
				rikisidata[i].migiuwatenage+
				rikisidata[i].hidariuwatenage+
				rikisidata[i].migisitatenage+
				rikisidata[i].hidarisitatenage+
				rikisidata[i].migikotenage+
				rikisidata[i].hidarikotenage+
				rikisidata[i].migisukuinage+
				rikisidata[i].hidarisukuinage+
				rikisidata[i].asihakobi+
				rikisidata[i].juunansei;
				//能力値max合計
				nouryoku_total_max[i]=rikisidata[i].sekkyokusei+
				rikisidata[i].stamina+
				rikisidata[i].konjou+
				rikisidata[i].nebari_max+
//				rikisidata[i].nebari+
				rikisidata[i].binshousei+
				rikisidata[i].tossinryoku_max+
				rikisidata[i].kerutikara_max+
				rikisidata[i].migiwanryoku_max+
				rikisidata[i].hidariwanryoku_max+
				rikisidata[i].balance_max+
				rikisidata[i].tatiaigijutu_max+
				rikisidata[i].tuki_max+
				rikisidata[i].migiwakikatasa_max+
				rikisidata[i].hidariwakikatasa_max+
				rikisidata[i].ategai_max+
				rikisidata[i].migikaesi_max+
				rikisidata[i].hidarikaesi_max+
				rikisidata[i].migisibori_max+
				rikisidata[i].hidarisibori_max+
				rikisidata[i].migikakaekomi_max+
				rikisidata[i].hidarikakaekomi_max+
				rikisidata[i].hikituke_max+
				rikisidata[i].migiakuryoku_max+
				rikisidata[i].hidariakuryoku_max+
				rikisidata[i].migiuwatenage_max+
				rikisidata[i].hidariuwatenage_max+
				rikisidata[i].migisitatenage_max+
				rikisidata[i].hidarisitatenage_max+
				rikisidata[i].migikotenage_max+
				rikisidata[i].hidarikotenage_max+
				rikisidata[i].migisukuinage_max+
				rikisidata[i].hidarisukuinage_max+
				rikisidata[i].asihakobi_max+
				rikisidata[i].juunansei;


				//所属部屋確定
				countheya=0;
				for (ii=0;ii<RIKISISUU;ii++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}
					if (rikisidata[ii].heyaid==myheyaid) countheya++;
				}
				if (scoutmoney>=200 && countheya<20 && nouryoku_total_max[i]>filter_nouryoku_total_max
				 && hoketuflag==0){
					siganshasuu_myheya++;
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					game_main_backscreen();//基本ゲーム画面表示ルーチン
					nouryokuhyoji(i,0);
					DrawBox(187,152,280,152+14,CRBACK,TRUE);
					DrawBox(287,216,380,216+14,CRBACK,TRUE);
					DrawBox(287,232,380,232+14,CRBACK,TRUE);
					DrawBox(187,72,637,87,CRBACK,TRUE);
					DrawBox(187,72+16,637,87+16,CRBACK,TRUE);
					//SetFontSize(16);
					DrawFormatString(187,369,CRWHITE,"%sでいい子を見つけました。",hometownstring[rikisidata[i].hometownid]);
//					DrawFormatString(187,369+16,CRWHITE,"入門するなら%sという四股名がいいそうです。",namestring[rikisidata[i].nameid]);
					if (tukedasi_sanndanmeflag==1){
						DrawString(187,369+16,"入門させますか(現在は18歳ですが15歳時点の能力を表示)",CRWHITE);
					}else{
						DrawString(187,369+16,"入門させますか(現在は21歳ですが15歳時点の能力を表示)",CRWHITE);
					}
					DrawString(187,369+48,"入門させる　　　　　　　見送る",CRGREEN);
					DrawString(187,369+64,"上の緑色の文字をクリックしてください",CRWHITE);
					DrawString(187,369+80,"もし紫色の文字が見えるのなら…予知能力！？",CRWHITE);
					ScreenFlip();
					// キー入力待ち(この一文を入れないとうまくいかないみたい)
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
					}
					while(1)
					{
						Sleep(1);
						if( get_mouseclick( 187,369+48,300,369+48+16 )==1){
							if (superrikisisuu[2]!=0){
								rikisidata[i].binshousei_natural=10;
								rikisidata[i].stamina_natural=0;
								rikisidata[i].konjou=100-rikisidata[i].sekkyokusei;
							}
							scoutmoney=0;
////幕下付け出しデビューテスト/////////////////////////////////////
{
	int r=0;
	r=GetRand(6);
	tukedasiid=i;
	if (tukedasi_sanndanmeflag==1){
		for (ii=0;ii<6*(6+r);ii++){
			keiko_nakami_com(tukedasiid);
			//if( ProcessMessage() == -1 ){mode=1;return ;}
		}
		rikisidata[i].age=18;
	}else{
		for (ii=0;ii<6*(12+r);ii++){
		//for (ii=0;ii<6*5;ii++){
			keiko_nakami_com(tukedasiid);
			//if( ProcessMessage() == -1 ){mode=1;return ;}
		}
		rikisidata[i].age=21;
	}
}
//////////////////////////////////////////////////////////////////
							shozokurikisisuu[myheyaid]++;
							shozokurikisisuu[rikisidata[i].heyaid]--;
							rikisidata[i].heyaid=myheyaid;
							for (ii=0;ii<5;ii++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}
								joukendata[i].motitatiaipattern_sakusen[ii]=ii;
								joukendata[i].motitatiaipattern_jouken[ii]=ii;
							}
							joukendata[i].joukenflag=0;
							strcpy(joukendata[i].joukenname,"未定義");
							for (ii=0;ii<100;ii++){
								joukendata[i].joukenwazaid[0][ii]=1;
								joukendata[i].joukenwazaid[1][ii]=8;
								joukendata[i].joukensentakuritu[0][ii]=100;
								joukendata[i].joukensentakuritu[1][ii]=100;
								for (iii=0;iii<11;iii++){
									//if( ProcessMessage() == -1 ){mode=1;return ;}
									joukendata[i].jouken[0][iii][ii]=0;
									joukendata[i].jouken[1][iii][ii]=0;
								}
							}
							strcpy(sakusenname[i],"未定義");
							//rikisidata[i].motiwazapattern[0]=0;
							rikisidata[i].motiwazapattern_sentakuritu[0]=8;
							rikisidata[i].motitatiaipattern_sentakuritu[0]=1;
							//rikisidata[i].motiwazapattern[1]=0;
							rikisidata[i].motiwazapattern_sentakuritu[1]=8;
							rikisidata[i].motitatiaipattern_sentakuritu[1]=1;
							//rikisidata[i].motiwazapattern[2]=2;
							rikisidata[i].motiwazapattern_sentakuritu[2]=8;
							rikisidata[i].motitatiaipattern_sentakuritu[2]=1;
							//rikisidata[i].motiwazapattern[3]=3;
							rikisidata[i].motiwazapattern_sentakuritu[3]=8;
							rikisidata[i].motitatiaipattern_sentakuritu[3]=1;
							//rikisidata[i].motiwazapattern[4]=4;
							rikisidata[i].motiwazapattern_sentakuritu[4]=8;
							rikisidata[i].motitatiaipattern_sentakuritu[4]=1;
							//rikisidata[i].motitatiaipattern[0]=0;
							//rikisidata[i].motitatiaipattern[1]=1;
							//rikisidata[i].motitatiaipattern[2]=2;
							//rikisidata[i].motitatiaipattern[3]=3;
							//rikisidata[i].motitatiaipattern[4]=4;
							if (superrikisisuu[2]==1){
								ikuseihousin_shori(i);
								if (randommode==0){//従来のランダム生成モードなら
									if (scout_housin>13 && scout_housin<19){
										rikisidata[i].sinchou_max=GetRand(15)+195;
									}else if (scout_housin>18){
										rikisidata[i].sinchou_max=GetRand(5)+170;
									}
								}
							}
							ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
							DrawBox(0,0,639,479,CRBACK,TRUE);
							game_main_backscreen();
							DrawString(187,369,"では、弟子の四股名を決定しましょう。",CRWHITE);
							DrawString(187,369+16,"全角５文字以内で入力して下さい。",CRWHITE);
							DrawString(187,369+32,"ENTERキーで確定です。",CRWHITE);
							DrawString(187,369+48,"四股名＞",CRWHITE);
							ScreenFlip() ;//裏画面を表画面にコピー
							while(1){
								KeyInputString( 187+120 , 369+48 , 10 , temp_str_name , FALSE );
								if (strncmp(temp_str_name,"\0",1)!=0){
									strcpy(namestring[i],temp_str_name);
									strcpy(namestring_choufukucheck[i],namestring[i]);
									break;
								}
								// メッセージ処理
								if( ProcessMessage() == -1 ){
									mode=1;
									return ;	// エラーが発生したらループを抜ける
								}
								Sleep(1);
							}
							break;
						}
						if( get_mouseclick( 340,369+48,480,369+48+16 )==1){
							break;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 )
						{
							mode=1;
							return ;	// エラーが起きたらループから抜ける
						}
					}
				}else if (scoutmoney>0 && countheya<20 && nouryoku_total_max[i]>filter_nouryoku_total_max
				 && hoketuflag==0){
					siganshasuu_myheya++;
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					game_main_backscreen();//基本ゲーム画面表示ルーチン
					nouryokuhyoji(i,0);
					DrawBox(187,152,280,152+14,CRBACK,TRUE);
					DrawBox(287,216,380,216+14,CRBACK,TRUE);
					DrawBox(287,232,380,232+14,CRBACK,TRUE);
					DrawBox(187,72,637,87,CRBACK,TRUE);
					DrawBox(187,72+16,637,87+16,CRBACK,TRUE);
					//SetFontSize(16);
					DrawFormatString(187,369,CRWHITE,"%sでいい子を見つけました。",hometownstring[rikisidata[i].hometownid]);
//					DrawFormatString(187,369+16,CRWHITE,"入門するなら%sという四股名がいいそうです。",namestring[rikisidata[i].nameid]);
					DrawString(187,369+16,"入門させますか",CRWHITE);
					DrawString(187,369+48,"入門させる　　　　　　　見送る",CRGREEN);
					DrawString(187,369+64,"上の緑色の文字をクリックしてください",CRWHITE);
					DrawString(187,369+80,"もし紫色の文字が見えるのなら…予知能力！？",CRWHITE);
					ScreenFlip();
					// キー入力待ち(この一文を入れないとうまくいかないみたい)
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
					}
					while(1)
					{
						Sleep(1);
						if( get_mouseclick( 187,369+48,300,369+48+16 )==1){
							if (superrikisisuu[2]!=0){
								rikisidata[i].binshousei_natural=10;
								rikisidata[i].stamina_natural=0;
								rikisidata[i].konjou=100-rikisidata[i].sekkyokusei;
							}
							scoutmoney=0;
							shozokurikisisuu[myheyaid]++;
							shozokurikisisuu[rikisidata[i].heyaid]--;
							rikisidata[i].heyaid=myheyaid;
							for (ii=0;ii<5;ii++){
								if( ProcessMessage() == -1 ){mode=1;return ;}
								joukendata[i].motitatiaipattern_sakusen[ii]=ii;
								joukendata[i].motitatiaipattern_jouken[ii]=ii;
							}
							joukendata[i].joukenflag=0;
							strcpy(joukendata[i].joukenname,"未定義");
							for (ii=0;ii<100;ii++){
								joukendata[i].joukenwazaid[0][ii]=1;
								joukendata[i].joukenwazaid[1][ii]=8;
								joukendata[i].joukensentakuritu[0][ii]=100;
								joukendata[i].joukensentakuritu[1][ii]=100;
								for (iii=0;iii<11;iii++){
									if( ProcessMessage() == -1 ){mode=1;return ;}
									joukendata[i].jouken[0][iii][ii]=0;
									joukendata[i].jouken[1][iii][ii]=0;
								}
							}
							strcpy(sakusenname[i],"未定義");
							//rikisidata[i].motiwazapattern[0]=0;
							rikisidata[i].motiwazapattern_sentakuritu[0]=8;
							rikisidata[i].motitatiaipattern_sentakuritu[0]=1;
							//rikisidata[i].motiwazapattern[1]=0;
							rikisidata[i].motiwazapattern_sentakuritu[1]=8;
							rikisidata[i].motitatiaipattern_sentakuritu[1]=1;
							//rikisidata[i].motiwazapattern[2]=2;
							rikisidata[i].motiwazapattern_sentakuritu[2]=8;
							rikisidata[i].motitatiaipattern_sentakuritu[2]=1;
							//rikisidata[i].motiwazapattern[3]=3;
							rikisidata[i].motiwazapattern_sentakuritu[3]=8;
							rikisidata[i].motitatiaipattern_sentakuritu[3]=1;
							//rikisidata[i].motiwazapattern[4]=4;
							rikisidata[i].motiwazapattern_sentakuritu[4]=8;
							rikisidata[i].motitatiaipattern_sentakuritu[4]=1;
							//rikisidata[i].motitatiaipattern[0]=0;
							//rikisidata[i].motitatiaipattern[1]=1;
							//rikisidata[i].motitatiaipattern[2]=2;
							//rikisidata[i].motitatiaipattern[3]=3;
							//rikisidata[i].motitatiaipattern[4]=4;
							if (superrikisisuu[2]==1){
								ikuseihousin_shori(i);
								if (randommode==0){//従来のランダム生成モードなら
									if (scout_housin>13 && scout_housin<19){
										rikisidata[i].sinchou_max=GetRand(15)+195;
									}else if (scout_housin>18){
										rikisidata[i].sinchou_max=GetRand(5)+170;
									}
								}
							}
							ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
							DrawBox(0,0,639,479,CRBACK,TRUE);
							game_main_backscreen();
							DrawString(187,369,"では、弟子の四股名を決定しましょう。",CRWHITE);
							DrawString(187,369+16,"全角５文字以内で入力して下さい。",CRWHITE);
							DrawString(187,369+32,"ENTERキーで確定です。",CRWHITE);
							DrawString(187,369+48,"四股名＞",CRWHITE);
							ScreenFlip() ;//裏画面を表画面にコピー
							while(1){
								KeyInputString( 187+120 , 369+48 , 10 , temp_str_name , FALSE );
								if (strncmp(temp_str_name,"\0",1)!=0){
									strcpy(namestring[i],temp_str_name);
									break;
								}
								// メッセージ処理
								if( ProcessMessage() == -1 ){
									mode=1;
									return ;	// エラーが発生したらループを抜ける
								}
								Sleep(1);
							}
							break;
						}
						if( get_mouseclick( 340,369+48,480,369+48+16 )==1){
							break;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 )
						{
							mode=1;
							return ;	// エラーが起きたらループから抜ける
						}
					}
				}else{
					heyadata[rikisidata[i].heyaid].hpoint-=100;
				}



				//次場所の番付を一番下にさせるため無理やり
				for (ii=0;ii<15;ii++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}
					rikisidata[i].lostkonbasho[ii]=1;
					rikisidata[i].winkonbasho[ii]=0;
					rikisidata[i].yaowinkonbasho[ii]=0;
				}
				rikisidata[i].retirekonbasho=1;
				//自己最高トーナメント、優勝回数
				rikisidata[i].jikosaiko_tournament=0;
				rikisidata[i].yuushoukaisuu_tournament=0;
				//自己最高位を序の口40にセット
				rikisidata[i].jikosaiko_bandukenameid=9;
				rikisidata[i].jikosaiko_bandukesuuji=40;
				//通算勝ち星、負け星リセット
				rikisidata[i].wintotal=0;
				rikisidata[i].losttotal=0;
				rikisidata[i].makuuti_win=0;
				rikisidata[i].makuuti_lost=0;
				//その他リセット
				for (ii=0;ii<50;ii++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}
					keikodata[i].keikoryou[ii]=1;
					keikodata[i].setteibalance[ii]=5;
					kakodata[i].nouryokuti[ii]=0;
				}
				binshousei_natural_kakosaikou[i]=0;//引退力士表示用
				stamina_natural_kakosaikou[i]=0;//引退力士表示用
				if (rikisidata[i].rinneflag!=1){
					for (ii=0;ii<5;ii++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}
						joukendata[i].motitatiaipattern_sakusen[ii]=ii;
						joukendata[i].motitatiaipattern_jouken[ii]=ii;
					}
					joukendata[i].joukenflag=0;
					strcpy(joukendata[i].joukenname,"未定義");
					for (ii=0;ii<100;ii++){
						joukendata[i].joukenwazaid[0][ii]=1;
						joukendata[i].joukenwazaid[1][ii]=8;
						joukendata[i].joukensentakuritu[0][ii]=100;
						joukendata[i].joukensentakuritu[1][ii]=100;
						for (iii=0;iii<11;iii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}
							joukendata[i].jouken[0][iii][ii]=0;
							joukendata[i].jouken[1][iii][ii]=0;
						}
					}
					strcpy(sakusenname[i],"未定義");
					rikisidata[i].motiwazapattern_sentakuritu[0]=8;
					rikisidata[i].motitatiaipattern_sentakuritu[0]=1;
					rikisidata[i].motiwazapattern[1]=0;
					rikisidata[i].motiwazapattern_sentakuritu[1]=8;
					rikisidata[i].motitatiaipattern_sentakuritu[1]=1;
					rikisidata[i].motiwazapattern[2]=2;
					rikisidata[i].motiwazapattern_sentakuritu[2]=8;
					rikisidata[i].motitatiaipattern_sentakuritu[2]=1;
					rikisidata[i].motiwazapattern[3]=3;
					rikisidata[i].motiwazapattern_sentakuritu[3]=8;
					rikisidata[i].motitatiaipattern_sentakuritu[3]=1;
					rikisidata[i].motiwazapattern[4]=4;
					rikisidata[i].motiwazapattern_sentakuritu[4]=8;
					rikisidata[i].motitatiaipattern_sentakuritu[4]=1;
					joukendata[i].motitatiaipattern_sakusen[0]=0;
					joukendata[i].motitatiaipattern_sakusen[1]=1;
					joukendata[i].motitatiaipattern_sakusen[2]=2;
					joukendata[i].motitatiaipattern_sakusen[3]=3;
					joukendata[i].motitatiaipattern_sakusen[4]=4;
				}
				rikisidata[i].wazaritu_tukidasi=0;
				rikisidata[i].wazaritu_yorikiri=0;
				rikisidata[i].wazaritu_migiuwatenage=0;
				rikisidata[i].wazaritu_hidariuwatenage=0;
				rikisidata[i].wazaritu_migisitatenage=0;
				rikisidata[i].wazaritu_hidarisitatenage=0;
				rikisidata[i].wazaritu_migikotenage=0;
				rikisidata[i].wazaritu_hidarikotenage=0;
				rikisidata[i].wazaritu_migisukuinage=0;
				rikisidata[i].wazaritu_hidarisukuinage=0;
				rikisidata[i].wazaritu_sonota=0;
				rikisidata[i].wazaritu_tukidasisuu=0;
				rikisidata[i].wazaritu_yorikirisuu=0;
				rikisidata[i].wazaritu_migiuwatenagesuu=0;
				rikisidata[i].wazaritu_hidariuwatenagesuu=0;
				rikisidata[i].wazaritu_migisitatenagesuu=0;
				rikisidata[i].wazaritu_hidarisitatenagesuu=0;
				rikisidata[i].wazaritu_migikotenagesuu=0;
				rikisidata[i].wazaritu_hidarikotenagesuu=0;
				rikisidata[i].wazaritu_migisukuinagesuu=0;
				rikisidata[i].wazaritu_hidarisukuinagesuu=0;
				rikisidata[i].wazaritu_sonotasuu=0;
				rikisidata[i].kinbosisuu_konbasho=0;
				rikisidata[i].ginbosisuu_konbasho=0;
				rikisidata[i].kinbosisuu=0;
				rikisidata[i].kiroku_renshou=0;
				rikisidata[i].kiroku_renpai=0;
				rikisidata[i].now_renshou=0;
				rikisidata[i].now_renpai=0;
//				rikisidata[i].mesinoryou=10;
//				rikisidata[i].mesinokori=10;
				rikisidata[i].torikumimiruflag=0;
				rikisidata[i].realmodeflag=0;
				rikisidata[i].kadobanflag=0;
				rikisidata[i].kadobankaraotitaflag=0;
				rikisidata[i].oozekiyuushouorjunyuushou[0]=0;
				rikisidata[i].oozekiyuushouorjunyuushou[1]=0;
				rikisidata[i].sanyakuwin[0]=0;
				rikisidata[i].sanyakuwin[1]=0;
				rikisidata[i].sanyakuwin[2]=0;
				seiseki_sentaku_page[i]=0;
				seiseki_max_page[i]=0;
				rikisidata[i].kiroku_yuushoukaisuu=0;
				rikisidata[i].ginoushousuu=0;
				rikisidata[i].kantoushousuu=0;
				rikisidata[i].shukunshousuu=0;

				kyuujouflag[i]=0;

				for (ii=0;ii<RIKISISUU;ii++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}
					rikisidata[i].rikisibetu_wintotal[ii]=0;
					rikisidata[i].rikisibetu_losttotal[ii]=0;
					rikisidata[ii].rikisibetu_wintotal[i]=0;
					rikisidata[ii].rikisibetu_losttotal[i]=0;
				}
				for (ii=0;ii<15;ii++){
					//rikisidata[i].winkonbasho[ii]=0;番付作成のためにここでは初期化できない
					//rikisidata[i].lostkonbasho[ii]=0;番付作成のためにここでは初期化できない
														//kyuujoukonbasho[][]も番付作成ルーチンの最後の方で初期化している
					rikisidata[i].aitekonbasho[ii]=-1;
				}
				for (ii=0;ii<180;ii++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}
					rikisidata[i].kako_bandukehigasiornisi[ii]=-1;//過去180場所の番付が東か西か、-1で未記録
					rikisidata[i].kako_bandukenameid[ii]=-1;
					rikisidata[i].kako_bandukesuuji[ii]=-1;
					rikisidata[i].kako_win[ii]=0;
					rikisidata[i].kako_lost[ii]=0;
					rikisidata[i].kako_yuushouflag[ii]=0;
				}
				for (ii=0;ii<6;ii++){
					for (iii=0;iii<15;iii++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}
					rikisidata[i].kako_turncountkonbasho[ii][iii]=-1;//過去6場所15日間の各取組の所要ターン数
					rikisidata[i].kako_winkonbasho[ii][iii]=0;//過去6場所15日間の各取組の決まり手
					rikisidata[i].kako_lostkonbasho[ii][iii]=0;//過去6場所15日間の各取組の決まり手
					rikisidata[i].kako_kimaritekonbasho[ii][iii][0]='\0';//過去6場所15日間の各取組の決まり手
					}
				}
				for (ii=0;ii<180;ii++){
					for (iii=0;iii<15;iii++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}
					rikisidata[i].kako_aitekonbasho[ii][iii]=-1;//過去180場所15日間の各取組の決まり手
					}
				}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (iiii=0;iiii<RIKISISUU;iiii++){
					for (ii=0;ii<6;ii++){
						for (iii=0;iii<15;iii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}
							if (rikisidata[iiii].kako_aitekonbasho[ii][iii]==i){
								rikisidata[iiii].kako_turncountkonbasho[ii][iii]=-1;
								rikisidata[iiii].kako_winkonbasho[ii][iii]=0;
								rikisidata[iiii].kako_lostkonbasho[ii][iii]=0;
								rikisidata[iiii].kako_aitekonbasho[ii][iii]=-1;
								rikisidata[iiii].kako_kimaritekonbasho[ii][iii][0]='\0';
							}
						}
					}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				//稽古量分をboost処理
				rikisidata[i].sekkyokusei+=heyadata[rikisidata[i].heyaid].keikoryou*keikoryou_boost;
				rikisidata[i].nebari+=heyadata[rikisidata[i].heyaid].keikoryou*keikoryou_boost;
				rikisidata[i].stamina+=heyadata[rikisidata[i].heyaid].keikoryou*keikoryou_boost;
				rikisidata[i].konjou+=heyadata[rikisidata[i].heyaid].keikoryou*keikoryou_boost;

				//自分の部屋の力士は取組を見るようにする
				if (rikisidata[i].heyaid==myheyaid){
					//「ver2.44」で30年スキップがある場合を想定して変更
					if (skipmode!=2 ||  (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){
						rikisidata[i].torikumimiruflag=1;
					}else{
						rikisidata[i].torikumimiruflag=0;//３０年スキップ用
					}
					if (superrikisisuu[2]==1){
						rikisidata[i].realmodeflag=1;
						joukendata[i].joukenflag=0;
					}
				}else{
					ikuseiboost[i]=1;
					ikuseibunbo[i]=1;
				}

				//初期設定の作戦が成長型AIの場合
//				if (rikisidata[i].rinneflag==0 && superrikisisuu[8]>=1){
				if (rikisidata[i].rinneflag==0 && AIheyaflag[rikisidata[i].heyaid]==1){
					if (memoryfusokuflag==0){
						joukendata[i].joukenflag=3;
					}else{
						joukendata[i].joukenflag=0;
					}
				}
				if (AIheyaflag[rikisidata[i].heyaid]==2){
					joukendata[i].joukenflag=4;
				}
				//自動稽古
				if (rikisidata[i].rinneflag==0){
					rikisidata[i].superrikisiflag=shokiti_superrikisiflag;
				}

				//max処理
				if (superrikisisuu[2]==0 && maxmode==1){//箱庭モードかつmaxモードなら
					rikisidata[i].sinchou=rikisidata[i].sinchou_max;
					rikisidata[i].taijuu=rikisidata[i].taijuu_max;
					//rikisidata[i].sekkyokusei=rikisidata[i].sekkyokusei_max;
					rikisidata[i].tossinryoku=rikisidata[i].tossinryoku_max;
					rikisidata[i].kerutikara=rikisidata[i].kerutikara_max;
					rikisidata[i].migiwanryoku=rikisidata[i].migiwanryoku_max;
					rikisidata[i].hidariwanryoku=rikisidata[i].hidariwanryoku_max;
					rikisidata[i].balance=rikisidata[i].balance_max;
					rikisidata[i].tatiaigijutu=rikisidata[i].tatiaigijutu_max;//「ver2.39での変更」
					rikisidata[i].tuki=rikisidata[i].tuki_max;
					rikisidata[i].migiwakikatasa=rikisidata[i].migiwakikatasa_max;
					rikisidata[i].hidariwakikatasa=rikisidata[i].hidariwakikatasa_max;
					rikisidata[i].ategai=rikisidata[i].ategai_max;
					rikisidata[i].migikaesi=rikisidata[i].migikaesi_max;
					rikisidata[i].hidarikaesi=rikisidata[i].hidarikaesi_max;
					rikisidata[i].migisibori=rikisidata[i].migisibori_max;
					rikisidata[i].hidarisibori=rikisidata[i].hidarisibori_max;
					rikisidata[i].migikakaekomi=rikisidata[i].migikakaekomi_max;
					rikisidata[i].hidarikakaekomi=rikisidata[i].hidarikakaekomi_max;
					rikisidata[i].hikituke=rikisidata[i].hikituke_max;
					rikisidata[i].migiakuryoku=rikisidata[i].migiakuryoku_max;
					rikisidata[i].hidariakuryoku=rikisidata[i].hidariakuryoku_max;
					//rikisidata[i].konjou=rikisidata[i].konjou_max;
					rikisidata[i].nebari=rikisidata[i].nebari_max;
					rikisidata[i].asihakobi=rikisidata[i].asihakobi_max;
					//rikisidata[i].juunansei=rikisidata[i].juunansei_max;
					//rikisidata[i].zunou=rikisidata[i].zunou_max;
					rikisidata[i].migiuwatenage=rikisidata[i].migiuwatenage_max;
					rikisidata[i].hidariuwatenage=rikisidata[i].hidariuwatenage_max;
					rikisidata[i].migisitatenage=rikisidata[i].migisitatenage_max;
					rikisidata[i].hidarisitatenage=rikisidata[i].hidarisitatenage_max;
					rikisidata[i].migikotenage=rikisidata[i].migikotenage_max;
					rikisidata[i].hidarikotenage=rikisidata[i].hidarikotenage_max;
					rikisidata[i].migisukuinage=rikisidata[i].migisukuinage_max;
					rikisidata[i].hidarisukuinage=rikisidata[i].hidarisukuinage_max;
					rikisidata[i].binshousei=60-(int)((rikisidata[i].sinchou-159)/2)-(int)((rikisidata[i].taijuu-69)/5)+rikisidata[i].binshousei_natural;
					if ( ((int)(((169-rikisidata[i].sinchou)*(-3))/2)+140) < rikisidata[i].taijuu ){
						rikisidata[i].binshousei-=(rikisidata[i].taijuu-((int)(((169-rikisidata[i].sinchou)*(-3))/2)+140))*2;
					}
					if (rikisidata[i].binshousei<10) rikisidata[i].binshousei=10;
					if (rikisidata[i].binshousei>99) rikisidata[i].binshousei=99;
					rikisidata[i].stamina=80+rikisidata[i].stamina_natural+rikisidata[i].binshousei;
				}





				//過去能力値リセット
				ii=0;
				kakodata[i].nouryokuti[ii]=rikisidata[i].sinchou;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].taijuu;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].sekkyokusei;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].binshousei;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].tossinryoku;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].kerutikara;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].migiwanryoku;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].hidariwanryoku;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].balance;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].tatiaigijutu;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].tuki;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].migiwakikatasa;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].hidariwakikatasa;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].ategai;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].migikaesi;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].hidarikaesi;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].migisibori;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].hidarisibori;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].migikakaekomi;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].hidarikakaekomi;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].hikituke;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].migiakuryoku;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].hidariakuryoku;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].stamina;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].konjou;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].nebari;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].asihakobi;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].juunansei;ii++;
				kakodata[i].nouryokuti[ii]=100-rikisidata[i].zunou;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].migiuwatenage;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].hidariuwatenage;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].migisitatenage;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].hidarisitatenage;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].migikotenage;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].hidarikotenage;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].migisukuinage;ii++;
				kakodata[i].nouryokuti[ii]=rikisidata[i].hidarisukuinage;ii++;

				//////////直近の稽古の付帯情報/////////////
				{
					int ii;
					lastkeiko_year[i]=0;
					lastkeiko_month[i]=0;
					lastkeiko_day[i]=0;
					for (ii=0;ii<12;ii++){
						lastkeiko_aitenamestring[i][ii]=0;
					}
				}

				//////////何の技を選択するのかのwazadata_kouka[22][RIKISISUU][5]初期化　ＡＩ関連AI関連///////////////
				{
					int ii,iii;
					for (iii=0;iii<22;iii++){
						for (ii=0;ii<5;ii++){
							lastwazadata_kouka_seme[iii][i][ii]=0;
							lastwazadata_bosuu_seme[iii][i][ii]=0;
						}
					}
					for (iii=0;iii<20;iii++){
						lasttatiaidata_kouka_seme[i][iii];//どの立ち合いが勝利に結びついたか
						lasttatiaidata_bosuu_seme[i][iii];//どの立ち合いが勝利に結びついたか
					}
				}
				///////////////////////////////////////////////////////////////////////////////

				//////////何の技を選択するのかのwazadata_kouka[22][RIKISISUU][5]初期化　ＡＩ関連AI関連///////////////
				{
					int ii,iii;
					for (iii=0;iii<22;iii++){
						for (ii=0;ii<5;ii++){
							wazadata_kouka_seme[iii][i][ii]=0;
							wazadata_bosuu_seme[iii][i][ii]=0;
						}
					}
					for (iii=0;iii<20;iii++){
						tatiaidata_kouka_seme[i][iii];//どの立ち合いが勝利に結びついたか
						tatiaidata_bosuu_seme[i][iii];//どの立ち合いが勝利に結びついたか
					}
				}
				///////////////////////////////////////////////////////////////////////////////

				//////////aidataファイル初期化　ＡＩ関連AI関連//////////////////////////////////
				if (memoryfusokuflag==0 && memorykakuchouflag==1){
					ClearDrawScreen();
					DrawString(187,369,"引退力士のAIdata初期化中…",CRWHITE);
					ScreenFlip();
					memset(rbetuwdata_kouka
						+i*RIKISISUU*22*5, 0, sizeof(unsigned short int) * RIKISISUU*22*5); // ここを追加
					memset(rbetuwdata_bosuu
						+i*RIKISISUU*22*5, 0, sizeof(unsigned short int) * RIKISISUU*22*5); // ここを追加
					memset(rbetutdata_kouka
						+i*RIKISISUU*20, 0, sizeof(unsigned short int) * RIKISISUU*20); // ここを追加
					memset(rbetutdata_bosuu
						+i*RIKISISUU*20, 0, sizeof(unsigned short int) * RIKISISUU*20); // ここを追加
					if( ProcessMessage() == -1 ){mode=1;return ;}// エラー処理
					for (ii=0;ii<RIKISISUU;ii++){
						memset(rbetuwdata_kouka
							+ii*RIKISISUU*22*5
							+i*22*5, 0, sizeof(unsigned short int) * 22*5); // ここを追加
						memset(rbetuwdata_bosuu
							+ii*RIKISISUU*22*5
							+i*22*5, 0, sizeof(unsigned short int) * 22*5); // ここを追加
						memset(rbetutdata_kouka
							+ii*RIKISISUU*20
							+i*20, 0, sizeof(unsigned short int) * 20); // ここを追加
						memset(rbetutdata_bosuu
							+ii*RIKISISUU*20
							+i*20, 0, sizeof(unsigned short int) * 20); // ここを追加

						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラー処理
					}

				}
				////////////////////////////////////////////////////////////////////////////////
				if (memoryfusokuflag==0){
				if (rikisidata[i].rinneflag==0){
					ClearDrawScreen();
					DrawString(187,369,"引退力士のAIdata初期化中…",CRWHITE);
					ScreenFlip();
					int temp_id1,temp_id2;
					int i1=0;
					int i2,i3,i4,i5,i6,i7;
					long temp_fichi=0;
					char temp_char=0;
					char bytedata=0;
					int ii;
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラー処理
					/////初期値2に////
					memset(aidata
						+i*RIKISISUU*AIDATABYTESUU, b10101010, sizeof(char) * RIKISISUU*AIDATABYTESUU); // ここを追加
					memset(aidata_tatiai
						+i*RIKISISUU*AIDATATATIAIBYTESUU, b10101010, sizeof(char) * RIKISISUU*AIDATATATIAIBYTESUU); // ここを追加
					if( ProcessMessage() == -1 ){mode=1;return ;}// エラー処理
					for (ii=0;ii<RIKISISUU;ii++){
						memset(aidata
							+ii*RIKISISUU*AIDATABYTESUU
							+i*AIDATABYTESUU, b10101010, sizeof(char) * AIDATABYTESUU); // ここを追加
						memset(aidata_tatiai
							+ii*RIKISISUU*AIDATATATIAIBYTESUU
							+i*AIDATATATIAIBYTESUU, b10101010, sizeof(char) * AIDATATATIAIBYTESUU); // ここを追加
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラー処理
					}

					//ver4.05beta010から初期値0はやめれるようにしてみた
					if (AIkotenagesukuinage_shokitizeroflag==1){
						////小手投げと掬い投げは初期値0に////
						temp_id1=i;
						for (temp_id2=0;temp_id2<RIKISISUU;temp_id2++){
						//if( ProcessMessage() == -1 ){mode=1;break ;}// エラーが発生したらループを抜ける
						for (i1=18;i1<22;i1++){//小手投げ掬い投げだけ
						for (i2=0;i2<5;i2++){
						for (i3=0;i3<2;i3++){
						for (i4=0;i4<2;i4++){
						for (i5=0;i5<2;i5++){
						for (i6=0;i6<2;i6++){
						for (i7=0;i7<4;i7++){
							temp_fichi=aidata_fichi[i1][i2][i3][i4][i5][i6][i7];
							if (temp_fichi!=-1){
								//////力士ごとデータ//////
								memcpy(&bytedata, 
									aidata
									+temp_id1*RIKISISUU*AIDATABYTESUU
									+temp_id2*AIDATABYTESUU
									+(int)(temp_fichi/4),
									sizeof(char));
								//値取り出し
								temp_char=getdatafrombit(bytedata,temp_fichi%4);
								//0にする
								temp_char=0;
								//値格納
								bytedata=setdatatobit(bytedata,temp_fichi%4,temp_char);
								memcpy(aidata
									+temp_id1*RIKISISUU*AIDATABYTESUU
									+temp_id2*AIDATABYTESUU
									+(int)(temp_fichi/4), 
									&bytedata,
									sizeof(char));
								//////力士ごとデータ//////
								memcpy(&bytedata, 
									aidata
									+temp_id2*RIKISISUU*AIDATABYTESUU
									+temp_id1*AIDATABYTESUU
									+(int)(temp_fichi/4),
									sizeof(char));
								//値取り出し
								temp_char=getdatafrombit(bytedata,temp_fichi%4);
								//0にする
								temp_char=0;
								//値格納
								bytedata=setdatatobit(bytedata,temp_fichi%4,temp_char);
								memcpy(aidata
									+temp_id2*RIKISISUU*AIDATABYTESUU
									+temp_id1*AIDATABYTESUU
									+(int)(temp_fichi/4), 
									&bytedata,
									sizeof(char));
							}
						}}}}}}}}
					}
					

				}}

				kobetu_sikiiti[i]=shokiti_kobetu_sikiiti;
				for (ii=0;ii<RIKISISUU;ii++){
					aikeikosuu[i][ii]=0;
					aikeikosuu[ii][i]=0;
				}

				////////////////////////////////////////////////////////////////////////////////

				//新弟子のお知らせ表示
//				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
//				game_main_backscreen();//基本ゲーム画面表示ルーチン
//				DrawFormatString(187,369,CRWHITE,"%s部屋に%sが",heyastring[rikisidata[i].heyaid],namestring[rikisidata[i].nameid]);
//				DrawString(187,369+16,"新弟子として入門しました。",CRWHITE);
//				draw_buttonF_mouse();
//				ScreenFlip() ;//裏画面を表画面にコピー
				// キー入力待ち(この一文を入れないとうまくいかないみたい)
				//while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				//	buttonG_mouse_change();
				//	Sleep(1);
				//}
				//while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				//	buttonG_mouse_change();
				//	Sleep(1);
				//}
				//while(1)
				//{
					//Sleep(1);
				//	if (get_mouseclick_buttonG() == 1){//メニューボタンGをクリックでループから抜け実際の取組へ
				//		break;
				//	}
				//	if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
				//		break;
				//	}
				//	// メッセージ処理
					//if( ProcessMessage() == -1 )
					//{
					//	mode=1;
					//	return ;	// エラーが起きたらループから抜ける
					//}
				//}
			
		}
	}

	if (scoutmoney>0 && siganshasuu_myheya==0){
		heyadata[myheyaid].hpoint+=scoutmoney;
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		game_main_backscreen();//基本ゲーム画面表示ルーチン
		DrawString(187,369,"残念ながらいい子は見つかりませんでした。",CRWHITE);
		DrawString(187,369+16,"スカウト費用を返還します。",CRWHITE);
		DrawString(187,369+48,"HIT　ANY　KEY",CRWHITE);
		ScreenFlip();
		WaitKey();
	}
	
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	game_main_backscreen();//基本ゲーム画面表示ルーチン
	DrawString(187,369,"もう少々お待ちを",CRWHITE);
	ScreenFlip();
if( ProcessMessage() == -1 ){mode=1;return;}


	//部屋ごとに所属力士数を数える
	for (i=0;i<HEYASUU;i++){
		shozokurikisisuu[i]=0;
	}
	for (i=0;i<HEYASUU;i++){
		for (ii=0;ii<RIKISISUU;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}
			if (rikisidata[ii].heyaid==i){
				shozokurikisisuu[i]++;
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

	//番付順ごとの力士ＩＤを検索
	for (ii=0;ii<RIKISISUU;ii++){//番付順位
		for (i=0;i<RIKISISUU;i++){//力士ＩＤ
			//if( ProcessMessage() == -1 ){mode=1;return ;}
			if (rikisidata[i].bandukejun==ii){
				bandukejunid[ii]=i;
				break;
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

	//部屋ごとの番付順力士IDを検索
	for (i=0;i<HEYASUU;i++){
		for (ii=0;ii<20;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}
			heyabandukejunid[i][ii]=-1;
		}
	}
	count=0;
	for (i=0;i<HEYASUU;i++){//部屋ID
		for (ii=0;ii<RIKISISUU;ii++){//番付順ID
			//if( ProcessMessage() == -1 ){mode=1;return ;}
			if (rikisidata[bandukejunid[ii]].heyaid==i){
				heyabandukejunid[i][count]=bandukejunid[ii];
				count++;
			}
		}
		count=0;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}


	//取組見る力士たちの番付順力士IDを検索
	count=0;
	for (i=0;i<RIKISISUU;i++){//
		if (rikisidata[bandukejunid[i]].torikumimiruflag==1){
			torimi_bandukejunid[count]=bandukejunid[i];
			count++;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	torimisuu=count;
	
	//輪廻させる力士たちの番付順力士IDを検索
	count=0;
	for (i=0;i<RIKISISUU;i++){//
		if (rikisidata[bandukejunid[i]].rinneflag==1){
			rinne_bandukejunid[count]=bandukejunid[i];
			count++;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	rinnesuu=count;


	//力士別対戦成績を表示する際（右リスト力士別選択時）の番付順IDを検索
	for (i=0;i<RIKISISUU;i++){//
		count=0;
		for (ii=0;ii<RIKISISUU;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}
			if (rikisidata[i].rikisibetu_wintotal[bandukejunid[ii]]>0 
			|| rikisidata[i].rikisibetu_losttotal[bandukejunid[ii]]>0){
				rikisibetu_bandukejunid[i][count]=bandukejunid[ii];
				count++;
			}
		}
		rikisibetusuu[i]=count;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//力士別選択ID初期化
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}
		rikisibetu_sentaku_id[i]=rikisibetu_bandukejunid[i][0];
	}
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//num,page初期化
	rikisisentaku_page=0;
	rikisisentaku_num=0;
	rikisisentaku_num_jiheya=0;
	torimi_rikisisentaku_num=0;
	torimi_rikisisentaku_page=0;
	rinne_rikisisentaku_num=0;
	rinne_rikisisentaku_page=0;
	bandukejun_or_jiheyaflag=0;
	rikisisentaku_id=bandukejunid[rikisisentaku_num+rikisisentaku_page*20];

	bandukejun_or_jiheyaflag=1;
	rikisisentaku_num_jiheya=0;
	rikisisentaku_id=heyabandukejunid[myheyaid][(rikisisentaku_num_jiheya+2)/2-1];



{////////理事選(理事長選)////////////////////////////////////////////
char kako_rijiflag[TOSIYORISUU];
for (i=0;i<TOSIYORISUU;i++){
	kako_rijiflag[i]=0;
	kako_rijiflag[i]=tosiyoridata[i].rijiflag;
}
if (year%2==1 && month==1){
	int temp_int=0;
	char rikkouhoflag[TOSIYORISUU];
	char rijitousenflag[TOSIYORISUU];
	int rijisenkakutokuhyousuu[TOSIYORISUU];
	int touhyousaki[TOSIYORISUU];
	int temp_suu[TOSIYORISUU];
	int jinbou_rand[TOSIYORISUU];
	int temp_suu_tokuhyousuu[TOSIYORISUU];
	int junbanid[TOSIYORISUU];
	int junbanid_tokuhyousuu[TOSIYORISUU];
	int junbanid_tokuhyousuu_rijichousen[TOSIYORISUU];
	int itimonbeturikkouhosuu[ITIMONSUU];
	int itimonbetutosiyorisuu[ITIMONSUU];
	int TEKISEIninzuu=0;//立候補者の適正人数
	int TEKISEIbunsi=0;//年寄数106を想定
	int count=0;
	int count_rikkouho=0;
	int loopsuu=0;
	char temp_namestring1[12];
	char temp_namestring2[12];
	char temp_namestring3[12];
	char temp_namestring4[12];
	char temp_namestring5[12];
	int temp_tuusanrikisiid=0;
	char itimonnusiflag[TOSIYORISUU];
	int itimonbetutousensuu[ITIMONSUU];
	char groupflag[TOSIYORISUU];//所属一門の一門主の現役時通算力士IDによって4の倍数とか2の倍数とかでグループ分け
	int rijichousenkakutokuhyousuu[TOSIYORISUU];
	int touhyousaki_rijichousen[TOSIYORISUU];
	//変数初期化
	for (i=0;i<TOSIYORISUU;i++){
		itimonnusiflag[i]=0;
		rikkouhoflag[i]=0;
		rijitousenflag[i]=0;
		rijisenkakutokuhyousuu[i]=0;
		touhyousaki[i]=0;
		temp_suu[i]=0;
		temp_suu_tokuhyousuu[i]=0;
		junbanid[i]=0;
		junbanid_tokuhyousuu[i]=0;
		junbanid_tokuhyousuu_rijichousen[i]=0;
		jinbou_rand[i]=0;
		groupflag[i]=0;
		rijichousenkakutokuhyousuu[i]=0;
		touhyousaki_rijichousen[i]=0;
	}
	for (i=0;i<ITIMONSUU;i++){
		itimonbeturikkouhosuu[i]=0;
		itimonbetutosiyorisuu[i]=0;
		itimonbetutousensuu[i]=0;
	}
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//一門別年寄数の確認
	for (i=0;i<ITIMONSUU;i++){
		for (ii=0;ii<TOSIYORISUU;ii++){
			if (tosiyoridata[ii].shozokuitimonid==i
			&& tosiyoridata[ii].shozokuheyaid!=-1){
				itimonbetutosiyorisuu[i]++;
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//一門主の確認
	for (i=0;i<ITIMONSUU;i++){
		for (ii=0;ii<TOSIYORISUU;ii++){
			if (tosiyoridata[ii].shozokuitimonid==i
			&& itimondata[i].shuheyaid==tosiyoridata[ii].shozokuheyaid
			&& tosiyoridata[ii].sishouflag==1
			&& tosiyoridata[ii].shozokuheyaid!=-1){
				itimonnusiflag[ii]=1;
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//一門を４つにグループ分け
	for (i=0;i<TOSIYORISUU;i++){
		if (itimonnusiflag[i]==1
		&& tosiyoridata[i].shozokuheyaid!=-1){
			groupflag[i]=GetRand(3);
		}
	}
	for (i=0;i<TOSIYORISUU;i++){
		for (ii=0;ii<TOSIYORISUU;ii++){
			if (tosiyoridata[i].shozokuitimonid==tosiyoridata[ii].shozokuitimonid
			&& itimonnusiflag[ii]==1
			&& tosiyoridata[i].shozokuheyaid!=-1){
				groupflag[i]=groupflag[ii];
				break;
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

	//立候補者の適正人数・適正分子決定
	TEKISEIninzuu=10;//0はダメ、適正分子より大きいのもダメ
	TEKISEIbunsi=106;
	loopsuu=0;
	while(1){
		//一門別に立候補数決定
		//(一門別年寄数/int(適正分子/適正人数))+GetRand(1)
		for (i=0;i<ITIMONSUU;i++){
			itimonbeturikkouhosuu[i]=(int)(itimonbetutosiyorisuu[i]/((int)(TEKISEIbunsi/TEKISEIninzuu)))+GetRand(1);
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//一門別に立候補者決定
		//GetRand((人望/1000)の自乗)の値をtemp_suuに代入
		for (i=0;i<TOSIYORISUU;i++){
			if (tosiyoridata[i].jinbou>0){
				//jinbou_rand[i]=GetRand((int)(tosiyoridata[i].jinbou/1000)*(int)(tosiyoridata[i].jinbou/1000));
				jinbou_rand[i]=tosiyoridata[i].jinbou;
				if (tosiyoridata[i].age<40){
					jinbou_rand[i]=(int)(jinbou_rand[i]/256);
				}else if (tosiyoridata[i].age<45){
					jinbou_rand[i]=(int)(jinbou_rand[i]/4);
				}else if (tosiyoridata[i].age<50){
					jinbou_rand[i]=(int)(jinbou_rand[i]/2);
				}else if (tosiyoridata[i].age>57){
					jinbou_rand[i]=(int)(jinbou_rand[i]/(256*(tosiyoridata[i].age-57)));
				}
			}else{
				jinbou_rand[i]=tosiyoridata[i].jinbou;
			}
			if (tosiyoridata[i].keishousha_rikisiid!=-1 || tosiyoridata[i].keishousha_tosiyoriid!=-1){
				jinbou_rand[i]-=9999999;
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//人望乱数の大きい順のIDをjunbanidに代入
		for (i=0;i<TOSIYORISUU;i++){
			junbanid[i]=i;
		}
		for (i=0;i<TOSIYORISUU;i++){
			temp_suu[i]=jinbou_rand[i];
		}
		for (i = 0;i < TOSIYORISUU - 1;i++) {
			for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
				if (temp_suu[ii + 1] > temp_suu[ii]) {
					temp_int = temp_suu[ii];
					temp_suu[ii] = temp_suu[ii + 1];
					temp_suu[ii + 1] = temp_int;
					temp_int = junbanid[ii];
					junbanid[ii] = junbanid[ii+1];
					junbanid[ii+1] = temp_int;
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return;}
		}
		//一門ごとに立候補者確定処理
		//条件 部屋の師匠、借株でない、期間限定一代ではない
		for (i=0;i<TOSIYORISUU;i++){
			rikkouhoflag[i]=0;
		}
		/*//一門主優先
		for (i=0;i<ITIMONSUU;i++){
			if (itimonbeturikkouhosuu[i]>0){
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (tosiyoridata[ii].shozokuitimonid==i
					&& itimonnusiflag[ii]==1){
						//if (tosiyoridata[ii].age<=63
						if (tosiyoridata[ii].sishouflag==1
						&& tosiyoridata[ii].keishousha_rikisiid==-1
						&& tosiyoridata[ii].keishousha_tosiyoriid==-1
						&& tosiyoridata[ii].category!=5
						&& tosiyoridata[ii].category!=6
						&& tosiyoridata[ii].shozokuheyaid!=-1
						){
							rikkouhoflag[ii]=1;
							break;
						}
					}
					if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
		}*/
		//
		for (i=0;i<ITIMONSUU;i++){
			count=0;
			for (ii=0;ii<TOSIYORISUU;ii++){
				if (rikkouhoflag[ii]==1
				&& tosiyoridata[ii].shozokuitimonid==i
				){
					count++;
				}
			}
			for (ii=0;ii<TOSIYORISUU;ii++){
				if (count>=itimonbeturikkouhosuu[i]){
					break;
				}
				if (tosiyoridata[junbanid[ii]].shozokuitimonid==i
				&& rikkouhoflag[junbanid[ii]]!=1
				){
					//if (tosiyoridata[junbanid[ii]].age<=63
					if (tosiyoridata[junbanid[ii]].sishouflag==1
					//&& tosiyoridata[junbanid[ii]].keishousha_rikisiid==-1
					//&& tosiyoridata[junbanid[ii]].keishousha_tosiyoriid==-1
					&& tosiyoridata[junbanid[ii]].category!=5
					&& tosiyoridata[junbanid[ii]].category!=6
					&& tosiyoridata[junbanid[ii]].shozokuheyaid!=-1
					){
						rikkouhoflag[junbanid[ii]]=1;
						count++;
					}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
		}
		//立候補者数が10人未満なら最初に戻って一門別立候補数決定から再度行う
		count=0;
		for (i=0;i<TOSIYORISUU;i++){
			if (rikkouhoflag[i]==1){
				count++;
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (count>=10){
			break;
		}
		TEKISEIninzuu+=(int)(loopsuu/10);
		if (loopsuu>1000){//無限ループ回避
			break;
		}
		loopsuu++;
	}
	//各年寄ごとに投票先を決定
		//-1にしておく
		for (i=0;i<TOSIYORISUU;i++){
			touhyousaki[i]=-1;
			rijisenkakutokuhyousuu[i]=0;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//優先順位 所属部屋の師匠が候補者なら確定
		for (i=0;i<TOSIYORISUU;i++){
			if (touhyousaki[i]==-1 
			&& tosiyoridata[i].shozokuheyaid!=-1
			){
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (tosiyoridata[i].shozokuheyaid==tosiyoridata[junbanid[ii]].shozokuheyaid){
						if (rikkouhoflag[junbanid[ii]]==1){
							touhyousaki[i]=junbanid[ii];
							rijisenkakutokuhyousuu[junbanid[ii]]++;
							break;
						}
					}
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		//優先順位 同じ一門に候補者がいれば
		for (i=0;i<TOSIYORISUU;i++){
			if (touhyousaki[i]==-1 
			&& tosiyoridata[i].shozokuheyaid!=-1
			){
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (tosiyoridata[i].shozokuitimonid==tosiyoridata[junbanid[ii]].shozokuitimonid){
						if (rikkouhoflag[junbanid[ii]]==1){
							if (rijisenkakutokuhyousuu[junbanid[ii]]<=(int)(itimonbetutosiyorisuu[tosiyoridata[i].shozokuitimonid]/itimonbeturikkouhosuu[tosiyoridata[i].shozokuitimonid]) ){
								touhyousaki[i]=junbanid[ii];
								rijisenkakutokuhyousuu[junbanid[ii]]++;
								break;
							}
						}
					}
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		//優先順位 一門外ならグループ分けも使いランダム
		for (i=0;i<TOSIYORISUU;i++){
			if (touhyousaki[i]==-1 
			&& tosiyoridata[i].shozokuheyaid!=-1
			){
				loopsuu=0;
				while(1){
					temp_int=GetRand(TOSIYORISUU-1);
					if (rikkouhoflag[temp_int]==1
					&& groupflag[i]==groupflag[temp_int]
					){
						touhyousaki[i]=temp_int;
						rijisenkakutokuhyousuu[temp_int]++;
						break;
					}
					if (loopsuu>10000){
						break;
					}
					loopsuu++;
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
		}
		//優先順位 一門外ならグループ分け使わずランダム
		for (i=0;i<TOSIYORISUU;i++){
			if (touhyousaki[i]==-1 
			&& tosiyoridata[i].shozokuheyaid!=-1
			){
				loopsuu=0;
				while(1){
					temp_int=GetRand(TOSIYORISUU-1);
					if (rikkouhoflag[temp_int]==1
					//&& groupflag[i]==groupflag[temp_int]
					){
						touhyousaki[i]=temp_int;
						rijisenkakutokuhyousuu[temp_int]++;
						break;
					}
					if (loopsuu>10000){
						break;
					}
					loopsuu++;
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}
		}

	//投票数集計
		//投票数集計
		for (i=0;i<TOSIYORISUU;i++){
			rijisenkakutokuhyousuu[i]=0;
			if (rikkouhoflag[i]==1){
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (touhyousaki[ii]==i){
						rijisenkakutokuhyousuu[i]++;
					}
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		//順番並び替え(10人目が同点の場合話し合いってことにしちゃえ)
		for (i=0;i<TOSIYORISUU;i++){
			junbanid_tokuhyousuu[i]=junbanid[i];
		}
		for (i=0;i<TOSIYORISUU;i++){
			temp_suu_tokuhyousuu[i]=rijisenkakutokuhyousuu[junbanid[i]];
		}
		//if( ProcessMessage() == -1 ){mode=1;return;}
		for (i = 0;i < TOSIYORISUU - 1;i++) {
			for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
				if (temp_suu_tokuhyousuu[ii + 1] > temp_suu_tokuhyousuu[ii]) {
					temp_int = temp_suu_tokuhyousuu[ii];
					temp_suu_tokuhyousuu[ii] = temp_suu_tokuhyousuu[ii + 1];
					temp_suu_tokuhyousuu[ii + 1] = temp_int;
					temp_int = junbanid_tokuhyousuu[ii];
					junbanid_tokuhyousuu[ii] = junbanid_tokuhyousuu[ii+1];
					junbanid_tokuhyousuu[ii+1] = temp_int;
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return;}
		}
		//rijitousenflagへ代入
		for (i=0;i<TOSIYORISUU;i++){
			rijitousenflag[i]=0;
		}
		if( ProcessMessage() == -1 ){mode=1;return;}
		count=0;
		for (i=0;i<TOSIYORISUU;i++){
			if (count<10
			&& tosiyoridata[junbanid_tokuhyousuu[i]].shozokuheyaid!=-1
			){
				rijitousenflag[junbanid_tokuhyousuu[i]]=1;
				count++;
			}
		}
		if( ProcessMessage() == -1 ){mode=1;return;}
		//一門別当選数
		for (i=0;i<TOSIYORISUU;i++){
			if (rijitousenflag[i]==1){
				itimonbetutousensuu[tosiyoridata[i].shozokuitimonid]++;
			}
		}
		if( ProcessMessage() == -1 ){mode=1;return;}
	//理事当選表示、ファイル記録

////////debug/////
strcpy(temp_filename,"debug_rijisen.csv");
fpcsv = fopen(temp_filename,"w");
fprintf(fpcsv,"一門ID,一門名,年寄数,立候補数,当選数\n");
for (i=0;i<ITIMONSUU;i++){
	if (itimondata[i].shuheyaid!=-1){
		for (ii=0;ii<TOSIYORISUU;ii++){
			if (tosiyoridata[ii].shozokuitimonid==i
			&& tosiyoridata[ii].shozokuheyaid!=-1
			){
				temp_int=(int)(groupflag[ii]);
			}
		}
		fprintf(fpcsv,"%d,%s,%d,%d,%d\n",
		i,
		itimondata[i].namestring,
		//temp_int,
		itimonbetutosiyorisuu[i],
		itimonbeturikkouhosuu[i],
		itimonbetutousensuu[i]);
	}
}
fclose(fpcsv);
if( ProcessMessage() == -1 ){mode=1;return;}
/////////////////////////////////////////////

	//理事長選
		//-1にしておく
		for (i=0;i<TOSIYORISUU;i++){
			touhyousaki_rijichousen[i]=-1;
			rijichousenkakutokuhyousuu[i]=0;
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//偶数・奇数グループ内の人望乱数一位に票集め
		for (i=0;i<TOSIYORISUU;i++){
			if (rijitousenflag[i]==1
			&& tosiyoridata[i].shozokuheyaid!=-1
			&& touhyousaki_rijichousen[i]==-1
			){
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (rijitousenflag[junbanid[ii]]==1
					&& tosiyoridata[junbanid[ii]].shozokuheyaid!=-1
					&& groupflag[i]%2==groupflag[junbanid[ii]]%2
					){
						touhyousaki_rijichousen[i]=junbanid[ii];
						break;
					}
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		//集計
		for (i=0;i<TOSIYORISUU;i++){
			if (touhyousaki_rijichousen[i]!=-1){
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (touhyousaki_rijichousen[i]==ii){
						rijichousenkakutokuhyousuu[ii]++;
						break;
					}
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		//順番並び替え(同点の場合話し合いってことにしちゃえ)
		for (i=0;i<TOSIYORISUU;i++){
			junbanid_tokuhyousuu_rijichousen[i]=junbanid[i];
		}
		for (i=0;i<TOSIYORISUU;i++){
			temp_suu_tokuhyousuu[i]=rijichousenkakutokuhyousuu[junbanid[i]];
		}
		if( ProcessMessage() == -1 ){mode=1;return;}
		for (i = 0;i < TOSIYORISUU - 1;i++) {
			for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
				if (temp_suu_tokuhyousuu[ii + 1] > temp_suu_tokuhyousuu[ii]) {
					temp_int = temp_suu_tokuhyousuu[ii];
					temp_suu_tokuhyousuu[ii] = temp_suu_tokuhyousuu[ii + 1];
					temp_suu_tokuhyousuu[ii + 1] = temp_int;
					temp_int = junbanid_tokuhyousuu_rijichousen[ii];
					junbanid_tokuhyousuu_rijichousen[ii] = junbanid_tokuhyousuu_rijichousen[ii+1];
					junbanid_tokuhyousuu_rijichousen[ii+1] = temp_int;
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return;}
		}
	//理事フラグ初期化
	for (i=0;i<TOSIYORISUU;i++){
		tosiyoridata[i].rijiflag&=0xf0;//下位4ビットのみ0で初期化
	}
	//理事確定処理(理事フラグへ代入)
	count=0;
	for (i=0;i<TOSIYORISUU;i++){
		if (rijitousenflag[junbanid_tokuhyousuu_rijichousen[i]]==1){
			tosiyoridata[junbanid_tokuhyousuu_rijichousen[i]].rijiflag|=(count+1);//下位4ビットにのみ代入
			count++;
		}
	}
	if( ProcessMessage() == -1 ){mode=1;return;}

	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString(0,369,"理事選挙が行われます",CRWHITE);
		DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();

		for (i=0;i<ITIMONSUU;i++){
			if (itimondata[i].shuheyaid!=-1
			&& itimonbeturikkouhosuu[i]==0
			){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawFormatString(0,369,CRWHITE,"%s一門は候補者の擁立を見送ったようです",
				itimondata[i].namestring);
				DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
			}
		}
		count_rikkouho=0;
		for (i=0;i<TOSIYORISUU;i++){
			if (rikkouhoflag[i]==1){
				count_rikkouho++;
			}
		}
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 200 , 464 , "Hit any key" , CRWHITE);
		if (count_rikkouho<=10){
			DrawString(0,0,"立候補者が10人以下なので無投票で理事が決定しました",CRWHITE);
		}else{
			DrawString(0,0,"理事選挙結果",CRWHITE);
		}
		DrawString( 0 , 40 , "一門名　所属年寄数　立候補数　当選数" , CRWHITE);
		for (i=0;i<ITIMONSUU;i++){
			if (itimondata[i].shuheyaid!=-1){
				DrawFormatString(0,80+i*25,CRWHITE,"%s",itimondata[i].namestring);
				DrawFormatString(100,80+i*25,CRWHITE,"%2d",itimonbetutosiyorisuu[i]);
				DrawFormatString(200,80+i*25,CRWHITE,"%2d",itimonbeturikkouhosuu[i]);
				DrawFormatString(300,80+i*25,CRWHITE,"%2d",itimonbetutousensuu[i]);
			}
		}
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();

		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString(0,0,"理事選結果",CRWHITE);
		if (rijisenkakutokuhyousuu[junbanid_tokuhyousuu[9]]==rijisenkakutokuhyousuu[junbanid_tokuhyousuu[10]]){
			DrawString( 100 , 444 , "10位は同点でしたが話し合いで決定しました" , CRWHITE);
		}
		DrawString( 200 , 464 , "Hit any key" , CRWHITE);
		count=0;
		for (ii=0;ii<ITIMONSUU;ii++){
			if (itimonbeturikkouhosuu[ii]>0){
				for (i=0;i<TOSIYORISUU;i++){
					if (rikkouhoflag[i]==1){
						if (tosiyoridata[i].shozokuitimonid==ii
						&& tosiyoridata[i].shozokuheyaid!=-1
						){
							if ((tosiyoridata[i].rijiflag&0x0f)>0 && (tosiyoridata[i].rijiflag&0x0f)<11){
								DrawString(0,60+25*count,"当",CRRED);
							}
							if (count_rikkouho>10){
								DrawFormatString(20,60+25*count,CRWHITE,"%s一門%s部屋 %s(元%s %d才) 獲得票数%2d",
								itimondata[tosiyoridata[i].shozokuitimonid].namestring,
								heyastring[tosiyoridata[i].shozokuheyaid],
								tosiyoridata[i].namestring,
								tosiyoridata[i].sikona,
								tosiyoridata[i].age,
								rijisenkakutokuhyousuu[i]);
							}else{
								DrawFormatString(20,60+25*count,CRWHITE,"%s一門%s部屋 %s(元%s %d才)",
								itimondata[tosiyoridata[i].shozokuitimonid].namestring,
								heyastring[tosiyoridata[i].shozokuheyaid],
								tosiyoridata[i].namestring,
								tosiyoridata[i].sikona,
								tosiyoridata[i].age);
							}
							count++;
						}
					}
				}
			}
		}
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();

		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString(0,369,"続いて選出された理事により理事長選挙が行われます",CRWHITE);
		DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();

		for (i=0;i<TOSIYORISUU;i++){
			if (tosiyoridata[i].shozokuheyaid!=-1
			&& rijichousenkakutokuhyousuu[i]>0
			){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawFormatString(0,369,CRWHITE,"%s一門%s部屋の%s(元%s %d才)が多数派工作を行っています",
				itimondata[tosiyoridata[i].shozokuitimonid].namestring,
				heyastring[tosiyoridata[i].shozokuheyaid],
				tosiyoridata[i].namestring,
				tosiyoridata[i].sikona,
				tosiyoridata[i].age);
				DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
			}
		}

		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString(0,0,"理事長選結果",CRWHITE);
		if (rijichousenkakutokuhyousuu[junbanid_tokuhyousuu_rijichousen[0]]==rijichousenkakutokuhyousuu[junbanid_tokuhyousuu_rijichousen[1]]){
			DrawString( 100 , 444 , "同点でしたが話し合いで決定しました" , CRWHITE);
		}
		DrawString( 200 , 464 , "Hit any key" , CRWHITE);
		count=0;
		for (ii=0;ii<ITIMONSUU;ii++){
			if (itimonbeturikkouhosuu[ii]>0){
				for (i=0;i<TOSIYORISUU;i++){
					if ((tosiyoridata[i].rijiflag&0x0f)>0 && (tosiyoridata[i].rijiflag&0x0f)<11){
						if (tosiyoridata[i].shozokuitimonid==ii
						&& tosiyoridata[i].shozokuheyaid!=-1
						){
							if ((tosiyoridata[i].rijiflag&0x0f)==1){
								DrawString(0,60+25*count,"当",CRRED);
							}
							DrawFormatString(20,60+25*count,CRWHITE,"%s一門%s部屋 %s(元%s %d才) 獲得票数%2d 　　投票先→%s",
							itimondata[tosiyoridata[i].shozokuitimonid].namestring,
							heyastring[tosiyoridata[i].shozokuheyaid],
							tosiyoridata[i].namestring,
							tosiyoridata[i].sikona,
							tosiyoridata[i].age,
							rijichousenkakutokuhyousuu[i],
							tosiyoridata[touhyousaki_rijichousen[i]].namestring);
							count++;
						}
					}
				}
			}
		}
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();

		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString(0,0,"理事一覧",CRWHITE);
		DrawString( 200 , 464 , "Hit any key" , CRWHITE);
		count=0;
		for (ii=0;ii<10;ii++){
			for (i=0;i<TOSIYORISUU;i++){
				if ((tosiyoridata[i].rijiflag&0x0f)==ii+1){
					if (tosiyoridata[i].shozokuheyaid!=-1
					){
						DrawFormatString(0,60+25*count,CRWHITE,"%s %s一門%s部屋 %s(元%s %d才)",
						namestring_riji[(tosiyoridata[i].rijiflag&0x0f)-1],
						itimondata[tosiyoridata[i].shozokuitimonid].namestring,
						heyastring[tosiyoridata[i].shozokuheyaid],
						tosiyoridata[i].namestring,
						tosiyoridata[i].sikona,
						tosiyoridata[i].age);
						count++;
					}
					break;
				}
			}
		}
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();

	}/////表示部分終わり



////////debug/////
if( ProcessMessage() == -1 ){mode=1;return;}
strcpy(temp_filename,"debug_rijichousen.csv");
fpcsv = fopen(temp_filename,"w");
	//書き込み準備
	for (i=0;i<12;i++){
		temp_namestring1[i]=0;
		temp_namestring2[i]=0;
		temp_namestring3[i]=0;
		temp_namestring4[i]=0;
		temp_namestring5[i]=0;
	}
	//ここから書き込み
	fprintf(fpcsv,"年寄ID,年寄名,年,月,年齢,カテ,就任年,部屋ID,部屋名,一門ID,一門名,現役時通算力士ID,現役時四股名,師匠フラグ,人望,理事フラグ,継承者通算力士ID,継承予定力士,継承者年寄ID,継承予定年寄,選挙人望,立候補フラグ,当選フラグ,得票数,理事選投票先,理事長選得票数,理事長選投票先\n");
	for (i=0;i<TOSIYORISUU;i++){//
		if (tosiyoridata[i].keishousha_rikisiid!=-1 && tosiyoridata[i].sishouflag==1){
			strcpy(temp_namestring1,"指");
		}else if(tosiyoridata[i].keishousha_rikisiid!=-1 && tosiyoridata[i].sishouflag!=1){
			strcpy(temp_namestring1,"借");
		}else{
			if (tosiyoridata[i].category==1){
				strcpy(temp_namestring1,"A");
			}else if (tosiyoridata[i].category==2){
				strcpy(temp_namestring1,"B");
			}else if (tosiyoridata[i].category==3){
				strcpy(temp_namestring1,"C");
			}else if (tosiyoridata[i].category==4){
				strcpy(temp_namestring1,"一");
			}else if (tosiyoridata[i].category>=5){
				strcpy(temp_namestring1,"期");
			}else{
				strcpy(temp_namestring1,"\0");
			}
		}
		if (tosiyoridata[i].shozokuheyaid>=0 && tosiyoridata[i].shozokuheyaid<HEYASUU){
			strcpy(temp_namestring2,heyastring[tosiyoridata[i].shozokuheyaid]);
		}else{
			strcpy(temp_namestring2,"\0");
		}
		if (tosiyoridata[i].shozokuitimonid>=0 && tosiyoridata[i].shozokuitimonid<ITIMONSUU){
			strcpy(temp_namestring3,itimondata[tosiyoridata[i].shozokuitimonid].namestring);
		}else{
			strcpy(temp_namestring3,"\0");
		}
		if (tosiyoridata[i].keishousha_rikisiid>=0 && tosiyoridata[i].keishousha_rikisiid<RIKISISUU){
			strcpy(temp_namestring4,namestring[tosiyoridata[i].keishousha_rikisiid]);
			temp_tuusanrikisiid=rikisidata[tosiyoridata[i].keishousha_rikisiid].rikisiid;
		}else{
			strcpy(temp_namestring4,"\0");
			temp_tuusanrikisiid=tosiyoridata[i].keishousha_rikisiid;
		}
		if (tosiyoridata[i].keishousha_tosiyoriid>=0 && tosiyoridata[i].keishousha_tosiyoriid<TOSIYORISUU){
			strcpy(temp_namestring5,tosiyoridata[tosiyoridata[i].keishousha_tosiyoriid].namestring);
		}else{
			strcpy(temp_namestring5,"\0");
		}

		fprintf(fpcsv,"%d,%s,%d,%d,%d,%s,%d,%d,%s,%d,%s,%d,%s,%d,%d,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d,%d,%d\n",
		i,//年寄ID
		tosiyoridata[i].namestring,//年寄名跡名
		year,
		month,
		tosiyoridata[i].age,
		temp_namestring1,//1Ａカテ、2Ｂカテ、3Ｃカテ、4一代年寄、5期間限定一代年寄（横綱）、6期間限定一代年寄（大関）
		tosiyoridata[i].startyear,//就任年（期間限定一代年寄用）
		tosiyoridata[i].shozokuheyaid,//0～53所属部屋ＩＤ、-1空名跡、-2一代年寄が重複取得している名跡の場合、-3現役力士が取得（後継者を予定）
		temp_namestring2,
		tosiyoridata[i].shozokuitimonid,//0～53所属一門ＩＤ、-1空名跡、-2一代年寄が重複取得している名跡の場合、-3現役力士が取得（後継者を予定）
		temp_namestring3,
		tosiyoridata[i].rikisiid,//現役時の通算力士ＩＤ
		tosiyoridata[i].sikona,//現役時四股名
		tosiyoridata[i].sishouflag,//師匠の場合は1
		tosiyoridata[i].jinbou,//人望、理事選挙に影響
		tosiyoridata[i].rijiflag,//0平、1理事長など
		//tosiyoridata[i].keishousha_rikisiid,//継承者指名の力士ＩＤ（0～707であって通算力士ＩＤではない）、-1は未指名
		temp_tuusanrikisiid,
		temp_namestring4,
		tosiyoridata[i].keishousha_tosiyoriid,//継承者指名の年寄ＩＤ（一代年寄の200番台を予定)、-1は未指名
		temp_namestring5,
		jinbou_rand[i],
		rikkouhoflag[i],
		rijitousenflag[i],
		rijisenkakutokuhyousuu[i],
		touhyousaki[i],
		//groupflag[i],
		rijichousenkakutokuhyousuu[i],
		touhyousaki_rijichousen[i]);
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
fclose(fpcsv);
if( ProcessMessage() == -1 ){mode=1;return ;}

	//副理事決定（手抜きで選挙なし）・役員待遇委員決定
	{
		int itimonbeturijiritu[ITIMONSUU];
		int rijiritujun_itimonid[ITIMONSUU];
		int temp_narabekaeyou[TOSIYORISUU];
		int temp_itimonid=0;
		int fukurijisuu=0;

		for (i=0;i<ITIMONSUU;i++){
			itimonbeturijiritu[i]=0;
			itimonbeturijiritu[i]=-99999;
			rijiritujun_itimonid[i]=0;
		}
		for (i=0;i<ITIMONSUU;i++){
			if (itimonbetutosiyorisuu[i]>0){
				itimonbeturijiritu[i]=(int)(itimonbetutousensuu[i]*10000/itimonbetutosiyorisuu[i]);
			}
		}
		//一門別理事率のソート
		//バブルソート
		for (iii=0;iii<ITIMONSUU;iii++){
			temp_narabekaeyou[iii]=0;
			temp_narabekaeyou[iii]=itimonbeturijiritu[iii];
			rijiritujun_itimonid[iii]=0;
			rijiritujun_itimonid[iii]=iii;
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		for (iii = 0;iii < ITIMONSUU - 1;iii++) {
			for (ii = 0;ii < ITIMONSUU - 1;ii++) {
				if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
					temp_itimonid = temp_narabekaeyou[ii];
					temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
					temp_narabekaeyou[ii + 1] = temp_itimonid;
					temp_itimonid = rijiritujun_itimonid[ii];
					rijiritujun_itimonid[ii] = rijiritujun_itimonid[ii+1];
					rijiritujun_itimonid[ii+1] = temp_itimonid;
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
		}
		//人望順年寄IDを検索
		//バブルソート
		for (i=0;i<TOSIYORISUU;i++){
			temp_narabekaeyou[i]=0;
			temp_narabekaeyou[i]=tosiyoridata[i].jinbou;
			jinboujun_tosiyoriid[i]=0;
			jinboujun_tosiyoriid[i]=i;
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		for (i = 0;i < TOSIYORISUU - 1;i++) {
			for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
				if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
					temp_tosiyoriid = temp_narabekaeyou[ii];
					temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
					temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
					temp_tosiyoriid = jinboujun_tosiyoriid[ii];
					jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
					jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
		}
		//ここで副理事決定（まずは年寄数3人以上の一門のなかから理事率の低い順で、決まらなければ2人以上、1人の順で）
		fukurijisuu=0;
		//委員以上から
		for (iii=3;iii>=1;iii--){
			for (i=ITIMONSUU-1;i>=0;i--){
				if (itimonbetutosiyorisuu[rijiritujun_itimonid[i]]>=iii){
					for (ii=0;ii<TOSIYORISUU;ii++){
						if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuitimonid==rijiritujun_itimonid[i] 
							&& tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
							&& ((tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)>11) 
							&& tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 
							&& tosiyoridata[jinboujun_tosiyoriid[ii]].age<=58
							&& ((kako_rijiflag[jinboujun_tosiyoriid[ii]]&0x0f)<=13 && (kako_rijiflag[jinboujun_tosiyoriid[ii]]&0x0f)>0)
						){
							tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|=11;//副理事
							fukurijisuu++;
							break;
						}
						if (fukurijisuu>=3){break;}
					}
					if (fukurijisuu>=3){break;}
				}
			}
			if (fukurijisuu>=3){break;}
		}
		if (fukurijisuu<3){
			//委員以上からで決まらなければ主任以上から
			for (iii=3;iii>=1;iii--){
				for (i=ITIMONSUU-1;i>=0;i--){
					if (itimonbetutosiyorisuu[rijiritujun_itimonid[i]]>=iii){
						for (ii=0;ii<TOSIYORISUU;ii++){
							if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuitimonid==rijiritujun_itimonid[i] 
								&& tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
								&& ((tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)>11) 
								&& tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 
								&& tosiyoridata[jinboujun_tosiyoriid[ii]].age<=58
								&& ((kako_rijiflag[jinboujun_tosiyoriid[ii]]&0x0f)<=14 && (kako_rijiflag[jinboujun_tosiyoriid[ii]]&0x0f)>0)
							){
								tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|=11;//副理事
								fukurijisuu++;
								break;
							}
							if (fukurijisuu>=3){break;}
						}
						if (fukurijisuu>=3){break;}
					}
				}
				if (fukurijisuu>=3){break;}
			}
		}
		if (fukurijisuu<3){
			//主任以上からで決まらなければ借株でない年寄以上から
			for (iii=3;iii>=1;iii--){
				for (i=ITIMONSUU-1;i>=0;i--){
					if (itimonbetutosiyorisuu[rijiritujun_itimonid[i]]>=iii){
						for (ii=0;ii<TOSIYORISUU;ii++){
							if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuitimonid==rijiritujun_itimonid[i] 
								&& tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
								&& ((tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)>11) 
								&& tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 
								&& tosiyoridata[jinboujun_tosiyoriid[ii]].age<=58
							){
								tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|=11;//副理事
								fukurijisuu++;
								break;
							}
							if (fukurijisuu>=3){break;}
						}
						if (fukurijisuu>=3){break;}
					}
				}
				if (fukurijisuu>=3){break;}
			}
		}

		if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString(0,0,"副理事一覧",CRWHITE);
//DrawFormatString(300,0,CRWHITE,"副理事数　%d人",fukurijisuu);
			DrawString( 200 , 464 , "Hit any key" , CRWHITE);
			count=0;
			for (i=0;i<TOSIYORISUU;i++){
				if ((tosiyoridata[jinboujun_tosiyoriid[i]].rijiflag&0x0f)==11){
					if (tosiyoridata[jinboujun_tosiyoriid[i]].shozokuheyaid!=-1
					){
						DrawFormatString(0,60+25*count,CRWHITE,"副理事 %s一門%s部屋 %s(元%s %d才)",
						itimondata[tosiyoridata[jinboujun_tosiyoriid[i]].shozokuitimonid].namestring,
						heyastring[tosiyoridata[jinboujun_tosiyoriid[i]].shozokuheyaid],
						tosiyoridata[jinboujun_tosiyoriid[i]].namestring,
						tosiyoridata[jinboujun_tosiyoriid[i]].sikona,
						tosiyoridata[jinboujun_tosiyoriid[i]].age);
						count++;
					}
				}
			}
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();

		}/////表示部分終わり

	}//副理事決定終わり

}//奇数年初場所のみ開催するようにするif文の最後

if (month==1){
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここから委員以下決定処理\n",year,month);
fclose(fpdebug);
*/
	//理事・副理事以外の理事フラグ初期化
	for (i=0;i<TOSIYORISUU;i++){
		if ((tosiyoridata[i].rijiflag&0x0f)>11){
			tosiyoridata[i].rijiflag&=0xf0;//下位4ビットのみ初期化
		}
	}
	//人望順年寄IDを検索
	//バブルソート
	for (i=0;i<TOSIYORISUU;i++){
		temp_narabekaeyou[i]=0;
		temp_narabekaeyou[i]=tosiyoridata[i].jinbou;
		jinboujun_tosiyoriid[i]=0;
		jinboujun_tosiyoriid[i]=i;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (i = 0;i < TOSIYORISUU - 1;i++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] > temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}
	//まず役員待遇委員決定
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここから役員待遇委員決定\n",year,month);
fclose(fpdebug);
*/
	for (ii=0;ii<TOSIYORISUU;ii++){
		if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
			&& ((tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)>12) 
			&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
			&& tosiyoridata[jinboujun_tosiyoriid[ii]].age>=59 
			&& tosiyoridata[jinboujun_tosiyoriid[ii]].jinbou>=10000
			&& ( (kako_rijiflag[jinboujun_tosiyoriid[ii]]&0x0f)>=1 && (kako_rijiflag[jinboujun_tosiyoriid[ii]]&0x0f)<=13 )
		){
			tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|=12;//役員待遇委員
		}
	}
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//委員決定
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここから委員決定\n",year,month);
fclose(fpdebug);
*/
	for (ii=0;ii<TOSIYORISUU;ii++){
		if (tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid>=0){
			if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
				&& ((tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)>13) 
				&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
				&& ( (kako_rijiflag[jinboujun_tosiyoriid[ii]]&0x0f)>=1 && (kako_rijiflag[jinboujun_tosiyoriid[ii]]&0x0f)<=14 )
			){
				retirerikisidata_rikisiid(tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid);
				//retirerikisidata_rikisiid(x)によって以下の3つのsub_retirenew内のグローバル変数に値がセットされる
				//int retirerikisidata_retireage;
				//int retirerikisidata_jikosaikoubandukenameid;
				//int retirerikisidata_jikosaikoubandukesuuji;
				if ( ( (tosiyoridata[jinboujun_tosiyoriid[ii]].age-retirerikisidata_retireage) >= 7 
						|| ( (tosiyoridata[jinboujun_tosiyoriid[ii]].age-retirerikisidata_retireage) >=5 && retirerikisidata_jikosaikoubandukenameid<=1) )
				){
					tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|=13;//委員
				}
			}
		}else{
			if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
				&& ((tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)>13) 
				&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
				&& ( tosiyoridata[jinboujun_tosiyoriid[ii]].age >= 45 
					|| ( tosiyoridata[jinboujun_tosiyoriid[ii]].age >= 43 && (tosiyoridata[jinboujun_tosiyoriid[ii]].category==1 || tosiyoridata[jinboujun_tosiyoriid[ii]].category>=4) ) )
				&& ( (kako_rijiflag[jinboujun_tosiyoriid[ii]]&0x0f)>=1 && (kako_rijiflag[jinboujun_tosiyoriid[ii]]&0x0f)<=14 )
			){
				tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|=13;//委員
			}
		}
	}
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//以前副理事以上でここまで役職未決定は委員に
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここから以前副理事以上でここまで役職未決定は委員に処理\n",year,month);
fclose(fpdebug);
*/
	for (ii=0;ii<TOSIYORISUU;ii++){
		if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
			&& ((tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)>13) 
			&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
			&& ((kako_rijiflag[jinboujun_tosiyoriid[ii]]&0x0f)<=11 && (kako_rijiflag[jinboujun_tosiyoriid[ii]]&0x0f)>0)
		){
			tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|=13;//委員
		}
	}
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//主任決定
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここから主任決定処理\n",year,month);
fclose(fpdebug);
*/
	for (ii=0;ii<TOSIYORISUU;ii++){
		if (tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid>=0){
			if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
				&& ((tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)>13) 
				&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
			){
				retirerikisidata_rikisiid(tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid);
				//retirerikisidata_rikisiid(x)によって以下の3つのsub_retirenew内のグローバル変数に値がセットされる
				//int retirerikisidata_retireage;
				//int retirerikisidata_jikosaikoubandukenameid;
				//int retirerikisidata_jikosaikoubandukesuuji;
				if ( (tosiyoridata[jinboujun_tosiyoriid[ii]].age-retirerikisidata_retireage)>=4 
				){
					tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|=14;//主任
				}
			}
		}else{
			if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
				&& ((tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)>13) 
				&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
				&& tosiyoridata[jinboujun_tosiyoriid[ii]].age >= 42 
			){
				tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|=14;//主任
			}

		}
	}
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//残りは平年寄

	//ここから審判部配属親方(審判委員)決定
	//一門別割り当て数=20*(当一門理事数/親方総数)
	{
		char suu_iin_yokoduna=0;
		char suu_iin_oozeki=0;
		char suu_iin_sekiwake=0;
		char suu_iin_komusubi=0;
		char suu_iin_maegasira=0;
		char suu_shunin_yokoduna=0;
		char suu_shunin_oozeki=0;
		char suu_shunin_sekiwake=0;
		char suu_shunin_komusubi=0;
		char suu_shunin_maegasira=0;
		char suu_hira_yokoduna=0;
		char suu_hira_oozeki=0;
		char suu_hira_sekiwake=0;
		char suu_hira_komusubi=0;
		char suu_hira_maegasira=0;

		char max_maisuu_maegasira=2;
		char max_iin_yokoduna=20;
		char max_iin_oozeki=20;
		char max_iin_sekiwake=20;
		char max_iin_komusubi=20;
		char max_iin_maegasira=20;
		char max_shunin_yokoduna=20;
		char max_shunin_oozeki=20;
		char max_shunin_sekiwake=20;
		char max_shunin_komusubi=20;
		char max_shunin_maegasira=20;
		char max_hira_yokoduna=20;
		char max_hira_oozeki=20;
		char max_hira_sekiwake=20;
		char max_hira_komusubi=20;
		char max_hira_maegasira=20;

		int mugenbousicount=0;
		int itimonbetuwariatesuu[ITIMONSUU];
		int itimonbetusinpansuu[ITIMONSUU];
		int oyakatasuutotal=0;
		int wariatesuutotal=0;
		int teiin_sinpansuu=0;
		int kijun_jikosaikoubandukenameid=0;
		int kijun_jikosaikoubandukesuuji=0;
		int itimonbetutosiyorisuu[ITIMONSUU];
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここから審判部配属親方(審判委員)決定\n",year,month);
fclose(fpdebug);
*/

		////////////////審判選定基準読込(各階級・最高位ごとの最大人数)///////////////
		{
			int kazu=0;
			char ch=0;
			char temp_string_kakuritu[301];
			int temp_int=0;
			if( ProcessMessage() == -1 ){mode=1;return;}// エラーが起きたらループから抜ける
			fpcsv = fopen("data/sinpankijun.csv","r");
			if( fpcsv == NULL ){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString( 250 , 240 - 32 , "sinpankijunファイルオープンに失敗" , GetColor(255,255,255) );
				DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				mode=1;return;
			}
			kazu=0;
			ch=1;
			while(1) 
			{
				for (ii=0;ii<301;ii++){
					temp_string_kakuritu[ii]=0;
				}
				if (ch == EOF){break;}
				for (ii=0;ii<300;ii++){
					ch = fgetc(fpcsv);
					if (ch == EOF){break;}
					if(ch == '\n'){
						break;
					}else{
						if(ch=='0'){
							strcat(temp_string_kakuritu,"0");
						}else if(ch=='1'){
							strcat(temp_string_kakuritu,"1");
						}else if(ch=='2'){
							strcat(temp_string_kakuritu,"2");
						}else if(ch=='3'){
							strcat(temp_string_kakuritu,"3");
						}else if(ch=='4'){
							strcat(temp_string_kakuritu,"4");
						}else if(ch=='5'){
							strcat(temp_string_kakuritu,"5");
						}else if(ch=='6'){
							strcat(temp_string_kakuritu,"6");
						}else if(ch=='7'){
							strcat(temp_string_kakuritu,"7");
						}else if(ch=='8'){
							strcat(temp_string_kakuritu,"8");
						}else if(ch=='9'){
							strcat(temp_string_kakuritu,"9");
						}
					}
				}
				if (kazu==4){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_maisuu_maegasira=temp_int;
					}
				}else if(kazu==6){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_iin_yokoduna=temp_int;
					}
				}else if(kazu==8){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_iin_oozeki=temp_int;
					}
				}else if(kazu==10){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_iin_sekiwake=temp_int;
					}
				}else if(kazu==12){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_iin_komusubi=temp_int;
					}
				}else if(kazu==14){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_iin_maegasira=temp_int;
					}
				}else if(kazu==16){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_shunin_yokoduna=temp_int;
					}
				}else if(kazu==18){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_shunin_oozeki=temp_int;
					}
				}else if(kazu==20){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_shunin_sekiwake=temp_int;
					}
				}else if(kazu==22){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_shunin_komusubi=temp_int;
					}
				}else if(kazu==24){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_shunin_maegasira=temp_int;
					}
				}else if(kazu==26){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_hira_yokoduna=temp_int;
					}
				}else if(kazu==28){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_hira_oozeki=temp_int;
					}
				}else if(kazu==30){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_hira_sekiwake=temp_int;
					}
				}else if(kazu==32){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_hira_komusubi=temp_int;
					}
				}else if(kazu==34){
					temp_int=atoi(temp_string_kakuritu);
					if (temp_int>=0 && temp_int<21){
						max_hira_maegasira=temp_int;
					}
				}
				kazu++;
				//if( ProcessMessage() == -1 ){mode=1;return;}// エラーが起きたらループから抜ける
			}
			fclose(fpcsv);
			if( ProcessMessage() == -1 ){mode=1;return;}
		}

		teiin_sinpansuu=20;
		kijun_jikosaikoubandukenameid=4;
		kijun_jikosaikoubandukesuuji=2;
		for (i=0;i<TOSIYORISUU;i++){
			if (tosiyoridata[i].shozokuheyaid!=-1){
				oyakatasuutotal++;
			}
		}
		//一門別年寄数の確認
		for (i=0;i<ITIMONSUU;i++){
			itimonbetutosiyorisuu[i]=0;
			for (ii=0;ii<TOSIYORISUU;ii++){
				if (tosiyoridata[ii].shozokuitimonid==i
				&& tosiyoridata[ii].shozokuheyaid!=-1){
					itimonbetutosiyorisuu[i]++;
				}
			}
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}

		//一門別割り当て数暫定
		for (i=0;i<ITIMONSUU;i++){
			itimonbetusinpansuu[i]=0;
			itimonbetuwariatesuu[i]=0;
			itimonbetuwariatesuu[i]=(int)(teiin_sinpansuu*itimonbetutosiyorisuu[i]/oyakatasuutotal);
			if (itimonbetuwariatesuu[i]>4){
				itimonbetuwariatesuu[i]=4;
			}
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//一門別割り当て数修正のための前準備
		for (i=0;i<ITIMONSUU;i++){
			wariatesuutotal+=itimonbetuwariatesuu[i];
		}
		//暫定割り当て数合計が20人未満ならまず親方数の一番多い一門を1人増加
		if (wariatesuutotal>=teiin_sinpansuu){
			char deruflag=0;
			for (i=TOSIYORISUU;i>0;i--){
				for (ii=0;ii<ITIMONSUU;ii++){
					if (itimonbetutosiyorisuu[ii]>=i && itimonbetuwariatesuu[ii]<4){
						itimonbetuwariatesuu[ii]++;
						wariatesuutotal++;
						deruflag=1;
						break;
					}
				}
				if (deruflag==1){break;}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
		}
		//まだ暫定割り当て数合計が20人未満なら親方数5人以上の一門から1人ずつ増加
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここからまだ暫定割り当て数合計が20人未満なら親方数5人以上の一門から1人ずつ増加処理\n",year,month);
fclose(fpdebug);
*/
		mugenbousicount=0;
		while(1){
			mugenbousicount++;
			if (mugenbousicount>1000000){
/*
				fpdebug = fopen("debug_sinpan.txt","a");
				fprintf(fpdebug,"%d年%d月　無限ループ防止処理(まだ暫定割り当て数合計が20人未満なら親方数5人以上の一門から1人ずつ増加)\n",year,month);
				fclose(fpdebug);
*/
				break;
			}
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (wariatesuutotal>=teiin_sinpansuu){break;}
			for (i=5;i>0;i--){
				for (ii=0;ii<ITIMONSUU;ii++){
					if (itimonbetutosiyorisuu[ii]>=i && itimonbetuwariatesuu[ii]<4){
						itimonbetuwariatesuu[ii]++;
						wariatesuutotal++;
					}
					if (wariatesuutotal>=teiin_sinpansuu){break;}
				}
				if (wariatesuutotal>=teiin_sinpansuu){break;}
			}
		}
		//一門数が少ないなどの理由でまだ暫定割り当て数合計が20人未満ならまず親方数の一番多い一門から順に1人増加
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここから一門数が少ないなどの理由でまだ暫定割り当て数合計が20人未満ならまず親方数の一番多い一門から順に1人増加処理\n",year,month);
fclose(fpdebug);
*/
		mugenbousicount=0;
		while(1){
			mugenbousicount++;
			if (mugenbousicount>1000000){
/*
				fpdebug = fopen("debug_sinpan.txt","a");
				fprintf(fpdebug,"%d年%d月　無限ループ防止処理(一門数が少ないなどの理由でまだ暫定割り当て数合計が20人未満ならまず親方数の一番多い一門から順に1人増加)\n",year,month);
				fclose(fpdebug);
*/
				break;
			}
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (wariatesuutotal>=teiin_sinpansuu){break;}
			for (i=TOSIYORISUU;i>0;i--){
				for (ii=0;ii<ITIMONSUU;ii++){
					if (itimonbetutosiyorisuu[ii]>=i){
						itimonbetuwariatesuu[ii]++;
						wariatesuutotal++;
					}
					if (wariatesuutotal>=teiin_sinpansuu){break;}
				}
				if (wariatesuutotal>=teiin_sinpansuu){break;}
			}
		}

		//ここから各一門ごとに審判委員決定
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここから各一門ごとに審判委員決定処理\n",year,month);
fclose(fpdebug);
*/
		//配属先フラグとなる理事フラグの上位4ビットを初期化
		for (i=0;i<TOSIYORISUU;i++){
			tosiyoridata[i].rijiflag=(tosiyoridata[i].rijiflag&0x0f);
		}


		//Ver4.00からの選定方法での処理
		//委員から決定
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここから各一門ごとに審判委員決定処理(委員から決定)\n",year,month);
fclose(fpdebug);
*/
		for (i=0;i<ITIMONSUU;i++){
			if (itimonbetuwariatesuu[i]>itimonbetusinpansuu[i]){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
						&& tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuitimonid==i 
						&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
						&& (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==13 
					){
						if (tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid>=0){
							retirerikisidata_rikisiid(tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid);
							//retirerikisidata_rikisiid(x)によって以下の3つのsub_retirenew内のグローバル変数に値がセットされる
							//int retirerikisidata_retireage;
							//int retirerikisidata_jikosaikoubandukenameid;
							//int retirerikisidata_jikosaikoubandukesuuji;
							if (retirerikisidata_jikosaikoubandukenameid==0){
								if (suu_iin_yokoduna<max_iin_yokoduna){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_iin_yokoduna++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==1){
								if (suu_iin_oozeki<max_iin_oozeki){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_iin_oozeki++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==2){
								if (suu_iin_sekiwake<max_iin_sekiwake){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_iin_sekiwake++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==3){
								if (suu_iin_komusubi<max_iin_komusubi){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_iin_komusubi++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==4
							&& retirerikisidata_jikosaikoubandukesuuji<=max_maisuu_maegasira){
								if (suu_iin_maegasira<max_iin_maegasira){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_iin_maegasira++;
								}
							}
						}else{
							//審判委員フラグ代入
							tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
							itimonbetusinpansuu[i]++;
						}
						if (itimonbetuwariatesuu[i]<=itimonbetusinpansuu[i]){break;}
					}
				}
			}
		}
		//主任から決定
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここから各一門ごとに審判委員決定処理(主任から決定)\n",year,month);
fclose(fpdebug);
*/
		for (i=0;i<ITIMONSUU;i++){
			if (itimonbetuwariatesuu[i]>itimonbetusinpansuu[i]){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
						&& tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuitimonid==i 
						&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
						&& (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==14 
					){
						if (tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid>=0){
							retirerikisidata_rikisiid(tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid);
							//retirerikisidata_rikisiid(x)によって以下の3つのsub_retirenew内のグローバル変数に値がセットされる
							//int retirerikisidata_retireage;
							//int retirerikisidata_jikosaikoubandukenameid;
							//int retirerikisidata_jikosaikoubandukesuuji;
							if (retirerikisidata_jikosaikoubandukenameid==0){
								if (suu_shunin_yokoduna<max_shunin_yokoduna){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_shunin_yokoduna++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==1){
								if (suu_shunin_oozeki<max_shunin_oozeki){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_shunin_oozeki++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==2){
								if (suu_shunin_sekiwake<max_shunin_sekiwake){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_shunin_sekiwake++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==3){
								if (suu_shunin_komusubi<max_shunin_komusubi){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_shunin_komusubi++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==4
							&& retirerikisidata_jikosaikoubandukesuuji<=max_maisuu_maegasira){
								if (suu_shunin_maegasira<max_shunin_maegasira){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_shunin_maegasira++;
								}
							}
						}else{
							//審判委員フラグ代入
							tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
							itimonbetusinpansuu[i]++;
						}
						if (itimonbetuwariatesuu[i]<=itimonbetusinpansuu[i]){break;}
					}
				}
			}
		}
		//委員・主任・年寄(レンタルでない)から番付制限なく決定
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここから各一門ごとに審判委員決定処理(年寄(レンタルでない)から決定)\n",year,month);
fclose(fpdebug);
*/
		for (i=0;i<ITIMONSUU;i++){
			if (itimonbetuwariatesuu[i]>itimonbetusinpansuu[i]){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
						&& tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuitimonid==i 
						&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
						&& (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 
					){
						if (tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid>=0){
							retirerikisidata_rikisiid(tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid);
							//retirerikisidata_rikisiid(x)によって以下の3つのsub_retirenew内のグローバル変数に値がセットされる
							//int retirerikisidata_retireage;
							//int retirerikisidata_jikosaikoubandukenameid;
							//int retirerikisidata_jikosaikoubandukesuuji;
							if (retirerikisidata_jikosaikoubandukenameid==0){
								if (suu_hira_yokoduna<max_hira_yokoduna){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_hira_yokoduna++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==1){
								if (suu_hira_oozeki<max_hira_oozeki){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_hira_oozeki++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==2){
								if (suu_hira_sekiwake<max_hira_sekiwake){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_hira_sekiwake++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==3){
								if (suu_hira_komusubi<max_hira_komusubi){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_hira_komusubi++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==4
							&& retirerikisidata_jikosaikoubandukesuuji<=max_maisuu_maegasira){
								if (suu_hira_maegasira<max_hira_maegasira){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_hira_maegasira++;
								}
							}
						}else{
							//審判委員フラグ代入
							tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
							itimonbetusinpansuu[i]++;
						}
						if (itimonbetuwariatesuu[i]<=itimonbetusinpansuu[i]){break;}
					}
				}
			}
		}
		//年寄(レンタルも含む)から番付制限なく決定
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　ここから各一門ごとに審判委員決定処理(年寄(レンタルも含む)から決定)\n",year,month);
fclose(fpdebug);
*/
		for (i=0;i<ITIMONSUU;i++){
			if (itimonbetuwariatesuu[i]>itimonbetusinpansuu[i]){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
						&& tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuitimonid==i 
						//&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
						&& (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 
					){
						if (tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid>=0){
							retirerikisidata_rikisiid(tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid);
							//retirerikisidata_rikisiid(x)によって以下の3つのsub_retirenew内のグローバル変数に値がセットされる
							//int retirerikisidata_retireage;
							//int retirerikisidata_jikosaikoubandukenameid;
							//int retirerikisidata_jikosaikoubandukesuuji;
							if (retirerikisidata_jikosaikoubandukenameid==0){
								if (suu_hira_yokoduna<max_hira_yokoduna){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_hira_yokoduna++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==1){
								if (suu_hira_oozeki<max_hira_oozeki){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_hira_oozeki++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==2){
								if (suu_hira_sekiwake<max_hira_sekiwake){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_hira_sekiwake++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==3){
								if (suu_hira_komusubi<max_hira_komusubi){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_hira_komusubi++;
								}
							}
							if (retirerikisidata_jikosaikoubandukenameid==4
							&& retirerikisidata_jikosaikoubandukesuuji<=max_maisuu_maegasira){
								if (suu_hira_maegasira<max_hira_maegasira){ 
									//審判委員フラグ代入
									tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
									itimonbetusinpansuu[i]++;
									suu_hira_maegasira++;
								}
							}
						}else{
							//審判委員フラグ代入
							tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
							itimonbetusinpansuu[i]++;
						}
						if (itimonbetuwariatesuu[i]<=itimonbetusinpansuu[i]){break;}
					}
				}
			}
		}

		//Ver4.00からの選定方法で人数に達しない場合の再度従前の処理
		//委員から決定
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　再度従前の処理、各一門ごとに審判委員決定処理(委員から決定)\n",year,month);
fclose(fpdebug);
*/
		for (i=0;i<ITIMONSUU;i++){
			if (itimonbetuwariatesuu[i]>itimonbetusinpansuu[i]){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
						&& tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuitimonid==i 
						&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
						&& (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==13 
					){
						if (tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid>=0){
							retirerikisidata_rikisiid(tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid);
							//retirerikisidata_rikisiid(x)によって以下の3つのsub_retirenew内のグローバル変数に値がセットされる
							//int retirerikisidata_retireage;
							//int retirerikisidata_jikosaikoubandukenameid;
							//int retirerikisidata_jikosaikoubandukesuuji;
							if (retirerikisidata_jikosaikoubandukenameid<kijun_jikosaikoubandukenameid 
								|| (retirerikisidata_jikosaikoubandukenameid==kijun_jikosaikoubandukenameid
									&& retirerikisidata_jikosaikoubandukesuuji<=kijun_jikosaikoubandukesuuji)
							){
								//審判委員フラグ代入
								tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
								itimonbetusinpansuu[i]++;
							}
						}else{
							//審判委員フラグ代入
							tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
							itimonbetusinpansuu[i]++;
						}
						if (itimonbetuwariatesuu[i]<=itimonbetusinpansuu[i]){break;}
					}
				}
			}
		}
		//主任から決定
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　再度従前の処理、各一門ごとに審判委員決定処理(主任から決定)\n",year,month);
fclose(fpdebug);
*/
		for (i=0;i<ITIMONSUU;i++){
			if (itimonbetuwariatesuu[i]>itimonbetusinpansuu[i]){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
						&& tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuitimonid==i 
						&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
						&& (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==14 
					){
						if (tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid>=0){
							retirerikisidata_rikisiid(tosiyoridata[jinboujun_tosiyoriid[ii]].rikisiid);
							//retirerikisidata_rikisiid(x)によって以下の3つのsub_retirenew内のグローバル変数に値がセットされる
							//int retirerikisidata_retireage;
							//int retirerikisidata_jikosaikoubandukenameid;
							//int retirerikisidata_jikosaikoubandukesuuji;
							if (retirerikisidata_jikosaikoubandukenameid<kijun_jikosaikoubandukenameid 
								|| (retirerikisidata_jikosaikoubandukenameid==kijun_jikosaikoubandukenameid
									&& retirerikisidata_jikosaikoubandukesuuji<=kijun_jikosaikoubandukesuuji)
							){
								//審判委員フラグ代入
								tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
								itimonbetusinpansuu[i]++;
							}
						}else{
							//審判委員フラグ代入
							tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
							itimonbetusinpansuu[i]++;
						}
						if (itimonbetuwariatesuu[i]<=itimonbetusinpansuu[i]){break;}
					}
				}
			}
		}
		//委員・主任・年寄(レンタルでない)から番付制限なく決定
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　再度従前の処理、各一門ごとに審判委員決定処理(委員・主任・年寄(レンタルでない)から番付制限なく決定)\n",year,month);
fclose(fpdebug);
*/
		for (i=0;i<ITIMONSUU;i++){
			if (itimonbetuwariatesuu[i]>itimonbetusinpansuu[i]){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
						&& tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuitimonid==i 
						&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
						&& ( (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==13 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==14 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 )
					){
						//審判委員フラグ代入
						tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
						itimonbetusinpansuu[i]++;
						if (itimonbetuwariatesuu[i]<=itimonbetusinpansuu[i]){break;}
					}
				}
			}
		}
		//委員・主任・年寄(レンタルも含む)から番付制限なく決定
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　再度従前の処理、各一門ごとに審判委員決定処理(委員・主任・年寄(レンタルも含む)から番付制限なく決定)\n",year,month);
fclose(fpdebug);
*/
		for (i=0;i<ITIMONSUU;i++){
			if (itimonbetuwariatesuu[i]>itimonbetusinpansuu[i]){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (ii=0;ii<TOSIYORISUU;ii++){
					if (tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuheyaid!=-1 
						&& tosiyoridata[jinboujun_tosiyoriid[ii]].shozokuitimonid==i 
						//&& (tosiyoridata[jinboujun_tosiyoriid[ii]].keishousha_rikisiid==-1 || tosiyoridata[jinboujun_tosiyoriid[ii]].sishouflag==1)
						&& ( (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==13 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==14 || (tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag&0x0f)==0 )
					){
						//審判委員フラグ代入
						tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag=(tosiyoridata[jinboujun_tosiyoriid[ii]].rijiflag|0x10);//審判委員は上位4ビットは1
						itimonbetusinpansuu[i]++;
						if (itimonbetuwariatesuu[i]<=itimonbetusinpansuu[i]){break;}
					}
				}
			}
		}
/*
fpdebug = fopen("debug_sinpan.txt","a");
fprintf(fpdebug,"%d年%d月　審判委員決定部分終わり\n",year,month);
fclose(fpdebug);
*/
	}//審判委員決定部分終わり

	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString(0,0,"1月場所後なので委員以下の役職を決定し直しました",CRWHITE);
		DrawString(0,100,"MENUの理事会から確認できます",CRWHITE);
//DrawFormatString(300,0,CRWHITE,"副理事数　%d人",fukurijisuu);
		DrawString( 200 , 464 , "Hit any key" , CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();

	}/////表示部分終わり

}//初場所後のみのif文の最後


}////////理事選部分の最後//////////////////////////////////////////////////


/////////////年寄画面表示専用ファイル書き込み定期処理(1年1月のみretirenew冒頭でも処理、定期処理はretirenewルーチンのおしり)/////////////
	for (i=0;i<106;i++){
		if (kirokuhituyouflag_tosiyoriid[i]==1){
			sprintf(temp_filename,"data/dat/hyoji_tosiyori%d.dat\0",i);
			fp = fopen(temp_filename,"ab");
			fwrite(&year,sizeof(year),1,fp);
			fwrite(&month,sizeof(month),1,fp);
			fwrite(&tosiyoridata[i].rikisiid,sizeof(tosiyoridata[i].rikisiid),1,fp);
			fwrite(tosiyoridata[i].sikona,sizeof(tosiyoridata[i].sikona),1,fp);
			fwrite(&tosiyoridata[i].keishousha_rikisiid,sizeof(tosiyoridata[i].keishousha_rikisiid),1,fp);
			if (tosiyoridata[i].keishousha_rikisiid>=0){
				fwrite(namestring[tosiyoridata[i].keishousha_rikisiid],sizeof(namestring[tosiyoridata[i].keishousha_rikisiid]),1,fp);
			}else{
				fwrite(namestring[0],sizeof(namestring[0]),1,fp);//ダミーで入れておいた、表示するときはkeishousha_rikisiidが-1かどうかで判断すべき
			}
			fwrite(&tosiyoridata[i].shozokuitimonid,sizeof(tosiyoridata[i].shozokuitimonid),1,fp);
			if (tosiyoridata[i].shozokuitimonid>=0){
				fwrite(itimondata[tosiyoridata[i].shozokuitimonid].namestring,sizeof(itimondata[tosiyoridata[i].shozokuitimonid].namestring),1,fp);
			}else{
				fwrite(itimondata[0].namestring,sizeof(itimondata[0].namestring),1,fp);//ダミー
			}
			fwrite(&tosiyoridata[i].shozokuheyaid,sizeof(tosiyoridata[i].shozokuheyaid),1,fp);
			if (tosiyoridata[i].shozokuheyaid>=0){
				fwrite(heyastring[tosiyoridata[i].shozokuheyaid],sizeof(heyastring[tosiyoridata[i].shozokuheyaid]),1,fp);
			}else{
				fwrite(heyastring[0],sizeof(heyastring[0]),1,fp);//ダミー
			}
			fwrite(&tosiyoridata[i].sishouflag,sizeof(tosiyoridata[i].sishouflag),1,fp);
			fwrite(&tosiyoridata[i].keishousha_tosiyoriid,sizeof(tosiyoridata[i].keishousha_tosiyoriid),1,fp);
			if (tosiyoridata[i].keishousha_tosiyoriid>=0){
				fwrite(tosiyoridata[tosiyoridata[i].keishousha_tosiyoriid].namestring,sizeof(tosiyoridata[tosiyoridata[i].keishousha_tosiyoriid].namestring),1,fp);
			}else{
				fwrite(tosiyoridata[0].namestring,sizeof(tosiyoridata[0].namestring),1,fp);//ダミー
			}
			fclose(fp);
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
	}
//////////////////////////////////////////////////////////


	/////////////debug//////////////
//	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
//	DrawString(187,369+16,"ここまでは来てる？",CRWHITE);
//	ScreenFlip() ;//裏画面を表画面にコピー
//	WaitKey();
	
	return;
}


void retirerikisidata_rikisiid(int x)//引退力士の通算力士IDから引退年月と自己最高位を検索
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
	int mugenbousicount=0;
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
	DrawString(100,300,"委員以下を任命中です",CRWHITE);
	DrawString(100,350,"しばらくお待ちください",CRWHITE);
	ScreenFlip();

	nowrenban=0;
	yomikomiokflag=0;
	mugenbousicount=0;
	//オープンするファイルの選択
	FILE *fp;
	FILE *fpdebug;
	while(nowrenban<RETIREMAXFILESUU){//
		mugenbousicount++;
		if (mugenbousicount>1000000){
/*
			fpdebug = fopen("debug_sinpan.txt","a");
			fprintf(fpdebug,"%d年%d月　無限ループ防止処理(retirerikisidata_rikisiidルーチン内)\n",year,month);
			fclose(fpdebug);
*/
			break;
		}
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
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (temp_rikisiid==x && yomikomiokflag==1){
			//ファイルクローズ
			fclose(fp);
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			retirerikisidata_retireage=temp_age;
			retirerikisidata_jikosaikoubandukenameid=temp_jikosaiko_bandukenameid;
			retirerikisidata_jikosaikoubandukesuuji=temp_jikosaiko_bandukesuuji;
			break;
		}

	}//ループ終端

	return;

}

void nouryokuhyoji(int x,int yokozure)
{
	int randbunsi=0;
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
	int rikisi_front_temp;

	if (heyadata[myheyaid].jikosaiko_bandukenameid==9) randbunsi=3;
	if (heyadata[myheyaid].jikosaiko_bandukenameid==8) randbunsi=5;
	if (heyadata[myheyaid].jikosaiko_bandukenameid==7) randbunsi=7;
	if (heyadata[myheyaid].jikosaiko_bandukenameid==6) randbunsi=10;
	if (heyadata[myheyaid].jikosaiko_bandukenameid==5) randbunsi=15;
	if (heyadata[myheyaid].jikosaiko_bandukenameid==4) randbunsi=20;
	if (heyadata[myheyaid].jikosaiko_bandukenameid==3) randbunsi=30;
	if (heyadata[myheyaid].jikosaiko_bandukenameid==2) randbunsi=40;
	if (heyadata[myheyaid].jikosaiko_bandukenameid==1) randbunsi=60;
	if (heyadata[myheyaid].jikosaiko_bandukenameid==0) randbunsi=80;

	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,104,CRPURPLE,FontHandle12,"身長　 %3d",
		rikisidata[x].sinchou_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,104,CRWHITE,FontHandle12,"身長　 %3d",
		rikisidata[x].sinchou
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,120,CRPURPLE,FontHandle12,"体重　 %3d",
		rikisidata[x].taijuu_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,120,CRWHITE,FontHandle12,"体重　 %3d",
		rikisidata[x].taijuu
		);
	}
	DrawFormatStringToHandle(187+yokozure,136,CRPURPLE,FontHandle12,"積極性 %3d",
	rikisidata[x].sekkyokusei
	);
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,168,CRPURPLE,FontHandle12,"突進力 %3d",
		rikisidata[x].tossinryoku_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,168,CRWHITE,FontHandle12,"突進力 %3d",
		rikisidata[x].tossinryoku
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,184,CRPURPLE,FontHandle12,"蹴る力 %3d",
		rikisidata[x].kerutikara_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,184,CRWHITE,FontHandle12,"蹴る力 %3d",
		rikisidata[x].kerutikara
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,200,CRPURPLE,FontHandle12,"右腕力 %3d",
		rikisidata[x].migiwanryoku_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,200,CRWHITE,FontHandle12,"右腕力 %3d",
		rikisidata[x].migiwanryoku
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,216,CRPURPLE,FontHandle12,"左腕力 %3d",
		rikisidata[x].hidariwanryoku_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,216,CRWHITE,FontHandle12,"左腕力 %3d",
		rikisidata[x].hidariwanryoku
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,232,CRPURPLE,FontHandle12,"バラン %3d",
		rikisidata[x].balance_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,232,CRWHITE,FontHandle12,"バラン %3d",
		rikisidata[x].balance
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,248,CRPURPLE,FontHandle12,"立会術 %3d",
		rikisidata[x].tatiaigijutu_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,248,CRWHITE,FontHandle12,"立会術 %3d",
		rikisidata[x].tatiaigijutu
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,264,CRPURPLE,FontHandle12,"突き　 %3d",
		rikisidata[x].tuki_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,264,CRWHITE,FontHandle12,"突き　 %3d",
		rikisidata[x].tuki
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,280,CRPURPLE,FontHandle12,"右脇堅 %3d",
		rikisidata[x].migiwakikatasa_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,280,CRWHITE,FontHandle12,"右脇堅 %3d",
		rikisidata[x].migiwakikatasa
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,296,CRPURPLE,FontHandle12,"左脇堅 %3d",
		rikisidata[x].hidariwakikatasa_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,296,CRWHITE,FontHandle12,"左脇堅 %3d",
		rikisidata[x].hidariwakikatasa
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,312,CRPURPLE,FontHandle12,"あてが %3d",
		rikisidata[x].ategai_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,312,CRWHITE,FontHandle12,"あてが %3d",
		rikisidata[x].ategai
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,328,CRPURPLE,FontHandle12,"右返し %3d",
		rikisidata[x].migikaesi_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,328,CRWHITE,FontHandle12,"右返し %3d",
		rikisidata[x].migikaesi
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(187+yokozure,344,CRPURPLE,FontHandle12,"左返し %3d",
		rikisidata[x].hidarikaesi_max
		);
	}else{
		DrawFormatStringToHandle(187+yokozure,344,CRWHITE,FontHandle12,"左返し %3d",
		rikisidata[x].hidarikaesi
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(287+yokozure,104,CRPURPLE,FontHandle12,"右絞り %3d",
		rikisidata[x].migisibori_max
		);
	}else{
		DrawFormatStringToHandle(287+yokozure,104,CRWHITE,FontHandle12,"右絞り %3d",
		rikisidata[x].migisibori
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(287+yokozure,120,CRPURPLE,FontHandle12,"左絞り %3d",
		rikisidata[x].hidarisibori_max
		);
	}else{
		DrawFormatStringToHandle(287+yokozure,120,CRWHITE,FontHandle12,"左絞り %3d",
		rikisidata[x].hidarisibori
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(287+yokozure,136,CRPURPLE,FontHandle12,"右抱込 %3d",
		rikisidata[x].migikakaekomi_max
		);
	}else{
		DrawFormatStringToHandle(287+yokozure,136,CRWHITE,FontHandle12,"右抱込 %3d",
		rikisidata[x].migikakaekomi
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(287+yokozure,152,CRPURPLE,FontHandle12,"左抱込 %3d",
		rikisidata[x].hidarikakaekomi_max
		);
	}else{
		DrawFormatStringToHandle(287+yokozure,152,CRWHITE,FontHandle12,"左抱込 %3d",
		rikisidata[x].hidarikakaekomi
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(287+yokozure,168,CRPURPLE,FontHandle12,"ひきつ %3d",
		rikisidata[x].hikituke_max
		);
	}else{
		DrawFormatStringToHandle(287+yokozure,168,CRWHITE,FontHandle12,"ひきつ %3d",
		rikisidata[x].hikituke
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(287+yokozure,184,CRPURPLE,FontHandle12,"右握力 %3d",
		rikisidata[x].migiakuryoku_max
		);
	}else{
		DrawFormatStringToHandle(287+yokozure,184,CRWHITE,FontHandle12,"右握力 %3d",
		rikisidata[x].migiakuryoku
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(287+yokozure,200,CRPURPLE,FontHandle12,"左握力 %3d",
		rikisidata[x].hidariakuryoku_max
		);
	}else{
		DrawFormatStringToHandle(287+yokozure,200,CRWHITE,FontHandle12,"左握力 %3d",
		rikisidata[x].hidariakuryoku
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(287+yokozure,248,CRPURPLE,FontHandle12,"粘り　 %3d",
		rikisidata[x].nebari_max
		);
	}else{
		DrawFormatStringToHandle(287+yokozure,248,CRWHITE,FontHandle12,"粘り　 %3d",
		rikisidata[x].nebari
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(287+yokozure,264,CRPURPLE,FontHandle12,"足運び %3d",
		rikisidata[x].asihakobi_max
		);
	}else{
		DrawFormatStringToHandle(287+yokozure,264,CRWHITE,FontHandle12,"足運び %3d",
		rikisidata[x].asihakobi
		);
	}
	if (superrikisisuu[2]==1){//育成モードなら
		DrawFormatStringToHandle(287+yokozure,280,CRWHITE,FontHandle12,"柔軟性 %3d",
		rikisidata[x].juunansei
		);
	}else{
		DrawFormatStringToHandle(287+yokozure,280,CRPURPLE,FontHandle12,"柔軟性 %3d",
		rikisidata[x].juunansei
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(387+yokozure,104,CRPURPLE,FontHandle12,"右上投%3d",
		rikisidata[x].migiuwatenage_max
		);
	}else{
		DrawFormatStringToHandle(387+yokozure,104,CRWHITE,FontHandle12,"右上投%3d",
		rikisidata[x].migiuwatenage
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(387+yokozure,120,CRPURPLE,FontHandle12,"左上投%3d",
		rikisidata[x].hidariuwatenage_max
		);
	}else{
		DrawFormatStringToHandle(387+yokozure,120,CRWHITE,FontHandle12,"左上投%3d",
		rikisidata[x].hidariuwatenage
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(387+yokozure,136,CRPURPLE,FontHandle12,"右下投%3d",
		rikisidata[x].migisitatenage_max
		);
	}else{
		DrawFormatStringToHandle(387+yokozure,136,CRWHITE,FontHandle12,"右下投%3d",
		rikisidata[x].migisitatenage
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(387+yokozure,152,CRPURPLE,FontHandle12,"左下投%3d",
		rikisidata[x].hidarisitatenage_max
		);
	}else{
		DrawFormatStringToHandle(387+yokozure,152,CRWHITE,FontHandle12,"左下投%3d",
		rikisidata[x].hidarisitatenage
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(387+yokozure,168,CRPURPLE,FontHandle12,"右小投%3d",
		rikisidata[x].migikotenage_max
		);
	}else{
		DrawFormatStringToHandle(387+yokozure,168,CRWHITE,FontHandle12,"右小投%3d",
		rikisidata[x].migikotenage
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(387+yokozure,184,CRPURPLE,FontHandle12,"左小投%3d",
		rikisidata[x].hidarikotenage_max
		);
	}else{
		DrawFormatStringToHandle(387+yokozure,184,CRWHITE,FontHandle12,"左小投%3d",
		rikisidata[x].hidarikotenage
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(387+yokozure,200,CRPURPLE,FontHandle12,"右掬投%3d",
		rikisidata[x].migisukuinage_max
		);
	}else{
		DrawFormatStringToHandle(387+yokozure,200,CRWHITE,FontHandle12,"右掬投%3d",
		rikisidata[x].migisukuinage
		);
	}
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(387+yokozure,216,CRPURPLE,FontHandle12,"左掬投%3d",
		rikisidata[x].hidarisukuinage_max
		);
	}else{
		DrawFormatStringToHandle(387+yokozure,216,CRWHITE,FontHandle12,"左掬投%3d",
		rikisidata[x].hidarisukuinage
		);
	}
	/*
	if (GetRand(99)<randbunsi){
		DrawFormatStringToHandle(387+yokozure,56,CRPURPLE,FontHandle12,"能力計 %4d",
		nouryoku_total_max[x]
		);
	}else{
		DrawFormatStringToHandle(387+yokozure,56,CRWHITE,FontHandle12,"能力計 %4d",
		nouryoku_total[x]
		);
	}
	*/

	//力士画像表示
	shukushou_tate_gazou=(int)(220-rikisidata[x].sinchou)*2/3;
	shukushou_yoko_gazou=(int)((250-rikisidata[x].taijuu)/2);
	if (shukushou_tate_gazou<0){shukushou_tate_gazou=0;}
	if (shukushou_yoko_gazou<0){shukushou_yoko_gazou=0;}
	x1_gazou=387-32;
	y1_gazou=239+shukushou_tate_gazou;
	x2_gazou=x1_gazou+128-shukushou_yoko_gazou;
	y2_gazou=y1_gazou;
	x3_gazou=x2_gazou;
	y3_gazou=y1_gazou+128-shukushou_tate_gazou;
	x4_gazou=x1_gazou;
	y4_gazou=y3_gazou;
	sprintf(filename,"rikisigraph/rikisi%d.png\0",x);
	rikisi_front_temp = LoadGraph( filename ) ;
	DrawModiGraph(x1_gazou+yokozure,y1_gazou ,	x2_gazou+yokozure,y2_gazou , x3_gazou+yokozure,y3_gazou , x4_gazou+yokozure,y4_gazou , rikisi_front_temp , TRUE ) ;
	if (GetRand(99)<randbunsi){
			yokozure+=100;
			shukushou_tate_gazou=(int)(220-rikisidata[x].sinchou_max)*2/3;
			shukushou_yoko_gazou=(int)((250-rikisidata[x].taijuu_max)/2);
			if (shukushou_tate_gazou<0){shukushou_tate_gazou=0;}
			if (shukushou_yoko_gazou<0){shukushou_yoko_gazou=0;}
			x1_gazou=387-32;
			y1_gazou=239+shukushou_tate_gazou;
			x2_gazou=x1_gazou+128-shukushou_yoko_gazou;
			y2_gazou=y1_gazou;
			x3_gazou=x2_gazou;
			y3_gazou=y1_gazou+128-shukushou_tate_gazou;
			x4_gazou=x1_gazou;
			y4_gazou=y3_gazou;
			sprintf(filename,"rikisigraph/rikisi%d.png\0",x);
			rikisi_front_temp = LoadGraph( filename ) ;
			DrawModiGraph(x1_gazou+yokozure,y1_gazou ,	x2_gazou+yokozure,y2_gazou , x3_gazou+yokozure,y3_gazou , x4_gazou+yokozure,y4_gazou , rikisi_front_temp , TRUE ) ;
	}
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける


	return;
}

