#include "DxLib.h"
#include <stdio.h>
#include "define.h"

extern int lastkeiko_year[RIKISISUU];
extern int lastkeiko_month[RIKISISUU];
extern int lastkeiko_day[RIKISISUU];
extern char lastkeiko_aitenamestring[RIKISISUU][12];

extern int genekirikisisentaku_keiko(int x,char flag);//選択した力士の画像IDが返される

extern int CheckHitKey_test(int);

extern int bunsekikeikoaite_id;

extern int day;
extern char AIkeikoflag;
extern char memoryfusokuflag;//動的メモリを使わない場合1
extern int aikeikosuu[RIKISISUU][RIKISISUU];//取組・稽古両方合わせた過去の力士別対戦数

extern int hyoji_kumiteid;

extern char namestring[RIKISISUU][12];//(力士IDごとの四股名,全角５文字まで)四股名
extern int FontHandle16;
extern int FontHandle12;
extern void game_main_backscreen(void);//基本ゲーム画面表示ルーチン

extern int get_mouseclick(int x1,int y1,int x2,int y2);//座標(x1,y1)と(x2,y2)に囲まれたところで
extern int x1[40];//[]内のリスト番号の左上x座標、初期化はwinmain関数内でする
extern int x2[40];//右下ｘ座標
extern int y1[40];//左上y座標
extern int y2[40];//右下y座標
extern int get_mouseclick_list(int x);//画面左のリスト上でクリックされたら1を返す、


extern struct rikisi_data rikisidata[RIKISISUU];
extern int kougekiken;//東方力士の攻撃＞1、西の攻撃＞2
extern int offenseid;//攻撃側力士のID
extern int defenseid;//守備側力士のID

//技ID
extern int NASI_WAZA;//0なし
extern int TUKI_WAZA;//1突き
extern int ATEGAI_WAZA;//2あてがい
extern int CHUUKANSHORI_WAZA;//3中間処理（距離が中間になったときの処理）
extern int MIGIUWATEMAWASINERAI_WAZA;//4右上手廻し狙い
extern int HIDARIUWATEMAWASINERAI_WAZA;//5左上手廻し狙い
extern int MIGISITATEMAWASINERAI_WAZA;//6右下手廻し狙い
extern int HIDARISITATEMAWASINERAI_WAZA;//7左下手廻し狙い
extern int YORI_WAZA;//8寄り
extern int GENJOUIJI_WAZA;//9現状維持
extern int MIGIUWATENERAI_WAZA;//10右上手狙い(下手からの巻き替え)
extern int HIDARIUWATENERAI_WAZA;//11左上手狙い(下手からの巻き替え)
extern int MIGISITATENERAI_WAZA;//12右下手狙い(上手からの巻き替え)
extern int HIDARISITATENERAI_WAZA;//13左下手狙い(上手からの巻き替え)
extern int MIGIUWATENAGE_WAZA;//14右上手投げ
extern int HIDARIUWATENAGE_WAZA;//15左上手投げ
extern int MIGISITATENAGE_WAZA;//16右下手投げ
extern int HIDARISITATENAGE_WAZA;//17左下手投げ
extern int MIGIKOTENAGE_WAZA;//18右小手投げ
extern int HIDARIKOTENAGE_WAZA;//19左小手投げ
extern int MIGISUKUINAGE_WAZA;//20右掬い投げ
extern int HIDARISUKUINAGE_WAZA;//21左掬い投げ
//立会い勢い
extern int ZENRYOKU_TATIAI_POWER;
extern int NORMAL_TATIAI_POWER;
extern int UKERU_TATIAI_POWER;
extern int HENKA_TATIAI_POWER;
extern int higasi_tatiai_power,nisi_tatiai_power;
//立会い狙い
extern int TUKIOSI_TATIAI_NERAI;
extern int MIGIYOTU_TATIAI_NERAI;
extern int HIDARIYOTU_TATIAI_NERAI;
extern int RYOUUWATE_TATIAI_NERAI;
extern int MOROZASI_TATIAI_NERAI;
extern int higasi_tatiai_nerai,nisi_tatiai_nerai,offense_tatiai_nerai,defense_tatiai_nerai;
//距離（間合い）
extern int FAR_STATE_KYORI;
extern int MIDDLE_STATE_KYORI;
extern int NEAR_STATE_KYORI;
//
extern int state_kyori;
extern int state_ichi;//土俵上での位置-4～+4、0が土俵中央、-4で東力士OUT、+4で西力士OUT
extern int offense_state_balance,defense_state_balance,higasi_state_balance,nisi_state_balance;//バランス、パラ/10がMAXで、0で倒れて負け
//上体の上下
extern int HIGH_STATE_JOUGE;
extern int MIDDLE_STATE_JOUGE;
extern int LOW_STATE_JOUGE;
extern int offense_state_jouge,defense_state_jouge,higasi_state_jouge,nisi_state_jouge;
//圧力前後
extern int MAE_ACTION_ZENGO;
extern int NASI_ACTION_ZENGO;
extern int USIRO_ACTION_ZENGO;
extern int offense_action_zengo,defense_action_zengo;
//横の動き
extern int YOKO_ACTION_SAYUU;
extern int NASI_ACTION_SAYUU;
extern int offense_action_sayuu,defense_action_sayuu;
//腕の状態（上手か下手か、廻しの有無）
extern int MAE_STATE_UDE;//間合いが近くない場合
extern int UWATE_STATE_UDE;
extern int SITATE_STATE_UDE;
extern int UWATETUKAMI_STATE_UDE;
extern int SITATETUKAMI_STATE_UDE;
extern int offense_state_migiude,offense_state_hidariude,defense_state_migiude,defense_state_hidariude,higasi_state_migiude,higasi_state_hidariude,nisi_state_migiude,nisi_state_hidariude;
//腕の動き
extern int NASI_ACTION_UDE;
extern int TUKI_ACTION_UDE;
extern int ATEGAI_ACTION_UDE;
extern int INASI_ACTION_UDE;
extern int OTTUKE_ACTION_UDE;
extern int OSI_ACTION_UDE;
extern int UWATENERAI_ACTION_UDE;
extern int SITATENERAI_ACTION_UDE;
extern int MAWASINERAI_ACTION_UDE;
extern int HIKITUKE_ACTION_UDE;
extern int SIBORI_ACTION_UDE;
extern int KAKAEKOMI_ACTION_UDE;
extern int KAESI_ACTION_UDE;
extern int NAGE_ACTION_UDE;
extern int MAWASIIJI_ACTION_UDE;
extern int offense_action_migiude,offense_action_hidariude,defense_action_migiude,defense_action_hidariude;

extern int tatiaipatternid_higasi;//東力士がこの取り組みで選択した立会いパターンID
extern int tatiaipatternid_nisi;
extern long Getfilesize(char name[]);//返り値が0は存在するけどファイルサイズ0、-1→エラー、-2→存在無し
extern int mode;//1：終了フラグ、2：ゲーム準備処理完了フラグ、
extern long maxfilesize;//本番用

extern int ichi_lastturn;//土俵上での位置-4～+4、0が土俵中央、-4で東力士OUT、+4で西力士OUT
extern int last_higasi_state_balance,last_nisi_state_balance;//バランス、パラ/10がMAXで、0で倒れて負け


extern char *aidata;//動的メモリ
extern char *aidata_tatiai;//動的メモリ
extern unsigned short int *rbetuwdata_kouka;
extern unsigned short int *rbetuwdata_bosuu;
extern unsigned short int *rbetutdata_kouka;
extern unsigned short int *rbetutdata_bosuu;

extern char memorykakuchouflag;//力士別の技データまでもメモリに乗せる場合は1


extern long aidata_fichi[22][5][2][2][2][2][4];//aidataのファイル記録位置
									//技ＩＤ	四つ	自分右廻し	自分左廻し	相手右廻し	相手左廻し	上体比較
									//上体は0→自分の方が高い、１→同じ、2→自分の方が低い

char getdatafrombit(char bytedata,char amari);//バイトデータから2bitの値を取り出す関数
										//aidataに記録されているのは2bitずつなので
										//上記fichi/4の位置の2bitの値を0~3の値で返す関数
char setdatatobit(char bytedata,char amari,char setdata);//bytedataのamariの位置の2ビットにsetdataの値をセット

extern int ito_higasi_tatiai_power;
extern int ito_nisi_tatiai_power;

extern char wazabunsekipage;
extern int wazadata_kouka_seme[22][RIKISISUU][5];//効果(+127～-127)
extern int wazadata_bosuu_seme[22][RIKISISUU][5];//効果(+127～-127)
extern int tatiaidata_kouka_seme[RIKISISUU][20];//どの立ち合いが勝利に結びついたか
extern int tatiaidata_bosuu_seme[RIKISISUU][20];//どの立ち合いが勝利に結びついたか
extern short int lastwazadata_kouka_seme[22][RIKISISUU][5];//
extern short int lastwazadata_bosuu_seme[22][RIKISISUU][5];//
extern short int lasttatiaidata_kouka_seme[RIKISISUU][20];//どの立ち合いが勝利に結びついたか
extern short int lasttatiaidata_bosuu_seme[RIKISISUU][20];//どの立ち合いが勝利に結びついたか

	//wazadata_kouka[技ID][力士ID][四つの状況]
	//効果を記録する(+127～-127)
/*	四つの状況
	0→間合い遠い
	1→右四つ
	2→左四つ
	3→両上手
	4→両差し
*/

extern int bandukejunid[RIKISISUU];

extern int count_temp_aidata;

int temp_aidata_jibunid[100];//0~707の画像ID
int temp_aidata_aiteid[100];//0~707の画像ID
char temp_aidata_wazaid[100];
char temp_aidata_yotu[100];
char temp_aidata_jibunmigimawasi[100];
char temp_aidata_jibunhidarimawasi[100];
char temp_aidata_aitemigimawasi[100];
char temp_aidata_aitehidarimawasi[100];
char temp_aidata_joutaiflag[100];

extern int chokuzen_state_kyori;
extern int	chokuzen_offense_state_migiude;
extern int	chokuzen_offense_state_hidariude;
extern int	chokuzen_defense_state_migiude;
extern int	chokuzen_defense_state_hidariude;
extern int	chokuzen_offense_action_migiude;
extern int	chokuzen_offense_action_hidariude;
extern int	chokuzen_defense_action_migiude;
extern int	chokuzen_defense_action_hidariude;
extern int	chokuzen_offense_action_zengo;
extern int	chokuzen_defense_action_zengo;
extern int	chokuzen_offense_state_jouge;
extern int	chokuzen_defense_state_jouge;
extern int	chokuzen_offense_state_balance;
extern int	chokuzen_defense_state_balance;

void kiroku_wazadata(char wazaid,int id1,int id2,char id1_higasiornisi,char tatiaigoflag);
void wazabunsekihyoji(int id);
void chokuzen(void);
void hozon_aidata(int higasiid,int nisiid,int winid);

extern int hyoka_upkakuritu[10];//AI評価の上がりやすさ、[]内はどの程度格上か格下かの度合い
								//0→格下rankも4つ以上下
								//1→格下rankも3つ下
								//2→格下rankも2つ下
								//3→格下rankも1つ下
								//4→格下rankは同じ
								//5→格上rankは同じ
								//6→格上rankは1つ上
								//7→格上rankは2つ上
								//8→格上rankは3つ上
								//9→格上rankは4つ以上上
extern int hyoka_downkakuritu[10];//AI評価の下がりやすさ、[]内はどの程度格上か格下かの度合い


