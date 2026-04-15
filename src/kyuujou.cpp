#include "DxLib.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include "define.h"

extern char tukedasi_sanndanmeflag;

extern char memoryfusokuflag;//動的メモリを使わない場合は1
extern void AIkeiko(int,int);

extern long maxfilesize;
extern char shousin_yokoduna_kijun2;//先々場所の成績について、0→不問、1→優勝、2→準優勝以上
extern char warihen_toptonosa;//デフォは2、幕内下位で自動割変更する優勝争いトップとの差
extern char warihen_shourisuu;//デフォは9、幕内下位で自動割変更する勝利数
extern char warihen_nannitimemade;//デフォは14(14だとday-11<14の条件文になるので千秋楽は割変しない、15だと千秋楽も割変することになる)
extern char shousin_yokoduna_konbashowinsuu;
extern char shousin_yokoduna_bashosuu;
extern char shousin_yokoduna_winsuu;
extern int kaerizakisuu;
extern int	kaerizakirikisikonbasho[RIKISISUU];
extern struct rikisi_data rikisidata[RIKISISUU];//力士データ用構造体変数708人分用意
extern struct heya_data heyadata[HEYASUU];//相撲データ用構造体変数50部屋分用意
extern int mode;
extern int aite[RIKISISUU][15];//確定対戦相手の番付順位
extern int uesuu[RIKISISUU];//番付順位ごとの上の階級の力士との対戦数
extern int taisensuu[RIKISISUU];//番付順位ごとの対戦の決まった数(幕下以下の力士が７回を超えて対戦することのないようにするためのチェック用)
extern int day;//ゲーム内日数、一月＝30日間、偶数月の11日から25日に本場所開催
extern int bandukejunid[RIKISISUU];
extern int makizoedejouinoaitesitayosuu[RIKISISUU_MAKUUTI];//本来下位なのに取組チェンジの巻き添え食らって上位と対戦させられた数
extern int kainoaitesitayosuu[RIKISISUU_MAKUUTI];//torikumichange内で使う番付順の下位の相手をした数
extern int warimode;//0割り変更なし、1割変更有り
extern void torikumichange(void);//取組変更ルーチン
extern char kyuujouflag[RIKISISUU];//1で休場
extern int kyuujoukonbasho[RIKISISUU][15];//今場所の何日目に休場したかrikisidata[].winkonbasho[]みたいなもん
extern int shousin_yokoduna_kijun;//0→普通、1→厳しい、2→甘い
extern int rekidai_yokodunasuu;
extern void yokoduna_tanjou(int);//引数は力士ID
extern int iji_oozeki_winsuu;
extern int shousin_oozeki_kanrakuchokugowinsuu;
extern void game_main_backscreen(void);//基本ゲーム画面表示ルーチン
extern char namestring[RIKISISUU][12];//(力士IDごとの四股名,全角５文字まで)四股名
extern char hometownstring[SICHOUSONSUU][28];//(2544市町村分,全角13文字まで)出身地
extern char heyastring[HEYASUU][12];//(54部屋分,全角５文字まで)相撲部屋
extern int skipmode;//0:全部の取り組みの詳細を表示
extern int skipyear;//skipmode==2のときの指定年
extern int skipmonth;//skipmode==2のときの指定月
extern int month;//ゲーム内月
extern int year;//ゲーム内年
extern void buttonG_mouse_change(void);//ボタン上にマウスがあればボタン画像変更
extern int get_mouseclick_buttonG(void);//メニューボタンGをクリックしたら1を返し、そうでなければ0をかえす
extern int CheckHitKey_test(int);
extern int shousin_oozeki_konbashowinsuu[4];
extern int shousin_oozeki_sanyakuwintotal[4];
extern int shousin_oozeki_genoozekisuu[4];
extern int shousin_oozeki_kakuritu[4];
extern int kanraku_kadoban_konbashowinsuu;
extern void oozeki_tanjou(int);//引数は力士ID
extern int tukedasiid;//自部屋の幕下付け出しデビュー用の力士ID（通算ではなく0～707）
extern char tanshuku_banduke[RIKISISUU][5];
extern char bandukenamestring[10][12];//(10名称分、全角5文字まで)番付名
extern int heyabandukejunid[HEYASUU][20];//部屋ごとの番付順の力士ID、
extern int torimi_bandukejunid[RIKISISUU];//取り組み見るフラグがたっている力士の中での番付順の力士ID
extern int rinne_bandukejunid[RIKISISUU];//取り組み見るフラグがたっている力士の中での番付順の力士ID
extern int torimisuu;//取組見るフラグがたっている力士の数
extern int rinnesuu;//取組見るフラグがたっている力士の数
extern int rikisibetu_bandukejunid[RIKISISUU][RIKISISUU];//力士情報画面右リスト力士別タブ選択時の番付順ID
extern int rikisibetusuu[RIKISISUU];//各力士IDごとの力士別タブ選択時の右リストに表示すべき力士数
extern int rikisibetu_sentaku_id[RIKISISUU];//士別ページに表示する力士のID
extern int rikisisentaku_page;//力士情報画面で表示されているページの番号
extern int rikisisentaku_num;//力士情報画面で選択された力士のリスのト番号
extern int rikisisentaku_id;//選択された力士ID
extern int rikisisentaku_num_jiheya;//力士情報画面で選択された力士のリスト番号(自部屋分)
extern int torimi_rikisisentaku_page;//力士情報画面で選択された取見リストページ
extern int torimi_rikisisentaku_num;//力士情報画面で選択された取見リスト番号
extern int rinne_rikisisentaku_page;//力士情報画面で選択された取見リストページ
extern int rinne_rikisisentaku_num;//力士情報画面で選択された取見リスト番号
extern int bandukejun_or_jiheyaflag;//力士情報画面左リスト表示切替、0＞番付順、1＞自部屋力士、2＞取り組み見る力士
extern int rikisibetu_sentaku_page[RIKISISUU];
extern int rikisibetu_sentaku_num[RIKISISUU];
extern int superrikisisuu[10];//引数1＞朝青龍の数
extern int myheyaid;//プレイヤーの運営する相撲部屋ID
extern void banduke_hyojijunbi(void);//番付表示の準備ルーチン
extern char kyuujoustring[RIKISISUU][21];//全角10文字以内
extern int page_kyuujou;
extern int x1[40];//[]内のリスト番号の左上x座標、初期化はwinmain関数内でする
extern int y1[40];//左上y座標
extern int get_mouseclick(int x1,int y1,int x2,int y2);//座標(x1,y1)と(x2,y2)に囲まれたところで
extern int get_mouseclick_list(int x);//画面左のリスト上でクリックされたら1を返す、

extern int kyuujousuu_max_category;
extern int kyuujou_zenkyuu_ritu;
extern int kyuujou_yokoduna1_day;
extern int kyuujou_yokoduna2_day;
extern int kyuujou_yokoduna3_day;
extern int kyuujou_yokoduna3_day2;
extern int kyuujou_yokoduna4_day;
extern int kyuujou_yokoduna4_lostsuu;
extern int kyuujou_oozeki1_day;
extern int kyuujou_oozeki2_day;
extern int kyuujou_sekitori1_day;
extern int kyuujou_sekitori2_day;
extern int kyuujou_yokoduna1_ritu;
extern int kyuujou_yokoduna2_ritu;
extern int kyuujou_yokoduna3_ritu;
extern int kyuujou_yokoduna4_ritu;
extern int kyuujou_oozeki1_ritu;
extern int kyuujou_oozeki2_ritu;
extern int kyuujou_sekitori1_ritu;
extern int kyuujou_sekitori2_ritu;
extern int kyuujou_all_ritu;

extern int intaisuu;
extern int intairikisikonbasho[RIKISISUU];
extern void keiko_nakami_com(int);


char *kegastring[] =
{
	"故郷で蹴球",
	"網膜剥離" ,
	"首の怪我",
	"内臓疾患",
	"肩の怪我",
	"腕の怪我",
	"背中の怪我",
	"腰痛",
	"膝の怪我",
	"突き指",
	"手首の怪我",
	"肘の怪我",
	"足首の痛み",
	"足の指の怪我",
	"脱臼",
	"股関節痛",
	"大腿部の怪我",
	"ふくらはぎ痛",
	"足の踵の怪我",
	"体調不良",
	NULL
} ;	



void torikumisakusei1_kyuujou(void);//休場あり初日
void torikumisakusei2_kyuujou(void);//休場あり2日目以降
void bandukesakusei_kyuujou(void);
void torikumichange_kyuujou(void);
void kyuujou(void);//場所ごとの休場力士の決定ルーチン
void kyuujou_tochuu(void);//その日ごとの休場力士の決定ルーチン
void kyuujouhyoji(int x);//現役力士の休場履歴表示
void kyuujoushousaisettei_hyoji(void);
void kyuujoushousaisettei(void);
void shozokurekihyoji(int x);

void torikumisakusei1_kyuujou(void)//休場あり初日
{
	
	int i,ii,iuesuu=0,dameflag;
	int bme;//本人基準の番付順位
	int d=0;//日
	int byou;//相手基準の番付順位(ビーユーと読む)

	//力士の取組順・相手を全部-1にして初期化
	for (ii=0;ii<15;ii++){
		for (i=0;
		i<RIKISISUU;i++){
			rikisidata[i].torikumijun[ii]=-1;
			rikisidata[i].aitekonbasho[ii]=-1;
		}
	}
	//初期化
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		taisensuu[i]=0;
		uesuu[i]=0;
		for (ii=0;ii<15;ii++){
			aite[i][ii]=0;
			aite[i][ii]=-1;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	
	//幕内上位
	for (bme=0;bme<20;bme++){
		for (d=14;d>=7;d--){
			if (aite[bme][d]==-1
			 && kyuujouflag[bandukejunid[bme]]!=1){
				for (byou=0;byou<RIKISISUU_MAKUUTI;byou++){
					dameflag=0;
					for (i=0;i<15;i++){
						if (aite[bme][i]==byou){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
						 && kyuujouflag[bandukejunid[byou]]!=1
						 && aite[byou][d]==-1){
							aite[bme][d]=byou;
							aite[byou][d]=bme;
							break;
				 		}
					}
				}
				if (aite[bme][d]==-1
				 && kyuujouflag[bandukejunid[bme]]!=1){//格下十両力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
						 && kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//念のため格下幕下力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下三段目力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下序二段力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下序の口力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){
					aite[bme][d]=999;//補欠と対戦させるということにしてみた
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
		for (d=0;d<=6;d++){
			if (aite[bme][d]==-1
				&& kyuujouflag[bandukejunid[bme]]!=1){
				for (byou=0;byou<RIKISISUU_MAKUUTI;byou++){
					dameflag=0;
					for (i=0;i<15;i++){
						if (aite[bme][i]==byou){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
						 && kyuujouflag[bandukejunid[byou]]!=1
						 && aite[byou][d]==-1){
							aite[bme][d]=byou;
							aite[byou][d]=bme;
							break;
				 		}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下十両力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//念のため格下幕下力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下三段目力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下序二段力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下序の口力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){
					aite[bme][d]=999;//補欠と対戦させるということにしてみた
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}

	//幕内下位初日のみ
	for (bme=20;bme<RIKISISUU_MAKUUTI;bme++){
		for (d=0;d<=0;d++){
			if (aite[bme][d]==-1
				&& kyuujouflag[bandukejunid[bme]]!=1){
				for (byou=0;byou<RIKISISUU_MAKUUTI;byou++){
					dameflag=0;
					for (i=0;i<15;i++){
						if (aite[bme][i]==byou){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
						 && kyuujouflag[bandukejunid[byou]]!=1
						 && aite[byou][d]==-1){
							aite[bme][d]=byou;
							aite[byou][d]=bme;
							break;
				 		}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下十両力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//念のため格下幕下力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下三段目力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下序二段力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下序の口力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){
					aite[bme][d]=999;//補欠と対戦させるということにしてみた
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}
	//十両初日のみ
	for (bme=RIKISISUU_MAKUUTI;bme<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;bme++){
		for (d=0;d<=0;d++){
			if (aite[bme][d]==-1
				&& kyuujouflag[bandukejunid[bme]]!=1){
				for (byou=RIKISISUU_MAKUUTI;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou++){
					dameflag=0;
					for (i=0;i<15;i++){
						if (aite[bme][i]==byou){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
						 && kyuujouflag[bandukejunid[byou]]!=1
						 && aite[byou][d]==-1){
							aite[bme][d]=byou;
							aite[byou][d]=bme;
							break;
				 		}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下幕下力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下三段目力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下序二段力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下序の口力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){
					aite[bme][d]=999;//補欠と対戦させるということにしてみた
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}


	//幕下初日のみ
	for (bme=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;bme<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;bme++){
		for (d=0;d<=0;d++){
			if (aite[bme][d]==-1
			 && taisensuu[bme]<7
				&& kyuujouflag[bandukejunid[bme]]!=1){
				for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou++){
					dameflag=0;
					for (i=0;i<15;i++){
						if (aite[bme][i]==byou){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
						 && kyuujouflag[bandukejunid[byou]]!=1
						 && aite[byou][d]==-1
						 && taisensuu[byou]<7){
							aite[bme][d]=byou;
							aite[byou][d]=bme;
							taisensuu[bme]++;
							taisensuu[byou]++;
							break;
					 	}
					}
				}
				if (aite[bme][d]==-1//格下三段目力士と対戦
				 && taisensuu[bme]<7
					&& kyuujouflag[bandukejunid[bme]]!=1){
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
						 && taisensuu[bme]<7
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[bme]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1//格下序二段力士と対戦
				 && taisensuu[bme]<7
					&& kyuujouflag[bandukejunid[bme]]!=1){
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
						 && taisensuu[bme]<7
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[bme]++;
											taisensuu[byou]++;
											break;
										 }
									 }
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1//格下序の口力士と対戦
				 && taisensuu[bme]<7
					&& kyuujouflag[bandukejunid[bme]]!=1){
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
						 && taisensuu[bme]<7
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[bme]++;
											taisensuu[byou]++;
											break;
										 }
									 }
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
				 && taisensuu[bme]<7
					&& kyuujouflag[bandukejunid[bme]]!=1){//さてどうしよう？？
					aite[bme][d]=999;//補欠と対戦させるということにしてみた
					taisensuu[bme]++;
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}

	//三段目初日のみ
	for (bme=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;bme<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;bme++){
		for (d=0;d<=0;d++){
			if (aite[bme][d]==-1
			 && taisensuu[bme]<7
				&& kyuujouflag[bandukejunid[bme]]!=1){
				for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou++){
					dameflag=0;
					for (i=0;i<15;i++){
						if (aite[bme][i]==byou){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
						 && kyuujouflag[bandukejunid[byou]]!=1
						 && aite[byou][d]==-1
						 && taisensuu[byou]<7){
							aite[bme][d]=byou;
							aite[byou][d]=bme;
							taisensuu[bme]++;
							taisensuu[byou]++;
							break;
						 }
				 	}
				}
				if (aite[bme][d]==-1//格下序二段力士と対戦
				 && taisensuu[bme]<7
					&& kyuujouflag[bandukejunid[bme]]!=1){
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
						 && taisensuu[bme]<7
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[bme]++;
											taisensuu[byou]++;
											break;
										 }
									 }
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1//格下序の口力士と対戦
				 && taisensuu[bme]<7
					&& kyuujouflag[bandukejunid[bme]]!=1){
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
						 && taisensuu[bme]<7
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[bme]++;
											taisensuu[byou]++;
											break;
										 }
									 }
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
				 && taisensuu[bme]<7
					&& kyuujouflag[bandukejunid[bme]]!=1){//さてどうしよう？？
					aite[bme][d]=999;//補欠と対戦させるということにしてみた
					taisensuu[bme]++;
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}
	//序二段初日のみ
	for (bme=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;bme<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;bme++){
		for (d=0;d<=0;d++){
			if (aite[bme][d]==-1
			 && taisensuu[bme]<7
				&& kyuujouflag[bandukejunid[bme]]!=1){
				for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou++){
					dameflag=0;
					for (i=0;i<15;i++){
						if (aite[bme][i]==byou){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
						 && kyuujouflag[bandukejunid[byou]]!=1
						 && aite[byou][d]==-1
						 && taisensuu[byou]<7){
							aite[bme][d]=byou;
							aite[byou][d]=bme;
							taisensuu[bme]++;
							taisensuu[byou]++;
							break;
						 }
				 	}
				}
				if (aite[bme][d]==-1//格下序の口力士と対戦
				 && taisensuu[bme]<7
					&& kyuujouflag[bandukejunid[bme]]!=1){
					for (iuesuu=1;iuesuu<15;iuesuu++){
						if (aite[bme][d]==-1
						 && taisensuu[bme]<7
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;byou++){
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[bme]++;
											taisensuu[byou]++;
											break;
										 }
									 }
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
				 && taisensuu[bme]<7
					&& kyuujouflag[bandukejunid[bme]]!=1){//さてどうしよう？？
					aite[bme][d]=999;//補欠と対戦させるということにしてみた
					taisensuu[bme]++;
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}
	//序の口初日のみ
	for (bme=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;bme<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;bme++){
		for (d=0;d<=0;d++){
			if (aite[bme][d]==-1
			 && taisensuu[bme]<7
				&& kyuujouflag[bandukejunid[bme]]!=1){
				for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;byou++){
					dameflag=0;
					for (i=0;i<15;i++){
						if (aite[bme][i]==byou){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
						 && kyuujouflag[bandukejunid[byou]]!=1
						 && aite[byou][d]==-1
						 && taisensuu[byou]<7){
							aite[bme][d]=byou;
							aite[byou][d]=bme;
							taisensuu[bme]++;
							taisensuu[byou]++;
							break;
						 }
				 	}
				}
				if (aite[bme][d]==-1
				 && taisensuu[bme]<7
					&& kyuujouflag[bandukejunid[bme]]!=1){//さてどうしよう？？
					aite[bme][d]=999;//補欠と対戦させるということにしてみた
					taisensuu[bme]++;
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}

	//代入処理
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}
		for (ii=0;ii<15;ii++){
			if (aite[i][ii]==999){
				rikisidata[bandukejunid[i]].aitekonbasho[ii]=999;
			}else if (aite[i][ii]!=-1){
				rikisidata[bandukejunid[i]].aitekonbasho[ii]=bandukejunid[aite[i][ii]];
			}else if (aite[i][ii]==-1){
				rikisidata[bandukejunid[i]].aitekonbasho[ii]=-1;
			}
		}
	}

	/*if (1){
		FILE *fp;
		fp = fopen("kyuujou.csv","w");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"%d日目\n",day-11+1);
		for (i=0;i<RIKISISUU;i++){
			fprintf(fp,"%d,%d\n",i,
			kyuujouflag[bandukejunid[i]]);
		}
		//クローズ
		fclose(fp);
		fp = fopen("torikumisakusei.csv","w");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"番付順ID,休場,初日,2日目,3日目,4日目,5日目,6日目,7日目,8日目,9日目,10日目,11日目,12日目,13日目,14日目,15日目\n");
		for (i=0;i<RIKISISUU;i++){
			fprintf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",i,kyuujouflag[bandukejunid[i]],
			rikisidata[bandukejunid[i]].aitekonbasho[0],
			rikisidata[bandukejunid[i]].aitekonbasho[1],
			rikisidata[bandukejunid[i]].aitekonbasho[2],
			rikisidata[bandukejunid[i]].aitekonbasho[3],
			rikisidata[bandukejunid[i]].aitekonbasho[4],
			rikisidata[bandukejunid[i]].aitekonbasho[5],
			rikisidata[bandukejunid[i]].aitekonbasho[6],
			rikisidata[bandukejunid[i]].aitekonbasho[7],
			rikisidata[bandukejunid[i]].aitekonbasho[8],
			rikisidata[bandukejunid[i]].aitekonbasho[9],
			rikisidata[bandukejunid[i]].aitekonbasho[10],
			rikisidata[bandukejunid[i]].aitekonbasho[11],
			rikisidata[bandukejunid[i]].aitekonbasho[12],
			rikisidata[bandukejunid[i]].aitekonbasho[13],
			rikisidata[bandukejunid[i]].aitekonbasho[14]);
		}
		//クローズ
		fclose(fp);
	}*/

			
	return;
}

void torikumisakusei2_kyuujou(void)//2日目以降
{
	int bme;//本人基準の番付順位
	int byou;//相手基準の番付順位(ビーユーと読む)

	int isitasuu=0;
	int sitasuu[RIKISISUU];
	int temp=0;
	int i,ii,iii,iuesuu=0,count,daycount,dameflag;
	int wme=0;//本人基準の勝ち順順位
	int d=0;//日
	int wyou=0;//相手基準の勝ち順順位(ビーユーと読む)
	int winjunb[RIKISISUU];//勝ち星順の番付順位(まったくの通しではなく、各段ごとで整理されている)
	int winjunid[RIKISISUU];//勝ち星順のID(まったくの通しではなく、各段ごとで整理されている)
	int banwin_makuuti[RIKISISUU_MAKUUTI];//幕内下位の番付順ごとの勝ち星数(つまり0～19は未使用)
	int winjun_makuuti[RIKISISUU_MAKUUTI];//幕内下位の勝ち星順の番付順位(つまり0～19は未使用)
	int banwin_jyuuryou[RIKISISUU_JYUURYOU];
	int winjun_jyuuryou[RIKISISUU_JYUURYOU];
	int banwin_makusita[RIKISISUU_MAKUSITA];
	int winjun_makusita[RIKISISUU_MAKUSITA];
	int banwin_sandanme[RIKISISUU_SANDANME];
	int winjun_sandanme[RIKISISUU_SANDANME];
	int banwin_jonidan[RIKISISUU_JONIDAN];
	int winjun_jonidan[RIKISISUU_JONIDAN];
	int banwin_jonokuti[RIKISISUU_JONOKUTI];
	int winjun_jonokuti[RIKISISUU_JONOKUTI];

	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjunb[i]=0;
		winjunid[i]=0;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		banwin_makuuti[i]=0;
		winjun_makuuti[i]=0;
	}
	for (i=0;i<RIKISISUU_JYUURYOU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		banwin_jyuuryou[i]=0;
		winjun_jyuuryou[i]=0;
	}
	for (i=0;i<RIKISISUU_MAKUSITA;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		banwin_makusita[i]=0;
		winjun_makusita[i]=0;
	}
	for (i=0;i<RIKISISUU_SANDANME;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		banwin_sandanme[i]=0;
		winjun_sandanme[i]=0;
	}
	for (i=0;i<RIKISISUU_JONIDAN;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		banwin_jonidan[i]=0;
		winjun_jonidan[i]=0;
	}
	for (i=0;i<RIKISISUU_JONOKUTI;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		banwin_jonokuti[i]=0;
		winjun_jonokuti[i]=0;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//勝ち星計算+番付による重み
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		for (ii=0;ii<15;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
				banwin_makuuti[i]++;
			}
//			//何回も格下力士と対戦しないようにするための補正
//			if (rikisidata[bandukejunid[i]].aitekonbasho[ii]>=0 && rikisidata[bandukejunid[i]].aitekonbasho[ii]<=RIKISISUU-1){
//				if (rikisidata[rikisidata[bandukejunid[i]].aitekonbasho[ii]].bandukenameid>4){
//					banwin_makuuti[i]+=3;
//				}
//			}
		}
		//番付による重み
		banwin_makuuti[i]+=(int)((RIKISISUU_MAKUUTI-i)/4);
	}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (i=RIKISISUU_MAKUUTI;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		for (ii=0;ii<15;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
				banwin_jyuuryou[i-RIKISISUU_MAKUUTI]++;
			}
//			//何回も格下力士と対戦しないようにするための補正
//			if (rikisidata[bandukejunid[i]].aitekonbasho[ii]>=0 && rikisidata[bandukejunid[i]].aitekonbasho[ii]<=RIKISISUU-1){
//				if (rikisidata[rikisidata[bandukejunid[i]].aitekonbasho[ii]].bandukenameid>5){
//					banwin_jyuuryou[i-RIKISISUU_MAKUUTI]+=3;
//				}
//			}
		}
		//番付による重み
		banwin_jyuuryou[i-RIKISISUU_MAKUUTI]+=(int)((RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU-i)/4);
	}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		for (ii=0;ii<15;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
				banwin_makusita[i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU)]++;
			}
		}
		//番付による重み
		banwin_makusita[i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU)]+=(int)((120-rikisidata[bandukejunid[i]].bandukesuuji)/4);//重み
	}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		for (ii=0;ii<15;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
				banwin_sandanme[i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)]++;
			}
		}
		//番付による重み
		banwin_sandanme[i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)]+=(int)((120-rikisidata[bandukejunid[i]].bandukesuuji)/4);//重み
	}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		for (ii=0;ii<15;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
				banwin_jonidan[i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)]++;
			}
		}
		//番付による重み
		banwin_jonidan[i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)]+=(int)((120-rikisidata[bandukejunid[i]].bandukesuuji)/4);//重み
	}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;i++){
		for (ii=0;ii<15;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
				banwin_jonokuti[i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN)]++;
			}
		}
		//番付による重み
		banwin_jonokuti[i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN)]+=(int)((120-rikisidata[bandukejunid[i]].bandukesuuji)/4);//重み
	}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//各段ごとの勝ち星順ID作成

	//幕内下位
	//バブルソート
	for (i=20;i<RIKISISUU_MAKUUTI;i++){
		winjun_makuuti[i]=i;
	}
	for (i = 20;i < RIKISISUU_MAKUUTI - 1;i++) {
		for (ii = 20;ii < RIKISISUU_MAKUUTI - 1;ii++) {
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (banwin_makuuti[ii + 1] > banwin_makuuti[ii]) {
				temp = banwin_makuuti[ii];
				banwin_makuuti[ii] = banwin_makuuti[ii + 1];
				banwin_makuuti[ii + 1] = temp;
				temp = winjun_makuuti[ii];
				winjun_makuuti[ii] = winjun_makuuti[ii+1];
				winjun_makuuti[ii+1] = temp;
			}
		}
		//Sleep(1);
		//if( ProcessMessage() == -1 )
		//{
		//	mode=1;
		//	return ;	// エラーが起きたらループから抜ける
		//}
	}
	//IDへ変換
	for (i=20;i<RIKISISUU_MAKUUTI;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjunb[i]=winjun_makuuti[i];
		winjunid[i]=bandukejunid[winjun_makuuti[i]];
	}
	//十両
	//バブルソート
	for (i=0;i<RIKISISUU_JYUURYOU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjun_jyuuryou[i]=i;
	}
	for (i = 0;i < RIKISISUU_JYUURYOU - 1;i++) {
		for (ii = 0;ii < RIKISISUU_JYUURYOU - 1;ii++) {
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (banwin_jyuuryou[ii + 1] > banwin_jyuuryou[ii]) {
				temp = banwin_jyuuryou[ii];
				banwin_jyuuryou[ii] = banwin_jyuuryou[ii + 1];
				banwin_jyuuryou[ii + 1] = temp;
				temp = winjun_jyuuryou[ii];
				winjun_jyuuryou[ii] = winjun_jyuuryou[ii+1];
				winjun_jyuuryou[ii+1] = temp;
			}
		}
		//Sleep(1);
		//if( ProcessMessage() == -1 )
		//{
		//	mode=1;
		//	return ;	// エラーが起きたらループから抜ける
		//}
	}
	//IDへ変換
	for (i=0;i<RIKISISUU_JYUURYOU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjunb[RIKISISUU_MAKUUTI+i]=RIKISISUU_MAKUUTI+winjun_jyuuryou[i];
		winjunid[RIKISISUU_MAKUUTI+i]=bandukejunid[RIKISISUU_MAKUUTI+winjun_jyuuryou[i]];
	}
	//幕下
	//バブルソート
	for (i=0;i<RIKISISUU_MAKUSITA;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjun_makusita[i]=i;
	}
	for (i = 0;i < RIKISISUU_MAKUSITA - 1;i++) {
		for (ii = 0;ii < RIKISISUU_MAKUSITA - 1;ii++) {
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (banwin_makusita[ii + 1] > banwin_makusita[ii]) {
				temp = banwin_makusita[ii];
				banwin_makusita[ii] = banwin_makusita[ii + 1];
				banwin_makusita[ii + 1] = temp;
				temp = winjun_makusita[ii];
				winjun_makusita[ii] = winjun_makusita[ii+1];
				winjun_makusita[ii+1] = temp;
			}
		}
		//Sleep(1);
		//if( ProcessMessage() == -1 )
		//{
		//	mode=1;
		//	return ;	// エラーが起きたらループから抜ける
		//}
	}
	//IDへ変換
	for (i=0;i<RIKISISUU_MAKUSITA;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjunb[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+i]=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+winjun_makusita[i];
		winjunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+i]=bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+winjun_makusita[i]];
	}
	//三段目
	//バブルソート
	for (i=0;i<RIKISISUU_SANDANME;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjun_sandanme[i]=i;
	}
	for (i = 0;i < RIKISISUU_SANDANME - 1;i++) {
		for (ii = 0;ii < RIKISISUU_SANDANME - 1;ii++) {
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (banwin_sandanme[ii + 1] > banwin_sandanme[ii]) {
				temp = banwin_sandanme[ii];
				banwin_sandanme[ii] = banwin_sandanme[ii + 1];
				banwin_sandanme[ii + 1] = temp;
				temp = winjun_sandanme[ii];
				winjun_sandanme[ii] = winjun_sandanme[ii+1];
				winjun_sandanme[ii+1] = temp;
			}
		}
		//Sleep(1);
		//if( ProcessMessage() == -1 )
		//{
		//	mode=1;
		//	return ;	// エラーが起きたらループから抜ける
		//}
	}
	//IDへ変換
	for (i=0;i<RIKISISUU_SANDANME;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjunb[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+i]=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+winjun_sandanme[i];
		winjunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+i]=bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+winjun_sandanme[i]];
	}
	//序二段
	//バブルソート
	for (i=0;i<RIKISISUU_JONIDAN;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjun_jonidan[i]=i;
	}
	for (i = 0;i < RIKISISUU_JONIDAN - 1;i++) {
		for (ii = 0;ii < RIKISISUU_JONIDAN - 1;ii++) {
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (banwin_jonidan[ii + 1] > banwin_jonidan[ii]) {
				temp = banwin_jonidan[ii];
				banwin_jonidan[ii] = banwin_jonidan[ii + 1];
				banwin_jonidan[ii + 1] = temp;
				temp = winjun_jonidan[ii];
				winjun_jonidan[ii] = winjun_jonidan[ii+1];
				winjun_jonidan[ii+1] = temp;
			}
		}
		//Sleep(1);
		//if( ProcessMessage() == -1 )
		//{
		//	mode=1;
		//	return ;	// エラーが起きたらループから抜ける
		//}
	}
	//IDへ変換
	for (i=0;i<RIKISISUU_JONIDAN;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjunb[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+i]=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+winjun_jonidan[i];
		winjunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+i]=bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+winjun_jonidan[i]];
	}
	//序の口
	//バブルソート
	for (i=0;i<RIKISISUU_JONOKUTI;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjun_jonokuti[i]=i;
	}
	for (i = 0;i < RIKISISUU_JONOKUTI - 1;i++) {
		for (ii = 0;ii < RIKISISUU_JONOKUTI - 1;ii++) {
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (banwin_jonokuti[ii + 1] > banwin_jonokuti[ii]) {
				temp = banwin_jonokuti[ii];
				banwin_jonokuti[ii] = banwin_jonokuti[ii + 1];
				banwin_jonokuti[ii + 1] = temp;
				temp = winjun_jonokuti[ii];
				winjun_jonokuti[ii] = winjun_jonokuti[ii+1];
				winjun_jonokuti[ii+1] = temp;
			}
		}
		//Sleep(1);
		//if( ProcessMessage() == -1 )
		//{
		//	mode=1;
		//	return ;	// エラーが起きたらループから抜ける
		//}
	}
	//IDへ変換
	for (i=0;i<RIKISISUU_JONOKUTI;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjunb[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+i]=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+winjun_jonokuti[i];
		winjunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+i]=bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+winjun_jonokuti[i]];
	}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//格下力士との対戦数を数える
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		sitasuu[i]=0;
		for (ii=0;ii<15;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[i].aitekonbasho[ii]>=0 && rikisidata[i].aitekonbasho[ii]<=RIKISISUU-1){
				if (rikisidata[i].bandukenameid<rikisidata[rikisidata[i].aitekonbasho[ii]].bandukenameid){
					sitasuu[i]++;
//if (rikisidata[i].bandukenameid==4){
//ClearDrawScreen();DrawFormatString(100,390,CRGREEN,"i %d  bandukejun %d",i,rikisidata[i].bandukejun);ScreenFlip();WaitKey();
//}
				}
			}
		}
	}

	//初期化
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		//taisensuu[i]=0;
		uesuu[i]=0;
		for (ii=0;ii<15;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			aite[i][ii]=0;
			aite[i][ii]=-1;
		}
	}

	//今場所のこれまでの対戦相手をセット
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		uesuu[i]=0;
		for (ii=0;ii<day-11;ii++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[bandukejunid[i]].aitekonbasho[ii]>=0 && rikisidata[bandukejunid[i]].aitekonbasho[ii]<=RIKISISUU-1){
				aite[i][ii]=rikisidata[rikisidata[bandukejunid[i]].aitekonbasho[ii]].bandukejun;
				if (rikisidata[bandukejunid[i]].bandukenameid>rikisidata[rikisidata[bandukejunid[i]].aitekonbasho[ii]].bandukenameid){
					uesuu[i]++;
				}
			}
			if (rikisidata[bandukejunid[i]].aitekonbasho[ii]==999){
				aite[i][ii]=999;
			}
			if (rikisidata[bandukejunid[i]].aitekonbasho[ii]==-1){
				aite[i][ii]=-1;
			}
		}
	}

	//////////////////ここに幕内下位で好調な力士を上位と当てる処理/////////////
	//幕内下位で成績優秀な力士を上位と当てる処理
	if (day-11==2){
		for (i=0;i<RIKISISUU_MAKUUTI;i++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			kainoaitesitayosuu[i]=0;
			makizoedejouinoaitesitayosuu[i]=0;
		}
	}
	if (warimode==1 && day-11>=2){//
		torikumichange_kyuujou();
	}

	//本処理
	//幕内上位
	for (bme=0;bme<20;bme++){
		for (d=14;d>=7;d--){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (d<(day-11)) break;
			if (aite[bme][d]==-1
				&& kyuujouflag[bandukejunid[bme]]!=1){
				for (byou=0;byou<RIKISISUU_MAKUUTI;byou++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					dameflag=0;
					for (i=0;i<15;i++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[bme][i]==byou){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
						 && kyuujouflag[bandukejunid[byou]]!=1
						 && aite[byou][d]==-1){
							aite[bme][d]=byou;
							aite[byou][d]=bme;
							break;
				 		}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下十両力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//念のため格下幕下力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下三段目力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下序二段力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下序の口力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;byou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){
					aite[bme][d]=999;//補欠と対戦させるということにしてみた
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
		for (d=day-11;d<=6;d++){//d=0をd=day-11に変えた
			if (aite[bme][d]==-1
				&& kyuujouflag[bandukejunid[bme]]!=1){
				for (byou=0;byou<RIKISISUU_MAKUUTI;byou++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					dameflag=0;
					for (i=0;i<15;i++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[bme][i]==byou){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
						 && kyuujouflag[bandukejunid[byou]]!=1
						 && aite[byou][d]==-1){
							aite[bme][d]=byou;
							aite[byou][d]=bme;
							break;
				 		}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下十両力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//念のため格下幕下力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下三段目力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下序二段力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){//格下序の口力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[bme][d]==-1
							&& kyuujouflag[bandukejunid[bme]]!=1){
							for (byou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;byou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;byou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[bme][i]==byou){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[byou]<=iuesuu){
										if (rikisidata[bandukejunid[bme]].heyaid!=rikisidata[bandukejunid[byou]].heyaid
										 && kyuujouflag[bandukejunid[byou]]!=1
										 && aite[byou][d]==-1
										 && taisensuu[byou]<7){
											aite[bme][d]=byou;
											aite[byou][d]=bme;
											uesuu[byou]++;
											taisensuu[byou]++;
											break;
										 }
									}
								}
							}
							if (aite[bme][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[bme][d]==-1
					&& kyuujouflag[bandukejunid[bme]]!=1){
					aite[bme][d]=999;//補欠と対戦させるということにしてみた
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}

	//本処理
	//幕内下位
	d=day-11;
	for (isitasuu=15;isitasuu>=3;isitasuu--){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (wme=RIKISISUU_MAKUUTI-1;wme>=20;wme--){//格下力士との対戦数を抑える処理
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (aite[winjunb[wme]][d]==-1
				&& kyuujouflag[winjunid[wme]]!=1){
				if (sitasuu[winjunid[wme]]>=isitasuu){
					for (wyou=RIKISISUU_MAKUUTI-1;wyou>=20;wyou--){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								break;
					 		}
						}
					}
				}
			}
		}
	}
	for (wme=20;wme<RIKISISUU_MAKUUTI;wme++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (d=day-11;d<=day-11;d++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (aite[winjunb[wme]][d]==-1
				&& kyuujouflag[winjunid[wme]]!=1){
				for (wyou=20;wyou<RIKISISUU_MAKUUTI;wyou++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					dameflag=0;
					for (i=0;i<15;i++){
						if (aite[winjunb[wme]][i]==winjunb[wyou]){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
						 && kyuujouflag[winjunid[wyou]]!=1
						 && aite[winjunb[wyou]][d]==-1){
							aite[winjunb[wme]][d]=winjunb[wyou];
							aite[winjunb[wyou]][d]=winjunb[wme];
							break;
				 		}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下十両力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											break;
										 }
									}
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//念のため格下幕下力士と対戦1-5
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=1 && rikisidata[winjunid[wyou]].bandukesuuji<=5)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//念のため格下幕下力士と対戦6-15
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=6 && rikisidata[winjunid[wyou]].bandukesuuji<=15)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//念のため格下幕下力士と対戦16-30
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=16 && rikisidata[winjunid[wyou]].bandukesuuji<=30)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//念のため格下幕下力士と対戦31-45
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=31 && rikisidata[winjunid[wyou]].bandukesuuji<=45)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//念のため格下幕下力士と対戦46-60
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=46 && rikisidata[winjunid[wyou]].bandukesuuji<=60)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦1-20
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=1 && rikisidata[winjunid[wyou]].bandukesuuji<=20)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦21-40
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=21 && rikisidata[winjunid[wyou]].bandukesuuji<=40)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦41-60
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=41 && rikisidata[winjunid[wyou]].bandukesuuji<=60)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦61-80
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=61 && rikisidata[winjunid[wyou]].bandukesuuji<=80)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦81-100
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=81 && rikisidata[winjunid[wyou]].bandukesuuji<=100)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦1-20
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=1 && rikisidata[winjunid[wyou]].bandukesuuji<=20)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦21-40
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=21 && rikisidata[winjunid[wyou]].bandukesuuji<=40)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦41-60
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=41 && rikisidata[winjunid[wyou]].bandukesuuji<=60)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦61-80
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=61 && rikisidata[winjunid[wyou]].bandukesuuji<=80)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦81-100
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=81 && rikisidata[winjunid[wyou]].bandukesuuji<=100)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦101-120
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=101 && rikisidata[winjunid[wyou]].bandukesuuji<=120)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序の口力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1
					&& kyuujouflag[winjunid[wme]]!=1){
					aite[winjunb[wme]][d]=999;//補欠と対戦させるということにしてみた
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}
	//十両
	d=day-11;
	for (isitasuu=15;isitasuu>=3;isitasuu--){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (wme=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU-1;wme>=RIKISISUU_MAKUUTI;wme--){//格下力士との対戦数を抑える処理
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (aite[winjunb[wme]][d]==-1
				&& kyuujouflag[winjunid[wme]]!=1){
				if (sitasuu[winjunid[wme]]>=isitasuu){
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU-1;wyou>=RIKISISUU_MAKUUTI;wyou--){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								break;
					 		}
						}
					}
				}
			}
		}
	}
	for (wme=RIKISISUU_MAKUUTI;wme<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wme++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (d=day-11;d<=day-11;d++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (aite[winjunb[wme]][d]==-1
				&& kyuujouflag[winjunid[wme]]!=1){
				for (wyou=RIKISISUU_MAKUUTI;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					dameflag=0;
					for (i=0;i<15;i++){
						if (aite[winjunb[wme]][i]==winjunb[wyou]){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
						 && kyuujouflag[winjunid[wyou]]!=1
						 && aite[winjunb[wyou]][d]==-1){
							aite[winjunb[wme]][d]=winjunb[wyou];
							aite[winjunb[wyou]][d]=winjunb[wme];
							break;
						 }
				 	}
				}
				if (aite[winjunb[wme]][d]==-1){//念のため格下幕下力士と対戦6-15
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=1 && rikisidata[winjunid[wyou]].bandukesuuji<=15)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//念のため格下幕下力士と対戦16-30
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=16 && rikisidata[winjunid[wyou]].bandukesuuji<=30)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//念のため格下幕下力士と対戦31-45
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=31 && rikisidata[winjunid[wyou]].bandukesuuji<=45)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//念のため格下幕下力士と対戦46-60
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=46 && rikisidata[winjunid[wyou]].bandukesuuji<=60)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦1-20
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=1 && rikisidata[winjunid[wyou]].bandukesuuji<=20)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦21-40
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=21 && rikisidata[winjunid[wyou]].bandukesuuji<=40)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦41-60
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=41 && rikisidata[winjunid[wyou]].bandukesuuji<=60)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦61-80
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=61 && rikisidata[winjunid[wyou]].bandukesuuji<=80)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦81-100
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=81 && rikisidata[winjunid[wyou]].bandukesuuji<=100)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦1-20
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=1 && rikisidata[winjunid[wyou]].bandukesuuji<=20)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦21-40
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=21 && rikisidata[winjunid[wyou]].bandukesuuji<=40)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦41-60
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=41 && rikisidata[winjunid[wyou]].bandukesuuji<=60)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦61-80
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=61 && rikisidata[winjunid[wyou]].bandukesuuji<=80)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦81-100
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=81 && rikisidata[winjunid[wyou]].bandukesuuji<=100)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦101-120
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=101 && rikisidata[winjunid[wyou]].bandukesuuji<=120)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序の口力士と対戦
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1
					&& kyuujouflag[winjunid[wme]]!=1){
					aite[winjunb[wme]][d]=999;//補欠と対戦させるということにしてみた
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}

