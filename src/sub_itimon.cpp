#include "DxLib.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include "define.h"

extern int bashocount;//ゲーム開始からの場所数
extern int nowhyoji_torikumitab_year;
extern char nowhyoji_torikumitab_month;
extern int nowhyoji_torikumitab_ID;
extern int nowhyoji_torikumitab_ID2[15];
extern char nowhyoji_torikumitab_namestring[12];
extern char nowhyoji_torikumitab_namestring2[15][12];
extern int get_mouseclick_buttonkensakuRIGHT(void);//メニューボタンAをクリックしたら1を返し、そうでなければ0をかえす
extern int kensaku_rikisibetu(void);//士別の力士検索、返り値はrikisibetu_sentaku_id

extern int day;
extern int keikosetteiflag;//???
extern int get_mouseclick_rlist(int x);//画面右のリスト上でクリックされたら1を返す、
extern int torikumi_sentaku_page;//力士IDごとの右タブ取組(場所ごとの戦績)表示の表示ページ(0が今場所、1が先場所という感じで遡る)
extern int seiseki_sentaku_page[RIKISISUU];//力士IDごとの右タブ成績表示の表示ページ
extern int seiseki_max_page[RIKISISUU];//力士IDごとの上記の最大ページ数
extern void video(int ID,int ID2,int YEAR,int MONTH,char ID_NAMESTRING[],char ID2_NAMESTRING[]);
extern int rikisibetu_sentaku_id[RIKISISUU];//士別ページに表示する力士のID


extern int bunsekikeikoaite_id;

extern void rijikaihenshuu(int tid);

int	pagenomihenkouflag_r_mainsibetu;
char temp_list_namestring[20][12];
char temp_namestring[12];
char temp_heyastring[12];
char temp_hometownstring[28];
char temp_kako_yuushouflag[180];
char temp_kako_bandukehigasiornisi[180];
char temp_kako_bandukenameid[180];
char temp_kako_bandukesuuji[180];
char temp_kako_win[180];
char temp_kako_lost[180];
char temp_jikosaiko_tournament;
int temp_yuushoukaisuu_tournament;
int temp_age;
int page_r_sibetu_main;
char temp_heyaid;
int temp_rikisiid;
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

extern char shuumeijunhyojiflag;//年寄一覧を襲名順で表示するか従来どおり人望順で表示するか
extern int itimonid_used;
extern int retiresuu_total;//引退力士トータル
extern long filesize_retire[RETIREMAXFILESUU];//引退力士ファイルの各連番のファイルサイズ
extern long filesize_retire_jiheya[RETIREMAXFILESUU];//ちなみに引退力士一人当たりは4460バイト
extern long filesize_retire_saikoui[RETIREMAXFILESUU];
extern int retire_sentaku_category;
extern char hometownstring[SICHOUSONSUU][28];//(2544市町村分,全角13文字まで)出身地
extern long Getfilesize(char name[]);//返り値が0は存在するけどファイルサイズ0、-1→エラー、-2→存在無し
extern int retiresuu_jiheya;
extern long maxfilesize;
extern int retiresuu_saikoui;
extern void retirerikisi_hyoji(long ichijouhou,long ichijouhou_jiheya,long ichijouhou_saikoui);
extern int r_torikumi_or_seisekiflag;//引退力士情報画面右リストの表示切替フラグ、1＞過去20場所の成績
extern int r_hyojikirikaeflag;//引退力士情報画面メイン画面の表示切替フラグ
extern long kensaku_retirerikisi(long);
extern int all_retiresentaku_page;
extern int jumppage_kiroku(void);
extern int jiheya_retiresentaku_page;
extern int saikoui_retiresentaku_page;

extern int G_age;
extern int G_rikisiid;
extern char G_sikona[12];
extern int G_category;
extern int G_shuumeizumitosiyoriid;

extern void rikisidatahyoji(int x);//引数として渡された力士IDの能力値等詳細を表示するルーチン
extern int retirerikisisentaku_num_jiheya;
extern int rikisisentaku_page;//力士情報画面で表示されているページの番号
extern int rikisisentaku_num;//力士情報画面で選択された力士のリスのト番号
extern int rikisisentaku_id;//選択された力士ID
extern int kyuujou_bandukejunid[RIKISISUU];//取り組み見るフラグがたっている力士の中での番付順の力士ID
extern int rinne_bandukejunid[RIKISISUU];//取り組み見るフラグがたっている力士の中での番付順の力士ID
extern int torimi_bandukejunid[RIKISISUU];//取り組み見るフラグがたっている力士の中での番付順の力士ID
extern int rikisisentaku_num_jiheya;//力士情報画面で選択された力士のリスト番号(自部屋分)
extern int torimisuu;//取組見るフラグがたっている力士の数
extern int torimi_rikisisentaku_page;//力士情報画面で選択された取見リストページ
extern int torimi_rikisisentaku_num;//力士情報画面で選択された取見リスト番号
extern int kyuujousuu;//休場フラグがたっている力士の数
extern int kyuujou_rikisisentaku_page;//力士情報画面で選択された取見リストページ
extern int kyuujou_rikisisentaku_num;//力士情報画面で選択された取見リスト番号
extern int rinnesuu;//取組見るフラグがたっている力士の数
extern int rinne_rikisisentaku_page;//力士情報画面で選択された取見リストページ
extern int rinne_rikisisentaku_num;//力士情報画面で選択された取見リスト番号
extern int get_mouseclick_buttonkensakuLEFT(void);//メニューボタンAをクリックしたら1を返し、そうでなければ0をかえす
extern int kensaku_allrikisi(void);//左リスト検索、返り値はrikisisentaku_id

extern int myheyaid;//プレイヤーの運営する相撲部屋ID
extern int shozokurikisisuu[HEYASUU];//部屋IDごとの所属力士数
extern int heya_tosiyorisuu[HEYASUU];
extern int heyasuu_genzon;
extern int heyabandukejunid[HEYASUU][20];//部屋ごとの番付順の力士ID、
extern int heyaid_used;//使用した通算部屋ID数
extern int bandukejunid[RIKISISUU];

extern void heyadatahyoji(int x);//引数として渡された部屋IDの財政状況等詳細を表示するルーチン
extern int kabusouba(void);
extern int superrikisisuu[10];
extern int FontHandle16;
extern int FontHandle12;
extern char namestring_riji[10][21];
extern void retirerikisi_rikisiid(int x);
extern struct rikisi_data rikisidata[RIKISISUU];
extern char namestring[RIKISISUU][12];//(力士IDごとの四股名,全角５文字まで)四股名

extern int rikisisentaku_page;//力士情報画面で表示されているページの番号
extern int rikisisentaku_num;//力士情報画面で選択された力士のリスのト番号
extern int rikisisentaku_id;//選択された力士ID
extern int bandukejun_or_jiheyaflag;//力士情報画面左リスト表示切替、0＞番付順、1＞自部屋力士、2＞取り組み見る力士
extern int torikumi_or_seisekiflag;//力士情報画面右リストの表示切替フラグ、0＞取組予定、1＞過去20場所の成績

extern int page_oyakata_itimon;
extern int page_oyakata;//部屋画面の親方表示ページ
extern void game_main_backscreen(void);//基本ゲーム画面表示ルーチン
extern int mode;
extern int year;
extern int month;
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
extern void draw_buttonA(void);//メニューボタンAの表示ルーチン
extern void draw_buttonA_mouse(void);//カーソルがのっているとき用のメニューボタンAの表示ルーチン
extern void buttonA_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonA(void);//メニューボタンAをクリックしたら1を返し、そうでなければ0をかえす
								//さらに、当該ボタン上にマウスカーソルがあれば画像変更もする
extern void draw_buttonB(void);//メニューボタンBの表示ルーチン
extern void draw_buttonB_mouse(void);//カーソルがのっているとき用のメニューボタンBの表示ルーチン
extern void buttonB_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonB(void);//メニューボタンBをクリックしたら1を返し、そうでなければ0をかえす
								//さらに、当該ボタン上にマウスカーソルがあれば画像変更もする
extern void draw_buttonC(void);//メニューボタンCの表示ルーチン
extern void draw_buttonC_mouse(void);//カーソルがのっているとき用のメニューボタンCの表示ルーチン
extern void buttonC_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonC(void);//メニューボタンCをクリックしたら1を返し、そうでなければ0をかえす
								//さらに、当該ボタン上にマウスカーソルがあれば画像変更もする
extern void draw_buttonD(void);//メニューボタンDの表示ルーチン
extern void draw_buttonD_mouse(void);//カーソルがのっているとき用のメニューボタンDの表示ルーチン
extern void buttonD_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonD(void);//メニューボタンDをクリックしたら1を返し、そうでなければ0をかえす
								//さらに、当該ボタン上にマウスカーソルがあれば画像変更もする
extern void draw_buttonE(void);//メニューボタンEの表示ルーチン
extern void draw_buttonE_mouse(void);//カーソルがのっているとき用のメニューボタンEの表示ルーチン
extern void buttonE_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonE(void);//メニューボタンEをクリックしたら1を返し、そうでなければ0をかえす
								//さらに、当該ボタン上にマウスカーソルがあれば画像変更もする
extern void draw_buttonF(void);//メニューボタンBの表示ルーチン
extern void draw_buttonF_mouse(void);//カーソルがのっているとき用のメニューボタンFの表示ルーチン
extern void buttonF_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonF(void);//メニューボタンFをクリックしたら1を返し、そうでなければ0をかえす
								//さらに、当該ボタン上にマウスカーソルがあれば画像変更もする
extern void draw_buttonG(void);//メニューボタンGの表示ルーチン
extern void draw_buttonG_mouse(void);//カーソルがのっているとき用のメニューボタンGの表示ルーチン
extern void buttonG_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonG(void);//メニューボタンGをクリックしたら1を返し、そうでなければ0をかえす
extern int get_mouseclick_list(int x);//画面左のリスト上でクリックされたら1を返す、
extern int CheckHitKey_test(int);
extern int menuflag;//1:初期画面へ
extern struct tosiyori_data tosiyoridata[TOSIYORISUU];
extern struct itimon_data itimondata[ITIMONSUU];
extern struct heya_data heyadata[HEYASUU];

extern int itimon_heyasuu[ITIMONSUU];
extern int itimon_tosiyorisuu[ITIMONSUU];
extern int itimonsentaku_num;//一門画面用
extern int itimonsentaku_page;
extern int itimonsentaku_id;
extern int tosiyorisentaku_num;//年寄画面用
extern int tosiyorisentaku_page;
extern int tosiyorisentaku_id;
extern int heyasentaku_num;
extern int heyasentaku_page;
extern int heyasentaku_id;

int torikumi_rikisiid=0;
int torikumi_year=0;
int torikumi_month=0;
char torikumi_aitekonbashonamestring[15][12];
int torikumi_aiteid[15];
int torikumi_aitekonbashorikisiid[15];
int torikumi_watasikonbashorikisiid[15];
int torikumi_turncountkonbasho[15];//初日から15日目までの(0～14)取組の所要ターン数
char torikumi_kimaritekonbasho[15][9];//初日から15日目まで(0～14)の決まり手string
//char torikumi_winkonbasho[15];//初日から15日目まで(0～14)で、勝ちなら1が入る
//char torikumi_lostkonbasho[15];////初日から15日目まで(0～14)で、負けなら1が入る

int page_tosiyori=0;
int itimonbetu_rijisuu[ITIMONSUU];


struct rikisi_data backup_rikisidata[RIKISISUU];
struct tosiyori_data backup_tosiyoridata[TOSIYORISUU];
struct itimon_data backup_itimondata[ITIMONSUU];

void tosiyoridatahyoji(int tosiyoriID);
void itimondatahyoji(char flag,int itimonID);//flagが0だと通常表示、1だと緑文字部分を白文字で表示
void menu_itimon(void);
void menu_tosiyori(void);
void tosiyorimeihenkou(int x);
//3.15より
void shozokuhenkou(int tosiyoriID);
void Q_shoyuuhenkou(int tosiyoriID);
void Q_shozokuhenkouORshuumeishasentaku(int tosiyoriID);
void Q_tosiyorihenshuu(int tosiyoriID);
void heyasinsetu(int tosiyoriID,int heyaid_dokuritusaki,int heyaid_dokuritumoto);//年寄画面編集ボタンでの部屋新設処理
void tosiyorihyoujifilekakikomi(int tosiyoriID);//年寄画面表示専用ファイル書き込み
void tosiyorisuukakunin(void);//部屋別年寄数、部屋別力士数、部屋番付順再計算
void heyashoumetu(int tosiyoriID,int heyaid_ikisaki,int heyaid_moto);//部屋消滅処理	//行き先部屋と元部屋が一緒の場合は、行き先決まっていない退職させる処理の場合
void iseki_tandoku(int tosiyoriID,int heyaid_ikisaki,int heyaid_moto);//移籍する年寄ID、移籍先部屋ＩＤ、現部屋ＩＤ
void itimonshoumetu(int shoumetuitimonid);//一門消滅処理
void taishokusaseru(int tosiyoriID);//退職させる処理
void keishou(int tosiyoriID,int keishouid);//継承して残したい(功績顕著一代年寄の場合は残らず)年寄株ID(現師匠),継承の結果空き株(師匠が功績顕著だと師匠に昇格するので空き株にはならない)になる年寄株ID(現継承者)
void oyakatasentaku(int tosiyoriID);//所有者として親方を選択させるルーチン
void genekirikisisentaku(int tosiyoriID);//所有者として現役力士を選択させるルーチン
void retirerikisisentaku(int tosiyoriID);//襲名者として引退力士の中から選択させるルーチン
void sonzaisakusei(int tosiyoriID);//襲名者として引退力士以外の存在を作成
int genekijisikonanyuuryoku(int tosiyoriID);//現役時の四股名を入力するルーチン、キャンセルで-1が返る
void agenyuuryoku(int tosiyoriID);//年齢入力ルーチン
void jinbounyuuryoku(int tosiyoriID);//人望入力ルーチン
void categorynyuuryoku(int tosiyoriID);//カテゴリー入力ルーチン(功績顕著の200-299は自動で4が入る)
void sishouninaru(int tosiyoriID);//部屋付が師匠と名跡交換して師匠になる処理
void itimonisekidokuritugouryuu(int heyaid);//一門移籍独立合流処理
void itimonnusininaru(int heyaid);//一門主になる処理

int genekirikisisentaku_keiko(int x,char flag);//
											//選択した力士の画像IDが返される
											//flag0→稽古相手選択、1→技分析相手選択


void Q_tosiyorihenshuu(int tosiyoriID)
{

loop:
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString(100,200,"キャンセル",CRGREEN);
	DrawString(250,200,"所有(継承)者変更",CRGREEN);
	if (tosiyoridata[tosiyoriID].shozokuheyaid>=0){
		DrawString(400,200,"所属先変更",CRGREEN);
		DrawString(400,150,"退職させる",CRGREEN);
	}else{
		DrawString(400,200,"襲名者選択",CRGREEN);
	}

	if (tosiyoridata[tosiyoriID].sishouflag==0 
	&& tosiyoriID<106 
	&& tosiyoridata[tosiyoriID].shozokuheyaid>=0 
	&& tosiyoridata[tosiyoriID].keishousha_rikisiid==-1
	&& tosiyoridata[tosiyoriID].keishousha_tosiyoriid==-1){
		DrawString(400,250,"師匠になる",CRGREEN);
	}
	if (tosiyoridata[tosiyoriID].shozokuheyaid>=0){
		if (tosiyoriID<106 || tosiyoriID>=300){
			DrawString(250,250,"カテゴリー変更",CRGREEN);
		}
		if (tosiyoridata[tosiyoriID].rikisiid<0){
			DrawString(250,275,"現役四股名変更",CRGREEN);
		}
		DrawString(250,300,"年齢変更",CRGREEN);
		DrawString(250,325,"人望変更",CRGREEN);
		DrawString(250,375,"地位・役職変更",CRGREEN);
	}

	ScreenFlip() ;//裏画面を表画面にコピー
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//キャンセル
		if (get_mouseclick(100,200,100+16*5,200+16)==1 ){
			break;
		}
		if (tosiyoridata[tosiyoriID].shozokuheyaid>=0){
			//カテゴリー変更
			if (tosiyoriID<106 || tosiyoriID>=300){
				if (get_mouseclick(250,250,250+16*7,250+16)==1 ){
					categorynyuuryoku(tosiyoriID);
					break;
				}
			}
			//現役四股名変更
			if (tosiyoridata[tosiyoriID].rikisiid<0){
				if (get_mouseclick(250,275,250+16*7,275+16)==1 ){
					genekijisikonanyuuryoku(tosiyoriID);
					break;
				}
			}
			//年齢変更
			if (get_mouseclick(250,300,250+16*4,300+16)==1 ){
				agenyuuryoku(tosiyoriID);
				break;
			}
			//人望変更
			if (get_mouseclick(250,325,250+16*4,325+16)==1 ){
				jinbounyuuryoku(tosiyoriID);
				break;
			}
			//地位・役職変更
			if (get_mouseclick(250,375,250+16*7,375+16)==1 ){
				rijikaihenshuu(tosiyoriID);
				break;
			}
		}
		//師匠になる
		if (tosiyoridata[tosiyoriID].sishouflag==0 && tosiyoridata[tosiyoriID].shozokuheyaid>=0 
		&& tosiyoriID<106 
		&& tosiyoridata[tosiyoriID].shozokuheyaid>=0 
		&& tosiyoridata[tosiyoriID].keishousha_rikisiid==-1
		&& tosiyoridata[tosiyoriID].keishousha_tosiyoriid==-1){
			if (get_mouseclick(400,250,400+16*5,250+16)==1 ){
				sishouninaru(tosiyoriID);
				break;
			}
		}
		//所有者変更
		if (get_mouseclick(250,200,250+16*8,200+16)==1 ){
			//ここにルーチン名
			Q_shoyuuhenkou(tosiyoriID);
			break;
		}
		//所属先変更・襲名者選択
		if (get_mouseclick(400,200,400+16*7,200+16)==1 ){
			//ここにルーチン名
			Q_shozokuhenkouORshuumeishasentaku(tosiyoriID);
			break;
		}
		//退職させる選択
		if (get_mouseclick(400,150,400+16*7,150+16)==1 ){
			if (tosiyoridata[tosiyoriID].shozokuheyaid>=0){
				//ここにルーチン名
				taishokusaseru(tosiyoriID);
				break;
			}
		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){mode=1;return ;}
		Sleep(1);
	}
	return;
}

void sishouninaru(int tosiyoriID)
{
	int i,ii;
	int sishouid=0;
	sishouid=-1;
	//部屋の師匠のIDを検索
	for (i=0;i<TOSIYORISUU;i++){
		if (tosiyoridata[i].sishouflag==1 
		&& tosiyoridata[tosiyoriID].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
			sishouid=i;
			break;
		}
	}
	if (sishouid==-1){return;}//想定外エラー
	//師匠に別の継承予定者がいるときは除外
	if (tosiyoridata[sishouid].keishousha_rikisiid>=0 
	|| (tosiyoridata[sishouid].keishousha_tosiyoriid>=0 && tosiyoridata[sishouid].keishousha_tosiyoriid!=tosiyoriID)){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString(100,200,"すでに別の継承者が指定されているので処理できません。",CRWHITE);
		DrawString(100,300,"HIT ANY KEY",CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return;
	}
	//師匠が一代年寄のときは除外
	if (sishouid>=200){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString(100,200,"一代年寄の師匠の場合はこの処理はできません。",CRWHITE);
		DrawString(100,300,"HIT ANY KEY",CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return;
	}

	//処理してよいかの確認
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(100,200,CRWHITE,"%s親方と%s親方が名跡交換し、元%sが%s部屋を継承します。",
	tosiyoridata[sishouid].namestring,
	tosiyoridata[tosiyoriID].namestring,
	tosiyoridata[tosiyoriID].sikona,
	tosiyoridata[sishouid].namestring);
//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
	DrawString(100,250,"それでもよろしいですか？",CRWHITE);
	DrawString(100,100,"キャンセル",CRGREEN);
	DrawString(400,100,"はい",CRGREEN);
	ScreenFlip() ;//裏画面を表画面にコピー
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//キャンセル
		if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
			return;
		}
		//決定
		if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
			break;
		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){mode=1;return ;}
		Sleep(1);
	}

	//名跡交換
	for (i=0;i<TOSIYORISUU;i++){
		backup_tosiyoridata[i]=tosiyoridata[i];
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}
	tosiyoridata[sishouid]=backup_tosiyoridata[tosiyoriID];
	tosiyoridata[tosiyoriID]=backup_tosiyoridata[sishouid];
	//丸ごと交換しているのでその修正
	tosiyoridata[sishouid].sishouflag=1;
	tosiyoridata[tosiyoriID].sishouflag=0;
	tosiyoridata[tosiyoriID].keishousha_tosiyoriid=-1;//もともと継承予定者だった可能性があるから
	strcpy(tosiyoridata[sishouid].namestring,backup_tosiyoridata[sishouid].namestring);
	strcpy(tosiyoridata[tosiyoriID].namestring,backup_tosiyoridata[tosiyoriID].namestring);

	tosiyorisuukakunin();

	tosiyorihyoujifilekakikomi(tosiyoriID);
	tosiyorihyoujifilekakikomi(sishouid);

	FILE *fp;
	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s親方と%s親方が名跡交換し、元%sが%s部屋を継承しました。(編集)\n",
	backup_tosiyoridata[sishouid].namestring,
	backup_tosiyoridata[tosiyoriID].namestring,
	backup_tosiyoridata[tosiyoriID].sikona,
	backup_tosiyoridata[sishouid].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	//DrawFormatString(0,369,CRWHITE,"%s一門は名称を変更するかどうかの処理で想定外の困ったなぁ",
	DrawFormatString(0,369,CRWHITE,"%s親方と%s親方が名跡交換し、元%sが%s部屋を継承しました。",
	backup_tosiyoridata[sishouid].namestring,
	backup_tosiyoridata[tosiyoriID].namestring,
	backup_tosiyoridata[tosiyoriID].sikona,
	backup_tosiyoridata[sishouid].namestring);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	//////////////////////////////////////////////////////////////

	return;
}

void Q_shozokuhenkouORshuumeishasentaku(int tosiyoriID)
{

loop:
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString(100,200,"キャンセル",CRGREEN);
	if (tosiyoridata[tosiyoriID].shozokuheyaid>=0){
		if (tosiyoridata[tosiyoriID].sishouflag==1){
			DrawString(400,200,"合併先の部屋を選ぶ",CRGREEN);
		}else{
			DrawString(400,200,"移籍先の部屋を選ぶ",CRGREEN);
		}
	}else{
		DrawString(250,200,"存在作成",CRGREEN);
		DrawString(400,200,"引退力士から選ぶ",CRGREEN);
	}
	ScreenFlip() ;//裏画面を表画面にコピー
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//キャンセル
		if (get_mouseclick(100,200,100+16*5,200+16)==1 ){
			break;
		}
		if (tosiyoridata[tosiyoriID].shozokuheyaid>=0){
			//所属部屋を選ぶ
			if (get_mouseclick(400,200,400+16*9,200+16)==1 ){
				//ここにルーチン名
				shozokuhenkou(tosiyoriID);
				break;
			}
		}else{
			//存在作成
			if (get_mouseclick(250,200,250+16*4,200+16)==1 ){
				//ここにルーチン名
				sonzaisakusei(tosiyoriID);
				break;
			}
			//引退力士から選ぶ
			if (get_mouseclick(400,200,400+16*8,200+16)==1 ){
				//ここにルーチン名
				retirerikisisentaku(tosiyoriID);
				break;
			}

		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){mode=1;return ;}
		Sleep(1);
	}
	return;
}

void taishokusaseru(int tosiyoriID)//退職させる処理
{

	int i,ii,iii;
	char namestring_backup[12];
	char namestring2_backup[12];
	for (i=0;i<12;i++){
		namestring_backup[i]=0;
		namestring2_backup[i]=0;
	}

	strcpy(namestring_backup,tosiyoridata[tosiyoriID].namestring);

	tosiyorisuukakunin();

	//一門主の師匠はＮＧ
	if (itimondata[tosiyoridata[tosiyoriID].shozokuitimonid].shuheyaid==tosiyoridata[tosiyoriID].shozokuheyaid 
	&& tosiyoridata[tosiyoriID].sishouflag==1){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString(100,200,"一門主の師匠は、この処理はできません。",CRWHITE);
		DrawString(100,300,"HIT ANY KEY",CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return;
	}

	//継承指名されている年寄はＮＧ
	{
		int simeiariflag=0;
		//継承者指名受けていないか確認
		for (i=0;i<TOSIYORISUU;i++){
			if (tosiyoridata[i].keishousha_tosiyoriid==tosiyoriID && tosiyoridata[i].shozokuheyaid>=0){
				simeiariflag=1;
				break;
			}
		}
		if (simeiariflag==1){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString(100,200,"継承者に指定されているので移籍できません。",CRWHITE);
			DrawString(100,300,"HIT ANY KEY",CRWHITE);
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			return;
		}
	}
	//継承者年寄いる場合、所属部屋IDリセットせず、継承者に継承させる
	if (tosiyoridata[tosiyoriID].keishousha_tosiyoriid>=0){

		keishou(tosiyoriID,tosiyoridata[tosiyoriID].keishousha_tosiyoriid);//継承して残したい年寄株ID(現師匠),継承の結果空き株になる年寄株ID(現継承者)

		return;
	//継承者年寄いない場合
	}else{
		//師匠の場合
		if (tosiyoridata[tosiyoriID].sishouflag==1){
			//師匠で継承指名現役力士いる場合ＮＧ
			if (tosiyoridata[tosiyoriID].keishousha_rikisiid>=0){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(0,200,"継承指名済み現役力士がいる師匠は、この処理はできません。",CRWHITE);
				DrawString(100,300,"HIT ANY KEY",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				return;
			}
			//師匠で部屋付いない場合→消滅処理
			if (heya_tosiyorisuu[tosiyoridata[tosiyoriID].shozokuheyaid]==1){
				if (heyasuu_genzon>=40){

					//処理してよいかの確認
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawFormatString(100,200,CRWHITE,"%s親方の退職に伴い、%s部屋は消滅します。",
					tosiyoridata[tosiyoriID].namestring,
					tosiyoridata[tosiyoriID].namestring);
				//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
					DrawString(100,250,"それでもよろしいですか？",CRWHITE);
					DrawString(100,100,"キャンセル",CRGREEN);
					DrawString(400,100,"はい",CRGREEN);
					ScreenFlip() ;//裏画面を表画面にコピー
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
					}
					while(1)
					{
						//キャンセル
						if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
							return;
						}
						//決定
						if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
							break;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 ){mode=1;return ;}
						Sleep(1);
					}

					//行き先も元部屋ＩＤも同じにして消滅処理
					heyashoumetu(tosiyoriID,tosiyoridata[tosiyoriID].shozokuheyaid,tosiyoridata[tosiyoriID].shozokuheyaid);
					WaitTimer(200);
					return;
				}else{
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawString(100,200,"40部屋未満になってしまうので、この処理はできません。",CRWHITE);
					DrawString(100,300,"HIT ANY KEY",CRWHITE);
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitKey();
					return;
				}
				return;
			//師匠で部屋付いる場合
			}else{
				int keishouid=0;
				int i_backup=0;
				int temp_narabekaeyou[TOSIYORISUU];//並べ替え用に並べ替えたい要素を入れる変数
				int jinboujun_tosiyoriid[TOSIYORISUU];
				int temp_tosiyoriid=0;

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

				keishouid=-1;
				for (i=0;i<TOSIYORISUU;i++){
					i_backup=i;
					i=jinboujun_tosiyoriid[i];
					if (tosiyoridata[i].shozokuheyaid==tosiyoridata[tosiyoriID].shozokuheyaid 
					&& i!=tosiyoriID 
					&& (tosiyoridata[i].category==1 || tosiyoridata[i].category==2 || tosiyoridata[i].category>=4) 
					&& tosiyoridata[i].keishousha_rikisiid==-1){
						keishouid=i;
						break;
					}
					i=i_backup;
				}
				//師匠になれる資格のある部屋付いない→ＮＧ
				if (keishouid==-1){
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawString(0,200,"部屋付がいるのに師匠になれる資格のあるのがいない場合、",CRWHITE);
					DrawString(0,250,"この処理はできません。",CRWHITE);
					DrawString(100,300,"HIT ANY KEY",CRWHITE);
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitKey();
					return;
				//師匠が通常株で部屋の師匠になる資格のある部屋付がいる→リセットせず継承させる
				//師匠が功績顕著一代年寄で部屋の師匠になる資格のある部屋付がいる
				//→一代年寄株はリセット、部屋付が師匠にそのまま昇格、部屋の名称変更も必要
				}else{
					keishou(tosiyoriID,keishouid);//継承して残したい(功績顕著一代年寄の場合は残らず)年寄株ID(現師匠),継承の結果空き株(師匠が功績顕著だと師匠に昇格するので空き株にはならない)になる年寄株ID(現継承者)
					return;
				}
			}
		//部屋付の場合
		}else{

			//処理してよいかの確認
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawFormatString(100,200,CRWHITE,"元%sが退職し、年寄株%sは空き株になります。",
			tosiyoridata[tosiyoriID].sikona,
			tosiyoridata[tosiyoriID].namestring);
		//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
			DrawString(100,250,"それでもよろしいですか？",CRWHITE);
			DrawString(100,100,"キャンセル",CRGREEN);
			DrawString(400,100,"はい",CRGREEN);
			ScreenFlip() ;//裏画面を表画面にコピー
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				Sleep(1);
			}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				Sleep(1);
			}
			while(1)
			{
				//キャンセル
				if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
					return;
				}
				//決定
				if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 ){mode=1;return ;}
				Sleep(1);
			}

			//所属部屋IDリセット
			tosiyoridata[tosiyoriID].shozokuheyaid=-1;
			//リセット処理	
			tosiyoridata[tosiyoriID].age=0;
			tosiyoridata[tosiyoriID].category=0;
			tosiyoridata[tosiyoriID].startyear=0;
			tosiyoridata[tosiyoriID].rikisiid=-1;
			strcpy(tosiyoridata[tosiyoriID].sikona,"\0");
			tosiyoridata[tosiyoriID].sishouflag=0;
			if (tosiyoriID>=200){
				strcpy(tosiyoridata[tosiyoriID].namestring,"\0");
			}
			tosiyoridata[tosiyoriID].jinbou=0;
			tosiyoridata[tosiyoriID].rijiflag=0;
			//tosiyoridata[tosiyoriID].keishousha_rikisiid=-1;
			//tosiyoridata[tosiyoriID].keishousha_tosiyoriid=-1;

			tosiyorisuukakunin();

			tosiyorihyoujifilekakikomi(tosiyoriID);

			FILE *fp;
			//eventlog書き込み/////////////////////////////////////////
			fp = fopen("data/eventlog.txt","a");
			// オープンできなかったらここで終了
			if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
			fprintf(fp,"年寄株%sを空き株にしました(編集)\n",
			namestring_backup);
			//クローズ
			fclose(fp);
			if( ProcessMessage() == -1 ){mode=1;return ;}
			////////////////////////////////////////////////////////////
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawFormatString(100,200,CRWHITE,"年寄株%sを空き株にしました",
			namestring_backup);
			DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			//////////////////////////////////////////////////////////////

			return;
		}
	}

}