void hozon_aidata(int higasiid,int nisiid,int winid)
{
	int lostid=0;
	int kakuueflag=0;
	int i,ii,i2,i3,i4,i5,i6,i7;
	long temp_fichi=0;
	char temp_char=0;
	char sumiflag_win[22][5][2][2][2][2][4];
	char sumiflag_lost[22][5][2][2][2][2][4];
	char bytedata=0;
	int temp_tatiaipatternid_higasi=0;
	int temp_tatiaipatternid_nisi=0;
	unsigned short int shortdata=0;

	//格上フラグ代入
	if (winid==higasiid){
		lostid=nisiid;
	}else{
		lostid==higasiid;
	}
	if (rikisidata[winid].bandukejun<rikisidata[lostid].bandukejun){//格下との取組
		if (rikisidata[winid].bandukenameid+4<=rikisidata[lostid].bandukenameid){
			kakuueflag=0;
		}else if(rikisidata[winid].bandukenameid+3==rikisidata[lostid].bandukenameid){
			kakuueflag=1;
		}else if(rikisidata[winid].bandukenameid+2==rikisidata[lostid].bandukenameid){
			kakuueflag=2;
		}else if(rikisidata[winid].bandukenameid+1==rikisidata[lostid].bandukenameid){
			kakuueflag=3;
		}else{
			kakuueflag=4;
		}
	}else{//格上との取組
		if (rikisidata[winid].bandukenameid-4>=rikisidata[lostid].bandukenameid){
			kakuueflag=9;
		}else if(rikisidata[winid].bandukenameid-3==rikisidata[lostid].bandukenameid){
			kakuueflag=8;
		}else if(rikisidata[winid].bandukenameid-2==rikisidata[lostid].bandukenameid){
			kakuueflag=7;
		}else if(rikisidata[winid].bandukenameid-1>=rikisidata[lostid].bandukenameid){
			kakuueflag=6;
		}else{
			kakuueflag=5;
		}
	}

	//取組・稽古数加算
	if (aikeikosuu[higasiid][nisiid]<2147483647){
		aikeikosuu[higasiid][nisiid]++;
	}
	if (aikeikosuu[nisiid][higasiid]<2147483647){
		aikeikosuu[nisiid][higasiid]++;
	}

	//全力が変化や受けになったりするなどがあるため、補正前の純粋な狙いと勢いを代入
	//temp_tatiaipatternid_higasi=higasi_tatiai_nerai*4+ito_higasi_tatiai_power;
	//temp_tatiaipatternid_nisi=nisi_tatiai_nerai*4+ito_nisi_tatiai_power;
	//4.01beta010で変更→意図に代入する前段階でテレパシーや成長型AIについては躊躇したり気負ったりで
						//勢いが変えられていたので、だったら「結果」で統一みたいな感じ
	temp_tatiaipatternid_higasi=tatiaipatternid_higasi;
	temp_tatiaipatternid_nisi=tatiaipatternid_nisi;

	//tatiaidata_bosuuはいずれにしても加算
	if (AIkeikoflag==0){
		tatiaidata_bosuu_seme[higasiid][temp_tatiaipatternid_higasi]++;//どの立ち合いが勝利に結びついたか
		tatiaidata_bosuu_seme[nisiid][temp_tatiaipatternid_nisi]++;//どの立ち合いが勝利に結びついたか
	}
	lasttatiaidata_bosuu_seme[higasiid][temp_tatiaipatternid_higasi]++;//どの立ち合いが勝利に結びついたか
	lasttatiaidata_bosuu_seme[nisiid][temp_tatiaipatternid_nisi]++;//どの立ち合いが勝利に結びついたか

	if (AIkeikoflag==0){
		if (memoryfusokuflag==0 && memorykakuchouflag==1){
			memcpy(&shortdata, 
				rbetutdata_bosuu
				+higasiid*RIKISISUU*20
				+nisiid*20
				+temp_tatiaipatternid_higasi,
				sizeof(unsigned short int));
			if (shortdata<65535) shortdata++;
			memcpy(rbetutdata_bosuu
				+higasiid*RIKISISUU*20
				+nisiid*20
				+temp_tatiaipatternid_higasi, 
				&shortdata,
				sizeof(unsigned short int));

			memcpy(&shortdata, 
				rbetutdata_bosuu
				+nisiid*RIKISISUU*20
				+higasiid*20
				+temp_tatiaipatternid_nisi,
				sizeof(unsigned short int));
			if (shortdata<65535) shortdata++;
			memcpy(rbetutdata_bosuu
				+nisiid*RIKISISUU*20
				+higasiid*20
				+temp_tatiaipatternid_nisi, 
				&shortdata,
				sizeof(unsigned short int));
		}
	}
	//aidata_tatiai(立合いの点数調整)とtatiaidata_kouka加算
	if (winid==higasiid){
		//tatiaidata加算
		//////立合い全体//////
		if (AIkeikoflag==0){
			tatiaidata_kouka_seme[higasiid][temp_tatiaipatternid_higasi]++;//どの立ち合いが勝利に結びついたか
		}
		lasttatiaidata_kouka_seme[higasiid][temp_tatiaipatternid_higasi]++;//どの立ち合いが勝利に結びついたか
		if (AIkeikoflag==0){
			if (memoryfusokuflag==0 && memorykakuchouflag==1){
				//////立合い力士別//////
				memcpy(&shortdata, 
					rbetutdata_kouka
					+higasiid*RIKISISUU*20
					+nisiid*20
					+temp_tatiaipatternid_higasi,
					sizeof(unsigned short int));
				if (shortdata<65535) shortdata++;
				memcpy(rbetutdata_kouka
					+higasiid*RIKISISUU*20
					+nisiid*20
					+temp_tatiaipatternid_higasi, 
					&shortdata,
					sizeof(unsigned short int));
			}
		}
		///////////////////////////
		if (memoryfusokuflag==0){
			//////力士ごとデータ//////
			///勝ちはプラス////
			memcpy(&bytedata, 
				aidata_tatiai
				+higasiid*RIKISISUU*AIDATATATIAIBYTESUU
				+nisiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_higasi/4),
				sizeof(char));
			//値取り出し
			temp_char=getdatafrombit(bytedata,temp_tatiaipatternid_higasi%4);
			//加算
			if (temp_char<3){
				if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
					temp_char++;
				}
			}
			//値格納
			bytedata=setdatatobit(bytedata,temp_tatiaipatternid_higasi%4,temp_char);
			memcpy(aidata_tatiai
				+higasiid*RIKISISUU*AIDATATATIAIBYTESUU
				+nisiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_higasi/4), 
				&bytedata,
				sizeof(char));
			///相手はマイナス///
			memcpy(&bytedata, 
				aidata_tatiai
				+nisiid*RIKISISUU*AIDATATATIAIBYTESUU
				+higasiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_nisi/4),
				sizeof(char));
			//値取り出し
			temp_char=getdatafrombit(bytedata,temp_tatiaipatternid_nisi%4);
			//減算
			if (temp_char>0){
				if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
					temp_char--;
				}
			}
			//値格納
			bytedata=setdatatobit(bytedata,temp_tatiaipatternid_nisi%4,temp_char);
			memcpy(aidata_tatiai
				+nisiid*RIKISISUU*AIDATATATIAIBYTESUU
				+higasiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_nisi/4), 
				&bytedata,
				sizeof(char));
			//////////////////////////
			//////トータルデータ//////
			memcpy(&bytedata, 
				aidata_tatiai
				+higasiid*RIKISISUU*AIDATATATIAIBYTESUU
				+higasiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_higasi/4),
				sizeof(char));
			//値取り出し
			temp_char=getdatafrombit(bytedata,temp_tatiaipatternid_higasi%4);
			//加算
			if (temp_char<3){
				if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
					temp_char++;
				}
			}
			//値格納
			bytedata=setdatatobit(bytedata,temp_tatiaipatternid_higasi%4,temp_char);
			memcpy(aidata_tatiai
				+higasiid*RIKISISUU*AIDATATATIAIBYTESUU
				+higasiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_higasi/4), 
				&bytedata,
				sizeof(char));
			///相手はマイナス///
			memcpy(&bytedata, 
				aidata_tatiai
				+nisiid*RIKISISUU*AIDATATATIAIBYTESUU
				+nisiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_nisi/4),
				sizeof(char));
			//値取り出し
			temp_char=getdatafrombit(bytedata,temp_tatiaipatternid_nisi%4);
			//減算
			if (temp_char>0){
				if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
					temp_char--;
				}
			}
			//値格納
			bytedata=setdatatobit(bytedata,temp_tatiaipatternid_nisi%4,temp_char);
			memcpy(aidata_tatiai
				+nisiid*RIKISISUU*AIDATATATIAIBYTESUU
				+nisiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_nisi/4), 
				&bytedata,
				sizeof(char));
		}
	}else{//nisiが勝ち
		//tatiaidata加算
		//////立合い全体//////
		if (AIkeikoflag==0){
			tatiaidata_kouka_seme[nisiid][temp_tatiaipatternid_nisi]++;//どの立ち合いが勝利に結びついたか
		}
		lasttatiaidata_kouka_seme[nisiid][temp_tatiaipatternid_nisi]++;//どの立ち合いが勝利に結びついたか
		if (AIkeikoflag==0){
			if (memoryfusokuflag==0 && memorykakuchouflag==1){
				//////立合い力士別//////
				memcpy(&shortdata, 
					rbetutdata_kouka
					+nisiid*RIKISISUU*20
					+higasiid*20
					+temp_tatiaipatternid_nisi,
					sizeof(unsigned short int));
				if (shortdata<65535) shortdata++;
				memcpy(rbetutdata_kouka
					+nisiid*RIKISISUU*20
					+higasiid*20
					+temp_tatiaipatternid_nisi, 
					&shortdata,
					sizeof(unsigned short int));
			}
		}
		//////////////////////////
		if (memoryfusokuflag==0){
			//////力士ごとデータ//////
			memcpy(&bytedata, 
				aidata_tatiai
				+nisiid*RIKISISUU*AIDATATATIAIBYTESUU
				+higasiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_nisi/4),
				sizeof(char));
			//値取り出し
			temp_char=getdatafrombit(bytedata,temp_tatiaipatternid_nisi%4);
			//加算
			if (temp_char<3){
				if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
					temp_char++;
				}
			}
			//値格納
			bytedata=setdatatobit(bytedata,temp_tatiaipatternid_nisi%4,temp_char);
			memcpy(aidata_tatiai
				+nisiid*RIKISISUU*AIDATATATIAIBYTESUU
				+higasiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_nisi/4), 
				&bytedata,
				sizeof(char));
			///相手はマイナス///
			memcpy(&bytedata, 
				aidata_tatiai
				+higasiid*RIKISISUU*AIDATATATIAIBYTESUU
				+nisiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_higasi/4),
				sizeof(char));
			//値取り出し
			temp_char=getdatafrombit(bytedata,temp_tatiaipatternid_higasi%4);
			//減算
			if (temp_char>0){
				if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
					temp_char--;
				}
			}
			//値格納
			bytedata=setdatatobit(bytedata,temp_tatiaipatternid_higasi%4,temp_char);
			memcpy(aidata_tatiai
				+higasiid*RIKISISUU*AIDATATATIAIBYTESUU
				+nisiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_higasi/4), 
				&bytedata,
				sizeof(char));
			///////////////////////////
			//////トータルデータ//////
			memcpy(&bytedata, 
				aidata_tatiai
				+nisiid*RIKISISUU*AIDATATATIAIBYTESUU
				+nisiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_nisi/4),
				sizeof(char));
			//値取り出し
			temp_char=getdatafrombit(bytedata,temp_tatiaipatternid_nisi%4);
			//加算
			if (temp_char<3){
				if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
					temp_char++;
				}
			}
			//値格納
			bytedata=setdatatobit(bytedata,temp_tatiaipatternid_nisi%4,temp_char);
			memcpy(aidata_tatiai
				+nisiid*RIKISISUU*AIDATATATIAIBYTESUU
				+nisiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_nisi/4), 
				&bytedata,
				sizeof(char));
			///相手はマイナス///
			memcpy(&bytedata, 
				aidata_tatiai
				+higasiid*RIKISISUU*AIDATATATIAIBYTESUU
				+higasiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_higasi/4),
				sizeof(char));
			//値取り出し
			temp_char=getdatafrombit(bytedata,temp_tatiaipatternid_higasi%4);
			//減算
			if (temp_char>0){
				if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
					temp_char--;
				}
			}
			//値格納
			bytedata=setdatatobit(bytedata,temp_tatiaipatternid_higasi%4,temp_char);
			memcpy(aidata_tatiai
				+higasiid*RIKISISUU*AIDATATATIAIBYTESUU
				+higasiid*AIDATATATIAIBYTESUU
				+(int)(temp_tatiaipatternid_higasi/4), 
				&bytedata,
				sizeof(char));
		}
	}
	if (memoryfusokuflag==0){
		//aidata(勝ち負け別技の加減)
		for (i=0;i<22;i++){
		for (i2=0;i2<5;i2++){
		for (i3=0;i3<2;i3++){
		for (i4=0;i4<2;i4++){
		for (i5=0;i5<2;i5++){
		for (i6=0;i6<2;i6++){
		for (i7=0;i7<4;i7++){
			sumiflag_win[i][i2][i3][i4][i5][i6][i7]=0;
			sumiflag_lost[i][i2][i3][i4][i5][i6][i7]=0;
		}}}}}}}
		for (i=0;i<100;i++){
			if (temp_aidata_jibunid[i]==-1) break;
			//勝ち
			if (temp_aidata_jibunid[i]==winid){
				temp_fichi=aidata_fichi[temp_aidata_wazaid[i]][temp_aidata_yotu[i]][temp_aidata_jibunmigimawasi[i]][temp_aidata_jibunhidarimawasi[i]][temp_aidata_aitemigimawasi[i]][temp_aidata_aitehidarimawasi[i]][temp_aidata_joutaiflag[i]];
				if (temp_fichi!=-1){
					if (sumiflag_win[temp_aidata_wazaid[i]][temp_aidata_yotu[i]][temp_aidata_jibunmigimawasi[i]][temp_aidata_jibunhidarimawasi[i]][temp_aidata_aitemigimawasi[i]][temp_aidata_aitehidarimawasi[i]][temp_aidata_joutaiflag[i]]!=1){
						//////////巻き替えと突き・あてがいのみ/////////
						if (temp_aidata_wazaid[i]==1 || temp_aidata_wazaid[i]==2 || (temp_aidata_wazaid[i]>=10 && temp_aidata_wazaid[i]<=13)){
							//////力士ごとデータ//////
							memcpy(&bytedata, 
								aidata
								+temp_aidata_jibunid[i]*RIKISISUU*AIDATABYTESUU
								+temp_aidata_aiteid[i]*AIDATABYTESUU
								+(int)(temp_fichi/4),
								sizeof(char));
							//値取り出し
							temp_char=getdatafrombit(bytedata,temp_fichi%4);
							//加算
							if (temp_char<3){
								if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
									temp_char++;
								}
							}
							//値格納
							bytedata=setdatatobit(bytedata,temp_fichi%4,temp_char);
							memcpy(aidata
								+temp_aidata_jibunid[i]*RIKISISUU*AIDATABYTESUU
								+temp_aidata_aiteid[i]*AIDATABYTESUU
								+(int)(temp_fichi/4), 
								&bytedata,
								sizeof(char));
							//////トータルデータ//////
							memcpy(&bytedata, 
								aidata
								+temp_aidata_jibunid[i]*RIKISISUU*AIDATABYTESUU
								+temp_aidata_jibunid[i]*AIDATABYTESUU
								+(int)(temp_fichi/4),
								sizeof(char));
							//値取り出し
							temp_char=getdatafrombit(bytedata,temp_fichi%4);
							//加算
							if (temp_char<3){
								if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
									temp_char++;
								}
							}
							//値格納
							bytedata=setdatatobit(bytedata,temp_fichi%4,temp_char);
							memcpy(aidata
								+temp_aidata_jibunid[i]*RIKISISUU*AIDATABYTESUU
								+temp_aidata_jibunid[i]*AIDATABYTESUU
								+(int)(temp_fichi/4), 
								&bytedata,
								sizeof(char));
							//////データセット済フラグ//////
							sumiflag_win[temp_aidata_wazaid[i]][temp_aidata_yotu[i]][temp_aidata_jibunmigimawasi[i]][temp_aidata_jibunhidarimawasi[i]][temp_aidata_aitemigimawasi[i]][temp_aidata_aitehidarimawasi[i]][temp_aidata_joutaiflag[i]]=1;
							//if( ProcessMessage() == -1 ){mode=1;return ;}
						}
					}
				}
			}else{//負け
				temp_fichi=aidata_fichi[temp_aidata_wazaid[i]][temp_aidata_yotu[i]][temp_aidata_jibunmigimawasi[i]][temp_aidata_jibunhidarimawasi[i]][temp_aidata_aitemigimawasi[i]][temp_aidata_aitehidarimawasi[i]][temp_aidata_joutaiflag[i]];
				if (temp_fichi!=-1){
					if (sumiflag_lost[temp_aidata_wazaid[i]][temp_aidata_yotu[i]][temp_aidata_jibunmigimawasi[i]][temp_aidata_jibunhidarimawasi[i]][temp_aidata_aitemigimawasi[i]][temp_aidata_aitehidarimawasi[i]][temp_aidata_joutaiflag[i]]!=1){
						//////////巻き替えと突き・あてがいのみ/////////
						if (temp_aidata_wazaid[i]==1 || temp_aidata_wazaid[i]==2 || (temp_aidata_wazaid[i]>=10 && temp_aidata_wazaid[i]<=13)){
							//////力士ごとデータ//////
							memcpy(&bytedata, 
								aidata
								+temp_aidata_jibunid[i]*RIKISISUU*AIDATABYTESUU
								+temp_aidata_aiteid[i]*AIDATABYTESUU
								+(int)(temp_fichi/4),
								sizeof(char));
							//値取り出し
							temp_char=getdatafrombit(bytedata,temp_fichi%4);
							//減算
							if (temp_char>0){
								if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
									temp_char--;
								}
							}
							//値格納
							bytedata=setdatatobit(bytedata,temp_fichi%4,temp_char);
							memcpy(aidata
								+temp_aidata_jibunid[i]*RIKISISUU*AIDATABYTESUU
								+temp_aidata_aiteid[i]*AIDATABYTESUU
								+(int)(temp_fichi/4), 
								&bytedata,
								sizeof(char));
							//////トータルデータ//////
							memcpy(&bytedata, 
								aidata
								+temp_aidata_jibunid[i]*RIKISISUU*AIDATABYTESUU
								+temp_aidata_jibunid[i]*AIDATABYTESUU
								+(int)(temp_fichi/4),
								sizeof(char));
							//値取り出し
							temp_char=getdatafrombit(bytedata,temp_fichi%4);
							//減算
							if (temp_char>0){
								if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
									temp_char--;
								}
							}
							//値格納
							bytedata=setdatatobit(bytedata,temp_fichi%4,temp_char);
							memcpy(aidata
								+temp_aidata_jibunid[i]*RIKISISUU*AIDATABYTESUU
								+temp_aidata_jibunid[i]*AIDATABYTESUU
								+(int)(temp_fichi/4), 
								&bytedata,
								sizeof(char));
							//////データセット済フラグ//////
							sumiflag_lost[temp_aidata_wazaid[i]][temp_aidata_yotu[i]][temp_aidata_jibunmigimawasi[i]][temp_aidata_jibunhidarimawasi[i]][temp_aidata_aitemigimawasi[i]][temp_aidata_aitehidarimawasi[i]][temp_aidata_joutaiflag[i]]=1;
							//if( ProcessMessage() == -1 ){mode=1;return ;}
						}
					}
				}
			}
		}
	}
	return;
}