if ((day-11)==3 || (day-11)==6 || (day-11)==9 || (day-11)==11 || (day-11)==13 || (day-11)==14){
	//幕下
	for (wme=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wme<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wme++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (d=day-11;d<=day-11;d++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (aite[winjunb[wme]][d]==-1
			 && taisensuu[winjunb[wme]]<7
				&& kyuujouflag[winjunid[wme]]!=1){
				for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					dameflag=0;
					if (!(rikisidata[winjunid[wme]].bandukesuuji+5 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-5 <= rikisidata[winjunid[wyou]].bandukesuuji)){
						dameflag=1;//番付の近い力士同士で対戦させるため+-5
					}
					for (i=0;i<15;i++){
						if (aite[winjunb[wme]][i]==winjunb[wyou]){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
						 && kyuujouflag[winjunid[wyou]]!=1
						 && aite[winjunb[wyou]][d]==-1
						 && taisensuu[winjunb[wyou]]<7){
							aite[winjunb[wme]][d]=winjunb[wyou];
							aite[winjunb[wyou]][d]=winjunb[wme];
							taisensuu[winjunb[wme]]++;
							taisensuu[winjunb[wyou]]++;
							break;
						 }
				 	}
				}
				if (aite[winjunb[wme]][d]==-1){//+-10
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+10 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-10 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-10
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//+-15
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+15 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-15 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-15
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//+-20
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+20 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-20 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-20
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//+-30
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+30 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-30 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-30
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//同じカテゴリーの力士同士で対戦させるため
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦1-20
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=1 && rikisidata[winjunid[wyou]].bandukesuuji<=20)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦21-40
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=21 && rikisidata[winjunid[wyou]].bandukesuuji<=40)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦41-60
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=41 && rikisidata[winjunid[wyou]].bandukesuuji<=60)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦61-80
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=61 && rikisidata[winjunid[wyou]].bandukesuuji<=80)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下三段目力士と対戦81-100
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=81 && rikisidata[winjunid[wyou]].bandukesuuji<=100)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦1-20
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=1 && rikisidata[winjunid[wyou]].bandukesuuji<=20)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦21-40
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=21 && rikisidata[winjunid[wyou]].bandukesuuji<=40)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦41-60
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=41 && rikisidata[winjunid[wyou]].bandukesuuji<=60)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦61-80
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=61 && rikisidata[winjunid[wyou]].bandukesuuji<=80)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦81-100
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=81 && rikisidata[winjunid[wyou]].bandukesuuji<=100)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦101-120
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=101 && rikisidata[winjunid[wyou]].bandukesuuji<=120)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1//格下序の口力士と対戦
				 && taisensuu[winjunb[wme]]<7){
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1
						 && taisensuu[winjunb[wme]]<7){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1
				 && taisensuu[winjunb[wme]]<7
					&& kyuujouflag[winjunid[wme]]!=1){//さてどうしよう？？
					aite[winjunb[wme]][d]=999;//補欠と対戦させるということにしてみた
					taisensuu[winjunb[wme]]++;
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}
	//三段目
	for (wme=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wme<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wme++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (d=day-11;d<=day-11;d++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (aite[winjunb[wme]][d]==-1
			 && taisensuu[winjunb[wme]]<7
				&& kyuujouflag[winjunid[wme]]!=1){
				for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					dameflag=0;
					if (!(rikisidata[winjunid[wme]].bandukesuuji+5 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-5 <= rikisidata[winjunid[wyou]].bandukesuuji)){
						dameflag=1;//番付の近い力士同士で対戦させるため+-5
					}
					for (i=0;i<15;i++){
						if (aite[winjunb[wme]][i]==winjunb[wyou]){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
						 && kyuujouflag[winjunid[wyou]]!=1
						 && aite[winjunb[wyou]][d]==-1
						 && taisensuu[winjunb[wyou]]<7){
							aite[winjunb[wme]][d]=winjunb[wyou];
							aite[winjunb[wyou]][d]=winjunb[wme];
							taisensuu[winjunb[wme]]++;
							taisensuu[winjunb[wyou]]++;
							break;
						 }
				 	}
				}
				if (aite[winjunb[wme]][d]==-1){
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+10 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-10 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-10
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+15 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-15 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-15
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+20 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-20 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-20
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+30 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-30 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-30
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//同じカテゴリーの力士同士で対戦させるため
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦1-20
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=1 && rikisidata[winjunid[wyou]].bandukesuuji<=20)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦21-40
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=21 && rikisidata[winjunid[wyou]].bandukesuuji<=40)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦41-60
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=41 && rikisidata[winjunid[wyou]].bandukesuuji<=60)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦61-80
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=61 && rikisidata[winjunid[wyou]].bandukesuuji<=80)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦81-100
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=81 && rikisidata[winjunid[wyou]].bandukesuuji<=100)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//格下序二段力士と対戦101-120
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								if (!(rikisidata[winjunid[wyou]].bandukesuuji>=101 && rikisidata[winjunid[wyou]].bandukesuuji<=120)){
									dameflag=1;
								}
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1//格下序の口力士と対戦
				 && taisensuu[winjunb[wme]]<7){
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1
						 && taisensuu[winjunb[wme]]<7){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1
				 && taisensuu[winjunb[wme]]<7
					&& kyuujouflag[winjunid[wme]]!=1){//さてどうしよう？？
					aite[winjunb[wme]][d]=999;//補欠と対戦させるということにしてみた
					taisensuu[winjunb[wme]]++;
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}
	//序二段
	for (wme=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wme<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wme++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (d=day-11;d<=day-11;d++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (aite[winjunb[wme]][d]==-1
			 && taisensuu[winjunb[wme]]<7
				&& kyuujouflag[winjunid[wme]]!=1){
				for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					dameflag=0;
					if (!(rikisidata[winjunid[wme]].bandukesuuji+5 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-5 <= rikisidata[winjunid[wyou]].bandukesuuji)){
						dameflag=1;//番付の近い力士同士で対戦させるため+-5
					}
					for (i=0;i<15;i++){
						if (aite[winjunb[wme]][i]==winjunb[wyou]){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
						 && kyuujouflag[winjunid[wyou]]!=1
						 && aite[winjunb[wyou]][d]==-1
						 && taisensuu[winjunb[wyou]]<7){
							aite[winjunb[wme]][d]=winjunb[wyou];
							aite[winjunb[wyou]][d]=winjunb[wme];
							taisensuu[winjunb[wme]]++;
							taisensuu[winjunb[wyou]]++;
							break;
						 }
				 	}
				}
				if (aite[winjunb[wme]][d]==-1){//
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+10 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-10 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-10
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+15 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-15 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-15
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+20 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-20 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-20
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+30 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-30 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-30
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//同じカテゴリーの力士同士で対戦させるため+-20
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
					 	}
					}
				}
				if (aite[winjunb[wme]][d]==-1//格下序の口力士と対戦
				 && taisensuu[winjunb[wme]]<7){
					for (iuesuu=1;iuesuu<15;iuesuu++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (aite[winjunb[wme]][d]==-1
						 && taisensuu[winjunb[wme]]<7){
							for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;wyou++){
								//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
								dameflag=0;
								for (i=0;i<15;i++){
									if (aite[winjunb[wme]][i]==winjunb[wyou]){
										dameflag=1;
										break;
									}
								}
								if (dameflag!=1){
									if (uesuu[winjunb[wyou]]<=iuesuu){
										if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
										 && kyuujouflag[winjunid[wyou]]!=1
										 && aite[winjunb[wyou]][d]==-1
										 && taisensuu[winjunb[wyou]]<7){
											aite[winjunb[wme]][d]=winjunb[wyou];
											aite[winjunb[wyou]][d]=winjunb[wme];
											uesuu[winjunb[wyou]]++;
											taisensuu[winjunb[wme]]++;
											taisensuu[winjunb[wyou]]++;
											break;
										 }
									 }
								}
							}
							if (aite[winjunb[wme]][d]!=-1){
								break;
							}
						}
					}
				}
				if (aite[winjunb[wme]][d]==-1
				 && taisensuu[winjunb[wme]]<7
					&& kyuujouflag[winjunid[wme]]!=1){//さてどうしよう？？
					aite[winjunb[wme]][d]=999;//補欠と対戦させるということにしてみた
					taisensuu[winjunb[wme]]++;
				}
				// メッセージ処理
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return ;
				//}
				//Sleep(1);
			}
		}
	}
	//序の口
	for (wme=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wme<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;wme++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (d=day-11;d<=day-11;d++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (aite[winjunb[wme]][d]==-1
			 && taisensuu[winjunb[wme]]<7
				&& kyuujouflag[winjunid[wme]]!=1){
				for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;wyou++){
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					dameflag=0;
					if (!(rikisidata[winjunid[wme]].bandukesuuji+5 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-5 <= rikisidata[winjunid[wyou]].bandukesuuji)){
						dameflag=1;//番付の近い力士同士で対戦させるため+-5
					}
					for (i=0;i<15;i++){
						if (aite[winjunb[wme]][i]==winjunb[wyou]){
							dameflag=1;
							break;
						}
					}
					if (dameflag!=1){
						if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
						 && kyuujouflag[winjunid[wyou]]!=1
						 && aite[winjunb[wyou]][d]==-1
						 && taisensuu[winjunb[wyou]]<7){
							aite[winjunb[wme]][d]=winjunb[wyou];
							aite[winjunb[wyou]][d]=winjunb[wme];
							taisensuu[winjunb[wme]]++;
							taisensuu[winjunb[wyou]]++;
							break;
						 }
				 	}
				}
				if (aite[winjunb[wme]][d]==-1){//
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+10 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-10 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-10
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
				 		}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+15 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-15 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-15
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
				 		}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						if (!(rikisidata[winjunid[wme]].bandukesuuji+20 >= rikisidata[winjunid[wyou]].bandukesuuji && rikisidata[winjunid[wme]].bandukesuuji-20 <= rikisidata[winjunid[wyou]].bandukesuuji)){
							dameflag=1;//番付の近い力士同士で対戦させるため+-20
						}
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
				 		}
					}
				}
				if (aite[winjunb[wme]][d]==-1){//同じカテゴリーの力士同士で対戦させるため+-20
					for (wyou=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;wyou<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;wyou++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						dameflag=0;
						for (i=0;i<15;i++){
							if (aite[winjunb[wme]][i]==winjunb[wyou]){
								dameflag=1;
								break;
							}
						}
						if (dameflag!=1){
							if (rikisidata[winjunid[wme]].heyaid!=rikisidata[winjunid[wyou]].heyaid
							 && kyuujouflag[winjunid[wyou]]!=1
							 && aite[winjunb[wyou]][d]==-1
							 && taisensuu[winjunb[wyou]]<7){
								aite[winjunb[wme]][d]=winjunb[wyou];
								aite[winjunb[wyou]][d]=winjunb[wme];
								taisensuu[winjunb[wme]]++;
								taisensuu[winjunb[wyou]]++;
								break;
							 }
				 		}
					}
				}
				if (aite[winjunb[wme]][d]==-1
				 && taisensuu[winjunb[wme]]<7
					&& kyuujouflag[winjunid[wme]]!=1){//さてどうしよう？？
					aite[winjunb[wme]][d]=999;//補欠と対戦させるということにしてみた
					taisensuu[winjunb[wme]]++;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode=1;
					return ;
				}
				Sleep(1);
			}
		}
	}
}
	
	//代入処理
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (aite[i][day-11]==999){
			rikisidata[bandukejunid[i]].aitekonbasho[day-11]=999;
		}else if (aite[i][day-11]!=-1){
			rikisidata[bandukejunid[i]].aitekonbasho[day-11]=bandukejunid[aite[i][day-11]];
		}else if (aite[i][day-11]==-1){
			rikisidata[bandukejunid[i]].aitekonbasho[day-11]=-1;
		}
	}
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//if (day-11==14){
	/*if (1){
		FILE *fp;
		fp = fopen("kyuujou.csv","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"%d日目\n",day-11+1);
		for (i=0;i<RIKISISUU;i++){
			fprintf(fp,"%d,%d\n",i,
			kyuujouflag[bandukejunid[i]]);
		}
		//クローズ
		fclose(fp);

		fp = fopen("torikumisakusei.csv","w");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"番付順ID,休場,初日,2日目,3日目,4日目,5日目,6日目,7日目,8日目,9日目,10日目,11日目,12日目,13日目,14日目,15日目\n");
		for (i=0;i<RIKISISUU;i++){
			fprintf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",i,kyuujouflag[bandukejunid[i]],
			rikisidata[bandukejunid[i]].aitekonbasho[0],
			rikisidata[bandukejunid[i]].aitekonbasho[1],
			rikisidata[bandukejunid[i]].aitekonbasho[2],
			rikisidata[bandukejunid[i]].aitekonbasho[3],
			rikisidata[bandukejunid[i]].aitekonbasho[4],
			rikisidata[bandukejunid[i]].aitekonbasho[5],
			rikisidata[bandukejunid[i]].aitekonbasho[6],
			rikisidata[bandukejunid[i]].aitekonbasho[7],
			rikisidata[bandukejunid[i]].aitekonbasho[8],
			rikisidata[bandukejunid[i]].aitekonbasho[9],
			rikisidata[bandukejunid[i]].aitekonbasho[10],
			rikisidata[bandukejunid[i]].aitekonbasho[11],
			rikisidata[bandukejunid[i]].aitekonbasho[12],
			rikisidata[bandukejunid[i]].aitekonbasho[13],
			rikisidata[bandukejunid[i]].aitekonbasho[14]);
		}
		//クローズ
		fclose(fp);
		fp = fopen("torikumisakusei2.txt","w");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		for (i=0;i<RIKISISUU;i++){
			count=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[winjunid[i]].winkonbasho[ii]==1){
					count++;
				}
			}
			fprintf(fp,"winjunid%3d winjunb%3d %2d勝\n",winjunid[i],winjunb[i],count);
		}
		//クローズ
		fclose(fp);
	}*/
	
	return;
}