void shozokuhenkou(int tosiyoriID)
{
	int i,ii,iii;
	int count=0;
	int heyasentaku_page=0;//表示されているページの番号
	int heyasentaku_num=0;//画面で選択された部屋のリストの番号
	int heyasentaku_id=0;//選択された部屋ID


loop:
	/*
	for (i=0;i<RIKISISUU;i++){
		backup_rikisidata[i]=rikisidata[i];
	}
	if( ProcessMessage() == -1 ){mode=1;return ;}
	for (i=0;i<TOSIYORISUU;i++){
		backup_tosiyoridata[i]=tosiyoridata[i];
	}
	if( ProcessMessage() == -1 ){mode=1;return ;}
	for (i=0;i<ITIMONSUU;i++){
		backup_itimondata[i]=itimondata[i];
	}
	if( ProcessMessage() == -1 ){mode=1;return ;}
	*/
	//リストに部屋ID順で部屋名を表示
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	game_main_backscreen();//基本画面表示
	DrawBox(3,76,183,475,CRTAB,TRUE);
	DrawBox(x1[heyasentaku_num],y1[heyasentaku_num],x2[heyasentaku_num],y2[heyasentaku_num],CRKEIJIBANON,TRUE);//クリックしたところを強調
	for(ii=0;ii<40;ii++){
		if (ii+heyasentaku_page*40<HEYASUU){
			DrawFormatStringToHandle(x1[ii],y1[ii],CRBLACK,FontHandle12,"%2d %s",ii+heyasentaku_page*40,heyastring[ii+heyasentaku_page*40]);
		}
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}
	if (tosiyoridata[tosiyoriID].sishouflag==1){
		DrawString(187,369,"↑↓←→で左のリストから合併先の部屋を選択",CRWHITE);
	}else{
		DrawString(187,369,"↑↓←→で左のリストから移籍先の部屋を選択",CRWHITE);
	}
	if (heyasentaku_page==0){
		DrawString(187,385,"一番下のときに↓で次ページ",CRWHITE);
	}else{
		DrawString(187,385,"一番上のときに↑で前ページ",CRWHITE);
	}

	//移動先部屋データ表示
	heyadatahyoji(heyasentaku_id);
	DrawBox(187,401,637,479,CRBACK,TRUE);//下部リンク部分消し
	DrawBox(187,41+70,187+32,41+70+15,CRBACK,TRUE);//編集ボタン消し
	DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分消し
	DrawBox(3,24,182,54,CRBACK,TRUE);//左上部分消し
	if (tosiyoridata[tosiyoriID].sishouflag==1){
		DrawFormatStringToHandle(240,5,CRWHITE,FontHandle12,"%s部屋の合併先決定画面",tosiyoridata[tosiyoriID].namestring);
	}else{
		DrawFormatStringToHandle(240,5,CRWHITE,FontHandle12,"%s親方の移籍先決定画面",tosiyoridata[tosiyoriID].namestring);
	}
	DrawString(5,30,"キャンセル",CRGREEN);
	DrawString(120,30,"決定",CRGREEN);


	ScreenFlip() ;//裏画面を表画面にコピー

	//リスト上で部屋名をクリックした場合に部屋詳細情報を表示
		// キー入力待ち(この一文を入れないとうまくいかないみたい)
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//キャンセル
		if (get_mouseclick(5,30,85,30+16)==1 ){
			break;
		}
		//決定
		if (get_mouseclick(120,30,152,30+16)==1 ){
			int temp_narabekaeyou[TOSIYORISUU];//並べ替え用に並べ替えたい要素を入れる変数
			int jinboujun_tosiyoriid[TOSIYORISUU];
			int temp_tosiyoriid=0;
			tosiyorisuukakunin();
			FILE *fp;
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

			//移籍先が（空き部屋）→新規設立（移籍先の師匠になる）
			if (heya_tosiyorisuu[heyasentaku_id]==0){
				//部屋の師匠だった場合（部屋丸ごと移籍）
				if (tosiyoridata[tosiyoriID].sishouflag==1){
					if (tosiyoridata[tosiyoriID].shozokuheyaid==myheyaid){
						ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
						DrawString(100,200,"あなたのお部屋の師匠は移籍できません",CRWHITE);
						DrawString(100,300,"HIT ANY KEY",CRWHITE);
						ScreenFlip() ;//裏画面を表画面にコピー
						WaitKey();
					}else{
						//if (heyasuu_genzon>=40){

							//処理してよいかの確認
							ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
							DrawFormatString(100,200,CRWHITE,"%s部屋が丸ごと所属部屋IDを変更するだけになります。",
							heyastring[tosiyoridata[tosiyoriID].shozokuheyaid]);
						//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
							DrawString(100,250,"それでもよろしいですか？",CRWHITE);
							DrawString(100,100,"キャンセル",CRGREEN);
							DrawString(400,100,"はい",CRGREEN);
							ScreenFlip() ;//裏画面を表画面にコピー
							while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
								Sleep(1);
							}
							while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
								Sleep(1);
							}
							while(1)
							{
								//キャンセル
								if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
									return;
								}
								//決定
								if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
									break;
								}
								// メッセージ処理
								if( ProcessMessage() == -1 ){mode=1;return ;}
								Sleep(1);
							}

							int motoheyaid=0;
							motoheyaid=tosiyoridata[tosiyoriID].shozokuheyaid;
							//部屋名をつける(空き部屋だったから)
							strcpy(heyastring[heyasentaku_id],tosiyoridata[tosiyoriID].namestring);
							//部屋消滅ルーチン流用
							heyashoumetu(tosiyoriID,heyasentaku_id,tosiyoridata[tosiyoriID].shozokuheyaid);
							//一門主だったら一門の主部屋ID変更
							for (i=0;i<ITIMONSUU;i++){
								if (itimondata[i].shuheyaid==motoheyaid){
									itimondata[i].shuheyaid=tosiyoridata[tosiyoriID].shozokuheyaid;
									break;
								}
							}
							//部屋関連変数
							heyadata[heyasentaku_id].heyaid_tuusan=heyaid_used;
							heyaid_used++;
							heyadata[heyasentaku_id].hpoint=GetRand(2000)+1000;
							//yaoflag;//八百長をやる部屋かどうかのフラグはいじらず
							for (ii=0;ii<HEYASUU;ii++){
								heyadata[heyasentaku_id].kpoint[ii]=0;
							}
							heyadata[heyasentaku_id].keikoryou=0;
						 	heyadata[heyasentaku_id].jikosaiko_bandukenameid=rikisidata[heyabandukejunid[heyasentaku_id][0]].bandukenameid;
							heyadata[heyasentaku_id].jikosaiko_bandukesuuji=rikisidata[heyabandukejunid[heyasentaku_id][0]].bandukesuuji;
							heyadata[heyasentaku_id].yuushoukaisuu=0;
							heyadata[heyasentaku_id].yokodunasuu=0;
							heyadata[heyasentaku_id].startyear=year;
							heyadata[heyasentaku_id].startmonth=month;

							WaitTimer(200);
							return;
						//}else{
						//	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
						//	DrawString(100,200,"40部屋未満になってしまうので、この処理はできません。",CRWHITE);
						//	DrawString(100,300,"HIT ANY KEY",CRWHITE);
						//	ScreenFlip() ;//裏画面を表画面にコピー
						//	WaitKey();
						//}
					}
				//部屋付だった場合→力士は3.14までの新規設立処理を流用し一部を連れて行く
				}else{
					int simeiariflag=0;
					//継承者指名受けていないか確認
					for (i=0;i<TOSIYORISUU;i++){
						if (tosiyoridata[i].keishousha_tosiyoriid==tosiyoriID && tosiyoridata[i].shozokuheyaid>=0){
							simeiariflag=1;
							break;
						}
					}
					if (simeiariflag==0){
						//師匠になれる資格があるか確認（Ｂ以上で借株・期間限定でない）
						if ( (tosiyoridata[tosiyoriID].category==1 || tosiyoridata[tosiyoriID].category==2 || tosiyoridata[tosiyoriID].category==4) && tosiyoridata[tosiyoriID].keishousha_rikisiid==-1){

							//処理してよいかの確認
							ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
							DrawFormatString(100,200,CRWHITE,"%s親方が独立し部屋を新設します。",
							tosiyoridata[tosiyoriID].namestring);
						//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
							DrawString(100,250,"それでもよろしいですか？",CRWHITE);
							DrawString(100,100,"キャンセル",CRGREEN);
							DrawString(400,100,"はい",CRGREEN);
							ScreenFlip() ;//裏画面を表画面にコピー
							while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
								Sleep(1);
							}
							while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
								Sleep(1);
							}
							while(1)
							{
								//キャンセル
								if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
									return;
								}
								//決定
								if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
									break;
								}
								// メッセージ処理
								if( ProcessMessage() == -1 ){mode=1;return ;}
								Sleep(1);
							}

							heyasinsetu(tosiyoriID,heyasentaku_id,tosiyoridata[tosiyoriID].shozokuheyaid);//独立年寄,独立先部屋ID,独立元部屋ID
							WaitTimer(200);
							return;
						}else{
							ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
							DrawString(100,200,"借株・Ｃカテ・期間限定年寄は、部屋の師匠にはなれません。",CRWHITE);
							DrawString(100,300,"HIT ANY KEY",CRWHITE);
							ScreenFlip() ;//裏画面を表画面にコピー
							WaitKey();
						}
					}else{
						ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
						DrawString(100,200,"継承者に指定されているので移籍できません。",CRWHITE);
						DrawString(100,300,"HIT ANY KEY",CRWHITE);
						ScreenFlip() ;//裏画面を表画面にコピー
						WaitKey();
					}
				}
			//移籍先が既存部屋
			}else{
				if (tosiyoridata[tosiyoriID].shozokuheyaid!=heyasentaku_id){
					//部屋の師匠だった場合→部屋全体が吸収される形、親方全員移籍先の部屋付になる。
					if (tosiyoridata[tosiyoriID].sishouflag==1){
						//留保付き師匠はだめよ
						if (tosiyoridata[tosiyoriID].keishousha_rikisiid>=0 || tosiyoridata[tosiyoriID].keishousha_tosiyoriid>=0){
							ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
							DrawString(100,200,"継承者指名済みの師匠は移籍できません",CRWHITE);
							DrawString(100,300,"HIT ANY KEY",CRWHITE);
							ScreenFlip() ;//裏画面を表画面にコピー
							WaitKey();
						//留保無し師匠はＯＫ
						}else{
							if (tosiyoridata[tosiyoriID].shozokuheyaid==myheyaid){
								ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
								DrawString(100,200,"あなたのお部屋の師匠は移籍できません",CRWHITE);
								DrawString(100,300,"HIT ANY KEY",CRWHITE);
								ScreenFlip() ;//裏画面を表画面にコピー
								WaitKey();
							}else{
								//一門主の師匠はＮＧ→その一門がその部屋1部屋しかない場合のみ部屋合併+一門の合併で
								if (itimondata[tosiyoridata[tosiyoriID].shozokuitimonid].shuheyaid==tosiyoridata[tosiyoriID].shozokuheyaid){
									int heyasuu_itimon=0;
									for (i=0;i<TOSIYORISUU;i++){
										if (tosiyoridata[i].shozokuitimonid==tosiyoridata[tosiyoriID].shozokuitimonid 
										&& tosiyoridata[i].sishouflag==1){
											heyasuu_itimon++;
										}
									}
									//部屋合併+一門合併処理
									if (heyasuu_itimon==1){
										//if部屋存在数下限確認
										if (heyasuu_genzon>=40){
											int shoumetuitimonid=0;

											//処理してよいかの確認
											ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
											DrawFormatString(100,200,CRWHITE,"%s親方の一門・部屋とも消滅します。",
											tosiyoridata[tosiyoriID].namestring);
										//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
											DrawString(100,250,"それでもよろしいですか？",CRWHITE);
											DrawString(100,100,"キャンセル",CRGREEN);
											DrawString(400,100,"はい",CRGREEN);
											ScreenFlip() ;//裏画面を表画面にコピー
											while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
												Sleep(1);
											}
											while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
												Sleep(1);
											}
											while(1)
											{
												//キャンセル
												if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
													return;
												}
												//決定
												if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
													break;
												}
												// メッセージ処理
												if( ProcessMessage() == -1 ){mode=1;return ;}
												Sleep(1);
											}

											shoumetuitimonid=tosiyoridata[tosiyoriID].shozokuitimonid;
											//部屋消滅処理
											heyashoumetu(tosiyoriID,heyasentaku_id,tosiyoridata[tosiyoriID].shozokuheyaid);
											//一門消滅処理
											itimonshoumetu(shoumetuitimonid);
											WaitTimer(200);
											return;
										}else{
											ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
											DrawString(100,200,"40部屋未満になってしまうので、この処理はできません。",CRWHITE);
											DrawString(100,300,"HIT ANY KEY",CRWHITE);
											ScreenFlip() ;//裏画面を表画面にコピー
											WaitKey();
										}
									//複数部屋を抱える一門の統帥部屋はＮＧ
									}else{
										ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
										DrawString(100,200,"複数の部屋を抱える一門の統帥は移籍処理をできません",CRWHITE);
										DrawString(100,300,"HIT ANY KEY",CRWHITE);
										ScreenFlip() ;//裏画面を表画面にコピー
										WaitKey();
									}
								//一門主でない師匠はＯＫ
								}else{
									//部屋合併処理
									//部屋消滅（力士は番付優先同行処理、他は一門優先移籍処理）
									//if部屋存在数下限確認
									if (heyasuu_genzon>=40){

										//処理してよいかの確認
										ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
										DrawFormatString(100,200,CRWHITE,"%s親方の部屋が消滅します。",
										tosiyoridata[tosiyoriID].namestring);
									//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
										DrawString(100,250,"それでもよろしいですか？",CRWHITE);
										DrawString(100,100,"キャンセル",CRGREEN);
										DrawString(400,100,"はい",CRGREEN);
										ScreenFlip() ;//裏画面を表画面にコピー
										while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
											Sleep(1);
										}
										while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
											Sleep(1);
										}
										while(1)
										{
											//キャンセル
											if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
												return;
											}
											//決定
											if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
												break;
											}
											// メッセージ処理
											if( ProcessMessage() == -1 ){mode=1;return ;}
											Sleep(1);
										}

										heyashoumetu(tosiyoriID,heyasentaku_id,tosiyoridata[tosiyoriID].shozokuheyaid);
										WaitTimer(200);
										return;
									}else{
										ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
										DrawString(100,200,"40部屋未満になってしまうので、この処理はできません。",CRWHITE);
										DrawString(100,300,"HIT ANY KEY",CRWHITE);
										ScreenFlip() ;//裏画面を表画面にコピー
										WaitKey();
									}
								}
							}
						}
					//部屋付だった場合→移籍先の部屋付になる、力士はそのまま
					}else{
						int motoheyaid=0;
						int simeiariflag=0;
						//継承者指名受けていないか確認
						for (i=0;i<TOSIYORISUU;i++){
							if (tosiyoridata[i].keishousha_tosiyoriid==tosiyoriID && tosiyoridata[i].shozokuheyaid>=0){
								simeiariflag=1;
								break;
							}
						}
						if (simeiariflag==0){
							//処理してよいかの確認
							ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
							DrawFormatString(100,200,CRWHITE,"%s親方が%s部屋から%s部屋に移籍します。",
							tosiyoridata[tosiyoriID].namestring,
							heyastring[tosiyoridata[tosiyoriID].shozokuheyaid],
							heyastring[heyasentaku_id]);
						//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
							DrawString(100,250,"それでもよろしいですか？",CRWHITE);
							DrawString(100,100,"キャンセル",CRGREEN);
							DrawString(400,100,"はい",CRGREEN);
							ScreenFlip() ;//裏画面を表画面にコピー
							while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
								Sleep(1);
							}
							while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
								Sleep(1);
							}
							while(1)
							{
								//キャンセル
								if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
									return;
								}
								//決定
								if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
									break;
								}
								// メッセージ処理
								if( ProcessMessage() == -1 ){mode=1;return ;}
								Sleep(1);
							}

							iseki_tandoku(tosiyoriID,heyasentaku_id,tosiyoridata[tosiyoriID].shozokuheyaid);//移籍する年寄ID、移籍先部屋ＩＤ、現部屋ＩＤ
							WaitTimer(200);
							return;
						}else{
							ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
							DrawString(100,200,"継承者に指定されているので移籍できません。",CRWHITE);
							DrawString(100,300,"HIT ANY KEY",CRWHITE);
							ScreenFlip() ;//裏画面を表画面にコピー
							WaitKey();
						}
					}
				}else{
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawString(100,200,"同じお部屋ですよ～",CRWHITE);
					DrawString(100,300,"HIT ANY KEY",CRWHITE);
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitKey();
				}
			}
			break;
		}

		if (heyasentaku_page==1){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				heyasentaku_page=0;
				heyasentaku_num=0;
				heyasentaku_id=heyasentaku_num+heyasentaku_page*40;
				page_oyakata=0;
				WaitTimer(200);
				goto loop;
			}
		}
		if (heyasentaku_page==0){
			if (get_mouseclick_buttonDOWN() == 1){//左リストUPボタンをクリック
				heyasentaku_page=1;
				heyasentaku_num=0;
				heyasentaku_id=heyasentaku_num+heyasentaku_page*40;
				page_oyakata=0;
				WaitTimer(200);
				goto loop;
			}
		}
		for (i=0;i<40;i++){
			if (get_mouseclick_list(i) == 1){//リスト上の部屋名をクリックしたら
				if (i+heyasentaku_page*40<HEYASUU){
					heyasentaku_num=i;
					heyasentaku_id=heyasentaku_num+heyasentaku_page*40;
					page_oyakata=0;
					WaitTimer(200);
					goto loop;
				}
			}
		}
		if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
			if (heyasentaku_page==1 && heyasentaku_num<2){
				heyasentaku_page=0;
				heyasentaku_num+=38;
				heyasentaku_id=heyasentaku_num+heyasentaku_page*40;
				page_oyakata=0;
				WaitTimer(100);
				goto loop;
			}else if (heyasentaku_num>1){
				heyasentaku_num=heyasentaku_num-2;
				heyasentaku_id=heyasentaku_num+heyasentaku_page*40;
				page_oyakata=0;
				WaitTimer(100);
				goto loop;
			}
		}
		if(CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
			if (heyasentaku_page==0 && heyasentaku_num>37){
				heyasentaku_page=1;
				heyasentaku_num-=38;
				heyasentaku_id=heyasentaku_num+heyasentaku_page*40;
				page_oyakata=0;
				WaitTimer(100);
				goto loop;
			}else if (heyasentaku_num<38){
				if (!(heyasentaku_page==1 && heyasentaku_num>11)){
					heyasentaku_num=heyasentaku_num+2;
					heyasentaku_id=heyasentaku_num+heyasentaku_page*40;
					page_oyakata=0;
					WaitTimer(100);
					goto loop;
				}
			}
		}
		if( CheckHitKey_test(KEY_INPUT_RIGHT)){//→キー
			if ((heyasentaku_num+2)%2==0 ){
				heyasentaku_num=heyasentaku_num+1;
				heyasentaku_id=heyasentaku_num+heyasentaku_page*40;
				page_oyakata=0;
				WaitTimer(100);
				goto loop;
			}
		}
		if( CheckHitKey_test(KEY_INPUT_LEFT)){//←キー
			if ((heyasentaku_num+2)%2==1 ){
				heyasentaku_num=heyasentaku_num-1;
				heyasentaku_id=heyasentaku_num+heyasentaku_page*40;
				page_oyakata=0;
				WaitTimer(100);
				goto loop;
			}
		}
		if (heya_tosiyorisuu[heyasentaku_id]>11 || page_oyakata>0){
			//親方表示部分の頁数減少
			if (get_mouseclick(200,170+12*15,200+24,170+12*15+12)==1 ){
				if (page_oyakata>0){
					page_oyakata--;
				}
				WaitTimer(200);
				goto loop;
			}
			//親方表示部分の頁数増加
			if (get_mouseclick(296,170+12*15,296+24,170+12*15+12)==1 ){
				if (page_oyakata<39){
					page_oyakata++;
				}
				WaitTimer(200);
				goto loop;
			}
		}

		// メッセージ処理
		if( ProcessMessage() == -1 ){mode=1;return ;}
		Sleep(1);
	}

	return;
}

void Q_shoyuuhenkou(int tosiyoriID)
{

loop:
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString(100,200,"キャンセル",CRGREEN);
	DrawString(250,200,"親方から選ぶ",CRGREEN);
	DrawString(400,200,"現役力士から選ぶ",CRGREEN);
	if (tosiyoridata[tosiyoriID].keishousha_rikisiid>=0 || tosiyoridata[tosiyoriID].keishousha_tosiyoriid>=0){
		DrawString(400,150,"被所有状態を解消",CRGREEN);
	}
	ScreenFlip() ;//裏画面を表画面にコピー
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//キャンセル
		if (get_mouseclick(100,200,100+16*5,200+16)==1 ){
			break;
		}
		//親方から選ぶ
		if (get_mouseclick(250,200,250+16*6,200+16)==1 ){
			//ここにルーチン名
			oyakatasentaku(tosiyoriID);
			WaitTimer(200);
			return;
		}
		//現役力士から選ぶ
		if (get_mouseclick(400,200,400+16*8,200+16)==1 ){
			//ここにルーチン名
			genekirikisisentaku(tosiyoriID);
			WaitTimer(200);
			return;
		}
		//被所有状態を解消を選ぶ
		if (get_mouseclick(400,150,400+16*8,150+16)==1 ){
			if (tosiyoridata[tosiyoriID].keishousha_rikisiid>=0 || tosiyoridata[tosiyoriID].keishousha_tosiyoriid>=0){

				//処理してよいかの確認
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawFormatString(100,200,CRWHITE,"年寄株%sの所有者・継承者をリセットします。",
				tosiyoridata[tosiyoriID].namestring);
			//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
				DrawString(100,250,"それでもよろしいですか？",CRWHITE);
				DrawString(100,100,"キャンセル",CRGREEN);
				DrawString(400,100,"はい",CRGREEN);
				ScreenFlip() ;//裏画面を表画面にコピー
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
				}
				while(1)
				{
					//キャンセル
					if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
						return;
					}
					//決定
					if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 ){mode=1;return ;}
					Sleep(1);
				}

				tosiyorisuukakunin();

				//留保をとる
				tosiyoridata[tosiyoriID].keishousha_rikisiid=-1;
				tosiyoridata[tosiyoriID].keishousha_tosiyoriid=-1;

				tosiyorisuukakunin();

				tosiyorihyoujifilekakikomi(tosiyoriID);

				FILE *fp;
				//eventlog書き込み/////////////////////////////////////////
				fp = fopen("data/eventlog.txt","a");
				// オープンできなかったらここで終了
				if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
				fprintf(fp,"年寄株%sの被所有状態を解消しました(編集)\n",
				tosiyoridata[tosiyoriID].namestring);
				//クローズ
				fclose(fp);
				if( ProcessMessage() == -1 ){mode=1;return ;}
				////////////////////////////////////////////////////////////
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawFormatString(100,200,CRWHITE,"年寄株%sの被所有状態を解消しました",
				tosiyoridata[tosiyoriID].namestring);
				DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				//////////////////////////////////////////////////////////////

				return;
			}
		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){mode=1;return ;}
		Sleep(1);
	}
	return;
}