void chokuzen(void)
{
	int i;
	chokuzen_state_kyori=state_kyori;
	chokuzen_offense_state_migiude=offense_state_migiude;
	chokuzen_offense_state_hidariude=offense_state_hidariude;
	chokuzen_defense_state_migiude=defense_state_migiude;
	chokuzen_defense_state_hidariude=defense_state_hidariude;
	chokuzen_offense_action_migiude=offense_action_migiude;
	chokuzen_offense_action_hidariude=offense_action_hidariude;
	chokuzen_defense_action_migiude=defense_action_migiude;
	chokuzen_defense_action_hidariude=defense_action_hidariude;
	chokuzen_offense_action_zengo=offense_action_zengo;
	chokuzen_defense_action_zengo=defense_action_zengo;
	chokuzen_offense_state_jouge=offense_state_jouge;
	chokuzen_defense_state_jouge=defense_state_jouge;
	chokuzen_offense_state_balance=offense_state_balance;
	chokuzen_defense_state_balance=defense_state_balance;
	if (count_temp_aidata==0){
		for (i=0;i<100;i++){
			temp_aidata_jibunid[i]=0;//0~707の画像ID
			temp_aidata_aiteid[i]=0;//0~707の画像ID
			temp_aidata_wazaid[i]=0;
			temp_aidata_yotu[i]=0;
			temp_aidata_jibunmigimawasi[i]=0;
			temp_aidata_jibunhidarimawasi[i]=0;
			temp_aidata_aitemigimawasi[i]=0;
			temp_aidata_aitehidarimawasi[i]=0;
			temp_aidata_joutaiflag[i]=0;
			temp_aidata_jibunid[i]=-1;//0~707の画像ID
			temp_aidata_aiteid[i]=-1;//0~707の画像ID
			temp_aidata_wazaid[i]=-1;
			temp_aidata_yotu[i]=-1;
			temp_aidata_jibunmigimawasi[i]=-1;
			temp_aidata_jibunhidarimawasi[i]=-1;
			temp_aidata_aitemigimawasi[i]=-1;
			temp_aidata_aitehidarimawasi[i]=-1;
			temp_aidata_joutaiflag[i]=-1;
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}
	}
	return;
}