void bandukesakusei_kyuujou(void)
{
	FILE *fp;
	int temp_shousin_yokoduna_winsuu=0;
	int motonojun=0;//付け出し力士を無理やり処理用
	int temp_karibanid=0;//付け出し力士を無理やり処理用
	int chouseizumi[RIKISISUU];//昇段力士・降段力士などの最後の調整用フラグ
	int sakijun,tempid,motojun;
	int win[RIKISISUU];
	int lost[RIKISISUU];
	int i;
	int ii;
	int iii;
	int iiii;
	int kouhoid=0;
	int count;
	int wincount=0;
	int yokodunacount=0;
	int oozekicount=0;
	int sekiwakecount=0;
	int shoukakurikisisuu=0;
	int nukeid[RIKISISUU];//番付が決まった順に並んだ力士IDの配列
	int nukekazu=0;//番付が決まった力士の数
	int dame=0;//次のポイント順IDに飛ばすフラグ、1で飛ばす
	int damejan=0;//同上
	int tempx=0;//並び替え用
	int temp[RIKISISUU];//並び替え用
	int karibandukepointjunid[RIKISISUU];//番付ポイント順に並んだ力士IDの配列
	int karibandukepoint[RIKISISUU];//力士ID順に並んだ番付ポイント(小さいほうがよい)の配列、[]内は力士IDが入る
	int karibandukejunid[RIKISISUU];//新しい番付順の力士のID番号、[]内は番付順、
	char tuikakijunpassflag=0;
//3.13で追加//
	int last_yokodunasuu=0;
	int last_oozekisuu=0;
	int last_sekiwakesuu=0;
	int last_bandukenameid[RIKISISUU];
	int last_bandukesuuji[RIKISISUU];
	int last_bandukehigasiornisi[RIKISISUU];
	int last_bandukejun[RIKISISUU];
	for (i=0;i<RIKISISUU;i++){
		last_bandukenameid[i]=0;
		last_bandukesuuji[i]=0;
		last_bandukehigasiornisi[i]=0;
		last_bandukejun[i]=0;
		last_bandukenameid[i]=rikisidata[i].bandukenameid;
		last_bandukesuuji[i]=rikisidata[i].bandukesuuji;
		last_bandukehigasiornisi[i]=rikisidata[i].bandukehigasiornisi;
		last_bandukejun[i]=rikisidata[i].bandukejun;
	}
	for (i=0;i<RIKISISUU;i++){
		if (rikisidata[i].bandukenameid==0){
			last_yokodunasuu++;
		}
		if (rikisidata[i].bandukenameid==1){
			last_oozekisuu++;
		}
		if (rikisidata[i].bandukenameid==2){
			last_sekiwakesuu++;
		}
	}
//ここまで追加分///

	for (i=0;i<RIKISISUU;i++){
		chouseizumi[i]=0;
		win[i]=0;
		lost[i]=0;
		karibandukepoint[i]=0;
		karibandukejunid[i]=0;
		nukeid[i]=0;
		karibandukepointjunid[i]=0;
	}
	for (i=0;i<RIKISISUU;i++){
		karibandukejunid[i]=-1;
		nukeid[i]=-1;
		karibandukepointjunid[i]=i;
	}

////////////////////////////debug 無理やり幕下の成績変更/////////////////////////////////////////////////////
//for (i=0;i<RIKISISUU;i++){
//	if (rikisidata[i].bandukenameid==6 && rikisidata[i].bandukesuuji<6){
//		for (ii=0;ii<15;ii++){
//			rikisidata[i].winkonbasho[ii]=0;
//			rikisidata[i].lostkonbasho[ii]=0;
//		}
//		for (ii=0;ii<7;ii++){
//			rikisidata[i].lostkonbasho[ii]=1;
//		}
//	}
//	if (rikisidata[i].bandukenameid==6 && rikisidata[i].bandukesuuji>5){
//		for (ii=0;ii<15;ii++){
//			rikisidata[i].winkonbasho[ii]=0;
//			rikisidata[i].lostkonbasho[ii]=0;
//		}
//		for (ii=0;ii<4;ii++){
//			rikisidata[i].winkonbasho[ii]=1;
//		}
//	}
//}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
////////////////////////////////////////////////////////////////////////////////////

	//勝ち負け拾う
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (ii=0;ii<15;ii++){
			if (rikisidata[i].winkonbasho[ii]==1){
				win[i]++;
			}else if (rikisidata[i].lostkonbasho[ii]==1){
				lost[i]++;
			}
		}
	}
	//休場分を負け数に加算
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (ii=0;ii<15;ii++){
			if (kyuujoukonbasho[i][ii]==1){
				if (rikisidata[i].bandukenameid<=5){
					if ( (win[i]+lost[i])<15 ){
						lost[i]++;
					}
				}else{
					if ( (win[i]+lost[i])<7 ){
						lost[i]++;
					}
				}
			}
		}
	}


if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	for (i=0;i<RIKISISUU;i++){//ポイント制の仮の番付を作る、[]内は力士ID
		//for (ii=0;ii<15;ii++){
		if (rikisidata[i].bandukejun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU){
			//karibandukepoint[i]=karibandukepoint[i]-win[i]*2+lost[i]*2;
			if (win[i]==15){
				karibandukepoint[i]=karibandukepoint[i]-29;
			}else if (win[i]==14){
				karibandukepoint[i]=karibandukepoint[i]-25;
			}else if (win[i]==13){
				karibandukepoint[i]=karibandukepoint[i]-21;
			}else if (win[i]==12){
				karibandukepoint[i]=karibandukepoint[i]-17;
			}else if (win[i]==11){
				karibandukepoint[i]=karibandukepoint[i]-13;
			}else if (win[i]==10){
				karibandukepoint[i]=karibandukepoint[i]-9;
			}else if (win[i]==9){
				karibandukepoint[i]=karibandukepoint[i]-5;
			}else if (win[i]==8){
				karibandukepoint[i]=karibandukepoint[i]-2;
			}else if (win[i]==7){
				karibandukepoint[i]=karibandukepoint[i]+2;
			}else if (win[i]==6){
				karibandukepoint[i]=karibandukepoint[i]+5;
			}else if (win[i]==5){
				karibandukepoint[i]=karibandukepoint[i]+9;
			}else if (win[i]==4){
				karibandukepoint[i]=karibandukepoint[i]+13;
			}else if (win[i]==3){
				karibandukepoint[i]=karibandukepoint[i]+17;
			}else if (win[i]==2){
				karibandukepoint[i]=karibandukepoint[i]+21;
			}else if (win[i]==1){
				karibandukepoint[i]=karibandukepoint[i]+24;
			}else{
				karibandukepoint[i]=karibandukepoint[i]+27;
			}


		}else if (rikisidata[i].bandukejun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA){
			if (win[i]==7){
				karibandukepoint[i]=karibandukepoint[i]-70;
			}else if (win[i]==6){
				karibandukepoint[i]=karibandukepoint[i]-60;
			}else if (win[i]==5){
				karibandukepoint[i]=karibandukepoint[i]-35;
			}else if (win[i]==4){
				karibandukepoint[i]=karibandukepoint[i]-20;
			}else if (win[i]==3){
				karibandukepoint[i]=karibandukepoint[i]+15;
			}else if (win[i]==2){
				karibandukepoint[i]=karibandukepoint[i]+25;
			}else if (win[i]==1){
				karibandukepoint[i]=karibandukepoint[i]+50;
			}else{
				karibandukepoint[i]=karibandukepoint[i]+70;
			}
		}else if (rikisidata[i].bandukejun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME){
			if (win[i]==7){
				karibandukepoint[i]=karibandukepoint[i]-100;
			}else if (win[i]==6){
				karibandukepoint[i]=karibandukepoint[i]-85;
			}else if (win[i]==5){
				karibandukepoint[i]=karibandukepoint[i]-55;
			}else if (win[i]==4){
				karibandukepoint[i]=karibandukepoint[i]-34;
			}else if (win[i]==3){
				karibandukepoint[i]=karibandukepoint[i]+21;
			}else if (win[i]==2){
				karibandukepoint[i]=karibandukepoint[i]+35;
			}else if (win[i]==1){
				karibandukepoint[i]=karibandukepoint[i]+70;
			}else{
				karibandukepoint[i]=karibandukepoint[i]+100;
			}
		}else{
			if (win[i]==7){
				karibandukepoint[i]=karibandukepoint[i]-140;
			}else if (win[i]==6){
				karibandukepoint[i]=karibandukepoint[i]-120;
			}else if (win[i]==5){
				karibandukepoint[i]=karibandukepoint[i]-80;
			}else if (win[i]==4){
				karibandukepoint[i]=karibandukepoint[i]-40;
			}else if (win[i]==3){
				karibandukepoint[i]=karibandukepoint[i]+24;
			}else if (win[i]==2){
				karibandukepoint[i]=karibandukepoint[i]+41;
			}else if (win[i]==1){
				karibandukepoint[i]=karibandukepoint[i]+85;
			}else{
				karibandukepoint[i]=karibandukepoint[i]+120;
			}
		}
		//}
		karibandukepoint[i]=karibandukepoint[i]+rikisidata[i].bandukejun;
		if (rikisidata[i].retirekonbasho==1){
			karibandukepoint[i]=999999;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//ポイント順の力士IDを検索(バブルソートも使用した)
	for (i=0;i<RIKISISUU;i++){
		temp[i]=0;
	}
	for (i=0;i<RIKISISUU;i++){
		temp[i]=karibandukepoint[i];
	}
	for (ii = 0;ii < RIKISISUU - 1;ii++) {
		for (i = 0;i < RIKISISUU - 1;i++) {
			if (temp[i + 1] < temp[i]) {
				tempx = temp[i];
				temp[i] = temp[i + 1];
				temp[i + 1] = tempx;
				tempx=karibandukepointjunid[i];
				karibandukepointjunid[i]=karibandukepointjunid[i+1];
				karibandukepointjunid[i+1]=tempx;
			}else if (temp[i + 1]==temp[i] && rikisidata[karibandukepointjunid[i+1]].bandukejun<rikisidata[karibandukepointjunid[i]].bandukejun) {
				tempx = temp[i];
				temp[i] = temp[i + 1];
				temp[i + 1] = tempx;
				tempx=karibandukepointjunid[i];
				karibandukepointjunid[i]=karibandukepointjunid[i+1];
				karibandukepointjunid[i+1]=tempx;
			}
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける


//////以下横綱から順に処理
	for (i=0;i<RIKISISUU;i++){//まず、現横綱を確定
		if (rikisidata[karibandukepointjunid[i]].bandukenameid==0 && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1){//引退してなければ
			karibandukejunid[nukekazu]=karibandukepointjunid[i];
			nukeid[nukekazu]=karibandukepointjunid[i];
			rikisidata[karibandukejunid[nukekazu]].bandukenameid=0;//横綱
			rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
			if ((nukekazu+2)%2==0){
				rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
			}else{
				rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
			}
			yokodunacount++;
			nukekazu++;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

for (i=0;i<RIKISISUU_MAKUUTI;i++){//横綱昇進できるのがいるか、いたら昇進させる
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	dame=0;
	for (ii=0;ii<nukekazu;ii++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (karibandukepointjunid[i]==nukeid[ii]){
			dame=1;
			break;
		}
	}
	if (dame!=1){
		wincount=0;
		for (ii=0;ii<15;ii++){
			if (rikisidata[karibandukepointjunid[i]].winkonbasho[ii]==1){
				wincount++;
			}
		}
		if (wincount>=shousin_yokoduna_konbashowinsuu){
			temp_shousin_yokoduna_winsuu=0;
			temp_shousin_yokoduna_winsuu=wincount;
			for (ii=1;ii<shousin_yokoduna_bashosuu;ii++){
				temp_shousin_yokoduna_winsuu+=rikisidata[karibandukepointjunid[i]].kako_win[ii];
			}
/*
ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
DrawString(187,369,"Dubug",CRWHITE);
DrawFormatString(187,385,CRWHITE,"%s部屋の%sが",heyastring[rikisidata[karibandukepointjunid[i]].heyaid],namestring[karibandukepointjunid[i]]);
DrawFormatString(187,417,CRWHITE,"過去３場所で%d勝",temp_shousin_yokoduna_winsuu);
DrawFormatString(187,417+32,CRWHITE,"条件は過去３場所で%d勝",shousin_yokoduna_winsuu);
ScreenFlip() ;//裏画面を表画面にコピー
WaitKey();
*/
			tuikakijunpassflag=0;
			if (shousin_yokoduna_kijun2==0){//先々場所不問
				tuikakijunpassflag=1;
			//先々場所優勝
			}else if (shousin_yokoduna_kijun2==1){
				if (rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[2]==1){
					tuikakijunpassflag=1;
				}
			//先々場所準優勝以上
			}else{
				if (rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[2]==1 || rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[2]==2){
					tuikakijunpassflag=1;
				}
			}
			if (tuikakijunpassflag==1){
				if (temp_shousin_yokoduna_winsuu>=shousin_yokoduna_winsuu){
					if (shousin_yokoduna_kijun==0){//普通
						if ((rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[1]==1 && rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[0]==1 && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1) || (rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[1]==1 && rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[0]==2 && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1) || (rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[1]==2 && rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[0]==1 && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1)){
							karibandukejunid[nukekazu]=karibandukepointjunid[i];
							nukeid[nukekazu]=karibandukepointjunid[i];
							rikisidata[karibandukejunid[nukekazu]].bandukenameid=0;//横綱
							rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
							if ((nukekazu+2)%2==0){
								rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
							}else{
								rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
							}
							yokodunacount++;
							nukekazu++;
							rekidai_yokodunasuu++;
							yokoduna_tanjou(karibandukejunid[nukekazu-1]);
						}
					}else if(shousin_yokoduna_kijun==1){//厳しい
						if (rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[1]==1 && rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[0]==1 && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1){
							karibandukejunid[nukekazu]=karibandukepointjunid[i];
							nukeid[nukekazu]=karibandukepointjunid[i];
							rikisidata[karibandukejunid[nukekazu]].bandukenameid=0;//横綱
							rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
							if ((nukekazu+2)%2==0){
								rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
							}else{
								rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
							}
							yokodunacount++;
							nukekazu++;
							rekidai_yokodunasuu++;
							yokoduna_tanjou(karibandukejunid[nukekazu-1]);
						}
					}else{//甘い
						if (rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[1]>=1 && rikisidata[karibandukepointjunid[i]].oozekiyuushouorjunyuushou[0]>=1 && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1){
							karibandukejunid[nukekazu]=karibandukepointjunid[i];
							nukeid[nukekazu]=karibandukepointjunid[i];
							rikisidata[karibandukejunid[nukekazu]].bandukenameid=0;//横綱
							rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
							if ((nukekazu+2)%2==0){
								rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
							}else{
								rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
							}
							yokodunacount++;
							nukekazu++;
							rekidai_yokodunasuu++;
							yokoduna_tanjou(karibandukejunid[nukekazu-1]);
						}
					}
				}
			}
		}
	}
}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//現大関で勝ち越し(デフォルトでは)た力士
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		wincount=0;
		for (ii=0;ii<15;ii++){
			if (rikisidata[karibandukepointjunid[i]].winkonbasho[ii]==1){
				wincount++;
			}
		}
		if (rikisidata[karibandukepointjunid[i]].bandukenameid==1 && wincount>=iji_oozeki_winsuu && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1){
			dame=0;
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
					break;
				}
			}
			if (dame!=1){
				karibandukejunid[nukekazu]=karibandukepointjunid[i];
				nukeid[nukekazu]=karibandukepointjunid[i];
				rikisidata[karibandukejunid[nukekazu]].bandukenameid=1;//大関
				rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
				rikisidata[karibandukejunid[nukekazu]].kadobanflag=0;//ver2.39まで欠落していた
				if ((oozekicount+2)%2==0){
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
				}else{
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
				}
				nukekazu++;
				oozekicount++;
			}
			dame=0;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//関脇に落ちたけど一場所で大関返り咲く力士の処理
	for (i=0;i<RIKISISUU;i++){
		if (rikisidata[karibandukepointjunid[i]].bandukenameid==2 && rikisidata[karibandukepointjunid[i]].kadobankaraotitaflag==1 && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1){
			rikisidata[karibandukepointjunid[i]].kadobankaraotitaflag=0;
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[karibandukepointjunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			dame=0;
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
					break;
				}
			}
			if (dame!=1){
				if (wincount>=shousin_oozeki_kanrakuchokugowinsuu){
					karibandukejunid[nukekazu]=karibandukepointjunid[i];
					nukeid[nukekazu]=karibandukepointjunid[i];
					if (kaerizakisuu<RIKISISUU){
						kaerizakirikisikonbasho[kaerizakisuu]=karibandukejunid[nukekazu];
					}
					kaerizakisuu++;
					rikisidata[karibandukejunid[nukekazu]].bandukenameid=1;//大関
					rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
					rikisidata[karibandukejunid[nukekazu]].kadobanflag=0;//ver2.39まで欠落していた
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					game_main_backscreen();
					DrawString(187,369,"一場所で大関に返り咲きました。",CRWHITE);
					DrawFormatString(187,385,CRWHITE,"%s部屋で%s出身の",heyastring[rikisidata[karibandukejunid[nukekazu]].heyaid],hometownstring[rikisidata[karibandukejunid[nukekazu]].hometownid]);
					DrawFormatString(187,401,CRWHITE,"%sが",namestring[rikisidata[karibandukejunid[nukekazu]].nameid]);
					DrawFormatString(187,417,CRWHITE,"%d勝以上あげたため",shousin_oozeki_kanrakuchokugowinsuu);
					DrawString(187,417+16,"大関に返り咲くことが決定しました！",CRWHITE);
					ScreenFlip() ;//裏画面を表画面にコピー
					if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
						// キー入力待ち(この一文を入れないとうまくいかないみたい)
						while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
							buttonG_mouse_change();
							Sleep(1);
						}
						while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						buttonG_mouse_change();
						Sleep(1);
						}
						while(1)
						{
							if (get_mouseclick_buttonG() == 1){//メニューボタンGをクリックでループから抜け次へ進む
								break;
							}
							if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜けメニュー画面へ
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
					}	
					if ((oozekicount+2)%2==0){
						rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
					}else{
						rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
					}
					nukekazu++;
					oozekicount++;
				}
			}
			dame=0;
			wincount=0;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//大関昇進できるのがいるか、いたら昇進させる処理
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		if (win[karibandukepointjunid[i]]>=shousin_oozeki_konbashowinsuu[0] && rikisidata[karibandukepointjunid[i]].sanyakuwin[0]+rikisidata[karibandukepointjunid[i]].sanyakuwin[1]+rikisidata[karibandukepointjunid[i]].sanyakuwin[2] >= shousin_oozeki_sanyakuwintotal[0] && oozekicount<=shousin_oozeki_genoozekisuu[0] && GetRand(99)<shousin_oozeki_kakuritu[0] && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1){
			dame=0;
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
					break;
				}
			}
			if (dame!=1){
				karibandukejunid[nukekazu]=karibandukepointjunid[i];
				nukeid[nukekazu]=karibandukepointjunid[i];
				rikisidata[karibandukejunid[nukekazu]].bandukenameid=1;//大関
				rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
				rikisidata[karibandukejunid[nukekazu]].kadobanflag=0;//ver2.40で追加
				oozeki_tanjou(karibandukejunid[nukekazu]);
				if ((oozekicount+2)%2==0){
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
				}else{
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
				}
				nukekazu++;
				oozekicount++;
			}
			dame=0;
		}else if (win[karibandukepointjunid[i]]>=shousin_oozeki_konbashowinsuu[1] && (rikisidata[karibandukepointjunid[i]].sanyakuwin[0]+rikisidata[karibandukepointjunid[i]].sanyakuwin[1]+rikisidata[karibandukepointjunid[i]].sanyakuwin[2] >= shousin_oozeki_sanyakuwintotal[1]) && oozekicount<=shousin_oozeki_genoozekisuu[1] && GetRand(99)<shousin_oozeki_kakuritu[1] && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1){
			dame=0;
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
					break;
				}
			}
			if (dame!=1){
				karibandukejunid[nukekazu]=karibandukepointjunid[i];
				nukeid[nukekazu]=karibandukepointjunid[i];
				rikisidata[karibandukejunid[nukekazu]].bandukenameid=1;//大関
				rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
				rikisidata[karibandukejunid[nukekazu]].kadobanflag=0;//ver2.40で追加
				oozeki_tanjou(karibandukejunid[nukekazu]);
				if ((oozekicount+2)%2==0){
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
				}else{
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
				}
				nukekazu++;
				oozekicount++;
			}
			dame=0;
		}else if (win[karibandukepointjunid[i]]>=shousin_oozeki_konbashowinsuu[2] && (rikisidata[karibandukepointjunid[i]].sanyakuwin[0]+rikisidata[karibandukepointjunid[i]].sanyakuwin[1]+rikisidata[karibandukepointjunid[i]].sanyakuwin[2] >= shousin_oozeki_sanyakuwintotal[2]) && oozekicount<=shousin_oozeki_genoozekisuu[2] && GetRand(99)<shousin_oozeki_kakuritu[2] && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1){
			dame=0;
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
					break;
				}
			}
			if (dame!=1){
				karibandukejunid[nukekazu]=karibandukepointjunid[i];
				nukeid[nukekazu]=karibandukepointjunid[i];
				rikisidata[karibandukejunid[nukekazu]].bandukenameid=1;//大関
				rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
				rikisidata[karibandukejunid[nukekazu]].kadobanflag=0;//ver2.40で追加
				oozeki_tanjou(karibandukejunid[nukekazu]);
				if ((oozekicount+2)%2==0){
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
				}else{
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
				}
				nukekazu++;
				oozekicount++;
			}
			dame=0;
		}else if (win[karibandukepointjunid[i]]>=shousin_oozeki_konbashowinsuu[3] && (rikisidata[karibandukepointjunid[i]].sanyakuwin[0]+rikisidata[karibandukepointjunid[i]].sanyakuwin[1]+rikisidata[karibandukepointjunid[i]].sanyakuwin[2] >= shousin_oozeki_sanyakuwintotal[3]) && oozekicount<=shousin_oozeki_genoozekisuu[3] && GetRand(99)<shousin_oozeki_kakuritu[3] && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1){
			dame=0;
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
					break;
				}
			}
			if (dame!=1){
				karibandukejunid[nukekazu]=karibandukepointjunid[i];
				nukeid[nukekazu]=karibandukepointjunid[i];
				rikisidata[karibandukejunid[nukekazu]].bandukenameid=1;//大関
				rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
				rikisidata[karibandukejunid[nukekazu]].kadobanflag=0;//ver2.40で追加
				oozeki_tanjou(karibandukejunid[nukekazu]);
				if ((oozekicount+2)%2==0){
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
				}else{
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
				}
				nukekazu++;
				oozekicount++;
			}
			dame=0;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//角番大関になる力士の処理
	for (i=0;i<RIKISISUU;i++){
		wincount=0;
		for (ii=0;ii<15;ii++){
			if (rikisidata[karibandukepointjunid[i]].winkonbasho[ii]==1){
				wincount++;
			}
		}
		if (rikisidata[karibandukepointjunid[i]].bandukenameid==1 && wincount<=kanraku_kadoban_konbashowinsuu && rikisidata[karibandukepointjunid[i]].kadobanflag==0 && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1){
			dame=0;//ver2.41で追加（これが抜けてたのが角番経由しないで関脇に落ちる場合があった原因）
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
					break;
				}
			}
			if (dame!=1){
				karibandukejunid[nukekazu]=karibandukepointjunid[i];
				nukeid[nukekazu]=karibandukepointjunid[i];
				rikisidata[karibandukejunid[nukekazu]].bandukenameid=1;//大関
				rikisidata[karibandukejunid[nukekazu]].kadobanflag=1;//だけど角番
				rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
				if ((oozekicount+2)%2==0){
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
				}else{
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
				}
				nukekazu++;
				oozekicount++;
			}
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	ClearDrawScreen();
	game_main_backscreen();
	DrawString(187,369,"お待ちください。",CRWHITE);
	ScreenFlip();

	//東と西の調整
	if (oozekicount!=0){
		if ((yokodunacount+2)%2==1){//横綱の数が奇数なら、大関の末席は西方なので
			rikisidata[karibandukejunid[nukekazu-1]].bandukehigasiornisi=2;//西
		}
	}
	//現関脇で勝ち越した力士の処理
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		if (rikisidata[karibandukepointjunid[i]].bandukenameid==2 && rikisidata[karibandukepointjunid[i]].bandukejun>karibandukepoint[karibandukepointjunid[i]] && rikisidata[karibandukepointjunid[i]].retirekonbasho!=1){
			dame=0;
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
					break;
				}
			}
			if (dame!=1){
				karibandukejunid[nukekazu]=karibandukepointjunid[i];
				nukeid[nukekazu]=karibandukepointjunid[i];
				if (rikisidata[karibandukejunid[nukekazu]].bandukenameid==1){//ver2.40で念のため追加
					rikisidata[karibandukepointjunid[i]].kadobankaraotitaflag=1;
				}else{
					rikisidata[karibandukepointjunid[i]].kadobankaraotitaflag=0;
				}
				rikisidata[karibandukejunid[nukekazu]].bandukenameid=2;//関脇
				rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
				if ((sekiwakecount+2)%2==0){
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
				}else{
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
				}
				nukekazu++;
				sekiwakecount++;
			}
			dame=0;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//もし、関脇が2人未満なら小結で勝ち越した力士がいれば関脇にする処理
	for (i=0;i<RIKISISUU_MAKUUTI;i++){//ポイント順
		if (sekiwakecount>1){
			break;
		}
		//すでに番付決定済みだったらパスする処理
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (karibandukepointjunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		//引退分カット
		if (rikisidata[karibandukepointjunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1 && rikisidata[karibandukepointjunid[i]].bandukenameid==3 
		&& rikisidata[karibandukepointjunid[i]].bandukejun>karibandukepoint[karibandukepointjunid[i]]){
			karibandukejunid[nukekazu]=karibandukepointjunid[i];
			nukeid[nukekazu]=karibandukepointjunid[i];
			if (rikisidata[karibandukejunid[nukekazu]].bandukenameid==1){//ver2.40で念のため追加
				rikisidata[karibandukepointjunid[i]].kadobankaraotitaflag=1;
			}else{
				rikisidata[karibandukepointjunid[i]].kadobankaraotitaflag=0;
			}
			rikisidata[karibandukejunid[nukekazu]].bandukenameid=2;//関脇
			rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
			rikisidata[karibandukejunid[nukekazu]].kadobanflag=0;
			if ((sekiwakecount+2)%2==0){
				rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
			}else{
				rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
			}
			nukekazu++;
			sekiwakecount++;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//もし、まだ関脇が2人未満ならポイント順で関脇にする力士の検索
	for (i=0;sekiwakecount<2;i++){//ポイント順に処理
		//すでに番付決定済みだったらパスする処理
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (karibandukepointjunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		//引退分カット
		if (rikisidata[karibandukepointjunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1 && rikisidata[karibandukepointjunid[i]].bandukejun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU){
			karibandukejunid[nukekazu]=karibandukepointjunid[i];
			nukeid[nukekazu]=karibandukepointjunid[i];
			if (rikisidata[karibandukejunid[nukekazu]].bandukenameid==1){//ver2.40で念のため追加
				rikisidata[karibandukepointjunid[i]].kadobankaraotitaflag=1;
			}else{
				rikisidata[karibandukepointjunid[i]].kadobankaraotitaflag=0;
			}
			rikisidata[karibandukejunid[nukekazu]].bandukenameid=2;//関脇
			rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
			rikisidata[karibandukejunid[nukekazu]].kadobanflag=0;
			if ((sekiwakecount+2)%2==0){
				rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
			}else{
				rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
			}
			nukekazu++;
			sekiwakecount++;
		}
	}
	
	//角番から関脇に落ちた力士の処理(ver2.36からは角番を経由せずに落ちる力士も想定)
	for (i=0;i<RIKISISUU;i++){
		//ver2.36での変更
		//if (rikisidata[karibandukepointjunid[i]].bandukenameid==1 && rikisidata[karibandukepointjunid[i]].bandukejun<karibandukepoint[karibandukepointjunid[i]] && rikisidata[karibandukepointjunid[i]].kadobanflag==1){
		if (rikisidata[karibandukepointjunid[i]].bandukenameid==1){
			dame=0;
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
				}
			}
			if (rikisidata[karibandukepointjunid[i]].retirekonbasho==1){
				dame=1;
			}
			if (dame!=1){
				rikisidata[karibandukepointjunid[i]].kadobanflag=0;
				karibandukejunid[nukekazu]=karibandukepointjunid[i];
				nukeid[nukekazu]=karibandukepointjunid[i];
				rikisidata[karibandukejunid[nukekazu]].bandukenameid=2;//関脇
				rikisidata[karibandukepointjunid[i]].kadobankaraotitaflag=1;//だけど返り咲きあるかもよ
				rikisidata[karibandukejunid[nukekazu]].bandukesuuji=0;
				if ((sekiwakecount+2)%2==0){
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=1;//東
				}else{
					rikisidata[karibandukejunid[nukekazu]].bandukehigasiornisi=2;//西
				}
				nukekazu++;
				sekiwakecount++;
			}
			dame=0;
		}
	}
	
	//東と西の調整
	if ((yokodunacount+oozekicount+2)%2==1){//横綱と大関を足したの数が奇数なら、関脇の末席は西方なので
		rikisidata[karibandukejunid[nukekazu-1]].bandukehigasiornisi=2;//西
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

//////前場所十両以上だった力士だけで小結以下の幕内と十両の番付を仮に作成
	//十両下位で負け越しとかはこの後入れ替え
	for (i=0;nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){//ポイント順に処理
		//勝ち越し力士を降格させないようにする処理
		if (nukekazu==yokodunacount+oozekicount+sekiwakecount){//東小結を決める時
			kouhoid=-101;
			for (iiii=0;iiii<RIKISISUU;iiii++){
				if (rikisidata[iiii].bandukenameid==3 
				&& rikisidata[iiii].bandukehigasiornisi==1 
				&& win[iiii]>lost[iiii]){
					kouhoid=iiii;
					break;
				}
			}
			if (kouhoid==-101){
				dame=1;
			}else{
				dame=0;
				for (ii=0;ii<nukekazu;ii++){
					if (kouhoid==nukeid[ii]){
						dame=1;
						break;
					}
				}
			}
			if (rikisidata[kouhoid].retirekonbasho==1){
				dame=1;
			}
			if (dame!=1){
				karibandukejunid[nukekazu]=kouhoid;
				nukeid[nukekazu]=kouhoid;
				nukekazu++;
			}
		}
		if (nukekazu==yokodunacount+oozekicount+sekiwakecount+1){//西小結を決める時
			kouhoid=-101;
			for (iiii=0;iiii<RIKISISUU;iiii++){
				if (rikisidata[iiii].bandukenameid==3 
				&& rikisidata[iiii].bandukehigasiornisi==2 
				&& win[iiii]>lost[iiii]){
					kouhoid=iiii;
					break;
				}
			}
			if (kouhoid==-101){
				dame=1;
			}else{
				dame=0;
				for (ii=0;ii<nukekazu;ii++){
					if (kouhoid==nukeid[ii]){
						dame=1;
						break;
					}
				}
			}
			if (rikisidata[kouhoid].retirekonbasho==1){
				dame=1;
			}
			if (dame!=1){
				karibandukejunid[nukekazu]=kouhoid;
				nukeid[nukekazu]=kouhoid;
				nukekazu++;
			}
		}
		if (nukekazu>=yokodunacount+oozekicount+sekiwakecount+2 && nukekazu<RIKISISUU_MAKUUTI){//前頭を決める時
			for (iii=nukekazu-(yokodunacount+oozekicount+sekiwakecount); nukekazu < RIKISISUU_MAKUUTI; iii++){
				kouhoid=-101;
				for (iiii=0;iiii<RIKISISUU;iiii++){
					if (rikisidata[iiii].bandukenameid==4 
					&& rikisidata[iiii].bandukesuuji==(int)(iii/2) 
					&& rikisidata[iiii].bandukehigasiornisi==iii%2+1 
					&& win[iiii]>lost[iiii]){
						kouhoid=iiii;
						break;
					}
				}
				if (kouhoid==-101){
					dame=1;
				}else{
					dame=0;
					for (ii=0;ii<nukekazu;ii++){
						if (kouhoid==nukeid[ii]){
							dame=1;
							break;
						}
					}
				}
				if (rikisidata[kouhoid].retirekonbasho==1){
					dame=1;
				}
				if (dame!=1){
					karibandukejunid[nukekazu]=kouhoid;
					nukeid[nukekazu]=kouhoid;
					nukekazu++;
				}else{
					break;//通常処理へ
				}
			}
		}
		if (nukekazu>=RIKISISUU_MAKUUTI && nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU){//十両を決める時
			for (iii=nukekazu-RIKISISUU_MAKUUTI+2; nukekazu < RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU; iii++){
				kouhoid=-101;
				for (iiii=0;iiii<RIKISISUU;iiii++){
					if (rikisidata[iiii].bandukenameid==5 
					&& rikisidata[iiii].bandukesuuji==(int)(iii/2) 
					&& rikisidata[iiii].bandukehigasiornisi==iii%2+1 
					&& win[iiii]>lost[iiii]){
						kouhoid=iiii;
						break;
					}
				}
				if (kouhoid==-101){
					dame=1;
				}else{
					dame=0;
					for (ii=0;ii<nukekazu;ii++){
						if (kouhoid==nukeid[ii]){
							dame=1;
							break;
						}
					}
				}
				if (rikisidata[kouhoid].retirekonbasho==1){
					dame=1;
				}
				if (dame!=1){
					karibandukejunid[nukekazu]=kouhoid;
					nukeid[nukekazu]=kouhoid;
					nukekazu++;
				}else{
					break;//通常処理へ
				}
			}
		}
		//通常処理
		if (rikisidata[karibandukepointjunid[i]].bandukejun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU){//前の場所十両以上
			dame=0;
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
					break;
				}
			}
			if (dame!=1){
				karibandukejunid[nukekazu]=karibandukepointjunid[i];
				nukeid[nukekazu]=karibandukepointjunid[i];
				nukekazu++;
			}
		}
	}

/////////////////debug
/*
		FILE *fp;
		fp = fopen("debug_nukekazu.csv","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"%3d年 %2d月  nukekazuは%3d\n",year,month,nukekazu);
		fclose(fp);
*/
//////////////////////

	//十両から幕下へ陥落させるべき力士を検索し、その分をリセット
	for (i=nukekazu-1;i>-1;i--){
		if (karibandukepoint[karibandukejunid[i]]>=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU){
			karibandukejunid[i]=-1;
			nukeid[i]=-1;
			nukekazu--;
		}else{
			break;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

/////////////////debug
/*
		fp = fopen("debug_nukekazu2.csv","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"%3d年 %2d月  nukekazuは%3d\n",year,month,nukekazu);
		fclose(fp);
*/
//////////////////////

	//幕下から十両へ上げる力士の決定
	//優先順位１、東幕下筆頭勝ち越し
	if (karibandukepoint[bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU]]<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU && nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU && rikisidata[bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU]].retirekonbasho!=1){
		karibandukejunid[nukekazu]=bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU];
		nukeid[nukekazu]=bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU];
		nukekazu++;
/////////////////debug/////////////////////////////////////////////////////
/*
		fp = fopen("debug_nukename_east1.csv","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"%d,%d,%s\n",year,month,namestring[bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU]]);
		fclose(fp);
*/
////////////////////////////////////////////////////////////////////////////
	}
	//順位2、幕下１５枚目以内で７戦全勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+15*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==7){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
/////////////////debug/////////////////////////////////////////////////////
/*
		fp = fopen("debug_nukename_7win15.csv","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"%d,%d,%s\n",year,month,namestring[bandukejunid[i]]);
		fclose(fp);
*/
////////////////////////////////////////////////////////////////////////////
			}
		}
	}
	//順位3、西幕下筆頭勝ち越し
	if (karibandukepoint[bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1]]<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1 && nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU){
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			karibandukejunid[nukekazu]=bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1];
			nukeid[nukekazu]=bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1];
			nukekazu++;