void categorynyuuryoku(int tosiyoriID)
{
	char nyuuryokustring[12];
	int kaeri;
	int i;
	for (i=0;i<12;i++){
		nyuuryokustring[i]=0;
	}
	//1Ａカテ、2Ｂカテ、3Ｃカテ、4一代年寄、5元横綱５年期間限定一代年寄、6元大関3年期間限定一代年寄を入力
	if (tosiyoriID<106){
		ClearDrawScreen();
		DrawFormatString(187,417-48-32,CRWHITE,"現在：%d",tosiyoridata[tosiyoriID].category);
		DrawFormatString(187,417-16-32,CRWHITE,"年寄　%sの",tosiyoridata[tosiyoriID].namestring);
		DrawString(187,417-32,"カテゴリーを数字1-3で入力してください。ESCでそのまま。",CRWHITE);
		DrawString(187,417-16,"1Ａカテ、2Ｂカテ、3Ｃカテ",CRWHITE);
		DrawString(187,433,"ENTERキーで確定です。",CRWHITE);
		DrawString(187,449,"カテゴリー　＞　　　　　",CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		kaeri=KeyInputNumber( 310 , 449 , 3 , 1 , TRUE );
		if (kaeri==3+1){
			return;
		}
		tosiyoridata[tosiyoriID].category=kaeri;
	}else if(tosiyoriID>=200 && tosiyoriID<300){
		tosiyoridata[tosiyoriID].category=4;
	}else{
		ClearDrawScreen();
		DrawFormatString(187,417-48-32,CRWHITE,"現在：%d",tosiyoridata[tosiyoriID].category);
		DrawFormatString(187,417-16-32,CRWHITE,"年寄　%sの",tosiyoridata[tosiyoriID].namestring);
		DrawString(187,417-32,"カテゴリーを数字5か6で入力してください。ESCでそのまま。",CRWHITE);
		DrawString(187,417-16,"5元横綱５年期間限定、6元大関3年期間限定",CRWHITE);
		DrawString(187,433,"ENTERキーで確定です。",CRWHITE);
		DrawString(187,449,"カテゴリー　＞　　　　　",CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		kaeri=KeyInputNumber( 310 , 449 , 6 , 5 , TRUE );
		if (kaeri==6+1){
			return;
		}
		tosiyoridata[tosiyoriID].category=kaeri;
	}
	tosiyorisuukakunin();
	return;
}


void jinbounyuuryoku(int tosiyoriID)
{
	char nyuuryokustring[12];
	int kaeri;
	int i;
	for (i=0;i<12;i++){
		nyuuryokustring[i]=0;
	}
	//人望入力
	ClearDrawScreen();
	DrawFormatString(187,417-48,CRWHITE,"現在：%d",tosiyoridata[tosiyoriID].jinbou);
	DrawFormatString(187,417-16,CRWHITE,"年寄　%sの",tosiyoridata[tosiyoriID].namestring);
	DrawString(187,417,"人望を入力してください。",CRWHITE);
	DrawString(187,433,"ENTERキーで確定です。ESCでそのまま。",CRWHITE);
	DrawString(187,449,"　　人　望　＞　　　　　",CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	kaeri=KeyInputNumber( 310 , 449 , 9999999 , -9999999 , TRUE );
	if (kaeri==9999999+1){
		return;
	}
	tosiyoridata[tosiyoriID].jinbou=kaeri;
	tosiyorisuukakunin();
	return;
}

void agenyuuryoku(int tosiyoriID)
{
	char nyuuryokustring[12];
	int kaeri;
	int i;
	for (i=0;i<12;i++){
		nyuuryokustring[i]=0;
	}
	//現在年齢入力
	ClearDrawScreen();
	DrawFormatString(187,417-48,CRWHITE,"現在：%d",tosiyoridata[tosiyoriID].age);
	DrawFormatString(187,417-16,CRWHITE,"年寄　%sの",tosiyoridata[tosiyoriID].namestring);
	DrawString(187,417,"現在の年齢を入力してください。",CRWHITE);
	DrawString(187,433,"ENTERキーで確定です。ESCでそのまま。",CRWHITE);
	DrawString(187,449,"現在の年齢　＞　　　　　",CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	kaeri=KeyInputNumber( 310 , 449 , 999999 , 0 , TRUE );
	if (kaeri==999999+1){
		return;
	}
	tosiyoridata[tosiyoriID].age=kaeri;
	tosiyorisuukakunin();
	return;
}

int genekijisikonanyuuryoku(int tosiyoriID)
{
	char nyuuryokustring[12];
	int kaeri;
	int i;
	for (i=0;i<12;i++){
		nyuuryokustring[i]=0;
	}
	//現役時四股名入力
	ClearDrawScreen();
	DrawFormatString(187,417-48,CRWHITE,"現在：%s",tosiyoridata[tosiyoriID].sikona);
	if (tosiyoriID<106){
		DrawFormatString(187,417-16,CRWHITE,"年寄　%sの",tosiyoridata[tosiyoriID].namestring);
	}
	DrawString(187,417,"現役時の四股名を入力してください。(全角5文字以内)",CRWHITE);
	DrawString(187,433,"ENTERキーで確定です。ESCでそのまま。",CRWHITE);
	DrawString(187,449,"現役時四股名＞　　　　　",CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	while(1){
		kaeri=KeyInputString( 310 , 449 , 10 , nyuuryokustring , TRUE );
		if (kaeri==2){
			return -1;
		}
		if (strncmp(nyuuryokustring,"\0",1)!=0){
			strcpy(tosiyoridata[tosiyoriID].sikona,nyuuryokustring);
			if (tosiyoriID>=200){
				strcpy(tosiyoridata[tosiyoriID].namestring,nyuuryokustring);
			}
			break;
		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){
			mode=1;
			return -1 ;	// エラーが発生したらループを抜ける
		}
		Sleep(1);
	}
	tosiyorisuukakunin();
	return 0;
}

void sonzaisakusei(int tosiyoriID)
{
	int i;
	if (genekijisikonanyuuryoku(tosiyoriID)==-1){
		return;
	}
	agenyuuryoku(tosiyoriID);
	categorynyuuryoku(tosiyoriID);
	jinbounyuuryoku(tosiyoriID);

	tosiyoridata[tosiyoriID].rikisiid=-1;
	tosiyoridata[tosiyoriID].startyear=year;
	tosiyoridata[tosiyoriID].shozokuheyaid=myheyaid;//とりあえず
	for (i=0;i<ITIMONSUU;i++){
		if (itimondata[i].shuheyaid==tosiyoridata[tosiyoriID].shozokuheyaid){
			tosiyoridata[tosiyoriID].shozokuitimonid=i;
			break;
		}
	}
	tosiyoridata[tosiyoriID].sishouflag=0;
	tosiyoridata[tosiyoriID].jinbou=0;
	tosiyoridata[tosiyoriID].rijiflag=0;
	//tosiyoridata[tosiyoriID].keishousha_rikisiid;
	//tosiyoridata[tosiyoriID].keishousha_tosiyoriid;

	tosiyorisuukakunin();

	tosiyorihyoujifilekakikomi(tosiyoriID);

	FILE *fp;
	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"年寄株%sは元%sが襲名しました(編集)\n",
	tosiyoridata[tosiyoriID].namestring,
	tosiyoridata[tosiyoriID].sikona);
	fprintf(fp,"%s一門%s部屋に部屋付親方として所属します(編集)\n",
	itimondata[tosiyoridata[tosiyoriID].shozokuitimonid].namestring,
	heyastring[tosiyoridata[tosiyoriID].shozokuheyaid]);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(100,200,CRWHITE,"年寄株%sは元%sが襲名しました",
	tosiyoridata[tosiyoriID].namestring,
	tosiyoridata[tosiyoriID].sikona);
	DrawFormatString(100,230,CRWHITE,"%s一門%s部屋付になりました(手抜き処理m(__)m)",
	itimondata[tosiyoridata[tosiyoriID].shozokuitimonid].namestring,
	heyastring[tosiyoridata[tosiyoriID].shozokuheyaid]);
	DrawString( 250 , 272 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	//////////////////////////////////////////////////////////////

	return;
}

void tosiyorimeihenkou(int x)
{
	char tosiyorimeistring[12];
	int kaeri;
	int i;
	for (i=0;i<12;i++){
		tosiyorimeistring[i]=0;
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

	DrawString(187,100,"年寄の名称を変更した場合、",CRWHITE);
	DrawString(187,116,"部屋の師匠である場合には部屋名も変わり、",CRWHITE);
	DrawString(187,132,"一門主である場合には一門名も変わります",CRWHITE);

	DrawFormatString(187,417-16,CRWHITE,"年寄　%s",tosiyoridata[x].namestring);
	DrawString(187,417,"の名称を変更します。(全角5文字以内)",CRWHITE);
	DrawString(187,433,"ENTERキーで確定、ESCキーでキャンセルです。",CRWHITE);
	DrawString(187,449,"新しい年寄名＞　　　　　",CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	while(1){
	kaeri=KeyInputString( 310 , 449 , 10 , tosiyorimeistring , TRUE );
		if (kaeri==2){
			break;
		}
		if (strncmp(tosiyorimeistring,"\0",1)!=0){
			strcpy(tosiyoridata[x].namestring,tosiyorimeistring);
			if (tosiyoridata[x].sishouflag==1
				&& tosiyoridata[x].shozokuheyaid>=0){
				strcpy(heyastring[tosiyoridata[x].shozokuheyaid],tosiyoridata[x].namestring);
				if (tosiyoridata[x].shozokuitimonid>=0
					&& itimondata[tosiyoridata[x].shozokuitimonid].shuheyaid==tosiyoridata[x].shozokuheyaid){
					strcpy(itimondata[tosiyoridata[x].shozokuitimonid].namestring,tosiyoridata[x].namestring);
				}
			}
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


void tosiyoridatahyoji(int tosiyoriID)
{
	int i,ii;
	int gyousuu=0;
	int gyousuu_max=0;
	
	int year_tosiyori=0;
	int month_tosiyori=0;
	int rikisiid_tosiyori=0;
	char sikona_tosiyori[12];
	int keishousha_rikisiid_tosiyori=0;
	char namestring_keishousha_rikisiid_tosiyori[12];
	char shozokuitimonid_tosiyori=0;
	char namestring_itimon_tosiyori[12];
	char shozokuheyaid_tosiyori=0;
	char namestring_heya_tosiyori[12];
	char sishouflag_tosiyori=0;
	int keishousha_tosiyoriid_tosiyori=0;
	char namestring_keishousha_tosiyoriid_tosiyori[12];

	char r_heyastring[HEYASUU][12];//(54部屋分,全角５文字まで)相撲部屋
	char temp_filename[MAX_PATH];
	char temp_filename2[MAX_PATH];
	char akikabusuu=0;
	char ryuuhosuu=0;

	gyousuu_max=15;

	for (i=0;i<12;i++){
		sikona_tosiyori[i]=0;
		namestring_keishousha_rikisiid_tosiyori[i]=0;
		namestring_itimon_tosiyori[i]=0;
		namestring_heya_tosiyori[i]=0;
		namestring_keishousha_tosiyoriid_tosiyori[i]=0;
	}
	for (i=0;i<MAX_PATH;i++){
		temp_filename[i]=0;
		temp_filename2[i]=0;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	for (i=0;i<HEYASUU;i++){
		for (ii=0;ii<12;ii++){
			r_heyastring[i][ii]=0;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

	FILE *fp;
	FILE *fp2;

	//しばらくお待ちください表示
	ClearDrawScreen();
	DrawString(100,300,"表示準備中です",CRWHITE);
	DrawString(100,350,"しばらくお待ちください",CRWHITE);
	ScreenFlip();
	//空き名跡数検索
	akikabusuu=0;ryuuhosuu=0;
	for (i=0;i<106;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (tosiyoridata[i].shozokuheyaid==-1){
			akikabusuu++;
			if (tosiyoridata[i].keishousha_rikisiid>=0 || tosiyoridata[i].keishousha_tosiyoriid>=0){
				ryuuhosuu++;
			}
		}
	}
	//リストに年寄ID順で年寄名を表示
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	game_main_backscreen();//基本画面表示
	DrawBox(3,76,183,475,CRTAB,TRUE);

	DrawBox(x1[tosiyorisentaku_num],y1[tosiyorisentaku_num],x2[tosiyorisentaku_num],y2[tosiyorisentaku_num],CRKEIJIBANON,TRUE);//クリックしたところを強調
	for(ii=0;ii<40;ii++){
//		if (ii+tosiyorisentaku_page*40<106){
		if (ii+tosiyorisentaku_page*40<TOSIYORISUU){
			DrawFormatStringToHandle(x1[ii],y1[ii],CRBLACK,FontHandle12,"%2d %s",ii+tosiyorisentaku_page*40,tosiyoridata[ii+tosiyorisentaku_page*40].namestring);
			//DrawFormatString(x1[ii],y1[ii],CRBLACK,"%s",tosiyoridata[ii+tosiyorisentaku_page*40].namestring);
		}
	}
	if (superrikisisuu[7]==1){
		if (ryuuhosuu>0){
			DrawFormatString(187,369,CRWHITE,"空き名跡数 %d(うち所有者あり %d)　相場%dp",akikabusuu,ryuuhosuu,kabusouba());
		}else{
			DrawFormatString(187,369,CRWHITE,"空き名跡数 %d　相場%dp",akikabusuu,kabusouba());
		}
	}else{
		if (ryuuhosuu>0){
			DrawFormatString(187,369,CRWHITE,"空き名跡数 %d(うち所有者あり %d)",akikabusuu,ryuuhosuu);
		}else{
			DrawFormatString(187,369,CRWHITE,"空き名跡数 %d",akikabusuu);
		}
	}
	DrawString(187,369+16,"↑↓←→で左のリストから年寄を選択できます。",CRWHITE);
	if (tosiyorisentaku_page==0){
		DrawString(187,385+16,"一番下のときに↓で次ページ",CRWHITE);
	}else{
		DrawString(187,385+16,"一番上のときに↑で前ページ",CRWHITE);
	}


	//メイン表示
	DrawFormatString(187,24,CRWHITE,"ID%d %s",tosiyoriID,tosiyoridata[tosiyoriID].namestring);
	if (tosiyoridata[tosiyoriID].keishousha_rikisiid>=0 
		&& tosiyoridata[tosiyoriID].keishousha_rikisiid<RIKISISUU){//勘違いして通算力士IDを代入してしまっている可能性があるため念のため
		DrawFormatString(410,44,CRGREEN,"所有者 %s",namestring[tosiyoridata[tosiyoriID].keishousha_rikisiid]);
	}
	for (i=0;i<TOSIYORISUU;i++){
		if (tosiyoridata[i].keishousha_tosiyoriid==tosiyoriID){ 
			DrawFormatString(410,44,CRWHITE,"%s部屋の後継者",tosiyoridata[i].namestring);
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	DrawString(330,24,"現襲名者",CRWHITE);
	if (tosiyoridata[tosiyoriID].shozokuheyaid>=0){
		if (tosiyoridata[tosiyoriID].rikisiid>=0){
			DrawFormatString(410,24,CRGREEN,"元 %s(%d才)",tosiyoridata[tosiyoriID].sikona,tosiyoridata[tosiyoriID].age);
		}else{
			DrawFormatString(410,24,CRWHITE,"元 %s(%d才)",tosiyoridata[tosiyoriID].sikona,tosiyoridata[tosiyoriID].age);
		}
		if (tosiyoridata[tosiyoriID].shozokuitimonid>=0){
			if (itimondata[tosiyoridata[tosiyoriID].shozokuitimonid].shuheyaid==tosiyoridata[tosiyoriID].shozokuheyaid
				&& tosiyoridata[tosiyoriID].sishouflag==1){
				DrawString(187,44,"所属一門",CRWHITE);
				DrawFormatString(270,44,CRGREEN,"%s(一門主)",itimondata[tosiyoridata[tosiyoriID].shozokuitimonid].namestring);
			}else{
				DrawString(187,44,"所属一門",CRWHITE);
				DrawFormatString(270,44,CRGREEN,"%s",itimondata[tosiyoridata[tosiyoriID].shozokuitimonid].namestring);
			}
		}
		DrawString(187,60,"所属部屋",CRWHITE);
		if (tosiyoridata[tosiyoriID].sishouflag==1){
			DrawFormatString(270,60,CRGREEN,"%s部屋師匠",heyastring[tosiyoridata[tosiyoriID].shozokuheyaid]);
		}else{
			DrawFormatString(270,60,CRGREEN,"%s部屋付き",heyastring[tosiyoridata[tosiyoriID].shozokuheyaid]);
		}
		if (tosiyoridata[tosiyoriID].category==1){
			DrawFormatStringToHandle(187,78,CRWHITE,FontHandle12,"人望:%d 　カテゴリー:A",tosiyoridata[tosiyoriID].jinbou);
		}
		if (tosiyoridata[tosiyoriID].category==2){
			DrawFormatStringToHandle(187,78,CRWHITE,FontHandle12,"人望:%d 　カテゴリー:B",tosiyoridata[tosiyoriID].jinbou);
		}
		if (tosiyoridata[tosiyoriID].category==3){
			DrawFormatStringToHandle(187,78,CRWHITE,FontHandle12,"人望:%d 　カテゴリー:C",tosiyoridata[tosiyoriID].jinbou);
		}
		if (tosiyoridata[tosiyoriID].category==4){
			DrawFormatStringToHandle(187,78,CRWHITE,FontHandle12,"人望:%d 　カテゴリー:功績顕著一代",tosiyoridata[tosiyoriID].jinbou);
		}
		if (tosiyoridata[tosiyoriID].category==5){
			DrawFormatStringToHandle(187,78,CRWHITE,FontHandle12,"人望:%d 　カテゴリー:期間限定横綱5年",tosiyoridata[tosiyoriID].jinbou);
		}
		if (tosiyoridata[tosiyoriID].category==6){
			DrawFormatStringToHandle(187,78,CRWHITE,FontHandle12,"人望:%d 　カテゴリー:期間限定大関3年",tosiyoridata[tosiyoriID].jinbou);
		}

	}else{
		DrawString(410,24,"なし(空き株)",CRWHITE);
	}

	if ((tosiyoridata[tosiyoriID].rijiflag&0x0f)>0 && (tosiyoridata[tosiyoriID].rijiflag&0x0f)<11){
		DrawFormatString(430,60,CRRED,"%s",namestring_riji[(tosiyoridata[tosiyoriID].rijiflag&0x0f)-1]);
	}
	if ((tosiyoridata[tosiyoriID].rijiflag&0x0f)==11){
		DrawString(430,60,"副理事",CRWHITE);
	}
	if ((tosiyoridata[tosiyoriID].rijiflag&0x0f)==12){
		DrawString(430,60,"役員待遇委員",CRWHITE);
	}
	if ((tosiyoridata[tosiyoriID].rijiflag&0x0f)==13){
		DrawString(430,60,"委員",CRWHITE);
	}
	if ((tosiyoridata[tosiyoriID].rijiflag&0x0f)==14){
		DrawString(430,60,"主任",CRWHITE);
	}
	if ((tosiyoridata[tosiyoriID].rijiflag&0x0f)==0){
		DrawString(430,60,"平年寄",CRWHITE);
	}


	if (superrikisisuu[2]==0 && superrikisisuu[6]==0
	&& (tosiyoriID<106 || tosiyoriID>=200)){
		DrawString(440,345,"編集",CRGREEN);
	}
	if (tosiyorisentaku_id<106){
		DrawString(545,345,"年寄名変更",CRGREEN);
	}

	DrawFormatString(3,78,CRBLACK,"%d／%dページ",tosiyorisentaku_page+1,(int)((TOSIYORISUU-1)/40)+1);

	DrawStringToHandle(30,60,"【年寄画面です】",CRWHITE,FontHandle12);

//	DrawString(200,460,"相撲部屋へ",CRGREEN);
//	DrawString(300,460,"力士情報へ",CRGREEN);
	DrawString(200,460,"一門画面",CRGREEN);
	DrawString(300,460,"年寄画面",CRWHITE);

	//SetFontSize(12);
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける


	if (tosiyoriID<106){
		DrawStringToHandle(187,92,"襲名者一覧",CRWHITE,FontHandle12);
		DrawStringToHandle(187,385+16+16,"襲名者一覧は",CRWHITE,FontHandle12);
		DrawStringToHandle(187,385+16+16+12,"年月、現役時四股名、()は所有者か継承予定者、所属一門、所属部屋",CRWHITE,FontHandle12);
		DrawStringToHandle(187,385+16+16+12+12,"の順で表示しています",CRWHITE,FontHandle12);

		//ここからメイン表示////////////////////////
		gyousuu=0;

		//ファイルオープン
		sprintf(temp_filename,"data/dat/hyoji_tosiyori%d.dat\0",tosiyoriID);
		fp = fopen(temp_filename,"rb");
		if( fp == NULL ){
			ClearDrawScreen();DrawBox(0,0,639,479,CRBACK,TRUE);DrawString( 250 , 240 - 32 , "sub_itimon~hyoji_tosiyori%d.datファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip();WaitKey();mode=1;return;
		}

		while(1){//
			//ここから表示用読み込み
			if(fread(&year_tosiyori,sizeof(year_tosiyori),1,fp)<1){//EOFor読み取り失敗
				break;
			}else{
				fread(&month_tosiyori,sizeof(month_tosiyori),1,fp);
				fread(&rikisiid_tosiyori,sizeof(tosiyoridata[0].rikisiid),1,fp);
				fread(sikona_tosiyori,sizeof(tosiyoridata[0].sikona),1,fp);
				fread(&keishousha_rikisiid_tosiyori,sizeof(tosiyoridata[0].keishousha_rikisiid),1,fp);
				fread(namestring_keishousha_rikisiid_tosiyori,sizeof(namestring[tosiyoridata[0].keishousha_rikisiid]),1,fp);
				fread(&shozokuitimonid_tosiyori,sizeof(tosiyoridata[0].shozokuitimonid),1,fp);
				fread(namestring_itimon_tosiyori,sizeof(itimondata[tosiyoridata[0].shozokuitimonid].namestring),1,fp);
				fread(&shozokuheyaid_tosiyori,sizeof(tosiyoridata[0].shozokuheyaid),1,fp);
				fread(namestring_heya_tosiyori,sizeof(heyastring[tosiyoridata[0].shozokuheyaid]),1,fp);
				fread(&sishouflag_tosiyori,sizeof(tosiyoridata[0].sishouflag),1,fp);
				fread(&keishousha_tosiyoriid_tosiyori,sizeof(tosiyoridata[0].keishousha_rikisiid),1,fp);
				fread(namestring_keishousha_tosiyoriid_tosiyori,sizeof(namestring[tosiyoridata[0].keishousha_rikisiid]),1,fp);
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

			//ここで表示
			if (shozokuheyaid_tosiyori==-1){
				//空き株の表示
				if (keishousha_rikisiid_tosiyori>=0){
					if (gyousuu<(page_tosiyori+1)*gyousuu_max && gyousuu>=page_tosiyori*gyousuu_max){

						DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%d月 空き株(%s)",
						year_tosiyori,month_tosiyori,
						namestring_keishousha_rikisiid_tosiyori);
					}
				}else if (keishousha_tosiyoriid_tosiyori!=-1){
					if (gyousuu<(page_tosiyori+1)*gyousuu_max && gyousuu>=page_tosiyori*gyousuu_max){
						DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%d月 空き株(年寄%s)",
						year_tosiyori,month_tosiyori,
						namestring_keishousha_tosiyoriid_tosiyori);
					}
				}else{
					if (gyousuu<(page_tosiyori+1)*gyousuu_max && gyousuu>=page_tosiyori*gyousuu_max){
						DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%d月 空き株",
						year_tosiyori,month_tosiyori);
					}
				}
			}else if (sishouflag_tosiyori==1){
				if (keishousha_rikisiid_tosiyori>=0){
					if (gyousuu<(page_tosiyori+1)*gyousuu_max && gyousuu>=page_tosiyori*gyousuu_max){
						DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%d月 %s(%s)  %s一門 %s部屋師匠",
						year_tosiyori,month_tosiyori,sikona_tosiyori,
						namestring_keishousha_rikisiid_tosiyori,
						namestring_itimon_tosiyori,
						namestring_heya_tosiyori
						);
					}
				}else if (keishousha_tosiyoriid_tosiyori!=-1){
					if (gyousuu<(page_tosiyori+1)*gyousuu_max && gyousuu>=page_tosiyori*gyousuu_max){
						DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%d月 %s(年寄%s)  %s一門 %s部屋師匠",
						year_tosiyori,month_tosiyori,sikona_tosiyori,
						namestring_keishousha_tosiyoriid_tosiyori,
						namestring_itimon_tosiyori,
						namestring_heya_tosiyori
						);
					}
				}else{
					if (gyousuu<(page_tosiyori+1)*gyousuu_max && gyousuu>=page_tosiyori*gyousuu_max){
						DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%d月 %s  %s一門 %s部屋師匠",
						year_tosiyori,month_tosiyori,sikona_tosiyori,
						namestring_itimon_tosiyori,
						namestring_heya_tosiyori
						);
					}
				}
			}else{
				if (keishousha_rikisiid_tosiyori>=0){
					if (gyousuu<(page_tosiyori+1)*gyousuu_max && gyousuu>=page_tosiyori*gyousuu_max){
						DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%d月 %s(%s)  %s一門 %s部屋付き",
						year_tosiyori,month_tosiyori,sikona_tosiyori,
						namestring_keishousha_rikisiid_tosiyori,
						namestring_itimon_tosiyori,
						namestring_heya_tosiyori
						);
					}
				}else if (keishousha_tosiyoriid_tosiyori!=-1){
					if (gyousuu<(page_tosiyori+1)*gyousuu_max && gyousuu>=page_tosiyori*gyousuu_max){
						DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%d月 %s(年寄%s)  %s一門 %s部屋付き",
						year_tosiyori,month_tosiyori,sikona_tosiyori,
						namestring_keishousha_tosiyoriid_tosiyori,
						namestring_itimon_tosiyori,
						namestring_heya_tosiyori
						);
					}
				}else{
					if (gyousuu<(page_tosiyori+1)*gyousuu_max && gyousuu>=page_tosiyori*gyousuu_max){
						DrawFormatStringToHandle(187,104+(gyousuu%gyousuu_max)*16,CRWHITE,FontHandle12,"%d年%d月 %s  %s一門 %s部屋付き",
						year_tosiyori,month_tosiyori,sikona_tosiyori,
						namestring_itimon_tosiyori,
						namestring_heya_tosiyori
						);
					}
				}
			}
			gyousuu++;
		}
		//ファイルクローズ
		fclose(fp);

		//if (gyousuu>=gyousuu_max){
		DrawFormatStringToHandle(200,170+12*15,CRGREEN,FontHandle12,"前頁　%dページ　次頁",page_tosiyori+1);
		//}
	}

	draw_buttonUP();
	draw_buttonDOWN();
	//draw_buttonB_mouse();

	//SetFontSize(16);
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//ScreenFlip() ;//裏画面を表画面にコピー

	return;
}


void menu_tosiyori(void)
{
	int i;
	int ii;
	int iii;
	int count=0;

	if (mode==0){
		menuflag=1;
		return;
	}

	tosiyoridatahyoji(tosiyorisentaku_id);
	ScreenFlip() ;//裏画面を表画面にコピー


	//リスト上で部屋名をクリックした場合に一門詳細情報を表示
		// キー入力待ち(この一文を入れないとうまくいかないみたい)
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		buttonA_mouse_change();
		buttonB_mouse_change();
		buttonC_mouse_change();
		buttonD_mouse_change();
		buttonE_mouse_change();
		buttonF_mouse_change();
		buttonG_mouse_change();
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		buttonA_mouse_change();
		buttonB_mouse_change();
		buttonC_mouse_change();
		buttonD_mouse_change();
		buttonE_mouse_change();
		buttonF_mouse_change();
		buttonG_mouse_change();
		Sleep(1);
	}
	while(1)
	{
		//所属一門名クリックしたら一門画面へ
		if (tosiyoridata[tosiyorisentaku_id].shozokuitimonid>=0 && tosiyoridata[tosiyorisentaku_id].shozokuitimonid<ITIMONSUU){
			if (get_mouseclick(270,44,270+16*5,44+16)){
				itimonsentaku_page=(int)((tosiyoridata[tosiyorisentaku_id].shozokuitimonid+40)/40)-1;
				itimonsentaku_num=(tosiyoridata[tosiyorisentaku_id].shozokuitimonid+40)%40;
				itimonsentaku_id=tosiyoridata[tosiyorisentaku_id].shozokuitimonid;
				menuflag=11;
				return;
			}
		}
		//現襲名者欄クリックしたら旧引退力士表示へ
		if (tosiyoridata[tosiyorisentaku_id].shozokuheyaid>=0
			&& tosiyoridata[tosiyorisentaku_id].rikisiid>=0){
			if (get_mouseclick(410,24,410+16*7,24+16)){
				retirerikisi_rikisiid(tosiyoridata[tosiyorisentaku_id].rikisiid);//subsubsub.cpp
				tosiyoridatahyoji(tosiyorisentaku_id);//年寄データを表示
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitTimer(200);
			}
		}
		//所属部屋名クリックしたら相撲部屋画面へ
		if (tosiyoridata[tosiyorisentaku_id].shozokuheyaid>=0 && tosiyoridata[tosiyorisentaku_id].shozokuheyaid<HEYASUU){
			if (get_mouseclick(270,60,270+16*7,60+16)){
				heyasentaku_page=(int)((tosiyoridata[tosiyorisentaku_id].shozokuheyaid+40)/40)-1;
				heyasentaku_num=(tosiyoridata[tosiyorisentaku_id].shozokuheyaid+40)%40;
				heyasentaku_id=tosiyoridata[tosiyorisentaku_id].shozokuheyaid;
				menuflag=2;
				return;
			}
		}
		//所有者欄クリックしたら力士情報画面へ
		if (tosiyoridata[tosiyorisentaku_id].keishousha_rikisiid>=0 
			&& tosiyoridata[tosiyorisentaku_id].keishousha_rikisiid<RIKISISUU){//勘違いして通算力士IDを代入してしまっている可能性があるため念のため
			if (get_mouseclick(410,44,410+16*9,44+16)){
				rikisisentaku_num=((rikisidata[tosiyoridata[tosiyorisentaku_id].keishousha_rikisiid].bandukejun+20)%20)*2;
				rikisisentaku_page=(int)((rikisidata[tosiyoridata[tosiyorisentaku_id].keishousha_rikisiid].bandukejun+20)/20)-1;
				rikisisentaku_id=tosiyoridata[tosiyorisentaku_id].keishousha_rikisiid;
				bandukejun_or_jiheyaflag=0;
				torikumi_or_seisekiflag=3;
				menuflag=3;
				return;
			}
		}
		//編集
		if (superrikisisuu[2]==0 && superrikisisuu[6]==0
		&& (tosiyorisentaku_id<106 || tosiyorisentaku_id>=200)){
			if (get_mouseclick(440,345,440+16*5,345+16)==1 ){
				Q_tosiyorihenshuu(tosiyorisentaku_id);
				tosiyoridatahyoji(tosiyorisentaku_id);//年寄データを表示
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitTimer(200);
			}
		}
		//名称変更
		if (tosiyorisentaku_id<106){
			if (get_mouseclick(545,345,545+16*5,345+16)==1 ){
				tosiyorimeihenkou(tosiyorisentaku_id);
				tosiyoridatahyoji(tosiyorisentaku_id);//年寄データを表示
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitTimer(200);
			}
		}
		//歴代表示のページ数減少
		if (get_mouseclick(200,170+12*15,200+24,170+12*15+12)==1 ){
			if (page_tosiyori>0){
				page_tosiyori--;
				tosiyoridatahyoji(tosiyorisentaku_id);//年寄データを表示
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitTimer(200);
			}
		}
		//歴代表示のページ数増加
		if (get_mouseclick(296,170+12*15,296+24,170+12*15+12)==1 ){
			if (page_tosiyori<1000){
				page_tosiyori++;
				tosiyoridatahyoji(tosiyorisentaku_id);//年寄データを表示
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitTimer(200);
			}
		}
		if (tosiyorisentaku_page>0){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				tosiyorisentaku_page--;
				tosiyorisentaku_num=0;
				tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
				tosiyoridatahyoji(tosiyorisentaku_id);//年寄データを表示
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitTimer(200);
			}
		}
//		if (tosiyorisentaku_page<(int)((106-1)/40)){
		if (tosiyorisentaku_page<(int)((TOSIYORISUU-1)/40)){
			if (get_mouseclick_buttonDOWN() == 1){//左リストUPボタンをクリック
				tosiyorisentaku_page++;
				tosiyorisentaku_num=0;
				tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
				tosiyoridatahyoji(tosiyorisentaku_id);//年寄データを表示
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitTimer(200);
			}
		}
		for (i=0;i<40;i++){
			if (get_mouseclick_list(i) == 1){//リスト上の年寄名をクリックしたら
				if (i+tosiyorisentaku_page*40<TOSIYORISUU){
					tosiyorisentaku_num=i;
					tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
					tosiyoridatahyoji(tosiyorisentaku_id);//年寄データを表示
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitTimer(200);
				}
			}
		}
		if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
			if (tosiyorisentaku_page>0 && tosiyorisentaku_num<2){
				tosiyorisentaku_page--;
				tosiyorisentaku_num+=38;
				tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
				tosiyoridatahyoji(tosiyorisentaku_id);//年寄データを表示
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitTimer(200);
			}else if (tosiyorisentaku_num>1){
				tosiyorisentaku_num=tosiyorisentaku_num-2;
				tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
				tosiyoridatahyoji(tosiyorisentaku_id);//年寄データを表示
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitTimer(200);
			}
		}
		if(CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
			if (tosiyorisentaku_page<(int)((TOSIYORISUU-1)/40) && tosiyorisentaku_num>37){
				tosiyorisentaku_page++;
				tosiyorisentaku_num-=38;
				tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
				tosiyoridatahyoji(tosiyorisentaku_id);//年寄データを表示
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitTimer(200);
			}else if (tosiyorisentaku_num<38){
				if (!(tosiyorisentaku_page==2 && tosiyorisentaku_num>23)){
					tosiyorisentaku_num=tosiyorisentaku_num+2;
					tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
					tosiyoridatahyoji(tosiyorisentaku_id);//部屋データを表示
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitTimer(200);
				}
			}
		}
		if( CheckHitKey_test(KEY_INPUT_RIGHT)){//→キー
			if ((tosiyorisentaku_num+2)%2==0 ){
					tosiyorisentaku_num=tosiyorisentaku_num+1;
					tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
					tosiyoridatahyoji(tosiyorisentaku_id);//部屋データを表示
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitTimer(200);
			}
		}
		if( CheckHitKey_test(KEY_INPUT_LEFT)){//←キー
			if ((tosiyorisentaku_num+2)%2==1 ){
				tosiyorisentaku_num=tosiyorisentaku_num-1;
				tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
				tosiyoridatahyoji(tosiyorisentaku_id);//部屋データを表示
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitTimer(200);
			}
		}
		if (get_mouseclick(200,460,200+16*5,460+16) == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=11;
			return;
		}
/*
		if (get_mouseclick(300,460,300+16*5,460+16) == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=3;
			return;
		}
		if (get_mouseclick(400,460,400+16*5,460+16) == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=11;
			return;
		}
*/
		if (get_mouseclick_buttonA() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=1;
			break;
		}
		if (get_mouseclick_buttonB() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=2;
			break;
		}
		if (get_mouseclick_buttonC() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=3;
			break;
		}
		if (get_mouseclick_buttonD() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=4;
			break;
		}
		if (get_mouseclick_buttonE() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=5;
			break;
		}
		if (get_mouseclick_buttonF() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=6;
			break;
		}
		if (get_mouseclick_buttonG() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=7;
			break;
		}
		if( CheckHitKey_test(KEY_INPUT_NUMPADENTER) || CheckHitKey_test( KEY_INPUT_RETURN)){//ENTERキーでループから抜けメニュー画面へ
			menuflag=7;
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
	
	return;
}




void itimondatahyoji(char flag,int itimonID){

	int i;
	int ii;
	int count;
	int iii;
	int temp_narabekaeyou[TOSIYORISUU];//並べ替え用に並べ替えたい要素を入れる変数
	int jinboujun_tosiyoriid[TOSIYORISUU];
	int temp_tosiyoriid=0;
	int temp_tosiyoriid2=0;

	//しばらくお待ちください表示
	ClearDrawScreen();
	DrawString(100,300,"表示準備中です",CRWHITE);
	DrawString(100,350,"しばらくお待ちください",CRWHITE);
	ScreenFlip();

	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	game_main_backscreen();//基本画面表示
/*
	DrawBox(0,0,640,480,CRLINE,TRUE);//大枠描画
	DrawBox(3,3,637,477,CRBACK,TRUE);
	DrawBox(0,21,187,480,CRLINE,TRUE);
	DrawBox(3,24,184,477,CRBACK,TRUE);
	DrawBox(184,21,640,369,CRLINE,TRUE);
	DrawBox(187,24,637,366,CRBACK,TRUE);
	DrawBox(184,366,640,480,CRLINE,TRUE);
	DrawBox(187,369,637,477,CRBACK,TRUE);
	DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分
	
	DrawLine(3,55,183,55,CRLINE);
*/
	DrawBox(3,76,183,475,CRTAB,TRUE);
	DrawBox(x1[itimonsentaku_num],y1[itimonsentaku_num],x2[itimonsentaku_num],y2[itimonsentaku_num],CRKEIJIBANON,TRUE);//クリックしたところを強調
	for(ii=0;ii<40;ii++){
		if (ii+itimonsentaku_page*40<ITIMONSUU){
			DrawFormatString(x1[ii],y1[ii],CRBLACK,"%s",itimondata[ii+itimonsentaku_page*40].namestring);
		}
	}

	DrawStringToHandle(30,60,"【一門画面です】",CRWHITE,FontHandle12);

	DrawString(187,369,"一門画面です。",CRWHITE);
	DrawString(187,369+16,"↑↓←→で左のリストから一門を選択できます。",CRWHITE);
	if (itimonsentaku_page==0){
		DrawString(187,385+16,"一番下のときに↓で次ページ",CRWHITE);
	}else{
		DrawString(187,385+16,"一番上のときに↑で前ページ",CRWHITE);
	}


	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
//	SetFontSize(12);
//	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	for (i=0;i<TOSIYORISUU;i++){
		if (tosiyoridata[i].shozokuheyaid!=-1 && tosiyoridata[i].shozokuitimonid==itimonID && tosiyoridata[i].sishouflag==1){
			if (itimondata[tosiyoridata[i].shozokuitimonid].shuheyaid==tosiyoridata[i].shozokuheyaid){
				if (tosiyoridata[i].rikisiid>=0){
					if (flag==0){
						DrawFormatStringToHandle(530,140,CRGREEN,FontHandle12,"(%s)",tosiyoridata[i].sikona);
					}else{
						DrawFormatStringToHandle(530,140,CRWHITE,FontHandle12,"(%s)",tosiyoridata[i].sikona);
					}
				}else{
					DrawFormatStringToHandle(530,140,CRWHITE,FontHandle12,"(%s)",tosiyoridata[i].sikona);
				}
				DrawFormatStringToHandle(202,140,CRWHITE,FontHandle12,"一門主 %s部屋師匠 %s %d才 %d年～",heyastring[tosiyoridata[i].shozokuheyaid],tosiyoridata[i].namestring,tosiyoridata[i].age,tosiyoridata[i].startyear);
				if (tosiyoridata[i].keishousha_rikisiid>=0){
					if (flag==0){
						DrawStringToHandle(187,140,"指",CRGREEN,FontHandle12);
					}else{
						DrawStringToHandle(187,140,"指",CRWHITE,FontHandle12);
					}
				}else if(tosiyoridata[i].keishousha_tosiyoriid>=0){
					//if (tosiyoridata[i].keishousha_tosiyoriid<106){
					if (flag==0){
						DrawStringToHandle(187,140,"指",CRGREEN,FontHandle12);
					}else{
						DrawStringToHandle(187,140,"指",CRWHITE,FontHandle12);
					}
					//}else{
					//	DrawStringToHandle(187,140,"指",CRWHITE,FontHandle12);
					//}
				}else{
					if (tosiyoridata[i].category==1){
						DrawStringToHandle(187,140,"A",CRWHITE,FontHandle12);
					}else if (tosiyoridata[i].category==2){
						DrawStringToHandle(187,140,"B",CRWHITE,FontHandle12);
					}else if (tosiyoridata[i].category==3){
						DrawStringToHandle(187,140,"C",CRWHITE,FontHandle12);
					}else if (tosiyoridata[i].category==4){
						DrawStringToHandle(187,140,"一",CRWHITE,FontHandle12);
					}else if (tosiyoridata[i].category>=5){
						DrawStringToHandle(187,140,"期",CRWHITE,FontHandle12);
					}
				}
				break;
			}
		}
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
if (shuumeijunhyojiflag==1){
	//人望順年寄IDを借りて襲名順
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].startyear;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] < temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
		}
	}
}else{
	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
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
		}
	}
}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	ii=0;
	for (i=0;i<TOSIYORISUU;i++){
		temp_tosiyoriid=i;//ループの終端でもどす
		i=jinboujun_tosiyoriid[i];
		if (tosiyoridata[i].shozokuheyaid!=-1 && tosiyoridata[i].shozokuitimonid==itimonID){
			if (tosiyoridata[i].sishouflag==1){
				if (ii<(page_oyakata_itimon+1)*10 && ii>=page_oyakata_itimon*10){
					if (flag==0){
						DrawFormatStringToHandle(202,170+(ii%10)*15,CRGREEN,FontHandle12,"%s部屋師匠",heyastring[tosiyoridata[i].shozokuheyaid]);
					}else{
						DrawFormatStringToHandle(202,170+(ii%10)*15,CRWHITE,FontHandle12,"%s部屋師匠",heyastring[tosiyoridata[i].shozokuheyaid]);
					}
					if ((tosiyoridata[i].rijiflag&0x0f)>0 && (tosiyoridata[i].rijiflag&0x0f)<11){
						DrawStringToHandle(316-12,170+(ii%10)*15,"理",CRRED,FontHandle12);
					}
					//if (i<106){
					if (flag==0){
						DrawFormatStringToHandle(316,170+(ii%10)*15,CRGREEN,FontHandle12,"%s",tosiyoridata[i].namestring);
					}else{
						DrawFormatStringToHandle(316,170+(ii%10)*15,CRWHITE,FontHandle12,"%s",tosiyoridata[i].namestring);
					}
					//}else{
					//	DrawFormatStringToHandle(316,170+(ii%10)*15,CRWHITE,FontHandle12,"%s",tosiyoridata[i].namestring);
					//}
					DrawFormatStringToHandle(382,170+(ii%10)*15,CRWHITE,FontHandle12,"%d才 %d年～",tosiyoridata[i].age,tosiyoridata[i].startyear);
					if (tosiyoridata[i].keishousha_rikisiid!=-1){
						if (flag==0){
							DrawStringToHandle(187,170+(ii%10)*15,"指",CRGREEN,FontHandle12);
						}else{
							DrawStringToHandle(187,170+(ii%10)*15,"指",CRWHITE,FontHandle12);
						}
					}else if(tosiyoridata[i].keishousha_tosiyoriid>=0){
						//if (tosiyoridata[i].keishousha_tosiyoriid<106){
						if (flag==0){
							DrawStringToHandle(187,170+(ii%10)*15,"指",CRGREEN,FontHandle12);
						}else{
							DrawStringToHandle(187,170+(ii%10)*15,"指",CRWHITE,FontHandle12);
						}
						//}else{
						//	DrawStringToHandle(187,170+(ii%10)*15,"指",CRWHITE,FontHandle12);
						//}
					}else{
						if (tosiyoridata[i].category==1){
							DrawStringToHandle(187,170+(ii%10)*15,"A",CRWHITE,FontHandle12);
						}else if (tosiyoridata[i].category==2){
							DrawStringToHandle(187,170+(ii%10)*15,"B",CRWHITE,FontHandle12);
						}else if (tosiyoridata[i].category==3){
							DrawStringToHandle(187,170+(ii%10)*15,"C",CRWHITE,FontHandle12);
						}else if (tosiyoridata[i].category==4){
							DrawStringToHandle(187,170+(ii%10)*15,"一",CRWHITE,FontHandle12);
						}else if (tosiyoridata[i].category>=5){
							DrawStringToHandle(187,170+(ii%10)*15,"期",CRWHITE,FontHandle12);
						}
					}
					if (tosiyoridata[i].rikisiid>=0){
						if (flag==0){
							DrawFormatStringToHandle(530,170+(ii%10)*15,CRGREEN,FontHandle12,"(%s)",tosiyoridata[i].sikona);
						}else{
							DrawFormatStringToHandle(530,170+(ii%10)*15,CRWHITE,FontHandle12,"(%s)",tosiyoridata[i].sikona);
						}
					}else{
						DrawFormatStringToHandle(530,170+(ii%10)*15,CRWHITE,FontHandle12,"(%s)",tosiyoridata[i].sikona);
					}
				}
				ii++;
				for (iii=0;iii<TOSIYORISUU;iii++){
					temp_tosiyoriid2=iii;//ループの終端でもどす
					iii=jinboujun_tosiyoriid[iii];
					if (tosiyoridata[iii].sishouflag!=1 
					&& tosiyoridata[iii].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
						if (ii<(page_oyakata_itimon+1)*10 && ii>=page_oyakata_itimon*10){
							if (flag==0){
								DrawFormatStringToHandle(202,170+(ii%10)*15,CRGREEN,FontHandle12,"%s部屋付",heyastring[tosiyoridata[iii].shozokuheyaid]);
							}else{
								DrawFormatStringToHandle(202,170+(ii%10)*15,CRWHITE,FontHandle12,"%s部屋付",heyastring[tosiyoridata[iii].shozokuheyaid]);
							}
							if ((tosiyoridata[iii].rijiflag&0x0f)>0 && (tosiyoridata[iii].rijiflag&0x0f)<11){
								DrawStringToHandle(316-12,170+(ii%10)*15,"理",CRRED,FontHandle12);
							}
							//if (iii<106){
							if (flag==0){
								DrawFormatStringToHandle(316,170+(ii%10)*15,CRGREEN,FontHandle12,"%s",tosiyoridata[iii].namestring);
							}else{
								DrawFormatStringToHandle(316,170+(ii%10)*15,CRWHITE,FontHandle12,"%s",tosiyoridata[iii].namestring);
							}
							//}else{
							//	DrawFormatStringToHandle(316,170+(ii%10)*15,CRWHITE,FontHandle12,"%s",tosiyoridata[iii].namestring);
							//}
							DrawFormatStringToHandle(382,170+(ii%10)*15,CRWHITE,FontHandle12,"%d才 %d年～",tosiyoridata[iii].age,tosiyoridata[iii].startyear);
							if (tosiyoridata[iii].keishousha_rikisiid!=-1 || tosiyoridata[iii].keishousha_tosiyoriid!=-1){
								if (flag==0){
									DrawStringToHandle(187,170+(ii%10)*15,"借",CRGREEN,FontHandle12);
								}else{
									DrawStringToHandle(187,170+(ii%10)*15,"借",CRWHITE,FontHandle12);
								}
							}else{
								if (tosiyoridata[iii].category==1){
									DrawStringToHandle(187,170+(ii%10)*15,"A",CRWHITE,FontHandle12);
								}else if (tosiyoridata[iii].category==2){
									DrawStringToHandle(187,170+(ii%10)*15,"B",CRWHITE,FontHandle12);
								}else if (tosiyoridata[iii].category==3){
									DrawStringToHandle(187,170+(ii%10)*15,"C",CRWHITE,FontHandle12);
								}else if (tosiyoridata[iii].category==4){
									DrawStringToHandle(187,170+(ii%10)*15,"一",CRWHITE,FontHandle12);
								}else if (tosiyoridata[iii].category>=5){
									DrawStringToHandle(187,170+(ii%10)*15,"期",CRWHITE,FontHandle12);
								}
							}
							if (tosiyoridata[iii].rikisiid>=0){
								if (flag==0){
									DrawFormatStringToHandle(530,170+(ii%10)*15,CRGREEN,FontHandle12,"(%s)",tosiyoridata[iii].sikona);
								}else{
									DrawFormatStringToHandle(530,170+(ii%10)*15,CRWHITE,FontHandle12,"(%s)",tosiyoridata[iii].sikona);
								}
							}else{
								DrawFormatStringToHandle(530,170+(ii%10)*15,CRWHITE,FontHandle12,"(%s)",tosiyoridata[iii].sikona);
							}
						}
						ii++;
					}
					iii=temp_tosiyoriid2;
				}
			}
		}
		i=temp_tosiyoriid;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//if (ii>10 || page_oyakata_itimon>0){
		DrawFormatStringToHandle(200,170+12*15,CRGREEN,FontHandle12,"前頁　%d／%d頁　次頁",page_oyakata_itimon+1,(int)((ii-1)/10)+1);
	//}

	DrawStringToHandle(187,385+16+20,"カテゴリー、所属、年寄名跡名、年齢、襲名年、(現役時四股名)",CRWHITE,FontHandle12);
	DrawStringToHandle(187,385+16+20+12,"の順の表示です",CRWHITE,FontHandle12);

	draw_buttonUP();
	draw_buttonDOWN();
	//draw_buttonB_mouse();


	//理事表示
	count=0;
	DrawStringToHandle(200,45,"所属理事",CRWHITE,FontHandle12);
	for (ii=0;ii<10;ii++){
		for (i=0;i<TOSIYORISUU;i++){
			if ((tosiyoridata[i].rijiflag&0x0f)==ii+1){
				if (tosiyoridata[i].shozokuitimonid==itimonID
				&& tosiyoridata[i].shozokuheyaid!=-1
				){
					DrawFormatStringToHandle(190+((int)(count/5))*225,60+15*(count%5),CRWHITE,FontHandle12,"%s %s %d才",
					namestring_riji[(tosiyoridata[i].rijiflag&0x0f)-1],
					tosiyoridata[i].namestring,
					tosiyoridata[i].age);
					count++;
				}
				break;
			}
		}
	}
	//SetFontSize(16);
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	DrawFormatString(3,78,CRBLACK,"%2d／2ページ",itimonsentaku_page+1);

	//メイン表示
	DrawFormatString(187,24,CRWHITE,"%s一門　%2d部屋　%2d人所属　理事数%2d人",itimondata[itimonID].namestring,itimon_heyasuu[itimonID],itimon_tosiyorisuu[itimonID],itimonbetu_rijisuu[itimonID]);
	//通算一門ID表示
	if (itimondata[itimonID].startyear==1 && itimondata[itimonID].startmonth==1){
		DrawFormatStringToHandle(300,42,CRWHITE,FontHandle12,"%d年%d月創設  ID%d(通算ID%d)",itimondata[itimonID].startyear,itimondata[itimonID].startmonth,itimonID,itimondata[itimonID].itimonid_tuusan);
	}else{
		DrawFormatStringToHandle(300,42,CRWHITE,FontHandle12,"%d年%d月場所後創設  ID%d(通算ID%d)",itimondata[itimonID].startyear,itimondata[itimonID].startmonth,itimonID,itimondata[itimonID].itimonid_tuusan);
	}

//	DrawString(200,460,"相撲部屋へ",CRGREEN);
//	DrawString(300,460,"力士情報へ",CRGREEN);
	DrawString(200,460,"一門画面",CRWHITE);
	DrawString(300,460,"年寄画面",CRGREEN);

	//ScreenFlip() ;//裏画面を表画面にコピー

	return;
}

void menu_itimon(void)
{
	int i;
	int ii;
	int iii;
	int count=0;
	int temp_narabekaeyou[TOSIYORISUU];//並べ替え用に並べ替えたい要素を入れる変数
	int jinboujun_tosiyoriid[TOSIYORISUU];
	int temp_tosiyoriid=0;
	int temp_tosiyoriid2=0;

	if (mode==0){
		menuflag=1;
		return;
	}
if (shuumeijunhyojiflag==1){
	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].startyear;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (iii = 0;iii < TOSIYORISUU - 1;iii++) {
		for (ii = 0;ii < TOSIYORISUU - 1;ii++) {
			if (temp_narabekaeyou[ii + 1] < temp_narabekaeyou[ii]) {
				temp_tosiyoriid = temp_narabekaeyou[ii];
				temp_narabekaeyou[ii] = temp_narabekaeyou[ii + 1];
				temp_narabekaeyou[ii + 1] = temp_tosiyoriid;
				temp_tosiyoriid = jinboujun_tosiyoriid[ii];
				jinboujun_tosiyoriid[ii] = jinboujun_tosiyoriid[ii+1];
				jinboujun_tosiyoriid[ii+1] = temp_tosiyoriid;
			}
		}
	}
}else{
	//人望順年寄IDを検索
	//バブルソート
	for (iii=0;iii<TOSIYORISUU;iii++){
		temp_narabekaeyou[iii]=0;
		temp_narabekaeyou[iii]=tosiyoridata[iii].jinbou;
		jinboujun_tosiyoriid[iii]=0;
		jinboujun_tosiyoriid[iii]=iii;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
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
		}
	}
}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//一門ごとの親方数を数える
	//一門ごとの年寄数・理事数確認
	for (i=0;i<ITIMONSUU;i++){
		itimon_tosiyorisuu[i]=0;
		itimonbetu_rijisuu[i]=0;
		for (ii=0;ii<TOSIYORISUU;ii++){
			if (tosiyoridata[ii].shozokuheyaid!=-1 && tosiyoridata[ii].shozokuitimonid==i){
				itimon_tosiyorisuu[i]++;
			}
			if (tosiyoridata[ii].shozokuheyaid!=-1 && tosiyoridata[ii].shozokuitimonid==i
			&& (tosiyoridata[ii].rijiflag&0x0f)>0 && (tosiyoridata[ii].rijiflag&0x0f)<11
			){
				itimonbetu_rijisuu[i]++;
			}
		}
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//一門ごとの部屋数確認
	for (i=0;i<ITIMONSUU;i++){
		itimon_heyasuu[i]=0;
		for (ii=0;ii<TOSIYORISUU;ii++){
			if (tosiyoridata[ii].shozokuheyaid!=-1 && tosiyoridata[ii].shozokuitimonid==i && tosiyoridata[ii].sishouflag==1){
				itimon_heyasuu[i]++;
			}
		}
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//page_oyakata_itimon=0;
	itimondatahyoji(0,itimonsentaku_id);
	ScreenFlip() ;
	//リスト上で部屋名をクリックした場合に一門詳細情報を表示
		// キー入力待ち(この一文を入れないとうまくいかないみたい)
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		buttonA_mouse_change();
		buttonB_mouse_change();
		buttonC_mouse_change();
		buttonD_mouse_change();
		buttonE_mouse_change();
		buttonF_mouse_change();
		buttonG_mouse_change();
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		buttonA_mouse_change();
		buttonB_mouse_change();
		buttonC_mouse_change();
		buttonD_mouse_change();
		buttonE_mouse_change();
		buttonF_mouse_change();
		buttonG_mouse_change();
		Sleep(1);
	}
	while(1)
	{

/*/////////////////////////////////////////////////////
///////////////////////////////////////////////////////*/
		//親方の現役"指"又は"借"をクリックしたら力士情報(年寄画面)へ飛ばす
		//一門主分
		for (i=0;i<TOSIYORISUU;i++){
//			if( ProcessMessage() == -1 ){mode=1;break;}
			if (tosiyoridata[i].shozokuitimonid==itimonsentaku_id && tosiyoridata[i].sishouflag==1
			&& itimondata[tosiyoridata[i].shozokuitimonid].shuheyaid==tosiyoridata[i].shozokuheyaid){
				if (tosiyoridata[i].keishousha_rikisiid>=0){
					if (get_mouseclick(187,140,187+20,140+12)==1 ){
						rikisisentaku_num=((rikisidata[tosiyoridata[i].keishousha_rikisiid].bandukejun+20)%20)*2;
						rikisisentaku_page=(int)((rikisidata[tosiyoridata[i].keishousha_rikisiid].bandukejun+20)/20)-1;
						rikisisentaku_id=tosiyoridata[i].keishousha_rikisiid;
						bandukejun_or_jiheyaflag=0;
						torikumi_or_seisekiflag=3;
						menuflag=3;
						WaitTimer(200);
						return;
					}
				}
				if (tosiyoridata[i].keishousha_tosiyoriid>=0
				&& tosiyoridata[i].keishousha_tosiyoriid<TOSIYORISUU){
					if (get_mouseclick(187,140,187+20,140+12)==1 ){
						tosiyorisentaku_page=(int)(tosiyoridata[i].keishousha_tosiyoriid/40);
						tosiyorisentaku_num=tosiyoridata[i].keishousha_tosiyoriid%40;
						tosiyorisentaku_id=tosiyoridata[i].keishousha_tosiyoriid;
						menuflag=12;
						WaitTimer(200);
						return;
					}
				}

			}
		}
		//他の親方分
		ii=0;
		for (i=0;i<TOSIYORISUU;i++){
			temp_tosiyoriid=i;
			i=jinboujun_tosiyoriid[i];
//			if( ProcessMessage() == -1 ){mode=1;break;}
			if (tosiyoridata[i].shozokuheyaid!=-1 && tosiyoridata[i].shozokuitimonid==itimonsentaku_id){
				if (tosiyoridata[i].sishouflag==1){
					if (tosiyoridata[i].keishousha_rikisiid>=0){
						if (ii<(page_oyakata_itimon+1)*10 && ii>=page_oyakata_itimon*10){
							if (get_mouseclick(187,170+(ii%10)*15,187+20,170+(ii%10)*15+12)==1 ){
								rikisisentaku_num=((rikisidata[tosiyoridata[i].keishousha_rikisiid].bandukejun+20)%20)*2;
								rikisisentaku_page=(int)((rikisidata[tosiyoridata[i].keishousha_rikisiid].bandukejun+20)/20)-1;
								rikisisentaku_id=tosiyoridata[i].keishousha_rikisiid;
								bandukejun_or_jiheyaflag=0;
								torikumi_or_seisekiflag=3;
								menuflag=3;
								WaitTimer(200);
								return;
							}
						}
					}
					if (tosiyoridata[i].keishousha_tosiyoriid>=0
					&& tosiyoridata[i].keishousha_tosiyoriid<TOSIYORISUU){
						if (ii<(page_oyakata_itimon+1)*10 && ii>=page_oyakata_itimon*10){
							if (get_mouseclick(187,170+(ii%10)*15,187+20,170+(ii%10)*15+12)==1 ){
								tosiyorisentaku_page=(int)(tosiyoridata[i].keishousha_tosiyoriid/40);
								tosiyorisentaku_num=tosiyoridata[i].keishousha_tosiyoriid%40;
								tosiyorisentaku_id=tosiyoridata[i].keishousha_tosiyoriid;
								menuflag=12;
								WaitTimer(200);
								return;
							}
						}
					}
					ii++;
					for (iii=0;iii<TOSIYORISUU;iii++){
						temp_tosiyoriid2=iii;
						iii=jinboujun_tosiyoriid[iii];
//						if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (tosiyoridata[iii].sishouflag!=1 
						&& tosiyoridata[iii].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
							if (tosiyoridata[iii].keishousha_rikisiid>=0){
								if (ii<(page_oyakata_itimon+1)*10 && ii>=page_oyakata_itimon*10){
									if (get_mouseclick(187,170+(ii%10)*15,187+20,170+(ii%10)*15+12)==1 ){
										rikisisentaku_num=((rikisidata[tosiyoridata[iii].keishousha_rikisiid].bandukejun+20)%20)*2;
										rikisisentaku_page=(int)((rikisidata[tosiyoridata[iii].keishousha_rikisiid].bandukejun+20)/20)-1;
										rikisisentaku_id=tosiyoridata[iii].keishousha_rikisiid;
										bandukejun_or_jiheyaflag=0;
										torikumi_or_seisekiflag=3;
										menuflag=3;
										WaitTimer(200);
										return;
									}
								}
							}
							ii++;
						}
						iii=temp_tosiyoriid2;
					}
				}
			}
			i=temp_tosiyoriid;
		}
		//if( ProcessMessage() == -1 ){mode=1;break;}
		//if (itimon_tosiyorisuu[itimonsentaku_num]>11){
			//親方表示部分の頁数減少
			if (get_mouseclick(200,170+12*15,200+24,170+12*15+12)==1 ){
				if (page_oyakata_itimon>0){
					page_oyakata_itimon--;
				}
				itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
				ScreenFlip() ;
				WaitTimer(200);
				//break;
			}
			//親方表示部分の頁数増加
			if (get_mouseclick(296,170+12*15,296+24,170+12*15+12)==1 ){
				if (page_oyakata_itimon<39){
					page_oyakata_itimon++;
				}
				itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
				ScreenFlip() ;
				WaitTimer(200);
				//break;
			}
		//}
		//親方の現役四股名をクリックしたら引退力士表示へ飛ばす
		//一門主分
		for (i=0;i<TOSIYORISUU;i++){
//			if( ProcessMessage() == -1 ){mode=1;break;}
			if (tosiyoridata[i].shozokuitimonid==itimonsentaku_id && tosiyoridata[i].sishouflag==1 
			&& itimondata[tosiyoridata[i].shozokuitimonid].shuheyaid==tosiyoridata[i].shozokuheyaid){
				if (tosiyoridata[i].rikisiid>=0){
					if (get_mouseclick(530,140,530+60,140+12)==1 ){
						retirerikisi_rikisiid(tosiyoridata[i].rikisiid);//subsubsub.cpp
						itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
						ScreenFlip() ;
						WaitTimer(200);
						break;
					}
				}
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;break;}
		//他の親方分
		ii=0;
		for (i=0;i<TOSIYORISUU;i++){
			temp_tosiyoriid=i;
			i=jinboujun_tosiyoriid[i];
//			if( ProcessMessage() == -1 ){mode=1;break;}
			if (tosiyoridata[i].shozokuheyaid!=-1 && tosiyoridata[i].shozokuitimonid==itimonsentaku_id){
				if (tosiyoridata[i].sishouflag==1){
					if (tosiyoridata[i].rikisiid>=0){
						if (ii<(page_oyakata_itimon+1)*10 && ii>=page_oyakata_itimon*10){
							if (get_mouseclick(530,170+(ii%10)*15,530+60,170+(ii%10)*15+12)==1 ){
								retirerikisi_rikisiid(tosiyoridata[i].rikisiid);
								itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
								ScreenFlip() ;
								WaitTimer(200);
								break;
							}
						}
					}
					ii++;
					for (iii=0;iii<TOSIYORISUU;iii++){
						temp_tosiyoriid2=iii;
						iii=jinboujun_tosiyoriid[iii];
//						if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (tosiyoridata[iii].sishouflag!=1 
						&& tosiyoridata[iii].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
							if (tosiyoridata[iii].rikisiid>=0){
								if (ii<(page_oyakata_itimon+1)*10 && ii>=page_oyakata_itimon*10){
									if (get_mouseclick(530,170+(ii%10)*15,530+60,170+(ii%10)*15+12)==1 ){
										retirerikisi_rikisiid(tosiyoridata[iii].rikisiid);
										itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
										ScreenFlip() ;
										WaitTimer(200);
										break;
									}
								}
							}
							ii++;
						}
						iii=temp_tosiyoriid2;
					}
				}
			}
			i=temp_tosiyoriid;
		}
		//if( ProcessMessage() == -1 ){mode=1;break;}
		//年寄名クリックで年寄画面へ
		//他の親方分のみ
		ii=0;
		for (i=0;i<TOSIYORISUU;i++){
			temp_tosiyoriid=i;
			i=jinboujun_tosiyoriid[i];
//			if( ProcessMessage() == -1 ){mode=1;break;}
			if (tosiyoridata[i].shozokuheyaid!=-1 && tosiyoridata[i].shozokuitimonid==itimonsentaku_id){
				if (tosiyoridata[i].sishouflag==1){
					//if (i<106){
						if (ii<(page_oyakata_itimon+1)*10 && ii>=page_oyakata_itimon*10){
							if (get_mouseclick(316,170+(ii%10)*15,316+60,170+(ii%10)*15+12)==1 ){
								tosiyorisentaku_page=(int)(i/40);
								tosiyorisentaku_num=i%40;
								tosiyorisentaku_id=i;
								menuflag=12;
								return;
							}
						}
					//}
					ii++;
					for (iii=0;iii<TOSIYORISUU;iii++){
						temp_tosiyoriid2=iii;
						iii=jinboujun_tosiyoriid[iii];
//						if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (tosiyoridata[iii].sishouflag!=1 
						&& tosiyoridata[iii].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
							//if (iii<106){
								if (ii<(page_oyakata_itimon+1)*10 && ii>=page_oyakata_itimon*10){
									if (get_mouseclick(316,170+(ii%10)*15,316+60,170+(ii%10)*15+12)==1 ){
										tosiyorisentaku_page=(int)(iii/40);
										tosiyorisentaku_num=iii%40;
										tosiyorisentaku_id=iii;
										menuflag=12;
										return;
									}
								}
							//}
							ii++;
						}
						iii=temp_tosiyoriid2;
					}
				}
			}
			i=temp_tosiyoriid;
		}
		//if( ProcessMessage() == -1 ){mode=1;break;}
		//部屋名クリックで部屋画面へ
		//他の親方分のみ
		ii=0;
		for (i=0;i<TOSIYORISUU;i++){
			temp_tosiyoriid=i;
			i=jinboujun_tosiyoriid[i];
//			if( ProcessMessage() == -1 ){mode=1;break;}
			if (tosiyoridata[i].shozokuheyaid!=-1 && tosiyoridata[i].shozokuitimonid==itimonsentaku_id){
				if (tosiyoridata[i].sishouflag==1){
					if (tosiyoridata[i].shozokuheyaid>=0 && tosiyoridata[i].shozokuheyaid<HEYASUU){
						if (ii<(page_oyakata_itimon+1)*10 && ii>=page_oyakata_itimon*10){
							if (get_mouseclick(202,170+(ii%10)*15,202+60,170+(ii%10)*15+12)==1 ){
								heyasentaku_page=(int)(tosiyoridata[i].shozokuheyaid/40);
								heyasentaku_num=tosiyoridata[i].shozokuheyaid%40;
								heyasentaku_id=tosiyoridata[i].shozokuheyaid;
								menuflag=2;
								return;
							}
						}
					}
					ii++;
					for (iii=0;iii<TOSIYORISUU;iii++){
						temp_tosiyoriid2=iii;
						iii=jinboujun_tosiyoriid[iii];
//						if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (tosiyoridata[iii].sishouflag!=1 
						&& tosiyoridata[iii].shozokuheyaid==tosiyoridata[i].shozokuheyaid){
							if (tosiyoridata[iii].shozokuheyaid>=0 && tosiyoridata[iii].shozokuheyaid<HEYASUU){
								if (ii<(page_oyakata_itimon+1)*10 && ii>=page_oyakata_itimon*10){
									if (get_mouseclick(202,170+(ii%10)*15,202+60,170+(ii%10)*15+12)==1 ){
										heyasentaku_page=(int)(tosiyoridata[iii].shozokuheyaid/40);
										heyasentaku_num=tosiyoridata[iii].shozokuheyaid%40;
										heyasentaku_id=tosiyoridata[iii].shozokuheyaid;
										menuflag=2;
										return;
									}
								}
							}
							ii++;
						}
						iii=temp_tosiyoriid2;
					}
				}
			}
			i=temp_tosiyoriid;
		}
		//if( ProcessMessage() == -1 ){mode=1;break;}
		if (itimonsentaku_page==1){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				itimonsentaku_page=0;
				itimonsentaku_num=0;
				itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
				itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
				ScreenFlip() ;
				WaitTimer(200);
			}
		}
		if (itimonsentaku_page==0){
			if (get_mouseclick_buttonDOWN() == 1){//左リストUPボタンをクリック
				itimonsentaku_page=1;
				itimonsentaku_num=0;
				itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
				itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
				ScreenFlip() ;
				WaitTimer(200);
			}
		}
		for (i=0;i<40;i++){
			if (get_mouseclick_list(i) == 1){//リスト上の部屋名をクリックしたら
				if (i+itimonsentaku_page*40<ITIMONSUU){
					itimonsentaku_num=i;
					itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
					itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
					ScreenFlip() ;
					WaitTimer(200);
				}
			}
		}

		if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
			if (itimonsentaku_page==1 && itimonsentaku_num<2){
				itimonsentaku_page=0;
				itimonsentaku_num+=38;
				itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
				itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
				ScreenFlip() ;
				WaitTimer(200);
			}else if (itimonsentaku_num>1){
				itimonsentaku_num=itimonsentaku_num-2;
				itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
				itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
				ScreenFlip() ;
				WaitTimer(200);
			}
		}
		if(CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
			if (itimonsentaku_page==0 && itimonsentaku_num>37){
				itimonsentaku_page=1;
				itimonsentaku_num-=38;
				itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
				itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
				ScreenFlip() ;
				WaitTimer(200);
			}else if (itimonsentaku_num<38){
				if (!(itimonsentaku_page==1 && itimonsentaku_num>11)){
					itimonsentaku_num=itimonsentaku_num+2;
					itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
					itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
					ScreenFlip() ;
					WaitTimer(200);
				}
			}
		}



		if( CheckHitKey_test(KEY_INPUT_RIGHT)){//→キー
			if ((itimonsentaku_num+2)%2==0 ){
					itimonsentaku_num=itimonsentaku_num+1;
					itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
					itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
					ScreenFlip() ;
					WaitTimer(200);
			}
		}
		if( CheckHitKey_test(KEY_INPUT_LEFT)){//←キー
			if ((itimonsentaku_num+2)%2==1 ){
				itimonsentaku_num=itimonsentaku_num-1;
				itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
				itimondatahyoji(0,itimonsentaku_id);//部屋データを表示
				ScreenFlip() ;
				WaitTimer(200);
			}
		}