void kiroku_wazadata(char wazaid,int id1,int id2,char id1_higasiornisi,char tatiaigoflag){//
										//id1側から見ての効果
										//id1_higasiornisiは1でid1が東力士をあらわす
										//tatiaigoflagが1→立合い直後の記録2→技ルーチン直後の記録
	int kakuueflag=0;
	int temp_koukasuu_seme=0;
	int temp_koukasuu_rbetuwdata=0;
	int temp_bosuu_rbetuwdata=0;
	char joutaiflag=0;
	char bosuuhenkaflag=0;
	char yotu=0;
	char jibunmigimawasi,jibunhidarimawasi,aitemigimawasi,aitehidarimawasi;
	long temp_fichi=0;
	char bytedata=0;
	char temp_char=0;
	char bytedata_total=0;
	char temp_char_total=0;

	//格上フラグ代入
	if (rikisidata[id1].bandukejun<rikisidata[id2].bandukejun){//格下との取組
		if (rikisidata[id1].bandukenameid+4<=rikisidata[id2].bandukenameid){
			kakuueflag=0;
		}else if(rikisidata[id1].bandukenameid+3==rikisidata[id2].bandukenameid){
			kakuueflag=1;
		}else if(rikisidata[id1].bandukenameid+2==rikisidata[id2].bandukenameid){
			kakuueflag=2;
		}else if(rikisidata[id1].bandukenameid+1==rikisidata[id2].bandukenameid){
			kakuueflag=3;
		}else{
			kakuueflag=4;
		}
	}else{//格上との取組
		if (rikisidata[id1].bandukenameid-4>=rikisidata[id2].bandukenameid){
			kakuueflag=9;
		}else if(rikisidata[id1].bandukenameid-3==rikisidata[id2].bandukenameid){
			kakuueflag=8;
		}else if(rikisidata[id1].bandukenameid-2==rikisidata[id2].bandukenameid){
			kakuueflag=7;
		}else if(rikisidata[id1].bandukenameid-1>=rikisidata[id2].bandukenameid){
			kakuueflag=6;
		}else{
			kakuueflag=5;
		}
	}


	//注射の場合はカウントしない
	if (rikisidata[id1].yao_win==1 || rikisidata[id2].yao_win==1) return;
	if (wazaid<0 || wazaid>21) return;

	if ((offenseid==id1 && id1_higasiornisi==1) || (offenseid==id2 && id1_higasiornisi!=1)){
		higasi_state_jouge=offense_state_jouge;
		nisi_state_jouge=defense_state_jouge;
		higasi_state_balance=offense_state_balance;
		nisi_state_balance=defense_state_balance;
		higasi_state_migiude=offense_state_migiude;
		higasi_state_hidariude=offense_state_hidariude;
		nisi_state_migiude=defense_state_migiude;
		nisi_state_hidariude=defense_state_hidariude;
	}else{
		higasi_state_jouge=defense_state_jouge;
		nisi_state_jouge=offense_state_jouge;
		higasi_state_balance=defense_state_balance;
		nisi_state_balance=offense_state_balance;
		higasi_state_migiude=defense_state_migiude;
		higasi_state_hidariude=defense_state_hidariude;
		nisi_state_migiude=offense_state_migiude;
		nisi_state_hidariude=offense_state_hidariude;
	}
	if (memoryfusokuflag==0){
		///////////////////////////////////////////////////////
		///////////////ここからaidata記録(勝敗後分)//////////////////////
		temp_aidata_jibunid[count_temp_aidata]=offenseid;//0~707の画像ID
		temp_aidata_aiteid[count_temp_aidata]=defenseid;//0~707の画像ID
		temp_aidata_wazaid[count_temp_aidata]=wazaid;

		//四つ
		//	0	間合い遠い
		if (chokuzen_state_kyori==FAR_STATE_KYORI){
			temp_aidata_yotu[count_temp_aidata]=0;
		//	1	右四つ
		}else if ((chokuzen_offense_state_migiude==SITATE_STATE_UDE || chokuzen_offense_state_migiude==SITATETUKAMI_STATE_UDE) 
			&& (chokuzen_offense_state_hidariude==UWATE_STATE_UDE || chokuzen_offense_state_hidariude==UWATETUKAMI_STATE_UDE)){
			temp_aidata_yotu[count_temp_aidata]=1;
		//	2	左四つ
		}else if ((chokuzen_offense_state_migiude==UWATE_STATE_UDE || chokuzen_offense_state_migiude==UWATETUKAMI_STATE_UDE) 
			&& (chokuzen_offense_state_hidariude==SITATE_STATE_UDE || chokuzen_offense_state_hidariude==SITATETUKAMI_STATE_UDE)){
			temp_aidata_yotu[count_temp_aidata]=2;
		//	3	両上手
		}else if ((chokuzen_offense_state_migiude==UWATE_STATE_UDE || chokuzen_offense_state_migiude==UWATETUKAMI_STATE_UDE) 
			&& (chokuzen_offense_state_hidariude==UWATE_STATE_UDE || chokuzen_offense_state_hidariude==UWATETUKAMI_STATE_UDE)){
			temp_aidata_yotu[count_temp_aidata]=3;
		//	4	両差し
		}else if ((chokuzen_offense_state_migiude==SITATE_STATE_UDE || chokuzen_offense_state_migiude==SITATETUKAMI_STATE_UDE) 
			&& (chokuzen_offense_state_hidariude==SITATE_STATE_UDE || chokuzen_offense_state_hidariude==SITATETUKAMI_STATE_UDE)){
			temp_aidata_yotu[count_temp_aidata]=4;
		}
		//廻し
		temp_aidata_jibunmigimawasi[count_temp_aidata]=0;
		temp_aidata_jibunhidarimawasi[count_temp_aidata]=0;
		temp_aidata_aitemigimawasi[count_temp_aidata]=0;
		temp_aidata_aitehidarimawasi[count_temp_aidata]=0;
		if (chokuzen_offense_state_migiude==UWATETUKAMI_STATE_UDE || chokuzen_offense_state_migiude==SITATETUKAMI_STATE_UDE){
			temp_aidata_jibunmigimawasi[count_temp_aidata]=1;
		}
		if (chokuzen_offense_state_hidariude==UWATETUKAMI_STATE_UDE || chokuzen_offense_state_hidariude==SITATETUKAMI_STATE_UDE){
			temp_aidata_jibunhidarimawasi[count_temp_aidata]=1;
		}
		if (chokuzen_defense_state_migiude==UWATETUKAMI_STATE_UDE || chokuzen_defense_state_migiude==SITATETUKAMI_STATE_UDE){
			temp_aidata_aitemigimawasi[count_temp_aidata]=1;
		}
		if (chokuzen_defense_state_hidariude==UWATETUKAMI_STATE_UDE || chokuzen_defense_state_hidariude==SITATETUKAMI_STATE_UDE){
			temp_aidata_aitehidarimawasi[count_temp_aidata]=1;
		}
		//上体の比較
		if (chokuzen_defense_action_zengo==NASI_ACTION_ZENGO
			|| (chokuzen_defense_state_balance<(int)(rikisidata[defenseid].balance/10)+1
					 && chokuzen_defense_state_balance<6)){//前に圧力がかかっていない状態か大きくバランスを崩した状態
			temp_aidata_joutaiflag[count_temp_aidata]=3;//
		}else if (chokuzen_offense_state_jouge>chokuzen_defense_state_jouge){//自低
			temp_aidata_joutaiflag[count_temp_aidata]=2;//
		}else if (chokuzen_offense_state_jouge==chokuzen_defense_state_jouge){//同じ
			temp_aidata_joutaiflag[count_temp_aidata]=1;//
		}else{
			temp_aidata_joutaiflag[count_temp_aidata]=0;//
		}
		//カウント
		if (count_temp_aidata<99){
			count_temp_aidata++;
		}


		///////////////////////////////////////////////////////
		///////////////ここからaidata記録(毎ターン分)//////////////////////

		//四つ
		//	0	間合い遠い
		if (chokuzen_state_kyori==FAR_STATE_KYORI){
			yotu=0;
		//	1	右四つ
		}else if ((chokuzen_offense_state_migiude==SITATE_STATE_UDE || chokuzen_offense_state_migiude==SITATETUKAMI_STATE_UDE) 
			&& (chokuzen_offense_state_hidariude==UWATE_STATE_UDE || chokuzen_offense_state_hidariude==UWATETUKAMI_STATE_UDE)){
			yotu=1;
		//	2	左四つ
		}else if ((chokuzen_offense_state_migiude==UWATE_STATE_UDE || chokuzen_offense_state_migiude==UWATETUKAMI_STATE_UDE) 
			&& (chokuzen_offense_state_hidariude==SITATE_STATE_UDE || chokuzen_offense_state_hidariude==SITATETUKAMI_STATE_UDE)){
			yotu=2;
		//	3	両上手
		}else if ((chokuzen_offense_state_migiude==UWATE_STATE_UDE || chokuzen_offense_state_migiude==UWATETUKAMI_STATE_UDE) 
			&& (chokuzen_offense_state_hidariude==UWATE_STATE_UDE || chokuzen_offense_state_hidariude==UWATETUKAMI_STATE_UDE)){
			yotu=3;
		//	4	両差し
		}else if ((chokuzen_offense_state_migiude==SITATE_STATE_UDE || chokuzen_offense_state_migiude==SITATETUKAMI_STATE_UDE) 
			&& (chokuzen_offense_state_hidariude==SITATE_STATE_UDE || chokuzen_offense_state_hidariude==SITATETUKAMI_STATE_UDE)){
			yotu=4;
		}
		//廻し
		jibunmigimawasi=0;
		jibunhidarimawasi=0;
		aitemigimawasi=0;
		aitehidarimawasi=0;
		if (chokuzen_offense_state_migiude==UWATETUKAMI_STATE_UDE || chokuzen_offense_state_migiude==SITATETUKAMI_STATE_UDE){
			jibunmigimawasi=1;
		}
		if (chokuzen_offense_state_hidariude==UWATETUKAMI_STATE_UDE || chokuzen_offense_state_hidariude==SITATETUKAMI_STATE_UDE){
			jibunhidarimawasi=1;
		}
		if (chokuzen_defense_state_migiude==UWATETUKAMI_STATE_UDE || chokuzen_defense_state_migiude==SITATETUKAMI_STATE_UDE){
			aitemigimawasi=1;
		}
		if (chokuzen_defense_state_hidariude==UWATETUKAMI_STATE_UDE || chokuzen_defense_state_hidariude==SITATETUKAMI_STATE_UDE){
			aitehidarimawasi=1;
		}
		//上体の比較
		if (chokuzen_defense_action_zengo==NASI_ACTION_ZENGO
			|| (chokuzen_defense_state_balance<(int)(rikisidata[defenseid].balance/10)+1
					 && chokuzen_defense_state_balance<6)){//前に圧力がかかっていない状態か大きくバランスを崩した状態
			joutaiflag=3;//
		}else if (chokuzen_offense_state_jouge>chokuzen_defense_state_jouge){//自低
			joutaiflag=2;//
		}else if (chokuzen_offense_state_jouge==chokuzen_defense_state_jouge){//同じ
			joutaiflag=1;//
		}else{
			joutaiflag=0;//
		}

		temp_fichi=aidata_fichi[wazaid][yotu][jibunmigimawasi][jibunhidarimawasi][aitemigimawasi][aitehidarimawasi][joutaiflag];
	/*
	if (offenseid==215){
	ClearDrawScreen();
	DrawFormatString(0,460,CRWHITE,"ルーチン内temp_fichi=%d,四つ=%d,右自=%d,左自=%d,右相手=%d,左相手=%d,上体=%d",
	temp_fichi,
	yotu,
	jibunmigimawasi,
	jibunhidarimawasi,
	aitemigimawasi,
	aitehidarimawasi,
	joutaiflag
	);
	ScreenFlip();
	WaitKey();
	}
	*/
		//if( ProcessMessage() == -1 ){mode=1;return ;}
		if (temp_fichi!=-1){
			//////力士ごとデータ//////
			//値取り出し
			memcpy(&bytedata, 
				aidata
				+id1*RIKISISUU*AIDATABYTESUU
				+id2*AIDATABYTESUU
				+(int)(temp_fichi/4),
				sizeof(char));
			temp_char=getdatafrombit(bytedata,temp_fichi%4);
			//////トータルデータ//////
			//値取り出し
			memcpy(&bytedata_total, 
				aidata
				+id1*RIKISISUU*AIDATABYTESUU
				+id1*AIDATABYTESUU
				+(int)(temp_fichi/4),
				sizeof(char));
			temp_char_total=getdatafrombit(bytedata_total,temp_fichi%4);
			//※突きとあてがいは後処理にしてみたのでここではしない
			if (wazaid==8 && chokuzen_defense_action_zengo==MAE_ACTION_ZENGO){
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (ichi_lastturn<state_ichi){
						if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
							//加算
							if (temp_char<3){
								temp_char++;
							}
							if (temp_char_total<3){
								temp_char_total++;
							}
						}
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (ichi_lastturn>state_ichi){
						if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
							//加算
							if (temp_char<3){
								temp_char++;
							}
							if (temp_char_total<3){
								temp_char_total++;
							}
						}
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}
			}else if (wazaid==8 && chokuzen_defense_action_zengo==NASI_ACTION_ZENGO){
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (ichi_lastturn<state_ichi){
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (ichi_lastturn>state_ichi){
						//加算
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}
			}
			if (wazaid>=14){
				if (chokuzen_defense_state_balance>defense_state_balance){
					if (defense_state_balance<1){
						if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
							//加算
							if (temp_char<3){
								temp_char++;
							}
							if (temp_char_total<3){
								temp_char_total++;
							}
						}
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}else{
					if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
						//減算
						if (temp_char>0){
							temp_char--;
						}
						if (temp_char_total>0){
							temp_char_total--;
						}
						//減算
						if (temp_char>0){
							temp_char--;
						}
						if (temp_char_total>0){
							temp_char_total--;
						}
					}
				}
	 			if (chokuzen_offense_state_balance>offense_state_balance){
					if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
						//減算
						if (temp_char>0){
							temp_char--;
						}
						if (temp_char_total>0){
							temp_char_total--;
						}
						//減算
						if (temp_char>0){
							temp_char--;
						}
						if (temp_char_total>0){
							temp_char_total--;
						}
					}
				}
			}
/*
			if (wazaid==2){
				if (chokuzen_defense_action_migiude==TUKI_ACTION_UDE || chokuzen_defense_action_hidariude==TUKI_ACTION_UDE){
					if (state_kyori==MIDDLE_STATE_KYORI){
						//加算
						if (temp_char<3){
							temp_char++;
						}
						if (temp_char_total<3){
							temp_char_total++;
						}
					}else{
						//減算
						if (temp_char>0){
							temp_char--;
						}
						if (temp_char_total>0){
							temp_char_total--;
						}
					}
				}
			}
*/
			if (wazaid==4){//右上廻し狙い
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (higasi_state_migiude==UWATETUKAMI_STATE_UDE){
						if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
							//加算
							if (temp_char<3){
								temp_char++;
							}
							if (temp_char_total<3){
								temp_char_total++;
							}
						}
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (nisi_state_migiude==UWATETUKAMI_STATE_UDE){
						if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
							//加算
							if (temp_char<3){
								temp_char++;
							}
							if (temp_char_total<3){
								temp_char_total++;
							}
						}
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}
			}
			if (wazaid==5){//左上廻し狙い
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (higasi_state_hidariude==UWATETUKAMI_STATE_UDE){
						if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
							//加算
							if (temp_char<3){
								temp_char++;
							}
							if (temp_char_total<3){
								temp_char_total++;
							}
						}
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (nisi_state_hidariude==UWATETUKAMI_STATE_UDE){
						if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
							//加算
							if (temp_char<3){
								temp_char++;
							}
							if (temp_char_total<3){
								temp_char_total++;
							}
						}
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}
			}
			if (wazaid==6){//右下廻し狙い
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (higasi_state_migiude==SITATETUKAMI_STATE_UDE){
						if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
							//加算
							if (temp_char<3){
								temp_char++;
							}
							if (temp_char_total<3){
								temp_char_total++;
							}
						}
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (nisi_state_migiude==SITATETUKAMI_STATE_UDE){
						if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
							//加算
							if (temp_char<3){
								temp_char++;
							}
							if (temp_char_total<3){
								temp_char_total++;
							}
						}
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}
			}
			if (wazaid==7){//左下廻し狙い
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (higasi_state_hidariude==SITATETUKAMI_STATE_UDE){
						if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
							//加算
							if (temp_char<3){
								temp_char++;
							}
							if (temp_char_total<3){
								temp_char_total++;
							}
						}
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (nisi_state_hidariude==SITATETUKAMI_STATE_UDE){
						if (GetRand(99)<hyoka_upkakuritu[kakuueflag]){
							//加算
							if (temp_char<3){
								temp_char++;
							}
							if (temp_char_total<3){
								temp_char_total++;
							}
						}
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}
			}
			if (wazaid==10){//"右上へ替",//10
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (higasi_state_migiude==UWATE_STATE_UDE){
/*
						//加算
						if (temp_char<3){
							temp_char++;
						}
*/
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (nisi_state_migiude==UWATE_STATE_UDE){
/*
						//加算
						if (temp_char<3){
							temp_char++;
						}
*/
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}
			}
			if (wazaid==11){//"左上へ替",//11
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (higasi_state_hidariude==UWATE_STATE_UDE){
/*
						//加算
						if (temp_char<3){
							temp_char++;
						}
*/
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (nisi_state_hidariude==UWATE_STATE_UDE){
/*
						//加算
						if (temp_char<3){
							temp_char++;
						}
*/
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}
			}
			if (wazaid==12){//"右下へ替",//12
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (higasi_state_migiude==SITATE_STATE_UDE){
/*
						//加算
						if (temp_char<3){
							temp_char++;
						}
*/
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (nisi_state_migiude==SITATE_STATE_UDE){
/*
						//加算
						if (temp_char<3){
							temp_char++;
						}
*/
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}
			}
			if (wazaid==13){//"左下へ替",//13
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (higasi_state_hidariude==SITATE_STATE_UDE){
/*
						//加算
						if (temp_char<3){
							temp_char++;
						}
*/
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (nisi_state_hidariude==SITATE_STATE_UDE){
/*
						//加算
						if (temp_char<3){
							temp_char++;
						}
*/
					}else{
						if (GetRand(99)<hyoka_downkakuritu[kakuueflag]){
							//減算
							if (temp_char>0){
								temp_char--;
							}
							if (temp_char_total>0){
								temp_char_total--;
							}
						}
					}
				}
			}
			//力士ごとデータ値格納
			bytedata=setdatatobit(bytedata,temp_fichi%4,temp_char);
			memcpy(aidata
				+id1*RIKISISUU*AIDATABYTESUU
				+id2*AIDATABYTESUU
				+(int)(temp_fichi/4), 
				&bytedata,
				sizeof(char));
			//トータルデータ値格納
			bytedata_total=setdatatobit(bytedata_total,temp_fichi%4,temp_char_total);
			memcpy(aidata
				+id1*RIKISISUU*AIDATABYTESUU
				+id1*AIDATABYTESUU
				+(int)(temp_fichi/4), 
				&bytedata_total,
				sizeof(char));
		}
	}
	/////////////////////////////////////////////////////////
	//if( ProcessMessage() == -1 ){mode=1;return ;}
	////////////////ここからwazadata記録/////////////////////
		////////////////////////////////////////////////////////
		//////////////ここからwazadata記録//////////////////////
		if (tatiaigoflag==1){//立合い直後の場合
		}else{//技効果の場合
		//	extern char wazadata_kouka[22][RIKISISUU][5];//効果(127~-127)
		//wazadata_kouka[技ID][力士ID][四つの状況]
		//効果を記録する(+127～-127)
	/*	四つの状況
		0→間合い遠い
		1→右四つ
		2→左四つ
		3→両上手
		4→両差し
	*/
		//四つについて
		//	0	間合い遠い
		if (chokuzen_state_kyori==FAR_STATE_KYORI){
			yotu=0;
		//	1	右四つ
		}else if ((chokuzen_offense_state_migiude==SITATE_STATE_UDE || chokuzen_offense_state_migiude==SITATETUKAMI_STATE_UDE) 
			&& (chokuzen_offense_state_hidariude==UWATE_STATE_UDE || chokuzen_offense_state_hidariude==UWATETUKAMI_STATE_UDE)){
			yotu=1;
		//	2	左四つ
		}else if ((chokuzen_offense_state_migiude==UWATE_STATE_UDE || chokuzen_offense_state_migiude==UWATETUKAMI_STATE_UDE) 
			&& (chokuzen_offense_state_hidariude==SITATE_STATE_UDE || chokuzen_offense_state_hidariude==SITATETUKAMI_STATE_UDE)){
			yotu=2;
		//	3	両上手
		}else if ((chokuzen_offense_state_migiude==UWATE_STATE_UDE || chokuzen_offense_state_migiude==UWATETUKAMI_STATE_UDE) 
			&& (chokuzen_offense_state_hidariude==UWATE_STATE_UDE || chokuzen_offense_state_hidariude==UWATETUKAMI_STATE_UDE)){
			yotu=3;
		//	4	両差し
		}else if ((chokuzen_offense_state_migiude==SITATE_STATE_UDE || chokuzen_offense_state_migiude==SITATETUKAMI_STATE_UDE) 
			&& (chokuzen_offense_state_hidariude==SITATE_STATE_UDE || chokuzen_offense_state_hidariude==SITATETUKAMI_STATE_UDE)){
			yotu=4;
		}

		//効果数増
		{
			temp_koukasuu_seme=0;
			temp_koukasuu_seme=wazadata_kouka_seme[wazaid][id1][yotu];
			temp_koukasuu_rbetuwdata=0;
			temp_bosuu_rbetuwdata=0;
			if (AIkeikoflag==0){
				if (memoryfusokuflag==0 && memorykakuchouflag==1){
					//値取り出し
					memcpy(&temp_koukasuu_rbetuwdata, 
						rbetuwdata_kouka
						+id1*RIKISISUU*22*5
						+id2*22*5
						+wazaid*5
						+yotu,
						sizeof(unsigned short int));
					//値取り出し
					memcpy(&temp_bosuu_rbetuwdata, 
						rbetuwdata_bosuu
						+id1*RIKISISUU*22*5
						+id2*22*5
						+wazaid*5
						+yotu,
						sizeof(unsigned short int));
				}
			}
			if ((wazaid==1 || wazaid==8) && chokuzen_defense_action_zengo==MAE_ACTION_ZENGO){
//			if (wazaid==1 || wazaid==8){
				//bosuuは効果ありなしにかかわらずプラス
				bosuuhenkaflag=1;
				if (AIkeikoflag==0){
					if (2147483647>wazadata_bosuu_seme[wazaid][id1][yotu]){
						wazadata_bosuu_seme[wazaid][id1][yotu]++;
					}
					if (65535>temp_bosuu_rbetuwdata){
						temp_bosuu_rbetuwdata++;
					}
				}
				if (65535>lastwazadata_bosuu_seme[wazaid][id1][yotu]){
					lastwazadata_bosuu_seme[wazaid][id1][yotu]++;
				}
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (ichi_lastturn<state_ichi){
						if (2147483647>temp_koukasuu_seme){
							temp_koukasuu_seme++;
						}
						if (65535>temp_koukasuu_rbetuwdata){
							temp_koukasuu_rbetuwdata++;
						}


					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (ichi_lastturn>state_ichi){
						if (2147483647>temp_koukasuu_seme){
							temp_koukasuu_seme++;
						}
						if (65535>temp_koukasuu_rbetuwdata){
							temp_koukasuu_rbetuwdata++;
						}
					}
				}
			}
			if (wazaid>=14){
				if (chokuzen_defense_state_balance>=6
					|| chokuzen_defense_state_balance==(int)(rikisidata[defenseid].balance/10)+1){
					bosuuhenkaflag=1;
					//bosuuは効果ありなしにかかわらずプラス
					if (AIkeikoflag==0){
						if (2147483647>wazadata_bosuu_seme[wazaid][id1][yotu]){
							wazadata_bosuu_seme[wazaid][id1][yotu]++;
						}
						if (65535>temp_bosuu_rbetuwdata){
							temp_bosuu_rbetuwdata++;
						}
					}
					if (65535>lastwazadata_bosuu_seme[wazaid][id1][yotu]){
						lastwazadata_bosuu_seme[wazaid][id1][yotu]++;
					}
					if (defense_state_balance<(int)(rikisidata[defenseid].balance/10)+1
					 && defense_state_balance<6){
						if (2147483647>temp_koukasuu_seme){
							temp_koukasuu_seme++;
						}
						if (65535>temp_koukasuu_rbetuwdata){
							temp_koukasuu_rbetuwdata++;
						}
					}
				}
			}
			if (wazaid==2){
				if (chokuzen_defense_action_migiude==TUKI_ACTION_UDE || chokuzen_defense_action_hidariude==TUKI_ACTION_UDE){
					bosuuhenkaflag=1;
					//bosuuは効果ありなしにかかわらずプラス
					if (AIkeikoflag==0){
						if (2147483647>wazadata_bosuu_seme[wazaid][id1][yotu]){
							wazadata_bosuu_seme[wazaid][id1][yotu]++;
						}
						if (65535>temp_bosuu_rbetuwdata){
							temp_bosuu_rbetuwdata++;
						}
					}
					if (65535>lastwazadata_bosuu_seme[wazaid][id1][yotu]){
						lastwazadata_bosuu_seme[wazaid][id1][yotu]++;
					}
					if (state_kyori==MIDDLE_STATE_KYORI){
						if (2147483647>temp_koukasuu_seme){
							temp_koukasuu_seme++;
						}
						if (65535>temp_koukasuu_rbetuwdata){
							temp_koukasuu_rbetuwdata++;
						}
					}
				}
			}
			if (wazaid==4){//右上廻し狙い
				bosuuhenkaflag=1;
				//bosuuは効果ありなしにかかわらずプラス
				if (AIkeikoflag==0){
					if (2147483647>wazadata_bosuu_seme[wazaid][id1][yotu]){
						wazadata_bosuu_seme[wazaid][id1][yotu]++;
					}
					if (65535>temp_bosuu_rbetuwdata){
						temp_bosuu_rbetuwdata++;
					}
				}
				if (65535>lastwazadata_bosuu_seme[wazaid][id1][yotu]){
					lastwazadata_bosuu_seme[wazaid][id1][yotu]++;
				}
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (higasi_state_migiude==UWATETUKAMI_STATE_UDE){
						if (2147483647>temp_koukasuu_seme){
							temp_koukasuu_seme++;
						}
						if (65535>temp_koukasuu_rbetuwdata){
							temp_koukasuu_rbetuwdata++;
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (nisi_state_migiude==UWATETUKAMI_STATE_UDE){
						if (2147483647>temp_koukasuu_seme){
							temp_koukasuu_seme++;
						}
						if (65535>temp_koukasuu_rbetuwdata){
							temp_koukasuu_rbetuwdata++;
						}
					}
				}
			}
			if (wazaid==5){//左上廻し狙い
				bosuuhenkaflag=1;
				//bosuuは効果ありなしにかかわらずプラス
				if (AIkeikoflag==0){
					if (2147483647>wazadata_bosuu_seme[wazaid][id1][yotu]){
						wazadata_bosuu_seme[wazaid][id1][yotu]++;
					}
					if (65535>temp_bosuu_rbetuwdata){
						temp_bosuu_rbetuwdata++;
					}
				}
				if (65535>lastwazadata_bosuu_seme[wazaid][id1][yotu]){
					lastwazadata_bosuu_seme[wazaid][id1][yotu]++;
				}
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (higasi_state_hidariude==UWATETUKAMI_STATE_UDE){
						if (2147483647>temp_koukasuu_seme){
							temp_koukasuu_seme++;
						}
						if (65535>temp_koukasuu_rbetuwdata){
							temp_koukasuu_rbetuwdata++;
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (nisi_state_hidariude==UWATETUKAMI_STATE_UDE){
						if (2147483647>temp_koukasuu_seme){
							temp_koukasuu_seme++;
						}
						if (65535>temp_koukasuu_rbetuwdata){
							temp_koukasuu_rbetuwdata++;
						}
					}
				}
			}
			if (wazaid==6){//右下廻し狙い
				bosuuhenkaflag=1;
				//bosuuは効果ありなしにかかわらずプラス
				if (AIkeikoflag==0){
					if (2147483647>wazadata_bosuu_seme[wazaid][id1][yotu]){
						wazadata_bosuu_seme[wazaid][id1][yotu]++;
					}
					if (65535>temp_bosuu_rbetuwdata){
						temp_bosuu_rbetuwdata++;
					}
				}
				if (65535>lastwazadata_bosuu_seme[wazaid][id1][yotu]){
					lastwazadata_bosuu_seme[wazaid][id1][yotu]++;
				}
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (higasi_state_migiude==SITATETUKAMI_STATE_UDE){
						if (2147483647>temp_koukasuu_seme){
							temp_koukasuu_seme++;
						}
						if (65535>temp_koukasuu_rbetuwdata){
							temp_koukasuu_rbetuwdata++;
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (nisi_state_migiude==SITATETUKAMI_STATE_UDE){
						if (2147483647>temp_koukasuu_seme){
							temp_koukasuu_seme++;
						}
						if (65535>temp_koukasuu_rbetuwdata){
							temp_koukasuu_rbetuwdata++;
						}
					}
				}
			}
			if (wazaid==7){//左下廻し狙い
				bosuuhenkaflag=1;
				//bosuuは効果ありなしにかかわらずプラス
				if (AIkeikoflag==0){
					if (2147483647>wazadata_bosuu_seme[wazaid][id1][yotu]){
						wazadata_bosuu_seme[wazaid][id1][yotu]++;
					}
					if (65535>temp_bosuu_rbetuwdata){
						temp_bosuu_rbetuwdata++;
					}
				}
				if (65535>lastwazadata_bosuu_seme[wazaid][id1][yotu]){
					lastwazadata_bosuu_seme[wazaid][id1][yotu]++;
				}
				if (id1_higasiornisi==1){//id1が東力士の場合
					//東力士効果ありパターン
					if (higasi_state_hidariude==SITATETUKAMI_STATE_UDE){
						if (2147483647>temp_koukasuu_seme){
							temp_koukasuu_seme++;
						}
						if (65535>temp_koukasuu_rbetuwdata){
							temp_koukasuu_rbetuwdata++;
						}
					}
				}else{//id1が西力士の場合
					//西力士効果ありパターン
					if (nisi_state_hidariude==SITATETUKAMI_STATE_UDE){
						if (2147483647>temp_koukasuu_seme){
							temp_koukasuu_seme++;
						}
						if (65535>temp_koukasuu_rbetuwdata){
							temp_koukasuu_rbetuwdata++;
						}
					}
				}
			}
			if (wazaid==10){//右上替え
				bosuuhenkaflag=1;
				//bosuuは効果ありなしにかかわらずプラス
				if (AIkeikoflag==0){
					if (2147483647>wazadata_bosuu_seme[wazaid][id1][yotu]){
						wazadata_bosuu_seme[wazaid][id1][yotu]++;
					}
					if (65535>temp_bosuu_rbetuwdata){
						temp_bosuu_rbetuwdata++;
					}
				}
				//効果ありパターン
				if (offense_state_migiude==UWATE_STATE_UDE){
					if (2147483647>temp_koukasuu_seme){
						temp_koukasuu_seme++;
					}
					if (65535>temp_koukasuu_rbetuwdata){
						temp_koukasuu_rbetuwdata++;
					}
				}
			}
			if (wazaid==11){//左上替え
				bosuuhenkaflag=1;
				//bosuuは効果ありなしにかかわらずプラス
				if (AIkeikoflag==0){
					if (2147483647>wazadata_bosuu_seme[wazaid][id1][yotu]){
						wazadata_bosuu_seme[wazaid][id1][yotu]++;
					}
					if (65535>temp_bosuu_rbetuwdata){
						temp_bosuu_rbetuwdata++;
					}
				}
				if (65535>lastwazadata_bosuu_seme[wazaid][id1][yotu]){
					lastwazadata_bosuu_seme[wazaid][id1][yotu]++;
				}
				//効果ありパターン
				if (offense_state_hidariude==UWATE_STATE_UDE){
					if (2147483647>temp_koukasuu_seme){
						temp_koukasuu_seme++;
					}
					if (65535>temp_koukasuu_rbetuwdata){
						temp_koukasuu_rbetuwdata++;
					}
				}
			}
			if (wazaid==12){//右下替え
				bosuuhenkaflag=1;
				//bosuuは効果ありなしにかかわらずプラス
				if (AIkeikoflag==0){
					if (2147483647>wazadata_bosuu_seme[wazaid][id1][yotu]){
						wazadata_bosuu_seme[wazaid][id1][yotu]++;
					}
					if (65535>temp_bosuu_rbetuwdata){
						temp_bosuu_rbetuwdata++;
					}
				}
				if (65535>lastwazadata_bosuu_seme[wazaid][id1][yotu]){
					lastwazadata_bosuu_seme[wazaid][id1][yotu]++;
				}
				//効果ありパターン
				if (offense_state_migiude==SITATE_STATE_UDE){
					if (2147483647>temp_koukasuu_seme){
						temp_koukasuu_seme++;
					}
					if (65535>temp_koukasuu_rbetuwdata){
						temp_koukasuu_rbetuwdata++;
					}
				}
			}
			if (wazaid==13){//左下替え
				bosuuhenkaflag=1;
				//bosuuは効果ありなしにかかわらずプラス
				if (AIkeikoflag==0){
					if (2147483647>wazadata_bosuu_seme[wazaid][id1][yotu]){
						wazadata_bosuu_seme[wazaid][id1][yotu]++;
					}
					if (65535>temp_bosuu_rbetuwdata){
						temp_bosuu_rbetuwdata++;
					}
				}
				if (65535>lastwazadata_bosuu_seme[wazaid][id1][yotu]){
					lastwazadata_bosuu_seme[wazaid][id1][yotu]++;
				}
				//効果ありパターン
				if (offense_state_hidariude==SITATE_STATE_UDE){
					if (2147483647>temp_koukasuu_seme){
						temp_koukasuu_seme++;
					}
					if (65535>temp_koukasuu_rbetuwdata){
						temp_koukasuu_rbetuwdata++;
					}
				}
			}

		}

		if (bosuuhenkaflag==1){
			//kouka確定
			lastwazadata_kouka_seme[wazaid][id1][yotu]
			+=(temp_koukasuu_seme-wazadata_kouka_seme[wazaid][id1][yotu]);//差が今回の増加分のはず
			if (AIkeikoflag==0){
				wazadata_kouka_seme[wazaid][id1][yotu]
				=temp_koukasuu_seme;
				if (memoryfusokuflag==0 && memorykakuchouflag==1){
					//kouka確定
					//値格納
					memcpy(rbetuwdata_kouka
						+id1*RIKISISUU*22*5
						+id2*22*5
						+wazaid*5
						+yotu,
						&temp_koukasuu_rbetuwdata,
						sizeof(unsigned short int));
					//値格納
					memcpy(rbetuwdata_bosuu
						+id1*RIKISISUU*22*5
						+id2*22*5
						+wazaid*5
						+yotu,
						&temp_bosuu_rbetuwdata,
						sizeof(unsigned short int));
				}
			}
		}

	}//技効果判断の場合の終端括弧
	//if( ProcessMessage() == -1 ){mode=1;return ;}
	return;
}

void wazabunsekihyoji(int id)
{
	int temp_koukasuu_rbetuwdata=0;
	int temp_bosuu_rbetuwdata=0;
	int temp_koukasuu_rbetutdata=0;
	int temp_bosuu_rbetutdata=0;
	int hyoji_wazaid=8;
	int i,count;
	int ritu=0;
	int shoki_x=190;
	int x;
	int y=180;
	int gyoukan=20;
	int hosei_y=0;
	int hyoji_pid=0;
	char *joutaistring[] =
	{
		"自分の方が高い" ,
		"同じ高さ",
		"自分の方が低い",
		"相手からの圧力がないか、相手がバランスを崩している",
		NULL
	} ;	
	char *arinasistring[] =
	{
		"無" ,
		"有",
		NULL
	} ;	
	char *kumitestring[] =
	{
		"間合遠い" ,
		"右四つ",
		"左四つ",
		"両上手",
		"両差し",
		NULL
	} ;	
	char *neraistring[] =
	{
		"突き押し" ,
		"右四つ",
		"左四つ",
		"両上手",
		"両差し",
		NULL
	} ;	
	char *ikioistring[] =
	{
		"全力" ,
		"強く",
		"受け",
		"変化",
		NULL
	} ;	
	char *hyoukastring[] =
	{
		"Ｄ" ,
		"Ｃ",
		"Ｂ",
		"Ａ",
		"Ｓ",//計算上はないはずだけど、念のため
		NULL
	} ;	
	char *wazanamestring[] =
	{
		"なし" ,//0
		"突っ張り",//1
		"あてがい",//2
		"中間処理",//3
		"右上廻狙",//4
		"左上廻狙",//5
		"右下廻狙",//6
		"左下廻狙",//7
		"寄り",//8
		"現状維持",//9
		"右上へ替",//10
		"左上へ替",//11
		"右下へ替",//12
		"左下へ替",//13
		"右上投",//14
		"左上投",//15
		"右下投",//16
		"左下投",//17
		"右小投",//18
		"左小投",//19
		"右掬投",//20
		"左掬投",//21
		NULL
	} ;	
	if (rikisidata[id].aitekonbasho[day-11]<0 || rikisidata[id].aitekonbasho[day-11]>=RIKISISUU){
		wazabunsekipage=0;
	}
	if (memorykakuchouflag==0 || memoryfusokuflag==1){
		if (wazabunsekipage==3) wazabunsekipage=0;
	}
	if (id==bunsekikeikoaite_id){
		bunsekikeikoaite_id=bandukejunid[0];
		if (id==bunsekikeikoaite_id){
			bunsekikeikoaite_id=bandukejunid[1];
		}
	}

HYOJI:
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	game_main_backscreen();//基本画面表示
	DrawBox(0,0,639,20,CRBACK,TRUE);
	if (wazabunsekipage==4 && lastkeiko_year[id]!=0){

		DrawFormatStringToHandle(10,5,CRWHITE,FontHandle12,"%sの直近稽古の技選択と成功率(対直近稽古力士合計、注射の場合は除く)",namestring[id]);

		DrawFormatStringToHandle(187,353,CRWHITE,FontHandle12,"※%d年%d月%d日目%sとの直近稽古の技選択と成功率",lastkeiko_year[id],lastkeiko_month[id],lastkeiko_day[id]-10,lastkeiko_aitenamestring[id]);

		DrawString(187,369,"左リストをクリックで表示内容を変更できます",CRWHITE);
		DrawStringToHandle(187,369+20,"※寄り・突っ張りの成功は、相手が前に圧力をかけてきているときに\n　少しでも前進できた場合です。",CRWHITE,FontHandle12);
		DrawStringToHandle(187,369+20+30,"※投げの成功は、相手のバランスを大きく崩せた場合です。",CRWHITE,FontHandle12);
		DrawStringToHandle(187,369+20+30+20,"※あてがいの成功は、相手が突っ張ってきたときに\n　間合いを詰めることができた場合です。",CRWHITE,FontHandle12);

		DrawString(200,25,"直近稽古の立合い→勝利率(勝利率・試行数)",CRWHITE);
		DrawStringToHandle(187,y1[4]-6,"※立合いの狙いは「意図」、勢いは「結果」での表示",CRWHITE,FontHandle12);

		DrawString(200,y1[0]-30-32+100+20,"直近稽古の技成功率(成功率・試行数)",CRWHITE);

		count=0;
		hosei_y=130;
		for (hyoji_pid=0;hyoji_pid<20;hyoji_pid++){
			x=shoki_x;
			if (tatiaidata_bosuu_seme[id][hyoji_pid]!=0){
				ritu=(int)(((double)lasttatiaidata_kouka_seme[id][hyoji_pid]
					/lasttatiaidata_bosuu_seme[id][hyoji_pid])
					*100);
			}else{
				ritu=0;
			}
			if (hyoji_kumiteid==0){
				if (hyoji_pid>=0 && hyoji_pid<=3){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<lasttatiaidata_bosuu_seme[id][hyoji_pid]){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lasttatiaidata_bosuu_seme[id][hyoji_pid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lasttatiaidata_bosuu_seme[id][hyoji_pid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==1){
				if (hyoji_pid>=4 && hyoji_pid<=7){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<lasttatiaidata_bosuu_seme[id][hyoji_pid]){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lasttatiaidata_bosuu_seme[id][hyoji_pid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lasttatiaidata_bosuu_seme[id][hyoji_pid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==2){
				if (hyoji_pid>=8 && hyoji_pid<=11){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<lasttatiaidata_bosuu_seme[id][hyoji_pid]){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lasttatiaidata_bosuu_seme[id][hyoji_pid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lasttatiaidata_bosuu_seme[id][hyoji_pid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==3){
				if (hyoji_pid>=12 && hyoji_pid<=15){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<lasttatiaidata_bosuu_seme[id][hyoji_pid]){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lasttatiaidata_bosuu_seme[id][hyoji_pid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lasttatiaidata_bosuu_seme[id][hyoji_pid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==4){
				if (hyoji_pid>=16 && hyoji_pid<=19){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<lasttatiaidata_bosuu_seme[id][hyoji_pid]){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lasttatiaidata_bosuu_seme[id][hyoji_pid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lasttatiaidata_bosuu_seme[id][hyoji_pid]);
					}
					count++;
				}
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}
		//lastwazadata_kouka_seme[技ID][力士ID][四つの状況]
		count=0;
		for (hyoji_wazaid=0;hyoji_wazaid<22;hyoji_wazaid++){
			if (lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]!=0){
				ritu=(int)(((double)lastwazadata_kouka_seme[hyoji_wazaid][id][hyoji_kumiteid]
					/lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid])
					*100);
			}else{
				ritu=0;
			}
			if (hyoji_kumiteid==0){
				if (hyoji_wazaid==1 || hyoji_wazaid==2){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==1){
				if (hyoji_wazaid==10 || hyoji_wazaid==13 || hyoji_wazaid==5 || hyoji_wazaid==6 || hyoji_wazaid==8 || hyoji_wazaid==15 || hyoji_wazaid==16 || hyoji_wazaid==19 ||hyoji_wazaid==20){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==2){
				if (hyoji_wazaid==11 || hyoji_wazaid==12 || hyoji_wazaid==4 || hyoji_wazaid==7 || hyoji_wazaid==8 || hyoji_wazaid==14 || hyoji_wazaid==17 || hyoji_wazaid==18 ||hyoji_wazaid==21){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==3){
				if (hyoji_wazaid==12 || hyoji_wazaid==13 || hyoji_wazaid==4 || hyoji_wazaid==5 || hyoji_wazaid==8 || hyoji_wazaid==14 || hyoji_wazaid==15 || hyoji_wazaid==18 ||hyoji_wazaid==19){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==4){
				if (hyoji_wazaid==10 || hyoji_wazaid==11 || hyoji_wazaid==6 || hyoji_wazaid==7 || hyoji_wazaid==8 || hyoji_wazaid==16 || hyoji_wazaid==17 || hyoji_wazaid==20 ||hyoji_wazaid==21){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",lastwazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}
					count++;
				}
			}
		}
	}else if (wazabunsekipage==0){
		DrawFormatStringToHandle(200,5,CRWHITE,FontHandle12,"%sの技選択と成功率(対全力士合計、注射の場合は除く)",namestring[id]);
		DrawString(187,369,"左リストをクリックで表示内容を変更できます",CRWHITE);
		DrawStringToHandle(187,369+20,"※寄り・突っ張りの成功は、相手が前に圧力をかけてきているときに\n　少しでも前進できた場合です。",CRWHITE,FontHandle12);
		DrawStringToHandle(187,369+20+30,"※投げの成功は、相手のバランスを大きく崩せた場合です。",CRWHITE,FontHandle12);
		DrawStringToHandle(187,369+20+30+20,"※あてがいの成功は、相手が突っ張ってきたときに\n　間合いを詰めることができた場合です。",CRWHITE,FontHandle12);

		DrawString(200,25,"対全力士合計の立合い→勝利率(勝利率・試行数)",CRWHITE);
		DrawStringToHandle(187,y1[4]-6,"※立合いの狙いは「意図」、勢いは「結果」での表示",CRWHITE,FontHandle12);

		DrawString(200,y1[0]-30-32+100+20,"対全力士合計の技成功率(成功率・試行数)",CRWHITE);

		count=0;
		hosei_y=130;
		for (hyoji_pid=0;hyoji_pid<20;hyoji_pid++){
			x=shoki_x;
			if (tatiaidata_bosuu_seme[id][hyoji_pid]!=0){
				ritu=(int)(((double)tatiaidata_kouka_seme[id][hyoji_pid]
					/tatiaidata_bosuu_seme[id][hyoji_pid])
					*100);
			}else{
				ritu=0;
			}
			if (hyoji_kumiteid==0){
				if (hyoji_pid>=0 && hyoji_pid<=3){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<tatiaidata_bosuu_seme[id][hyoji_pid]){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",tatiaidata_bosuu_seme[id][hyoji_pid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",tatiaidata_bosuu_seme[id][hyoji_pid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==1){
				if (hyoji_pid>=4 && hyoji_pid<=7){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<tatiaidata_bosuu_seme[id][hyoji_pid]){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",tatiaidata_bosuu_seme[id][hyoji_pid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",tatiaidata_bosuu_seme[id][hyoji_pid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==2){
				if (hyoji_pid>=8 && hyoji_pid<=11){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<tatiaidata_bosuu_seme[id][hyoji_pid]){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",tatiaidata_bosuu_seme[id][hyoji_pid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",tatiaidata_bosuu_seme[id][hyoji_pid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==3){
				if (hyoji_pid>=12 && hyoji_pid<=15){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<tatiaidata_bosuu_seme[id][hyoji_pid]){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",tatiaidata_bosuu_seme[id][hyoji_pid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",tatiaidata_bosuu_seme[id][hyoji_pid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==4){
				if (hyoji_pid>=16 && hyoji_pid<=19){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<tatiaidata_bosuu_seme[id][hyoji_pid]){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",tatiaidata_bosuu_seme[id][hyoji_pid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",tatiaidata_bosuu_seme[id][hyoji_pid]);
					}
					count++;
				}
			}
		}
		//if( ProcessMessage() == -1 ){mode=1;return ;}
		//wazadata_kouka_seme[技ID][力士ID][四つの状況]
		count=0;
		for (hyoji_wazaid=0;hyoji_wazaid<22;hyoji_wazaid++){
			if (wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]!=0){
				ritu=(int)(((double)wazadata_kouka_seme[hyoji_wazaid][id][hyoji_kumiteid]
					/wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid])
					*100);
			}else{
				ritu=0;
			}
			if (hyoji_kumiteid==0){
				if (hyoji_wazaid==1 || hyoji_wazaid==2){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==1){
				if (hyoji_wazaid==10 || hyoji_wazaid==13 || hyoji_wazaid==5 || hyoji_wazaid==6 || hyoji_wazaid==8 || hyoji_wazaid==15 || hyoji_wazaid==16 || hyoji_wazaid==19 ||hyoji_wazaid==20){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==2){
				if (hyoji_wazaid==11 || hyoji_wazaid==12 || hyoji_wazaid==4 || hyoji_wazaid==7 || hyoji_wazaid==8 || hyoji_wazaid==14 || hyoji_wazaid==17 || hyoji_wazaid==18 ||hyoji_wazaid==21){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==3){
				if (hyoji_wazaid==12 || hyoji_wazaid==13 || hyoji_wazaid==4 || hyoji_wazaid==5 || hyoji_wazaid==8 || hyoji_wazaid==14 || hyoji_wazaid==15 || hyoji_wazaid==18 ||hyoji_wazaid==19){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}
					count++;
				}
			}else if (hyoji_kumiteid==4){
				if (hyoji_wazaid==10 || hyoji_wazaid==11 || hyoji_wazaid==6 || hyoji_wazaid==7 || hyoji_wazaid==8 || hyoji_wazaid==16 || hyoji_wazaid==17 || hyoji_wazaid==20 ||hyoji_wazaid==21){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",wazadata_bosuu_seme[hyoji_wazaid][id][hyoji_kumiteid]);
					}
					count++;
				}
			}
		}
	}else if (wazabunsekipage==3 && memorykakuchouflag==1 && memoryfusokuflag==0){
		DrawFormatStringToHandle(200,5,CRWHITE,FontHandle12,"%sの技選択と成功率(対%s、注射の場合は除く)",namestring[id],namestring[bunsekikeikoaite_id]);
		DrawString(187,369,"左リストをクリックで表示内容を変更できます",CRWHITE);
		DrawStringToHandle(187,369+20,"※寄り・突っ張りの成功は、相手が前に圧力をかけてきているときに\n　少しでも前進できた場合です。",CRWHITE,FontHandle12);
		DrawStringToHandle(187,369+20+30,"※投げの成功は、相手のバランスを大きく崩せた場合です。",CRWHITE,FontHandle12);
		DrawStringToHandle(187,369+20+30+20,"※あてがいの成功は、相手が突っ張ってきたときに\n　間合いを詰めることができた場合です。",CRWHITE,FontHandle12);

		DrawFormatString(200,25,CRWHITE,"対%sの立合い→勝利率(勝利率・試行数)",namestring[bunsekikeikoaite_id]);
		DrawStringToHandle(187,y1[4]-6,"※立合いの狙いは「意図」、勢いは「結果」での表示",CRWHITE,FontHandle12);

		DrawFormatString(200,y1[0]-30-32+100+20,CRWHITE,"対%sの技成功率(成功率・試行数)",namestring[bunsekikeikoaite_id]);


		count=0;
		hosei_y=130;
		for (hyoji_pid=0;hyoji_pid<20;hyoji_pid++){
			x=shoki_x;
			memcpy(&temp_koukasuu_rbetutdata, 
				rbetutdata_kouka
				+id*RIKISISUU*20
				+bunsekikeikoaite_id*20
				+hyoji_pid,
				sizeof(unsigned short int));
			memcpy(&temp_bosuu_rbetutdata, 
				rbetutdata_bosuu
				+id*RIKISISUU*20
				+bunsekikeikoaite_id*20
				+hyoji_pid,
				sizeof(unsigned short int));
			if (temp_bosuu_rbetutdata!=0){
				ritu=(int)(((double)temp_koukasuu_rbetutdata
					/temp_bosuu_rbetutdata)
					*100);
			}else{
				ritu=0;
			}
			if (hyoji_kumiteid==0){
				if (hyoji_pid>=0 && hyoji_pid<=3){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<temp_bosuu_rbetutdata){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetutdata);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetutdata);
					}
					count++;
				}
			}else if (hyoji_kumiteid==1){
				if (hyoji_pid>=4 && hyoji_pid<=7){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<temp_bosuu_rbetutdata){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetutdata);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetutdata);
					}
					count++;
				}
			}else if (hyoji_kumiteid==2){
				if (hyoji_pid>=8 && hyoji_pid<=11){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<temp_bosuu_rbetutdata){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetutdata);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetutdata);
					}
					count++;
				}
			}else if (hyoji_kumiteid==3){
				if (hyoji_pid>=12 && hyoji_pid<=15){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<temp_bosuu_rbetutdata){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetutdata);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetutdata);
					}
					count++;
				}
			}else if (hyoji_kumiteid==4){
				if (hyoji_pid>=16 && hyoji_pid<=19){
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(hyoji_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[hyoji_pid%4]);x+=90;
					if (0<temp_bosuu_rbetutdata){
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetutdata);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetutdata);
					}
					count++;
				}
			}
		}

		//if( ProcessMessage() == -1 ){mode=1;return ;}
		//koukasuu_rbetuwdata
		//bosuu_rbetuwdata
		count=0;
		for (hyoji_wazaid=0;hyoji_wazaid<22;hyoji_wazaid++){
			if( ProcessMessage() == -1 ){mode=1;return ;}
			//値取り出し
			memcpy(&temp_koukasuu_rbetuwdata, 
				rbetuwdata_kouka
				+id*RIKISISUU*22*5
				+bunsekikeikoaite_id*22*5
				+hyoji_wazaid*5
				+hyoji_kumiteid,
				sizeof(unsigned short int));
			//値取り出し
			memcpy(&temp_bosuu_rbetuwdata, 
				rbetuwdata_bosuu
				+id*RIKISISUU*22*5
				+bunsekikeikoaite_id*22*5
				+hyoji_wazaid*5
				+hyoji_kumiteid,
				sizeof(unsigned short int));
			if (temp_bosuu_rbetuwdata!=0){
				ritu=(int)(((double)temp_koukasuu_rbetuwdata
					/temp_bosuu_rbetuwdata)
					*100);
			}else{
				ritu=0;
			}
			if (hyoji_kumiteid==0){
				if (hyoji_wazaid==1 || hyoji_wazaid==2){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<temp_bosuu_rbetuwdata){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetuwdata);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetuwdata);
					}
					count++;
				}
			}else if (hyoji_kumiteid==1){
				if (hyoji_wazaid==10 || hyoji_wazaid==13 || hyoji_wazaid==5 || hyoji_wazaid==6 || hyoji_wazaid==8 || hyoji_wazaid==15 || hyoji_wazaid==16 || hyoji_wazaid==19 ||hyoji_wazaid==20){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<temp_bosuu_rbetuwdata){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetuwdata);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetuwdata);
					}
					count++;
				}
			}else if (hyoji_kumiteid==2){
				if (hyoji_wazaid==11 || hyoji_wazaid==12 || hyoji_wazaid==4 || hyoji_wazaid==7 || hyoji_wazaid==8 || hyoji_wazaid==14 || hyoji_wazaid==17 || hyoji_wazaid==18 ||hyoji_wazaid==21){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<temp_bosuu_rbetuwdata){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetuwdata);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetuwdata);
					}
					count++;
				}
			}else if (hyoji_kumiteid==3){
				if (hyoji_wazaid==12 || hyoji_wazaid==13 || hyoji_wazaid==4 || hyoji_wazaid==5 || hyoji_wazaid==8 || hyoji_wazaid==14 || hyoji_wazaid==15 || hyoji_wazaid==18 ||hyoji_wazaid==19){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<temp_bosuu_rbetuwdata){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetuwdata);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetuwdata);
					}
					count++;
				}
			}else if (hyoji_kumiteid==4){
				if (hyoji_wazaid==10 || hyoji_wazaid==11 || hyoji_wazaid==6 || hyoji_wazaid==7 || hyoji_wazaid==8 || hyoji_wazaid==16 || hyoji_wazaid==17 || hyoji_wazaid==20 ||hyoji_wazaid==21){
					x=shoki_x;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[hyoji_kumiteid]);x+=90;
					DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[hyoji_wazaid]);x+=90;
					if (0<temp_bosuu_rbetuwdata){
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%3d％",ritu);x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetuwdata);
					}else{
						x+=50;
						DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%5d回",temp_bosuu_rbetuwdata);
					}
					count++;
				}
			}
		}
	}else if (memoryfusokuflag==0 && wazabunsekipage>=1){//ai評価個別
		int i1,i2,i3,i4,i5,i6,i7;
		long temp_fichi=0;
		char bytedata=0;
		int tensuu=0;
		char chuushutucount=0;
		int temp_pid=0;
		DrawString(187,369,"左リストをクリックで表示内容を変更できます",CRWHITE);
		DrawStringToHandle(187,y1[4]-6,"※立合いの狙いは「意図」、勢いは「結果」での表示",CRWHITE,FontHandle12);

		if (wazabunsekipage==1 && bunsekikeikoaite_id>=0 && bunsekikeikoaite_id<RIKISISUU){
			DrawFormatStringToHandle(100,5,CRWHITE,FontHandle12,"%sのＡＩによる評価点数(対%s(取組・稽古数=%d)、注射の場合は除く)",namestring[id],namestring[bunsekikeikoaite_id],aikeikosuu[id][bunsekikeikoaite_id]);
			DrawFormatString(200,25,CRWHITE,"%svs%sの立合い別評価",namestring[id],namestring[bunsekikeikoaite_id]);
			DrawFormatString(200,y1[0]-30-32+100+20,CRWHITE,"%svs%sの技別評価",namestring[id],namestring[bunsekikeikoaite_id]);
			////////立合い表示///////
			count=0;
			for (temp_pid=0;temp_pid<20;temp_pid++){
				tensuu=0;
				chuushutucount=0;
				if (((int)(temp_pid/4))==hyoji_kumiteid){
					//////力士ごとデータ//////
					memcpy(&bytedata, 
						aidata_tatiai
						+id*RIKISISUU*AIDATATATIAIBYTESUU
						+bunsekikeikoaite_id*AIDATATATIAIBYTESUU
						+(int)(temp_pid/4),
						sizeof(char));
					tensuu+=getdatafrombit(bytedata,temp_pid%4);
					chuushutucount++;
				}
				//ここでtensuuの値を表示
				if (chuushutucount>0){
					x=shoki_x;
					hosei_y=130;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(temp_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[temp_pid%4]);x+=90;
					x+=50;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",hyoukastring[tensuu]);
					count++;
				}
			}

			////////技表示///////
			count=0;
			for (i1=0;i1<22;i1++){
			for (i2=0;i2<5;i2++){
			tensuu=0;
			chuushutucount=0;
			for (i3=0;i3<2;i3++){
			for (i4=0;i4<2;i4++){
			for (i5=0;i5<2;i5++){
			for (i6=0;i6<2;i6++){
			for (i7=0;i7<4;i7++){
				temp_fichi=aidata_fichi[i1][i2][i3][i4][i5][i6][i7];
				if (temp_fichi!=-1){
					if (hyoji_kumiteid==i2){
						//////力士ごとデータ//////
						//値取り出し
						memcpy(&bytedata, 
							aidata
							+id*RIKISISUU*AIDATABYTESUU
							+bunsekikeikoaite_id*AIDATABYTESUU
							+(int)(temp_fichi/4),
							sizeof(char));
						tensuu+=getdatafrombit(bytedata,temp_fichi%4);
						chuushutucount++;
					}
				}
			}}}}}
			//ここでtensuuの値を表示
			if (chuushutucount>0){
				if (tensuu%chuushutucount!=0){
					tensuu=(int)(tensuu/chuushutucount)+1;
				}else{
					tensuu=(int)(tensuu/chuushutucount);
				}
				x=shoki_x;
				DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[i2]);x+=90;
				DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[i1]);x+=90;
				x+=50;
				DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",hyoukastring[tensuu]);
				count++;
			}
			}}
		}else if (wazabunsekipage==2){
			DrawFormatStringToHandle(200,5,CRWHITE,FontHandle12,"%sのＡＩによる評価点数(対全体、注射の場合は除く)",namestring[id]);
			DrawString(200,25,"対全力士の立合い別評価",CRWHITE);
			DrawString(200,y1[0]-30-32+100+20,"対全力士の技別評価",CRWHITE);
			////////立合い表示///////
			count=0;
			for (temp_pid=0;temp_pid<20;temp_pid++){
				tensuu=0;
				chuushutucount=0;
				if (((int)(temp_pid/4))==hyoji_kumiteid){
					//////トータルデータ//////
					memcpy(&bytedata, 
						aidata_tatiai
						+id*RIKISISUU*AIDATATATIAIBYTESUU
						+id*AIDATATATIAIBYTESUU
						+(int)(temp_pid/4),
						sizeof(char));
					tensuu+=getdatafrombit(bytedata,temp_pid%4);
					chuushutucount++;
				}
				//ここでtensuuの値を表示
				if (chuushutucount>0){
					x=shoki_x;
					hosei_y=130;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",neraistring[(int)(temp_pid/4)]);x+=90;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",ikioistring[temp_pid%4]);x+=90;
					x+=50;
					DrawFormatStringToHandle(x,-hosei_y+y+gyoukan*count,CRWHITE,FontHandle12,"%s",hyoukastring[tensuu]);
					count++;
				}
			}

			////////技表示///////
			count=0;
			for (i1=0;i1<22;i1++){
			for (i2=0;i2<5;i2++){
			tensuu=0;
			chuushutucount=0;
			for (i3=0;i3<2;i3++){
			for (i4=0;i4<2;i4++){
			for (i5=0;i5<2;i5++){
			for (i6=0;i6<2;i6++){
			for (i7=0;i7<4;i7++){
				temp_fichi=aidata_fichi[i1][i2][i3][i4][i5][i6][i7];
				if (temp_fichi!=-1){
					if (hyoji_kumiteid==i2){
						//////トータルデータ//////
						//値取り出し
						memcpy(&bytedata, 
							aidata
							+id*RIKISISUU*AIDATABYTESUU
							+id*AIDATABYTESUU
							+(int)(temp_fichi/4),
							sizeof(char));
						tensuu+=getdatafrombit(bytedata,temp_fichi%4);
						chuushutucount++;
					}
				}
			}}}}}
			//ここでtensuuの値を表示
			if (chuushutucount>0){
				if (tensuu%chuushutucount!=0){
					tensuu=(int)(tensuu/chuushutucount)+1;
				}else{
					tensuu=(int)(tensuu/chuushutucount);
				}
				x=shoki_x;
				DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",kumitestring[i2]);x+=90;
				DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",wazanamestring[i1]);x+=90;
				x+=50;
				DrawFormatStringToHandle(x,y+gyoukan*count,CRWHITE,FontHandle12,"%s",hyoukastring[tensuu]);
				count++;
			}
			}}
		}
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}
	//戻る表示
	DrawString(x1[0],y1[0]-30,"力士画面へ戻る",CRGREEN);
	//組手リスト表示
	for(i=2;i<7;i++){
		if (i-2==hyoji_kumiteid){
			DrawBox(x1[i],y1[i],x2[i],y2[i],CRKEIJIBANON,TRUE);
		}else{
			DrawBox(x1[i],y1[i],x2[i],y2[i],CRKEIJIBANOFF,TRUE);
		}
		DrawFormatStringToHandle(x1[i],y1[i],CRBLACK,FontHandle16,"%s",kumitestring[i-2]);
	}
	//ページリスト表示
	if (wazabunsekipage==3){
		DrawBox(x1[10],y1[10],x2[11],y2[11],CRKEIJIBANON,TRUE);
	}else{
		DrawBox(x1[10],y1[10],x2[11],y2[11],CRKEIJIBANOFF,TRUE);
	}
	if (wazabunsekipage==0){
		DrawBox(x1[12],y1[12],x2[13],y2[13],CRKEIJIBANON,TRUE);
	}else{
		DrawBox(x1[12],y1[12],x2[13],y2[13],CRKEIJIBANOFF,TRUE);
	}
	if (wazabunsekipage==1){
		DrawBox(x1[14],y1[14],x2[15],y2[15],CRKEIJIBANON,TRUE);
	}else{
		DrawBox(x1[14],y1[14],x2[15],y2[15],CRKEIJIBANOFF,TRUE);
	}
	if (wazabunsekipage==2){
		DrawBox(x1[16],y1[16],x2[17],y2[17],CRKEIJIBANON,TRUE);
	}else{
		DrawBox(x1[16],y1[16],x2[17],y2[17],CRKEIJIBANOFF,TRUE);
	}
	if (lastkeiko_year[id]!=0){
		if (wazabunsekipage==4){
			DrawBox(x1[18],y1[18],x2[19],y2[19],CRKEIJIBANON,TRUE);
		}else{
			DrawBox(x1[18],y1[18],x2[19],y2[19],CRKEIJIBANOFF,TRUE);
		}
	}
	DrawStringToHandle(x1[10],y1[10],"対力士別統計",CRBLACK,FontHandle16);
	DrawStringToHandle(x1[12],y1[12],"対全体統計",CRBLACK,FontHandle16);
	DrawStringToHandle(x1[14],y1[14],"対力士別AI評価",CRBLACK,FontHandle16);
	DrawStringToHandle(x1[16],y1[16],"対全体AI評価",CRBLACK,FontHandle16);
	if (lastkeiko_year[id]!=0){
		DrawStringToHandle(x1[18],y1[18],"直近稽古集計",CRBLACK,FontHandle16);
	}

	if (wazabunsekipage==1 || wazabunsekipage==3){
		DrawStringToHandle(x1[22],y1[22],"分析相手選択",CRGREEN,FontHandle16);
	}
	if (wazabunsekipage==3){
		DrawStringToHandle(580,25,"消去",CRGREEN,FontHandle16);
	}