/////////////////debug/////////////////////////////////////////////////////
/*
		fp = fopen("debug_nukename_west1.csv","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"%d,%d,%s\n",year,month,namestring[bandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1]]);
		fclose(fp);
*/
////////////////////////////////////////////////////////////////////////////
		}
	}
	//順位3、5枚目以内でpoint順で上がるべき力士
	count=0;
	for (i=0;nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		count++;
		if (count>RIKISISUU) break;
		//すでに番付決定済みだったらパスする処理
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (karibandukepointjunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[karibandukepointjunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (rikisidata[karibandukepointjunid[i]].bandukenameid<=5){//陥落力士は除く処理
			dame=1;
		}
		if (!(rikisidata[karibandukepointjunid[i]].bandukejun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+5*2)){//5枚目以内に限る処理
			dame=1;
		}
		if (win[karibandukepointjunid[i]]<=3){//負け越し力士は除く処理
			dame=1;
		}
		//
		if (dame!=1){
			karibandukejunid[nukekazu]=karibandukepointjunid[i];
			nukeid[nukekazu]=karibandukepointjunid[i];
			nukekazu++;
/////////////////debug/////////////////////////////////////////////////////
/*
		fp = fopen("debug_nukename_point5.csv","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"%d,%d,%d,%d,%s\n",year,month,i,count,namestring[karibandukepointjunid[i]]);
		fclose(fp);

		if (count>100){
			ClearDrawScreen();
			DrawString(100,300,"キターーーーーーーーーーー！",GetColor(255,0,0));
			DrawString(100,350,"Hit any key",GetColor(255,0,0));
			ScreenFlip();
			WaitKey();
		}
*/
////////////////////////////////////////////////////////////////////////////
		}
	}
	//順位4、10枚目以内でpoint順で上がるべき力士
	count=0;
	for (i=0;nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		count++;
		if (count>RIKISISUU) break;
		//すでに番付決定済みだったらパスする処理
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (karibandukepointjunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[karibandukepointjunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (rikisidata[karibandukepointjunid[i]].bandukenameid<=5){//陥落力士は除く処理
			dame=1;
		}
		if (!(rikisidata[karibandukepointjunid[i]].bandukejun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+10*2)){//10枚目以内に限る処理
			dame=1;
		}
		if (win[karibandukepointjunid[i]]<=3){//負け越し力士は除く処理
			dame=1;
		}
		//
		if (dame!=1){
			karibandukejunid[nukekazu]=karibandukepointjunid[i];
			nukeid[nukekazu]=karibandukepointjunid[i];
			nukekazu++;
/////////////////debug/////////////////////////////////////////////////////
/*
		fp = fopen("debug_nukename_point10.csv","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"%d,%d,%d,%d,%s\n",year,month,i,count,namestring[karibandukepointjunid[i]]);
		fclose(fp);
*/
////////////////////////////////////////////////////////////////////////////
		}
	}
	//順位5、15枚目以内でpoint順で上がるべき力士
	count=0;
	for (i=0;nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		count++;
		if (count>RIKISISUU) break;
		//すでに番付決定済みだったらパスする処理
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (karibandukepointjunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[karibandukepointjunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (rikisidata[karibandukepointjunid[i]].bandukenameid<=5){//陥落力士は除く処理
			dame=1;
		}
		if (!(rikisidata[karibandukepointjunid[i]].bandukejun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+15*2)){//15枚目以内に限る処理
			dame=1;
		}
		if (win[karibandukepointjunid[i]]<=3){//負け越し力士は除く処理
			dame=1;
		}
		//
		if (dame!=1){
			karibandukejunid[nukekazu]=karibandukepointjunid[i];
			nukeid[nukekazu]=karibandukepointjunid[i];
			nukekazu++;
/////////////////debug/////////////////////////////////////////////////////
/*
		fp = fopen("debug_nukename_point15.csv","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"%d,%d,%d,%d,%s\n",year,month,i,count,namestring[karibandukepointjunid[i]]);
		fclose(fp);
*/
////////////////////////////////////////////////////////////////////////////
		}
	}
	//順位6、point順で上がるべき力士(陥落すべきとされた力士が復活する場合もありうる)
	for (i=0;nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		//すでに番付決定済みだったらパスする処理
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (karibandukepointjunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[karibandukepointjunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (rikisidata[karibandukepointjunid[i]].bandukenameid>6){
			dame=1;
		}
		//
		if (dame!=1){
			karibandukejunid[nukekazu]=karibandukepointjunid[i];
			nukeid[nukekazu]=karibandukepointjunid[i];
			nukekazu++;
/////////////////debug/////////////////////////////////////////////////////
/*
		fp = fopen("debug_nukename_pointonly.csv","a");
		// オープンできなかったらここで終了
		if( fp == NULL ){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
			DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			mode=1 ;		// ＤＸライブラリ使用の終了処理
			return  ;		// ソフトの終了
		}
		fprintf(fp,"%d,%d,%d,%s\n",year,month,i,namestring[karibandukepointjunid[i]]);
		fclose(fp);
*/
////////////////////////////////////////////////////////////////////////////
		}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける


//////幕下以上だった力士だけで幕下の番付を仮に作成
	//幕下と三段目の入れ替えはこの後処理
	for (i=0;nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){//ポイント順に処理
		//勝ち越し力士を降格させないようにする処理
		if (nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA){//幕下を決める時
			for (iii=nukekazu-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU)+2; nukekazu < RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA; iii++){
				kouhoid=-101;
				for (iiii=0;iiii<RIKISISUU;iiii++){
					if (rikisidata[iiii].bandukenameid==6 
					&& rikisidata[iiii].bandukesuuji==(int)(iii/2) 
					&& rikisidata[iiii].bandukehigasiornisi==iii%2+1 
					&& win[iiii]>lost[iiii]){
						kouhoid=iiii;
						break;
					}
				}
				if (kouhoid==-101){
					dame=1;
				}else{
					dame=0;
					for (ii=0;ii<nukekazu;ii++){
						if (kouhoid==nukeid[ii]){
							dame=1;
							break;
						}
					}
				}
				if (rikisidata[kouhoid].retirekonbasho==1){
					dame=1;
				}
				if (dame!=1){
					karibandukejunid[nukekazu]=kouhoid;
					nukeid[nukekazu]=kouhoid;
					nukekazu++;
				}else{
					break;//通常処理へ
				}
			}
		}
		//通常処理
		if (rikisidata[karibandukepointjunid[i]].bandukejun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA){//前の場所幕下以上
			//すでに番付決定済みだったらパスする処理
			dame=0;
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
					break;
				}
			}
			//
			if (dame!=1){
				karibandukejunid[nukekazu]=karibandukepointjunid[i];
				nukeid[nukekazu]=karibandukepointjunid[i];
				nukekazu++;
			}
		}
	}

	//幕下から陥落させるべき力士を検索し、その分をリセット
	for (i=nukekazu-1;i>-1;i--){
		if (karibandukepoint[karibandukejunid[i]]>=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA){
			karibandukejunid[i]=-1;
			nukeid[i]=-1;
			nukekazu--;
		}else{
			break;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//三段目から幕下へ上げる力士の決定
	//順位1、７戦全勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==7
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位2、筆頭で勝ち越し
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+1*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount>=4
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
/*	//順位3、20枚目以内で6勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+20*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==6
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位4、10枚目以内で5勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+10*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==5
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位5、5枚目以内で4勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+5*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==4
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位6、40枚目以内で6勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+40*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==6
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位7、11枚目から20枚目以内で5勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+10*2;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+20*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==5
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位8、10枚目以内で4勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+10*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==4
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}*/
	//順位3、point順で上がるべき力士(陥落すべきとされた力士が復活する場合もありうる)
	//引退力士分で得する力士っちゅうこと
	for (i=0;nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		//すでに番付決定済みだったらパスする処理
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (karibandukepointjunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[karibandukepointjunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (rikisidata[karibandukepointjunid[i]].bandukenameid>7){
			dame=1;
		}
		//
		if (dame!=1){
			karibandukejunid[nukekazu]=karibandukepointjunid[i];
			nukeid[nukekazu]=karibandukepointjunid[i];
			nukekazu++;
		}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
//////三段目以上だった力士だけで三段目の番付を仮に作成
	//三段目と序二段の入れ替えはこの後処理
	for (i=0;nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){//ポイント順に処理
		//勝ち越し力士を降格させないようにする処理
		if (nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME){//三段目を決める時
			for (iii=nukekazu-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)+2; nukekazu < RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME; iii++){
				kouhoid=-101;
				for (iiii=0;iiii<RIKISISUU;iiii++){
					if (rikisidata[iiii].bandukenameid==7 
					&& rikisidata[iiii].bandukesuuji==(int)(iii/2) 
					&& rikisidata[iiii].bandukehigasiornisi==iii%2+1 
					&& win[iiii]>lost[iiii]){
						kouhoid=iiii;
						break;
					}
				}
				if (kouhoid==-101){
					dame=1;
				}else{
					dame=0;
					for (ii=0;ii<nukekazu;ii++){
						if (kouhoid==nukeid[ii]){
							dame=1;
							break;
						}
					}
				}
				if (rikisidata[kouhoid].retirekonbasho==1){
					dame=1;
				}
				if (dame!=1){
					karibandukejunid[nukekazu]=kouhoid;
					nukeid[nukekazu]=kouhoid;
					nukekazu++;
				}else{
					break;//通常処理へ
				}
			}
		}
		//通常処理
		if (rikisidata[karibandukepointjunid[i]].bandukejun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME){//前の場所三段目以上
			//すでに番付決定済みだったらパスする処理
			dame=0;
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
					break;
				}
			}
			//
			if (dame!=1){
				karibandukejunid[nukekazu]=karibandukepointjunid[i];
				nukeid[nukekazu]=karibandukepointjunid[i];
				nukekazu++;
			}
		}
	}

	//三段目から陥落させるべき力士を検索し、その分をリセット
	for (i=nukekazu-1;i>-1;i--){
		if (karibandukepoint[karibandukejunid[i]]>=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME){
			karibandukejunid[i]=-1;
			nukeid[i]=-1;
			nukekazu--;
		}else{
			break;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//序二段から三段目へ上げる力士の決定
	//順位1、７戦全勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==7
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位2、筆頭で勝ち越し
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+1*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount>=4
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
/*	//順位3、20枚目以内で6勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==6
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位4、10枚目以内で5勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+10*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==5
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位5、5枚目以内で4勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+5*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==4
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位6、21枚目から40枚目以内で6勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+40*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==6
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位7、20枚目以内で5勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==5
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位8、10枚目以内で4勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+10*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==4
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位9、41枚目から60枚目以内で6勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+40*2;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+60*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==6
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位10、21枚目から40枚目以内で5勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+40*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==5
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位11、20枚目以内で4勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==4
			&& rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}*/
	//順位3、point順で上がるべき力士(陥落すべきとされた力士が復活する場合もありうる)
	//引退力士分で得する力士っちゅうこと
	for (i=0;nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		//すでに番付決定済みだったらパスする処理
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (karibandukepointjunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[karibandukepointjunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (rikisidata[karibandukepointjunid[i]].bandukenameid>8){
			dame=1;
		}
		//
		if (dame!=1){
			karibandukejunid[nukekazu]=karibandukepointjunid[i];
			nukeid[nukekazu]=karibandukepointjunid[i];
			nukekazu++;
		}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}


	
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

//////序二段以上だった力士だけで序二段の番付を仮に作成
	//序二段と序の口の入れ替えはこの後処理
	for (i=0;nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){//ポイント順に処理
		//勝ち越し力士を降格させないようにする処理
		if (nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN){//序二段を決める時
			for (iii=nukekazu-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)+2; nukekazu < RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN; iii++){
				kouhoid=-101;
				for (iiii=0;iiii<RIKISISUU;iiii++){
					if (rikisidata[iiii].bandukenameid==8 
					&& rikisidata[iiii].bandukesuuji==(int)(iii/2) 
					&& rikisidata[iiii].bandukehigasiornisi==iii%2+1 
					&& win[iiii]>lost[iiii]){
						kouhoid=iiii;
						break;
					}
				}
				if (kouhoid==-101){
					dame=1;
				}else{
					dame=0;
					for (ii=0;ii<nukekazu;ii++){
						if (kouhoid==nukeid[ii]){
							dame=1;
							break;
						}
					}
				}
				if (rikisidata[kouhoid].retirekonbasho==1){
					dame=1;
				}
				if (dame!=1){
					karibandukejunid[nukekazu]=kouhoid;
					nukeid[nukekazu]=kouhoid;
					nukekazu++;
				}else{
					break;//通常処理へ
				}
			}
		}
		//通常処理
		if (rikisidata[karibandukepointjunid[i]].bandukejun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN){//前の場所序二段以上
			//すでに番付決定済みだったらパスする処理
			dame=0;
			for (ii=0;ii<nukekazu;ii++){
				if (karibandukepointjunid[i]==nukeid[ii]){
					dame=1;
					break;
				}
			}
			//
			if (dame!=1){
				karibandukejunid[nukekazu]=karibandukepointjunid[i];
				nukeid[nukekazu]=karibandukepointjunid[i];
				nukekazu++;
			}
		}
	}

	//序二段から陥落させるべき力士を検索し、その分をリセット
	for (i=nukekazu-1;i>-1;i--){
		if (karibandukepoint[karibandukejunid[i]]>=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN){
			karibandukejunid[i]=-1;
			nukeid[i]=-1;
			nukekazu--;
		}else{
			break;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//序の口から序二段へ上げる力士の決定
	//順位1、７戦全勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;
	i<RIKISISUU;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN)){
			break;
		}
		wincount=0;
		for (ii=0;ii<15;ii++){
			if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
				wincount++;
			}
		}
		if (wincount==7 && rikisidata[bandukejunid[i]].retirekonbasho!=1){
			karibandukejunid[nukekazu]=bandukejunid[i];
			nukeid[nukekazu]=bandukejunid[i];
			nukekazu++;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//順位2、筆頭勝ち越し
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;
	i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+1*2;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount>=4 && rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
/*	//順位3、6勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;
	i<RIKISISUU;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==6 && rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位4、5勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;
	i<RIKISISUU;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==5 && rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}
	//順位5、4勝
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;
	i<RIKISISUU;i++){
		if (!(nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN)){
			break;
		}
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (bandukejunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[bandukejunid[i]].retirekonbasho==1){
			dame=1;
		}
		if (dame!=1){
			wincount=0;
			for (ii=0;ii<15;ii++){
				if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
					wincount++;
				}
			}
			if (wincount==4 && rikisidata[bandukejunid[i]].retirekonbasho!=1){
				karibandukejunid[nukekazu]=bandukejunid[i];
				nukeid[nukekazu]=bandukejunid[i];
				nukekazu++;
			}
		}
	}*/
	//順位3、point順で上がるべき力士(陥落すべきとされた力士が復活する場合もありうる)
	//引退力士分で得する力士っちゅうこと
	for (i=0;nukekazu<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		//すでに番付決定済みだったらパスする処理
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (karibandukepointjunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		if (rikisidata[karibandukepointjunid[i]].retirekonbasho==1){
			dame=1;
		}
		//
		if (dame!=1){
			karibandukejunid[nukekazu]=karibandukepointjunid[i];
			nukeid[nukekazu]=karibandukepointjunid[i];
			nukekazu++;
		}
//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

//////残りの力士で序の口の番付を作成
	for (i=0;nukekazu<RIKISISUU;i++){//ポイント順に処理
		//勝ち越し力士を降格させないようにする処理
		if (nukekazu<RIKISISUU){//序の口を決める時
			for (iii=nukekazu-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN)+2; nukekazu < RIKISISUU; iii++){
				kouhoid=-101;
				for (iiii=0;iiii<RIKISISUU;iiii++){
					if (rikisidata[iiii].bandukenameid==9 
					&& rikisidata[iiii].bandukesuuji==(int)(iii/2) 
					&& rikisidata[iiii].bandukehigasiornisi==iii%2+1 
					&& win[iiii]>lost[iiii]){
						kouhoid=iiii;
						break;
					}
				}
				if (kouhoid==-101){
					dame=1;
				}else{
					dame=0;
					for (ii=0;ii<nukekazu;ii++){
						if (kouhoid==nukeid[ii]){
							dame=1;
							break;
						}
					}
				}
				if (rikisidata[kouhoid].retirekonbasho==1){
					dame=1;
				}
				if (dame!=1){
					karibandukejunid[nukekazu]=kouhoid;
					nukeid[nukekazu]=kouhoid;
					nukekazu++;
				}else{
					break;//通常処理へ
				}
			}
		}
		//通常処理
		//すでに番付決定済みだったらパスする処理
		dame=0;
		for (ii=0;ii<nukekazu;ii++){
			if (karibandukepointjunid[i]==nukeid[ii]){
				dame=1;
				break;
			}
		}
		//
		if (dame!=1){
			karibandukejunid[nukekazu]=karibandukepointjunid[i];
			nukeid[nukekazu]=karibandukepointjunid[i];
			nukekazu++;
		}
	}

if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

///昇段力士調整処理
	//幕下→十両
	for (i=RIKISISUU_MAKUUTI;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==6
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==7){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(120*14/60) );
				if (sakijun<RIKISISUU_MAKUUTI+6*2){
					sakijun=RIKISISUU_MAKUUTI+6*2;
				}
				//残留力士で同じ勝ち数相当以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==5
					 && win[karibandukejunid[ii]]>=11){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==6
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if(win[karibandukejunid[i]]==6){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(120*14/60*5/7) );
				if (sakijun<RIKISISUU_MAKUUTI+6*2){
					sakijun=RIKISISUU_MAKUUTI+6*2;
				}
				//残留力士で同じ勝ち数相当以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==5
					 && win[karibandukejunid[ii]]>=10){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==6
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if(win[karibandukejunid[i]]==5){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(120*14/60*3/7) );
				if (sakijun<RIKISISUU_MAKUUTI+6*2){
					sakijun=RIKISISUU_MAKUUTI+6*2;
				}
				//残留力士で同じ勝ち数相当以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==5
					 && win[karibandukejunid[ii]]>=9){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==6
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if(win[karibandukejunid[i]]==4){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(120*14/60*2/7) );
				if (sakijun<RIKISISUU_MAKUUTI+6*2){
					sakijun=RIKISISUU_MAKUUTI+6*2;
				}
				//残留力士で同じ勝ち数相当以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==5
					 && win[karibandukejunid[ii]]>=8){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//三段目→幕下
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==7//三段目から昇格した力士を検索
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==7){//7勝
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(200*6/10) );
				if (sakijun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+10*2){
					sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+10*2;
				}
				//残留力士で同じ勝ち数以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==6
					 && win[karibandukejunid[ii]]==7){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==7
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if(win[karibandukejunid[i]]==6){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(200*6/10*4/7) );
				if (sakijun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+10*2){
					sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+10*2;
				}
				//残留力士で同じ勝ち数以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==6
					 && win[karibandukejunid[ii]]>=6){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==7
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if(win[karibandukejunid[i]]==5){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(200*6/10*2/7) );
				if (sakijun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+10*2){
					sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+10*2;
				}
				//残留力士で同じ勝ち数以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==6
					 && win[karibandukejunid[ii]]>=5){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==7
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if(win[karibandukejunid[i]]==4){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(200*6/10*1/11) );
				if (sakijun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+10*2){
					sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+10*2;
				}
				//残留力士で同じ勝ち数以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==6
					 && win[karibandukejunid[ii]]>=4){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//序二段→三段目
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==8
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==7){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(240*200/240) );
				if (sakijun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+10*2){
					sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+10*2;
				}
				//残留力士で同じ勝ち数以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==7
					 && win[karibandukejunid[ii]]==7){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==8
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if(win[karibandukejunid[i]]==6){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(240*200/240*4/7) );
				if (sakijun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+10*2){
					sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+10*2;
				}
				//残留力士で同じ勝ち数以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==7
					 && win[karibandukejunid[ii]]>=6){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==8
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if(win[karibandukejunid[i]]==5){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(240*200/240*2/7) );
				if (sakijun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+10*2){
					sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+10*2;
				}
				//残留力士で同じ勝ち数以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==7
					 && win[karibandukejunid[ii]]>=5){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==8
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if(win[karibandukejunid[i]]==4){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(240*200/240*1/11) );
				if (sakijun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+10*2){
					sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+10*2;
				}
				//残留力士で同じ勝ち数以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==7
					 && win[karibandukejunid[ii]]>=4){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	//序の口→序二段
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==9
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==7){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(80*240/80) );
				if (sakijun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2){
					sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2;
				}
				//残留力士で同じ勝ち数以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONOKUTI;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==8
					 && win[karibandukejunid[ii]]==7){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==9
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if(win[karibandukejunid[i]]==6){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(80*240/80*4/7) );
				if (sakijun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2){
					sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2;
				}
				//残留力士で同じ勝ち数以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONOKUTI;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==8
					 && win[karibandukejunid[ii]]>=6){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==9
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if(win[karibandukejunid[i]]==5){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(80*240/80*2/7) );
				if (sakijun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2){
					sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2;
				}
				//残留力士で同じ勝ち数以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONOKUTI;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==8
					 && win[karibandukejunid[ii]]>=5){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==9
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if(win[karibandukejunid[i]]==4){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-( (int)(80*240/80*1/7) );
				if (sakijun<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2){
					sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+20*2;
				}
				//残留力士で同じ勝ち数以上の力士より上にいっちゃまずいので
				for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONOKUTI;ii++){
					if (rikisidata[karibandukejunid[ii]].bandukenameid==8
					 && win[karibandukejunid[ii]]>=4){
					 	if (ii>=sakijun) sakijun=ii+1;
					 }
				}
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

///降段力士の落ち幅の調整
	for (i=0;i<RIKISISUU;i++){
		chouseizumi[i]=0;
	}
	//十両→幕下
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==5
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==7){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+2*1;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==5
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==6){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+2*3;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==5
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==5){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+2*5;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==5
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==4){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+2*7;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==5
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==3){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+2*9;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==5
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==2){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+2*11;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==5
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==1){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+2*13;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==5
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==0){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+2*15;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}

if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//幕下→三段目
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==6
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==3){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+10*1;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==6
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==2){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+10*3;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==6
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==1){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+10*5;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==6
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==0){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+10*7;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//三段目→序二段
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==7
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==3){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+14*1;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==7
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==2){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+14*3;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==7
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==1){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+14*5;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==7
		 && chouseizumi[karibandukejunid[i]]!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==0){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+14*7;
				//筆頭力士は残留力士から作りたいので
			 	if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//序二段→序の口
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==8
		 && chouseizumi[karibandukejunid[i]]!=1
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==3){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+17*1;
				//筆頭力士は残留力士から作りたいので
			 	//if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==8
		 && chouseizumi[karibandukejunid[i]]!=1
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==2){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+17*3;
				//筆頭力士は残留力士から作りたいので
			 	//if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==8
		 && chouseizumi[karibandukejunid[i]]!=1
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==1){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+17*5;
				//筆頭力士は残留力士から作りたいので
			 	//if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==8
		 && chouseizumi[karibandukejunid[i]]!=1
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]==0){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun+17*7;
				//筆頭力士は残留力士から作りたいので
			 	//if (RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_+1>=sakijun) sakijun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+2;
				chouseizumi[karibandukejunid[i]]=1;//調整済みフラグ
			}
			if (sakijun<i){
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
			}
		 }
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
///ここで、勝ち越しなのに番付あがってないのがいたらためしにあげてみる処理
///だけど、東筆頭で勝ち越しなのに番付上がってないのをいじるとヤバソウナノデいじらないようにした（2008/4/1）「+1」がそれ
	//十両
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+1;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==5
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]>lost[karibandukejunid[i]]
			&& i>=rikisidata[karibandukejunid[i]].bandukejun
			&& !(win[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]]>lost[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]] && rikisidata[karibandukejunid[i]].bandukejun-1>=rikisidata[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]].bandukejun-1) ){//sakijunの力士の仮順位がせいぜい1上がっただけの場合には、かわいそうなのと千日手防止も兼ねて調整しないようにするための条件
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-1;
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
				i=RIKISISUU_MAKUUTI;//調整したらまた最初から見直す
				chouseizumi[0]++;
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"十両の勝ち越し力士の番付上昇にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//幕下
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+1;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==6
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]>lost[karibandukejunid[i]]
			&& i>=rikisidata[karibandukejunid[i]].bandukejun
			&& !(win[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]]>lost[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]] && rikisidata[karibandukejunid[i]].bandukejun-1>=rikisidata[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]].bandukejun-1) ){//sakijunの力士の仮順位がせいぜい1上がっただけの場合には、かわいそうなのと千日手防止も兼ねて調整しないようにするための条件
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-1;
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
				i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;//調整したらまた最初から見直す
				chouseizumi[0]++;
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"幕下の勝ち越し力士の番付上昇にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//三段目
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+1;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==7
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]>lost[karibandukejunid[i]]
			&& i>=rikisidata[karibandukejunid[i]].bandukejun
			&& !(win[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]]>lost[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]] && rikisidata[karibandukejunid[i]].bandukejun-1>=rikisidata[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]].bandukejun-1) ){//sakijunの力士の仮順位がせいぜい1上がっただけの場合には、かわいそうなのと千日手防止も兼ねて調整しないようにするための条件
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-1;
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
				i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;//調整したらまた最初から見直す
				chouseizumi[0]++;
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"三段目の勝ち越し力士の番付上昇にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//序二段
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+1;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==8
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]>lost[karibandukejunid[i]]
			&& i>=rikisidata[karibandukejunid[i]].bandukejun
			&& !(win[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]]>lost[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]] && rikisidata[karibandukejunid[i]].bandukejun-1>=rikisidata[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]].bandukejun-1) ){//sakijunの力士の仮順位がせいぜい1上がっただけの場合には、かわいそうなのと千日手防止も兼ねて調整しないようにするための条件
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-1;
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
				i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;//調整したらまた最初から見直す
				chouseizumi[0]++;
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"序二段の勝ち越し力士の番付上昇にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//序の口
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+1;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==9
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]>lost[karibandukejunid[i]]
			&& i>=rikisidata[karibandukejunid[i]].bandukejun
			&& !(win[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]]>lost[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]] && rikisidata[karibandukejunid[i]].bandukejun-1>=rikisidata[karibandukejunid[rikisidata[karibandukejunid[i]].bandukejun-1]].bandukejun-1) ){//sakijunの力士の仮順位がせいぜい1上がっただけの場合には、かわいそうなのと千日手防止も兼ねて調整しないようにするための条件
				sakijun=rikisidata[karibandukejunid[i]].bandukejun-1;
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
				i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;//調整したらまた最初から見直す
				chouseizumi[0]++;
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"序の口の勝ち越し力士の番付上昇にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
///調整の結果勝ち越しなのに番付下落しているのがいたら復活させる処理
	//十両
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==5
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]>lost[karibandukejunid[i]]
			&& i>rikisidata[karibandukejunid[i]].bandukejun){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun;
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
				i=RIKISISUU_MAKUUTI;//調整したらまた最初から見直す
				chouseizumi[0]++;
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"十両の勝ち越し力士の番付維持にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//幕下
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==6
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]>lost[karibandukejunid[i]]
			&& i>rikisidata[karibandukejunid[i]].bandukejun){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun;
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
				i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;//調整したらまた最初から見直す
				chouseizumi[0]++;
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"幕下の勝ち越し力士の番付維持にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//三段目
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==7
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]>lost[karibandukejunid[i]]
			&& i>rikisidata[karibandukejunid[i]].bandukejun){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun;
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
				i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;//調整したらまた最初から見直す
				chouseizumi[0]++;
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"三段目の勝ち越し力士の番付維持にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//序二段
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==8
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]>lost[karibandukejunid[i]]
			&& i>rikisidata[karibandukejunid[i]].bandukejun){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun;
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
				i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;//調整したらまた最初から見直す
				chouseizumi[0]++;
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"序二段の勝ち越し力士の番付維持にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//序の口
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;i++){
		if (rikisidata[karibandukejunid[i]].bandukenameid==9
		 && rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			sakijun=9999;
			if (win[karibandukejunid[i]]>lost[karibandukejunid[i]]
			&& i>rikisidata[karibandukejunid[i]].bandukejun){
				sakijun=rikisidata[karibandukejunid[i]].bandukejun;
				tempid=karibandukejunid[i];
				motojun=i;
				for (ii=motojun;ii>sakijun;ii--){
					karibandukejunid[ii]=karibandukejunid[ii-1];
				}
				karibandukejunid[sakijun]=tempid;
				i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;//調整したらまた最初から見直す
				chouseizumi[0]++;
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"序の口の勝ち越し力士の番付維持にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}

///調整の結果、番付で矛盾しているのがいたら直す処理
	//十両
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		if (rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			for (ii=RIKISISUU_MAKUUTI;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;ii++){
				if (i<ii
				&& rikisidata[karibandukejunid[i]].bandukejun > rikisidata[karibandukejunid[ii]].bandukejun
				&& win[karibandukejunid[i]]<=win[karibandukejunid[ii]]
				&& rikisidata[karibandukejunid[i]].bandukenameid==rikisidata[karibandukejunid[ii]].bandukenameid
				&& rikisidata[karibandukejunid[ii]].retirekonbasho!=1){
					tempid=karibandukejunid[ii];
					karibandukejunid[ii]=karibandukejunid[i];
					karibandukejunid[i]=tempid;
					i=RIKISISUU_MAKUUTI-1;//調整したらまた最初から見直す
					chouseizumi[0]++;
					break;
				}
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"十両の番付の矛盾防止にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
//////////////
//ClearDrawScreen();
//DrawFormatString(0,0,CRRED,"十両%d回調整した",chouseizumi[0]);
//ScreenFlip();
//WaitKey();
///////////
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//幕下
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		if (rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;ii++){
				if (i<ii
				&& rikisidata[karibandukejunid[i]].bandukejun > rikisidata[karibandukejunid[ii]].bandukejun
				&& win[karibandukejunid[i]]<=win[karibandukejunid[ii]]
				&& rikisidata[karibandukejunid[i]].bandukenameid==rikisidata[karibandukejunid[ii]].bandukenameid
				&& rikisidata[karibandukejunid[ii]].retirekonbasho!=1){
					tempid=karibandukejunid[ii];
					karibandukejunid[ii]=karibandukejunid[i];
					karibandukejunid[i]=tempid;
					i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU-1;//調整したらまた最初から見直す
					chouseizumi[0]++;
					break;
				}
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"幕下の番付の矛盾防止にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
//////////////
//ClearDrawScreen();
//DrawFormatString(0,0,CRRED,"幕下%d回調整した",chouseizumi[0]);
//ScreenFlip();
//WaitKey();
///////////
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//三段目
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		if (rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;ii++){
				if (i<ii
				&& rikisidata[karibandukejunid[i]].bandukejun > rikisidata[karibandukejunid[ii]].bandukejun
				&& win[karibandukejunid[i]]<=win[karibandukejunid[ii]]
				&& rikisidata[karibandukejunid[i]].bandukenameid==rikisidata[karibandukejunid[ii]].bandukenameid
				&& rikisidata[karibandukejunid[ii]].retirekonbasho!=1){
					tempid=karibandukejunid[ii];
					karibandukejunid[ii]=karibandukejunid[i];
					karibandukejunid[i]=tempid;
					i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA-1;//調整したらまた最初から見直す
					chouseizumi[0]++;
					break;
				}
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"三段目の番付の矛盾防止にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
//////////////
//ClearDrawScreen();
//DrawFormatString(0,0,CRRED,"三段目%d回調整した",chouseizumi[0]);
//ScreenFlip();
//WaitKey();
///////////
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//序二段
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		if (rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;ii++){
				if (i<ii
				&& rikisidata[karibandukejunid[i]].bandukejun > rikisidata[karibandukejunid[ii]].bandukejun
				&& win[karibandukejunid[i]]<=win[karibandukejunid[ii]]
				&& rikisidata[karibandukejunid[i]].bandukenameid==rikisidata[karibandukejunid[ii]].bandukenameid
				&& rikisidata[karibandukejunid[ii]].retirekonbasho!=1){
					tempid=karibandukejunid[ii];
					karibandukejunid[ii]=karibandukejunid[i];
					karibandukejunid[i]=tempid;
					i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME-1;//調整したらまた最初から見直す
					chouseizumi[0]++;
					break;
				}
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"序二段の番付の矛盾防止にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
//////////////
//ClearDrawScreen();
//DrawFormatString(0,0,CRRED,"序二段%d回調整した",chouseizumi[0]);
//ScreenFlip();
//WaitKey();
///////////
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//序の口
	chouseizumi[0]=0;//無限ループ防止用カウント
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;i++){
		if (rikisidata[karibandukejunid[i]].retirekonbasho!=1){//調整済みだと-1にしてフラグ代わりにする
			for (ii=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;ii<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN+RIKISISUU_JONOKUTI;ii++){
				if (i<ii
				&& rikisidata[karibandukejunid[i]].bandukejun > rikisidata[karibandukejunid[ii]].bandukejun
				&& win[karibandukejunid[i]]<=win[karibandukejunid[ii]]
				&& rikisidata[karibandukejunid[i]].bandukenameid==rikisidata[karibandukejunid[ii]].bandukenameid
				&& rikisidata[karibandukejunid[ii]].retirekonbasho!=1){
					tempid=karibandukejunid[ii];
					karibandukejunid[ii]=karibandukejunid[i];
					karibandukejunid[i]=tempid;
					i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN-1;//調整したらまた最初から見直す
					chouseizumi[0]++;
					break;
				}
			}
		}
		if (chouseizumi[0]>100){//無限ループ防止
			ClearDrawScreen();
			DrawString(187,369,"序の口の番付の矛盾防止にこだわった結果",CRWHITE);
			DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
			DrawString(187,369+32,"Hit Any Key",CRWHITE);
			ScreenFlip();
			WaitKey();
			break;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
//////////////
//ClearDrawScreen();
//DrawFormatString(0,0,CRRED,"序の口%d回調整した",chouseizumi[0]);
//ScreenFlip();
//WaitKey();
///////////
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

//力士全員共通の仕上げ////////////////
	//付け出し力士だったら無理やりねじ込む処理
	//もし自部屋で付け出し力士をスカウトしていなければ一定の確率でCOM部屋でデビューさせる
	if (tukedasiid==-1){
		for (i=0;i<intaisuu;i++){
			if (rikisidata[intairikisikonbasho[i]].tatiaigijutu_max>50
			 && rikisidata[intairikisikonbasho[i]].juunansei>50
			 && rikisidata[intairikisikonbasho[i]].kerutikara_max>150
			 && ((rikisidata[intairikisikonbasho[i]].migiwanryoku_max>50 && (rikisidata[intairikisikonbasho[i]].migikaesi_max>50 || rikisidata[intairikisikonbasho[i]].migisibori_max>50))
				|| (rikisidata[intairikisikonbasho[i]].hidariwanryoku_max>50 && (rikisidata[intairikisikonbasho[i]].hidarikaesi_max>50 || rikisidata[intairikisikonbasho[i]].hidarisibori_max>50)))
			 && ((rikisidata[intairikisikonbasho[i]].migiwanryoku_max>50 && rikisidata[intairikisikonbasho[i]].migiakuryoku_max>50)
				|| (rikisidata[intairikisikonbasho[i]].hidariwanryoku_max>50 && rikisidata[intairikisikonbasho[i]].hidariakuryoku_max>50))
			 && rikisidata[intairikisikonbasho[i]].tossinryoku_max>40){
				if (GetRand(99)<80){
					tukedasiid=intairikisikonbasho[i];
					tukedasi_sanndanmeflag=GetRand(1);
					if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
						ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
						DrawFormatString(100,369,CRWHITE,"%s部屋から%sが付け出しデビュー！！",
						heyastring[rikisidata[tukedasiid].heyaid],
						namestring[tukedasiid]);
						DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
						ScreenFlip() ;//裏画面を表画面にコピー
						WaitKey();
					}
					break;
				}
			}
		}
		////幕下付け出しデビューテスト→自部屋の場合はretirenew.cpp内でこの処理を行っている////////////
		{
			int r=0;int ii;
			r=GetRand(6);
			//tukedasiid=i;
			if (tukedasi_sanndanmeflag==1){
				for (ii=0;ii<6*(6+r);ii++){
					keiko_nakami_com(tukedasiid);
					//if( ProcessMessage() == -1 ){mode=1;return ;}
				}
				rikisidata[tukedasiid].age=18;
			}else{
				for (ii=0;ii<6*(12+r);ii++){
				//for (ii=0;ii<6*5;ii++){
					keiko_nakami_com(tukedasiid);
					//if( ProcessMessage() == -1 ){mode=1;return ;}
				}
				//rikisidata[i].age=21;
				rikisidata[tukedasiid].age=21;
			}
		}
		//////////////////////////////////////////////////////////////////
	}
	if (tukedasiid!=-1){
		for (i=0;i<RIKISISUU;i++){
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (karibandukejunid[i]==tukedasiid){
				motonojun=i;
				break;
			}
		}
		if (tukedasi_sanndanmeflag==1){
			for (i=motonojun-1;i>=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME-1;i--){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				temp_karibanid=karibandukejunid[i];
				karibandukejunid[i+1]=temp_karibanid;
			}
			karibandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME-1]=tukedasiid;
		}else{
			for (i=motonojun-1;i>=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+30;i--){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				temp_karibanid=karibandukejunid[i];
				karibandukejunid[i+1]=temp_karibanid;
			}
			karibandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+30]=tukedasiid;
		}

//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"%s部屋から%sが付け出しデビューしました！！\n",
heyastring[rikisidata[tukedasiid].heyaid],
namestring[tukedasiid]);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////

		//成長型AI成長用稽古→前頭の全力士と１０回ずつ稽古させておくことにした
		if (memoryfusokuflag==0){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawString( 100 , 272 - 32 , "付け出しデビュー力士がAI稽古中…" , CRWHITE);
			ScreenFlip() ;//裏画面を表画面にコピー
			if( ProcessMessage() == -1 ){mode=1;return ;}
			for (i=0;i<RIKISISUU;i++){
				if (rikisidata[i].bandukenameid==4){
					for (ii=0;ii<10;ii++){ 
						AIkeiko(tukedasiid,i);
					}
					if (mode==1) return;
				}
			}
		}

		tukedasiid=-1;//付け出しIDをリセット
	}
	for (i=0;i<RIKISISUU;i++){
		rikisidata[karibandukejunid[i]].bandukejun=i;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//小結以下の仕上げ
	//小結の仕上げ
	rikisidata[karibandukejunid[yokodunacount+oozekicount+sekiwakecount]].bandukenameid=3;//東小結
	rikisidata[karibandukejunid[yokodunacount+oozekicount+sekiwakecount]].bandukesuuji=0;
	rikisidata[karibandukejunid[yokodunacount+oozekicount+sekiwakecount]].bandukehigasiornisi=1;
	rikisidata[karibandukejunid[yokodunacount+oozekicount+sekiwakecount+1]].bandukenameid=3;//西小結
	rikisidata[karibandukejunid[yokodunacount+oozekicount+sekiwakecount+1]].bandukesuuji=0;
	rikisidata[karibandukejunid[yokodunacount+oozekicount+sekiwakecount+1]].bandukehigasiornisi=2;
	//前頭の仕上げ
	for (i=yokodunacount+oozekicount+sekiwakecount+2;i<RIKISISUU_MAKUUTI;i++){
		rikisidata[karibandukejunid[i]].bandukenameid=4;//前頭
		rikisidata[karibandukejunid[i]].bandukesuuji=(int)(i-(yokodunacount+oozekicount+sekiwakecount+2)+2)/2;
		if ((i-(yokodunacount+oozekicount+sekiwakecount+2)+2)%2==0){
			rikisidata[karibandukejunid[i]].bandukehigasiornisi=1;
		}else{
			rikisidata[karibandukejunid[i]].bandukehigasiornisi=2;
		}
	}
	//十両の仕上げ
	for (i=RIKISISUU_MAKUUTI;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i++){
		rikisidata[karibandukejunid[i]].bandukenameid=5;//十両
		rikisidata[karibandukejunid[i]].bandukesuuji=(int)(i-RIKISISUU_MAKUUTI+2)/2;
		if ((i-RIKISISUU_MAKUUTI+2)%2==0){
			rikisidata[karibandukejunid[i]].bandukehigasiornisi=1;
		}else{
			rikisidata[karibandukejunid[i]].bandukehigasiornisi=2;
		}
	}
	//幕下の仕上げ
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		rikisidata[karibandukejunid[i]].bandukenameid=6;//幕下
		rikisidata[karibandukejunid[i]].bandukesuuji=(int)(i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU)+2)/2;
		if ((i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU)+2)%2==0){
			rikisidata[karibandukejunid[i]].bandukehigasiornisi=1;
		}else{
			rikisidata[karibandukejunid[i]].bandukehigasiornisi=2;
		}
	}
	//三段目の仕上げ
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i++){
		rikisidata[karibandukejunid[i]].bandukenameid=7;//三段目
		rikisidata[karibandukejunid[i]].bandukesuuji=(int)(i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)+2)/2;
		if ((i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA)+2)%2==0){
			rikisidata[karibandukejunid[i]].bandukehigasiornisi=1;
		}else{
			rikisidata[karibandukejunid[i]].bandukehigasiornisi=2;
		}
	}
	//序二段の仕上げ
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i++){
		rikisidata[karibandukejunid[i]].bandukenameid=8;//序二段
		rikisidata[karibandukejunid[i]].bandukesuuji=(int)(i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)+2)/2;
		if ((i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME)+2)%2==0){
			rikisidata[karibandukejunid[i]].bandukehigasiornisi=1;
		}else{
			rikisidata[karibandukejunid[i]].bandukehigasiornisi=2;
		}
	}
	//序の口の仕上げ
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN;i<RIKISISUU;i++){
		rikisidata[karibandukejunid[i]].bandukenameid=9;//序の口
		rikisidata[karibandukejunid[i]].bandukesuuji=(int)(i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN)+2)/2;
		if ((i-(RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA+RIKISISUU_SANDANME+RIKISISUU_JONIDAN)+2)%2==0){
			rikisidata[karibandukejunid[i]].bandukehigasiornisi=1;
		}else{
			rikisidata[karibandukejunid[i]].bandukehigasiornisi=2;
		}
	}