/*
		if (get_mouseclick(200,460,200+16*5,460+16) == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=11;
			return;
		}
*/
		if (get_mouseclick(300,460,300+16*5,460+16) == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=12;
			return;
		}
/*
		if (get_mouseclick(500,460,500+16*5,460+16) == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=12;
			return;
		}
*/
		if (get_mouseclick_buttonA() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=1;
			break;
		}
		if (get_mouseclick_buttonB() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=2;
			break;
		}
		if (get_mouseclick_buttonC() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=3;
			break;
		}
		if (get_mouseclick_buttonD() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=4;
			break;
		}
		if (get_mouseclick_buttonE() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=5;
			break;
		}
		if (get_mouseclick_buttonF() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=6;
			break;
		}
		if (get_mouseclick_buttonG() == 1){//メニューボタンGをクリックでループから抜け次へ進む
			menuflag=7;
			break;
		}
		if( CheckHitKey_test(KEY_INPUT_NUMPADENTER) || CheckHitKey_test( KEY_INPUT_RETURN)){//ENTERキーでループから抜けメニュー画面へ
			menuflag=7;
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
	
	return;
}

void heyasinsetu(int tosiyoriID,int heyaid_dokuritusaki,int heyaid_dokuritumoto)//年寄画面編集ボタンでの部屋新設処理
{
	int i,ii,iii;
	int count=0;
	int mitizuresuu=0;
	int count_mitizuresuu=0;
	int dokuritumoto_sishouid=0;
	FILE *fp;

	//部屋の力士数が3.14新規設立処理の下限数をクリアしているか（連れていける力士がいるか）
	if (shozokurikisisuu[tosiyoridata[tosiyoriID].shozokuheyaid]>=2){

		tosiyorisuukakunin();

		//年寄変数関連
		tosiyoridata[tosiyoriID].shozokuheyaid=heyaid_dokuritusaki;
		tosiyoridata[tosiyoriID].sishouflag=1;
		strcpy(heyastring[heyaid_dokuritusaki],tosiyoridata[tosiyoriID].namestring);
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
		////////////////temp_dat初期化////////////////
		fp = fopen("temp_dat.dat","w");
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}
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
				//eventlog書き込み/////////////////////////////////////////
				fp = fopen("data/eventlog.txt","a");
				// オープンできなかったらここで終了
				if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
				fprintf(fp,"%sは%s親方と共に%s部屋に移籍しました(編集：新設)\n",
				namestring[heyabandukejunid[heyaid_dokuritumoto][shozokurikisisuu[heyaid_dokuritumoto]-1-ii]],
				tosiyoridata[tosiyoriID].namestring,
				heyastring[heyaid_dokuritusaki]);
				//クローズ
				fclose(fp);
				if( ProcessMessage() == -1 ){mode=1;return ;}
				////////////////////////////////////////////////////////////
				//temp_dat書き込み/////////////////////////////////////////
				fp = fopen("temp_dat.dat","ab");
				// オープンできなかったらここで終了
				if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "temp_dat.datファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
				//ここから書き込み
				fwrite(&heyabandukejunid[heyaid_dokuritumoto][shozokurikisisuu[heyaid_dokuritumoto]-1-ii],sizeof(int),1,fp);//力士ID
				fwrite(&heyaid_dokuritusaki,sizeof(int),1,fp);//新部屋ID
				//クローズ
				fclose(fp);
				if( ProcessMessage() == -1 ){mode=1;return ;}
				////////////////////////////////////////////////////////////
			}
			if (count_mitizuresuu>=mitizuresuu){break;}
		}
		shozokurikisisuu[heyaid_dokuritumoto]-=mitizuresuu;
		shozokurikisisuu[heyaid_dokuritusaki]+=mitizuresuu;
		
		tosiyorisuukakunin();

		//年寄画面表示専用ファイル書き込み
		tosiyorihyoujifilekakikomi(tosiyoriID);

		//eventlog書き込み/////////////////////////////////////////
		fp = fopen("data/eventlog.txt","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
		fprintf(fp,"%s(%d才)親方が%s部屋から独立し、%s部屋を立ち上げました(編集)\n",
		tosiyoridata[tosiyoriID].namestring,
		tosiyoridata[tosiyoriID].age,
		heyastring[heyaid_dokuritumoto],
		tosiyoridata[tosiyoriID].namestring);
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}
		////////////////////////////////////////////////////////////
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawFormatString(0,369,CRWHITE,"%s(%d才)親方が%s部屋から独立し、%s部屋を立ち上げました",
		tosiyoridata[tosiyoriID].namestring,
		tosiyoridata[tosiyoriID].age,
		heyastring[heyaid_dokuritumoto],
		tosiyoridata[tosiyoriID].namestring);
		DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		//////////////////////////////////////////////////////////////
		//部屋移籍した力士を表示
		//////////////////////////////////////////////////////////////////
		{
			int temp_rikisiid=0;
			int temp_heyaid_new=0;
			int count=0;
			//temp_dat読込/////////////////////////////////////////
			fp = fopen("temp_dat.dat","rb");
			// オープンできなかったらここで終了
			if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "temp_dat.datファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString(20,20,"部屋の新設に伴い、以下の力士が移籍しました",CRWHITE);
			//ここから読込
			while(1){
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
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
			DrawString( 250 , 460 , "Hit any key" , CRWHITE);
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
		}
	}else{
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString(100,200,"元の部屋の力士の数が2人以上いないと、この処理は行えません。",CRWHITE);
		DrawString(100,300,"HIT ANY KEY",CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
	}

	return;

}