/*
	//個別データ出力
	if (memoryfusokuflag==0){
		if (bunsekikeikoaite_id>=0 && bunsekikeikoaite_id<RIKISISUU){
			DrawFormatString(x1[26],y1[26],CRGREEN,"対%sAIデータ出力",namestring[bunsekikeikoaite_id]);
		}
	}
*/
	//技リスト表示
/*
	for(i=14;i<36;i++){
		if (i-14==hyoji_wazaid){
			DrawBox(x1[i],y1[i],x2[i],y2[i],CRKEIJIBANON,TRUE);
		}else{
			DrawBox(x1[i],y1[i],x2[i],y2[i],CRKEIJIBANOFF,TRUE);
		}
		DrawFormatStringToHandle(x1[i],y1[i],CRBLACK,FontHandle16,"%s",wazanamestring[i-14]);
	}
*/
	ScreenFlip() ;//裏画面を表画面にコピー
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		if (get_mouseclick(580,25,639,25+16)==1 && wazabunsekipage==3 && memorykakuchouflag==1 && memoryfusokuflag==0){
			ClearDrawScreen();
			DrawFormatString(x1[0],y1[0],CRRED,"%s VS %s の統計をリセットして本当によろしいですか",namestring[id],namestring[bunsekikeikoaite_id]);
			DrawString(x1[4],y1[4],"リセットする",CRGREEN);
			DrawString(x1[8],y1[8],"やっぱりやめる",CRGREEN);
			DrawString(187,369,"力士別統計は最大カウント数が65535なので\n必要に応じてリセットすることができます",CRWHITE);
			ScreenFlip();
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){Sleep(1);}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){Sleep(1);}
			while(1)
			{
				if (get_mouseclick_list(4) || get_mouseclick_list(5)){
					memset(rbetuwdata_kouka
						+id*RIKISISUU*22*5
						+bunsekikeikoaite_id*22*5, 0, sizeof(unsigned short int) * 22*5); // ここを追加
					memset(rbetuwdata_bosuu
						+id*RIKISISUU*22*5
						+bunsekikeikoaite_id*22*5, 0, sizeof(unsigned short int) * 22*5); // ここを追加
					memset(rbetutdata_kouka
						+id*RIKISISUU*20
						+bunsekikeikoaite_id*20, 0, sizeof(unsigned short int) * 20); // ここを追加
					memset(rbetutdata_bosuu
						+id*RIKISISUU*20
						+bunsekikeikoaite_id*20, 0, sizeof(unsigned short int) * 20); // ここを追加
					memset(rbetuwdata_kouka
						+bunsekikeikoaite_id*RIKISISUU*22*5
						+id*22*5, 0, sizeof(unsigned short int) * 22*5); // ここを追加
					memset(rbetuwdata_bosuu
						+bunsekikeikoaite_id*RIKISISUU*22*5
						+id*22*5, 0, sizeof(unsigned short int) * 22*5); // ここを追加
					memset(rbetutdata_kouka
						+bunsekikeikoaite_id*RIKISISUU*20
						+id*20, 0, sizeof(unsigned short int) * 20); // ここを追加
					memset(rbetutdata_bosuu
						+bunsekikeikoaite_id*RIKISISUU*20
						+id*20, 0, sizeof(unsigned short int) * 20); // ここを追加
					break;
				}
				if (get_mouseclick_list(8) || get_mouseclick_list(9)){
					break;
				}
				if( ProcessMessage() == -1 ){mode=1;return ;}
				Sleep(1);
			}
			WaitTimer(200);
			goto HYOJI;
		}

		if (wazabunsekipage==1 || wazabunsekipage==3){
			if (get_mouseclick_list(22)==1 || get_mouseclick_list(23)==1){
				int kaeri;
				WaitTimer(200);
				kaeri=genekirikisisentaku_keiko(id,1);
				if (kaeri>=0 && kaeri<RIKISISUU){
					bunsekikeikoaite_id=kaeri;
				}
				WaitTimer(200);
				goto HYOJI;
			}
		}
		//ページ切替
		if (lastkeiko_year[id]!=0){
			if (get_mouseclick_list(18)==1 || get_mouseclick_list(19)==1){
				if (wazabunsekipage!=4){
					wazabunsekipage=4;
					WaitTimer(200);
					goto HYOJI;
				}
			}
		}
		if (get_mouseclick_list(12)==1 || get_mouseclick_list(13)==1){
			if (wazabunsekipage!=0){
				wazabunsekipage=0;
				WaitTimer(200);
				goto HYOJI;
			}
		}
		if (get_mouseclick_list(14)==1 || get_mouseclick_list(15)==1){
			if (memoryfusokuflag==0){
				if (bunsekikeikoaite_id>=0 && bunsekikeikoaite_id<RIKISISUU){
					if (wazabunsekipage!=1){
						wazabunsekipage=1;
						WaitTimer(200);
						goto HYOJI;
					}
				}else{
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawString(10,369,"相手の画像IDが変です",CRWHITE);
					DrawString(10,369+16,"表示できません",CRWHITE);
					DrawString(187,369+48,"Hit Any Key",CRWHITE);
					ScreenFlip() ;//裏画面を表画面にコピー
					WaitKey();
					WaitTimer(200);
					goto HYOJI;
				}
			}else{
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(10,369,"AI機能は使用していないので",CRWHITE);
				DrawString(10,369+16,"表示できません",CRWHITE);
				DrawString(10,369+32,"MENUのメモリ設定をご確認ください",CRWHITE);
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);
				goto HYOJI;
			}
		}
		if (get_mouseclick_list(16)==1 || get_mouseclick_list(17)==1){
			if (memoryfusokuflag==0){
				if (wazabunsekipage!=2){
					wazabunsekipage=2;
					WaitTimer(200);
					goto HYOJI;
				}
			}else{
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(10,369,"AI機能は使用していないので",CRWHITE);
				DrawString(10,369+16,"表示できません",CRWHITE);
				DrawString(10,369+32,"MENUのメモリ設定をご確認ください",CRWHITE);
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);
				goto HYOJI;
			}
		}
		if (get_mouseclick_list(10)==1 || get_mouseclick_list(11)==1){
			if (memoryfusokuflag==0 && memorykakuchouflag==1){
				if (wazabunsekipage!=3){
					wazabunsekipage=3;
					WaitTimer(200);
					goto HYOJI;
				}
			}else{
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawString(10,369,"力士別統計はとっていないので",CRWHITE);
				DrawString(10,369+16,"表示できません",CRWHITE);
				DrawString(10,369+32,"MENUのメモリ設定をご確認ください",CRWHITE);
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);
				goto HYOJI;
			}
		}
		//組手リスト選択
		for(i=2;i<7;i++){
			if (get_mouseclick_list(i)==1){
				hyoji_kumiteid=i-2;
				WaitTimer(200);
				goto HYOJI;
			}
		}
		//技リスト選択