if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	///////////////3.13で追加//十両以上関脇以下で負け越し力士番付上昇防止処理//////////
	{
		int temp_bandukejun=0;
		int temp_bandukenameid=0;
		int temp_bandukesuuji=0;
		int temp_bandukehigasiornisi=0;
		int temp_karibandukejunid=0;
		char akirameroflag=0;
		char madairuyoflag=0;
		int kasansuu=0;
		char temp_string_kakuritu[301];
		char ch=0;
		int kazu=0;
		int makekosibandukesisuu=0;
		int ijinasiflag=0;
		int ikisakijun=0;
		char makusitaitaflag=0;
		char temp_filename[MAX_PATH];
		for (ii=0;ii<301;ii++){
			temp_string_kakuritu[ii]=0;
		}
		for (ii=0;ii<MAX_PATH;ii++){
			temp_filename[ii]=0;
		}
			//指数ファイル読み込み(見つからなければ作成)
			FILE *fpcsv;
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			strcpy(temp_filename,"data/makekosibandukesisuu.csv");
			fpcsv = fopen(temp_filename,"r");
			if( fpcsv == NULL ){
				fclose(fpcsv);
				fpcsv = fopen(temp_filename,"w");
				fprintf(fpcsv,"十両～関脇負け越し力士の番付について、-1→上昇もあり、0～10→維持or下がる\n");
				fprintf(fpcsv,"0に近いほど負け越し点数に近い下がり具合になる\n");
				fprintf(fpcsv,"ただし、0に近いほど8勝力士でも急上昇する場合あり\n");
				fprintf(fpcsv,"また、10に近いほど大きく負け越していても少ししか下がらない場合あり\n");
				fprintf(fpcsv,"6行目(この下の行)に数字を入れておいてください\n");
				fprintf(fpcsv,"5\n");
				fprintf(fpcsv,"この下の行に番付維持有り無し、0→維持あり、1→維持無し(東から西はあり)\n");
				fprintf(fpcsv,"0\n");
				fclose(fpcsv);
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
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
						}else if(ch=='-'){
							strcat(temp_string_kakuritu,"-");
						}
					}
				}
				if (kazu==5){
					makekosibandukesisuu=atoi(temp_string_kakuritu);
					if (makekosibandukesisuu<-1){
						makekosibandukesisuu=-1;
					}else if (makekosibandukesisuu>10){
						makekosibandukesisuu=10;
					}
				}else if (kazu==7){
					ijinasiflag=atoi(temp_string_kakuritu);
					if (ijinasiflag<0){
						makekosibandukesisuu=0;
					}else if (ijinasiflag>1){
						makekosibandukesisuu=1;
					}

				}
				kazu++;
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			fclose(fpcsv);
			if( ProcessMessage() == -1 ){mode=1;return ;}