void tosiyorihyoujifilekakikomi(tosiyoriID)
{
	if (tosiyoriID<106){
		char temp_filename[MAX_PATH];
		FILE *fp;
		sprintf(temp_filename,"data/dat/hyoji_tosiyori%d.dat\0",tosiyoriID);
		fp = fopen(temp_filename,"ab");
		fwrite(&year,sizeof(year),1,fp);
		fwrite(&month,sizeof(month),1,fp);
		fwrite(&tosiyoridata[tosiyoriID].rikisiid,sizeof(tosiyoridata[tosiyoriID].rikisiid),1,fp);
		fwrite(tosiyoridata[tosiyoriID].sikona,sizeof(tosiyoridata[tosiyoriID].sikona),1,fp);
		fwrite(&tosiyoridata[tosiyoriID].keishousha_rikisiid,sizeof(tosiyoridata[tosiyoriID].keishousha_rikisiid),1,fp);
		if (tosiyoridata[tosiyoriID].keishousha_rikisiid>=0){
			fwrite(namestring[tosiyoridata[tosiyoriID].keishousha_rikisiid],sizeof(namestring[tosiyoridata[tosiyoriID].keishousha_rikisiid]),1,fp);
		}else{
			fwrite(namestring[0],sizeof(namestring[0]),1,fp);//ダミーで入れておいた、表示するときはkeishousha_rikisiidが-1かどうかで判断すべき
		}
		fwrite(&tosiyoridata[tosiyoriID].shozokuitimonid,sizeof(tosiyoridata[tosiyoriID].shozokuitimonid),1,fp);
		if (tosiyoridata[tosiyoriID].shozokuitimonid>=0){
			fwrite(itimondata[tosiyoridata[tosiyoriID].shozokuitimonid].namestring,sizeof(itimondata[tosiyoridata[tosiyoriID].shozokuitimonid].namestring),1,fp);
		}else{
			fwrite(itimondata[0].namestring,sizeof(itimondata[0].namestring),1,fp);//ダミー
		}
		fwrite(&tosiyoridata[tosiyoriID].shozokuheyaid,sizeof(tosiyoridata[tosiyoriID].shozokuheyaid),1,fp);
		if (tosiyoridata[tosiyoriID].shozokuheyaid>=0){
			fwrite(heyastring[tosiyoridata[tosiyoriID].shozokuheyaid],sizeof(heyastring[tosiyoridata[tosiyoriID].shozokuheyaid]),1,fp);
		}else{
			fwrite(heyastring[0],sizeof(heyastring[0]),1,fp);//ダミー
		}
		fwrite(&tosiyoridata[tosiyoriID].sishouflag,sizeof(tosiyoridata[tosiyoriID].sishouflag),1,fp);
		fwrite(&tosiyoridata[tosiyoriID].keishousha_tosiyoriid,sizeof(tosiyoridata[tosiyoriID].keishousha_tosiyoriid),1,fp);
		if (tosiyoridata[tosiyoriID].keishousha_tosiyoriid>=0){
			fwrite(tosiyoridata[tosiyoridata[tosiyoriID].keishousha_tosiyoriid].namestring,sizeof(tosiyoridata[tosiyoridata[tosiyoriID].keishousha_tosiyoriid].namestring),1,fp);
		}else{
			fwrite(tosiyoridata[0].namestring,sizeof(tosiyoridata[0].namestring),1,fp);//ダミー
		}
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}


	return;
}