/*
		for(i=14;i<36;i++){
			if (get_mouseclick_list(i)==1){
				hyoji_wazaid=i-14;
				goto HYOJI;
				WaitTimer(200);
			}
		}
*/
		//個別データ出力
		if (memoryfusokuflag==0){
			if (bunsekikeikoaite_id>=0
			&& bunsekikeikoaite_id<RIKISISUU
			&& get_mouseclick(x1[12],y1[12],x2[13],y2[13]) == 2
			&& CheckHitKey_test(KEY_INPUT_LSHIFT)==1){
				////////////////////////
				{
				int i1,i2,i3,i4,i5,i6,i7;
				long temp_fichi=0;
				char bytedata=0;
				char temp_char=0;
				char temp_filename[MAX_PATH];
				for (i=0;i<MAX_PATH;i++){
					temp_filename[i]=0;
					//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				}
				FILE *fpcsv;
				sprintf(temp_filename,"output/ai_%d_%d.csv\0",id,bunsekikeikoaite_id);
				fpcsv = fopen(temp_filename,"w");
				fprintf(fpcsv,"点数(0~3),技,四つ,自右廻,自左廻,相右廻,相右廻,上体\n");
				for (i1=0;i1<22;i1++){
				for (i2=0;i2<5;i2++){
				for (i3=0;i3<2;i3++){
				for (i4=0;i4<2;i4++){
				for (i5=0;i5<2;i5++){
				for (i6=0;i6<2;i6++){
				for (i7=0;i7<4;i7++){
				temp_fichi=aidata_fichi[i1][i2][i3][i4][i5][i6][i7];
				if (temp_fichi!=-1 && bunsekikeikoaite_id>=0 && bunsekikeikoaite_id<RIKISISUU){
				//////力士ごとデータ//////
				//値取り出し
				memcpy(&bytedata, 
					aidata
					+id*RIKISISUU*AIDATABYTESUU
					+bunsekikeikoaite_id*AIDATABYTESUU
					+(int)(temp_fichi/4),
					sizeof(char));
				temp_char=getdatafrombit(bytedata,temp_fichi%4);
				fprintf(fpcsv,"%d,%s,%s,%s,%s,%s,%s,%s\n"
				,temp_char
				,wazanamestring[i1]
				,kumitestring[i2]
				,arinasistring[i3]
				,arinasistring[i4]
				,arinasistring[i5]
				,arinasistring[i6]
				,joutaistring[i7]
				);
				}
				}}}}}}}
				fclose(fpcsv);
				}
				////////////////////////
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawFormatString(10,369,CRWHITE,"outputフォルダにai_%d_%d.csv",id,bunsekikeikoaite_id,CRWHITE);
				DrawString(10,369+16,"を出力しました",CRWHITE);
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);
				goto HYOJI;
			}
		}

		if (get_mouseclick(x1[0],y1[0]-30,x2[1],y1[0]-30+16) == 1) break;
		if( ProcessMessage() == -1 ){mode=1;return ;}
		Sleep(1);
	}//キー入力待ちループの終端

	return;
}