/*
FILE *fpdebug;
fpdebug = fopen("debug_ban_joushou.csv","a");
fprintf(fpdebug,"\n%d年%d月　負け越し番付指数=%d　維持無しフラグ=%d\n",year,month,makekosibandukesisuu,ijinasiflag);
*/
	if (makekosibandukesisuu!=-1){
/*for (i=0;i<50;i++){
	fprintf(fpdebug,"ID%d bandukejun%d\n",karibandukejunid[i],rikisidata[karibandukejunid[i]].bandukejun);
}*/
		ClearDrawScreen();
		DrawString(187,369,"負け越し力士の番付上昇防止処理中…",CRWHITE);
		ScreenFlip();
		akirameroflag=0;
		chouseizumi[0]=0;
		for (i=yokodunacount+oozekicount;i<RIKISISUU-100;i++){//引退力士なども含めて多めにしておいた
			if (win[karibandukejunid[i]]<8 && last_bandukenameid[karibandukejunid[i]]<=5){
				if (last_bandukenameid[karibandukejunid[i]]>rikisidata[karibandukejunid[i]].bandukenameid
					|| (last_bandukenameid[karibandukejunid[i]]==rikisidata[karibandukejunid[i]].bandukenameid
						&& last_bandukesuuji[karibandukejunid[i]]>rikisidata[karibandukejunid[i]].bandukesuuji)
					|| (last_bandukenameid[karibandukejunid[i]]==rikisidata[karibandukejunid[i]].bandukenameid
						&& last_bandukesuuji[karibandukejunid[i]]==rikisidata[karibandukejunid[i]].bandukesuuji
						&& last_bandukehigasiornisi[karibandukejunid[i]]>rikisidata[karibandukejunid[i]].bandukehigasiornisi)
					|| (last_bandukenameid[karibandukejunid[i]]==rikisidata[karibandukejunid[i]].bandukenameid
						&& last_bandukesuuji[karibandukejunid[i]]==rikisidata[karibandukejunid[i]].bandukesuuji
						&& last_bandukehigasiornisi[karibandukejunid[i]]>=rikisidata[karibandukejunid[i]].bandukehigasiornisi
						&& ijinasiflag==1)
					|| (-makekosibandukesisuu+last_bandukejun[karibandukejunid[i]]-last_yokodunasuu-last_oozekisuu-last_sekiwakesuu+(15-win[karibandukejunid[i]]-win[karibandukejunid[i]])*2>rikisidata[karibandukejunid[i]].bandukejun-yokodunacount-oozekicount-sekiwakecount
						&& last_bandukenameid[karibandukejunid[i]]>=3)
				){
					if (sekiwakecount>2 && last_bandukenameid[karibandukejunid[i]]==2
						&& yokodunacount+oozekicount+1==rikisidata[karibandukejunid[i]].bandukejun){
						//通常の西関脇の場合(大関から落ちてすぐの関脇がいる場合)
						//加算数
						kasansuu=0;
						for (ii=i;ii<RIKISISUU-1-sekiwakecount+2;ii++){
							if (ii+1+sekiwakecount-2>=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU
								&& last_bandukenameid[karibandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU-1]]<=4){
								akirameroflag=1;
								break;
							}
							if (rikisidata[karibandukejunid[ii+1+sekiwakecount-2]].retirekonbasho==1){
								kasansuu++;
							}else{
								if (win[karibandukejunid[ii+1+sekiwakecount-2]]<8 && last_bandukenameid[karibandukejunid[ii+1+sekiwakecount-2]]<=5){
									if (last_bandukenameid[karibandukejunid[ii+1+sekiwakecount-2]]>rikisidata[karibandukejunid[i]].bandukenameid
										|| (last_bandukenameid[karibandukejunid[ii+1+sekiwakecount-2]]==rikisidata[karibandukejunid[i]].bandukenameid
											&& last_bandukesuuji[karibandukejunid[ii+1+sekiwakecount-2]]>rikisidata[karibandukejunid[i]].bandukesuuji)
										|| (last_bandukenameid[karibandukejunid[ii+1+sekiwakecount-2]]==rikisidata[karibandukejunid[i]].bandukenameid
											&& last_bandukesuuji[karibandukejunid[ii+1+sekiwakecount-2]]==rikisidata[karibandukejunid[i]].bandukesuuji
											&& last_bandukehigasiornisi[karibandukejunid[ii+1+sekiwakecount-2]]>rikisidata[karibandukejunid[i]].bandukehigasiornisi)
										|| (last_bandukenameid[karibandukejunid[ii+1+sekiwakecount-2]]==rikisidata[karibandukejunid[i]].bandukenameid
											&& last_bandukesuuji[karibandukejunid[ii+1+sekiwakecount-2]]==rikisidata[karibandukejunid[i]].bandukesuuji
											&& last_bandukehigasiornisi[karibandukejunid[ii+1+sekiwakecount-2]]>=rikisidata[karibandukejunid[i]].bandukehigasiornisi
											&& ijinasiflag==1)
										|| (last_bandukenameid[karibandukejunid[ii+1]]>=6 && rikisidata[karibandukejunid[i]].bandukejun<=RIKISISUU_MAKUUTI-1)//幕下力士が幕内に上がるのを防止
									){
										kasansuu++;
									}else{
										break;
									}
								}else{
									break;
								}
							}
						}
						if (akirameroflag==1){
/*
fprintf(fpdebug,"id=%d 先番name=%d 先番数=%d 先東西=%d 勝ち星=%d",karibandukejunid[i],last_bandukenameid[karibandukejunid[i]],last_bandukesuuji[karibandukejunid[i]],last_bandukehigasiornisi[karibandukejunid[i]],win[karibandukejunid[i]]);
fprintf(fpdebug,"（今番name=%d 今番数=%d 今東西=%d）加算数=%d について\n",rikisidata[karibandukejunid[i]].bandukenameid,rikisidata[karibandukejunid[i]].bandukesuuji,rikisidata[karibandukejunid[i]].bandukehigasiornisi,kasansuu);
fprintf(fpdebug,"幕内力士が幕下まで落ちてしまう恐れがあるので、負け越し番付上昇防止処理をあきらめました\n");
*/
							break;
						}
/*
fprintf(fpdebug,"id=%d 番付nameid=%d 番付数字=%d 番付東西=%d 勝ち星=%d",karibandukejunid[i],last_bandukenameid[karibandukejunid[i]],last_bandukesuuji[karibandukejunid[i]],last_bandukehigasiornisi[karibandukejunid[i]],win[karibandukejunid[i]]);
fprintf(fpdebug,"（番付nameid=%d 番付数字=%d 番付東西=%d）加算数=%d\n",rikisidata[karibandukejunid[i]].bandukenameid,rikisidata[karibandukejunid[i]].bandukesuuji,rikisidata[karibandukejunid[i]].bandukehigasiornisi,kasansuu);
*/
						//入れ替え処理
						temp_bandukejun=rikisidata[karibandukejunid[i+1+sekiwakecount-2+kasansuu]].bandukejun;
						temp_bandukenameid=rikisidata[karibandukejunid[i+1+sekiwakecount-2+kasansuu]].bandukenameid;
						temp_bandukesuuji=rikisidata[karibandukejunid[i+1+sekiwakecount-2+kasansuu]].bandukesuuji;
						temp_bandukehigasiornisi=rikisidata[karibandukejunid[i+1+sekiwakecount-2+kasansuu]].bandukehigasiornisi;
						for (ii=i+1+sekiwakecount-2+kasansuu;ii>i;ii--){
							rikisidata[karibandukejunid[ii]].bandukejun=rikisidata[karibandukejunid[ii-1]].bandukejun;
							rikisidata[karibandukejunid[ii]].bandukenameid=rikisidata[karibandukejunid[ii-1]].bandukenameid;
							rikisidata[karibandukejunid[ii]].bandukesuuji=rikisidata[karibandukejunid[ii-1]].bandukesuuji;
							rikisidata[karibandukejunid[ii]].bandukehigasiornisi=rikisidata[karibandukejunid[ii-1]].bandukehigasiornisi;
						}
						rikisidata[karibandukejunid[i]].bandukejun=temp_bandukejun;
						rikisidata[karibandukejunid[i]].bandukenameid=temp_bandukenameid;
						rikisidata[karibandukejunid[i]].bandukesuuji=temp_bandukesuuji;
						rikisidata[karibandukejunid[i]].bandukehigasiornisi=temp_bandukehigasiornisi;
						for (ii=0;ii<RIKISISUU;ii++){//番付順位
							for (iii=0;iii<RIKISISUU;iii++){//力士ＩＤ
								if (rikisidata[iii].bandukejun==ii){
									karibandukejunid[ii]=iii;
									break;
								}
							}
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
					}else{
						//小結以下の場合
						//加算数
						kasansuu=0;
						for (ii=i;ii<RIKISISUU-1;ii++){
							if (ii+1>=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU
								&& last_bandukenameid[karibandukejunid[RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU-1]]<=4){
								akirameroflag=1;
								break;
							}
							if (rikisidata[karibandukejunid[ii+1]].retirekonbasho==1){
								kasansuu++;
							}else{
								if ( (win[karibandukejunid[ii+1]]<8 && last_bandukenameid[karibandukejunid[ii+1]]<=5)
									|| (win[karibandukejunid[ii+1]]<4 && last_bandukenameid[karibandukejunid[ii+1]]>5)
								){
									if (last_bandukenameid[karibandukejunid[ii+1]]>rikisidata[karibandukejunid[i]].bandukenameid
										|| (last_bandukenameid[karibandukejunid[ii+1]]==rikisidata[karibandukejunid[i]].bandukenameid
											&& last_bandukesuuji[karibandukejunid[ii+1]]>rikisidata[karibandukejunid[i]].bandukesuuji)
										|| (last_bandukenameid[karibandukejunid[ii+1]]==rikisidata[karibandukejunid[i]].bandukenameid
											&& last_bandukesuuji[karibandukejunid[ii+1]]==rikisidata[karibandukejunid[i]].bandukesuuji
											&& last_bandukehigasiornisi[karibandukejunid[ii+1]]>rikisidata[karibandukejunid[i]].bandukehigasiornisi)
										|| (last_bandukenameid[karibandukejunid[ii+1]]==rikisidata[karibandukejunid[i]].bandukenameid
											&& last_bandukesuuji[karibandukejunid[ii+1]]==rikisidata[karibandukejunid[i]].bandukesuuji
											&& last_bandukehigasiornisi[karibandukejunid[ii+1]]>=rikisidata[karibandukejunid[i]].bandukehigasiornisi
											&& ijinasiflag==1)
										|| (last_bandukenameid[karibandukejunid[ii+1]]<=5 && -makekosibandukesisuu+last_bandukejun[karibandukejunid[ii+1]]-last_yokodunasuu-last_oozekisuu-last_sekiwakesuu+(15-win[karibandukejunid[ii+1]]-win[karibandukejunid[ii+1]])*2>rikisidata[karibandukejunid[i]].bandukejun-yokodunacount-oozekicount-sekiwakecount)
										|| (last_bandukenameid[karibandukejunid[ii+1]]>=6 && rikisidata[karibandukejunid[i]].bandukejun<=RIKISISUU_MAKUUTI-1)//幕下力士が幕内に上がるのを防止
									){
										kasansuu++;
									}else{
										break;
									}
								}else{
									break;
								}
							}
						}
						if (akirameroflag==1){
/*
fprintf(fpdebug,"id=%d 先番name=%d 先番数=%d 先東西=%d 勝ち星=%d",karibandukejunid[i],last_bandukenameid[karibandukejunid[i]],last_bandukesuuji[karibandukejunid[i]],last_bandukehigasiornisi[karibandukejunid[i]],win[karibandukejunid[i]]);
fprintf(fpdebug,"（今番name=%d 今番数=%d 今東西=%d）加算数=%d について\n",rikisidata[karibandukejunid[i]].bandukenameid,rikisidata[karibandukejunid[i]].bandukesuuji,rikisidata[karibandukejunid[i]].bandukehigasiornisi,kasansuu);
fprintf(fpdebug,"幕内力士が幕下まで落ちてしまう恐れがあるので、負け越し番付上昇防止処理をあきらめました\n");
*/
							break;
						}
/*
fprintf(fpdebug,"id=%d 番付nameid=%d 番付数字=%d 番付東西=%d 勝ち星=%d",karibandukejunid[i],last_bandukenameid[karibandukejunid[i]],last_bandukesuuji[karibandukejunid[i]],last_bandukehigasiornisi[karibandukejunid[i]],win[karibandukejunid[i]]);
fprintf(fpdebug,"（番付nameid=%d 番付数字=%d 番付東西=%d）加算数=%d\n",rikisidata[karibandukejunid[i]].bandukenameid,rikisidata[karibandukejunid[i]].bandukesuuji,rikisidata[karibandukejunid[i]].bandukehigasiornisi,kasansuu);
*/
						//入れ替え処理
						temp_bandukejun=rikisidata[karibandukejunid[i]].bandukejun;
						temp_bandukenameid=rikisidata[karibandukejunid[i]].bandukenameid;
						temp_bandukesuuji=rikisidata[karibandukejunid[i]].bandukesuuji;
						temp_bandukehigasiornisi=rikisidata[karibandukejunid[i]].bandukehigasiornisi;
						for (ii=i;ii<i+1+kasansuu;ii++){
//fprintf(fpdebug,"ID%d bandukejun%d ← ID%d bandukejun%d\n",karibandukejunid[ii],rikisidata[karibandukejunid[ii]].bandukejun,karibandukejunid[ii+1],rikisidata[karibandukejunid[ii+1]].bandukejun);
							rikisidata[karibandukejunid[ii]].bandukejun=rikisidata[karibandukejunid[ii+1]].bandukejun;
							rikisidata[karibandukejunid[ii]].bandukenameid=rikisidata[karibandukejunid[ii+1]].bandukenameid;
							rikisidata[karibandukejunid[ii]].bandukesuuji=rikisidata[karibandukejunid[ii+1]].bandukesuuji;
							rikisidata[karibandukejunid[ii]].bandukehigasiornisi=rikisidata[karibandukejunid[ii+1]].bandukehigasiornisi;
						}
//fprintf(fpdebug,"ID%d bandukejun%d ←  bandukejun%d\n",karibandukejunid[i+1+kasansuu],rikisidata[karibandukejunid[i+1+kasansuu]].bandukejun,temp_bandukejun);
						rikisidata[karibandukejunid[i+1+kasansuu]].bandukejun=temp_bandukejun;
						rikisidata[karibandukejunid[i+1+kasansuu]].bandukenameid=temp_bandukenameid;
						rikisidata[karibandukejunid[i+1+kasansuu]].bandukesuuji=temp_bandukesuuji;
						rikisidata[karibandukejunid[i+1+kasansuu]].bandukehigasiornisi=temp_bandukehigasiornisi;
						for (ii=0;ii<RIKISISUU;ii++){//番付順位
							for (iii=0;iii<RIKISISUU;iii++){//力士ＩＤ
								if (rikisidata[iii].bandukejun==ii){
									karibandukejunid[ii]=iii;
									break;
								}
							}
							//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						}
					}
				}
			}
			chouseizumi[0]++;
		}
//fprintf(fpdebug,"負け越し力士調整ループ回数=%d\n",chouseizumi[0]);
/*for (i=0;i<50;i++){
	fprintf(fpdebug,"ID%d bandukejun%d\n",karibandukejunid[i],rikisidata[karibandukejunid[i]].bandukejun);
}*/

		//幕内から幕下に落ちてしまった力士がいたら無理やりねじ込む処理
		//→さらに、負け越し点数的には幕下に転落しないはずの力士を救出する処理
		chouseizumi[0]=0;
		while(1){
			madairuyoflag=0;
			for (i=0;i<RIKISISUU;i++){
				if (rikisidata[karibandukejunid[i]].bandukenameid>=6
					&& ( (last_bandukenameid[karibandukejunid[i]]<=5 && (15-win[karibandukejunid[i]]-win[karibandukejunid[i]])*2+last_bandukejun[karibandukejunid[i]]<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU)
						|| last_bandukenameid[karibandukejunid[i]]<=4 )
					&& rikisidata[karibandukejunid[i]].retirekonbasho!=1
				){
					madairuyoflag=1;
//fprintf(fpdebug,"理不尽に幕下に落ちた力士ID%d win=%d 先番名=%d 先番数=%d 先番東西%d 今番名=%d 今番数=%d 今東西=%d\n",karibandukejunid[i],win[karibandukejunid[i]],last_bandukenameid[karibandukejunid[i]],last_bandukesuuji[karibandukejunid[i]],last_bandukehigasiornisi[karibandukejunid[i]],rikisidata[karibandukejunid[i]].bandukenameid,rikisidata[karibandukejunid[i]].bandukesuuji,rikisidata[karibandukejunid[i]].bandukehigasiornisi);
					break;
				}
			}
			if (madairuyoflag!=0){
				for (i=0;i<RIKISISUU;i++){
					if (rikisidata[karibandukejunid[i]].bandukenameid>=6
					&& ( (last_bandukenameid[karibandukejunid[i]]<=5 && (15-win[karibandukejunid[i]]-win[karibandukejunid[i]])*2+last_bandukejun[karibandukejunid[i]]<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU)
						|| last_bandukenameid[karibandukejunid[i]]<=4 )
					&& rikisidata[karibandukejunid[i]].retirekonbasho!=1
					){
						motonojun=i;//一気に幕下まで落ちてしまった番付順位
						break;
					}
				}
				makusitaitaflag=0;
				for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU-1;i>yokodunacount+oozekicount;i--){
					if (last_bandukenameid[karibandukejunid[i]]>=6
						&& rikisidata[karibandukejunid[i]].retirekonbasho!=1
					){
						makusitaitaflag=1;
						ikisakijun=i;//代わりに十両から幕下に落ちる番付順位
//fprintf(fpdebug,"代わりに十両から幕下に落ちるID%d win=%d 先番名=%d 先番数=%d 先番東西%d 今番名=%d 今番数=%d 今東西=%d\n",karibandukejunid[i],win[karibandukejunid[i]],last_bandukenameid[karibandukejunid[i]],last_bandukesuuji[karibandukejunid[i]],last_bandukehigasiornisi[karibandukejunid[i]],rikisidata[karibandukejunid[i]].bandukenameid,rikisidata[karibandukejunid[i]].bandukesuuji,rikisidata[karibandukejunid[i]].bandukehigasiornisi);
						break;
					}
				}
				if (makusitaitaflag==0){
					for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU-1;i>yokodunacount+oozekicount;i--){
						if (last_bandukenameid[karibandukejunid[i]]>=5
							&& rikisidata[karibandukejunid[i]].retirekonbasho!=1
						){
							makusitaitaflag=1;
							ikisakijun=i;//代わりに十両から幕下に落ちる番付順位
//	fprintf(fpdebug,"代わりに十両から幕下に落ちるID%d win=%d 先番名=%d 先番数=%d 先番東西%d 今番名=%d 今番数=%d 今東西=%d\n",karibandukejunid[i],win[karibandukejunid[i]],last_bandukenameid[karibandukejunid[i]],last_bandukesuuji[karibandukejunid[i]],last_bandukehigasiornisi[karibandukejunid[i]],rikisidata[karibandukejunid[i]].bandukenameid,rikisidata[karibandukejunid[i]].bandukesuuji,rikisidata[karibandukejunid[i]].bandukehigasiornisi);
							break;
						}
					}
				}
				//代わりに幕下に落ちる力士がいた順位を目指して十両下位力士の番付を一つずつあげる処理
				for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU-1;i>ikisakijun;i--){
					rikisidata[karibandukejunid[i]].bandukejun=rikisidata[karibandukejunid[i-1]].bandukejun;
					rikisidata[karibandukejunid[i]].bandukenameid=rikisidata[karibandukejunid[i-1]].bandukenameid;
					rikisidata[karibandukejunid[i]].bandukesuuji=rikisidata[karibandukejunid[i-1]].bandukesuuji;
					rikisidata[karibandukejunid[i]].bandukehigasiornisi=rikisidata[karibandukejunid[i-1]].bandukehigasiornisi;
				}
				//一気に幕下に落ちてしまった力士がいた順位を目指して幕下上位力士の番付を一つずつ下げる処理
				for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<motonojun;i++){
					rikisidata[karibandukejunid[i]].bandukejun=rikisidata[karibandukejunid[i+1]].bandukejun;
					rikisidata[karibandukejunid[i]].bandukenameid=rikisidata[karibandukejunid[i+1]].bandukenameid;
					rikisidata[karibandukejunid[i]].bandukesuuji=rikisidata[karibandukejunid[i+1]].bandukesuuji;
					rikisidata[karibandukejunid[i]].bandukehigasiornisi=rikisidata[karibandukejunid[i+1]].bandukehigasiornisi;
				}
				//十両最下位に幕内から一気に幕下まで落ちてしまった力士をいれる
				rikisidata[karibandukejunid[motonojun]].bandukejun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU-1;
				rikisidata[karibandukejunid[motonojun]].bandukenameid=5;
				rikisidata[karibandukejunid[motonojun]].bandukesuuji=14;
				rikisidata[karibandukejunid[motonojun]].bandukehigasiornisi=2;
				//幕下筆頭に代わりに十両から幕下に落ちる力士を入れる
				rikisidata[karibandukejunid[ikisakijun]].bandukejun=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;
				rikisidata[karibandukejunid[ikisakijun]].bandukenameid=6;
				rikisidata[karibandukejunid[ikisakijun]].bandukesuuji=1;
				rikisidata[karibandukejunid[ikisakijun]].bandukehigasiornisi=1;
				//仮番付順をつけ直し
				for (ii=0;ii<RIKISISUU;ii++){//番付順位
					for (i=0;i<RIKISISUU;i++){//力士ＩＤ
						if (rikisidata[i].bandukejun==ii){
							karibandukejunid[ii]=i;
							break;
						}
					}
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
			}else{
				break;
			}
			if (chouseizumi[0]>100000){//無限ループ防止
				ClearDrawScreen();
				DrawString(5,369,"負け越し力士番付上昇防止処理後の理不尽に幕下まで落ちないようにする処理で困ったかも",CRWHITE);
				DrawString(187,369+16,"番付作成が難しくて困ったみたいです",CRWHITE);
				DrawString(187,369+32,"Hit Any Key",CRWHITE);
				ScreenFlip();
				WaitKey();
				break;
			}
			chouseizumi[0]++;
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
//fprintf(fpdebug,"理不尽に幕下まで落ちた力士救うための処理回数=%d\n",chouseizumi[0]);

/*for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU-5;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+5;i++){
	fprintf(fpdebug,"ID%d bandukejun%d\n",karibandukejunid[i],rikisidata[karibandukejunid[i]].bandukejun);
}*/
	}//負け越し番付指数-1じゃなければの終わり
chouseizumi[0]=0;
for (i=0;i<RIKISISUU;i++){
	if ( (rikisidata[karibandukejunid[i]].bandukenameid<last_bandukenameid[karibandukejunid[i]]
		&& win[karibandukejunid[i]]<8 && last_bandukenameid[karibandukejunid[i]]<=5)
		|| (rikisidata[karibandukejunid[i]].bandukenameid<last_bandukenameid[karibandukejunid[i]]
		&& win[karibandukejunid[i]]<4 && last_bandukenameid[karibandukejunid[i]]>5 && last_bandukenameid[karibandukejunid[i]]<9)
	){
		if (rikisidata[karibandukejunid[i]].retirekonbasho!=1){
			chouseizumi[0]++;
//fprintf(fpdebug,"%d勝なのに%s%d枚目から%s%d枚目に昇進\n",win[karibandukejunid[i]],bandukenamestring[last_bandukenameid[karibandukejunid[i]]],last_bandukesuuji[karibandukejunid[i]],bandukenamestring[rikisidata[karibandukejunid[i]].bandukenameid],rikisidata[karibandukejunid[i]].bandukesuuji);
		}
	}
}
//fprintf(fpdebug,"負け越したのに上のカテゴリーに上がった力士数=%d(序の口から序二段を除く)\n",chouseizumi[0]);

//fclose(fpdebug);
	}//ルーチンの終わり
	////負け越し力士番付上昇防止処理ここまで//////////////////////

	//力士IDごとの短縮表示用番付名作成
	for (i=0;i<RIKISISUU;i++){
		if (rikisidata[i].bandukenameid==8){
			strcpy(tanshuku_banduke[i],"二");
		}else{
			strncpy(tanshuku_banduke[i],bandukenamestring[rikisidata[i].bandukenameid],2);
			tanshuku_banduke[i][2]='\0';
		}
	}

	//番付順ごとの力士ＩＤを検索
	for (ii=0;ii<RIKISISUU;ii++){//番付順位
		for (i=0;i<RIKISISUU;i++){//力士ＩＤ
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
			heyabandukejunid[i][ii]=-1;
		}
	}
	count=0;
	for (i=0;i<HEYASUU;i++){//部屋ID
		for (ii=0;ii<RIKISISUU;ii++){//番付順ID
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
		rikisibetu_sentaku_id[i]=rikisibetu_bandukejunid[i][0];
	}

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
	for (i=0;i<RIKISISUU;i++){
		rikisibetu_sentaku_id[i]=rikisibetu_bandukejunid[i][0];
		rikisibetu_sentaku_page[i]=0;
		rikisibetu_sentaku_num[i]=0;
	}

	bandukejun_or_jiheyaflag=1;
	rikisisentaku_num_jiheya=0;
	rikisisentaku_id=heyabandukejunid[myheyaid][(rikisisentaku_num_jiheya+2)/2-1];

	
	//デバグ用
/*	FILE *fp;
	fp = fopen("debug/debug_for_bandukesakusei.csv","a");
	// オープンできなかったらここで終了
	if( fp == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		DxLib_End() ;		// ＤＸライブラリ使用の終了処理
		return  ;		// ソフトの終了
	}
	//ここから書き込み
	fprintf(fp,"年,月,力士ID,番付順位,四股名,パワー,東西,番付名,枚目,勝数,負数,仮番付ポイント\n");
	for (i=0;i<RIKISISUU;i++){//
		fprintf(fp,"%d,%d,%d,%d,%s,%d,%d,%s,%d,%d,%d,%d\n",
		year,
		month,
		i,
		rikisidata[i].bandukejun,
		namestring[rikisidata[i].nameid],
		rikisidata[i].power,
		rikisidata[i].bandukehigasiornisi,
		bandukenamestring[rikisidata[i].bandukenameid],
		rikisidata[i].bandukesuuji,
		win[i],
		lost[i],
		karibandukepoint[i]);
	}

	//クローズ
	fclose(fp);
	//デバグ用
//	FILE *fp;
	fp = fopen("debug_for_bandukesakusei_2.csv","w");
	// オープンできなかったらここで終了
	if( fp == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		DxLib_End() ;		// ＤＸライブラリ使用の終了処理
		return  ;		// ソフトの終了
	}
	//ここから書き込み
		fprintf(fp,"%d,%d,%d,%d,%d,%d,%d\n",
		pass0,
		pass1,
		pass2,
		pass3,
		pass4,
		pass5,
		pass6);

	//クローズ
	fclose(fp);
	//デバグ用
//	FILE *fp;
	fp = fopen("debug_for_bandukesakusei_3.csv","w");
	// オープンできなかったらここで終了
	if( fp == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		DxLib_End() ;		// ＤＸライブラリ使用の終了処理
		return  ;		// ソフトの終了
	}
	//ここから書き込み
	for (i=RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU;i<RIKISISUU_MAKUUTI+RIKISISUU_JYUURYOU+RIKISISUU_MAKUSITA;i++){
		fprintf(fp,"%d,%s\n",
		karibandukejunid[i],
		namestring[rikisidata[karibandukejunid[i]].nameid]);
	}

	//クローズ
	fclose(fp);*/

	//デバグ用
	//mode=1;
	//return;

if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//初期化・自己最高位更新
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (ii=0;ii<15;ii++){
			kyuujoukonbasho[i][ii]=0;
			rikisidata[i].yaowinkonbasho[ii]=0;//ver4.00で追加（それまでkyuujouバージョンでは漏れてたっぽい）
			rikisidata[i].winkonbasho[ii]=0;
			rikisidata[i].lostkonbasho[ii]=0;
			rikisidata[i].kimaritekonbasho[ii][0]='\0';
		}
		if (rikisidata[i].bandukenameid<rikisidata[i].jikosaiko_bandukenameid 
		|| (rikisidata[i].bandukenameid==rikisidata[i].jikosaiko_bandukenameid && rikisidata[i].bandukesuuji<rikisidata[i].jikosaiko_bandukesuuji)){
/*
if (rikisidata[i].bandukenameid<rikisidata[i].jikosaiko_bandukenameid){
if (rikisidata[i].bandukenameid==2){
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"新関脇　%s部屋の%s(%d才)\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
}else if (rikisidata[i].bandukenameid==3){
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"新小結　%s部屋の%s(%d才)\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
}else if (rikisidata[i].bandukenameid==4){
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"新入幕　%s部屋の%s(%d才)\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
}else if (rikisidata[i].bandukenameid==5){
//eventlog書き込み/////////////////////////////////////////
fp = fopen("data/eventlog.txt","a");
// オープンできなかったらここで終了
if( fp == NULL ){ClearDrawScreen() ;DrawString( 250 , 240 - 32 , "eventlog.txtファイルオープンに失敗" , GetColor(255,255,255) );DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );ScreenFlip() ;	WaitKey();	DxLib_End() ;return  ;}
fprintf(fp,"新十両　%s部屋の%s(%d才)\n",
heyastring[rikisidata[i].heyaid],
namestring[i],
rikisidata[i].age);
//クローズ
fclose(fp);
if( ProcessMessage() == -1 ){mode=1;return ;}
////////////////////////////////////////////////////////////
}
}
*/
		 	rikisidata[i].jikosaiko_bandukenameid=rikisidata[i].bandukenameid;
			rikisidata[i].jikosaiko_bandukesuuji=rikisidata[i].bandukesuuji;
		}
		rikisidata[i].retirekonbasho=0;
		rikisidata[i].oozekiyuushouorjunyuushou[2]=rikisidata[i].oozekiyuushouorjunyuushou[1];
		rikisidata[i].oozekiyuushouorjunyuushou[1]=rikisidata[i].oozekiyuushouorjunyuushou[0];
		rikisidata[i].oozekiyuushouorjunyuushou[0]=0;
		rikisidata[i].sanyakuwin[2]=rikisidata[i].sanyakuwin[1];
		rikisidata[i].sanyakuwin[1]=rikisidata[i].sanyakuwin[0];
		rikisidata[i].sanyakuwin[0]=0;
		rikisidata[i].kinbosisuu_konbasho=0;
		rikisidata[i].ginbosisuu_konbasho=0;
	}
	//部屋最高位更新
	for (i=0;i<HEYASUU;i++){
		if (heyadata[i].jikosaiko_bandukenameid>rikisidata[heyabandukejunid[i][0]].bandukenameid){
		 	heyadata[i].jikosaiko_bandukenameid=rikisidata[heyabandukejunid[i][0]].bandukenameid;
			heyadata[i].jikosaiko_bandukesuuji=rikisidata[heyabandukejunid[i][0]].bandukesuuji;
			if (i==myheyaid && (skipmode!=2 ||  (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month)) ){///////////////////////////////
				ClearDrawScreen();
				DrawBox(0,0,639,479,CRBACK,TRUE);
				game_main_backscreen();
				DrawString(187,369,"おめでとうございます！",CRWHITE);
				DrawString(187,459,"Hit any key",CRWHITE);
				if (heyadata[i].jikosaiko_bandukenameid>5){
					if (superrikisisuu[2]!=2){
						DrawFormatString(187,369+16,CRWHITE,"%s部屋初の%s力士の誕生です。",heyastring[myheyaid],bandukenamestring[heyadata[i].jikosaiko_bandukenameid]);
					}
					DrawFormatString(187,369+16+16,CRWHITE,"%sの%sへの昇進が決定しました。",namestring[heyabandukejunid[myheyaid][0]],bandukenamestring[heyadata[i].jikosaiko_bandukenameid]);
				}else if (heyadata[i].jikosaiko_bandukenameid>4){
					if (superrikisisuu[2]!=2){
						DrawFormatString(187,369+16,CRWHITE,"%s部屋初の関取の誕生です。",heyastring[myheyaid]);
					}
					DrawFormatString(187,369+16+16,CRWHITE,"%sの%sへの昇進が決定しました。",namestring[heyabandukejunid[myheyaid][0]],bandukenamestring[heyadata[i].jikosaiko_bandukenameid]);
				}else if (heyadata[i].jikosaiko_bandukenameid>3){
					if (superrikisisuu[2]!=2){
						DrawFormatString(187,369+16,CRWHITE,"%s部屋初の幕内力士の誕生です。",heyastring[myheyaid]);
					}
					DrawFormatString(187,369+16+16,CRWHITE,"%sの%s%d枚目への昇進が決定しました。",namestring[heyabandukejunid[myheyaid][0]],bandukenamestring[heyadata[i].jikosaiko_bandukenameid],rikisidata[heyabandukejunid[myheyaid][0]].bandukesuuji);
				}else if (heyadata[i].jikosaiko_bandukenameid>2){
					if (superrikisisuu[2]!=2){
						DrawFormatString(187,369+16,CRWHITE,"%s部屋初の三役力士の誕生です。",heyastring[myheyaid]);
					}
					DrawFormatString(187,369+16+16,CRWHITE,"%sの%sへの昇進が決定しました。",namestring[heyabandukejunid[myheyaid][0]],bandukenamestring[heyadata[i].jikosaiko_bandukenameid]);
				}else if (heyadata[i].jikosaiko_bandukenameid>1){
					if (superrikisisuu[2]!=2){
						DrawFormatString(187,369+16,CRWHITE,"%s部屋初の関脇の誕生です。",heyastring[myheyaid]);
					}
					DrawFormatString(187,369+16+16,CRWHITE,"%sの%sへの昇進が決定しました。",namestring[heyabandukejunid[myheyaid][0]],bandukenamestring[heyadata[i].jikosaiko_bandukenameid]);
				}else if (heyadata[i].jikosaiko_bandukenameid>0){
					if (superrikisisuu[2]!=2){
						DrawFormatString(187,369+16,CRWHITE,"%s部屋初の大関の誕生です。",heyastring[myheyaid]);
					}
					DrawFormatString(187,369+16+16,CRWHITE,"%sの%sへの昇進が決定しました。",namestring[heyabandukejunid[myheyaid][0]],bandukenamestring[heyadata[i].jikosaiko_bandukenameid]);
				}else{
					DrawString(187,369+16,"ついにやりました！！",CRWHITE);
					if (superrikisisuu[2]!=2){
						DrawFormatString(187,369+16+16,CRWHITE,"%s部屋初の横綱誕生です。",heyastring[myheyaid]);
					}
					DrawFormatString(187,369+16+16+16,CRWHITE,"%sの%sへの昇進が決定しました。",namestring[heyabandukejunid[myheyaid][0]],bandukenamestring[heyadata[i].jikosaiko_bandukenameid]);
					DrawString(187,369+16+16+16+16,"歴史に残る大横綱を目指してください。",CRWHITE);
				}
				ScreenFlip();
				WaitKey();
			}
		}else if((heyadata[i].jikosaiko_bandukenameid==rikisidata[heyabandukejunid[i][0]].bandukenameid && heyadata[i].jikosaiko_bandukesuuji>rikisidata[heyabandukejunid[i][0]].bandukesuuji)){
		 	heyadata[i].jikosaiko_bandukenameid=rikisidata[heyabandukejunid[i][0]].bandukenameid;
			heyadata[i].jikosaiko_bandukesuuji=rikisidata[heyabandukejunid[i][0]].bandukesuuji;
		}
	}

	//番付表示準備
	banduke_hyojijunbi();

	return;
}