void tosiyorisuukakunin(void)
{
	int i,ii,iii;
	int count;
	int temp_narabekaeyou[TOSIYORISUU];//並べ替え用に並べ替えたい要素を入れる変数
	int jinboujun_tosiyoriid[TOSIYORISUU];
	int temp_tosiyoriid=0;

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
	//一門ごとの親方数を数える
	//一門ごとの年寄数・理事数確認
	for (i=0;i<ITIMONSUU;i++){
		itimon_tosiyorisuu[i]=0;
		itimonbetu_rijisuu[i]=0;
		for (ii=0;ii<TOSIYORISUU;ii++){
			if (tosiyoridata[ii].shozokuheyaid!=-1 && tosiyoridata[ii].shozokuitimonid==i){
				itimon_tosiyorisuu[i]++;
			}
			if (tosiyoridata[ii].shozokuheyaid!=-1 && tosiyoridata[ii].shozokuitimonid==i
			&& (tosiyoridata[ii].rijiflag&0x0f)>0 && (tosiyoridata[ii].rijiflag&0x0f)<11
			){
				itimonbetu_rijisuu[i]++;
			}
		}
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//一門ごとの部屋数確認
	for (i=0;i<ITIMONSUU;i++){
		itimon_heyasuu[i]=0;
		for (ii=0;ii<TOSIYORISUU;ii++){
			if (tosiyoridata[ii].shozokuheyaid!=-1 && tosiyoridata[ii].shozokuitimonid==i && tosiyoridata[ii].sishouflag==1){
				itimon_heyasuu[i]++;
			}
		}
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	return;
}



void heyashoumetu(int tosiyoriID,int heyaid_ikisaki,int heyaid_moto)//部屋消滅処理、
					//行き先部屋と元部屋が一緒の場合は、行き先決まっていない退職させる処理の場合
{
	int i,ii,iii,iiii,iiiii;
	int count;
	int temp_tosiyoriid;
	int temp_jinbou;
	char marugotoflag=0;//空き部屋に部屋丸ごと引越しの場合は1になって師匠フラグはそのまま1
	FILE *fp;
	//部屋名リセット
	strcpy(heyastring[heyaid_moto],"\0");
	//所属部屋
	//退職させる処理から飛んできた場合の消滅処理
	if (heyaid_ikisaki==heyaid_moto){
		tosiyoridata[tosiyoriID].shozokuheyaid=-1;
		//eventlog書き込み/////////////////////////////////////////
		fp = fopen("data/eventlog.txt","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
		fprintf(fp,"%s(%d才)親方の退職に伴い、%s部屋は消滅しました(編集)\n",
		tosiyoridata[tosiyoriID].namestring,
		tosiyoridata[tosiyoriID].age,
		tosiyoridata[tosiyoriID].namestring);
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}
		////////////////////////////////////////////////////////////
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawFormatString(0,369,CRWHITE,"%s(%d才)親方の退職に伴い、%s部屋は消滅しました",
		tosiyoridata[tosiyoriID].namestring,
		tosiyoridata[tosiyoriID].age,
		tosiyoridata[tosiyoriID].namestring);
		DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		//////////////////////////////////////////////////////////////
		//年寄画面表示専用ファイル書き込み
		tosiyorihyoujifilekakikomi(tosiyoriID);

		//他に親方いれば全員一緒にどこかに移籍とも思ったけど
		//退職させる処理の中で
		//部屋付いる親方のうち継承させられる部屋付がいない場合はＮＧとしてここまで飛ばさないことにした

	//所属先変更処理から飛んできた場合の消滅処理
	}else{
		tosiyoridata[tosiyoriID].shozokuheyaid=heyaid_ikisaki;
		//所属一門ID
		marugotoflag=1;
		for (i=0;i<TOSIYORISUU;i++){
			if (tosiyoridata[i].shozokuheyaid==tosiyoridata[tosiyoriID].shozokuheyaid
				&& i!=tosiyoriID){
				tosiyoridata[tosiyoriID].shozokuitimonid=tosiyoridata[i].shozokuitimonid;
				marugotoflag=0;
				break;
			}
		}
		//師匠フラグ
		if (marugotoflag==0){
			tosiyoridata[tosiyoriID].sishouflag=0;
		}
		//eventlog書き込み/////////////////////////////////////////
		fp = fopen("data/eventlog.txt","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
		fprintf(fp,"部屋の消滅に伴い、%s(%d才)親方は%s部屋に移籍しました(編集)\n",
		tosiyoridata[tosiyoriID].namestring,
		tosiyoridata[tosiyoriID].age,
		heyastring[heyaid_ikisaki]);
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}
		////////////////////////////////////////////////////////////
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawFormatString(0,369,CRWHITE,"部屋の消滅に伴い、%s(%d才)親方は%s部屋に移籍しました",
		tosiyoridata[tosiyoriID].namestring,
		tosiyoridata[tosiyoriID].age,
		heyastring[heyaid_ikisaki]);
		DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		//////////////////////////////////////////////////////////////
		//年寄画面表示専用ファイル書き込み
		tosiyorihyoujifilekakikomi(tosiyoriID);
		//他に親方いれば全員一緒に移籍
		for (i=0;i<TOSIYORISUU;i++){
			if (tosiyoridata[i].shozokuheyaid==heyaid_moto){
				tosiyoridata[i].shozokuheyaid=heyaid_ikisaki;
				tosiyoridata[i].sishouflag=0;
				tosiyoridata[i].shozokuitimonid=tosiyoridata[tosiyoriID].shozokuitimonid;
				//年寄画面表示専用ファイル書き込み
				tosiyorihyoujifilekakikomi(i);
				//eventlog書き込み/////////////////////////////////////////
				fp = fopen("data/eventlog.txt","a");
				// オープンできなかったらここで終了
				if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
				fprintf(fp,"部屋の消滅に伴い、%s(%d才)親方は%s部屋に移籍しました(編集)\n",
				tosiyoridata[i].namestring,
				tosiyoridata[i].age,
				heyastring[heyaid_ikisaki]);
				//クローズ
				fclose(fp);
				if( ProcessMessage() == -1 ){mode=1;return ;}
				////////////////////////////////////////////////////////////
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawFormatString(0,369,CRWHITE,"部屋の消滅に伴い、%s(%d才)親方は%s部屋に移籍しました",
				tosiyoridata[i].namestring,
				tosiyoridata[i].age,
				heyastring[heyaid_ikisaki]);
				DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				//////////////////////////////////////////////////////////////

			}
		}

	}



	////////////
	////////////力士を移動させる処理(年寄のいない部屋から他の部屋へ力士移動させる処理を改変し流用)//////////////////////////
	////////////
	////////////////temp_dat初期化////////////////
	fp = fopen("temp_dat.dat","w");
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}

	tosiyorisuukakunin();

	//ここで力士部屋移動処理(同じ移動先の部屋)
	count=0;
	while(heya_tosiyorisuu[heyaid_ikisaki]>=1 && shozokurikisisuu[heyaid_ikisaki]<20){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//eventlog書き込み/////////////////////////////////////////
		fp = fopen("data/eventlog.txt","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
		fprintf(fp,"%sは%s部屋の消滅に伴い%s部屋に移籍しました(編集：親方に随伴して移籍)\n",
		namestring[heyabandukejunid[heyaid_moto][count]],
		heyastring[heyaid_moto],
		heyastring[heyaid_ikisaki]);
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}
		////////////////////////////////////////////////////////////
		//temp_dat書き込み/////////////////////////////////////////
		fp = fopen("temp_dat.dat","ab");
		// オープンできなかったらここで終了
		if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "temp_dat.datファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
		//ここから書き込み
		fwrite(&heyabandukejunid[heyaid_moto][count],sizeof(heyabandukejunid[heyaid_moto][count]),1,fp);//力士ID
		fwrite(&heyaid_ikisaki,sizeof(heyaid_ikisaki),1,fp);//新部屋ID
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}
		////////////////////////////////////////////////////////////
		rikisidata[heyabandukejunid[heyaid_moto][count]].heyaid=heyaid_ikisaki;
		shozokurikisisuu[heyaid_ikisaki]++;
		shozokurikisisuu[heyaid_moto]--;
		count++;
		if (shozokurikisisuu[heyaid_moto]==0){break;}
	}

	tosiyorisuukakunin();

	//ここで力士部屋移動処理(同じ一門)
	for (ii=0;ii<HEYASUU;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (heya_tosiyorisuu[ii]==0){
			count=0;
			while (shozokurikisisuu[ii]>0){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (iiii=1;iiii<HEYASUU;iiii++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if(heya_tosiyorisuu[iiii]>=1){
						for (iii=0;iii<TOSIYORISUU;iii++){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							if (tosiyoridata[iii].shozokuheyaid==iiii 
								&& tosiyoridata[iii].shozokuitimonid==tosiyoridata[tosiyoriID].shozokuitimonid){
								while(shozokurikisisuu[iiii]<20){
									//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									//eventlog書き込み/////////////////////////////////////////
									fp = fopen("data/eventlog.txt","a");
									// オープンできなかったらここで終了
									if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
									fprintf(fp,"%sは%s部屋の消滅に伴い%s部屋に移籍しました(編集：同一門)\n",
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

	tosiyorisuukakunin();

	//ここで力士部屋移動処理(一門関係なし)
	for (ii=0;ii<HEYASUU;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (heya_tosiyorisuu[ii]==0){
			count=0;
			while (shozokurikisisuu[ii]>0){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				for (iiii=1;iiii<HEYASUU;iiii++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if(heya_tosiyorisuu[iiii]>=1){
						while(shozokurikisisuu[iiii]<20){
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
							//eventlog書き込み/////////////////////////////////////////
							fp = fopen("data/eventlog.txt","a");
							// オープンできなかったらここで終了
							if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
							fprintf(fp,"%sは%s部屋の消滅に伴い%s部屋に移籍しました(編集：他一門)\n",
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
							if (shozokurikisisuu[ii]==0){break;}
						}
						if (shozokurikisisuu[ii]==0){break;}
					}
				}
			}
		}
	}

	tosiyorisuukakunin();

	//部屋移籍した力士を表示
	//////////////////////////////////////////////////////////////////
	{
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
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
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
		DrawString( 250 , 460 , "Hit any key" , CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
	}

	return;
}

void iseki_tandoku(int tosiyoriID,int heyaid_ikisaki,int heyaid_moto)//移籍する年寄ID、移籍先部屋ＩＤ、現部屋ＩＤ
{
	int i;
	FILE *fp;
	//所属部屋ID
	tosiyoridata[tosiyoriID].shozokuheyaid=heyaid_ikisaki;
	//所属一門ID
	for (i=0;i<TOSIYORISUU;i++){
		if (tosiyoridata[i].shozokuheyaid==tosiyoridata[tosiyoriID].shozokuheyaid
			&& i!=tosiyoriID){
			tosiyoridata[tosiyoriID].shozokuitimonid=tosiyoridata[i].shozokuitimonid;
			break;
		}
	}

	tosiyorisuukakunin();

	//ファイル書き込み
	tosiyorihyoujifilekakikomi(tosiyoriID);

	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s(%d才)親方が%s部屋から%s部屋に移籍しました(編集)\n",
	tosiyoridata[tosiyoriID].namestring,
	tosiyoridata[tosiyoriID].age,
	heyastring[heyaid_moto],
	heyastring[tosiyoridata[tosiyoriID].shozokuheyaid]);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s(%d才)親方が%s部屋から%s部屋に移籍しました",
	tosiyoridata[tosiyoriID].namestring,
	tosiyoridata[tosiyoriID].age,
	heyastring[heyaid_moto],
	heyastring[tosiyoridata[tosiyoriID].shozokuheyaid]);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	//////////////////////////////////////////////////////////////
	return;

}

void itimonshoumetu(int shoumetuitimonid)
{

	FILE *fp;
	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	//fprintf(fp,"%s一門は名称を変更するかどうかの処理で想定外の困ったなぁ\n",
	fprintf(fp,"%s一門は消滅します(編集)\n",
	itimondata[shoumetuitimonid].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	//DrawFormatString(0,369,CRWHITE,"%s一門は名称を変更するかどうかの処理で想定外の困ったなぁ",
	DrawFormatString(0,369,CRWHITE,"%s一門は消滅します",
	itimondata[shoumetuitimonid].namestring);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	//////////////////////////////////////////////////////////////

	strcpy(itimondata[shoumetuitimonid].namestring,"\0");
	itimondata[shoumetuitimonid].shuheyaid=-1;

	return;
}

void keishou(int tosiyoriID,int keishouid)//継承して残したい(功績顕著一代年寄の場合は残らず)年寄株ID(現師匠),継承の結果空き株(師匠が功績顕著だと師匠に昇格するので空き株にはならない)になる年寄株ID(現継承者)
{
	int i,ii;
	char namestring_backup[12];
	char namestring2_backup[12];
	for (i=0;i<12;i++){
		namestring_backup[i]=0;
		namestring2_backup[i]=0;
	}

	strcpy(namestring_backup,tosiyoridata[tosiyoriID].namestring);
	strcpy(namestring2_backup,tosiyoridata[keishouid].namestring);

	//師匠が功績顕著一代年寄の場合
	if (tosiyoriID>=200){

		//処理してよいかの確認
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawFormatString(100,200,CRWHITE,"%s親方が退職し、%s親方が部屋を継承し%s部屋に名称変更します。",
		namestring_backup,
		namestring2_backup,
		namestring2_backup);
		//DrawFormatString(100,225,CRWHITE,"%s部屋付になります(手抜き処理)",
		//heyastring[myheyaid]);
		DrawString(100,250,"それでもよろしいですか？",CRWHITE);
		DrawString(100,100,"キャンセル",CRGREEN);
		DrawString(400,100,"はい",CRGREEN);
		ScreenFlip() ;//裏画面を表画面にコピー
		while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
			Sleep(1);
		}
		while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
			Sleep(1);
		}
		while(1)
		{
			//キャンセル
			if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
				return;
			}
			//決定
			if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
				break;
			}
			// メッセージ処理
			if( ProcessMessage() == -1 ){mode=1;return ;}
			Sleep(1);
		}

		tosiyoridata[tosiyoriID].shozokuheyaid=-1;

		tosiyoridata[keishouid].sishouflag=tosiyoridata[tosiyoriID].sishouflag;
		if (tosiyoridata[keishouid].sishouflag==1){
			strcpy(heyastring[tosiyoridata[keishouid].shozokuheyaid],tosiyoridata[keishouid].namestring);
		}

		//リセット処理	
		tosiyoridata[tosiyoriID].age=0;
		tosiyoridata[tosiyoriID].category=0;
		tosiyoridata[tosiyoriID].startyear=0;
		tosiyoridata[tosiyoriID].rikisiid=-1;
		strcpy(tosiyoridata[tosiyoriID].sikona,"\0");
		tosiyoridata[tosiyoriID].sishouflag=0;
		if (tosiyoriID>=200){
			strcpy(tosiyoridata[tosiyoriID].namestring,"\0");
		}
		tosiyoridata[tosiyoriID].jinbou=0;
		tosiyoridata[tosiyoriID].rijiflag=0;
		tosiyoridata[tosiyoriID].keishousha_rikisiid=-1;
		tosiyoridata[tosiyoriID].keishousha_tosiyoriid=-1;

		tosiyorisuukakunin();

		tosiyorihyoujifilekakikomi(tosiyoriID);
		tosiyorihyoujifilekakikomi(keishouid);

		FILE *fp;
		//eventlog書き込み/////////////////////////////////////////
		fp = fopen("data/eventlog.txt","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
		fprintf(fp,"%s親方が退職し、%s親方が部屋を継承し%s部屋に名称変更しました(編集)\n",
		namestring_backup,
		namestring2_backup,
		namestring2_backup);
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}
		////////////////////////////////////////////////////////////
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		//DrawFormatString(0,369,CRWHITE,"%s一門は名称を変更するかどうかの処理で想定外の困ったなぁ",
		DrawFormatString(0,369,CRWHITE,"%s親方が退職し、%s親方が部屋を継承し%s部屋に名称変更しました",
		namestring_backup,
		namestring2_backup,
		namestring2_backup);
		DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		//////////////////////////////////////////////////////////////
	//師匠が通常株の場合
	}else{

		//処理してよいかの確認
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawFormatString(100,200,CRWHITE,"%s親方が退職し、%s親方が%sを継承します。",
		namestring_backup,
		namestring2_backup,
		namestring_backup);
		//DrawFormatString(100,225,CRWHITE,"%s部屋付になります(手抜き処理)",
		//heyastring[myheyaid]);
		DrawString(100,250,"それでもよろしいですか？",CRWHITE);
		DrawString(100,100,"キャンセル",CRGREEN);
		DrawString(400,100,"はい",CRGREEN);
		ScreenFlip() ;//裏画面を表画面にコピー
		while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
			Sleep(1);
		}
		while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
			Sleep(1);
		}
		while(1)
		{
			//キャンセル
			if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
				return;
			}
			//決定
			if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
				break;
			}
			// メッセージ処理
			if( ProcessMessage() == -1 ){mode=1;return ;}
			Sleep(1);
		}

		tosiyoridata[keishouid].shozokuheyaid=-1;
		tosiyoridata[tosiyoriID].age=tosiyoridata[keishouid].age;
		if (tosiyoridata[keishouid].category>=4){//一代年寄ならAカテクリアしているので
			tosiyoridata[tosiyoriID].category=1;
		}else{
			tosiyoridata[tosiyoriID].category=tosiyoridata[keishouid].category;
		}
		tosiyoridata[tosiyoriID].startyear=year;
		//tosiyoridata[tosiyoriID].shozokuheyaidはそのまま
		//tosiyoridata[tosiyoriID].shozokuitimonidもそのまま
		tosiyoridata[tosiyoriID].jinbou=tosiyoridata[keishouid].jinbou;
		tosiyoridata[tosiyoriID].rijiflag=0;
		tosiyoridata[tosiyoriID].rikisiid=tosiyoridata[keishouid].rikisiid;
		strcpy(tosiyoridata[tosiyoriID].sikona,tosiyoridata[keishouid].sikona);
		//tosiyoridata[tosiyoriID].sishouflag=tosiyoridata[keishouid].sishouflag;
		//tosiyoridata[tosiyoriID].namestirngはもちろんそのまま
		tosiyoridata[tosiyoriID].keishousha_tosiyoriid=-1;
		//tosiyoridata[tosiyoriID].keishousha_rikisiid=-1;
		//リセット処理	
		tosiyoridata[keishouid].age=0;
		tosiyoridata[keishouid].category=0;
		tosiyoridata[keishouid].startyear=0;
		tosiyoridata[keishouid].rikisiid=-1;
		strcpy(tosiyoridata[keishouid].sikona,"\0");
		tosiyoridata[keishouid].sishouflag=0;
		if (keishouid>=200){
			strcpy(tosiyoridata[keishouid].namestring,"\0");
		}
		tosiyoridata[keishouid].jinbou=0;
		tosiyoridata[keishouid].rijiflag=0;
		//tosiyoridata[keishouid].keishousha_rikisiid=-1;
		//tosiyoridata[keishouid].keishousha_tosiyoriid=-1;

		tosiyorisuukakunin();

		tosiyorihyoujifilekakikomi(tosiyoriID);
		tosiyorihyoujifilekakikomi(keishouid);

		FILE *fp;
		//eventlog書き込み/////////////////////////////////////////
		fp = fopen("data/eventlog.txt","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
		fprintf(fp,"%s親方が退職し、%s親方が%sを継承しました(編集)\n",
		namestring_backup,
		namestring2_backup,
		namestring_backup);
		//クローズ
		fclose(fp);
		if( ProcessMessage() == -1 ){mode=1;return ;}
		////////////////////////////////////////////////////////////
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		//DrawFormatString(0,369,CRWHITE,"%s一門は名称を変更するかどうかの処理で想定外の困ったなぁ",
		DrawFormatString(0,369,CRWHITE,"%s親方が退職し、%s親方が%sを継承しました",
		namestring_backup,
		namestring2_backup,
		namestring_backup);
		DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		//////////////////////////////////////////////////////////////
	}

	return;
}

void oyakatasentaku(int tosiyoriID)
{
	int i;

loop:
	//年寄データ表示
	tosiyoridatahyoji(tosiyorisentaku_id);
	DrawBox(440,345,637,345+15,CRBACK,TRUE);//右下部リンク部分消し
	DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分消し
	DrawBox(3,24,182,54,CRBACK,TRUE);//左上部分消し
	DrawBox(200,460,637,460+15,CRBACK,TRUE);//下部分消し
	DrawBox(187,24,637,86,CRBACK,TRUE);//メイン上部分消し

	//メイン上部分白色再描画
	DrawFormatString(187,24,CRWHITE,"ID%d %s",tosiyorisentaku_id,tosiyoridata[tosiyorisentaku_id].namestring);
	if (tosiyoridata[tosiyorisentaku_id].keishousha_rikisiid>=0 
		&& tosiyoridata[tosiyorisentaku_id].keishousha_rikisiid<RIKISISUU){//勘違いして通算力士IDを代入してしまっている可能性があるため念のため
		DrawFormatString(410,44,CRWHITE,"所有者 %s",namestring[tosiyoridata[tosiyorisentaku_id].keishousha_rikisiid]);
	}
	for (i=0;i<TOSIYORISUU;i++){
		if (tosiyoridata[i].keishousha_tosiyoriid==tosiyorisentaku_id){ 
			DrawFormatString(410,44,CRWHITE,"%s部屋の後継者",tosiyoridata[i].namestring);
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	DrawString(330,24,"現襲名者",CRWHITE);
	if (tosiyoridata[tosiyorisentaku_id].shozokuheyaid>=0){
		if (tosiyoridata[tosiyorisentaku_id].rikisiid>=0){
			DrawFormatString(410,24,CRWHITE,"元 %s(%d才)",tosiyoridata[tosiyorisentaku_id].sikona,tosiyoridata[tosiyorisentaku_id].age);
		}else{
			DrawFormatString(410,24,CRWHITE,"元 %s(%d才)",tosiyoridata[tosiyorisentaku_id].sikona,tosiyoridata[tosiyorisentaku_id].age);
		}
		if (tosiyoridata[tosiyorisentaku_id].shozokuitimonid>=0){
			if (itimondata[tosiyoridata[tosiyorisentaku_id].shozokuitimonid].shuheyaid==tosiyoridata[tosiyorisentaku_id].shozokuheyaid
				&& tosiyoridata[tosiyorisentaku_id].sishouflag==1){
				DrawString(187,44,"所属一門",CRWHITE);
				DrawFormatString(270,44,CRWHITE,"%s(一門主)",itimondata[tosiyoridata[tosiyorisentaku_id].shozokuitimonid].namestring);
			}else{
				DrawString(187,44,"所属一門",CRWHITE);
				DrawFormatString(270,44,CRWHITE,"%s",itimondata[tosiyoridata[tosiyorisentaku_id].shozokuitimonid].namestring);
			}
		}
		DrawString(187,60,"所属部屋",CRWHITE);
		if (tosiyoridata[tosiyoriID].sishouflag==1){
			DrawFormatString(270,60,CRWHITE,"%s部屋師匠",heyastring[tosiyoridata[tosiyorisentaku_id].shozokuheyaid]);
		}else{
			DrawFormatString(270,60,CRWHITE,"%s部屋付き",heyastring[tosiyoridata[tosiyorisentaku_id].shozokuheyaid]);
		}
		if (tosiyoridata[tosiyorisentaku_id].category==1){
			DrawFormatStringToHandle(187,78,CRWHITE,FontHandle12,"人望:%d 　カテゴリー:A",tosiyoridata[tosiyorisentaku_id].jinbou);
		}
		if (tosiyoridata[tosiyorisentaku_id].category==2){
			DrawFormatStringToHandle(187,78,CRWHITE,FontHandle12,"人望:%d 　カテゴリー:B",tosiyoridata[tosiyorisentaku_id].jinbou);
		}
		if (tosiyoridata[tosiyorisentaku_id].category==3){
			DrawFormatStringToHandle(187,78,CRWHITE,FontHandle12,"人望:%d 　カテゴリー:C",tosiyoridata[tosiyorisentaku_id].jinbou);
		}
		if (tosiyoridata[tosiyorisentaku_id].category==4){
			DrawFormatStringToHandle(187,78,CRWHITE,FontHandle12,"人望:%d 　カテゴリー:功績顕著一代",tosiyoridata[tosiyorisentaku_id].jinbou);
		}
		if (tosiyoridata[tosiyorisentaku_id].category==5){
			DrawFormatStringToHandle(187,78,CRWHITE,FontHandle12,"人望:%d 　カテゴリー:期間限定横綱5年",tosiyoridata[tosiyorisentaku_id].jinbou);
		}
		if (tosiyoridata[tosiyorisentaku_id].category==6){
			DrawFormatStringToHandle(187,78,CRWHITE,FontHandle12,"人望:%d 　カテゴリー:期間限定大関3年",tosiyoridata[tosiyorisentaku_id].jinbou);
		}
	}else{
		DrawString(410,24,"なし(空き株)",CRWHITE);
	}
	if ((tosiyoridata[tosiyorisentaku_id].rijiflag&0x0f)>0 && (tosiyoridata[tosiyorisentaku_id].rijiflag&0x0f)<11){
		DrawFormatString(430,60,CRWHITE,"%s",namestring_riji[(tosiyoridata[tosiyorisentaku_id].rijiflag&0x0f)-1]);
	}


	DrawFormatStringToHandle(240,5,CRWHITE,FontHandle12,"年寄株%sを所有(継承)する親方を決定する画面",tosiyoridata[tosiyoriID].namestring);
	DrawString(5,30,"キャンセル",CRGREEN);
	DrawString(120,30,"決定",CRGREEN);


	ScreenFlip() ;//裏画面を表画面にコピー

	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//キャンセル
		if (get_mouseclick(5,30,85,30+16)==1 ){
			break;
		}
		//決定
		if (get_mouseclick(120,30,152,30+16)==1 ){

			tosiyorisuukakunin();

			//同じ株を除外
			if (tosiyorisentaku_id==tosiyoriID){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(100,200,"同じ株です",CRWHITE);
				DrawString(100,300,"HIT ANY KEY",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				return;
			}

			//すでに他の所有者（継承予定者）になっている親方を除外
			{
				int i;
				int hishoyuuid=0;
				hishoyuuid=-1;
				for (i=0;i<TOSIYORISUU;i++){
					if (tosiyoridata[i].keishousha_tosiyoriid==tosiyorisentaku_id){
						hishoyuuid=i;
						break;
					}
				}
				if (hishoyuuid!=-1){
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawFormatString(100,200,CRWHITE,"%s親方はすでに年寄株%sの継承者になっています。",tosiyoridata[tosiyorisentaku_id].namestring,tosiyoridata[hishoyuuid].namestring);
					DrawString(100,300,"HIT ANY KEY",CRWHITE);
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitKey();
					return;
				}
			}
			//空き株を除外
			if (tosiyoridata[tosiyorisentaku_id].shozokuheyaid==-1){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(100,200,"空き株です",CRWHITE);
				DrawString(100,300,"HIT ANY KEY",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				return;
			}

			//部屋の師匠警告
			if (tosiyoridata[tosiyorisentaku_id].shozokuheyaid!=-1 && tosiyoridata[tosiyorisentaku_id].sishouflag==1){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(100,200,"部屋の師匠が他の年寄株の継承者(所有者)になること",CRWHITE);
				DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
				DrawString(100,250,"不具合の可能性が高まりますが、それでもよろしいですか？",CRWHITE);
				DrawString(100,100,"キャンセル",CRGREEN);
				DrawString(400,100,"はい",CRGREEN);
				ScreenFlip() ;//裏画面を表画面にコピー
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
				}
				while(1)
				{
					//キャンセル
					if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
						return;
					}
					//決定
					if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 ){mode=1;return ;}
					Sleep(1);
				}
			}

			//異なる部屋の継承者警告
			if (tosiyoridata[tosiyorisentaku_id].shozokuheyaid!=tosiyoridata[tosiyoriID].shozokuheyaid){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(100,200,"異なる部屋の親方が継承者(所有者)になること",CRWHITE);
				DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
				DrawString(100,250,"不具合の可能性が高まりますが、それでもよろしいですか？",CRWHITE);
				DrawString(100,100,"キャンセル",CRGREEN);
				DrawString(400,100,"はい",CRGREEN);
				ScreenFlip() ;//裏画面を表画面にコピー
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
				}
				while(1)
				{
					//キャンセル
					if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
						return;
					}
					//決定
					if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 ){mode=1;return ;}
					Sleep(1);
				}
			}

			//上書き警告
			if (tosiyoridata[tosiyoriID].keishousha_rikisiid!=-1 
			|| tosiyoridata[tosiyoriID].keishousha_tosiyoriid!=-1){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (tosiyoridata[tosiyoriID].keishousha_rikisiid!=-1){
					DrawFormatString(10,200,CRWHITE,"現在の年寄株%sの継承者(所有者)は%sです。",tosiyoridata[tosiyoriID].namestring,namestring[tosiyoridata[tosiyoriID].keishousha_rikisiid]);
				}else{
					DrawFormatString(10,200,CRWHITE,"現在の年寄株%sの継承者(所有者)は%sです。",tosiyoridata[tosiyoriID].namestring,tosiyoridata[tosiyoridata[tosiyoriID].keishousha_tosiyoriid].namestring);
				}
				DrawString(100,250,"上書きしますか？",CRWHITE);
				DrawString(100,100,"キャンセル",CRGREEN);
				DrawString(400,100,"はい",CRGREEN);
				ScreenFlip() ;//裏画面を表画面にコピー
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
				}
				while(1)
				{
					//キャンセル
					if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
						return;
					}
					//決定
					if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 ){mode=1;return ;}
					Sleep(1);
				}
			}

			//留保をとる
			tosiyoridata[tosiyoriID].keishousha_rikisiid=-1;
			tosiyoridata[tosiyoriID].keishousha_tosiyoriid=-1;
			//新所有者留保
			tosiyoridata[tosiyoriID].keishousha_tosiyoriid=tosiyorisentaku_id;

			tosiyorisuukakunin();

			if (tosiyoriID<106){
				tosiyorihyoujifilekakikomi(tosiyoriID);
			}

			FILE *fp;
			//eventlog書き込み/////////////////////////////////////////
			fp = fopen("data/eventlog.txt","a");
			// オープンできなかったらここで終了
			if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
			fprintf(fp,"年寄株%sは%s親方が継承する予定になりました(編集)\n",
			tosiyoridata[tosiyoriID].namestring,
			tosiyoridata[tosiyorisentaku_id].namestring);
			//クローズ
			fclose(fp);
			if( ProcessMessage() == -1 ){mode=1;return ;}
			////////////////////////////////////////////////////////////
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawFormatString(100,200,CRWHITE,"年寄株%sは%s親方が継承する予定になりました",
			tosiyoridata[tosiyoriID].namestring,
			tosiyoridata[tosiyorisentaku_id].namestring);
			DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			//////////////////////////////////////////////////////////////

			return;

		}
		//歴代表示のページ数減少
		if (get_mouseclick(200,170+12*15,200+24,170+12*15+12)==1 ){
			if (page_tosiyori>0){
				page_tosiyori--;
				WaitTimer(200);
				goto loop;
			}
		}
		//歴代表示のページ数増加
		if (get_mouseclick(296,170+12*15,296+24,170+12*15+12)==1 ){
			if (page_tosiyori<1000){
				page_tosiyori++;
				WaitTimer(200);
				goto loop;
			}
		}
		if (tosiyorisentaku_page>0){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				tosiyorisentaku_page--;
				tosiyorisentaku_num=0;
				tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
				WaitTimer(200);
				goto loop;
			}
		}
		//if (tosiyorisentaku_page<(int)((106-1)/40)){
		if (tosiyorisentaku_page<(int)((TOSIYORISUU-1)/40)){
			if (get_mouseclick_buttonDOWN() == 1){//左リストUPボタンをクリック
				tosiyorisentaku_page++;
				tosiyorisentaku_num=0;
				tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
				WaitTimer(200);
				goto loop;
			}
		}
		for (i=0;i<40;i++){
			if (get_mouseclick_list(i) == 1){//リスト上の年寄名をクリックしたら
				if (i+tosiyorisentaku_page*40<TOSIYORISUU){
					tosiyorisentaku_num=i;
					tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
					WaitTimer(200);
					goto loop;
				}
			}
		}
		if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
			if (tosiyorisentaku_page>0 && tosiyorisentaku_num<2){
				tosiyorisentaku_page--;
				tosiyorisentaku_num+=38;
				tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
				WaitTimer(200);
				goto loop;
			}else if (tosiyorisentaku_num>1){
				tosiyorisentaku_num=tosiyorisentaku_num-2;
				tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
				WaitTimer(200);
				goto loop;
			}
		}
		if(CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
			if (tosiyorisentaku_page<(int)((TOSIYORISUU-1)/40) && tosiyorisentaku_num>37){
				tosiyorisentaku_page++;
				tosiyorisentaku_num-=38;
				tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
				WaitTimer(200);
				goto loop;
			}else if (tosiyorisentaku_num<38){
				if (!(tosiyorisentaku_page==2 && tosiyorisentaku_num>23)){
					tosiyorisentaku_num=tosiyorisentaku_num+2;
					tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
					WaitTimer(200);
					goto loop;
				}
			}
		}
		if( CheckHitKey_test(KEY_INPUT_RIGHT)){//→キー
			if ((tosiyorisentaku_num+2)%2==0 ){
					tosiyorisentaku_num=tosiyorisentaku_num+1;
					tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
					WaitTimer(200);
					goto loop;
			}
		}
		if( CheckHitKey_test(KEY_INPUT_LEFT)){//←キー
			if ((tosiyorisentaku_num+2)%2==1 ){
				tosiyorisentaku_num=tosiyorisentaku_num-1;
				tosiyorisentaku_id=tosiyorisentaku_num+tosiyorisentaku_page*40;
				WaitTimer(200);
				goto loop;
			}
		}

		// メッセージ処理
		if( ProcessMessage() == -1 ){mode=1;return ;}
		Sleep(1);
	}

	return;
}