char getdatafrombit(char bytedata,char amari)
{
	char kaeri=0;

	if (amari==0){
		if ( (bytedata & b10000000) == b00000000 
			&& (bytedata & b01000000) == b00000000){
			kaeri=0;
		}
		if ( (bytedata & b10000000) == b00000000 
			&& (bytedata & b01000000) == b01000000){
			kaeri=1;
		}
		if ( (bytedata & b10000000) == b10000000 
			&& (bytedata & b01000000) == b00000000){
			kaeri=2;
		}
		if ( (bytedata & b10000000) == b10000000 
			&& (bytedata & b01000000) == b01000000){
			kaeri=3;
		}
	}
	if (amari==1){
		if ( (bytedata & b00100000) == b00000000 
			&& (bytedata & b00010000) == b00000000){
			kaeri=0;
		}
		if ( (bytedata & b00100000) == b00000000 
			&& (bytedata & b00010000) == b00010000){
			kaeri=1;
		}
		if ( (bytedata & b00100000) == b00100000 
			&& (bytedata & b00010000) == b00000000){
			kaeri=2;
		}
		if ( (bytedata & b00100000) == b00100000 
			&& (bytedata & b00010000) == b00010000){
			kaeri=3;
		}
	}
	if (amari==2){
		if ( (bytedata & b00001000) == b00000000 
			&& (bytedata & b00000100) == b00000000){
			kaeri=0;
		}
		if ( (bytedata & b00001000) == b00000000 
			&& (bytedata & b00000100) == b00000100){
			kaeri=1;
		}
		if ( (bytedata & b00001000) == b00001000 
			&& (bytedata & b00000100) == b00000000){
			kaeri=2;
		}
		if ( (bytedata & b00001000) == b00001000 
			&& (bytedata & b00000100) == b00000100){
			kaeri=3;
		}
	}
	if (amari==3){
		if ( (bytedata & b00000010) == b00000000 
			&& (bytedata & b00000001) == b00000000){
			kaeri=0;
		}
		if ( (bytedata & b00000010) == b00000000 
			&& (bytedata & b00000001) == b00000001){
			kaeri=1;
		}
		if ( (bytedata & b00000010) == b00000010 
			&& (bytedata & b00000001) == b00000000){
			kaeri=2;
		}
		if ( (bytedata & b00000010) == b00000010 
			&& (bytedata & b00000001) == b00000001){
			kaeri=3;
		}
	}
	return kaeri;
}
char setdatatobit(char bytedata,char amari,char setdata)
{
	if (amari==0){
		//まずは該当ビットを0クリア
		bytedata = (bytedata & b00111111);
		//該当ビットにデータセット
		if (setdata==0){
			bytedata = (bytedata | b00000000);
		}
		if (setdata==1){
			bytedata = (bytedata | b01000000);
		}
		if (setdata==2){
			bytedata = (bytedata | b10000000);
		}
		if (setdata==3){
			bytedata = (bytedata | b11000000);
		}
	}
	if (amari==1){
		//まずは該当ビットを0クリア
		bytedata = (bytedata & b11001111);
		//該当ビットにデータセット
		if (setdata==0){
			bytedata = (bytedata | b00000000);
		}
		if (setdata==1){
			bytedata = (bytedata | b00010000);
		}
		if (setdata==2){
			bytedata = (bytedata | b00100000);
		}
		if (setdata==3){
			bytedata = (bytedata | b00110000);
		}
	}
	if (amari==2){
		//まずは該当ビットを0クリア
		bytedata = (bytedata & b11110011);
		//該当ビットにデータセット
		if (setdata==0){
			bytedata = (bytedata | b00000000);
		}
		if (setdata==1){
			bytedata = (bytedata | b00000100);
		}
		if (setdata==2){
			bytedata = (bytedata | b00001000);
		}
		if (setdata==3){
			bytedata = (bytedata | b00001100);
		}
	}
	if (amari==3){
		//まずは該当ビットを0クリア
		bytedata = (bytedata & b11111100);
		//該当ビットにデータセット
		if (setdata==0){
			bytedata = (bytedata | b00000000);
		}
		if (setdata==1){
			bytedata = (bytedata | b00000001);
		}
		if (setdata==2){
			bytedata = (bytedata | b00000010);
		}
		if (setdata==3){
			bytedata = (bytedata | b00000011);
		}
	}
	return bytedata;
}