void torikumichange_kyuujou(void)
{
	int temp=0;
	int i=0;
	int ii=0;
	int iii=0;
	int dameflag=0;
	int temp_aite_kai=0;
	int temp_aite_joui=0;
	int win[RIKISISUU_MAKUUTI];
	int banwin_makuuti[RIKISISUU_MAKUUTI];//
	int winjun_makuuti[RIKISISUU_MAKUUTI];//幕内の勝ち星順の番付順
	int winjunb[RIKISISUU_MAKUUTI];//勝ち星順の番付順位
	int winjunid[RIKISISUU_MAKUUTI];//勝ち星順のID
	char konkaihenkouzumiflag[RIKISISUU];//同じ日で何回も同じ相手が変更させられないように[]は回と対戦させられる上位力士のID

	for (i=0;i<RIKISISUU;i++){
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		konkaihenkouzumiflag[i]=0;
	}
	temp_aite_kai=-1;
	temp_aite_joui=-1;
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		win[i]=0;
		winjunb[i]=0;
		winjunid[i]=0;
		banwin_makuuti[i]=0;
		winjun_makuuti[i]=0;
	}
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		for (ii=0;ii<15;ii++){
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
				banwin_makuuti[i]++;
				win[i]++;
			}
		}
	}
	//バブルソート
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjun_makuuti[i]=i;
	}
	for (i = 0;i < RIKISISUU_MAKUUTI - 1;i++) {
		for (ii = 0;ii < RIKISISUU_MAKUUTI - 1;ii++) {
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (banwin_makuuti[ii + 1] > banwin_makuuti[ii]) {
				temp = banwin_makuuti[ii];
				banwin_makuuti[ii] = banwin_makuuti[ii + 1];
				banwin_makuuti[ii + 1] = temp;
				temp = winjun_makuuti[ii];
				winjun_makuuti[ii] = winjun_makuuti[ii+1];
				winjun_makuuti[ii+1] = temp;
			}
		}
		Sleep(1);
		if( ProcessMessage() == -1 )
		{
			mode=1;
			return ;	// エラーが起きたらループから抜ける
		}
	}
	//IDへ変換
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		winjunb[i]=winjun_makuuti[i];
		winjunid[i]=bandukejunid[winjun_makuuti[i]];
	}

	for (i=RIKISISUU_MAKUUTI-1;i>=16;i--){
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

//ClearDrawScreen();
//DrawString(0,0,"ここまでOK",CRWHITE);
//DrawFormatString(0,32,CRWHITE,"%s win[i]%d win[winjunb[0]]%d",namestring[bandukejunid[i]],win[i],win[winjunb[0]]);
//ScreenFlip();
//WaitKey();

		//2差以内で9勝以上していたら(千秋楽は変えない)
		if ( (day-11<warihen_nannitimemade && win[i]+warihen_toptonosa>=win[winjunb[0]] && win[i]>=warihen_shourisuu) 
		&& kyuujouflag[bandukejunid[i]]!=1){
/*
ClearDrawScreen();
DrawString(0,0,"ここまでOK",CRWHITE);
DrawFormatString(0,32,CRWHITE,"%s の取組変更",namestring[bandukejunid[i]]);
ScreenFlip();
WaitKey();
*/
			for (ii=8;ii>=0;ii--){//番付上位9番以内とやらせる
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (kainoaitesitayosuu[ii]<=1){
					dameflag=0;
					if (konkaihenkouzumiflag[bandukejunid[ii]]==1){
						dameflag=1;
					}else if (rikisidata[bandukejunid[i]].rikisibetu_wintotal[bandukejunid[ii]]>rikisidata[bandukejunid[i]].rikisibetu_losttotal[bandukejunid[ii]]){
						dameflag=1;
					}else if (rikisidata[bandukejunid[i]].heyaid==rikisidata[bandukejunid[ii]].heyaid){
						dameflag=1;
					}else if(kyuujouflag[bandukejunid[ii]]==1){
						dameflag=1;
					}else{
						for (iii=0;iii<15;iii++){
							if (rikisidata[bandukejunid[i]].aitekonbasho[iii]==bandukejunid[ii] 
							  || rikisidata[bandukejunid[ii]].aitekonbasho[iii]==bandukejunid[i]){
								dameflag=1;
								break;
							 }
						}
					}
					if (dameflag!=1){
/*
ClearDrawScreen();
DrawString(0,0,"ここまでOK",CRWHITE);
DrawFormatString(0,32,CRWHITE,"%s の取組相手は%s",namestring[bandukejunid[i]],namestring[bandukejunid[ii]]);
ScreenFlip();
WaitKey();
*/
						konkaihenkouzumiflag[bandukejunid[ii]]=1;
						rikisidata[bandukejunid[i]].aitekonbasho[day-11]=bandukejunid[ii];
						rikisidata[bandukejunid[ii]].aitekonbasho[day-11]=bandukejunid[i];
						aite[i][day-11]=ii;
						aite[ii][day-11]=i;
						kainoaitesitayosuu[ii]++;
						break;
					}
				}
			}

			if (dameflag==1){
				for (ii=3;ii>=0;ii--){//番付上位4番以内とやらせる
					if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
					if (kainoaitesitayosuu[ii]<=1){
						dameflag=0;
						if (konkaihenkouzumiflag[bandukejunid[ii]]==1){
							dameflag=1;
						//}else if (rikisidata[bandukejunid[i]].rikisibetu_wintotal[bandukejunid[ii]]>rikisidata[bandukejunid[i]].rikisibetu_losttotal[bandukejunid[ii]]){
						//	dameflag=1;
						}else if (rikisidata[bandukejunid[i]].heyaid==rikisidata[bandukejunid[ii]].heyaid){
							dameflag=1;
						}else if(kyuujouflag[bandukejunid[ii]]==1){
							dameflag=1;
						}else{
							for (iii=0;iii<15;iii++){
								if (rikisidata[bandukejunid[i]].aitekonbasho[iii]==bandukejunid[ii] 
								  || rikisidata[bandukejunid[ii]].aitekonbasho[iii]==bandukejunid[i]){
									dameflag=1;
									break;
								 }
							}
						}
						if (dameflag!=1){
	/*
	ClearDrawScreen();
	DrawString(0,0,"ここまでOK",CRWHITE);
	DrawFormatString(0,32,CRWHITE,"%s の取組相手は%s",namestring[bandukejunid[i]],namestring[bandukejunid[ii]]);
	ScreenFlip();
	WaitKey();
	*/
							konkaihenkouzumiflag[bandukejunid[ii]]=1;
							rikisidata[bandukejunid[i]].aitekonbasho[day-11]=bandukejunid[ii];
							rikisidata[bandukejunid[ii]].aitekonbasho[day-11]=bandukejunid[i];
							aite[i][day-11]=ii;
							aite[ii][day-11]=i;
							kainoaitesitayosuu[ii]++;
							break;
						}
					}
				}
			}
		}
	}
			
			
	return;
}



/*
void torikumichange_kyuujou(void)
{
	int temp=0;
	int i=0;
	int ii=0;
	int iii=0;
	int dameflag=0;
	int temp_aite_kai=0;
	int temp_aite_joui=0;
	int win[RIKISISUU_MAKUUTI];
	int banwin_makuuti[RIKISISUU_MAKUUTI];//
	int winjun_makuuti[RIKISISUU_MAKUUTI];//幕内の勝ち星順の番付順
	int winjunb[RIKISISUU_MAKUUTI];//勝ち星順の番付順位
	int winjunid[RIKISISUU_MAKUUTI];//勝ち星順のID
	char konkaihenkouzumiflag[RIKISISUU];//同じ日で何回も同じ相手が変更させられないように[]は回と対戦させられる上位力士のID

	for (i=0;i<RIKISISUU;i++){
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		konkaihenkouzumiflag[i]=0;
	}
	temp_aite_kai=-1;
	temp_aite_joui=-1;
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		win[i]=0;
		winjunb[i]=0;
		winjunid[i]=0;
		banwin_makuuti[i]=0;
		winjun_makuuti[i]=0;
	}
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		for (ii=0;ii<15;ii++){
			if (rikisidata[bandukejunid[i]].winkonbasho[ii]==1){
				banwin_makuuti[i]++;
				win[i]++;
			}
		}
	}
	//バブルソート
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		winjun_makuuti[i]=i;
	}
	for (i = 0;i < RIKISISUU_MAKUUTI - 1;i++) {
		for (ii = 0;ii < RIKISISUU_MAKUUTI - 1;ii++) {
			if (banwin_makuuti[ii + 1] > banwin_makuuti[ii]) {
				temp = banwin_makuuti[ii];
				banwin_makuuti[ii] = banwin_makuuti[ii + 1];
				banwin_makuuti[ii + 1] = temp;
				temp = winjun_makuuti[ii];
				winjun_makuuti[ii] = winjun_makuuti[ii+1];
				winjun_makuuti[ii+1] = temp;
			}
		}
		Sleep(1);
		if( ProcessMessage() == -1 )
		{
			mode=1;
			return ;	// エラーが起きたらループから抜ける
		}
	}
	//IDへ変換
	for (i=0;i<RIKISISUU_MAKUUTI;i++){
		winjunb[i]=winjun_makuuti[i];
		winjunid[i]=bandukejunid[winjun_makuuti[i]];
	}

	for (i=RIKISISUU_MAKUUTI-1;i>=16;i--){


		//2差以内で勝ち越していたら(千秋楽は変えない)
		if ( (day-11<14 && win[i]+2>=win[winjunb[0]] && win[i]>=8) 
		&& kyuujouflag[bandukejunid[i]]!=1){
			for (ii=8;ii>=0;ii--){//番付上位9番以内とやらせる
				if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (kainoaitesitayosuu[ii]<=1){
					temp_aite_kai=rikisidata[bandukejunid[i]].aitekonbasho[day-11];
					temp_aite_joui=rikisidata[bandukejunid[ii]].aitekonbasho[day-11];
					dameflag=0;
					if (rikisidata[temp_aite_kai].heyaid==rikisidata[temp_aite_joui].heyaid){
						dameflag=1;
					}else if (konkaihenkouzumiflag[bandukejunid[ii]]==1){
						dameflag=1;
					}else if (rikisidata[bandukejunid[i]].rikisibetu_wintotal[bandukejunid[ii]]>rikisidata[bandukejunid[i]].rikisibetu_losttotal[bandukejunid[ii]]){
						dameflag=1;
					}else if (rikisidata[bandukejunid[i]].heyaid==rikisidata[bandukejunid[ii]].heyaid){
						dameflag=1;
					}else if (rikisidata[temp_aite_joui].bandukejun<ii){
						dameflag=1;
					}else if (makizoedejouinoaitesitayosuu[rikisidata[temp_aite_kai].bandukejun]>0){
						dameflag=1;
					}else if(kyuujouflag[bandukejunid[ii]]==1
							|| kyuujouflag[temp_aite_kai]==1
							|| kyuujouflag[temp_aite_joui]==1){
						dameflag=1;
					}else{
						for (iii=0;iii<15;iii++){
							if (rikisidata[bandukejunid[i]].aitekonbasho[iii]==bandukejunid[ii] 
							  || rikisidata[bandukejunid[ii]].aitekonbasho[iii]==bandukejunid[i]
							  || rikisidata[temp_aite_kai].aitekonbasho[iii]==temp_aite_joui
							  || rikisidata[temp_aite_joui].aitekonbasho[iii]==temp_aite_kai){
								dameflag=1;
								break;
							 }
						}
					}
					if (dameflag!=1){
						konkaihenkouzumiflag[bandukejunid[ii]]=1;
						rikisidata[bandukejunid[i]].aitekonbasho[day-11]=bandukejunid[ii];
						//rikisidata[bandukejunid[i]].torikumijun[day-11]=rikisidata[bandukejunid[ii].torikumijun[day-11];
						rikisidata[bandukejunid[ii]].aitekonbasho[day-11]=bandukejunid[i];
						//rikisidata[temp_aite_joui].torikumijun[day-11]=rikisidata[temp_aite_kai].torikumijun[day-11];
						rikisidata[temp_aite_kai].aitekonbasho[day-11]=temp_aite_joui;
						rikisidata[temp_aite_joui].aitekonbasho[day-11]=temp_aite_kai;
						makizoedejouinoaitesitayosuu[temp_aite_kai]++;
						kainoaitesitayosuu[ii]++;
						if (rikisidata[temp_aite_joui].bandukejun<=8){
							kainoaitesitayosuu[rikisidata[temp_aite_joui].bandukejun]++;
						}
						break;
					}
				}
			}
		}
	}
			
			
	return;
}
*/


void kyuujou(void){
	
	int i;
	int temp_kyuujousuu_category[10];//0→横綱、9→序の口
	char okflag=0;
	for (i=0;i<10;i++){
		temp_kyuujousuu_category[i]=0;
	}
	//休場者リセット
	for (i=0;i<RIKISISUU;i++){
		kyuujouflag[i]=0;
		//if( ProcessMessage() == -1 ){mode=1;return ;}
	}
	for (i=0;i<RIKISISUU;i++){
		okflag=0;
		if (rikisidata[i].bandukenameid<=4){
			if ((temp_kyuujousuu_category[0]+temp_kyuujousuu_category[1]+temp_kyuujousuu_category[2]+temp_kyuujousuu_category[3]+temp_kyuujousuu_category[4])<kyuujousuu_max_category){
				okflag=1;
			}
		}else{
			if (temp_kyuujousuu_category[rikisidata[i].bandukenameid]<kyuujousuu_max_category){
				okflag=1;
			}
		} 
		if (okflag==1){
			if (GetRand( 999 )<kyuujou_zenkyuu_ritu){
				kyuujouflag[i]=1;
				temp_kyuujousuu_category[rikisidata[i].bandukenameid]++;
				if (GetRand(999)==0){
					strcpy(kyuujoustring[i],kegastring[0]);
				}else if (GetRand(199)==0){
					strcpy(kyuujoustring[i],kegastring[1]);
				}else{
					strcpy(kyuujoustring[i],kegastring[GetRand(17)+2]);
				}
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}
	}

	return;
}

void kyuujou_tochuu(void){
	//day-11は0が初日、14が千秋楽
	//このルーチンは当日の取組作成ルーチンの直前のはず（このゲームでは取組作成を当日に行っている）
	//なので、初日のみ終わった状態で考える場合、day-11は1のはず
	//要するに直前である前日の取組は[day-11-1]
	int i,ii;
	int win[RIKISISUU];
	int lost[RIKISISUU];
	int temp_kyuujousuu_category[10];//0→横綱、9→序の口
	char okflag=0;

	if ((day-11)<=1){return;}

	for (i=0;i<10;i++){
		temp_kyuujousuu_category[i]=0;
	}
	for (i=0;i<RIKISISUU;i++){
		win[i]=0;
		lost[i]=0;
	}
	//力士IDごとの今場所の成績検索
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		for (ii=0;ii<15;ii++){
			if (rikisidata[i].winkonbasho[ii]==1){
				win[i]++;
			}else if (rikisidata[i].lostkonbasho[ii]==1){
				lost[i]++;
			}
		}
	}
	//カテゴリーごとの休場者数カウント
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (kyuujouflag[i]==1){
			temp_kyuujousuu_category[rikisidata[i].bandukenameid]++;
		}
	}
	for (i=0;i<RIKISISUU;i++){
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		okflag=0;
		if (rikisidata[i].bandukenameid<=4){
			if ((temp_kyuujousuu_category[0]+temp_kyuujousuu_category[1]+temp_kyuujousuu_category[2]+temp_kyuujousuu_category[3]+temp_kyuujousuu_category[4])<kyuujousuu_max_category){
				okflag=1;
			}
		}else{
			if (temp_kyuujousuu_category[rikisidata[i].bandukenameid]<kyuujousuu_max_category){
				okflag=1;
			}
		} 
		if (okflag==1){
			//横綱の場合
			if (rikisidata[i].bandukenameid==0 && kyuujouflag[i]!=1){
				//11日目までで4連敗で50%休場
				if ((day-11)>3
				&& (day-11)<=kyuujou_yokoduna1_day
				&& GetRand(99)<kyuujou_yokoduna1_ritu
				&& rikisidata[i].lostkonbasho[day-11-1]==1
				&& rikisidata[i].lostkonbasho[day-11-2]==1
				&& rikisidata[i].lostkonbasho[day-11-3]==1
				&& rikisidata[i].lostkonbasho[day-11-4]==1
				){
					kyuujouflag[i]=1;
					temp_kyuujousuu_category[rikisidata[i].bandukenameid]++;
					strcpy(kyuujoustring[i],kegastring[GetRand(17)+2]);
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋の%sが%sのため途中休場",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	kyuujoustring[i]);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString( 250 , 272 - 32 , "しばらくお待ちください" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	if( ProcessMessage() == -1 ){mode=1;return ;}
	}
	//////////////////////////////////////////////////////////////
				//10日目までで3連敗で25%休場
				}else if ((day-11)>2
				&& (day-11)<=kyuujou_yokoduna2_day
				&& GetRand(99)<kyuujou_yokoduna2_ritu
				&& rikisidata[i].lostkonbasho[day-11-1]==1
				&& rikisidata[i].lostkonbasho[day-11-2]==1
				&& rikisidata[i].lostkonbasho[day-11-3]==1
				){
					kyuujouflag[i]=1;
					temp_kyuujousuu_category[rikisidata[i].bandukenameid]++;
					strcpy(kyuujoustring[i],kegastring[GetRand(17)+2]);
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋の%sが%sのため途中休場",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	kyuujoustring[i]);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString( 250 , 272 - 32 , "しばらくお待ちください" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	if( ProcessMessage() == -1 ){mode=1;return ;}
	}
	//////////////////////////////////////////////////////////////
				//11日目までで7日目以降で負け先行で前日負けなら30%休場
				}else if ((day-11)>=kyuujou_yokoduna3_day2
				&& (day-11)<=kyuujou_yokoduna3_day
				&& GetRand(99)<kyuujou_yokoduna3_ritu
				&& rikisidata[i].lostkonbasho[day-11-1]==1
				&& lost[i]>win[i]
				){
					kyuujouflag[i]=1;
					temp_kyuujousuu_category[rikisidata[i].bandukenameid]++;
					strcpy(kyuujoustring[i],kegastring[GetRand(17)+2]);
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋の%sが%sのため途中休場",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	kyuujoustring[i]);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString( 250 , 272 - 32 , "しばらくお待ちください" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	if( ProcessMessage() == -1 ){mode=1;return ;}
	}
	//////////////////////////////////////////////////////////////
				//13日目までで6敗以上で前日負けなら30%休場
				}else if ((day-11)>5
				&& (day-11)<=kyuujou_yokoduna4_day
				&& GetRand(99)<kyuujou_yokoduna4_ritu
				&& rikisidata[i].lostkonbasho[day-11-1]==1
				&& lost[i]>=kyuujou_yokoduna4_lostsuu
				){
					kyuujouflag[i]=1;
					temp_kyuujousuu_category[rikisidata[i].bandukenameid]++;
					strcpy(kyuujoustring[i],kegastring[GetRand(17)+2]);
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋の%sが%sのため途中休場",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	kyuujoustring[i]);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString( 250 , 272 - 32 , "しばらくお待ちください" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	if( ProcessMessage() == -1 ){mode=1;return ;}
	}
	//////////////////////////////////////////////////////////////
				}
			}
			//大関の場合
			if (rikisidata[i].bandukenameid==1 && kyuujouflag[i]!=1){
				//カド番でなければ10日目までで4連敗で20%休場
				if ((day-11)>3
				&& (day-11)<=kyuujou_oozeki1_day
				&& rikisidata[i].kadobanflag!=1
				&& GetRand(99)<kyuujou_oozeki1_ritu
				&& rikisidata[i].lostkonbasho[day-11-1]==1
				&& rikisidata[i].lostkonbasho[day-11-2]==1
				&& rikisidata[i].lostkonbasho[day-11-3]==1
				&& rikisidata[i].lostkonbasho[day-11-4]==1
				){
					kyuujouflag[i]=1;
					temp_kyuujousuu_category[rikisidata[i].bandukenameid]++;
					strcpy(kyuujoustring[i],kegastring[GetRand(17)+2]);
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋の%sが%sのため途中休場",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	kyuujoustring[i]);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString( 250 , 272 - 32 , "しばらくお待ちください" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	if( ProcessMessage() == -1 ){mode=1;return ;}
	}
	//////////////////////////////////////////////////////////////
				//カド番でなければ10日目までで3連敗で10%休場
				}else if ((day-11)>2
				&& (day-11)<=kyuujou_oozeki2_day
				&& rikisidata[i].kadobanflag!=1
				&& GetRand(99)<kyuujou_oozeki2_ritu
				&& rikisidata[i].lostkonbasho[day-11-1]==1
				&& rikisidata[i].lostkonbasho[day-11-2]==1
				&& rikisidata[i].lostkonbasho[day-11-3]==1
				){
					kyuujouflag[i]=1;
					temp_kyuujousuu_category[rikisidata[i].bandukenameid]++;
					strcpy(kyuujoustring[i],kegastring[GetRand(17)+2]);
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋の%sが%sのため途中休場",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	kyuujoustring[i]);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString( 250 , 272 - 32 , "しばらくお待ちください" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	if( ProcessMessage() == -1 ){mode=1;return ;}
	}
	//////////////////////////////////////////////////////////////
				}
			}
			//十両以上全力士
			if (rikisidata[i].bandukenameid<=5 && kyuujouflag[i]!=1){
				//10日目までで3連敗で3%休場
				if ((day-11)>2
				&& (day-11)<=kyuujou_sekitori1_day
				&& GetRand(99)<kyuujou_sekitori1_ritu
				&& rikisidata[i].lostkonbasho[day-11-1]==1
				&& rikisidata[i].lostkonbasho[day-11-2]==1
				&& rikisidata[i].lostkonbasho[day-11-3]==1
				){
					kyuujouflag[i]=1;
					temp_kyuujousuu_category[rikisidata[i].bandukenameid]++;
					strcpy(kyuujoustring[i],kegastring[GetRand(17)+2]);
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋の%sが%sのため途中休場",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	kyuujoustring[i]);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString( 250 , 272 - 32 , "しばらくお待ちください" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	if( ProcessMessage() == -1 ){mode=1;return ;}
	}
	//////////////////////////////////////////////////////////////
				//10日目までで4連敗で4%休場
				}else if ((day-11)>3
				&& (day-11)<=kyuujou_sekitori2_day
				&& GetRand(99)<kyuujou_sekitori2_ritu
				&& rikisidata[i].lostkonbasho[day-11-1]==1
				&& rikisidata[i].lostkonbasho[day-11-2]==1
				&& rikisidata[i].lostkonbasho[day-11-3]==1
				&& rikisidata[i].lostkonbasho[day-11-4]==1
				){
					kyuujouflag[i]=1;
					temp_kyuujousuu_category[rikisidata[i].bandukenameid]++;
					strcpy(kyuujoustring[i],kegastring[GetRand(17)+2]);
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋の%sが%sのため途中休場",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	kyuujoustring[i]);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString( 250 , 272 - 32 , "しばらくお待ちください" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	if( ProcessMessage() == -1 ){mode=1;return ;}
	}
	//////////////////////////////////////////////////////////////
				}
			}
			//全力士
			//前日負けただけで0.2%休場
			if ((day-11)>0
			&& kyuujouflag[i]!=1
			&& GetRand(999)<kyuujou_all_ritu
			&& rikisidata[i].lostkonbasho[day-11-1]==1
			){
				kyuujouflag[i]=1;
				temp_kyuujousuu_category[rikisidata[i].bandukenameid]++;
				strcpy(kyuujoustring[i],kegastring[GetRand(17)+2]);
	////////////////////////////////////////////////////////////
	if (skipmode!=2 || (skipmode==2 && skipyear<year) || (skipmode==2 && skipyear==year && skipmonth<=month) ){///////////////////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(0,369,CRWHITE,"%s部屋の%sが%sのため途中休場",
	heyastring[rikisidata[i].heyaid],
	namestring[i],
	kyuujoustring[i]);
	DrawString( 250 , 272 - 32 , "Hit any key" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	WaitKey();
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawString( 250 , 272 - 32 , "しばらくお待ちください" , CRWHITE);
	ScreenFlip() ;//裏画面を表画面にコピー
	if( ProcessMessage() == -1 ){mode=1;return ;}
	}
	//////////////////////////////////////////////////////////////
			}
		}
	}

	return;
}