void genekirikisisentaku(int tosiyoriID)
{
	int i;

loop:
	//現役力士データ表示
	torikumi_or_seisekiflag=3;
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	game_main_backscreen();//基本画面表示
	rikisidatahyoji(rikisisentaku_id);



	DrawBox(187,369,637,477,CRBACK,TRUE);//下部リンク部分消し
	DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分消し
	DrawBox(3,24,182,54,CRBACK,TRUE);//左上部分消し
	DrawBox(187,25+64,187+32,25+64+15,CRBACK,TRUE);//作戦ボタン部分消し
	DrawBox(505-40-40,25+64,505-40-40+32,25+64+15,CRBACK,TRUE);//作戦ボタン部分消し
	DrawBox(505-40,24,637,24+16,CRBACK,TRUE);//編集ボタン～取組見る見ない選択部分消し
	DrawBox(rx1[0]-11,ry1[0]+3-3,637,ry1[0]+3+14,CRBACK,TRUE);//右タブ選択部分消し
	DrawBox(187,72,187+16*7,72+15,CRBACK,TRUE);//部屋名緑色消し

	DrawFormatString(187,72,CRWHITE,"%s部屋",
	heyastring[rikisidata[rikisisentaku_id].heyaid]
	);

	DrawFormatStringToHandle(150,5,CRWHITE,FontHandle12,"年寄株%sを所有(継承)する現役力士を決定する画面",tosiyoridata[tosiyoriID].namestring);
	DrawString(5,30,"キャンセル",CRGREEN);
	DrawString(120,30,"決定",CRGREEN);




	ScreenFlip() ;//裏画面を表画面にコピー

	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//キャンセル
		if (get_mouseclick(5,30,85,30+16)==1 ){
			break;
		}
		//決定
		if (get_mouseclick(120,30,152,30+16)==1 ){
			tosiyorisuukakunin();

			//すでに他の所有者（継承予定者）になっている力士を除外
			{
				int i;
				int hishoyuuid=0;
				hishoyuuid=-1;
				for (i=0;i<TOSIYORISUU;i++){
					if (tosiyoridata[i].keishousha_rikisiid==rikisisentaku_id){
						hishoyuuid=i;
						break;
					}
				}
				if (hishoyuuid!=-1){
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawFormatString(100,200,CRWHITE,"%sはすでに年寄株%sの継承者になっています。",namestring[rikisisentaku_id],tosiyoridata[hishoyuuid].namestring);
					DrawString(100,300,"HIT ANY KEY",CRWHITE);
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitKey();
					return;
				}
			}


			//異なる部屋の継承者警告
			if (rikisidata[rikisisentaku_id].heyaid!=tosiyoridata[tosiyoriID].shozokuheyaid 
			&& tosiyoridata[tosiyoriID].sishouflag==1){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(100,200,"異なる部屋の継承者になること",CRWHITE);
				DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
				DrawString(100,250,"不具合の可能性が高まりますが、それでもよろしいですか？",CRWHITE);
				DrawString(100,100,"キャンセル",CRGREEN);
				DrawString(400,100,"はい",CRGREEN);
				ScreenFlip() ;//裏画面を表画面にコピー
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
				}
				while(1)
				{
					//キャンセル
					if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
						return;
					}
					//決定
					if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 ){mode=1;return ;}
					Sleep(1);
				}
			}
			//上書き警告
			if (tosiyoridata[tosiyoriID].keishousha_rikisiid!=-1 
			|| tosiyoridata[tosiyoriID].keishousha_tosiyoriid!=-1){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (tosiyoridata[tosiyoriID].keishousha_rikisiid!=-1){
					DrawFormatString(10,200,CRWHITE,"現在の年寄株%sの継承者(所有者)は%sです。",tosiyoridata[tosiyoriID].namestring,namestring[tosiyoridata[tosiyoriID].keishousha_rikisiid]);
				}else{
					DrawFormatString(10,200,CRWHITE,"現在の年寄株%sの継承者(所有者)は%sです。",tosiyoridata[tosiyoriID].namestring,tosiyoridata[tosiyoridata[tosiyoriID].keishousha_tosiyoriid].namestring);
				}
				DrawString(100,250,"上書きしますか？",CRWHITE);
				DrawString(100,100,"キャンセル",CRGREEN);
				DrawString(400,100,"はい",CRGREEN);
				ScreenFlip() ;//裏画面を表画面にコピー
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
				}
				while(1)
				{
					//キャンセル
					if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
						return;
					}
					//決定
					if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 ){mode=1;return ;}
					Sleep(1);
				}
			}

			//留保をとる
			tosiyoridata[tosiyoriID].keishousha_rikisiid=-1;
			tosiyoridata[tosiyoriID].keishousha_tosiyoriid=-1;
			//新所有者留保
			tosiyoridata[tosiyoriID].keishousha_rikisiid=rikisisentaku_id;

			tosiyorisuukakunin();

			if (tosiyoriID<106){
				tosiyorihyoujifilekakikomi(tosiyoriID);
			}

			FILE *fp;
			//eventlog書き込み/////////////////////////////////////////
			fp = fopen("data/eventlog.txt","a");
			// オープンできなかったらここで終了
			if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
			if (tosiyoridata[tosiyoriID].sishouflag==1){
				fprintf(fp,"年寄株%sは%sが継承する予定になりました(編集)\n",
				tosiyoridata[tosiyoriID].namestring,
				namestring[rikisisentaku_id]);
			}else{
				fprintf(fp,"年寄株%sは%sが所有しました(編集)\n",
				tosiyoridata[tosiyoriID].namestring,
				namestring[rikisisentaku_id]);
			}
			//クローズ
			fclose(fp);
			if( ProcessMessage() == -1 ){mode=1;return ;}
			////////////////////////////////////////////////////////////
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			if (tosiyoridata[tosiyoriID].sishouflag==1){
				DrawFormatString(100,200,CRWHITE,"年寄株%sは%sが継承する予定になりました",
				tosiyoridata[tosiyoriID].namestring,
				namestring[rikisisentaku_id]);
			}else{
				DrawFormatString(100,200,CRWHITE,"年寄株%sは%sが所有しました",
				tosiyoridata[tosiyoriID].namestring,
				namestring[rikisisentaku_id]);
			}
			DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			//////////////////////////////////////////////////////////////

			return;
		}


		if (get_mouseclick(3,56,41,78)==1 && bandukejun_or_jiheyaflag!=0){
			bandukejun_or_jiheyaflag=0;
//			rikisisentaku_page=(int)((rikisidata[rikisisentaku_id].bandukejun+20)/20)-1;
//			rikisisentaku_num=((rikisidata[rikisisentaku_id].bandukejun+20)%20)*2;
			rikisisentaku_id=bandukejunid[(rikisisentaku_num+2)/2-1+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
		}
		if (get_mouseclick(42,56,79,78)==1 && bandukejun_or_jiheyaflag!=1){
			bandukejun_or_jiheyaflag=1;
			if ((rikisisentaku_num_jiheya+2)/2>shozokurikisisuu[myheyaid]){
				rikisisentaku_num_jiheya=0;
			}
			rikisisentaku_id=heyabandukejunid[myheyaid][(rikisisentaku_num_jiheya+2)/2-1];
				WaitTimer(200);
				goto loop;
		}
		if (get_mouseclick(80,56,116,78)==1 && bandukejun_or_jiheyaflag!=2){
			int count=0;
			bandukejun_or_jiheyaflag=2;
			//「ver2.44」で追加
			for (i=0;i<RIKISISUU;i++){
				if (rikisidata[i].realmodeflag==1){
					rikisidata[i].torikumimiruflag=1;
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			count=0;//取組見る力士たちの番付順力士IDを検索
			for (i=0;i<RIKISISUU;i++){//
				//if( ProcessMessage() == -1 ){mode=1;return ;}
				if (rikisidata[bandukejunid[i]].torikumimiruflag==1){
					torimi_bandukejunid[count]=bandukejunid[i];
					count++;
				}
			}
			torimisuu=count;
			//「ver2.44」で追加ここまで
			if (torimisuu!=0){
				rikisisentaku_id=torimi_bandukejunid[(torimi_rikisisentaku_num+2)/2-1+torimi_rikisisentaku_page*20];
			}
				WaitTimer(200);
				goto loop;
		}
		if (get_mouseclick(117,56,151,78)==1 && bandukejun_or_jiheyaflag!=3){
			if (superrikisisuu[2]==0){
			bandukejun_or_jiheyaflag=3;
			if (rinnesuu!=0){
				rikisisentaku_id=rinne_bandukejunid[(rinne_rikisisentaku_num+2)/2-1+rinne_rikisisentaku_page*20];
			}
				WaitTimer(200);
				goto loop;
			}
		}
		if (get_mouseclick(152,56,184,78)==1 && bandukejun_or_jiheyaflag!=4){
			bandukejun_or_jiheyaflag=4;
			if (kyuujousuu!=0){
				rikisisentaku_id=kyuujou_bandukejunid[(kyuujou_rikisisentaku_num+2)/2-1+kyuujou_rikisisentaku_page*20];
			}
				WaitTimer(200);
				goto loop;
		}

		for (i=0;i<20;i++){//左リストタブ番付順のときの左リストクリック処理
			//if( ProcessMessage() == -1 ){mode=1;return ;}
			if (bandukejun_or_jiheyaflag==0 && (get_mouseclick_list(i*2) == 1 || get_mouseclick_list(i*2+1)==1) ){//リスト上の力士名をクリックしたら
				if (i+rikisisentaku_page*20<RIKISISUU){
					rikisisentaku_num=i*2;
					rikisisentaku_id=bandukejunid[i+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}
		}
		for (i=0;i<shozokurikisisuu[myheyaid];i++){//左リストタブ自部屋のときの左リストクリック処理
			//if( ProcessMessage() == -1 ){mode=1;return ;}
			if (bandukejun_or_jiheyaflag==1 && (get_mouseclick_list(i*2+1) == 1 || get_mouseclick_list(i*2)==1) ){//自部屋表示の左リスト上の力士名をクリックしたら
				rikisisentaku_num_jiheya=i*2;
				rikisisentaku_id=heyabandukejunid[myheyaid][i];
				WaitTimer(200);
				goto loop;
			}
		}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (i=0;i<20;i++){//左リストタブ取見のときの左リストクリック処理
			//if( ProcessMessage() == -1 ){mode=1;return ;}
			if (bandukejun_or_jiheyaflag==2 && (get_mouseclick_list(i*2) == 1 || get_mouseclick_list(i*2+1)==1) ){//リスト上の力士名をクリックしたら
				if (i+torimi_rikisisentaku_page*20<torimisuu){
					torimi_rikisisentaku_num=i*2;
					rikisisentaku_id=torimi_bandukejunid[i+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}
		}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (superrikisisuu[2]==0){
		for (i=0;i<20;i++){//左リストタブ輪廻のときの左リストクリック処理
			//if( ProcessMessage() == -1 ){mode=1;return ;}
			if (bandukejun_or_jiheyaflag==3 && (get_mouseclick_list(i*2) == 1 || get_mouseclick_list(i*2+1)==1) ){//リスト上の力士名をクリックしたら
				if (i+rinne_rikisisentaku_page*20<rinnesuu){
					rinne_rikisisentaku_num=i*2;
					rikisisentaku_id=rinne_bandukejunid[i+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}
		}
		}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (i=0;i<20;i++){//左リストタブ休場のときの左リストクリック処理
			//if( ProcessMessage() == -1 ){mode=1;return ;}
			if (bandukejun_or_jiheyaflag==4 && (get_mouseclick_list(i*2) == 1 || get_mouseclick_list(i*2+1)==1) ){//リスト上の力士名をクリックしたら
				if (i+kyuujou_rikisisentaku_page*20<kyuujousuu){
					kyuujou_rikisisentaku_num=i*2;
					rikisisentaku_id=kyuujou_bandukejunid[i+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}
		}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (bandukejun_or_jiheyaflag==0){
			if (get_mouseclick_buttonkensakuLEFT() == 1){//左リスト検索ボタンをクリック
				rikisisentaku_id=kensaku_allrikisi();
				rikisisentaku_page=(int)((rikisidata[rikisisentaku_id].bandukejun+20)/20)-1;
				rikisisentaku_num=((rikisidata[rikisisentaku_id].bandukejun+20)%20)*2;
				WaitTimer(200);
				goto loop;
			}
		}
		if (bandukejun_or_jiheyaflag==0 && rikisisentaku_page>0){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				rikisisentaku_page--;
				rikisisentaku_num=0;
				rikisisentaku_id=bandukejunid[rikisisentaku_num+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}
		if (bandukejun_or_jiheyaflag==0 && rikisisentaku_page<(int)((RIKISISUU+19)/20)-1){
			if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
				rikisisentaku_page++;
				rikisisentaku_num=0;
				rikisisentaku_id=bandukejunid[rikisisentaku_num+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}
		if (bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_page>0){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				torimi_rikisisentaku_page--;
				torimi_rikisisentaku_num=0;
				rikisisentaku_id=torimi_bandukejunid[torimi_rikisisentaku_num+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}
		if (bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_page<(int)((torimisuu+19)/20)-1){
			if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
				torimi_rikisisentaku_page++;
				torimi_rikisisentaku_num=0;
				rikisisentaku_id=torimi_bandukejunid[torimi_rikisisentaku_num+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}

		if (bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_page>0){
			if (superrikisisuu[2]==0){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				rinne_rikisisentaku_page--;
				rinne_rikisisentaku_num=0;
				rikisisentaku_id=rinne_bandukejunid[rinne_rikisisentaku_num+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
			}
		}
		if (bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_page<(int)((rinnesuu+19)/20)-1){
			if (superrikisisuu[2]==0){
			if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
				rinne_rikisisentaku_page++;
				rinne_rikisisentaku_num=0;
				rikisisentaku_id=rinne_bandukejunid[rinne_rikisisentaku_num+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
			}
		}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

		if (bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_page>0){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				kyuujou_rikisisentaku_page--;
				kyuujou_rikisisentaku_num=0;
				rikisisentaku_id=kyuujou_bandukejunid[kyuujou_rikisisentaku_num+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}
		if (bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_page<(int)((kyuujousuu+19)/20)-1){
			if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
				kyuujou_rikisisentaku_page++;
				kyuujou_rikisisentaku_num=0;
				rikisisentaku_id=kyuujou_bandukejunid[kyuujou_rikisisentaku_num+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}

	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
			if (bandukejun_or_jiheyaflag==0 && rikisisentaku_num==0 && rikisisentaku_page>0){
				rikisisentaku_page--;
				rikisisentaku_num=38;
				rikisisentaku_id=bandukejunid[(rikisisentaku_num+2)/2-1+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if (bandukejun_or_jiheyaflag==0 && rikisisentaku_num>1){
				rikisisentaku_num=rikisisentaku_num-2;
				rikisisentaku_id=bandukejunid[(rikisisentaku_num+2)/2-1+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if(bandukejun_or_jiheyaflag==1 && rikisisentaku_num_jiheya>1){
				rikisisentaku_num_jiheya-=2;
				rikisisentaku_id=heyabandukejunid[myheyaid][(rikisisentaku_num_jiheya+2)/2-1];
				WaitTimer(200);
				goto loop;
			}else if(bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_num==0 && torimi_rikisisentaku_page>0){
				torimi_rikisisentaku_page--;
				torimi_rikisisentaku_num=38;
				rikisisentaku_id=torimi_bandukejunid[(torimi_rikisisentaku_num+2)/2-1+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if (bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_num>1){
				torimi_rikisisentaku_num-=2;
				rikisisentaku_id=torimi_bandukejunid[(torimi_rikisisentaku_num+2)/2-1+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if(bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_num==0 && rinne_rikisisentaku_page>0){
				if (superrikisisuu[2]==0){
				rinne_rikisisentaku_page--;
				rinne_rikisisentaku_num=38;
				rikisisentaku_id=rinne_bandukejunid[(rinne_rikisisentaku_num+2)/2-1+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}else if (bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_num>1){
				if (superrikisisuu[2]==0){
				rinne_rikisisentaku_num-=2;
				rikisisentaku_id=rinne_bandukejunid[(rinne_rikisisentaku_num+2)/2-1+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}else if(bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_num==0 && kyuujou_rikisisentaku_page>0){
				kyuujou_rikisisentaku_page--;
				kyuujou_rikisisentaku_num=38;
				rikisisentaku_id=kyuujou_bandukejunid[(kyuujou_rikisisentaku_num+2)/2-1+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if (bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_num>1){
				kyuujou_rikisisentaku_num-=2;
				rikisisentaku_id=kyuujou_bandukejunid[(kyuujou_rikisisentaku_num+2)/2-1+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if( CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
			if (bandukejun_or_jiheyaflag==0 && rikisisentaku_num==38 && rikisisentaku_page<(int)((RIKISISUU+19)/20)-1){
				rikisisentaku_page++;
				rikisisentaku_num=0;
				rikisisentaku_id=bandukejunid[(rikisisentaku_num+2)/2-1+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if ((bandukejun_or_jiheyaflag==0 && rikisisentaku_num<38 && rikisisentaku_page<(int)((RIKISISUU+19)/20)-1)
						|| (bandukejun_or_jiheyaflag==0 && rikisisentaku_num<(RIKISISUU%20)*2-2 && rikisisentaku_page==(int)((RIKISISUU+19)/20)-1)){
				rikisisentaku_num=rikisisentaku_num+2;
				rikisisentaku_id=bandukejunid[(rikisisentaku_num+2)/2-1+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if(bandukejun_or_jiheyaflag==1 && rikisisentaku_num_jiheya<shozokurikisisuu[myheyaid]*2-2){
				rikisisentaku_num_jiheya+=2;
				rikisisentaku_id=heyabandukejunid[myheyaid][(rikisisentaku_num_jiheya+2)/2-1];
				WaitTimer(200);
				goto loop;
			}else if(bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_num==38 && torimi_rikisisentaku_page<(int)((torimisuu+19)/20)-1){
				torimi_rikisisentaku_page++;
				torimi_rikisisentaku_num=0;
				rikisisentaku_id=torimi_bandukejunid[(torimi_rikisisentaku_num+2)/2-1+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if ((bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_num<38 && torimi_rikisisentaku_page<(int)((torimisuu+19)/20)-1)
						|| (bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_num<(torimisuu%20)*2-2 && torimi_rikisisentaku_page==(int)((torimisuu+19)/20)-1)){
				torimi_rikisisentaku_num+=2;
				rikisisentaku_id=torimi_bandukejunid[(torimi_rikisisentaku_num+2)/2-1+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if(bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_num==38 && rinne_rikisisentaku_page<(int)((rinnesuu+19)/20)-1){
				if (superrikisisuu[2]==0){
				rinne_rikisisentaku_page++;
				rinne_rikisisentaku_num=0;
				rikisisentaku_id=rinne_bandukejunid[(rinne_rikisisentaku_num+2)/2-1+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}else if ((bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_num<38 && rinne_rikisisentaku_page<(int)((rinnesuu+19)/20)-1)
						|| (bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_num<(rinnesuu%20)*2-2 && rinne_rikisisentaku_page==(int)((rinnesuu+19)/20)-1)){
				if (superrikisisuu[2]==0){
				rinne_rikisisentaku_num+=2;
				rikisisentaku_id=rinne_bandukejunid[(rinne_rikisisentaku_num+2)/2-1+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}else if(bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_num==38 && kyuujou_rikisisentaku_page<(int)((kyuujousuu+19)/20)-1){
				kyuujou_rikisisentaku_page++;
				kyuujou_rikisisentaku_num=0;
				rikisisentaku_id=kyuujou_bandukejunid[(kyuujou_rikisisentaku_num+2)/2-1+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if ((bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_num<38 && kyuujou_rikisisentaku_page<(int)((kyuujousuu+19)/20)-1)
						|| (bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_num<(kyuujousuu%20)*2-2 && kyuujou_rikisisentaku_page==(int)((kyuujousuu+19)/20)-1)){
				kyuujou_rikisisentaku_num+=2;
				rikisisentaku_id=kyuujou_bandukejunid[(kyuujou_rikisisentaku_num+2)/2-1+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){mode=1;return ;}
		Sleep(1);
	}

	return;
}

void retirerikisisentaku(int tosiyoriID)
{

//void retirerikisi_new(int hyojiheyaid)
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
	int hyojiheyaid=0;
	hyojiheyaid=-1;
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
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
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
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
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



	r_hyojikirikaeflag=0;
	r_torikumi_or_seisekiflag=3;

loop:

	retirerikisi_hyoji(ichijouhou,ichijouhou_jiheya,ichijouhou_saikoui);

	DrawBox(187,369,637,420,CRBACK,TRUE);//下部リンク部分消し
	DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分消し
	DrawBox(3,24,182,54,CRBACK,TRUE);//左上部分消し
	DrawBox(rx1[0]-11,ry1[0]+3-3,637,ry1[0]+3+14,CRBACK,TRUE);//右タブ選択部分消し

	DrawFormatStringToHandle(240,5,CRWHITE,FontHandle12,"年寄株%sを襲名する引退力士を決定する画面",tosiyoridata[tosiyoriID].namestring);
	DrawString(5,30,"キャンセル",CRGREEN);
	DrawString(120,30,"決定",CRGREEN);



	ScreenFlip();

	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//キャンセル
		if (get_mouseclick(5,30,85,30+16)==1 ){
			break;
		}
		//決定
		if (get_mouseclick(120,30,152,30+16)==1 ){
			int i;

			//すでに襲名済み引退力士は除く
			if (G_shuumeizumitosiyoriid!=-1){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawFormatString(100,200,CRWHITE,"すでに年寄株%sを襲名しています。",tosiyoridata[G_shuumeizumitosiyoriid].namestring);
				DrawString(100,300,"HIT ANY KEY",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);
				goto loop;
			}

			//処理してよいかの確認
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawFormatString(100,200,CRWHITE,"年寄株%sを元%sが襲名します。",
			tosiyoridata[tosiyoriID].namestring,
			G_sikona);
			DrawFormatString(100,225,CRWHITE,"%s部屋付になります(手抜き処理)",
			heyastring[myheyaid]);
			DrawString(100,250,"それでもよろしいですか？",CRWHITE);
			DrawString(100,100,"キャンセル",CRGREEN);
			DrawString(400,100,"はい",CRGREEN);
			ScreenFlip() ;//裏画面を表画面にコピー
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				Sleep(1);
			}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				Sleep(1);
			}
			while(1)
			{
				//キャンセル
				if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
					return;
				}
				//決定
				if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 ){mode=1;return ;}
				Sleep(1);
			}

			tosiyoridata[tosiyoriID].age=G_age;
			if (tosiyoriID<106){
				if (G_category==5 || G_category==6){
					tosiyoridata[tosiyoriID].category=1;
				}else if (G_category==0){
					tosiyoridata[tosiyoriID].category=3;
				}else{
					tosiyoridata[tosiyoriID].category=G_category;
				}
			}else if (tosiyoriID<300){
				tosiyoridata[tosiyoriID].category=4;
			}else{
				if (G_category==5 || G_category==6){
					tosiyoridata[tosiyoriID].category=G_category;
				}else{
					tosiyoridata[tosiyoriID].category=6;
				}
			}
			tosiyoridata[tosiyoriID].startyear=year;
			tosiyoridata[tosiyoriID].shozokuheyaid=myheyaid;//とりあえず
			for (i=0;i<ITIMONSUU;i++){
				if (itimondata[i].shuheyaid==tosiyoridata[tosiyoriID].shozokuheyaid){
					tosiyoridata[tosiyoriID].shozokuitimonid=i;
					break;
				}
			}
			tosiyoridata[tosiyoriID].rikisiid=G_rikisiid;
			strcpy(tosiyoridata[tosiyoriID].sikona,G_sikona);
			tosiyoridata[tosiyoriID].sishouflag=0;
			//tosiyoridata[tosiyoriID].namestring;//年寄名跡名
			tosiyoridata[tosiyoriID].jinbou=0;
			tosiyoridata[tosiyoriID].rijiflag=0;
			//tosiyoridata[tosiyoriID].keishousha_rikisiid;
			//tosiyoridata[tosiyoriID].keishousha_tosiyoriid;

			tosiyorisuukakunin();

			tosiyorihyoujifilekakikomi(tosiyoriID);

			FILE *fp;
			//eventlog書き込み/////////////////////////////////////////
			fp = fopen("data/eventlog.txt","a");
			// オープンできなかったらここで終了
			if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
			fprintf(fp,"年寄株%sは元%sが襲名しました(編集)\n",
			tosiyoridata[tosiyoriID].namestring,
			tosiyoridata[tosiyoriID].sikona);
			fprintf(fp,"%s一門%s部屋に部屋付親方として所属します(編集)\n",
			itimondata[tosiyoridata[tosiyoriID].shozokuitimonid].namestring,
			heyastring[tosiyoridata[tosiyoriID].shozokuheyaid]);
			//クローズ
			fclose(fp);
			if( ProcessMessage() == -1 ){mode=1;return ;}
			////////////////////////////////////////////////////////////
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawFormatString(100,200,CRWHITE,"年寄株%sは元%sが襲名しました",
			tosiyoridata[tosiyoriID].namestring,
			tosiyoridata[tosiyoriID].sikona);
			DrawFormatString(100,230,CRWHITE,"%s一門%s部屋付になりました(手抜き処理m(__)m)",
			itimondata[tosiyoridata[tosiyoriID].shozokuitimonid].namestring,
			heyastring[tosiyoridata[tosiyoriID].shozokuheyaid]);
			DrawString( 250 , 272 , "Hit any key" , CRWHITE);
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			//////////////////////////////////////////////////////////////

			return;
		}


		if (get_mouseclick(3,56,62,78)==1 && retire_sentaku_category!=0){
			retire_sentaku_category=0;
			pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
		}
		if (get_mouseclick(63,56,126,78)==1 && retire_sentaku_category!=1){
			retire_sentaku_category=1;
			pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
		}
		if (get_mouseclick(127,56,183,78)==1 && retire_sentaku_category!=2){
			retire_sentaku_category=2;
			pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
		}
		if (get_mouseclick_buttonkensakuLEFT() == 1){//左リスト検索ボタンをクリック
			ichijouhou=kensaku_retirerikisi(ichijouhou);
			if (ichijouhou==-1){
				return;
			}
			retire_sentaku_category=0;
			pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
		}

		if (retire_sentaku_category==0){
			if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
				if (ichijouhou>=temp_size){
					ichijouhou-=temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
				}
			}
			if( CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
				if (ichijouhou<(retiresuu_total-1)*temp_size){
					ichijouhou+=temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
				}
			}
			for (i=0;i<20;i++){
				if (i+all_retiresentaku_page*20<retiresuu_total){
					if (get_mouseclick_list(i*2) || get_mouseclick_list(i*2+1)){
						ichijouhou=(all_retiresentaku_page*20+i)*temp_size;
						pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
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
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
				goto loop;
				}
			}
			if (all_retiresentaku_page>0){
				if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
					all_retiresentaku_page--;
					ichijouhou=20*all_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
				}
			}
			if (all_retiresentaku_page<(int)((retiresuu_total-1)/20)){
				if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
					all_retiresentaku_page++;
					ichijouhou=20*all_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
				}
			}
		}

		if (retire_sentaku_category==1){
			if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
				if (ichijouhou_jiheya>=temp_size){
					ichijouhou_jiheya-=temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
				}
			}
			if( CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
				if (ichijouhou_jiheya<(retiresuu_jiheya-1)*temp_size){
					ichijouhou_jiheya+=temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
				}
			}
			for (i=0;i<20;i++){
				if (i+jiheya_retiresentaku_page*20<retiresuu_jiheya){
					if (get_mouseclick_list(i*2) || get_mouseclick_list(i*2+1)){
						ichijouhou_jiheya=(jiheya_retiresentaku_page*20+i)*temp_size;
						pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
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
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
				goto loop;

				}
			}
			if (jiheya_retiresentaku_page>0){
				if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
					jiheya_retiresentaku_page--;
					ichijouhou_jiheya=20*jiheya_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
				}
			}
			if (jiheya_retiresentaku_page<(int)((retiresuu_jiheya-1)/20)){
				if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
					jiheya_retiresentaku_page++;
					ichijouhou_jiheya=20*jiheya_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
				}
			}
		}

		if (retire_sentaku_category==2){
			if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
				if (ichijouhou_saikoui>=temp_size){
					ichijouhou_saikoui-=temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
				}
			}
			if( CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
				if (ichijouhou_saikoui<(retiresuu_saikoui-1)*temp_size){
					ichijouhou_saikoui+=temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
				}
			}
			for (i=0;i<20;i++){
				//if( ProcessMessage() == -1 ){mode=1;return ;}
				if (i+saikoui_retiresentaku_page*20<retiresuu_saikoui){
					if (get_mouseclick_list(i*2) || get_mouseclick_list(i*2+1)){
						ichijouhou_saikoui=(saikoui_retiresentaku_page*20+i)*temp_size;
						pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
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
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
				goto loop;

				}
			}
			if (saikoui_retiresentaku_page>0){
				if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
					saikoui_retiresentaku_page--;
					ichijouhou_saikoui=20*saikoui_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
				}
			}
			if (saikoui_retiresentaku_page<(int)((retiresuu_saikoui-1)/20)){
				if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
					saikoui_retiresentaku_page++;
					ichijouhou_saikoui=20*saikoui_retiresentaku_page*temp_size;
					pagenomihenkouflag_r_mainsibetu=0;
				WaitTimer(200);
				goto loop;
				}
			}
		}

		// メッセージ処理
		if( ProcessMessage() == -1 ){mode=1;return ;}
		Sleep(1);
	}


	return;
}

void itimonisekidokuritugouryuu(int heyaid)
{
	int i;

loop:
	tosiyorisuukakunin();

	itimondatahyoji(1,itimonsentaku_id);

	DrawBox(187,369,637,478,CRBACK,TRUE);//下部リンク部分消し
	DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分消し
	DrawBox(3,24,182,54,CRBACK,TRUE);//左上部分消し

	DrawFormatStringToHandle(240,5,CRWHITE,FontHandle12,"%s部屋の移籍・合流先一門を決定する画面",heyastring[heyaid]);
	DrawString(5,30,"キャンセル",CRGREEN);
	DrawString(120,30,"決定",CRGREEN);


	ScreenFlip() ;

	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//キャンセル
		if (get_mouseclick(5,30,85,30+16)==1 ){
			break;
		}
		//決定
		if (get_mouseclick(120,30,152,30+16)==1 ){
			char shuheyaflag=0;
			int itimonid=0;
			//if( ProcessMessage() == -1 ){mode=1;return ;}
			//一門主の部屋かどうかを確認
			for (i=0;i<ITIMONSUU;i++){
				if (itimondata[i].shuheyaid==heyaid){
					shuheyaflag=1;
					break;
				}
			}
			//現在所属する一門IDを検索
			for (i=0;i<TOSIYORISUU;i++){
				if (tosiyoridata[i].shozokuheyaid==heyaid){
					itimonid=tosiyoridata[i].shozokuitimonid;
					break;
				}
			}
			//同じ一門ＮＧ
			if (itimonid==itimonsentaku_id){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(100,200,"同じ一門ですよ～",CRWHITE);
				DrawString(100,300,"HIT ANY KEY",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);
				goto loop;
			}

			//一門主の部屋なら
			if (shuheyaflag==1){
				//既存の一門への合流処理のみＯＫ→一門丸ごと合流処理になる、旧一門は消滅
				if (itimondata[itimonsentaku_id].shuheyaid>=0){
					char tempstr[12];
					for (i=0;i<12;i++){
						tempstr[i]=0;
					}

					//処理してよいかの確認
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawFormatString(100,200,CRWHITE,"%s一門が消滅し%s一門に合流します。",
					itimondata[itimonid].namestring,itimondata[itimonsentaku_id].namestring);
				//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
					DrawString(100,250,"それでもよろしいですか？",CRWHITE);
					DrawString(100,100,"キャンセル",CRGREEN);
					DrawString(400,100,"はい",CRGREEN);
					ScreenFlip() ;//裏画面を表画面にコピー
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
					}
					while(1)
					{
						//キャンセル
						if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
							return;
						}
						//決定
						if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
							break;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 ){mode=1;return ;}
						Sleep(1);
					}

					//旧一門namestring一時保存
					strcpy(tempstr,itimondata[itimonid].namestring);
					//旧一門消滅処理
					itimondata[itimonid].shuheyaid=-1;
					strcpy(itimondata[itimonid].namestring,"\0");
					//所属一門ID変更、ファイル書き込み
					for (i=0;i<TOSIYORISUU;i++){
						if (tosiyoridata[i].shozokuitimonid==itimonid){
							tosiyoridata[i].shozokuitimonid=itimonsentaku_id;
							tosiyorihyoujifilekakikomi(i);
						}
					}

					tosiyorisuukakunin();

					FILE *fp;
					//eventlog書き込み/////////////////////////////////////////
					fp = fopen("data/eventlog.txt","a");
					// オープンできなかったらここで終了
					if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
					fprintf(fp,"%s一門は%s一門に合流しました(編集)\n",
					tempstr,
					itimondata[itimonsentaku_id].namestring);
					//クローズ
					fclose(fp);
					if( ProcessMessage() == -1 ){mode=1;return ;}
					////////////////////////////////////////////////////////////
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawFormatString(100,200,CRWHITE,"%s一門は%s一門に合流しました",
					tempstr,
					itimondata[itimonsentaku_id].namestring);
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitKey();
					//////////////////////////////////////////////////////////////

					return;


				}else{
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawString(100,200,"一門主の部屋が新一門の創設をすることはできません。",CRWHITE);
					DrawString(100,300,"HIT ANY KEY",CRWHITE);
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitKey();
					WaitTimer(200);
					goto loop;
				}
			//一門主の部屋ではないなら
			}else{
				//既存の一門への合流処理
				if (itimondata[itimonsentaku_id].shuheyaid>=0){

					//処理してよいかの確認
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawFormatString(100,200,CRWHITE,"%s一門%s部屋が%s一門に移籍します。",
					itimondata[itimonid].namestring,
					heyastring[heyaid],
					itimondata[itimonsentaku_id].namestring);
				//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
					DrawString(100,250,"それでもよろしいですか？",CRWHITE);
					DrawString(100,100,"キャンセル",CRGREEN);
					DrawString(400,100,"はい",CRGREEN);
					ScreenFlip() ;//裏画面を表画面にコピー
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
					}
					while(1)
					{
						//キャンセル
						if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
							return;
						}
						//決定
						if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
							break;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 ){mode=1;return ;}
						Sleep(1);
					}

					//所属一門ID変更、ファイル書き込み
					for (i=0;i<TOSIYORISUU;i++){
						if (tosiyoridata[i].shozokuheyaid==heyaid){
							tosiyoridata[i].shozokuitimonid=itimonsentaku_id;
							tosiyorihyoujifilekakikomi(i);
						}
					}

					tosiyorisuukakunin();

					FILE *fp;
					//eventlog書き込み/////////////////////////////////////////
					fp = fopen("data/eventlog.txt","a");
					// オープンできなかったらここで終了
					if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
					fprintf(fp,"%s一門%s部屋が%s一門に移籍しました(編集)\n",
					itimondata[itimonid].namestring,
					heyastring[heyaid],
					itimondata[itimonsentaku_id].namestring);
					//クローズ
					fclose(fp);
					if( ProcessMessage() == -1 ){mode=1;return ;}
					////////////////////////////////////////////////////////////
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawFormatString(100,200,CRWHITE,"%s一門%s部屋が%s一門に移籍しました",
					itimondata[itimonid].namestring,
					heyastring[heyaid],
					itimondata[itimonsentaku_id].namestring);
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitKey();
					//////////////////////////////////////////////////////////////

					return;

				//新一門の創設処理
				}else{

					//処理してよいかの確認
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawFormatString(100,200,CRWHITE,"%s一門%s部屋が離脱し、%s一門を新設します。",
					itimondata[itimonid].namestring,
					heyastring[heyaid],
					itimondata[itimonsentaku_id].namestring);
				//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
					DrawString(100,250,"それでもよろしいですか？",CRWHITE);
					DrawString(100,100,"キャンセル",CRGREEN);
					DrawString(400,100,"はい",CRGREEN);
					ScreenFlip() ;//裏画面を表画面にコピー
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
					}
					while(1)
					{
						//キャンセル
						if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
							return;
						}
						//決定
						if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
							break;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 ){mode=1;return ;}
						Sleep(1);
					}

					itimondata[itimonsentaku_id].shuheyaid=heyaid;
					strcpy(itimondata[itimonsentaku_id].namestring,heyastring[heyaid]);
					itimondata[itimonsentaku_id].itimonid_tuusan=itimonid_used;
					itimonid_used++;
					itimondata[itimonsentaku_id].startyear=year;
					itimondata[itimonsentaku_id].startmonth=month;

					//所属一門ID変更、ファイル書き込み
					for (i=0;i<TOSIYORISUU;i++){
						if (tosiyoridata[i].shozokuheyaid==heyaid){
							tosiyoridata[i].shozokuitimonid=itimonsentaku_id;
							tosiyorihyoujifilekakikomi(i);
						}
					}

					tosiyorisuukakunin();

					FILE *fp;
					//eventlog書き込み/////////////////////////////////////////
					fp = fopen("data/eventlog.txt","a");
					// オープンできなかったらここで終了
					if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
					fprintf(fp,"%s一門%s部屋が離脱し、%s一門を新設しました(編集)\n",
					itimondata[itimonid].namestring,
					heyastring[heyaid],
					itimondata[itimonsentaku_id].namestring);
					//クローズ
					fclose(fp);
					if( ProcessMessage() == -1 ){mode=1;return ;}
					////////////////////////////////////////////////////////////
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawFormatString(100,200,CRWHITE,"%s一門%s部屋が離脱し、%s一門を新設しました",
					itimondata[itimonid].namestring,
					heyastring[heyaid],
					itimondata[itimonsentaku_id].namestring);
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitKey();
					//////////////////////////////////////////////////////////////

					return;
				}
			}
		}


		//親方表示部分の頁数減少
		if (get_mouseclick(200,170+12*15,200+24,170+12*15+12)==1 ){
			if (page_oyakata_itimon>0){
				page_oyakata_itimon--;
				WaitTimer(200);
				goto loop;
			}
			//break;
		}
		//親方表示部分の頁数増加
		if (get_mouseclick(296,170+12*15,296+24,170+12*15+12)==1 ){
			if (page_oyakata_itimon<39){
				page_oyakata_itimon++;
				WaitTimer(200);
				goto loop;
			}
			//break;
		}
		if (itimonsentaku_page==1){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				itimonsentaku_page=0;
				itimonsentaku_num=0;
				itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
				WaitTimer(200);
				goto loop;
			}
		}
		if (itimonsentaku_page==0){
			if (get_mouseclick_buttonDOWN() == 1){//左リストUPボタンをクリック
				itimonsentaku_page=1;
				itimonsentaku_num=0;
				itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
				WaitTimer(200);
				goto loop;
			}
		}
		for (i=0;i<40;i++){
			if (get_mouseclick_list(i) == 1){//リスト上の部屋名をクリックしたら
				if (i+itimonsentaku_page*40<ITIMONSUU){
					itimonsentaku_num=i;
					itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
					WaitTimer(200);
					goto loop;
				}
			}
		}

		if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
			if (itimonsentaku_page==1 && itimonsentaku_num<2){
				itimonsentaku_page=0;
				itimonsentaku_num+=38;
				itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
				WaitTimer(200);
				goto loop;
			}else if (itimonsentaku_num>1){
				itimonsentaku_num=itimonsentaku_num-2;
				itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
				WaitTimer(200);
				goto loop;
			}
		}
		if(CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
			if (itimonsentaku_page==0 && itimonsentaku_num>37){
				itimonsentaku_page=1;
				itimonsentaku_num-=38;
				itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
				WaitTimer(200);
				goto loop;
			}else if (itimonsentaku_num<38){
				if (!(itimonsentaku_page==1 && itimonsentaku_num>11)){
					itimonsentaku_num=itimonsentaku_num+2;
					itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
					WaitTimer(200);
					goto loop;
				}
			}
		}
		if( CheckHitKey_test(KEY_INPUT_RIGHT)){//→キー
			if ((itimonsentaku_num+2)%2==0 ){
					itimonsentaku_num=itimonsentaku_num+1;
					itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
					WaitTimer(200);
					goto loop;
			}
		}
		if( CheckHitKey_test(KEY_INPUT_LEFT)){//←キー
			if ((itimonsentaku_num+2)%2==1 ){
				itimonsentaku_num=itimonsentaku_num-1;
				itimonsentaku_id=itimonsentaku_num+itimonsentaku_page*40;
				WaitTimer(200);
				goto loop;
			}
		}

		// メッセージ処理
		if( ProcessMessage() == -1 ){mode=1;return ;}
		Sleep(1);
	}

	return;
}


void itimonnusininaru(int heyaid)
{
	int i;
	int itimonid=0;
	char tempstr[12];
	for (i=0;i<12;i++){
		tempstr[i]=0;
	}

	tosiyorisuukakunin();

	//現在所属する一門IDを検索
	for (i=0;i<TOSIYORISUU;i++){
		if (tosiyoridata[i].shozokuheyaid==heyaid){
			itimonid=tosiyoridata[i].shozokuitimonid;
			break;
		}
	}

	//自部屋ＮＧ
/*
	if (itimondata[itimonid].shuheyaid==myheyaid){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString(100,200,"あなたの一門はこの処理はできません",CRWHITE);
		DrawString(100,300,"HIT ANY KEY",CRWHITE);
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		WaitTimer(200);
		return;
	}
*/

	//処理してよいかの確認
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(100,200,CRWHITE,"%s部屋が%s部屋に替わって一門の主部屋になります。",heyastring[heyaid],itimondata[itimonid].namestring);
//	DrawString(100,225,"を想定して作られたゲームではありません。",CRWHITE);
	DrawString(100,250,"それでもよろしいですか？",CRWHITE);
	DrawString(100,100,"キャンセル",CRGREEN);
	DrawString(400,100,"はい",CRGREEN);
	ScreenFlip() ;//裏画面を表画面にコピー
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//キャンセル
		if (get_mouseclick(100,100,100+16*5,100+16)==1 ){
			return;
		}
		//決定
		if (get_mouseclick(400,100,400+16*3,100+16)==1 ){
			break;
		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){mode=1;return ;}
		Sleep(1);
	}


	//旧一門namestring一時保存
	strcpy(tempstr,itimondata[itimonid].namestring);

	//一門主更新
	itimondata[itimonid].shuheyaid=heyaid;
	strcpy(itimondata[itimonid].namestring,heyastring[heyaid]);

	//ファイル書き込み
	for (i=0;i<TOSIYORISUU;i++){
		if (tosiyoridata[i].shozokuitimonid==itimonid
		&& tosiyoridata[i].shozokuheyaid>=0){
			tosiyorihyoujifilekakikomi(i);
		}
	}

	tosiyorisuukakunin();

	FILE *fp;
	//eventlog書き込み/////////////////////////////////////////
	fp = fopen("data/eventlog.txt","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
	fprintf(fp,"%s一門は一門主の変更で%s一門に改称しました(編集)\n",
	tempstr,
	itimondata[itimonid].namestring);
	//クローズ
	fclose(fp);
	if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////////////////////////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(100,200,CRWHITE,"%s一門は一門主の変更で%s一門に改称しました",
	tempstr,
	itimondata[itimonid].namestring);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	//////////////////////////////////////////////////////////////


	return;
}


int genekirikisisentaku_keiko(int x,char flag)//選択した力士の画像IDが返される
											//flag0→稽古相手選択、1→技分析相手選択
{
	int i;
	int last_rikisisentaku_id=0;

loop:
	//現役力士データ表示
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	game_main_backscreen();//基本画面表示
	rikisidatahyoji(rikisisentaku_id);

	DrawBox(187,369,637,477,CRBACK,TRUE);//下部リンク部分消し
	DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分消し
	DrawBox(3,24,182,54,CRBACK,TRUE);//左上部分消し
	DrawBox(187,25+64,187+32,25+64+15,CRBACK,TRUE);//作戦ボタン部分消し
	DrawBox(505-40-40,25+64,505-40-40+32,25+64+15,CRBACK,TRUE);//作戦ボタン部分消し
	DrawBox(505-40,24,637,24+16,CRBACK,TRUE);//編集ボタン～取組見る見ない選択部分消し
	//DrawBox(rx1[0]-11,ry1[0]+3-3,637,ry1[0]+3+14,CRBACK,TRUE);//右タブ選択部分消し
	DrawBox(187,72,187+16*7,72+15,CRBACK,TRUE);//部屋名緑色消し
	DrawBox(260,350,260+50,350+16,CRBACK,TRUE);//技分析文字部分消し

	DrawFormatString(187,72,CRWHITE,"%s部屋",
	heyastring[rikisidata[rikisisentaku_id].heyaid]
	);
	
	if (flag==0){
		DrawFormatStringToHandle(150,5,CRWHITE,FontHandle12,"%sの稽古相手を決定する画面",namestring[x]);
		DrawString(187,369,"稽古相手を選択してください",CRWHITE);
	}
	if (flag==1){
		DrawFormatStringToHandle(150,5,CRWHITE,FontHandle12,"%sの分析相手を決定する画面",namestring[x]);
		DrawString(187,369,"分析相手を選択してください",CRWHITE);
	}
	DrawString(5,30,"キャンセル",CRGREEN);
	DrawString(120,30,"決定",CRGREEN);




	ScreenFlip() ;//裏画面を表画面にコピー

	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//キャンセル
		if (get_mouseclick(5,30,85,30+16)==1 ){
			WaitTimer(200);
			return -1;
		}
		//決定
		if (get_mouseclick(120,30,152,30+16)==1 ){
			if (x==rikisisentaku_id){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(100,369,"自分同士ですよ～",CRWHITE);
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);
				goto loop;
			}else{
				WaitTimer(200);
				return rikisisentaku_id;
			}
		}


		if (keikosetteiflag!=1 || rikisidata[rikisisentaku_id].heyaid!=myheyaid){
			if (get_mouseclick(rx1[0]-10,ry1[0],rx1[0]-10+34*1-1,ry1[0]+16)==1 && torikumi_or_seisekiflag!=0){
				torikumi_or_seisekiflag=0;
				WaitTimer(200);
				goto loop;
			}
			if (get_mouseclick(rx1[0]-10+34*1,ry1[0],rx1[0]-10+34*2-1,ry1[0]+16)==1 && torikumi_or_seisekiflag!=1){
				torikumi_or_seisekiflag=1;
				WaitTimer(200);
				goto loop;
			}
			if (get_mouseclick(rx1[0]-10+34*2,ry1[0],rx1[0]-10+34*3-1,ry1[0]+16)==1 && torikumi_or_seisekiflag!=2){
				torikumi_or_seisekiflag=2;
				WaitTimer(200);
				goto loop;
			}
			if (get_mouseclick(rx1[0]-10+34*3,ry1[0],rx1[0]-10+34*4-1,ry1[0]+16)==1 && torikumi_or_seisekiflag!=3){
				torikumi_or_seisekiflag=3;
				WaitTimer(200);
				goto loop;
			}
			if (get_mouseclick(rx1[0]-10+34*4,ry1[0],rx1[0]-10+34*5-1,ry1[0]+16)==1 && torikumi_or_seisekiflag!=4){
				torikumi_or_seisekiflag=4;
				WaitTimer(200);
				goto loop;
			}
			for (i=0;i<18;i++){//右リスト成績のときの右リストクリック処理
				//if( ProcessMessage() == -1 ){mode=1;return -1;}
				if (torikumi_or_seisekiflag==1 && (get_mouseclick_rlist(i*2+4) == 1 || get_mouseclick_rlist(i*2+5)==1) ){//リスト上の過去の成績をクリックしたら
					if (rikisidata[rikisisentaku_id].kako_bandukehigasiornisi[i+seiseki_sentaku_page[rikisisentaku_id]*18]!=-1){
						torikumi_sentaku_page=i+seiseki_sentaku_page[rikisisentaku_id]*18+1;
						torikumi_or_seisekiflag=0;
						WaitTimer(200);
						goto loop;
					}
				}
			}
			if (mode!=25 && torikumi_or_seisekiflag==2){//右リストタブ士別のときの過去六場所成績欄の力士名クリック処理
				for (i=0;i<15;i++){
					//if( ProcessMessage() == -1 ){mode=1;return -1;}
					if(get_mouseclick_rlist(i*2+11) == 2){//右リスト上の決まり手を右クリック
						if (((int)(month/2)-((i+1)%6)) >= 0){
							if (year-(int)((i+1)/6)>0){
								video(rikisidata[rikisibetu_sentaku_id[rikisisentaku_id]].rikisiid,rikisidata[rikisisentaku_id].rikisiid,year-(int)((i+1)/6),(((int)(month/2))-((i+1)%6))*2+1,namestring[rikisibetu_sentaku_id[rikisisentaku_id]],namestring[rikisisentaku_id]);
							}
						}else{
							if (year-(int)((i+1)/6)-1>0){
								video(rikisidata[rikisibetu_sentaku_id[rikisisentaku_id]].rikisiid,rikisidata[rikisisentaku_id].rikisiid,year-(int)((i+1)/6)-1,(((int)(month/2))-((i+1)%6)+6)*2+1,namestring[rikisibetu_sentaku_id[rikisisentaku_id]],namestring[rikisisentaku_id]);
							}
						}
						WaitTimer(200);
						goto loop;
					}
				}
				if (get_mouseclick_rlist(2) == 1 ){//リスト上の力士名をクリックしたら
					bandukejun_or_jiheyaflag=0;
					last_rikisisentaku_id=rikisisentaku_id;
					rikisisentaku_id=rikisibetu_sentaku_id[last_rikisisentaku_id];
					rikisisentaku_num=((rikisidata[rikisisentaku_id].bandukejun+20)%20)*2;
					rikisisentaku_page=(int)((rikisidata[rikisisentaku_id].bandukejun+20)/20)-1;
					rikisibetu_sentaku_id[rikisisentaku_id]=last_rikisisentaku_id;
					WaitTimer(200);
					goto loop;
				}else if (get_mouseclick_buttonkensakuRIGHT()== 1){//「検索」をクリックしたら
					rikisibetu_sentaku_id[rikisisentaku_id]=kensaku_rikisibetu();
					WaitTimer(200);
					goto loop;
				}
			}
			if (torikumi_or_seisekiflag==0 && torikumi_sentaku_page>0){
				if (get_mouseclick_buttonUPFAST() == 1){//右リストUPボタンをクリック
					torikumi_sentaku_page--;
					WaitTimer(200);
					goto loop;
				}
			}
			if (torikumi_or_seisekiflag==0 && torikumi_sentaku_page<bashocount){
				if (get_mouseclick_buttonDOWNFAST() == 1){//右リストDOWNボタンをクリック
					torikumi_sentaku_page++;
					WaitTimer(200);
					goto loop;
				}
			}
			if (torikumi_or_seisekiflag==1 && seiseki_sentaku_page[rikisisentaku_id]>0){
				if (get_mouseclick_buttonUPFAST() == 1){//右リストUPボタンをクリック
					seiseki_sentaku_page[rikisisentaku_id]--;
					WaitTimer(200);
					goto loop;
				}
			}
			if (torikumi_or_seisekiflag==1 && seiseki_sentaku_page[rikisisentaku_id]<seiseki_max_page[rikisisentaku_id]){
				if (get_mouseclick_buttonDOWNFAST() == 1){//右リストDOWNボタンをクリック
					seiseki_sentaku_page[rikisisentaku_id]++;
					WaitTimer(200);
					goto loop;
				}
			}
			if (torikumi_or_seisekiflag==0){
				if (torikumi_sentaku_page==0){//今場所の場合
					if (mode!=25){
						for (i=0;i<=day-11;i++){//取組予定のリスト上の力士名クリック処理
							//if( ProcessMessage() == -1 ){mode=1;return -1;}
							if (rikisidata[rikisisentaku_id].aitekonbasho[i]!=-1
							 && rikisidata[rikisisentaku_id].aitekonbasho[i]!=999){
								if (get_mouseclick_rlist(i*2+4) == 1){//右リスト上の力士名をクリックしたら
									rikisisentaku_id=rikisidata[rikisisentaku_id].aitekonbasho[i];
									rikisisentaku_num=((rikisidata[rikisisentaku_id].bandukejun+20)%20)*2;
									rikisisentaku_page=(int)((rikisidata[rikisisentaku_id].bandukejun+20)/20)-1;
									if (rikisidata[rikisisentaku_id].heyaid!=myheyaid){
										bandukejun_or_jiheyaflag=0;
									}
									WaitTimer(200);
									goto loop;
//変更必要
								}else if (get_mouseclick_rlist(i*2+5) == 1){//右リスト上の決まり手左クリック
									torikumi_or_seisekiflag=2;
									rikisibetu_sentaku_id[rikisisentaku_id]=rikisidata[rikisisentaku_id].aitekonbasho[i];
									if (rikisidata[rikisisentaku_id].heyaid!=myheyaid){
										bandukejun_or_jiheyaflag=0;
									}
									WaitTimer(200);
									goto loop;
								}else if (get_mouseclick_rlist(i*2+5) == 2){//右リスト上の決まり手右クリック
									if (rikisidata[rikisisentaku_id].aitekonbasho[i]!=-1
									 && rikisidata[rikisisentaku_id].aitekonbasho[i]!=999){
										video(rikisidata[rikisisentaku_id].rikisiid,rikisidata[rikisidata[rikisisentaku_id].aitekonbasho[i]].rikisiid,year,month,namestring[rikisisentaku_id],namestring[rikisidata[rikisisentaku_id].aitekonbasho[i]]);
									}
									WaitTimer(200);
									goto loop;
								}
							}
						}
					}
				}else{//過去の場所の場合
					for (i=0;i<15;i++){//取組予定のリスト上の力士名クリック処理
						//if( ProcessMessage() == -1 ){mode=1;return -1;}
						if (rikisidata[rikisisentaku_id].kako_aitekonbasho[torikumi_sentaku_page-1][i]!=999){
							if(get_mouseclick_rlist(i*2+5) == 2){//右リスト上の決まり手を右クリック
								video(nowhyoji_torikumitab_ID,nowhyoji_torikumitab_ID2[i],nowhyoji_torikumitab_year,nowhyoji_torikumitab_month,nowhyoji_torikumitab_namestring,nowhyoji_torikumitab_namestring2[i]);
								WaitTimer(200);
								goto loop;
							}
						}
						if (rikisidata[rikisisentaku_id].kako_aitekonbasho[torikumi_sentaku_page-1][i]!=-1
						 && rikisidata[rikisisentaku_id].kako_aitekonbasho[torikumi_sentaku_page-1][i]!=999
						&& nowhyoji_torikumitab_ID2[i]==rikisidata[rikisidata[rikisisentaku_id].kako_aitekonbasho[torikumi_sentaku_page-1][i]].rikisiid){
							if (get_mouseclick_rlist(i*2+4) == 1){//右リスト上の力士名をクリックしたら
								rikisisentaku_id=rikisidata[rikisisentaku_id].kako_aitekonbasho[torikumi_sentaku_page-1][i];
								rikisisentaku_num=((rikisidata[rikisisentaku_id].bandukejun+20)%20)*2;
								rikisisentaku_page=(int)((rikisidata[rikisisentaku_id].bandukejun+20)/20)-1;
								if (rikisidata[rikisisentaku_id].heyaid!=myheyaid){
									bandukejun_or_jiheyaflag=0;
								}
								WaitTimer(200);
								goto loop;
//変更必要
							}else if(get_mouseclick_rlist(i*2+5) == 1){//右リスト上の決まり手を左クリック
								torikumi_or_seisekiflag=2;
								rikisibetu_sentaku_id[rikisisentaku_id]=rikisidata[rikisisentaku_id].kako_aitekonbasho[torikumi_sentaku_page-1][i];
								if (rikisidata[rikisisentaku_id].heyaid!=myheyaid){
									bandukejun_or_jiheyaflag=0;
								}
								WaitTimer(200);
								goto loop;
							}
						}
					}
				}
			}
		}else{

		}
		if (get_mouseclick(3,56,41,78)==1 && bandukejun_or_jiheyaflag!=0){
			bandukejun_or_jiheyaflag=0;
//			rikisisentaku_page=(int)((rikisidata[rikisisentaku_id].bandukejun+20)/20)-1;
//			rikisisentaku_num=((rikisidata[rikisisentaku_id].bandukejun+20)%20)*2;
			rikisisentaku_id=bandukejunid[(rikisisentaku_num+2)/2-1+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
		}
		if (get_mouseclick(42,56,79,78)==1 && bandukejun_or_jiheyaflag!=1){
			bandukejun_or_jiheyaflag=1;
			if ((rikisisentaku_num_jiheya+2)/2>shozokurikisisuu[myheyaid]){
				rikisisentaku_num_jiheya=0;
			}
			rikisisentaku_id=heyabandukejunid[myheyaid][(rikisisentaku_num_jiheya+2)/2-1];
				WaitTimer(200);
				goto loop;
		}
		if (get_mouseclick(80,56,116,78)==1 && bandukejun_or_jiheyaflag!=2){
			int count=0;
			bandukejun_or_jiheyaflag=2;
			//「ver2.44」で追加
			for (i=0;i<RIKISISUU;i++){
				if (rikisidata[i].realmodeflag==1){
					rikisidata[i].torikumimiruflag=1;
				}
				//if( ProcessMessage() == -1 ){mode=1;return -1 ;}// エラーが起きたらループから抜ける
			}
			count=0;//取組見る力士たちの番付順力士IDを検索
			for (i=0;i<RIKISISUU;i++){//
				//if( ProcessMessage() == -1 ){mode=1;return -1 ;}
				if (rikisidata[bandukejunid[i]].torikumimiruflag==1){
					torimi_bandukejunid[count]=bandukejunid[i];
					count++;
				}
			}
			torimisuu=count;
			//「ver2.44」で追加ここまで
			if (torimisuu!=0){
				rikisisentaku_id=torimi_bandukejunid[(torimi_rikisisentaku_num+2)/2-1+torimi_rikisisentaku_page*20];
			}
				WaitTimer(200);
				goto loop;
		}
		if (get_mouseclick(117,56,151,78)==1 && bandukejun_or_jiheyaflag!=3){
			if (superrikisisuu[2]==0){
			bandukejun_or_jiheyaflag=3;
			if (rinnesuu!=0){
				rikisisentaku_id=rinne_bandukejunid[(rinne_rikisisentaku_num+2)/2-1+rinne_rikisisentaku_page*20];
			}
				WaitTimer(200);
				goto loop;
			}
		}
		if (get_mouseclick(152,56,184,78)==1 && bandukejun_or_jiheyaflag!=4){
			bandukejun_or_jiheyaflag=4;
			if (kyuujousuu!=0){
				rikisisentaku_id=kyuujou_bandukejunid[(kyuujou_rikisisentaku_num+2)/2-1+kyuujou_rikisisentaku_page*20];
			}
				WaitTimer(200);
				goto loop;
		}

		for (i=0;i<20;i++){//左リストタブ番付順のときの左リストクリック処理
			//if( ProcessMessage() == -1 ){mode=1;return -1 ;}
			if (bandukejun_or_jiheyaflag==0 && (get_mouseclick_list(i*2) == 1 || get_mouseclick_list(i*2+1)==1) ){//リスト上の力士名をクリックしたら
				if (i+rikisisentaku_page*20<RIKISISUU){
					rikisisentaku_num=i*2;
					rikisisentaku_id=bandukejunid[i+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}
		}
		for (i=0;i<shozokurikisisuu[myheyaid];i++){//左リストタブ自部屋のときの左リストクリック処理
			//if( ProcessMessage() == -1 ){mode=1;return -1 ;}
			if (bandukejun_or_jiheyaflag==1 && (get_mouseclick_list(i*2+1) == 1 || get_mouseclick_list(i*2)==1) ){//自部屋表示の左リスト上の力士名をクリックしたら
				rikisisentaku_num_jiheya=i*2;
				rikisisentaku_id=heyabandukejunid[myheyaid][i];
				WaitTimer(200);
				goto loop;
			}
		}
	if( ProcessMessage() == -1 ){mode=1;return -1 ;}// エラーが起きたらループから抜ける
		for (i=0;i<20;i++){//左リストタブ取見のときの左リストクリック処理
			//if( ProcessMessage() == -1 ){mode=1;return -1 ;}
			if (bandukejun_or_jiheyaflag==2 && (get_mouseclick_list(i*2) == 1 || get_mouseclick_list(i*2+1)==1) ){//リスト上の力士名をクリックしたら
				if (i+torimi_rikisisentaku_page*20<torimisuu){
					torimi_rikisisentaku_num=i*2;
					rikisisentaku_id=torimi_bandukejunid[i+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}
		}
	if( ProcessMessage() == -1 ){mode=1;return -1 ;}// エラーが起きたらループから抜ける
		if (superrikisisuu[2]==0){
		for (i=0;i<20;i++){//左リストタブ輪廻のときの左リストクリック処理
			//if( ProcessMessage() == -1 ){mode=1;return -1 ;}
			if (bandukejun_or_jiheyaflag==3 && (get_mouseclick_list(i*2) == 1 || get_mouseclick_list(i*2+1)==1) ){//リスト上の力士名をクリックしたら
				if (i+rinne_rikisisentaku_page*20<rinnesuu){
					rinne_rikisisentaku_num=i*2;
					rikisisentaku_id=rinne_bandukejunid[i+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}
		}
		}
	if( ProcessMessage() == -1 ){mode=1;return -1 ;}// エラーが起きたらループから抜ける
		for (i=0;i<20;i++){//左リストタブ休場のときの左リストクリック処理
			//if( ProcessMessage() == -1 ){mode=1;return -1 ;}
			if (bandukejun_or_jiheyaflag==4 && (get_mouseclick_list(i*2) == 1 || get_mouseclick_list(i*2+1)==1) ){//リスト上の力士名をクリックしたら
				if (i+kyuujou_rikisisentaku_page*20<kyuujousuu){
					kyuujou_rikisisentaku_num=i*2;
					rikisisentaku_id=kyuujou_bandukejunid[i+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}
		}
	if( ProcessMessage() == -1 ){mode=1;return -1 ;}// エラーが起きたらループから抜ける
		if (bandukejun_or_jiheyaflag==0){
			if (get_mouseclick_buttonkensakuLEFT() == 1){//左リスト検索ボタンをクリック
				rikisisentaku_id=kensaku_allrikisi();
				rikisisentaku_page=(int)((rikisidata[rikisisentaku_id].bandukejun+20)/20)-1;
				rikisisentaku_num=((rikisidata[rikisisentaku_id].bandukejun+20)%20)*2;
				WaitTimer(200);
				goto loop;
			}
		}
		if (bandukejun_or_jiheyaflag==0 && rikisisentaku_page>0){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				rikisisentaku_page--;
				rikisisentaku_num=0;
				rikisisentaku_id=bandukejunid[rikisisentaku_num+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}
		if (bandukejun_or_jiheyaflag==0 && rikisisentaku_page<(int)((RIKISISUU+19)/20)-1){
			if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
				rikisisentaku_page++;
				rikisisentaku_num=0;
				rikisisentaku_id=bandukejunid[rikisisentaku_num+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}
		if (bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_page>0){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				torimi_rikisisentaku_page--;
				torimi_rikisisentaku_num=0;
				rikisisentaku_id=torimi_bandukejunid[torimi_rikisisentaku_num+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}
		if (bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_page<(int)((torimisuu+19)/20)-1){
			if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
				torimi_rikisisentaku_page++;
				torimi_rikisisentaku_num=0;
				rikisisentaku_id=torimi_bandukejunid[torimi_rikisisentaku_num+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}

		if (bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_page>0){
			if (superrikisisuu[2]==0){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				rinne_rikisisentaku_page--;
				rinne_rikisisentaku_num=0;
				rikisisentaku_id=rinne_bandukejunid[rinne_rikisisentaku_num+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
			}
		}
		if (bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_page<(int)((rinnesuu+19)/20)-1){
			if (superrikisisuu[2]==0){
			if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
				rinne_rikisisentaku_page++;
				rinne_rikisisentaku_num=0;
				rikisisentaku_id=rinne_bandukejunid[rinne_rikisisentaku_num+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
			}
		}
	if( ProcessMessage() == -1 ){mode=1;return -1 ;}// エラーが起きたらループから抜ける

		if (bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_page>0){
			if (get_mouseclick_buttonUP() == 1){//左リストUPボタンをクリック
				kyuujou_rikisisentaku_page--;
				kyuujou_rikisisentaku_num=0;
				rikisisentaku_id=kyuujou_bandukejunid[kyuujou_rikisisentaku_num+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}
		if (bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_page<(int)((kyuujousuu+19)/20)-1){
			if (get_mouseclick_buttonDOWN() == 1){//左リストDOWNボタンをクリック
				kyuujou_rikisisentaku_page++;
				kyuujou_rikisisentaku_num=0;
				rikisisentaku_id=kyuujou_bandukejunid[kyuujou_rikisisentaku_num+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}

	if( ProcessMessage() == -1 ){mode=1;return -1 ;}// エラーが起きたらループから抜ける
		if( CheckHitKey_test(KEY_INPUT_UP)){//↑キー
			if (bandukejun_or_jiheyaflag==0 && rikisisentaku_num==0 && rikisisentaku_page>0){
				rikisisentaku_page--;
				rikisisentaku_num=38;
				rikisisentaku_id=bandukejunid[(rikisisentaku_num+2)/2-1+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if (bandukejun_or_jiheyaflag==0 && rikisisentaku_num>1){
				rikisisentaku_num=rikisisentaku_num-2;
				rikisisentaku_id=bandukejunid[(rikisisentaku_num+2)/2-1+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if(bandukejun_or_jiheyaflag==1 && rikisisentaku_num_jiheya>1){
				rikisisentaku_num_jiheya-=2;
				rikisisentaku_id=heyabandukejunid[myheyaid][(rikisisentaku_num_jiheya+2)/2-1];
				WaitTimer(200);
				goto loop;
			}else if(bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_num==0 && torimi_rikisisentaku_page>0){
				torimi_rikisisentaku_page--;
				torimi_rikisisentaku_num=38;
				rikisisentaku_id=torimi_bandukejunid[(torimi_rikisisentaku_num+2)/2-1+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if (bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_num>1){
				torimi_rikisisentaku_num-=2;
				rikisisentaku_id=torimi_bandukejunid[(torimi_rikisisentaku_num+2)/2-1+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if(bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_num==0 && rinne_rikisisentaku_page>0){
				if (superrikisisuu[2]==0){
				rinne_rikisisentaku_page--;
				rinne_rikisisentaku_num=38;
				rikisisentaku_id=rinne_bandukejunid[(rinne_rikisisentaku_num+2)/2-1+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}else if (bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_num>1){
				if (superrikisisuu[2]==0){
				rinne_rikisisentaku_num-=2;
				rikisisentaku_id=rinne_bandukejunid[(rinne_rikisisentaku_num+2)/2-1+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}else if(bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_num==0 && kyuujou_rikisisentaku_page>0){
				kyuujou_rikisisentaku_page--;
				kyuujou_rikisisentaku_num=38;
				rikisisentaku_id=kyuujou_bandukejunid[(kyuujou_rikisisentaku_num+2)/2-1+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if (bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_num>1){
				kyuujou_rikisisentaku_num-=2;
				rikisisentaku_id=kyuujou_bandukejunid[(kyuujou_rikisisentaku_num+2)/2-1+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}
	if( ProcessMessage() == -1 ){mode=1;return -1 ;}// エラーが起きたらループから抜ける
		if( CheckHitKey_test(KEY_INPUT_DOWN)){//↓キー
			if (bandukejun_or_jiheyaflag==0 && rikisisentaku_num==38 && rikisisentaku_page<(int)((RIKISISUU+19)/20)-1){
				rikisisentaku_page++;
				rikisisentaku_num=0;
				rikisisentaku_id=bandukejunid[(rikisisentaku_num+2)/2-1+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if ((bandukejun_or_jiheyaflag==0 && rikisisentaku_num<38 && rikisisentaku_page<(int)((RIKISISUU+19)/20)-1)
						|| (bandukejun_or_jiheyaflag==0 && rikisisentaku_num<(RIKISISUU%20)*2-2 && rikisisentaku_page==(int)((RIKISISUU+19)/20)-1)){
				rikisisentaku_num=rikisisentaku_num+2;
				rikisisentaku_id=bandukejunid[(rikisisentaku_num+2)/2-1+rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if(bandukejun_or_jiheyaflag==1 && rikisisentaku_num_jiheya<shozokurikisisuu[myheyaid]*2-2){
				rikisisentaku_num_jiheya+=2;
				rikisisentaku_id=heyabandukejunid[myheyaid][(rikisisentaku_num_jiheya+2)/2-1];
				WaitTimer(200);
				goto loop;
			}else if(bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_num==38 && torimi_rikisisentaku_page<(int)((torimisuu+19)/20)-1){
				torimi_rikisisentaku_page++;
				torimi_rikisisentaku_num=0;
				rikisisentaku_id=torimi_bandukejunid[(torimi_rikisisentaku_num+2)/2-1+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if ((bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_num<38 && torimi_rikisisentaku_page<(int)((torimisuu+19)/20)-1)
						|| (bandukejun_or_jiheyaflag==2 && torimi_rikisisentaku_num<(torimisuu%20)*2-2 && torimi_rikisisentaku_page==(int)((torimisuu+19)/20)-1)){
				torimi_rikisisentaku_num+=2;
				rikisisentaku_id=torimi_bandukejunid[(torimi_rikisisentaku_num+2)/2-1+torimi_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if(bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_num==38 && rinne_rikisisentaku_page<(int)((rinnesuu+19)/20)-1){
				if (superrikisisuu[2]==0){
				rinne_rikisisentaku_page++;
				rinne_rikisisentaku_num=0;
				rikisisentaku_id=rinne_bandukejunid[(rinne_rikisisentaku_num+2)/2-1+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}else if ((bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_num<38 && rinne_rikisisentaku_page<(int)((rinnesuu+19)/20)-1)
						|| (bandukejun_or_jiheyaflag==3 && rinne_rikisisentaku_num<(rinnesuu%20)*2-2 && rinne_rikisisentaku_page==(int)((rinnesuu+19)/20)-1)){
				if (superrikisisuu[2]==0){
				rinne_rikisisentaku_num+=2;
				rikisisentaku_id=rinne_bandukejunid[(rinne_rikisisentaku_num+2)/2-1+rinne_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
				}
			}else if(bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_num==38 && kyuujou_rikisisentaku_page<(int)((kyuujousuu+19)/20)-1){
				kyuujou_rikisisentaku_page++;
				kyuujou_rikisisentaku_num=0;
				rikisisentaku_id=kyuujou_bandukejunid[(kyuujou_rikisisentaku_num+2)/2-1+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}else if ((bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_num<38 && kyuujou_rikisisentaku_page<(int)((kyuujousuu+19)/20)-1)
						|| (bandukejun_or_jiheyaflag==4 && kyuujou_rikisisentaku_num<(kyuujousuu%20)*2-2 && kyuujou_rikisisentaku_page==(int)((kyuujousuu+19)/20)-1)){
				kyuujou_rikisisentaku_num+=2;
				rikisisentaku_id=kyuujou_bandukejunid[(kyuujou_rikisisentaku_num+2)/2-1+kyuujou_rikisisentaku_page*20];
				WaitTimer(200);
				goto loop;
			}
		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){mode=1;return -1;}
		Sleep(1);
	}

	return -1;
}