void kyuujouhyoji(int x)//現役力士の休場履歴表示
{
	char temp_filename[MAX_PATH];
	int temp_rikisiid=0;
	int temp_year=0;
	int temp_month=0;
	char temp_bandukenameid=0;
	char temp_bandukesuuji=0;
	int temp_yasumi=0;
	char temp_kyuujoustring[21];
	int gyousuu=0;
	int gyousuu_max=0;

	strcpy(temp_filename,"\0");
	strcpy(temp_kyuujoustring,"\0");

	gyousuu_max=15;
	FILE *fp;
loop:
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	game_main_backscreen();//基本画面表示
	DrawFormatString(240,24,CRWHITE,
			"%sの休場履歴",
			namestring[x]
			);

	sprintf(temp_filename,"data/dat/kyuujou%d.dat\0",x);
	fp = fopen(temp_filename,"rb");
	gyousuu=0;
	while(1){
		if( fp == NULL ){
			//ここにエラー処理
			ClearDrawScreen();
			DrawFormatString(187,369,CRWHITE,"%sのオープン失敗",temp_filename);
			ScreenFlip();
			WaitKey();
			mode=1;return ;
		}else{
			if (fread(&temp_rikisiid,sizeof(int),1,fp)<1){
				break;
			}
			fread(&temp_year,sizeof(int),1,fp);
			fread(&temp_month,sizeof(int),1,fp);
			fread(&temp_bandukenameid,sizeof(char),1,fp);
			fread(&temp_bandukesuuji,sizeof(char),1,fp);
			fread(&temp_yasumi,sizeof(int),1,fp);
			fread(temp_kyuujoustring,sizeof(temp_kyuujoustring),1,fp);
		}
		//ここから表示
		if (gyousuu<(page_kyuujou+1)*gyousuu_max && gyousuu>=page_kyuujou*gyousuu_max){
			if (temp_bandukesuuji!=0){
				DrawFormatString(187,44+(gyousuu%gyousuu_max)*16,CRWHITE,
				"%d年%d月 %s%d %d休 %s",
				temp_year,temp_month,
				bandukenamestring[temp_bandukenameid],temp_bandukesuuji,
				temp_yasumi,temp_kyuujoustring
				);
			}else{
				DrawFormatString(187,44+(gyousuu%gyousuu_max)*16,CRWHITE,
				"%d年%d月 %s %d休 %s",
				temp_year,temp_month,
				bandukenamestring[temp_bandukenameid],
				temp_yasumi,temp_kyuujoustring
				);
			}
		}
		gyousuu++;
	}
	fclose(fp);

	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	DrawFormatString(200,170+12*15,CRGREEN,"前頁　%dページ　次頁",page_kyuujou+1);

	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	DrawString(x1[0],y1[0],"戻る",CRGREEN);

	ScreenFlip() ;//裏画面を表画面にコピー
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		if (get_mouseclick(200,170+12*15,200+32,170+12*15+16)==1 ){
			if (page_kyuujou>0){
				page_kyuujou--;
			}
			WaitTimer(200);
			goto loop;
		}
		if (get_mouseclick(328,170+12*15,328+32,170+12*15+16)==1 ){
			if (page_kyuujou<99){
				page_kyuujou++;
			}
			WaitTimer(200);
			goto loop;
		}

		if (get_mouseclick_list(0) == 1 || get_mouseclick_list(1)==1 ){
			return;
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

void kyuujoushousaisettei_hyoji(void){
	ClearDrawScreen();
	DrawBox(0,0,639,479,CRBACK,TRUE);
	DrawBox(0,0,640,480,CRLINE,TRUE);//大枠描画
	DrawBox(3,3,637,477,CRBACK,TRUE);
	DrawBox(0,21,187,480,CRLINE,TRUE);
	DrawBox(3,24,184,477,CRBACK,TRUE);
	DrawBox(184,21,640,420,CRLINE,TRUE);
	DrawBox(187,24,637,417,CRBACK,TRUE);
	DrawBox(184,417,640,480,CRLINE,TRUE);
	DrawBox(187,420,637,477,CRBACK,TRUE);
	DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分
	DrawBox(3,76,183,475,CRTAB,TRUE);
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	SetFontSize(12);
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	DrawString(100,6,"　　　　　　　休場条件設定画面",CRWHITE);
	DrawString(187,40,"全休の確率",CRWHITE);
	DrawFormatString(187,55,CRGREEN,"%d/1000",kyuujou_zenkyuu_ritu);
	DrawString(187,80,"横綱のみ適用",CRWHITE);
	DrawFormatString(200,95,CRGREEN,"%d日目までで",kyuujou_yokoduna1_day);
	DrawString(290,95,"4連敗で",CRWHITE);
	DrawFormatString(340,95,CRGREEN,"%d/100",kyuujou_yokoduna1_ritu);
	DrawFormatString(200,110,CRGREEN,"%d日目までで",kyuujou_yokoduna2_day);
	DrawString(290,110,"3連敗で",CRWHITE);
	DrawFormatString(340,110,CRGREEN,"%d/100",kyuujou_yokoduna2_ritu);
	DrawFormatString(200,125,CRGREEN,"%d日目以降",kyuujou_yokoduna3_day2);
	DrawFormatString(270,125,CRGREEN,"%d日目までで",kyuujou_yokoduna3_day);
	DrawString(360,125,"黒星先行で前日負けで",CRWHITE);
	DrawFormatString(500,125,CRGREEN,"%d/100",kyuujou_yokoduna3_ritu);
	DrawFormatString(200,140,CRGREEN,"%d日目までで",kyuujou_yokoduna4_day);
	DrawFormatString(290,140,CRGREEN,"%d敗以上で",kyuujou_yokoduna4_lostsuu);
	DrawString(350,140,"前日負けで",CRWHITE);
	DrawFormatString(420,140,CRGREEN,"%d/100",kyuujou_yokoduna4_ritu);
	DrawString(187,155,"カド番でない大関のみ適用",CRWHITE);
	DrawFormatString(200,170,CRGREEN,"%d日目までで",kyuujou_oozeki1_day);
	DrawString(290,170,"4連敗で",CRWHITE);
	DrawFormatString(340,170,CRGREEN,"%d/100",kyuujou_oozeki1_ritu);
	DrawFormatString(200,185,CRGREEN,"%d日目までで",kyuujou_oozeki2_day);
	DrawString(290,185,"3連敗で",CRWHITE);
	DrawFormatString(340,185,CRGREEN,"%d/100",kyuujou_oozeki2_ritu);
	DrawString(187,200,"十両以上全力士に適用",CRWHITE);
	DrawFormatString(200,215,CRGREEN,"%d日目までで",kyuujou_sekitori1_day);
	DrawString(290,215,"4連敗で",CRWHITE);
	DrawFormatString(340,215,CRGREEN,"%d/100",kyuujou_sekitori1_ritu);
	DrawFormatString(200,230,CRGREEN,"%d日目までで",kyuujou_sekitori2_day);
	DrawString(290,230,"3連敗で",CRWHITE);
	DrawFormatString(340,230,CRGREEN,"%d/100",kyuujou_sekitori2_ritu);
	DrawString(187,245,"全力士に適用",CRWHITE);
	DrawString(200,260,"前日負けただけで",CRWHITE);
	DrawFormatString(320,260,CRGREEN,"%d/1000",kyuujou_all_ritu);
	DrawString(187,290,"各カテゴリー(幕内、十両など)ごとの最大休場人数",CRWHITE);
	DrawFormatString(200,305,CRGREEN,"%d人",kyuujousuu_max_category);
	DrawString(187,320,"この人数がリミッターとして機能します",CRWHITE);
	DrawString(187,335,"大きくした場合には不具合の確率が高まります",CRRED);

	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	SetFontSize(16);
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	DrawString(x1[16],y1[16],"メニューへ戻る(確定)",CRGREEN);
	DrawString(x1[26],y1[26],"初期設定に戻す",CRGREEN);

	DrawString(187,370,"緑色の数字上",CRWHITE);
	DrawString(187,370+16,"を左右クリックして条件を設定してください",CRWHITE);
	DrawString(187,420,"設定内容により",CRRED);
	DrawString(187,440,"不具合の可能性があることをご了承ください",CRRED);
	ScreenFlip();
	return;
}
void kyuujoushousaisettei(void){

	FILE *fpwindow;
	kyuujoushousaisettei_hyoji();
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		if ( get_mouseclick(187,305,240,305+12) == 1 ){
			if (kyuujousuu_max_category<100){
				kyuujousuu_max_category++;
			}else if (kyuujousuu_max_category<200){
				kyuujousuu_max_category+=10;
			}else{
				kyuujousuu_max_category=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(187,305,240,305+12) == 2 ){
			if (kyuujousuu_max_category>100){
				kyuujousuu_max_category-=10;
			}else if (kyuujousuu_max_category>0){
				kyuujousuu_max_category--;
			}else{
				kyuujousuu_max_category=200;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(187,55,240,67) == 1 ){
			if (kyuujou_zenkyuu_ritu<100){
				kyuujou_zenkyuu_ritu++;
			}else if (kyuujou_zenkyuu_ritu<1000){
				kyuujou_zenkyuu_ritu+=10;
			}else{
				kyuujou_zenkyuu_ritu=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(187,55,240,67) == 2 ){
			if (kyuujou_zenkyuu_ritu>100){
				kyuujou_zenkyuu_ritu-=10;
			}else if (kyuujou_zenkyuu_ritu>0){
				kyuujou_zenkyuu_ritu--;
			}else{
				kyuujou_zenkyuu_ritu=1000;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(200,95,200+60,95+12) == 1 ){
			if (kyuujou_yokoduna1_day<14){
				kyuujou_yokoduna1_day++;
			}else{
				kyuujou_yokoduna1_day=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(200,95,200+60,95+12) == 2 ){
			if (kyuujou_yokoduna1_day>0){
				kyuujou_yokoduna1_day--;
			}else{
				kyuujou_yokoduna1_day=15;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(340,95,340+36,95+12) == 1 ){
			if (kyuujou_yokoduna1_ritu<100){
				kyuujou_yokoduna1_ritu++;
			}else{
				kyuujou_yokoduna1_ritu=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(340,95,340+36,95+12) == 2 ){
			if (kyuujou_yokoduna1_ritu>0){
				kyuujou_yokoduna1_ritu--;
			}else{
				kyuujou_yokoduna1_ritu=100;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(200,110,200+60,110+12) == 1 ){
			if (kyuujou_yokoduna2_day<14){
				kyuujou_yokoduna2_day++;
			}else{
				kyuujou_yokoduna2_day=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(200,110,200+60,110+12) == 2 ){
			if (kyuujou_yokoduna2_day>0){
				kyuujou_yokoduna2_day--;
			}else{
				kyuujou_yokoduna2_day=15;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(340,110,340+36,110+12) == 1 ){
			if (kyuujou_yokoduna2_ritu<100){
				kyuujou_yokoduna2_ritu++;
			}else{
				kyuujou_yokoduna2_ritu=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(340,110,340+36,110+12) == 2 ){
			if (kyuujou_yokoduna2_ritu>0){
				kyuujou_yokoduna2_ritu--;
			}else{
				kyuujou_yokoduna2_ritu=100;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(200,125,200+50,125+12) == 1 ){
			if (kyuujou_yokoduna3_day2<14){
				kyuujou_yokoduna3_day2++;
			}else{
				kyuujou_yokoduna3_day2=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(200,125,200+50,125+12) == 2 ){
			if (kyuujou_yokoduna3_day2>0){
				kyuujou_yokoduna3_day2--;
			}else{
				kyuujou_yokoduna3_day2=15;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(270,125,270+60,125+12) == 1 ){
			if (kyuujou_yokoduna3_day<14){
				kyuujou_yokoduna3_day++;
			}else{
				kyuujou_yokoduna3_day=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(270,125,270+60,125+12) == 2 ){
			if (kyuujou_yokoduna3_day>0){
				kyuujou_yokoduna3_day--;
			}else{
				kyuujou_yokoduna3_day=15;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(500,125,500+36,125+12) == 1 ){
			if (kyuujou_yokoduna3_ritu<100){
				kyuujou_yokoduna3_ritu++;
			}else{
				kyuujou_yokoduna3_ritu=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(500,125,500+36,125+12) == 2 ){
			if (kyuujou_yokoduna3_ritu>0){
				kyuujou_yokoduna3_ritu--;
			}else{
				kyuujou_yokoduna3_ritu=100;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(200,140,200+60,140+12) == 1 ){
			if (kyuujou_yokoduna4_day<14){
				kyuujou_yokoduna4_day++;
			}else{
				kyuujou_yokoduna4_day=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(200,140,200+60,140+12) == 2 ){
			if (kyuujou_yokoduna4_day>0){
				kyuujou_yokoduna4_day--;
			}else{
				kyuujou_yokoduna4_day=15;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(290,140,290+50,140+12) == 1 ){
			if (kyuujou_yokoduna4_lostsuu<14){
				kyuujou_yokoduna4_lostsuu++;
			}else{
				kyuujou_yokoduna4_lostsuu=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(290,140,290+50,140+12) == 2 ){
			if (kyuujou_yokoduna4_lostsuu>0){
				kyuujou_yokoduna4_lostsuu--;
			}else{
				kyuujou_yokoduna4_lostsuu=15;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(420,140,420+36,140+12) == 1 ){
			if (kyuujou_yokoduna4_ritu<100){
				kyuujou_yokoduna4_ritu++;
			}else{
				kyuujou_yokoduna4_ritu=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(420,140,420+36,140+12) == 2 ){
			if (kyuujou_yokoduna4_ritu>0){
				kyuujou_yokoduna4_ritu--;
			}else{
				kyuujou_yokoduna4_ritu=100;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(200,170,200+60,170+12) == 1 ){
			if (kyuujou_oozeki1_day<14){
				kyuujou_oozeki1_day++;
			}else{
				kyuujou_oozeki1_day=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(200,170,200+60,170+12) == 2 ){
			if (kyuujou_oozeki1_day>0){
				kyuujou_oozeki1_day--;
			}else{
				kyuujou_oozeki1_day=15;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(340,170,340+36,170+12) == 1 ){
			if (kyuujou_oozeki1_ritu<100){
				kyuujou_oozeki1_ritu++;
			}else{
				kyuujou_oozeki1_ritu=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(340,170,340+36,170+12) == 2 ){
			if (kyuujou_oozeki1_ritu>0){
				kyuujou_oozeki1_ritu--;
			}else{
				kyuujou_oozeki1_ritu=100;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(200,185,200+60,185+12) == 1 ){
			if (kyuujou_oozeki2_day<14){
				kyuujou_oozeki2_day++;
			}else{
				kyuujou_oozeki2_day=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(200,185,200+60,185+12) == 2 ){
			if (kyuujou_oozeki2_day>0){
				kyuujou_oozeki2_day--;
			}else{
				kyuujou_oozeki2_day=15;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(340,185,340+36,185+12) == 1 ){
			if (kyuujou_oozeki2_ritu<100){
				kyuujou_oozeki2_ritu++;
			}else{
				kyuujou_oozeki2_ritu=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(340,185,340+36,185+12) == 2 ){
			if (kyuujou_oozeki2_ritu>0){
				kyuujou_oozeki2_ritu--;
			}else{
				kyuujou_oozeki2_ritu=100;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(200,215,200+60,215+12) == 1 ){
			if (kyuujou_sekitori1_day<14){
				kyuujou_sekitori1_day++;
			}else{
				kyuujou_sekitori1_day=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(200,215,200+60,215+12) == 2 ){
			if (kyuujou_sekitori1_day>0){
				kyuujou_sekitori1_day--;
			}else{
				kyuujou_sekitori1_day=15;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(340,215,340+36,215+12) == 1 ){
			if (kyuujou_sekitori1_ritu<100){
				kyuujou_sekitori1_ritu++;
			}else{
				kyuujou_sekitori1_ritu=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(340,215,340+36,215+12) == 2 ){
			if (kyuujou_sekitori1_ritu>0){
				kyuujou_sekitori1_ritu--;
			}else{
				kyuujou_sekitori1_ritu=100;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(200,230,200+60,230+12) == 1 ){
			if (kyuujou_sekitori2_day<14){
				kyuujou_sekitori2_day++;
			}else{
				kyuujou_sekitori2_day=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(200,230,200+60,230+12) == 2 ){
			if (kyuujou_sekitori2_day>0){
				kyuujou_sekitori2_day--;
			}else{
				kyuujou_sekitori2_day=15;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(340,230,340+36,230+12) == 1 ){
			if (kyuujou_sekitori2_ritu<100){
				kyuujou_sekitori2_ritu++;
			}else{
				kyuujou_sekitori2_ritu=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(340,230,340+36,230+12) == 2 ){
			if (kyuujou_sekitori2_ritu>0){
				kyuujou_sekitori2_ritu--;
			}else{
				kyuujou_sekitori2_ritu=100;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if ( get_mouseclick(320,260,320+36,260+12) == 1 ){
			if (kyuujou_all_ritu<100){
				kyuujou_all_ritu++;
			}else if (kyuujou_all_ritu<1000){
				kyuujou_all_ritu+=10;
			}else{
				kyuujou_all_ritu=0;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}
		if ( get_mouseclick(320,260,320+36,260+12) == 2 ){
			if (kyuujou_all_ritu>100){
				kyuujou_all_ritu-=10;
			}else if (kyuujou_all_ritu>0){
				kyuujou_all_ritu--;
			}else{
				kyuujou_all_ritu=1000;
			}
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if (get_mouseclick_list(26) == 1 || get_mouseclick_list(27)==1 ){
			kyuujousuu_max_category=5;
			kyuujou_zenkyuu_ritu=20;
			kyuujou_yokoduna1_day=11;
			kyuujou_yokoduna2_day=10;
			kyuujou_yokoduna3_day=11;
			kyuujou_yokoduna3_day2=7;
			kyuujou_yokoduna4_day=13;
			kyuujou_yokoduna4_lostsuu=6;
			kyuujou_oozeki1_day=10;
			kyuujou_oozeki2_day=10;
			kyuujou_sekitori1_day=10;
			kyuujou_sekitori2_day=10;
			kyuujou_yokoduna1_ritu=50;
			kyuujou_yokoduna2_ritu=25;
			kyuujou_yokoduna3_ritu=30;
			kyuujou_yokoduna4_ritu=30;
			kyuujou_oozeki1_ritu=20;
			kyuujou_oozeki2_ritu=10;
			kyuujou_sekitori1_ritu=4;
			kyuujou_sekitori2_ritu=3;
			kyuujou_all_ritu=2;
			kyuujoushousaisettei_hyoji();
			WaitTimer(150);
		}

		if (get_mouseclick_list(16) == 1 || get_mouseclick_list(17)==1 ){
			FILE *fpwindow;
			fpwindow = fopen("data/kyuujoushousaisettei.dat","wb");
			fwrite(&kyuujou_zenkyuu_ritu,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_yokoduna1_day,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_yokoduna2_day,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_yokoduna3_day,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_yokoduna3_day2,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_yokoduna4_day,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_yokoduna4_lostsuu,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_oozeki1_day,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_oozeki2_day,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_sekitori1_day,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_sekitori2_day,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_yokoduna1_ritu,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_yokoduna2_ritu,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_yokoduna3_ritu,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_yokoduna4_ritu,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_oozeki1_ritu,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_oozeki2_ritu,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_sekitori1_ritu,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_sekitori2_ritu,sizeof(int),1,fpwindow);
			fwrite(&kyuujou_all_ritu,sizeof(int),1,fpwindow);
			fwrite(&kyuujousuu_max_category,sizeof(int),1,fpwindow);
			fclose(fpwindow);
			WaitTimer(200);
			return;
		}
		// メッセージ処理
		if( ProcessMessage() == -1 )
		{
			mode=1;
			return ;	// エラーが起きたらループから抜ける
		}
		Sleep(1);
	}

//	return;
}

void shozokurekihyoji(int x)//現役力士の所属履歴表示
{
int i,ii;
char gyousuu=0;
char deruflag=0;
char jiyuustr[22];
//char hyoji_shozoku_heyaid_chokuzen=0;
char hyoji_heyaid_tuusan_chokuzen=0;
char hyoji_heyastring_chokuzen[12];
char hyoji_itimonstring_chokuzen[12];
int hyoji_month_chokuzen=0;
long bsize_shozoku=0;
long bsize_tosiyori=0;
int year_shozoku=0;
int month_shozoku=0;
int year_tosiyori=0;
int month_tosiyori=0;
int shozoku_rikisiid[RIKISISUU];
char shozoku_heyaid[RIKISISUU];
int nowrenban=0;
char r_heyastring[HEYASUU][12];//(54部屋分,全角５文字まで)相撲部屋
char temp_filename[MAX_PATH];
int hyoji_month_2mae=0;
int hyoji_year_2mae=0;
struct tosiyori_data r_tosiyoridata[TOSIYORISUU];
struct itimon_data r_itimondata[ITIMONSUU];
struct heya_data r_heyadata[HEYASUU];

for (i=0;i<MAX_PATH;i++){
	temp_filename[i]=0;
}

for (i=0;i<HEYASUU;i++){
	for (ii=0;ii<12;ii++){
		r_heyastring[i][ii]=0;
	}
}

for (i=0;i<22;i++){
	jiyuustr[i]=0;
}
for (i=0;i<12;i++){
	hyoji_heyastring_chokuzen[i]=0;
	hyoji_itimonstring_chokuzen[i]=0;
}

	FILE *fp;
	FILE *fp2;
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	SetFontSize(12);
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	ClearDrawScreen();
	///////////////////////////////////////////////////////////////////
	////////////////tosiyori.datとshozoku.datを読み込みながら表示///////////////////////////////////
	DrawBox(463,43,639,367,CRBACK,TRUE);//右リスト部分黒塗りつぶし(文字が右にはみ出すので)
	DrawString( 187 , 369+35 , "※所属年月、事由、一門名、部屋名 部屋ID(通算部屋ID)の順の表示です" , CRWHITE );
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
	bsize_shozoku=sizeof(year)+sizeof(month)+(sizeof(rikisidata[0].rikisiid)+sizeof(rikisidata[0].heyaid))*RIKISISUU;
	bsize_tosiyori=sizeof(year)+sizeof(month)+sizeof(r_tosiyoridata)+sizeof(r_itimondata)+sizeof(r_heyadata)+sizeof(r_heyastring);
	//所属ファイルオープン
	strcpy(temp_filename,"data/dat/shozoku.dat\0");
	fp = fopen(temp_filename,"rb");
	if( fp == NULL ){
		DrawString( 187 , 369+48, "sub_retirerikisi_new~shozoku.datファイルオープンに失敗" , GetColor(255,255,255) );
		fclose(fp);
	}else{
		fseek(fp,
			bsize_shozoku*( (rikisidata[x].hatudohyo_year-1)*6+(int)(rikisidata[x].hatudohyo_month/2) ),
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

//DrawFormatString( 187, 369-60 ,CRWHITE, "↓初土俵%d年%d月とのtemp_hatudohyo" ,temp_hatudohyo_year,temp_hatudohyo_month);
//DrawFormatString( 187, 369-40 ,CRWHITE, "%d年%d月　year_shozokuの読込失敗でループ抜け" ,year_shozoku,month_shozoku);

				//ファイル末端と引退年月が重なる場合もありうるので以下のメッセージはコメントアウト
				//DrawString( 187 , 369+48 , "shozoku.datの年の読込に失敗(コメントアウト予定)" , CRWHITE );
				break;
			}
			fread(&month_shozoku,sizeof(month_shozoku),1,fp);
			for(i=0;i<RIKISISUU;i++){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				fread(&shozoku_rikisiid[i],sizeof(rikisidata[0].rikisiid),1,fp);
				fread(&shozoku_heyaid[i],sizeof(rikisidata[0].heyaid),1,fp);
			}
			//現在年月後の読込あり得ないけどね
			if (year*12+month<year_shozoku*12+month_shozoku){
				fclose(fp);
				fclose(fp2);

//DrawFormatString( 187, 369-60 ,CRWHITE, "↓引退%d年%d月とのtemp_retire" ,temp_retire_year,temp_retire_month);
//DrawFormatString( 187, 369-40 ,CRWHITE, "%d年%d月　引退後年月の読込でループ抜け" ,year_shozoku,month_shozoku);

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
						DrawFormatString( 187 , 369+48 ,CRWHITE, "shozoku.datは読み込めてるのにtosiyori.datファイルオープンに失敗(ban%d)" , nowrenban );
						break;
					}
				}else{
					sprintf(temp_filename,"data/dat/tosiyori%d.dat\0",nowrenban+1);
					fp2 = fopen(temp_filename,"rb");
					if( fp2 == NULL ){
						fclose(fp);
						fclose(fp2);
						DrawFormatString( 187 , 369+48 ,CRWHITE, "shozoku.datは読み込めてるのにtosiyori.datファイルオープンに失敗(ban%d)" , nowrenban );
						break;
					}
				}
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				fseek(fp2,
					bsize_tosiyori*( ((rikisidata[x].hatudohyo_year-1)*6+(int)(rikisidata[x].hatudohyo_month/2))-nowrenban*((int)(maxfilesize/bsize_tosiyori)+1) ),
					SEEK_SET);
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			}
			if(fread(&year_tosiyori,sizeof(year_tosiyori),1,fp2)<1){//EOFor読み取り失敗
				fclose(fp);
				fclose(fp2);
				DrawFormatString( 187 , 369+48 ,CRWHITE, "shozoku.datは読み込めてるのにtosiyori.datファイル読込に失敗(ban%d)" , nowrenban );
				break;
			}
			fread(&month_tosiyori,sizeof(month_tosiyori),1,fp2);
			fread(r_tosiyoridata,sizeof(r_tosiyoridata),1,fp2);
			fread(r_itimondata,sizeof(r_itimondata),1,fp2);
			fread(r_heyadata,sizeof(r_heyadata),1,fp2);
			fread(r_heyastring,sizeof(r_heyastring),1,fp2);
			//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			//ここから表示
			deruflag=0;
			for(i=0;i<RIKISISUU;i++){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				if (shozoku_rikisiid[i]==rikisidata[x].rikisiid
				){
/////////
//DrawBox(187,369-20,639,367,CRBACK,TRUE);
//DrawFormatString( 187, 369-20 ,CRWHITE, "%d年%d月%d通過　部屋ID%d" ,year_tosiyori,month_tosiyori, temp_rikisiid,shozoku_heyaid[i] );
/////////
					for (ii=0;ii<TOSIYORISUU;ii++){
						//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
						if (r_tosiyoridata[ii].shozokuheyaid==shozoku_heyaid[i]){
							//ここに前回表示時と同じ状況でないかどうかの判断文
							if (hyoji_heyaid_tuusan_chokuzen!=r_heyadata[shozoku_heyaid[i]].heyaid_tuusan
							|| strcmp(hyoji_heyastring_chokuzen,r_heyastring[shozoku_heyaid[i]])!=0
							|| strcmp(hyoji_itimonstring_chokuzen,r_itimondata[r_tosiyoridata[ii].shozokuitimonid].namestring)!=0
							){
								//ここに入門、部屋名変更、部屋移籍(新設や消滅の場合)、一門名変更なのかの区別if文
								if (year_shozoku==rikisidata[x].hatudohyo_year && month_shozoku==rikisidata[x].hatudohyo_month){
									strcpy(jiyuustr," 入門");
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
								DrawFormatString(187,40+gyousuu*16,CRWHITE,"%d年%d月%s %s一門 %s部屋 ID%d(%d)",
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

	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	SetFontSize(16);
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	DrawFormatString(200,0,CRWHITE,"%sの所属部屋履歴",namestring[x]);
	DrawString(x1[0],y1[0],"戻る",CRGREEN);
	ScreenFlip();

	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{

		if (get_mouseclick_list(0) == 1 || get_mouseclick_list(1)==1 ){
			return;
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
