#include "DxLib.h"
#include <stdio.h>
#include "define.h"

extern int lastkeiko_year[RIKISISUU];
extern int lastkeiko_month[RIKISISUU];
extern int lastkeiko_day[RIKISISUU];
extern char lastkeiko_aitenamestring[RIKISISUU][12];

extern int genekirikisisentaku_keiko(int x,char flag);//sub_itimonにあるよ～
											//選択した力士の画像IDが返される
											//flag0→稽古相手選択、1→技分析相手選択
extern int bunsekikeikoaite_id;

extern char *aidata;//動的メモリ
extern char *aidata_tatiai;//動的メモリ

extern char AIkeikoflag;

extern char memoryfusokuflag;//動的メモリを使わない場合1
extern char shokiti_superrikisiflag;
extern int aikeikosuu[RIKISISUU][RIKISISUU];//取組・稽古両方合わせた過去の力士別対戦数
extern int kobetu_sikiiti[RIKISISUU];//トータルデータを使うか個別データを使うのかの閾値
extern int shokiti_kobetu_sikiiti;

extern short int lastwazadata_kouka_seme[22][RIKISISUU][5];//
extern short int lastwazadata_bosuu_seme[22][RIKISISUU][5];//
extern short int lasttatiaidata_kouka_seme[RIKISISUU][20];//どの立ち合いが勝利に結びついたか
extern short int lasttatiaidata_bosuu_seme[RIKISISUU][20];//どの立ち合いが勝利に結びついたか

extern char kyuujoumode;

//extern char matatukihanasitaflag;


extern struct jouken_data joukendata[RIKISISUU];//構造体変数力士数分用意
extern struct jouken_data joukendata_temp_higasi;//構造体変数力士数分用意
extern struct jouken_data joukendata_temp_nisi;//構造体変数力士数分用意
extern struct jouken_data2 joukendata2[RIKISISUU];//構造体変数力士数分用意
extern struct jouken_data2 joukendata2_temp_higasi;//構造体変数力士数分用意
extern struct jouken_data2 joukendata2_temp_nisi;//構造体変数力士数分用意

extern char win_skip[RIKISISUU];
extern char lost_skip[RIKISISUU];
extern int CheckHitKey_test(int);
extern int skipmode;//0:全部の取り組みの詳細を表示
extern int skipyear;//skipmode==2のときの指定年
extern int skipmonth;//skipmode==2のときの指定月
extern int skipday;
extern int day;//ゲーム内日数、一月＝30日間、偶数月の11日から25日に本場所開催
extern int month;//ゲーム内月
extern int year;//ゲーム内年
extern int skiphyojimode;
extern int hyoji_skipgyousuu;
extern int heyabandukejunid[HEYASUU][20];//部屋ごとの番付順の力士ID、
						//[部屋ID][部屋内部での番付順]
extern int shozokurikisisuu[HEYASUU];//部屋IDごとの所属力士数
extern char heyastring[HEYASUU][12];//(54部屋分,全角５文字まで)相撲部屋
extern char bandukenamestring[10][12];//(10名称分、全角5文字まで)番付名
extern char tournamentkekkahyojiflag_skip;
extern int yuushourikisikonbasho;//今場所の優勝力士ID
extern char kyuujouflag[RIKISISUU];//1で休場
extern int bandukejunid[RIKISISUU];
extern char temp_tournament_heyastring[12];
extern char temp_tournament_bandukenameid;
extern char temp_tournament_namestring[12];
extern int shukunshourikisikonbasho;
extern int kantoushourikisikonbasho;
extern int ginoushourikisikonbasho;
extern char temp_bandukenameid_skip[RIKISISUU];
extern char temp_bandukesuuji_skip[RIKISISUU];
extern int temp_bandukejun_skip[RIKISISUU];
extern int temp_age_skip[RIKISISUU];
extern char temp_heyastring_skip[RIKISISUU][12];
extern int kakobandukewin[RIKISISUU];
extern int kakobandukelost[RIKISISUU];
extern int nenkansaitashourisuu;
extern char nenkansaitashourikisihokanimoiruyoflag;
extern int jiheyarikisikonbasho;//スキップ中の表示用の自部屋力士(先場所)
extern int intaisuu;
extern int intairikisikonbasho[RIKISISUU];
extern int shousinsuu;
extern int shousinrikisikonbasho[RIKISISUU];
extern char temp_namestring_skip[RIKISISUU][12];
extern int kaerizakisuu;
extern int kaerizakirikisikonbasho[RIKISISUU];
extern char normal_bashostring[6][7];//最長「名古屋」の3文字分

extern int get_mouseclick(int x1,int y1,int x2,int y2);//座標(x1,y1)と(x2,y2)に囲まれたところで

//extern char higasi_aidata[AIDATABYTESUU];
//extern char nisi_aidata[AIDATABYTESUU];
extern int ito_higasi_tatiai_power;
extern int ito_nisi_tatiai_power;

extern long filebytesuu_aidata;

extern char keikosumiflag[RIKISISUU];//稽古をやりすぎてwazadataがオーバーフローしないように

extern void chokuzen(void);
extern void kiroku_wazadata(char wazaid,int id1,int id2,char id1_higasiornisi,char tatiaigoflag);

extern void dataexchange(void);//オフェンスとディフェンスのデータ入れ替えルーチン
extern int waza(int,int,int);//技ごとの効果判断ルーチン、引数は技ID、東ID、西ID
extern int sisuu_binshou_gyakuten;//デフォは10、大きいほど逆転叩きを喰らいにくい
extern int sisuu_binshou_mawarikomi;//デフォは10
extern int sisuu_ashi_gyakuten;//デフォは99

extern int tatiaipattern_powerid[TATIAIPATTERNSUU];//[立会いパターンID]、立会いパターンIDごとの立会いの勢い
extern int tatiaipattern_neraiid[TATIAIPATTERNSUU];//[立会いパターンID]、立会いパターンIDごとの立会いの狙い
extern int wazapattern_far_sentakuwazaid_trysuu[WAZAPATTERNSUU][5];//[技パターンID][遠距離での技の選択肢の各maxtry数]
extern int wazapattern_middle_sentakuwazaid_trysuu[WAZAPATTERNSUU][5];//[技パターンID][中距離での技の選択肢の各maxtry数]
extern int wazapattern_near_sentakuwazaid_trysuu[WAZAPATTERNSUU][5];//[技パターンID][近距離での技の選択肢の各maxtry数]
extern int wazapattern_far_sentakuwazaid[WAZAPATTERNSUU][5];//[技パターンID][遠距離での技の選択肢その1～5]
extern int wazapattern_far_sentakuwazaid_maxtry[WAZAPATTERNSUU][5];//[技パターンID][遠距離での技の選択肢の各maxtry数]
extern int wazapattern_near_sentakuwazaid[WAZAPATTERNSUU][5];//[技パターンID][近距離での技の選択肢その1～5]
extern int wazapattern_near_sentakuwazaid_maxtry[WAZAPATTERNSUU][5];//[技パターンID][近距離での技の選択肢の各maxtry数]

extern int ichi_lastturn;//→ローカル変数ですでに使っていたがグローバルにした　土俵上の位置-4～+4、0が土俵中央、-4で東力士OUT、+4で西力士OUT
extern int last_higasi_state_balance,last_nisi_state_balance;//バランス、パラ/10がMAXで、0で倒れて負け

extern char ritu_tatiai_zenryoku;//デフォ7
extern char ritu_tatiai_tuyoku;//デフォ79
extern char ritu_tatiai_uke;//デフォ7
extern int MAGIRE;//戦闘中の乱数用紛れ定数
extern int MAGIRE_CHUUKANSHORI;
extern int MAGIRE_MAKIKAE;
extern int MAGIRE_MAWASINERAI;
extern int MAGIRE_BINSHOUSEI;
extern int MAGIRE_TATIAI_JOUGE;

extern char getdatafrombit(char bytedata,char amari);//バイトデータから2bitの値を取り出す関数
										//aidataに記録されているのは2bitずつなので
										//上記fichi/4の位置の2bitの値を0~3の値で返す関数
extern char setdatatobit(char bytedata,char amari,char setdata);//bytedataのamariの位置の2ビットにsetdataの値をセット

extern long aidata_fichi[22][5][2][2][2][2][4];//aidataのファイル記録位置
extern int offense_stamina;
extern int defense_stamina;
extern int turncount;//取組の戦闘中のターン数
extern int kougekiken;//東方力士の攻撃＞1、西の攻撃＞2
extern int offenseid;//攻撃側力士のID
extern int defenseid;//守備側力士のID
extern int wazapatternid_higasi;//東力士がこの取り組みで選択した技パターンID
extern int wazapatternid_nisi;
extern int wazaid_sentaku;//力士が選択した技ID
extern int tatiaipatternid_higasi;//東力士がこの取り組みで選択した立会いパターンID
extern int tatiaipatternid_nisi;

extern struct rikisi_data temp_rikisidata_higasi;//取組時バランス調整前のバックアップ用
extern struct rikisi_data temp_rikisidata_nisi;//バックアップ用
extern struct rikisi_data rikisidata[RIKISISUU];
extern struct bl_data bldata;//バランス調整用
extern int count_temp_aidata;
extern int mode;//1：終了フラグ、2：ゲーム準備処理完了フラグ、
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

extern int FontHandle16;
extern int FontHandle12;
extern int x1[40];//[]内のリスト番号の左上x座標、初期化はwinmain関数内でする
extern int x2[40];//右下ｘ座標
extern int y1[40];//左上y座標
extern int y2[40];//右下y座標
extern char namestring[RIKISISUU][12];//(力士IDごとの四股名,全角５文字まで)四股名
extern int get_mouseclick_list(int x);//画面左のリスト上でクリックされたら1を返す、

extern void hozon_aidata(int higasiid,int nisiid,int winid);

int keikowin;

void AIkeiko(int higasiid,int nisiid);
int fight_fight_keiko(int higasiid,int nisiid);//東が勝なら1、西が勝なら2を返す
void torikumimaekeiko(int x);
void aikeikochuuhyoji(void);
extern char keikochuudanflag;

void AIkotenagesukuinage_shokiti(void);
extern int AIkotenagesukuinage_shokitizeroflag;//AI評価の初期値のうち小手投げと掬い投げだけは0(D)にするフラグ（他はB）、今まではＤだったけどver4.05beta010から変更

void AIhyokajougeritu(void);
void AIwazarandomritu(void);
extern int waza_randomsentakuritu_makekosisuu[7];//AI評価によらずにランダムで技選択を行う率
										//直近６場所での対戦相手との負け越し数に応じて率を設定
										//0→負け越しなし
										//1→１つ負け越し
										//2→２つ負け越し
										//3→３つ負け越し
										//4→４つ負け越し
										//5→５つ負け越し
										//6→６つ負け越し

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

void torikumimaekeiko(int x)
{
	int i,ii;
	int keikosuu=0;

HYOJI_torikumimaekeiko:
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
	//DrawBox(3,76,183,475,CRTAB,TRUE);
	if (memoryfusokuflag==0){
		DrawStringToHandle(100,6,"　　　　　　　　　　AI設定画面",CRWHITE,FontHandle12);
	}else{
		DrawStringToHandle(100,6,"　　　　　　      　　　　稽古画面",CRWHITE,FontHandle12);
	}

	i=0;i=1;
	DrawString(x1[4],y1[4],"10回(今すぐ)",CRGREEN);i++;
	DrawString(x1[6],y1[6],"100回(今すぐ)",CRGREEN);i++;
	DrawString(x1[8],y1[8],"1000回(今すぐ)",CRGREEN);i++;
	if (memoryfusokuflag==0){
		i++;
		DrawString(x1[12],y1[12],"2回(自動)",CRGREEN);i++;
		DrawString(x1[14],y1[14],"4回(自動)",CRGREEN);i++;
		DrawString(x1[16],y1[16],"8回(自動)",CRGREEN);i++;
		DrawString(x1[18],y1[18],"16回(自動)",CRGREEN);i++;
		DrawString(x1[20],y1[20],"20回(自動)",CRGREEN);i++;
		DrawString(x1[22],y1[22],"40回(自動)",CRGREEN);i++;
		DrawString(x1[24],y1[24],"100回(自動)",CRGREEN);i++;
		DrawString(x1[26],y1[26],"200回(自動)",CRGREEN);i++;
		DrawString(x1[28],y1[28],"1000回(自動)",CRGREEN);i++;
		DrawString(x1[32],y1[32],"0回(自動)",CRGREEN);i++;
		i++;
		if (rikisidata[x].superrikisiflag==101){
			DrawFormatString(187,369,CRWHITE,"この力士は、自動で %d回 取組前AI稽古をします。",rikisidata[x].superrikisiflag*10-10);i++;
		}else{
			DrawFormatString(187,369,CRWHITE,"この力士は、自動で %d回 取組前AI稽古をします。",rikisidata[x].superrikisiflag*2);i++;
		}
		DrawString(187,400,"全力士にこの自動稽古回数を適用",CRGREEN);i++;
		DrawStringToHandle(187,400+18,"※新たに入門してくる力士の初期値にも適用されます",CRWHITE,FontHandle12);

		DrawFormatStringToHandle(187,25,CRWHITE,FontHandle12,"下の緑色の数字を左右クリックで、%sの",namestring[x]);
		DrawStringToHandle(187,25+12,"AIの種類を変更する閾値を増減できます。",CRWHITE,FontHandle12);
		DrawStringToHandle(187,25+24,"この数字以上の回数の取組・稽古をした相手には",CRWHITE,FontHandle12);
		DrawStringToHandle(187,25+36,"対戦相手ごとの個別データを使用します。",CRWHITE,FontHandle12);
		DrawStringToHandle(187,25+48,"この回数未満の相手には共通データを使用します。",CRWHITE,FontHandle12);
		DrawFormatString(250,25+64,CRGREEN,"%d",kobetu_sikiiti[x]);
		DrawString(320,25+64,"この閾値を全力士に適用",CRGREEN);
	}

	DrawString(x1[0],y1[0]-50,"　　戻る",CRGREEN);


	DrawString(187,132,"左のリスト上(今すぐ)をクリックすると、",CRWHITE);
	DrawFormatString(187,132+16,CRWHITE,"回数分、今すぐ%sの稽古を行います",namestring[x]);
	if (memoryfusokuflag==0){
		DrawStringToHandle(187,132+50,"※この力士のAIも相手のAIも頭が良くなります。",CRWHITE,FontHandle12);
	}
	DrawStringToHandle(187,132+50+20,"※今設定している作戦が頑固の値にかかわらず必ず適用されます",CRWHITE,FontHandle12);

	DrawString(190,240,"評価上下率(共通)",CRGREEN);
	DrawString(400,240,"技ランダム率(共通)",CRGREEN);
	DrawString(190,260,"小手掬い投初期値(共通)",CRGREEN);


	DrawString(187,300,"左のリスト上(自動)をクリックすると、",CRWHITE);
	if (memoryfusokuflag==0){
		DrawFormatString(187,300+16,CRWHITE,"明日以降の%sの対戦相手との自動AI稽古回数",namestring[x]);
		DrawString(187,300+32,"を変更できます。",CRWHITE);
		DrawStringToHandle(187,300+48,"※今日の分の自動稽古時間はすでに終わっています",CRWHITE,FontHandle12);
	}

	ScreenFlip();
	if( ProcessMessage() == -1 ){mode=1;return;}
	while(1)
	{
		if (memoryfusokuflag==0){
			if (get_mouseclick(190,260,190+200,260+16) == 1){
				AIkotenagesukuinage_shokiti();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick(190,240,190+160,240+16) == 1){
				AIhyokajougeritu();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick(400,240,400+160,240+16) == 1){
				AIwazarandomritu();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}

			if (get_mouseclick(320,25+64,320+180,25+64+16) == 1){
				for (i=0;i<RIKISISUU;i++){
					kobetu_sikiiti[i]=kobetu_sikiiti[x];
				}
				shokiti_kobetu_sikiiti=kobetu_sikiiti[x];
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawFormatString(100,369,CRWHITE,"全ての力士の閾値が%d回に変更されました",kobetu_sikiiti[x]);
				DrawString(100,369+16,"入門力士の初期値も同じく変更されました",CRWHITE);
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick(250,25+64,250+30,25+64+16) == 1){
				if (kobetu_sikiiti[x]<100){
					kobetu_sikiiti[x]+=10;
				}else if (kobetu_sikiiti[x]<1000){
					kobetu_sikiiti[x]+=100;
				}else if (kobetu_sikiiti[x]>=1000){
					kobetu_sikiiti[x]=0;
				}
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick(250,25+64,250+30,25+64+16) == 2){
				if (kobetu_sikiiti[x]>100){
					kobetu_sikiiti[x]-=100;
				}else if (kobetu_sikiiti[x]>0){
					kobetu_sikiiti[x]-=10;
				}else if (kobetu_sikiiti[x]<=0){
					kobetu_sikiiti[x]=1000;
				}
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
		}
		if (get_mouseclick_list(4) == 1 || get_mouseclick_list(5)==1
		|| get_mouseclick_list(6) == 1 || get_mouseclick_list(7)==1
		|| get_mouseclick_list(8) == 1 || get_mouseclick_list(9)==1){
			int kaeri;
			if (get_mouseclick_list(4) == 1 || get_mouseclick_list(5)==1){
				 keikosuu=10;
			}else if (get_mouseclick_list(6) == 1 || get_mouseclick_list(7)==1){
				 keikosuu=100;
			}else if (get_mouseclick_list(8) == 1 || get_mouseclick_list(9)==1){
				 keikosuu=1000;
			}
			
			WaitTimer(200);

			kaeri=genekirikisisentaku_keiko(x,0);
			if (kaeri<0 || kaeri>=RIKISISUU) {WaitTimer(200);goto HYOJI_torikumimaekeiko;}
			bunsekikeikoaite_id=kaeri;

			lastkeiko_year[x]=year;
			lastkeiko_month[x]=month;
			lastkeiko_day[x]=day;
			strcpy(lastkeiko_aitenamestring[x],namestring[bunsekikeikoaite_id]);

			lastkeiko_year[bunsekikeikoaite_id]=year;
			lastkeiko_month[bunsekikeikoaite_id]=month;
			lastkeiko_day[bunsekikeikoaite_id]=day;
			strcpy(lastkeiko_aitenamestring[bunsekikeikoaite_id],namestring[x]);

			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawFormatString(100,369,CRWHITE,"%sと%sが%d回AI稽古中です…",namestring[x],namestring[bunsekikeikoaite_id],keikosuu);
			ScreenFlip() ;//裏画面を表画面にコピー
			if( ProcessMessage() == -1 ){mode=1;return;}
			for (i=0;i<RIKISISUU;i++){
				//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
				win_skip[i]=0;
				lost_skip[i]=0;
				for (ii=0;ii<15;ii++){
					if (rikisidata[i].winkonbasho[ii]==1){
						win_skip[i]++;
					}
					if (rikisidata[i].lostkonbasho[ii]==1){
						lost_skip[i]++;
					}
				}
			}
			keikowin=0;
			keikochuudanflag=0;
			aikeikochuuhyoji();
			//////直前稽古データリセット/////////
			for (i=0;i<22;i++){
				for (ii=0;ii<5;ii++){
					lastwazadata_kouka_seme[i][x][ii]=0;//
					lastwazadata_bosuu_seme[i][x][ii]=0;//
					lastwazadata_kouka_seme[i][bunsekikeikoaite_id][ii]=0;//
					lastwazadata_bosuu_seme[i][bunsekikeikoaite_id][ii]=0;//
				}
			}
			for (i=0;i<20;i++){
				lasttatiaidata_kouka_seme[x][i]=0;//どの立ち合いが勝利に結びついたか
				lasttatiaidata_bosuu_seme[x][i]=0;//どの立ち合いが勝利に結びついたか
				lasttatiaidata_kouka_seme[bunsekikeikoaite_id][i]=0;//どの立ち合いが勝利に結びついたか
				lasttatiaidata_bosuu_seme[bunsekikeikoaite_id][i]=0;//どの立ち合いが勝利に結びついたか
			}
			//AIkeikoflag=1;//lastwazadataとlasttatiaidata以外は加算しないようにするフラグ
			for (ii=0;ii<keikosuu;ii++){
				AIkeiko(x,bunsekikeikoaite_id);
				if (keikochuudanflag==1){
					break;
				}
			}
			AIkeikoflag=0;
			keikosumiflag[x]=1;keikosumiflag[bunsekikeikoaite_id]=1;
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			DrawFormatString(100,369,CRWHITE,"%sと%sが%d回AI稽古を行いました",namestring[x],namestring[bunsekikeikoaite_id],ii,CRWHITE);
			DrawFormatString(100,369+16,CRWHITE,"%sの%d勝、%sの%d勝でした",namestring[x],keikowin,namestring[bunsekikeikoaite_id],ii-keikowin,CRWHITE);
			DrawString(187,369+32,"詳細は「技分析」の直近稽古集計をご確認ください",CRWHITE);
			DrawString(187,369+64,"Hit Any Key",CRWHITE);
			ScreenFlip() ;//裏画面を表画面にコピー
			WaitKey();
			WaitTimer(200);
			goto HYOJI_torikumimaekeiko;
		}
		if (memoryfusokuflag==0){
			if (get_mouseclick_list(12) == 1 || get_mouseclick_list(13)==1){
				rikisidata[x].superrikisiflag=1;
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (rikisidata[x].superrikisiflag==101){
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*10-10);
				}else{
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*2);
				}
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick_list(14) == 1 || get_mouseclick_list(15)==1){
				rikisidata[x].superrikisiflag=2;
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (rikisidata[x].superrikisiflag==101){
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*10-10);
				}else{
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*2);
				}
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick_list(16) == 1 || get_mouseclick_list(17)==1){
				rikisidata[x].superrikisiflag=4;
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (rikisidata[x].superrikisiflag==101){
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*10-10);
				}else{
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*2);
				}
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick_list(18) == 1 || get_mouseclick_list(19)==1){
				rikisidata[x].superrikisiflag=8;
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (rikisidata[x].superrikisiflag==101){
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*10-10);
				}else{
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*2);
				}
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick_list(20) == 1 || get_mouseclick_list(21)==1){
				rikisidata[x].superrikisiflag=10;
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (rikisidata[x].superrikisiflag==101){
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*10-10);
				}else{
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*2);
				}
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick_list(22) == 1 || get_mouseclick_list(23)==1){
				rikisidata[x].superrikisiflag=20;
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (rikisidata[x].superrikisiflag==101){
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*10-10);
				}else{
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*2);
				}
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick_list(24) == 1 || get_mouseclick_list(25)==1){
				rikisidata[x].superrikisiflag=50;
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (rikisidata[x].superrikisiflag==101){
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*10-10);
				}else{
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*2);
				}
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick_list(26) == 1 || get_mouseclick_list(27)==1){
				rikisidata[x].superrikisiflag=100;
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (rikisidata[x].superrikisiflag==101){
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*10-10);
				}else{
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*2);
				}
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick_list(28) == 1 || get_mouseclick_list(29)==1){
				rikisidata[x].superrikisiflag=101;//オーバーフローしてしまうので
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (rikisidata[x].superrikisiflag==101){
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*10-10);
				}else{
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*2);
				}
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick_list(32) == 1 || get_mouseclick_list(33)==1){
				rikisidata[x].superrikisiflag=0;
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (rikisidata[x].superrikisiflag==101){
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*10-10);
				}else{
					DrawFormatString(100,369,CRWHITE,"この力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*2);
				}
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
			if (get_mouseclick(187,400,187+240,400+16) == 1){
				for (i=0;i<RIKISISUU;i++){
					rikisidata[i].superrikisiflag=rikisidata[x].superrikisiflag;
				}
				shokiti_superrikisiflag=rikisidata[x].superrikisiflag;
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				if (rikisidata[x].superrikisiflag==101){
					DrawFormatString(100,369,CRWHITE,"全ての力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*10-10);
				}else{
					DrawFormatString(100,369,CRWHITE,"全ての力士の稽古回数が%d回に変更されました",rikisidata[x].superrikisiflag*2);
				}
				DrawString(187,369+48,"Hit Any Key",CRWHITE);
				ScreenFlip() ;//裏画面を表画面にコピー
				WaitKey();
				WaitTimer(200);goto HYOJI_torikumimaekeiko;
			}
		}
		if (get_mouseclick(x1[0],y1[0]-50,x2[1],y1[0]-50+16) == 1){
			WaitTimer(200);
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

void AIkeiko(int higasiid,int nisiid)
{
	int kaeri=0;
	char higasiid_raalTOjouken0flag=0;
	char nisiid_raalTOjouken0flag=0;
	char higasiid_jouken4TOjouken0flag=0;
	char nisiid_jouken4TOjouken0flag=0;


	/*if (memoryfusokuflag==1){
		return;
	}*/

	//取り組み中のデータいじりのためのバックアップ処理
	temp_rikisidata_higasi=rikisidata[higasiid];
	temp_rikisidata_nisi=rikisidata[nisiid];
/*
	//三役以上ボーナス処理///////////////////////
	if (rikisidata[higasiid].bandukenameid==0 && sanyakuijouzaiisuu[higasiid]>=1){
		rikisidata[higasiid].tatiaigijutu+=bonus_yokoduna_tatiaigijutu;
	}
	if (rikisidata[nisiid].bandukenameid==0 && sanyakuijouzaiisuu[nisiid]>=1){
		rikisidata[nisiid].tatiaigijutu+=bonus_yokoduna_tatiaigijutu;
	}
	if (rikisidata[higasiid].bandukenameid==1 && sanyakuijouzaiisuu[higasiid]>=1){
		rikisidata[higasiid].tatiaigijutu+=bonus_oozeki_tatiaigijutu;
	}
	if (rikisidata[nisiid].bandukenameid==1 && sanyakuijouzaiisuu[nisiid]>=1){
		rikisidata[nisiid].tatiaigijutu+=bonus_oozeki_tatiaigijutu;
	}
	if (rikisidata[higasiid].bandukenameid==2 && sanyakuijouzaiisuu[higasiid]>=1){
		rikisidata[higasiid].tatiaigijutu+=bonus_sekiwake_tatiaigijutu;
	}
	if (rikisidata[nisiid].bandukenameid==2 && sanyakuijouzaiisuu[nisiid]>=1){
		rikisidata[nisiid].tatiaigijutu+=bonus_sekiwake_tatiaigijutu;
	}
	if (rikisidata[higasiid].bandukenameid==3 && sanyakuijouzaiisuu[higasiid]>=1){
		rikisidata[higasiid].tatiaigijutu+=bonus_komusubi_tatiaigijutu;
	}
	if (rikisidata[nisiid].bandukenameid==3 && sanyakuijouzaiisuu[nisiid]>=1){
		rikisidata[nisiid].tatiaigijutu+=bonus_komusubi_tatiaigijutu;
	}
	/////////////////////
*/
	//バランス調整
	rikisidata[higasiid].sinchou=(int)(rikisidata[higasiid].sinchou*bldata.sinchou/bldata.sinchou_bunbo);
	rikisidata[higasiid].taijuu=(int)(rikisidata[higasiid].taijuu*bldata.taijuu/bldata.taijuu_bunbo);
	rikisidata[higasiid].sekkyokusei=(int)(rikisidata[higasiid].sekkyokusei*bldata.sekkyokusei/bldata.sekkyokusei_bunbo);
	rikisidata[higasiid].binshousei=(int)(rikisidata[higasiid].binshousei*bldata.binshousei/bldata.binshousei_bunbo);
	rikisidata[higasiid].tossinryoku=(int)(rikisidata[higasiid].tossinryoku*bldata.tossinryoku/bldata.tossinryoku_bunbo);
	rikisidata[higasiid].kerutikara=(int)(rikisidata[higasiid].kerutikara*bldata.kerutikara/bldata.kerutikara_bunbo);
	rikisidata[higasiid].migiwanryoku=(int)(rikisidata[higasiid].migiwanryoku*bldata.migiwanryoku/bldata.migiwanryoku_bunbo);
	rikisidata[higasiid].hidariwanryoku=(int)(rikisidata[higasiid].hidariwanryoku*bldata.hidariwanryoku/bldata.hidariwanryoku_bunbo);
	rikisidata[higasiid].balance=(int)(rikisidata[higasiid].balance*bldata.balance/bldata.balance_bunbo);
	rikisidata[higasiid].tatiaigijutu=(int)(rikisidata[higasiid].tatiaigijutu*bldata.tatiaigijutu/bldata.tatiaigijutu_bunbo);
	rikisidata[higasiid].tuki=(int)(rikisidata[higasiid].tuki*bldata.tuki/bldata.tuki_bunbo);
	rikisidata[higasiid].migiwakikatasa=(int)(rikisidata[higasiid].migiwakikatasa*bldata.migiwakikatasa/bldata.migiwakikatasa_bunbo);
	rikisidata[higasiid].hidariwakikatasa=(int)(rikisidata[higasiid].hidariwakikatasa*bldata.hidariwakikatasa/bldata.hidariwakikatasa_bunbo);
	rikisidata[higasiid].ategai=(int)(rikisidata[higasiid].ategai*bldata.ategai/bldata.ategai_bunbo);
	rikisidata[higasiid].migikaesi=(int)(rikisidata[higasiid].migikaesi*bldata.migikaesi/bldata.migikaesi_bunbo);
	rikisidata[higasiid].hidarikaesi=(int)(rikisidata[higasiid].hidarikaesi*bldata.hidarikaesi/bldata.hidarikaesi_bunbo);
	rikisidata[higasiid].migisibori=(int)(rikisidata[higasiid].migisibori*bldata.migisibori/bldata.migisibori_bunbo);
	rikisidata[higasiid].hidarisibori=(int)(rikisidata[higasiid].hidarisibori*bldata.hidarisibori/bldata.hidarisibori_bunbo);
	rikisidata[higasiid].migikakaekomi=(int)(rikisidata[higasiid].migikakaekomi*bldata.migikakaekomi/bldata.migikakaekomi_bunbo);
	rikisidata[higasiid].hidarikakaekomi=(int)(rikisidata[higasiid].hidarikakaekomi*bldata.hidarikakaekomi/bldata.hidarikakaekomi_bunbo);
	rikisidata[higasiid].hikituke=(int)(rikisidata[higasiid].hikituke*bldata.hikituke/bldata.hikituke_bunbo);
	rikisidata[higasiid].migiakuryoku=(int)(rikisidata[higasiid].migiakuryoku*bldata.migiakuryoku/bldata.migiakuryoku_bunbo);
	rikisidata[higasiid].hidariakuryoku=(int)(rikisidata[higasiid].hidariakuryoku*bldata.hidariakuryoku/bldata.hidariakuryoku_bunbo);
	rikisidata[higasiid].stamina=(int)(rikisidata[higasiid].stamina*bldata.stamina/bldata.stamina_bunbo);
	rikisidata[higasiid].konjou=(int)(rikisidata[higasiid].konjou*bldata.konjou/bldata.konjou_bunbo);
	rikisidata[higasiid].nebari=(int)(rikisidata[higasiid].nebari*bldata.nebari/bldata.nebari_bunbo);
	rikisidata[higasiid].asihakobi=(int)(rikisidata[higasiid].asihakobi*bldata.asihakobi/bldata.asihakobi_bunbo);
	rikisidata[higasiid].juunansei=(int)(rikisidata[higasiid].juunansei*bldata.juunansei/bldata.juunansei_bunbo);
	rikisidata[higasiid].zunou=(int)(rikisidata[higasiid].zunou*bldata.zunou/bldata.zunou_bunbo);
	rikisidata[higasiid].migiuwatenage=(int)(rikisidata[higasiid].migiuwatenage*bldata.migiuwatenage/bldata.migiuwatenage_bunbo);
	rikisidata[higasiid].hidariuwatenage=(int)(rikisidata[higasiid].hidariuwatenage*bldata.hidariuwatenage/bldata.hidariuwatenage_bunbo);
	rikisidata[higasiid].migisitatenage=(int)(rikisidata[higasiid].migisitatenage*bldata.migisitatenage/bldata.migisitatenage_bunbo);
	rikisidata[higasiid].hidarisitatenage=(int)(rikisidata[higasiid].hidarisitatenage*bldata.hidarisitatenage/bldata.hidarisitatenage_bunbo);
	rikisidata[higasiid].migikotenage=(int)(rikisidata[higasiid].migikotenage*bldata.migikotenage/bldata.migikotenage_bunbo);
	rikisidata[higasiid].hidarikotenage=(int)(rikisidata[higasiid].hidarikotenage*bldata.hidarikotenage/bldata.hidarikotenage_bunbo);
	rikisidata[higasiid].migisukuinage=(int)(rikisidata[higasiid].migisukuinage*bldata.migisukuinage/bldata.migisukuinage_bunbo);
	rikisidata[higasiid].hidarisukuinage=(int)(rikisidata[higasiid].hidarisukuinage*bldata.hidarisukuinage/bldata.hidarisukuinage_bunbo);

	rikisidata[nisiid].sinchou=(int)(rikisidata[nisiid].sinchou*bldata.sinchou/bldata.sinchou_bunbo);
	rikisidata[nisiid].taijuu=(int)(rikisidata[nisiid].taijuu*bldata.taijuu/bldata.taijuu_bunbo);
	rikisidata[nisiid].sekkyokusei=(int)(rikisidata[nisiid].sekkyokusei*bldata.sekkyokusei/bldata.sekkyokusei_bunbo);
	rikisidata[nisiid].binshousei=(int)(rikisidata[nisiid].binshousei*bldata.binshousei/bldata.binshousei_bunbo);
	rikisidata[nisiid].tossinryoku=(int)(rikisidata[nisiid].tossinryoku*bldata.tossinryoku/bldata.tossinryoku_bunbo);
	rikisidata[nisiid].kerutikara=(int)(rikisidata[nisiid].kerutikara*bldata.kerutikara/bldata.kerutikara_bunbo);
	rikisidata[nisiid].migiwanryoku=(int)(rikisidata[nisiid].migiwanryoku*bldata.migiwanryoku/bldata.migiwanryoku_bunbo);
	rikisidata[nisiid].hidariwanryoku=(int)(rikisidata[nisiid].hidariwanryoku*bldata.hidariwanryoku/bldata.hidariwanryoku_bunbo);
	rikisidata[nisiid].balance=(int)(rikisidata[nisiid].balance*bldata.balance/bldata.balance_bunbo);
	rikisidata[nisiid].tatiaigijutu=(int)(rikisidata[nisiid].tatiaigijutu*bldata.tatiaigijutu/bldata.tatiaigijutu_bunbo);
	rikisidata[nisiid].tuki=(int)(rikisidata[nisiid].tuki*bldata.tuki/bldata.tuki_bunbo);
	rikisidata[nisiid].migiwakikatasa=(int)(rikisidata[nisiid].migiwakikatasa*bldata.migiwakikatasa/bldata.migiwakikatasa_bunbo);
	rikisidata[nisiid].hidariwakikatasa=(int)(rikisidata[nisiid].hidariwakikatasa*bldata.hidariwakikatasa/bldata.hidariwakikatasa_bunbo);
	rikisidata[nisiid].ategai=(int)(rikisidata[nisiid].ategai*bldata.ategai/bldata.ategai_bunbo);
	rikisidata[nisiid].migikaesi=(int)(rikisidata[nisiid].migikaesi*bldata.migikaesi/bldata.migikaesi_bunbo);
	rikisidata[nisiid].hidarikaesi=(int)(rikisidata[nisiid].hidarikaesi*bldata.hidarikaesi/bldata.hidarikaesi_bunbo);
	rikisidata[nisiid].migisibori=(int)(rikisidata[nisiid].migisibori*bldata.migisibori/bldata.migisibori_bunbo);
	rikisidata[nisiid].hidarisibori=(int)(rikisidata[nisiid].hidarisibori*bldata.hidarisibori/bldata.hidarisibori_bunbo);
	rikisidata[nisiid].migikakaekomi=(int)(rikisidata[nisiid].migikakaekomi*bldata.migikakaekomi/bldata.migikakaekomi_bunbo);
	rikisidata[nisiid].hidarikakaekomi=(int)(rikisidata[nisiid].hidarikakaekomi*bldata.hidarikakaekomi/bldata.hidarikakaekomi_bunbo);
	rikisidata[nisiid].hikituke=(int)(rikisidata[nisiid].hikituke*bldata.hikituke/bldata.hikituke_bunbo);
	rikisidata[nisiid].migiakuryoku=(int)(rikisidata[nisiid].migiakuryoku*bldata.migiakuryoku/bldata.migiakuryoku_bunbo);
	rikisidata[nisiid].hidariakuryoku=(int)(rikisidata[nisiid].hidariakuryoku*bldata.hidariakuryoku/bldata.hidariakuryoku_bunbo);
	rikisidata[nisiid].stamina=(int)(rikisidata[nisiid].stamina*bldata.stamina/bldata.stamina_bunbo);
	rikisidata[nisiid].konjou=(int)(rikisidata[nisiid].konjou*bldata.konjou/bldata.konjou_bunbo);
	rikisidata[nisiid].nebari=(int)(rikisidata[nisiid].nebari*bldata.nebari/bldata.nebari_bunbo);
	rikisidata[nisiid].asihakobi=(int)(rikisidata[nisiid].asihakobi*bldata.asihakobi/bldata.asihakobi_bunbo);
	rikisidata[nisiid].juunansei=(int)(rikisidata[nisiid].juunansei*bldata.juunansei/bldata.juunansei_bunbo);
	rikisidata[nisiid].zunou=(int)(rikisidata[nisiid].zunou*bldata.zunou/bldata.zunou_bunbo);
	rikisidata[nisiid].migiuwatenage=(int)(rikisidata[nisiid].migiuwatenage*bldata.migiuwatenage/bldata.migiuwatenage_bunbo);
	rikisidata[nisiid].hidariuwatenage=(int)(rikisidata[nisiid].hidariuwatenage*bldata.hidariuwatenage/bldata.hidariuwatenage_bunbo);
	rikisidata[nisiid].migisitatenage=(int)(rikisidata[nisiid].migisitatenage*bldata.migisitatenage/bldata.migisitatenage_bunbo);
	rikisidata[nisiid].hidarisitatenage=(int)(rikisidata[nisiid].hidarisitatenage*bldata.hidarisitatenage/bldata.hidarisitatenage_bunbo);
	rikisidata[nisiid].migikotenage=(int)(rikisidata[nisiid].migikotenage*bldata.migikotenage/bldata.migikotenage_bunbo);
	rikisidata[nisiid].hidarikotenage=(int)(rikisidata[nisiid].hidarikotenage*bldata.hidarikotenage/bldata.hidarikotenage_bunbo);
	rikisidata[nisiid].migisukuinage=(int)(rikisidata[nisiid].migisukuinage*bldata.migisukuinage/bldata.migisukuinage_bunbo);
	rikisidata[nisiid].hidarisukuinage=(int)(rikisidata[nisiid].hidarisukuinage*bldata.hidarisukuinage/bldata.hidarisukuinage_bunbo);

	////////テレパシーの力士は既定の作戦にしてしまおう//////////
	higasiid_raalTOjouken0flag=0;
	nisiid_raalTOjouken0flag=0;
	if (rikisidata[higasiid].realmodeflag==1){
		joukendata[higasiid].joukenflag=0;
		higasiid_raalTOjouken0flag=1;
	}
	if (rikisidata[nisiid].realmodeflag==1){
		joukendata[nisiid].joukenflag=0;
		nisiid_raalTOjouken0flag=1;
	}
	////////deepAI力士は既定の作戦にしてしまおう//////////
	higasiid_jouken4TOjouken0flag=0;
	nisiid_jouken4TOjouken0flag=0;
	if (joukendata[higasiid].joukenflag==4){
		joukendata[higasiid].joukenflag=0;
		higasiid_jouken4TOjouken0flag=1;
	}
	if (joukendata[nisiid].joukenflag==4){
		joukendata[nisiid].joukenflag=0;
		nisiid_jouken4TOjouken0flag=1;
	}


	//取り組みの核心ルーチン呼び出し
	count_temp_aidata=0;
	kaeri=fight_fight_keiko(higasiid,nisiid);

	////////テレパシーの力士は既定の作戦にしてしまおうの戻し//////////
	if (higasiid_raalTOjouken0flag==1) rikisidata[higasiid].realmodeflag=1;
	if (nisiid_raalTOjouken0flag==1) rikisidata[nisiid].realmodeflag=1;
	////////deepAI力士は既定の作戦にしてしまおうの戻し//////////
	if (higasiid_jouken4TOjouken0flag==1) joukendata[higasiid].joukenflag=4;
	if (nisiid_jouken4TOjouken0flag==1) joukendata[nisiid].joukenflag=4;

	//if( ProcessMessage() == -1 ){mode=1;return;}

	if (mode==1){
		return;
	}
	//aidata保存
	if (kaeri==1){//東方の勝ち
		hozon_aidata(higasiid,nisiid,higasiid);
		keikowin++;
	}else{
		hozon_aidata(higasiid,nisiid,nisiid);
	}
	//バックアップからの戻し
	rikisidata[higasiid]=temp_rikisidata_higasi;
	rikisidata[nisiid]=temp_rikisidata_nisi;

	return;
}


int fight_fight_keiko(int higasiid,int nisiid)//東が勝なら1、西が勝なら2を返す
{
	char p_max=0;
	char pid_max=0;
	char temp_pid=0;
		int startid;
		int temp_wazaid;
		char yotu=0;
		char yotu_max=0;
		char temp_char=0;
		char waza_max=0;
		int wazaid_max=0;
		char jibunmigimawasi,jibunhidarimawasi,aitemigimawasi,aitehidarimawasi;
		char joutaiflag=0;
		long temp_fichi=0;
		char bytedata=0;
		char waza_sisuu[22];
		char makikaedameflag=0;

	char zunouflag_higasi=0;
	char zunouflag_nisi=0;

	//int temp_joukenflag_higasi,temp_joukenflag_nisi;
	char kioi_flag_higasi=0;
	char kioi_flag_nisi=0;
	char chuucho_flag_higasi=0;
	char chuucho_flag_nisi=0;
	char yowaki_flag_higasi=0;
	char yowaki_flag_nisi=0;
	char pride_flag_higasi=0;
	char pride_flag_nisi=0;

	int nerai_higasi,nerai_nisi,ikioi_higasi,ikioi_nisi;
	int nowwazatrysuu;
	int nebari_loss;
	int loopderuflag=0;
	//int ichi_lastturn=0;→3.17からグローバルに
	int starttime;
	int nyuuryokuti=0;
	int i;
	int ii,iii;
	int r;
	int rr;
	int temp;
	int totalsentakuritu;
	int balancenaosi;
//	int higasimagire=0;//紛れ
//	int nisimagire=0;//紛れ
//	int migiorhidari_higasi;//右半身の攻撃＞1、左半身の攻撃＞2
//	int migiorhidari_nisi;//
	int wazatrycount;
	int nebaritrycount_higasi=0;
	int nebaritrycount_nisi=0;
	int staminagirehyojiflag_higasi;
	int staminagirehyojiflag_nisi;
	int shousan[20];
	int junban[20];
	int wazapattern_far_sentakuwazaid_higasi[5];
	int wazapattern_far_sentakuwazaid_maxtry_higasi[5];
	int wazapattern_far_sentakuwazaid_trysuu_higasi[5];
	int wazapattern_middle_sentakuwazaid_higasi[5];
	int wazapattern_middle_sentakuwazaid_maxtry_higasi[5];
	int wazapattern_middle_sentakuwazaid_trysuu_higasi[5];
	int wazapattern_near_sentakuwazaid_higasi[5];
	int wazapattern_near_sentakuwazaid_maxtry_higasi[5];
	int wazapattern_near_sentakuwazaid_trysuu_higasi[5];
	int wazapattern_far_sentakuwazaid_nisi[5];
	int wazapattern_far_sentakuwazaid_maxtry_nisi[5];
	int wazapattern_far_sentakuwazaid_trysuu_nisi[5];
	int wazapattern_middle_sentakuwazaid_nisi[5];
	int wazapattern_middle_sentakuwazaid_maxtry_nisi[5];
	int wazapattern_middle_sentakuwazaid_trysuu_nisi[5];
	int wazapattern_near_sentakuwazaid_nisi[5];
	int wazapattern_near_sentakuwazaid_maxtry_nisi[5];
	int wazapattern_near_sentakuwazaid_trysuu_nisi[5];
	int joukentrysuu_higasi[2][100];
	int joukentrysuu_nisi[2][100];
	long temp_long=0;

	///////////higasi_aidata[]とnisi_aidata[]に代入//////////////////////////
//	memcpy(higasi_aidata, aidata+(higasiid*RIKISISUU*AIDATABYTESUU + nisiid*AIDATABYTESUU), sizeof(higasi_aidata));
//	memcpy(nisi_aidata, aidata+(nisiid*RIKISISUU*AIDATABYTESUU + higasiid*AIDATABYTESUU), sizeof(nisi_aidata));
	//if( ProcessMessage() == -1 ){mode=1;return 0;}

	////////////////////////////////////////////////////////



	for (i=0;i<100;i++){
		joukentrysuu_higasi[0][i]=0;
		joukentrysuu_higasi[1][i]=0;
		joukentrysuu_nisi[0][i]=0;
		joukentrysuu_nisi[1][i]=0;
	}
	for (i=0;i<5;i++){
		wazapattern_far_sentakuwazaid_higasi[i];
		wazapattern_far_sentakuwazaid_maxtry_higasi[i];
		wazapattern_far_sentakuwazaid_trysuu_higasi[i];
		wazapattern_middle_sentakuwazaid_higasi[i];
		wazapattern_middle_sentakuwazaid_maxtry_higasi[i];
		wazapattern_middle_sentakuwazaid_trysuu_higasi[i];
		wazapattern_near_sentakuwazaid_higasi[i];
		wazapattern_near_sentakuwazaid_maxtry_higasi[i];
		wazapattern_near_sentakuwazaid_trysuu_higasi[i];
		wazapattern_far_sentakuwazaid_nisi[i];
		wazapattern_far_sentakuwazaid_maxtry_nisi[i];
		wazapattern_far_sentakuwazaid_trysuu_nisi[i];
		wazapattern_middle_sentakuwazaid_nisi[i];
		wazapattern_middle_sentakuwazaid_maxtry_nisi[i];
		wazapattern_middle_sentakuwazaid_trysuu_nisi[i];
		wazapattern_near_sentakuwazaid_nisi[i];
		wazapattern_near_sentakuwazaid_maxtry_nisi[i];
		wazapattern_near_sentakuwazaid_trysuu_nisi[i];
	}
	for (i=0;i<20;i++){
		shousan[i]=0;
	}

	//初期化
	joukendata_temp_higasi=joukendata[higasiid];
	joukendata_temp_nisi=joukendata[nisiid];
	joukendata2_temp_higasi=joukendata2[higasiid];
	joukendata2_temp_nisi=joukendata2[nisiid];
	//matatukihanasitaflag=0;
	state_kyori=FAR_STATE_KYORI;
	state_ichi=0;
   	offense_state_jouge=LOW_STATE_JOUGE ;
    offense_action_zengo=MAE_ACTION_ZENGO ;
    offense_action_sayuu=NASI_ACTION_SAYUU ;
   	offense_state_migiude=MAE_STATE_UDE ;
    offense_state_hidariude=MAE_STATE_UDE ;
   	offense_action_migiude=NASI_ACTION_UDE ;
    offense_action_hidariude=NASI_ACTION_UDE ;
    defense_state_jouge=LOW_STATE_JOUGE ;
   	defense_action_zengo=MAE_ACTION_ZENGO ;
    defense_action_sayuu=NASI_ACTION_SAYUU ;
   	defense_state_migiude=MAE_STATE_UDE ;
    defense_state_hidariude=MAE_STATE_UDE ;
   	defense_action_migiude=NASI_ACTION_UDE ;
    defense_action_hidariude=NASI_ACTION_UDE ;

	offense_stamina=0;
	defense_stamina=0;

	turncount=0;
	
	staminagirehyojiflag_higasi=0;
	staminagirehyojiflag_nisi=0;

	higasi_tatiai_power=ZENRYOKU_TATIAI_POWER;
	nisi_tatiai_power=ZENRYOKU_TATIAI_POWER;
	higasi_tatiai_nerai=TUKIOSI_TATIAI_NERAI;
	nisi_tatiai_nerai=TUKIOSI_TATIAI_NERAI;
    offense_state_balance=10 ;
   	defense_state_balance=10 ;

	////////テレパシーの力士は既定の作戦にしてしまおう//////////
	//if (rikisidata[higasiid].realmodeflag==1) joukendata[higasiid].joukenflag=0;
	//if (rikisidata[nisiid].realmodeflag==1) joukendata[nisiid].joukenflag=0;
	
	//東力士の技パターンの選択
	wazapatternid_higasi=rikisidata[higasiid].motiwazapattern[0];

	//西力士の技パターンの選択
	wazapatternid_nisi=rikisidata[nisiid].motiwazapattern[0];

	//東力士の立会いパターンの選択
	if (joukendata[higasiid].joukenflag==0){
		r=GetRand(99);
		if (r<ritu_tatiai_zenryoku){
			tatiaipatternid_higasi=rikisidata[higasiid].motitatiaipattern[0];
		}else if(r<ritu_tatiai_zenryoku+ritu_tatiai_tuyoku){
			tatiaipatternid_higasi=rikisidata[higasiid].motitatiaipattern[1];
		}else if(r<ritu_tatiai_zenryoku+ritu_tatiai_tuyoku+ritu_tatiai_uke){
			tatiaipatternid_higasi=rikisidata[higasiid].motitatiaipattern[2];
		}else{
			tatiaipatternid_higasi=rikisidata[higasiid].motitatiaipattern[3];
		}
	}else if (joukendata[higasiid].joukenflag==1){
		r=GetRand(99);
		if (r<ritu_tatiai_zenryoku){
			tatiaipatternid_higasi=joukendata[higasiid].motitatiaipattern_sakusen[0];
		}else if(r<ritu_tatiai_zenryoku+ritu_tatiai_tuyoku){
			tatiaipatternid_higasi=joukendata[higasiid].motitatiaipattern_sakusen[1];
		}else if(r<ritu_tatiai_zenryoku+ritu_tatiai_tuyoku+ritu_tatiai_uke){
			tatiaipatternid_higasi=joukendata[higasiid].motitatiaipattern_sakusen[2];
		}else{
			tatiaipatternid_higasi=joukendata[higasiid].motitatiaipattern_sakusen[3];
		}
	}else if (joukendata[higasiid].joukenflag==2){
		r=GetRand(99);
		if (r<ritu_tatiai_zenryoku){
			tatiaipatternid_higasi=joukendata[higasiid].motitatiaipattern_jouken[0];
		}else if(r<ritu_tatiai_zenryoku+ritu_tatiai_tuyoku){
			tatiaipatternid_higasi=joukendata[higasiid].motitatiaipattern_jouken[1];
		}else if(r<ritu_tatiai_zenryoku+ritu_tatiai_tuyoku+ritu_tatiai_uke){
			tatiaipatternid_higasi=joukendata[higasiid].motitatiaipattern_jouken[2];
		}else{
			tatiaipatternid_higasi=joukendata[higasiid].motitatiaipattern_jouken[3];
		}
	}else if (joukendata[higasiid].joukenflag==3){
		////////////////Ver4.00からのAIの選択/////////////////////////
		temp_char=0;
		p_max=-1;
		pid_max=0;
		bytedata=0;
		for (i=0;i<20;i++){//tatiaipatternid_higasi,nisiの20種類
			//if( ProcessMessage() == -1 ){mode=1;return 0;}
			startid=GetRand(19);
			temp_pid=i+startid;
			if (temp_pid>19) temp_pid-=20;
			if (kobetu_sikiiti[higasiid]<=aikeikosuu[higasiid][nisiid]){
				//////力士ごとデータ//////
				memcpy(&bytedata, 
					aidata_tatiai
					+higasiid*RIKISISUU*AIDATATATIAIBYTESUU
					+nisiid*AIDATATATIAIBYTESUU
					+(int)(temp_pid/4),
					sizeof(char));
			}else{
				//////トータルデータ//////
				memcpy(&bytedata, 
					aidata_tatiai
					+higasiid*RIKISISUU*AIDATATATIAIBYTESUU
					+higasiid*AIDATATATIAIBYTESUU
					+(int)(temp_pid/4),
					sizeof(char));
			}
			//値取り出し
			temp_char=getdatafrombit(bytedata,temp_pid%4);
			if (p_max<temp_char){
				p_max=temp_char;
				pid_max=temp_pid;
			}
		}
		tatiaipatternid_higasi=pid_max;
		//気負いで全力が受け、変化が受け
		if (tatiaipatternid_higasi%4==0){
			if (GetRand(1)==0){
				tatiaipatternid_higasi+=2;
				kioi_flag_higasi=1;
			}
		}else if (tatiaipatternid_higasi%4==3){
			if (GetRand(1)==0 && rikisidata[higasiid].bandukenameid>1){
				tatiaipatternid_higasi--;
				chuucho_flag_higasi=1;
			}
		}
	}

	//西力士の立会いパターンの選択
	if (joukendata[nisiid].joukenflag==0){
		r=GetRand(99);
		if (r<ritu_tatiai_zenryoku){
			tatiaipatternid_nisi=rikisidata[nisiid].motitatiaipattern[0];
		}else if(r<ritu_tatiai_zenryoku+ritu_tatiai_tuyoku){
			tatiaipatternid_nisi=rikisidata[nisiid].motitatiaipattern[1];
		}else if(r<ritu_tatiai_zenryoku+ritu_tatiai_tuyoku+ritu_tatiai_uke){
			tatiaipatternid_nisi=rikisidata[nisiid].motitatiaipattern[2];
		}else{
			tatiaipatternid_nisi=rikisidata[nisiid].motitatiaipattern[3];
		}
	}else if (joukendata[nisiid].joukenflag==1){
		r=GetRand(99);
		if (r<ritu_tatiai_zenryoku){
			tatiaipatternid_nisi=joukendata[nisiid].motitatiaipattern_sakusen[0];
		}else if(r<ritu_tatiai_zenryoku+ritu_tatiai_tuyoku){
			tatiaipatternid_nisi=joukendata[nisiid].motitatiaipattern_sakusen[1];
		}else if(r<ritu_tatiai_zenryoku+ritu_tatiai_tuyoku+ritu_tatiai_uke){
			tatiaipatternid_nisi=joukendata[nisiid].motitatiaipattern_sakusen[2];
		}else{
			tatiaipatternid_nisi=joukendata[nisiid].motitatiaipattern_sakusen[3];
		}
	}else if (joukendata[nisiid].joukenflag==2){
		r=GetRand(99);
		if (r<ritu_tatiai_zenryoku){
			tatiaipatternid_nisi=joukendata[nisiid].motitatiaipattern_jouken[0];
		}else if(r<ritu_tatiai_zenryoku+ritu_tatiai_tuyoku){
			tatiaipatternid_nisi=joukendata[nisiid].motitatiaipattern_jouken[1];
		}else if(r<ritu_tatiai_zenryoku+ritu_tatiai_tuyoku+ritu_tatiai_uke){
			tatiaipatternid_nisi=joukendata[nisiid].motitatiaipattern_jouken[2];
		}else{
			tatiaipatternid_nisi=joukendata[nisiid].motitatiaipattern_jouken[3];
		}
	}else if (joukendata[nisiid].joukenflag==3){
		////////////////Ver4.00からのAIの選択/////////////////////////
		temp_char=0;
		p_max=-1;
		pid_max=0;
		bytedata=0;
		for (i=0;i<20;i++){//tatiaipatternid_higasi,nisiの20種類
			//if( ProcessMessage() == -1 ){mode=1;return 0;}
			startid=GetRand(19);
			temp_pid=i+startid;
			if (temp_pid>19) temp_pid-=20;
			if (kobetu_sikiiti[nisiid]<=aikeikosuu[nisiid][higasiid]){
				//////力士ごとデータ//////
				memcpy(&bytedata, 
					aidata_tatiai
					+nisiid*RIKISISUU*AIDATATATIAIBYTESUU
					+higasiid*AIDATATATIAIBYTESUU
					+(int)(temp_pid/4),
					sizeof(char));
			}else{
				//////トータルデータ//////
				memcpy(&bytedata, 
					aidata_tatiai
					+nisiid*RIKISISUU*AIDATATATIAIBYTESUU
					+nisiid*AIDATATATIAIBYTESUU
					+(int)(temp_pid/4),
					sizeof(char));
			}
			//値取り出し
			temp_char=getdatafrombit(bytedata,temp_pid%4);
			if (p_max<temp_char){
				p_max=temp_char;
				pid_max=temp_pid;
			}
		}
		tatiaipatternid_nisi=pid_max;
		//気負いで全力が受け、変化が受け
		if (tatiaipatternid_nisi%4==0){
			if (GetRand(1)==0){
				tatiaipatternid_nisi+=2;
				kioi_flag_nisi=1;
			}
		}else if (tatiaipatternid_nisi%4==3){
			if (GetRand(1)==0 && rikisidata[nisiid].bandukenameid>1){
				tatiaipatternid_nisi--;
				chuucho_flag_nisi=1;
			}
		}
	}


	//ファイトルーチン用に代入処理
	if (joukendata[higasiid].joukenflag==0){
		for (i=0;i<5;i++){
			wazapattern_far_sentakuwazaid_higasi[i]=wazapattern_far_sentakuwazaid[wazapatternid_higasi][i];
			wazapattern_far_sentakuwazaid_maxtry_higasi[i]=wazapattern_far_sentakuwazaid_maxtry[wazapatternid_higasi][i];
			wazapattern_near_sentakuwazaid_higasi[i]=wazapattern_near_sentakuwazaid[wazapatternid_higasi][i];
			wazapattern_near_sentakuwazaid_maxtry_higasi[i]=wazapattern_near_sentakuwazaid_maxtry[wazapatternid_higasi][i];
		}
	}else if (joukendata[higasiid].joukenflag==1){
		if (rikisidata[higasiid].motiwazapattern[1]==0){
			for (i=0;i<5;i++){
				wazapattern_far_sentakuwazaid_higasi[i]=1;
				wazapattern_far_sentakuwazaid_maxtry_higasi[i]=999;
			}
		}else if (rikisidata[higasiid].motiwazapattern[1]==2){
			for (i=0;i<5;i++){
				wazapattern_far_sentakuwazaid_higasi[i]=2;
				wazapattern_far_sentakuwazaid_maxtry_higasi[i]=999;
			}
		}else{
			wazapattern_far_sentakuwazaid_higasi[0]=1;
			wazapattern_far_sentakuwazaid_maxtry_higasi[0]=1;
			wazapattern_far_sentakuwazaid_higasi[1]=2;
			wazapattern_far_sentakuwazaid_maxtry_higasi[1]=1;
			wazapattern_far_sentakuwazaid_higasi[2]=1;
			wazapattern_far_sentakuwazaid_maxtry_higasi[2]=1;
			wazapattern_far_sentakuwazaid_higasi[3]=2;
			wazapattern_far_sentakuwazaid_maxtry_higasi[3]=1;
			wazapattern_far_sentakuwazaid_higasi[4]=1;
			wazapattern_far_sentakuwazaid_maxtry_higasi[4]=1;
		}
		for (i=0;i<5;i++){
			wazapattern_near_sentakuwazaid_higasi[i]=rikisidata[higasiid].motiwazapattern_sentakuritu[i];//nearの時の選択技ＩD
			wazapattern_near_sentakuwazaid_maxtry_higasi[i]=rikisidata[higasiid].motitatiaipattern_sentakuritu[i];//nearの時の各選択技ＭＡＸＴＲＹ数
		}
	}
	if (joukendata[nisiid].joukenflag==0){
		for (i=0;i<5;i++){
			wazapattern_far_sentakuwazaid_nisi[i]=wazapattern_far_sentakuwazaid[wazapatternid_nisi][i];
			wazapattern_far_sentakuwazaid_maxtry_nisi[i]=wazapattern_far_sentakuwazaid_maxtry[wazapatternid_nisi][i];
			wazapattern_near_sentakuwazaid_nisi[i]=wazapattern_near_sentakuwazaid[wazapatternid_nisi][i];
			wazapattern_near_sentakuwazaid_maxtry_nisi[i]=wazapattern_near_sentakuwazaid_maxtry[wazapatternid_nisi][i];
		}
	}else if (joukendata[nisiid].joukenflag==1){
		if (rikisidata[nisiid].motiwazapattern[1]==0){
			for (i=0;i<5;i++){
				wazapattern_far_sentakuwazaid_nisi[i]=1;
				wazapattern_far_sentakuwazaid_maxtry_nisi[i]=999;
			}
		}else if (rikisidata[nisiid].motiwazapattern[1]==2){
			for (i=0;i<5;i++){
				wazapattern_far_sentakuwazaid_nisi[i]=2;
				wazapattern_far_sentakuwazaid_maxtry_nisi[i]=999;
			}
		}else{
			wazapattern_far_sentakuwazaid_nisi[0]=1;
			wazapattern_far_sentakuwazaid_maxtry_nisi[0]=1;
			wazapattern_far_sentakuwazaid_nisi[1]=2;
			wazapattern_far_sentakuwazaid_maxtry_nisi[0]=1;
			wazapattern_far_sentakuwazaid_nisi[2]=1;
			wazapattern_far_sentakuwazaid_maxtry_nisi[0]=1;
			wazapattern_far_sentakuwazaid_nisi[3]=2;
			wazapattern_far_sentakuwazaid_maxtry_nisi[0]=1;
			wazapattern_far_sentakuwazaid_nisi[4]=1;
			wazapattern_far_sentakuwazaid_maxtry_nisi[0]=1;
		}
		for (i=0;i<5;i++){
			wazapattern_near_sentakuwazaid_nisi[i]=rikisidata[nisiid].motiwazapattern_sentakuritu[i];//nearの時の選択技ＩD
			wazapattern_near_sentakuwazaid_maxtry_nisi[i]=rikisidata[nisiid].motitatiaipattern_sentakuritu[i];//nearの時の各選択技ＭＡＸＴＲＹ数
		}
	}

	/////////////aidata用の立合いの勢いの意図の段階での保存
	ito_higasi_tatiai_power=tatiaipattern_powerid[tatiaipatternid_higasi];
	ito_nisi_tatiai_power=tatiaipattern_powerid[tatiaipatternid_nisi];

	//積極性が低いほど受け・変化の立会いが多くなるようにする処理
	if (rikisidata[higasiid].sekkyokusei<GetRand(100) && GetRand(2)==1){
		if (GetRand(1)==0 && chuucho_flag_higasi==0 && kioi_flag_higasi==0){//受けの立会い
			yowaki_flag_higasi=1;
			if (tatiaipatternid_higasi<4){
				tatiaipatternid_higasi=2;
			}else if (tatiaipatternid_higasi<8){
				tatiaipatternid_higasi=6;
			}else if (tatiaipatternid_higasi<12){
				tatiaipatternid_higasi=10;
			}else if (tatiaipatternid_higasi<16){
				tatiaipatternid_higasi=14;
			}else{
				tatiaipatternid_higasi=18;
			}
		}else if(rikisidata[higasiid].bandukenameid>1){//変化の立会い
			yowaki_flag_higasi=1;
			if (tatiaipatternid_higasi<4){
				tatiaipatternid_higasi=3;
			}else if (tatiaipatternid_higasi<8){
				tatiaipatternid_higasi=7;
			}else if (tatiaipatternid_higasi<12){
				tatiaipatternid_higasi=11;
			}else if (tatiaipatternid_higasi<16){
				tatiaipatternid_higasi=15;
			}else{
				tatiaipatternid_higasi=19;
			}
		}
	}
	if (rikisidata[nisiid].sekkyokusei<GetRand(100) && GetRand(2)==1){
		if (GetRand(1)==0 && chuucho_flag_nisi==0 && kioi_flag_nisi==0){
			yowaki_flag_nisi=1;
			if (tatiaipatternid_nisi<4){
				tatiaipatternid_nisi=2;
			}else if (tatiaipatternid_nisi<8){
				tatiaipatternid_nisi=6;
			}else if (tatiaipatternid_nisi<12){
				tatiaipatternid_nisi=10;
			}else if (tatiaipatternid_nisi<16){
				tatiaipatternid_nisi=14;
			}else{
				tatiaipatternid_nisi=18;
			}
		}else if (rikisidata[nisiid].bandukenameid>1){
			yowaki_flag_nisi=1;
			if (tatiaipatternid_nisi<4){
				tatiaipatternid_nisi=3;
			}else if (tatiaipatternid_nisi<8){
				tatiaipatternid_nisi=7;
			}else if (tatiaipatternid_nisi<12){
				tatiaipatternid_nisi=11;
			}else if (tatiaipatternid_nisi<16){
				tatiaipatternid_nisi=15;
			}else{
				tatiaipatternid_nisi=19;
			}
		}
	}

	//横綱と大関は、変化する立会いをしないようにする処理
	if (rikisidata[higasiid].bandukenameid<2){
		if (tatiaipatternid_higasi==3){ tatiaipatternid_higasi=2;pride_flag_higasi=1;}
		if (tatiaipatternid_higasi==7){ tatiaipatternid_higasi=6;pride_flag_higasi=1;}
		if (tatiaipatternid_higasi==11){ tatiaipatternid_higasi=10;pride_flag_higasi=1;}
		if (tatiaipatternid_higasi==15){ tatiaipatternid_higasi=14;pride_flag_higasi=1;}
		if (tatiaipatternid_higasi==19){ tatiaipatternid_higasi=18;pride_flag_higasi=1;}
	}
	if (rikisidata[nisiid].bandukenameid<2){
		if (tatiaipatternid_nisi==3){ tatiaipatternid_nisi=2;pride_flag_nisi=1;}
		if (tatiaipatternid_nisi==7){ tatiaipatternid_nisi=6;pride_flag_nisi=1;}
		if (tatiaipatternid_nisi==11){ tatiaipatternid_nisi=10;pride_flag_nisi=1;}
		if (tatiaipatternid_nisi==15){ tatiaipatternid_nisi=14;pride_flag_nisi=1;}
		if (tatiaipatternid_nisi==19){ tatiaipatternid_nisi=18;pride_flag_nisi=1;}
	}
	//立会いが突き押し以外なら、突きの威力を1/3させる処理
	if (tatiaipatternid_higasi>3){
		rikisidata[higasiid].tuki=(int)(rikisidata[higasiid].tuki/3);
	}
	if (tatiaipatternid_nisi>3){
		rikisidata[nisiid].tuki=(int)(rikisidata[nisiid].tuki/3);
	}

	//立会いの処理

	//立会いの勢いと狙いを確定
	higasi_tatiai_power=tatiaipattern_powerid[tatiaipatternid_higasi];
	nisi_tatiai_power=tatiaipattern_powerid[tatiaipatternid_nisi];
	higasi_tatiai_nerai=tatiaipattern_neraiid[tatiaipatternid_higasi];
	nisi_tatiai_nerai=tatiaipattern_neraiid[tatiaipatternid_nisi];

	//稽古のために一時的にスタミナ回復
	rikisidata[higasiid].stamina=200;
	rikisidata[nisiid].stamina=200;

	//立会いの結果処理
	if (higasi_tatiai_power==ZENRYOKU_TATIAI_POWER
	 && nisi_tatiai_power==ZENRYOKU_TATIAI_POWER){
		if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		>GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else{
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}
	    offense_action_zengo=MAE_ACTION_ZENGO ;
	    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  	defense_action_zengo=MAE_ACTION_ZENGO ;
   		defense_action_sayuu=NASI_ACTION_SAYUU ;
	 }else if (higasi_tatiai_power==ZENRYOKU_TATIAI_POWER
	  && nisi_tatiai_power==NORMAL_TATIAI_POWER){
		if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		>GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=2;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		>GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2/2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=1;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else{
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}
	    offense_action_zengo=MAE_ACTION_ZENGO ;
	    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  	defense_action_zengo=MAE_ACTION_ZENGO ;
   		defense_action_sayuu=NASI_ACTION_SAYUU ;
	 }else if (higasi_tatiai_power==ZENRYOKU_TATIAI_POWER
	  && nisi_tatiai_power==UKERU_TATIAI_POWER){
		if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		>GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=3;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		>GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2/2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=2;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		>GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2/4+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=1;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else{
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}
	    offense_action_zengo=MAE_ACTION_ZENGO ;
	    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  	defense_action_zengo=MAE_ACTION_ZENGO ;
   		defense_action_sayuu=NASI_ACTION_SAYUU ;
	 }else if (higasi_tatiai_power==ZENRYOKU_TATIAI_POWER
	  && nisi_tatiai_power==HENKA_TATIAI_POWER){
		if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei/2
		>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=3;
		    offense_action_zengo=MAE_ACTION_ZENGO ;
		    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  		defense_action_zengo=NASI_ACTION_ZENGO ;
	   		defense_action_sayuu=YOKO_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei/2
			>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=LOW_STATE_JOUGE;
			}
		}else{
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
   			defense_state_balance-=5 ;
		    offense_action_zengo=NASI_ACTION_ZENGO ;
		    offense_action_sayuu=YOKO_ACTION_SAYUU ;
	  		defense_action_zengo=MAE_ACTION_ZENGO ;
	   		defense_action_sayuu=NASI_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei/2){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=LOW_STATE_JOUGE;
			}
		}

	}else if (higasi_tatiai_power==NORMAL_TATIAI_POWER
	 && nisi_tatiai_power==ZENRYOKU_TATIAI_POWER){
		if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		<GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=-2;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2/2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		<GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=-1;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else{
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}
	    offense_action_zengo=MAE_ACTION_ZENGO ;
	    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  	defense_action_zengo=MAE_ACTION_ZENGO ;
   		defense_action_sayuu=NASI_ACTION_SAYUU ;
	 }else if (higasi_tatiai_power==NORMAL_TATIAI_POWER
	  && nisi_tatiai_power==NORMAL_TATIAI_POWER){
		if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2/2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		>GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2/2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
//			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou*3-(rikisidata[higasiid].tatiaigijutu+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2/2+rikisidata[higasiid].kerutikara)
//			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou*3-(rikisidata[nisiid].tatiaigijutu+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2/2+rikisidata[nisiid].kerutikara)){
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
//			if (GetRand(99)<50){
//		   		offense_state_jouge=MIDDLE_STATE_JOUGE;
//				defense_state_jouge=MIDDLE_STATE_JOUGE;
//			}else if(GetRand(99)<50){
//		   		offense_state_jouge=LOW_STATE_JOUGE;
//				defense_state_jouge=MIDDLE_STATE_JOUGE;
//			}else{
//		   		offense_state_jouge=MIDDLE_STATE_JOUGE;
//				defense_state_jouge=HIGH_STATE_JOUGE;
//			}
		}else{
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
//			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou*3-(rikisidata[higasiid].tatiaigijutu+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2/2+rikisidata[higasiid].kerutikara)
//			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou*3-(rikisidata[nisiid].tatiaigijutu+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2/2+rikisidata[nisiid].kerutikara)){
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
//			if (GetRand(99)<50){
//		   		offense_state_jouge=MIDDLE_STATE_JOUGE;
//				defense_state_jouge=MIDDLE_STATE_JOUGE;
//			}else if(GetRand(99)<50){
//		   		offense_state_jouge=LOW_STATE_JOUGE;
//				defense_state_jouge=MIDDLE_STATE_JOUGE;
//			}else{
//		   		offense_state_jouge=MIDDLE_STATE_JOUGE;
//				defense_state_jouge=HIGH_STATE_JOUGE;
//			}
		}
	    offense_action_zengo=MAE_ACTION_ZENGO ;
	    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  	defense_action_zengo=MAE_ACTION_ZENGO ;
   		defense_action_sayuu=NASI_ACTION_SAYUU ;
	 }else if (higasi_tatiai_power==NORMAL_TATIAI_POWER
	  && nisi_tatiai_power==UKERU_TATIAI_POWER){
		if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2/2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		>GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=2;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2/2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		>GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2/2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=1;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2/2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		>GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2/4+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else{
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}
	    offense_action_zengo=MAE_ACTION_ZENGO ;
	    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  	defense_action_zengo=MAE_ACTION_ZENGO ;
   		defense_action_sayuu=NASI_ACTION_SAYUU ;
	 }else if (higasi_tatiai_power==NORMAL_TATIAI_POWER
	  && nisi_tatiai_power==HENKA_TATIAI_POWER){
		if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
		>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei/2){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=2;
		    offense_action_zengo=MAE_ACTION_ZENGO ;
		    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  		defense_action_zengo=NASI_ACTION_ZENGO ;
	   		defense_action_sayuu=YOKO_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei/2){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=LOW_STATE_JOUGE;
			}
		}else{
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
   			defense_state_balance-=3 ;
		    offense_action_zengo=NASI_ACTION_ZENGO ;
		    offense_action_sayuu=YOKO_ACTION_SAYUU ;
	  		defense_action_zengo=MAE_ACTION_ZENGO ;
	   		defense_action_sayuu=NASI_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei/2
			<GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=LOW_STATE_JOUGE;
			}
		}

	}else if (higasi_tatiai_power==UKERU_TATIAI_POWER
	 && nisi_tatiai_power==ZENRYOKU_TATIAI_POWER){
		if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		<GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=-3;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2/2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		<GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=-2;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2/4+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		<GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=-1;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else{
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}
	    offense_action_zengo=MAE_ACTION_ZENGO ;
	    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  	defense_action_zengo=MAE_ACTION_ZENGO ;
   		defense_action_sayuu=NASI_ACTION_SAYUU ;
	 }else if (higasi_tatiai_power==UKERU_TATIAI_POWER
	  && nisi_tatiai_power==NORMAL_TATIAI_POWER){
		if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		<GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2/2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=-2;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2/2+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		<GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2/2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=-1;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2/4+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		<GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2/2+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else{
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}
	    offense_action_zengo=MAE_ACTION_ZENGO ;
	    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  	defense_action_zengo=MAE_ACTION_ZENGO ;
   		defense_action_sayuu=NASI_ACTION_SAYUU ;
	 }else if (higasi_tatiai_power==UKERU_TATIAI_POWER
	  && nisi_tatiai_power==UKERU_TATIAI_POWER){
		if (GetRand(MAGIRE)+rikisidata[higasiid].taijuu+rikisidata[higasiid].juunansei+rikisidata[higasiid].tossinryoku*2/4+rikisidata[higasiid].kerutikara+rikisidata[higasiid].tatiaigijutu
		>GetRand(MAGIRE)+rikisidata[nisiid].taijuu+rikisidata[nisiid].juunansei+rikisidata[nisiid].tossinryoku*2/4
		+rikisidata[nisiid].kerutikara+rikisidata[nisiid].tatiaigijutu){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=2;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else{
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			if (GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[higasiid].sinchou-rikisidata[higasiid].tatiaigijutu-rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_TATIAI_JOUGE)+rikisidata[nisiid].sinchou-rikisidata[nisiid].tatiaigijutu-rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}
	    offense_action_zengo=MAE_ACTION_ZENGO ;
	    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  	defense_action_zengo=MAE_ACTION_ZENGO ;
   		defense_action_sayuu=NASI_ACTION_SAYUU ;
	 }else if (higasi_tatiai_power==UKERU_TATIAI_POWER
	  && nisi_tatiai_power==HENKA_TATIAI_POWER){
		if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
		>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei/4){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			state_ichi=1;
		    offense_action_zengo=MAE_ACTION_ZENGO ;
		    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  		defense_action_zengo=NASI_ACTION_ZENGO ;
	   		defense_action_sayuu=YOKO_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else{
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
   			defense_state_balance-=1 ;
		    offense_action_zengo=NASI_ACTION_ZENGO ;
		    offense_action_sayuu=YOKO_ACTION_SAYUU ;
	  		defense_action_zengo=MAE_ACTION_ZENGO ;
	   		defense_action_sayuu=NASI_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei/4){
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}

	 }else if (higasi_tatiai_power==HENKA_TATIAI_POWER
	  && nisi_tatiai_power==ZENRYOKU_TATIAI_POWER){
		if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
		>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei/2){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			defense_state_balance-=5;
		    offense_action_zengo=NASI_ACTION_ZENGO ;
		    offense_action_sayuu=YOKO_ACTION_SAYUU ;
	  		defense_action_zengo=MAE_ACTION_ZENGO ;
	   		defense_action_sayuu=NASI_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei/2){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=HIGH_STATE_JOUGE;
				defense_state_jouge=LOW_STATE_JOUGE;
			}
		}else{
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
   			state_ichi=-3 ;
		    offense_action_zengo=MAE_ACTION_ZENGO ;
		    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  		defense_action_zengo=NASI_ACTION_ZENGO ;
	   		defense_action_sayuu=YOKO_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei/2){
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=LOW_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}
		}
	 }else if (higasi_tatiai_power==HENKA_TATIAI_POWER
	  && nisi_tatiai_power==NORMAL_TATIAI_POWER){
		if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei/2
		>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
			defense_state_balance-=3;
		    offense_action_zengo=NASI_ACTION_ZENGO ;
		    offense_action_sayuu=YOKO_ACTION_SAYUU ;
	  		defense_action_zengo=MAE_ACTION_ZENGO ;
	   		defense_action_sayuu=NASI_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei/2
			>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=HIGH_STATE_JOUGE;
				defense_state_jouge=LOW_STATE_JOUGE;
			}
		}else{
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
   			state_ichi=-2 ;
		    offense_action_zengo=MAE_ACTION_ZENGO ;
		    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  		defense_action_zengo=NASI_ACTION_ZENGO ;
	   		defense_action_sayuu=YOKO_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei/2
			>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=LOW_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}
		}
	 }else if (higasi_tatiai_power==HENKA_TATIAI_POWER
	  && nisi_tatiai_power==UKERU_TATIAI_POWER){
		if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei/4
		<GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
		    offense_action_zengo=NASI_ACTION_ZENGO ;
		    offense_action_sayuu=YOKO_ACTION_SAYUU ;
	  		defense_action_zengo=MAE_ACTION_ZENGO ;
	   		defense_action_sayuu=NASI_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
			<GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else{
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
   			state_ichi=-1 ;
			defense_state_balance-=1;
		    offense_action_zengo=MAE_ACTION_ZENGO ;
		    offense_action_sayuu=NASI_ACTION_SAYUU ;
	  		defense_action_zengo=NASI_ACTION_ZENGO ;
	   		defense_action_sayuu=YOKO_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei/4
			<GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=LOW_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}
		}
	 }else if (higasi_tatiai_power==HENKA_TATIAI_POWER
	  && nisi_tatiai_power==HENKA_TATIAI_POWER){
		if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
		>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			kougekiken=1;
			offenseid=higasiid;
			defenseid=nisiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
		    offense_action_zengo=NASI_ACTION_ZENGO ;
		    offense_action_sayuu=YOKO_ACTION_SAYUU ;
	  		defense_action_zengo=NASI_ACTION_ZENGO ;
	   		defense_action_sayuu=YOKO_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}else{
			   	offense_state_jouge=HIGH_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}
		}else{
			kougekiken=2;
			offenseid=nisiid;
			defenseid=higasiid;
		    offense_state_balance=(int)(rikisidata[offenseid].balance/10)+1 ;
		   	defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1 ;
		    offense_action_zengo=NASI_ACTION_ZENGO ;
		    offense_action_sayuu=YOKO_ACTION_SAYUU ;
	  		defense_action_zengo=NASI_ACTION_ZENGO ;
	   		defense_action_sayuu=YOKO_ACTION_SAYUU ;
			if (GetRand(MAGIRE_BINSHOUSEI)+rikisidata[higasiid].binshousei
			>GetRand(MAGIRE_BINSHOUSEI)+rikisidata[nisiid].binshousei){
			   	offense_state_jouge=HIGH_STATE_JOUGE;
				defense_state_jouge=MIDDLE_STATE_JOUGE;
			}else{
			   	offense_state_jouge=MIDDLE_STATE_JOUGE;
				defense_state_jouge=HIGH_STATE_JOUGE;
			}
		}
	 }
	
	///////////////////ＡＩ関連AI関連/////////
	/////////////AIDATA記録/////////////////立ち合い後分
	//kiroku_wazadata(char wazaid,int id1,int id2,char id1_higasiornisi,char tatiaigoflag){//
	//id1側から見ての効果//id1_higasiornisiは1でid1が東力士をあらわす
	//tatiaigoflagが1→立合い直後の記録、0→技ルーチン直後の記録
	//if (offenseid==higasiid){
	//	kiroku_wazadata(wazaid_sentaku,offenseid,defenseid,1,1);
	//}else{
	//	kiroku_wazadata(wazaid_sentaku,offenseid,defenseid,2,1);
	//}
	////////////////////////////////////////

	//負けの判定
	if (state_ichi<-3 || state_ichi>3 || offense_state_balance<1 || defense_state_balance<1){
	}
	if (state_ichi<-3){//東が土俵から出て西の勝ち
		joukendata[higasiid]=joukendata_temp_higasi;
		joukendata[nisiid]=joukendata_temp_nisi;
		joukendata2[higasiid]=joukendata2_temp_higasi;
		joukendata2[nisiid]=joukendata2_temp_nisi;
		return 2;
	}else if (state_ichi>3){//西が土俵から出て東の勝ち
		joukendata[higasiid]=joukendata_temp_higasi;
		joukendata[nisiid]=joukendata_temp_nisi;
		joukendata2[higasiid]=joukendata2_temp_higasi;
		joukendata2[nisiid]=joukendata2_temp_nisi;
		return 1;
	}else if (offense_state_balance<1){//以下相手のバランス崩れて勝ち
		if (offenseid==higasiid){
			joukendata[higasiid]=joukendata_temp_higasi;
			joukendata[nisiid]=joukendata_temp_nisi;
			joukendata2[higasiid]=joukendata2_temp_higasi;
			joukendata2[nisiid]=joukendata2_temp_nisi;
			return 2;
		}else{
			joukendata[higasiid]=joukendata_temp_higasi;
			joukendata[nisiid]=joukendata_temp_nisi;
			joukendata2[higasiid]=joukendata2_temp_higasi;
			joukendata2[nisiid]=joukendata2_temp_nisi;
			return 1;
		}
	}else if (defense_state_balance<1){
		if (defenseid==higasiid){
			joukendata[higasiid]=joukendata_temp_higasi;
			joukendata[nisiid]=joukendata_temp_nisi;
			joukendata2[higasiid]=joukendata2_temp_higasi;
			joukendata2[nisiid]=joukendata2_temp_nisi;
			return 2;
		}else{
			joukendata[higasiid]=joukendata_temp_higasi;
			joukendata[nisiid]=joukendata_temp_nisi;
			joukendata2[higasiid]=joukendata2_temp_higasi;
			joukendata2[nisiid]=joukendata2_temp_nisi;
			return 1;
		}
	}

	//立会いの狙いをオフェンスとディフェンスに代入
	if (kougekiken==1){
		offense_tatiai_nerai=higasi_tatiai_nerai;
		defense_tatiai_nerai=nisi_tatiai_nerai;
	}else{
		offense_tatiai_nerai=nisi_tatiai_nerai;
		defense_tatiai_nerai=higasi_tatiai_nerai;
	}
	//スタミナ代入
	if (kougekiken==1){
		offense_stamina=rikisidata[higasiid].stamina;
		defense_stamina=rikisidata[nisiid].stamina;
	}else{
		offense_stamina=rikisidata[nisiid].stamina;
		defense_stamina=rikisidata[higasiid].stamina;
	}

	//粘りtrycount初期化
	nebaritrycount_higasi=0;
	nebaritrycount_nisi=0;
	//各技のtry数初期化
	for (i=0;i<WAZAPATTERNSUU;i++){
		for (ii=0;ii<5;ii++){
			wazapattern_far_sentakuwazaid_trysuu[i][ii]=0;
			wazapattern_middle_sentakuwazaid_trysuu[i][ii]=0;
			wazapattern_near_sentakuwazaid_trysuu[i][ii]=0;
		}
	}


	//ここからループ////////
	while(1){

		if ( CheckHitKey_test( KEY_INPUT_ESCAPE ) == 1 ){
			//ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			if (skipmode==1 && skipday==99){
				DrawString(187,480-40,"稽古を中断してもよろしいですか",CRGREEN);
				DrawString(75,480-20,"1＞中断、0＞続行、2＞表示切替、ENTERで確定＞",CRGREEN);
			}else{
				DrawString(187,480-40,"スキップモードを中断してもよろしいですか",CRGREEN);
				DrawString(75,480-20,"1＞中断、0＞スキップ続行、2＞表示切替、ENTERで確定＞",CRGREEN);
			}
			ScreenFlip() ;//裏画面を表画面にコピー
			if( ProcessMessage() == -1 ){mode=1;return 0;}
			nyuuryokuti=0;
			nyuuryokuti= KeyInputNumber( 520 , 480-20 , 2 , 0 , FALSE );
			if (nyuuryokuti==1){
				if (skipmode==1 && skipday==99){
					//稽古中断処理
					keikochuudanflag=1;//AIkeikoルーチンを呼び出すところでこのフラグをチェック
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawString(187,369,"稽古中断処理中です…",CRWHITE);
					ScreenFlip() ;//裏画面を表画面にコピー
					if( ProcessMessage() == -1 ){mode=1;return 0;}
				}else{
					skipmode=1;
					skipday=99;
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawString(187,369,"ルンルン休暇からは復帰しますが、AI稽古中です。",CRGREEN);
					DrawString(187,369+16,"稽古も中断するには 1 を",CRGREEN);
					DrawString(187,369+32,"稽古は完結させるには 0 を入力してください",CRGREEN);
					ScreenFlip() ;//裏画面を表画面にコピー
					if( ProcessMessage() == -1 ){mode=1;return 0;}
					nyuuryokuti=0;
					nyuuryokuti= KeyInputNumber( 520 , 480-20 , 2 , 0 , FALSE );
					if (nyuuryokuti==1){
						//稽古中断処理
						keikochuudanflag=1;//AIkeikoルーチンを呼び出すところでこのフラグをチェック
						ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
						DrawString(187,369,"稽古中断処理中です…",CRWHITE);
						ScreenFlip() ;//裏画面を表画面にコピー
						if( ProcessMessage() == -1 ){mode=1;return 0;}
					}else{
						aikeikochuuhyoji();
					}
				}
			}else{
				if (nyuuryokuti==2){
					if (skiphyojimode==0){
						skiphyojimode=1;
						aikeikochuuhyoji();
					}else{
						skiphyojimode=0;
						aikeikochuuhyoji();
					}
				}else{
					aikeikochuuhyoji();
				}
			}
		}

		///////////////
		turncount++;
		wazatrycount=0;
		////////////////

		if (joukendata[offenseid].joukenflag==3){
			////////////////Ver4.00からのAIの技選択/////////////////////////
			yotu=0;
			temp_char=0;
			waza_max=-1;
			wazaid_max=0;
			joutaiflag=0;
			temp_fichi=0;
			bytedata=0;
			makikaedameflag=0;
			for (i=0;i<22;i++){
				waza_sisuu[i]=0;
				waza_sisuu[i]=-1;
			}
			wazaid_max=-1;
			wazaid_sentaku=-1;
			if (state_kyori==FAR_STATE_KYORI || state_kyori==NEAR_STATE_KYORI){//遠距離
				//四つ
				//	0	間合い遠い
				if (state_kyori==FAR_STATE_KYORI){
					yotu=0;
				//	1	右四つ
				}else if ((offense_state_migiude==SITATE_STATE_UDE || offense_state_migiude==SITATETUKAMI_STATE_UDE) 
					&& (offense_state_hidariude==UWATE_STATE_UDE || offense_state_hidariude==UWATETUKAMI_STATE_UDE)){
					yotu=1;
				//	2	左四つ
				}else if ((offense_state_migiude==UWATE_STATE_UDE || offense_state_migiude==UWATETUKAMI_STATE_UDE) 
					&& (offense_state_hidariude==SITATE_STATE_UDE || offense_state_hidariude==SITATETUKAMI_STATE_UDE)){
					yotu=2;
				//	3	両上手
				}else if ((offense_state_migiude==UWATE_STATE_UDE || offense_state_migiude==UWATETUKAMI_STATE_UDE) 
					&& (offense_state_hidariude==UWATE_STATE_UDE || offense_state_hidariude==UWATETUKAMI_STATE_UDE)){
					yotu=3;
				//	4	両差し
				}else if ((offense_state_migiude==SITATE_STATE_UDE || offense_state_migiude==SITATETUKAMI_STATE_UDE) 
					&& (offense_state_hidariude==SITATE_STATE_UDE || offense_state_hidariude==SITATETUKAMI_STATE_UDE)){
					yotu=4;
				}
				//廻し
				jibunmigimawasi=0;
				jibunhidarimawasi=0;
				aitemigimawasi=0;
				aitehidarimawasi=0;
				if (offense_state_migiude==UWATETUKAMI_STATE_UDE || offense_state_migiude==SITATETUKAMI_STATE_UDE){
					jibunmigimawasi=1;
				}
				if (offense_state_hidariude==UWATETUKAMI_STATE_UDE || offense_state_hidariude==SITATETUKAMI_STATE_UDE){
					jibunhidarimawasi=1;
				}
				if (defense_state_migiude==UWATETUKAMI_STATE_UDE || defense_state_migiude==SITATETUKAMI_STATE_UDE){
					aitemigimawasi=1;
				}
				if (defense_state_hidariude==UWATETUKAMI_STATE_UDE || defense_state_hidariude==SITATETUKAMI_STATE_UDE){
					aitehidarimawasi=1;
				}
				//上体の比較
				if (defense_action_zengo==NASI_ACTION_ZENGO
					|| (defense_state_balance<(int)(rikisidata[defenseid].balance/10)+1
							 && defense_state_balance<6)){//前に圧力がかかっていない状態か大きくバランスを崩した状態
					joutaiflag=3;//
				}else if (offense_state_jouge>defense_state_jouge){//自低
					joutaiflag=2;//
				}else if (offense_state_jouge==defense_state_jouge){//自低
					joutaiflag=1;//
				}else{
					joutaiflag=0;//
				}
				//技選択
				while(1){
					//if( ProcessMessage() == -1 ){mode=1;return 0;}
					if (yotu==0){
						startid=GetRand(1)+1;
						break;
					}else{
						startid=GetRand(17)+4;
						if (startid!=9){
							break;
						}
					}
				}
				for (i=0;i<22;i++){
					temp_wazaid=i+startid;
					if (temp_wazaid>21) temp_wazaid-=22;
					//狙いの四つになっていたら巻き替えを狙わないように補正
					//また、狙いの四つになるような巻き替えのみ狙うよう補正
					//tatiaipatternid_higasi,tatiaipatternid_nisi
					//ちなみに上記変数が0~3は立合い突き押し、4~7右四つ、8~11左四つ、12~15両上手、16~19両差し
					makikaedameflag=0;
					if (offenseid==higasiid){
						if ((int)(tatiaipatternid_higasi/4)==yotu){
							if (temp_wazaid>=10 && temp_wazaid<=13){
								makikaedameflag=1;
							}
						}
						if ((int)(tatiaipatternid_higasi/4)==1){
							if (temp_wazaid==10 || temp_wazaid==13){
								makikaedameflag=1;
							}
						}
						if ((int)(tatiaipatternid_higasi/4)==2){
							if (temp_wazaid==11 || temp_wazaid==12){
								makikaedameflag=1;
							}
						}
						if ((int)(tatiaipatternid_higasi/4)==3){
							if (temp_wazaid==12 || temp_wazaid==13){
								makikaedameflag=1;
							}
						}
						if ((int)(tatiaipatternid_higasi/4)==4){
							if (temp_wazaid==10 || temp_wazaid==11){
								makikaedameflag=1;
							}
						}
					}else{
						if ((int)(tatiaipatternid_nisi/4)==yotu){
							if (temp_wazaid>=10 && temp_wazaid<=13){
								makikaedameflag=1;
							}
						}
						if ((int)(tatiaipatternid_nisi/4)==1){
							if (temp_wazaid==10 || temp_wazaid==13){
								makikaedameflag=1;
							}
						}
						if ((int)(tatiaipatternid_nisi/4)==2){
							if (temp_wazaid==11 || temp_wazaid==12){
								makikaedameflag=1;
							}
						}
						if ((int)(tatiaipatternid_nisi/4)==3){
							if (temp_wazaid==12 || temp_wazaid==13){
								makikaedameflag=1;
							}
						}
						if ((int)(tatiaipatternid_nisi/4)==4){
							if (temp_wazaid==10 || temp_wazaid==11){
								makikaedameflag=1;
							}
						}
					}
					if (makikaedameflag==0){
						temp_fichi=aidata_fichi[temp_wazaid][yotu][jibunmigimawasi][jibunhidarimawasi][aitemigimawasi][aitehidarimawasi][joutaiflag];
						if (temp_fichi!=-1){
							if (kobetu_sikiiti[offenseid]<=aikeikosuu[offenseid][defenseid]){
								//力士別個別データから値取り出し
								memcpy(&bytedata, 
									aidata
									+offenseid*RIKISISUU*AIDATABYTESUU
									+defenseid*AIDATABYTESUU
									+(int)(temp_fichi/4),
									sizeof(char));
							}else{
								//トータルデータから値取り出し
								memcpy(&bytedata, 
									aidata
									+offenseid*RIKISISUU*AIDATABYTESUU
									+offenseid*AIDATABYTESUU
									+(int)(temp_fichi/4),
									sizeof(char));
							}
							temp_char=getdatafrombit(bytedata,temp_fichi%4);
							waza_sisuu[temp_wazaid]=temp_char;
							if (waza_max<waza_sisuu[temp_wazaid]){
								waza_max=waza_sisuu[temp_wazaid];
								wazaid_max=temp_wazaid;
							}
						}
					}
				}
				//if( ProcessMessage() == -1 ){mode=1;return 0;}

				wazaid_sentaku=wazaid_max;

				//ランダム選択率適用判断でwazaid_sentakuを上書き
				{
					int i;int kakoday;int temp_wazaid=0;
					int makesuu=0;int katisuu=0;
					int makekosisuu_6basho=0;
					for (i=0;i<6;i++){//0が１場所前、1が２場所前…
						for (kakoday=0;kakoday<15;kakoday++){
							if (rikisidata[offenseid].kako_aitekonbasho[i][kakoday]==defenseid){
								if (rikisidata[offenseid].kako_lostkonbasho[i][kakoday]==1){
									makesuu++;break;
								}
								if (rikisidata[offenseid].kako_winkonbasho[i][kakoday]==1){
									katisuu++;break;
								}
							}
						}
					}
					makekosisuu_6basho=makesuu-katisuu;
					if (makekosisuu_6basho<0) makekosisuu_6basho=0;
					if (GetRand(99)<waza_randomsentakuritu_makekosisuu[makekosisuu_6basho]){
						while(1){
							//if( ProcessMessage() == -1 ){mode=1;return 0;}
							temp_wazaid=GetRand(21);
							//巻き替えは選択しない
							if (temp_wazaid>=10 && temp_wazaid<=13){
								continue;
							}
							//シチュエーション的に無理な技はもちろん選択しない
							if (-1==aidata_fichi[temp_wazaid][yotu][jibunmigimawasi][jibunhidarimawasi][aitemigimawasi][aitehidarimawasi][joutaiflag]){
								continue;
							}
							wazaid_sentaku=temp_wazaid;
							break;
						}
					}
					//if( ProcessMessage() == -1 ){mode=1;return 0;}
				}//ランダム選択率適用判断終わり

			}else{
				wazaid_sentaku=CHUUKANSHORI_WAZA;
			}

			//技効果判断ルーチンへ
			if (wazaid_sentaku!=-1){
				if (state_ichi<-4) state_ichi=-4;
				if (state_ichi>4) state_ichi=4;
				ichi_lastturn=state_ichi;
				if (offenseid==higasiid){
					last_higasi_state_balance=offense_state_balance;
				}else{
					last_nisi_state_balance=offense_state_balance;
				}
				chokuzen();
				if (waza(wazaid_sentaku,higasiid,nisiid)==-1){
					wazaid_sentaku=-1;
				}else{
					/////////////AIDATA記録/////////////////AI作戦
					//kiroku_wazadata(char wazaid,int id1,int id2,char id1_higasiornisi,char tatiaigoflag){//
					//id1側から見ての効果//id1_higasiornisiは1でid1が東力士をあらわす
					//tatiaigoflagが1→立合い直後の記録、0→技ルーチン直後の記録
					if (offenseid==higasiid){
						kiroku_wazadata(wazaid_sentaku,offenseid,defenseid,1,0);
					}else{
						kiroku_wazadata(wazaid_sentaku,offenseid,defenseid,2,0);
					}

					if (state_ichi<-4) state_ichi=-4;
					if (state_ichi>4) state_ichi=4;
				}
			}
			////////////////Ver4.00からのAIの技選択終わり/////////////////////////
		}else if (joukendata[offenseid].joukenflag==0 || joukendata[offenseid].joukenflag==1){
			nowwazatrysuu=0;
			while(1){//優先度の高い技から検討
				if (wazapattern_far_sentakuwazaid_maxtry_higasi[4]<=wazapattern_far_sentakuwazaid_trysuu[1][4]){
					for (i=0;i<5;i++){
						wazapattern_far_sentakuwazaid_trysuu[1][i]=0;
					}
				}
				if (wazapattern_middle_sentakuwazaid_maxtry_higasi[4]<=wazapattern_middle_sentakuwazaid_trysuu[1][4]){
					for (i=0;i<5;i++){
						wazapattern_middle_sentakuwazaid_trysuu[1][i]=0;
					}
				}
				if (wazapattern_near_sentakuwazaid_maxtry_higasi[4]<=wazapattern_near_sentakuwazaid_trysuu[1][4]){
					for (i=0;i<5;i++){
						wazapattern_near_sentakuwazaid_trysuu[1][i]=0;
					}
				}
				if (wazapattern_far_sentakuwazaid_maxtry_nisi[4]<=wazapattern_far_sentakuwazaid_trysuu[2][4]){
					for (i=0;i<5;i++){
						wazapattern_far_sentakuwazaid_trysuu[2][i]=0;
					}
				}
				if (wazapattern_middle_sentakuwazaid_maxtry_nisi[4]<=wazapattern_middle_sentakuwazaid_trysuu[2][4]){
					for (i=0;i<5;i++){
						wazapattern_middle_sentakuwazaid_trysuu[2][i]=0;
					}
				}
				if (wazapattern_near_sentakuwazaid_maxtry_nisi[4]<=wazapattern_near_sentakuwazaid_trysuu[2][4]){
					for (i=0;i<5;i++){
						wazapattern_near_sentakuwazaid_trysuu[2][i]=0;
					}
				}
				if (wazatrycount>4){
					wazatrycount=0;
				}
				if (nowwazatrysuu>4){
					nowwazatrysuu=0;
					break;
				}
				if (kougekiken==1 ){//攻撃権東の場合
					if (state_kyori==FAR_STATE_KYORI){//遠距離
						if (wazapattern_far_sentakuwazaid_maxtry_higasi[wazatrycount]>wazapattern_far_sentakuwazaid_trysuu[1][wazatrycount]){
							wazaid_sentaku=wazapattern_far_sentakuwazaid_higasi[wazatrycount];
							wazapattern_far_sentakuwazaid_trysuu[1][wazatrycount]++;
							nowwazatrysuu++;
						}else{
							wazaid_sentaku=-1;//次優先度の技へ飛ばすフラグ
						}
					}else if(state_kyori==MIDDLE_STATE_KYORI){//中距離
						if (wazapattern_middle_sentakuwazaid_maxtry_higasi[wazatrycount]>wazapattern_middle_sentakuwazaid_trysuu[1][wazatrycount]){
							wazaid_sentaku=wazapattern_middle_sentakuwazaid_higasi[wazatrycount];
							wazapattern_middle_sentakuwazaid_trysuu[1][wazatrycount]++;
							nowwazatrysuu++;
						}else{
							wazaid_sentaku=-1;//次優先度の技へ飛ばすフラグ
						}
					}else{//近距離
						if (wazapattern_near_sentakuwazaid_maxtry_higasi[wazatrycount]>wazapattern_near_sentakuwazaid_trysuu[1][wazatrycount]){
							wazaid_sentaku=wazapattern_near_sentakuwazaid_higasi[wazatrycount];
							wazapattern_near_sentakuwazaid_trysuu[1][wazatrycount]++;
							nowwazatrysuu++;
						}else{
							wazaid_sentaku=-1;//次優先度の技へ飛ばすフラグ
						}
					}
				}else if(kougekiken==2 ){//攻撃権西の場合
					if (state_kyori==FAR_STATE_KYORI){//遠距離
						if (wazapattern_far_sentakuwazaid_maxtry_nisi[wazatrycount]>wazapattern_far_sentakuwazaid_trysuu[2][wazatrycount]){
							wazaid_sentaku=wazapattern_far_sentakuwazaid_nisi[wazatrycount];
							wazapattern_far_sentakuwazaid_trysuu[2][wazatrycount]++;
							nowwazatrysuu++;
						}else{
							wazaid_sentaku=-1;//次優先度の技へ飛ばすフラグ
						}
					}else if(state_kyori==MIDDLE_STATE_KYORI){//中距離
						if (wazapattern_middle_sentakuwazaid_maxtry_nisi[wazatrycount]>wazapattern_middle_sentakuwazaid_trysuu[2][wazatrycount]){
							wazaid_sentaku=wazapattern_middle_sentakuwazaid_nisi[wazatrycount];
							wazapattern_middle_sentakuwazaid_trysuu[2][wazatrycount]++;
							nowwazatrysuu++;
						}else{
							wazaid_sentaku=-1;//次優先度の技へ飛ばすフラグ
						}
					}else{//近距離
						if (wazapattern_near_sentakuwazaid_maxtry_nisi[wazatrycount]>wazapattern_near_sentakuwazaid_trysuu[2][wazatrycount]){
							wazaid_sentaku=wazapattern_near_sentakuwazaid_nisi[wazatrycount];
							wazapattern_near_sentakuwazaid_trysuu[2][wazatrycount]++;
							nowwazatrysuu++;
						}else{
							wazaid_sentaku=-1;//次優先度の技へ飛ばすフラグ
						}
					}
				}

				//距離が中間のときは例外的処理
				if (state_kyori==MIDDLE_STATE_KYORI){
					wazaid_sentaku=CHUUKANSHORI_WAZA;
				}
				//技効果判断ルーチンへ
				if (wazaid_sentaku!=-1){
					if (state_ichi<-4) state_ichi=-4;
					if (state_ichi>4) state_ichi=4;
					ichi_lastturn=state_ichi;
					if (offenseid==higasiid){
						last_higasi_state_balance=offense_state_balance;
					}else{
						last_nisi_state_balance=offense_state_balance;
					}
					chokuzen();
					if (waza(wazaid_sentaku,higasiid,nisiid)!=-1){
						/////////////AIDATA記録/////////////////簡易作戦
						//kiroku_wazadata(char wazaid,int id1,int id2,char id1_higasiornisi,char tatiaigoflag){//
						//id1側から見ての効果//id1_higasiornisiは1でid1が東力士をあらわす
						//tatiaigoflagが1→立合い直後の記録、0→技ルーチン直後の記録
						if (offenseid==higasiid){
							kiroku_wazadata(wazaid_sentaku,offenseid,defenseid,1,0);
						}else{
							kiroku_wazadata(wazaid_sentaku,offenseid,defenseid,2,0);
						}
						if (state_ichi<-4) state_ichi=-4;
						if (state_ichi>4) state_ichi=4;
						break;
					}
				}
				//if( ProcessMessage() == -1 )
				//{
				//	mode=1;
				//	return 0;	// エラーが起きたらループから抜ける
				//}
				wazatrycount++;
			}
		}else if (joukendata[offenseid].joukenflag==2){
			//優先度の高い技から検討
			if (state_kyori==FAR_STATE_KYORI || state_kyori==NEAR_STATE_KYORI){//遠距離
				if (state_kyori==FAR_STATE_KYORI){
					iii=0;
				}else{
					iii=1;
				}
				wazaid_sentaku=-1;
				for (i=0;i<100;i++){
					if (offenseid==higasiid){
						if (joukendata[offenseid].jouken[iii][0][i]==0
						 || (joukendata[offenseid].jouken[iii][0][i]==1 && state_ichi==-3)
						 || (joukendata[offenseid].jouken[iii][0][i]==2 && (state_ichi==-3 || state_ichi==-2))
						 || (joukendata[offenseid].jouken[iii][0][i]==3 && (state_ichi==-1 || state_ichi==0 || state_ichi==1))
						 || (joukendata[offenseid].jouken[iii][0][i]==4 && (state_ichi==3 || state_ichi==2))
						 || (joukendata[offenseid].jouken[iii][0][i]==5 && state_ichi==3)
						 ){
						if (joukendata[offenseid].jouken[iii][1][i]==0
						 || (joukendata[offenseid].jouken[iii][1][i]==1 && offense_state_jouge>defense_state_jouge)
						 || (joukendata[offenseid].jouken[iii][1][i]==2 && (offense_state_jouge>defense_state_jouge || offense_state_jouge==defense_state_jouge))
						 || (joukendata[offenseid].jouken[iii][1][i]==3 && offense_state_jouge==defense_state_jouge)
						 || (joukendata[offenseid].jouken[iii][1][i]==4 && (offense_state_jouge<defense_state_jouge || offense_state_jouge==defense_state_jouge))
						 || (joukendata[offenseid].jouken[iii][1][i]==5 && offense_state_jouge<defense_state_jouge)
						 ){
						if (joukendata[offenseid].jouken[iii][2][i]==0
						 || (joukendata[offenseid].jouken[iii][2][i]==1 && ((offense_state_migiude==SITATE_STATE_UDE || offense_state_migiude==SITATETUKAMI_STATE_UDE) && (offense_state_hidariude==UWATE_STATE_UDE || offense_state_hidariude==UWATETUKAMI_STATE_UDE)))
						 || (joukendata[offenseid].jouken[iii][2][i]==2 && ((offense_state_hidariude==SITATE_STATE_UDE || offense_state_hidariude==SITATETUKAMI_STATE_UDE) && (offense_state_migiude==UWATE_STATE_UDE || offense_state_migiude==UWATETUKAMI_STATE_UDE)))
						 || (joukendata[offenseid].jouken[iii][2][i]==3 && ((offense_state_migiude==UWATE_STATE_UDE || offense_state_migiude==UWATETUKAMI_STATE_UDE) && (offense_state_hidariude==UWATE_STATE_UDE || offense_state_hidariude==UWATETUKAMI_STATE_UDE)))
						 || (joukendata[offenseid].jouken[iii][2][i]==4 && ((offense_state_migiude==SITATE_STATE_UDE || offense_state_migiude==SITATETUKAMI_STATE_UDE) && (offense_state_hidariude==SITATE_STATE_UDE || offense_state_hidariude==SITATETUKAMI_STATE_UDE)))
						 ){
						if (joukendata[offenseid].jouken[iii][3][i]==0
						 || (joukendata[offenseid].jouken[iii][3][i]==1 && offense_state_migiude!=UWATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][3][i]==2 && offense_state_migiude==UWATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][4][i]==0
						 || (joukendata[offenseid].jouken[iii][4][i]==1 && offense_state_hidariude!=UWATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][4][i]==2 && offense_state_hidariude==UWATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][5][i]==0
						 || (joukendata[offenseid].jouken[iii][5][i]==1 && offense_state_migiude!=SITATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][5][i]==2 && offense_state_migiude==SITATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][6][i]==0
						 || (joukendata[offenseid].jouken[iii][6][i]==1 && offense_state_hidariude!=SITATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][6][i]==2 && offense_state_hidariude==SITATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][7][i]==0
						 || (joukendata[offenseid].jouken[iii][7][i]==1 && defense_state_migiude!=UWATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][7][i]==2 && defense_state_migiude==UWATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][8][i]==0
						 || (joukendata[offenseid].jouken[iii][8][i]==1 && defense_state_hidariude!=UWATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][8][i]==2 && defense_state_hidariude==UWATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][9][i]==0
						 || (joukendata[offenseid].jouken[iii][9][i]==1 && defense_state_migiude!=SITATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][9][i]==2 && defense_state_migiude==SITATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][10][i]==0
						 || (joukendata[offenseid].jouken[iii][10][i]==1 && defense_state_hidariude!=SITATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][10][i]==2 && defense_state_hidariude==SITATETUKAMI_STATE_UDE)
						 ){
						 	if (joukendata[offenseid].joukensentakuritu[iii][i]>GetRand(99)){
								if (joukendata2[offenseid].joukenmaxtrysuu[iii][i]>joukentrysuu_higasi[iii][i]
								 || joukendata2[offenseid].joukenmaxtrysuu[iii][i]==0){
									joukentrysuu_higasi[iii][i]++;
									wazaid_sentaku=joukendata[offenseid].joukenwazaid[iii][i];
									break;
								}
							}
						 }}}}}}}}}}}
					}else{//offenseid==nisiidの場合
						if (joukendata[offenseid].jouken[iii][0][i]==0
						 || (joukendata[offenseid].jouken[iii][0][i]==1 && state_ichi==3)
						 || (joukendata[offenseid].jouken[iii][0][i]==2 && (state_ichi==3 || state_ichi==2))
						 || (joukendata[offenseid].jouken[iii][0][i]==3 && (state_ichi==-1 || state_ichi==0 || state_ichi==1))
						 || (joukendata[offenseid].jouken[iii][0][i]==4 && (state_ichi==-3 || state_ichi==-2))
						 || (joukendata[offenseid].jouken[iii][0][i]==5 && state_ichi==-3)
						 ){
						if (joukendata[offenseid].jouken[iii][1][i]==0
						 || (joukendata[offenseid].jouken[iii][1][i]==1 && offense_state_jouge>defense_state_jouge)
						 || (joukendata[offenseid].jouken[iii][1][i]==2 && (offense_state_jouge>defense_state_jouge || offense_state_jouge==defense_state_jouge))
						 || (joukendata[offenseid].jouken[iii][1][i]==3 && offense_state_jouge==defense_state_jouge)
						 || (joukendata[offenseid].jouken[iii][1][i]==4 && (offense_state_jouge<defense_state_jouge || offense_state_jouge==defense_state_jouge))
						 || (joukendata[offenseid].jouken[iii][1][i]==5 && offense_state_jouge<defense_state_jouge)
						 ){
						if (joukendata[offenseid].jouken[iii][2][i]==0
						 || (joukendata[offenseid].jouken[iii][2][i]==1 && ((offense_state_migiude==SITATE_STATE_UDE || offense_state_migiude==SITATETUKAMI_STATE_UDE) && (offense_state_hidariude==UWATE_STATE_UDE || offense_state_hidariude==UWATETUKAMI_STATE_UDE)))
						 || (joukendata[offenseid].jouken[iii][2][i]==2 && ((offense_state_hidariude==SITATE_STATE_UDE || offense_state_hidariude==SITATETUKAMI_STATE_UDE) && (offense_state_migiude==UWATE_STATE_UDE || offense_state_migiude==UWATETUKAMI_STATE_UDE)))
						 || (joukendata[offenseid].jouken[iii][2][i]==3 && ((offense_state_migiude==UWATE_STATE_UDE || offense_state_migiude==UWATETUKAMI_STATE_UDE) && (offense_state_hidariude==UWATE_STATE_UDE || offense_state_hidariude==UWATETUKAMI_STATE_UDE)))
						 || (joukendata[offenseid].jouken[iii][2][i]==4 && ((offense_state_migiude==SITATE_STATE_UDE || offense_state_migiude==SITATETUKAMI_STATE_UDE) && (offense_state_hidariude==SITATE_STATE_UDE || offense_state_hidariude==SITATETUKAMI_STATE_UDE)))
						 ){
						if (joukendata[offenseid].jouken[iii][3][i]==0
						 || (joukendata[offenseid].jouken[iii][3][i]==1 && offense_state_migiude!=UWATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][3][i]==2 && offense_state_migiude==UWATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][4][i]==0
						 || (joukendata[offenseid].jouken[iii][4][i]==1 && offense_state_hidariude!=UWATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][4][i]==2 && offense_state_hidariude==UWATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][5][i]==0
						 || (joukendata[offenseid].jouken[iii][5][i]==1 && offense_state_migiude!=SITATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][5][i]==2 && offense_state_migiude==SITATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][6][i]==0
						 || (joukendata[offenseid].jouken[iii][6][i]==1 && offense_state_hidariude!=SITATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][6][i]==2 && offense_state_hidariude==SITATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][7][i]==0
						 || (joukendata[offenseid].jouken[iii][7][i]==1 && defense_state_migiude!=UWATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][7][i]==2 && defense_state_migiude==UWATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][8][i]==0
						 || (joukendata[offenseid].jouken[iii][8][i]==1 && defense_state_hidariude!=UWATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][8][i]==2 && defense_state_hidariude==UWATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][9][i]==0
						 || (joukendata[offenseid].jouken[iii][9][i]==1 && defense_state_migiude!=SITATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][9][i]==2 && defense_state_migiude==SITATETUKAMI_STATE_UDE)
						 ){
						if (joukendata[offenseid].jouken[iii][10][i]==0
						 || (joukendata[offenseid].jouken[iii][10][i]==1 && defense_state_hidariude!=SITATETUKAMI_STATE_UDE)
						 || (joukendata[offenseid].jouken[iii][10][i]==2 && defense_state_hidariude==SITATETUKAMI_STATE_UDE)
						 ){
						 	if (joukendata[offenseid].joukensentakuritu[iii][i]>GetRand(99)){
								if (joukendata2[offenseid].joukenmaxtrysuu[iii][i]>joukentrysuu_nisi[iii][i]
								 || joukendata2[offenseid].joukenmaxtrysuu[iii][i]==0){
									joukentrysuu_nisi[iii][i]++;
									wazaid_sentaku=joukendata[offenseid].joukenwazaid[iii][i];
									break;
								}
						 	}
						 }}}}}}}}}}}
					}
				}
			}else{
				wazaid_sentaku=CHUUKANSHORI_WAZA;
			}
			//技効果判断ルーチンへ
			if (wazaid_sentaku!=-1){
				if (state_ichi<-4) state_ichi=-4;
				if (state_ichi>4) state_ichi=4;
				ichi_lastturn=state_ichi;
				if (offenseid==higasiid){
					last_higasi_state_balance=offense_state_balance;
				}else{
					last_nisi_state_balance=offense_state_balance;
				}
				chokuzen();
				if (waza(wazaid_sentaku,higasiid,nisiid)==-1){
					wazaid_sentaku=-1;
				}else{
					/////////////AIDATA記録/////////////////詳細作戦
					//kiroku_wazadata(char wazaid,int id1,int id2,char id1_higasiornisi,char tatiaigoflag){//
					//id1側から見ての効果//id1_higasiornisiは1でid1が東力士をあらわす
					//tatiaigoflagが1→立合い直後の記録、0→技ルーチン直後の記録
					if (offenseid==higasiid){
						kiroku_wazadata(wazaid_sentaku,offenseid,defenseid,1,0);
					}else{
						kiroku_wazadata(wazaid_sentaku,offenseid,defenseid,2,0);
					}
					if (state_ichi<-4) state_ichi=-4;
					if (state_ichi>4) state_ichi=4;
				}
			}
		}

		//イレギュラー処理したければここにいれればよい

		//足運び判定
		if (state_ichi<-3 
		&& offense_state_migiude!=UWATETUKAMI_STATE_UDE 
		&& offense_state_migiude!=SITATETUKAMI_STATE_UDE 
		&& offense_state_hidariude!=UWATETUKAMI_STATE_UDE 
		&& offense_state_hidariude!=SITATETUKAMI_STATE_UDE
		){
			//if (rikisidata[nisiid].binshousei<rikisidata[higasiid].binshousei
			//&& rikisidata[nisiid].asihakobi+100 <GetRand(200)
			//&& GetRand(99) < 33 ){
			if ((rikisidata[nisiid].asihakobi<50 && rikisidata[nisiid].asihakobi<GetRand(100) && rikisidata[nisiid].asihakobi<GetRand(100) && GetRand(sisuu_ashi_gyakuten)<50)
			 || (rikisidata[nisiid].asihakobi>=50 && rikisidata[nisiid].asihakobi<60 && GetRand(sisuu_ashi_gyakuten)<10)
			 || (rikisidata[nisiid].asihakobi>=60 && rikisidata[nisiid].asihakobi<70 && GetRand(sisuu_ashi_gyakuten)<9)
			 || (rikisidata[nisiid].asihakobi>=70 && rikisidata[nisiid].asihakobi<80 && GetRand(sisuu_ashi_gyakuten)<7)
			 || (rikisidata[nisiid].asihakobi>=80 && rikisidata[nisiid].asihakobi<90 && GetRand(sisuu_ashi_gyakuten)<5)
			 || (rikisidata[nisiid].asihakobi>=90 && rikisidata[nisiid].asihakobi<95 && GetRand(sisuu_ashi_gyakuten)<3)
			 || (rikisidata[nisiid].asihakobi>=95 && rikisidata[nisiid].asihakobi<98 && GetRand(sisuu_ashi_gyakuten)<2)
			 || (rikisidata[nisiid].asihakobi>=98 && GetRand(sisuu_ashi_gyakuten)<1)
			 ){
				if (
				(defense_state_migiude==UWATETUKAMI_STATE_UDE || defense_state_migiude==SITATETUKAMI_STATE_UDE)
				&&
				(defense_state_hidariude==UWATETUKAMI_STATE_UDE || defense_state_hidariude==SITATETUKAMI_STATE_UDE)
				){
					if (GetRand(1)==0){
						if (defense_state_migiude==UWATETUKAMI_STATE_UDE){
							defense_state_migiude=UWATE_STATE_UDE;
						}else{
							defense_state_migiude=SITATE_STATE_UDE;
						}
					}else{
						if (defense_state_hidariude==UWATETUKAMI_STATE_UDE){
							defense_state_hidariude=UWATE_STATE_UDE;
						}else{
							defense_state_hidariude=SITATE_STATE_UDE;
						}
					}
				}
				state_ichi=-3;
				offense_state_balance=-1;
			}
		}else if (state_ichi>3 
		&& offense_state_migiude!=UWATETUKAMI_STATE_UDE 
		&& offense_state_migiude!=SITATETUKAMI_STATE_UDE 
		&& offense_state_hidariude!=UWATETUKAMI_STATE_UDE 
		&& offense_state_hidariude!=SITATETUKAMI_STATE_UDE
		){
			//if (rikisidata[higasiid].binshousei<rikisidata[nisiid].binshousei
			//&& rikisidata[higasiid].asihakobi+100 <GetRand(200)
			//&& GetRand(99) < 33 ){
			if ((rikisidata[higasiid].asihakobi<50 && rikisidata[higasiid].asihakobi<GetRand(100) && rikisidata[higasiid].asihakobi<GetRand(100) && GetRand(sisuu_ashi_gyakuten)<50)
			 || (rikisidata[higasiid].asihakobi>=50 && rikisidata[higasiid].asihakobi<60 && GetRand(sisuu_ashi_gyakuten)<10)
			 || (rikisidata[higasiid].asihakobi>=60 && rikisidata[higasiid].asihakobi<70 && GetRand(sisuu_ashi_gyakuten)<9)
			 || (rikisidata[higasiid].asihakobi>=70 && rikisidata[higasiid].asihakobi<80 && GetRand(sisuu_ashi_gyakuten)<7)
			 || (rikisidata[higasiid].asihakobi>=80 && rikisidata[higasiid].asihakobi<90 && GetRand(sisuu_ashi_gyakuten)<5)
			 || (rikisidata[higasiid].asihakobi>=90 && rikisidata[higasiid].asihakobi<95 && GetRand(sisuu_ashi_gyakuten)<3)
			 || (rikisidata[higasiid].asihakobi>=95 && rikisidata[higasiid].asihakobi<98 && GetRand(sisuu_ashi_gyakuten)<2)
			 || (rikisidata[higasiid].asihakobi>=98 && GetRand(sisuu_ashi_gyakuten)<1)
			 ){
				if (
				(defense_state_migiude==UWATETUKAMI_STATE_UDE || defense_state_migiude==SITATETUKAMI_STATE_UDE)
				&&
				(defense_state_hidariude==UWATETUKAMI_STATE_UDE || defense_state_hidariude==SITATETUKAMI_STATE_UDE)
				){
					if (GetRand(1)==0){
						if (defense_state_migiude==UWATETUKAMI_STATE_UDE){
							defense_state_migiude=UWATE_STATE_UDE;
						}else{
							defense_state_migiude=SITATE_STATE_UDE;
						}
					}else{
						if (defense_state_hidariude==UWATETUKAMI_STATE_UDE){
							defense_state_hidariude=UWATE_STATE_UDE;
						}else{
							defense_state_hidariude=SITATE_STATE_UDE;
						}
					}
				}
				state_ichi=3;
				offense_state_balance=-1;
			}
		}
		//土俵際粘り判定
		if (state_kyori==NEAR_STATE_KYORI){
			if (state_ichi<-3){
				if (nebaritrycount_higasi==0){
					if (rikisidata[higasiid].taijuu<rikisidata[nisiid].taijuu){
						nebari_loss=rikisidata[nisiid].taijuu-rikisidata[higasiid].taijuu;
					}else{
						nebari_loss=0;
					}
					if (rikisidata[higasiid].nebari>GetRand(100+nebari_loss)){
						state_ichi=-3;
						nebaritrycount_higasi++;
					}
				}else if(nebaritrycount_higasi==1){
					if (rikisidata[higasiid].taijuu<rikisidata[nisiid].taijuu){
						nebari_loss=rikisidata[nisiid].taijuu-rikisidata[higasiid].taijuu;
					}else{
						nebari_loss=0;
					}
					if (rikisidata[higasiid].nebari>GetRand(150+nebari_loss)){
						state_ichi=-3;
						nebaritrycount_higasi++;
					}
				}else if(nebaritrycount_higasi>=2){
					if (rikisidata[higasiid].taijuu<rikisidata[nisiid].taijuu){
						nebari_loss=rikisidata[nisiid].taijuu-rikisidata[higasiid].taijuu;
					}else{
						nebari_loss=0;
					}
					if (rikisidata[higasiid].nebari>GetRand(200+nebari_loss)){
						//state_ichi=-3;
						nebaritrycount_higasi++;
						//粘った方は低い体勢になり、土俵中央へ、バランスも直す
						state_ichi=0;
						defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1;
						defense_state_jouge=LOW_STATE_JOUGE;
					}
				}
			}else if (state_ichi>3){
				if (nebaritrycount_nisi==0){
					if (rikisidata[nisiid].taijuu<rikisidata[higasiid].taijuu){
						nebari_loss=rikisidata[higasiid].taijuu-rikisidata[nisiid].taijuu;
					}else{
						nebari_loss=0;
					}
					if (rikisidata[nisiid].nebari>GetRand(100+nebari_loss)){
						state_ichi=3;
						nebaritrycount_nisi++;
					}
				}else if(nebaritrycount_nisi==1){
					if (rikisidata[nisiid].taijuu<rikisidata[higasiid].taijuu){
						nebari_loss=rikisidata[higasiid].taijuu-rikisidata[nisiid].taijuu;
					}else{
						nebari_loss=0;
					}

					if (rikisidata[nisiid].nebari>GetRand(150+nebari_loss)){
						state_ichi=3;
						nebaritrycount_nisi++;
					}
				}else if(nebaritrycount_nisi>=2){
					if (rikisidata[nisiid].taijuu<rikisidata[higasiid].taijuu){
						nebari_loss=rikisidata[higasiid].taijuu-rikisidata[nisiid].taijuu;
					}else{
						nebari_loss=0;
					}
					if (rikisidata[nisiid].nebari>GetRand(200+nebari_loss)){
						//state_ichi=3;
						nebaritrycount_nisi++;
						//粘った方は低い体勢になり、土俵中央へ、バランスも直す
						state_ichi=0;
						defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1;
						defense_state_jouge=LOW_STATE_JOUGE;
					}
				}
			}
		}else if(state_kyori==FAR_STATE_KYORI){
			if (state_ichi<-3 && GetRand(rikisidata[higasiid].binshousei)>GetRand(rikisidata[nisiid].binshousei)){
				if (GetRand(rikisidata[higasiid].binshousei*5)>GetRand(rikisidata[nisiid].binshousei*sisuu_binshou_gyakuten)){
					state_ichi=-3;
					offense_state_balance=-1;
				}else if (GetRand(rikisidata[higasiid].binshousei*10)>GetRand(rikisidata[nisiid].binshousei*sisuu_binshou_mawarikomi)){
					state_ichi=-2;
				}
			}else if (state_ichi>3 && GetRand(rikisidata[higasiid].binshousei)<GetRand(rikisidata[nisiid].binshousei)){
				if (GetRand(rikisidata[higasiid].binshousei*sisuu_binshou_gyakuten)<GetRand(rikisidata[nisiid].binshousei*5)){
					state_ichi=3;
					offense_state_balance=-1;
				}else if (GetRand(rikisidata[higasiid].binshousei*sisuu_binshou_mawarikomi)<GetRand(rikisidata[nisiid].binshousei*10)){
					state_ichi=2;
				}

			}
		}
				
		//負けの判定
		if (state_ichi<-3){//東が土俵から出て西の勝ち
			joukendata[higasiid]=joukendata_temp_higasi;
			joukendata[nisiid]=joukendata_temp_nisi;
			joukendata2[higasiid]=joukendata2_temp_higasi;
			joukendata2[nisiid]=joukendata2_temp_nisi;
			return 2;
		}else if (state_ichi>3){//西が土俵から出て東の勝ち
			joukendata[higasiid]=joukendata_temp_higasi;
			joukendata[nisiid]=joukendata_temp_nisi;
			joukendata2[higasiid]=joukendata2_temp_higasi;
			joukendata2[nisiid]=joukendata2_temp_nisi;
			return 1;
		}else if (offense_state_balance<1){//以下相手のバランス崩れて勝ち
			if (offenseid==higasiid){
				joukendata[higasiid]=joukendata_temp_higasi;
				joukendata[nisiid]=joukendata_temp_nisi;
				joukendata2[higasiid]=joukendata2_temp_higasi;
				joukendata2[nisiid]=joukendata2_temp_nisi;
				return 2;
			}else{
				joukendata[higasiid]=joukendata_temp_higasi;
				joukendata[nisiid]=joukendata_temp_nisi;
				joukendata2[higasiid]=joukendata2_temp_higasi;
				joukendata2[nisiid]=joukendata2_temp_nisi;
				return 1;
			}
		}else if (defense_state_balance<1){
			if (defenseid==higasiid){
				joukendata[higasiid]=joukendata_temp_higasi;
				joukendata[nisiid]=joukendata_temp_nisi;
				joukendata2[higasiid]=joukendata2_temp_higasi;
				joukendata2[nisiid]=joukendata2_temp_nisi;
				return 2;
			}else{
				joukendata[higasiid]=joukendata_temp_higasi;
				joukendata[nisiid]=joukendata_temp_nisi;
				joukendata2[higasiid]=joukendata2_temp_higasi;
				joukendata2[nisiid]=joukendata2_temp_nisi;
				return 1;
			}
		}

		//バランスが大きく崩れているときは圧力が前にかからなくなる処理
		if (defense_state_balance<(int)(rikisidata[defenseid].balance/10)+1
		 && defense_state_balance<6){
	  		defense_action_zengo=NASI_ACTION_ZENGO ;//圧力も前にかからなくなる
		 }
		if (offense_state_balance<(int)(rikisidata[offenseid].balance/10)+1
		 && offense_state_balance<6){
	  		offense_action_zengo=NASI_ACTION_ZENGO ;//圧力も前にかからなくなる
		 }
		
		//突きのときの相手の上体を起こせるかどうかの処理
		//相手の根性次第
		if (wazaid_sentaku==TUKI_WAZA){
			if (defense_state_jouge!=HIGH_STATE_JOUGE){
				if (rikisidata[defenseid].konjou<GetRand(100)){
					defense_state_jouge-=1;
				}
			}
		}
		
		//スタミナマイナス処理
		offense_stamina-=GetRand(((int)(rikisidata[offenseid].taijuu/30)))+1;
		defense_stamina-=GetRand(((int)(rikisidata[defenseid].taijuu/60)))+1;
		//守備側のバランスが崩れている場合の処理
		if (defense_state_balance<(int)(rikisidata[defenseid].balance/10)+1){
			balancenaosi=rikisidata[defenseid].balance-GetRand(100);
			if (balancenaosi>0){//バランスがよければ回復
				defense_state_balance+=(int)(balancenaosi/10)+1;
				if (defense_state_balance>(int)(rikisidata[defenseid].balance/10)+1){
					defense_state_balance=(int)(rikisidata[defenseid].balance/10)+1;
				}
			}
		}
		//両者立合い突き押し狙いなのに、あてがいを選択した場合、中間処理で「また突き放した」と返される
		//永遠に相手に攻撃のターンが回ってこないので、それを回避するため
		//技なしにして相手に攻撃のターンをまわす処理
		//相手の動きについていけないことにした
		/*if (matatukihanasitaflag==1){
			//データ入れ替え
			dataexchange();
			//攻撃権チェンジ
			if (kougekiken==1){
				kougekiken=2;
				offenseid=nisiid;
				defenseid=higasiid;
			}else{
				kougekiken=1;
				offenseid=higasiid;
				defenseid=nisiid;
			}
			waza(NASI_WAZA,higasiid,nisiid);
			matatukihanasitaflag=0;
			//データ入れ替え
			dataexchange();
			//攻撃権チェンジ
			if (kougekiken==1){
				kougekiken=2;
				offenseid=nisiid;
				defenseid=higasiid;
			}else{
				kougekiken=1;
				offenseid=higasiid;
				defenseid=nisiid;
			}*/
		//守備側が大きくバランスを崩された場合の連続攻撃を受ける処理
		if (defense_state_balance<(int)(rikisidata[defenseid].balance/10)+1
		 && defense_state_balance<6){
			//データ入れ替え
			dataexchange();
			//攻撃権チェンジ
			if (kougekiken==1){
				kougekiken=2;
				offenseid=nisiid;
				defenseid=higasiid;
			}else{
				kougekiken=1;
				offenseid=higasiid;
				defenseid=nisiid;
			}
			waza(NASI_WAZA,higasiid,nisiid);
			//データ入れ替え
			dataexchange();
			//攻撃権チェンジ
			if (kougekiken==1){
				kougekiken=2;
				offenseid=nisiid;
				defenseid=higasiid;
			}else{
				kougekiken=1;
				offenseid=higasiid;
				defenseid=nisiid;
			}
		//守備側の敏捷性が低い場合は、技なしにして攻守交代なしの処理
		}else if (rikisidata[offenseid].binshousei>rikisidata[defenseid].binshousei
		 && rikisidata[offenseid].binshousei-rikisidata[defenseid].binshousei>GetRand(150)
		 && state_kyori!=MIDDLE_STATE_KYORI){
			//力士画像の変更用フラグ、1＞東を変更、2＞西を変更
			//データ入れ替え
			dataexchange();
			//攻撃権チェンジ
			if (kougekiken==1){
				kougekiken=2;
				offenseid=nisiid;
				defenseid=higasiid;
			}else{
				kougekiken=1;
				offenseid=higasiid;
				defenseid=nisiid;
			}
			waza(NASI_WAZA,higasiid,nisiid);
			//データ入れ替え
			dataexchange();
			//攻撃権チェンジ
			if (kougekiken==1){
				kougekiken=2;
				offenseid=nisiid;
				defenseid=higasiid;
			}else{
				kougekiken=1;
				offenseid=higasiid;
				defenseid=nisiid;
			}
		//守備側の積極性が低い場合は、現状維持という技で攻守交替(土俵際に追い込まれているときは除く)
		}else if (rikisidata[defenseid].sekkyokusei+200<GetRand(300)
		 && state_kyori!=MIDDLE_STATE_KYORI
		 && rikisidata[defenseid].realmodeflag!=1){//リアルモードの時は自分で操るから積極性は関係ない
			if (defenseid==higasiid){
				if (state_ichi>-2){
					//データ入れ替え
					dataexchange();
					//攻撃権チェンジ
					if (kougekiken==1){
						kougekiken=2;
						offenseid=nisiid;
						defenseid=higasiid;
					}else{
						kougekiken=1;
						offenseid=higasiid;
						defenseid=nisiid;
					}
					waza(GENJOUIJI_WAZA,higasiid,nisiid);
					//データ入れ替え
					dataexchange();
					//攻撃権チェンジ
					if (kougekiken==1){
						kougekiken=2;
						offenseid=nisiid;
						defenseid=higasiid;
					}else{
						kougekiken=1;
						offenseid=higasiid;
						defenseid=nisiid;
					}
				}else{
					//通常の攻守交替
					//データ入れ替え
					dataexchange();
					//攻撃権チェンジ
					if (kougekiken==1){
						kougekiken=2;
						offenseid=nisiid;
						defenseid=higasiid;
					}else{
						kougekiken=1;
						offenseid=higasiid;
						defenseid=nisiid;
					}
				}
			}else{
				if (state_ichi<2){
					//データ入れ替え
					dataexchange();
					//攻撃権チェンジ
					if (kougekiken==1){
						kougekiken=2;
						offenseid=nisiid;
						defenseid=higasiid;
					}else{
						kougekiken=1;
						offenseid=higasiid;
						defenseid=nisiid;
					}
					waza(GENJOUIJI_WAZA,higasiid,nisiid);
					//データ入れ替え
					dataexchange();
					//攻撃権チェンジ
					if (kougekiken==1){
						kougekiken=2;
						offenseid=nisiid;
						defenseid=higasiid;
					}else{
						kougekiken=1;
						offenseid=higasiid;
						defenseid=nisiid;
					}
				}else{
					//通常の攻守交替
					//データ入れ替え
					dataexchange();
					//攻撃権チェンジ
					if (kougekiken==1){
						kougekiken=2;
						offenseid=nisiid;
						defenseid=higasiid;
					}else{
						kougekiken=1;
						offenseid=higasiid;
						defenseid=nisiid;
					}
				}
			}
		}else{
			//通常の攻守交替
			//データ入れ替え
			dataexchange();
			//攻撃権チェンジ
			if (kougekiken==1){
				kougekiken=2;
				offenseid=nisiid;
				defenseid=higasiid;
			}else{
				kougekiken=1;
				offenseid=higasiid;
				defenseid=nisiid;
			}
		}

		//スタミナ切れ処理
		if (defense_stamina<0){
			rikisidata[defenseid].kerutikara=(int)(rikisidata[defenseid].kerutikara/2)+1;
			defense_state_jouge=HIGH_STATE_JOUGE;
			if (defense_action_zengo==MAE_ACTION_ZENGO){
				defense_action_zengo=NASI_ACTION_ZENGO;
			}
			defense_action_sayuu=NASI_ACTION_SAYUU;
		}
		if (offense_stamina<0){
			rikisidata[offenseid].kerutikara=(int)(rikisidata[offenseid].kerutikara/2)+1;
			offense_state_jouge=HIGH_STATE_JOUGE;
			if (offense_action_zengo==MAE_ACTION_ZENGO){
				offense_action_zengo=NASI_ACTION_ZENGO;
			}
			offense_action_sayuu=NASI_ACTION_SAYUU;
		}
		if (defense_stamina<-5){
			defense_state_balance=0;
			if (defenseid==higasiid){
				joukendata[higasiid]=joukendata_temp_higasi;
				joukendata[nisiid]=joukendata_temp_nisi;
				joukendata2[higasiid]=joukendata2_temp_higasi;
				joukendata2[nisiid]=joukendata2_temp_nisi;
				return 2;
			}else{
				joukendata[higasiid]=joukendata_temp_higasi;
				joukendata[nisiid]=joukendata_temp_nisi;
				joukendata2[higasiid]=joukendata2_temp_higasi;
				joukendata2[nisiid]=joukendata2_temp_nisi;
				return 1;
			}
		}else if (offense_stamina<-5){
			offense_state_balance=0;
			if (offenseid==higasiid){
				joukendata[higasiid]=joukendata_temp_higasi;
				joukendata[nisiid]=joukendata_temp_nisi;
				joukendata2[higasiid]=joukendata2_temp_higasi;
				joukendata2[nisiid]=joukendata2_temp_nisi;
				return 2;
			}else{
				joukendata[higasiid]=joukendata_temp_higasi;
				joukendata[nisiid]=joukendata_temp_nisi;
				joukendata2[higasiid]=joukendata2_temp_higasi;
				joukendata2[nisiid]=joukendata2_temp_nisi;
				return 1;
			}
		}

		//Sleep(1);
		
		//if( ProcessMessage() == -1 )
		//{
		//	mode=1;
		//	return 0;	// エラーが起きたらループから抜ける
		//}
	}
	
}

void aikeikochuuhyoji(void)
{
	int i,ii;
	int temp_year_saitashou=0;
	int temp_nenkansaitashourisuu=0;
	char temp_namestring_saitashou[12];
	int temp_age_saitashou=0;
	char temp_heyastring_saitashou[12];
	char temp_nenkansaitashourikisihokanimoiruyoflag=0;

	if (year==1 && month==1 && day-11==0) return;

	FILE *fp;

	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	if (skipmode==1 && skipday==99){
		DrawFormatString(5,462,GetColor(90,90,90),"ESCで中断   AIが稽古中、現在%d年%d月 %d日目",year,month,day-11+1);
	}else if (skipday>=0 && skipday!=99){
		DrawFormatString(5,462,GetColor(90,90,90),"ESCで中断   %d日目までスキップ中、現在%d日目",skipday+1,day-11+1);
	}else{
		DrawFormatString(5,462,GetColor(90,90,90),"ESCで中断   %d年%d月までスキップ中、現在%d年%d月 %d日目",skipyear,skipmonth,year,month,day-11+1);
	}
	DrawString(570,0,"AI稽古中",CRPURPLE);
	if (day-11==0){
		if (month<3){
			DrawFormatString(20,5,CRWHITE,"先場所(%d年%s場所)の結果(ゲーム再開直後は正しく表示できません)",year-1,normal_bashostring[5]);
		}else{
			DrawFormatString(20,5,CRWHITE,"先場所(%d年%s場所)の結果(ゲーム再開直後は正しく表示できません)",year,normal_bashostring[(int)((month-2)/2)]);
		}
		if (yuushourikisikonbasho>=0 && yuushourikisikonbasho<RIKISISUU){
			if (rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[yuushourikisikonbasho].kako_bandukesuuji[0]==1){
				if ( (rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0])<15){
					DrawFormatString(10,30,CRWHITE,"幕内最高優勝　%s筆頭 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],15-(rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
				}else{
					DrawFormatString(10,30,CRWHITE,"幕内最高優勝　%s筆頭 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
				}
			}else if (rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[yuushourikisikonbasho].kako_bandukesuuji[0]!=1){
				if ( (rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0])<15){
					DrawFormatString(10,30,CRWHITE,"幕内最高優勝　%s%d枚目 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],rikisidata[yuushourikisikonbasho].kako_bandukesuuji[0],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],15-(rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
				}else{
					DrawFormatString(10,30,CRWHITE,"幕内最高優勝　%s%d枚目 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],rikisidata[yuushourikisikonbasho].kako_bandukesuuji[0],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
				}
			}else{
				if ( (rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0])<15){
					DrawFormatString(10,30,CRWHITE,"幕内最高優勝　%s %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],15-(rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
				}else{
					DrawFormatString(10,30,CRWHITE,"幕内最高優勝　%s %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
				}
			}
		}
		if (shukunshourikisikonbasho>=0 && shukunshourikisikonbasho<RIKISISUU){
			if (rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[shukunshourikisikonbasho].kako_bandukesuuji[0]==1){
				if ( (rikisidata[shukunshourikisikonbasho].kako_win[0]+rikisidata[shukunshourikisikonbasho].kako_lost[0])<15){
					DrawFormatString(10,60,CRWHITE,"殊勲賞　%s筆頭 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]],namestring[shukunshourikisikonbasho],rikisidata[shukunshourikisikonbasho].age,rikisidata[shukunshourikisikonbasho].kako_win[0],rikisidata[shukunshourikisikonbasho].kako_lost[0],15-(rikisidata[shukunshourikisikonbasho].kako_win[0]+rikisidata[shukunshourikisikonbasho].kako_lost[0]),heyastring[rikisidata[shukunshourikisikonbasho].heyaid],rikisidata[shukunshourikisikonbasho].shukunshousuu);
				}else{
					DrawFormatString(10,60,CRWHITE,"殊勲賞　%s筆頭 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]],namestring[shukunshourikisikonbasho],rikisidata[shukunshourikisikonbasho].age,rikisidata[shukunshourikisikonbasho].kako_win[0],rikisidata[shukunshourikisikonbasho].kako_lost[0],heyastring[rikisidata[shukunshourikisikonbasho].heyaid],rikisidata[shukunshourikisikonbasho].shukunshousuu);
				}
			}else if (rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[shukunshourikisikonbasho].kako_bandukesuuji[0]!=1){
				if ( (rikisidata[shukunshourikisikonbasho].kako_win[0]+rikisidata[shukunshourikisikonbasho].kako_lost[0])<15){
					DrawFormatString(10,60,CRWHITE,"殊勲賞　%s%d枚目 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]],rikisidata[shukunshourikisikonbasho].kako_bandukesuuji[0],namestring[shukunshourikisikonbasho],rikisidata[shukunshourikisikonbasho].age,rikisidata[shukunshourikisikonbasho].kako_win[0],rikisidata[shukunshourikisikonbasho].kako_lost[0],15-(rikisidata[shukunshourikisikonbasho].kako_win[0]+rikisidata[shukunshourikisikonbasho].kako_lost[0]),heyastring[rikisidata[shukunshourikisikonbasho].heyaid],rikisidata[shukunshourikisikonbasho].shukunshousuu);
				}else{
					DrawFormatString(10,60,CRWHITE,"殊勲賞　%s%d枚目 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]],rikisidata[shukunshourikisikonbasho].kako_bandukesuuji[0],namestring[shukunshourikisikonbasho],rikisidata[shukunshourikisikonbasho].age,rikisidata[shukunshourikisikonbasho].kako_win[0],rikisidata[shukunshourikisikonbasho].kako_lost[0],heyastring[rikisidata[shukunshourikisikonbasho].heyaid],rikisidata[shukunshourikisikonbasho].shukunshousuu);
				}
			}else{
				if ( (rikisidata[shukunshourikisikonbasho].kako_win[0]+rikisidata[shukunshourikisikonbasho].kako_lost[0])<15){
					DrawFormatString(10,60,CRWHITE,"殊勲賞　%s %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]],namestring[shukunshourikisikonbasho],rikisidata[shukunshourikisikonbasho].age,rikisidata[shukunshourikisikonbasho].kako_win[0],rikisidata[shukunshourikisikonbasho].kako_lost[0],15-(rikisidata[shukunshourikisikonbasho].kako_win[0]+rikisidata[shukunshourikisikonbasho].kako_lost[0]),heyastring[rikisidata[shukunshourikisikonbasho].heyaid],rikisidata[shukunshourikisikonbasho].shukunshousuu);
				}else{
					DrawFormatString(10,60,CRWHITE,"殊勲賞　%s %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]],namestring[shukunshourikisikonbasho],rikisidata[shukunshourikisikonbasho].age,rikisidata[shukunshourikisikonbasho].kako_win[0],rikisidata[shukunshourikisikonbasho].kako_lost[0],heyastring[rikisidata[shukunshourikisikonbasho].heyaid],rikisidata[shukunshourikisikonbasho].shukunshousuu);
				}
			}
		}else{
			DrawString(10,60,"殊勲賞　該当なし",CRWHITE);
		}
		if (kantoushourikisikonbasho>=0 && kantoushourikisikonbasho<RIKISISUU){
			if (rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[kantoushourikisikonbasho].kako_bandukesuuji[0]==1){
				if ( (rikisidata[kantoushourikisikonbasho].kako_win[0]+rikisidata[kantoushourikisikonbasho].kako_lost[0])<15){
					DrawFormatString(10,80,CRWHITE,"敢闘賞　%s筆頭 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]],namestring[kantoushourikisikonbasho],rikisidata[kantoushourikisikonbasho].age,rikisidata[kantoushourikisikonbasho].kako_win[0],rikisidata[kantoushourikisikonbasho].kako_lost[0],15-(rikisidata[kantoushourikisikonbasho].kako_win[0]+rikisidata[kantoushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[kantoushourikisikonbasho].heyaid],rikisidata[kantoushourikisikonbasho].kantoushousuu);
				}else{
					DrawFormatString(10,80,CRWHITE,"敢闘賞　%s筆頭 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]],namestring[kantoushourikisikonbasho],rikisidata[kantoushourikisikonbasho].age,rikisidata[kantoushourikisikonbasho].kako_win[0],rikisidata[kantoushourikisikonbasho].kako_lost[0],heyastring[rikisidata[kantoushourikisikonbasho].heyaid],rikisidata[kantoushourikisikonbasho].kantoushousuu);
				}
			}else if (rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[kantoushourikisikonbasho].kako_bandukesuuji[0]!=1){
				if ( (rikisidata[kantoushourikisikonbasho].kako_win[0]+rikisidata[kantoushourikisikonbasho].kako_lost[0])<15){
					DrawFormatString(10,80,CRWHITE,"敢闘賞　%s%d枚目 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]],rikisidata[kantoushourikisikonbasho].kako_bandukesuuji[0],namestring[kantoushourikisikonbasho],rikisidata[kantoushourikisikonbasho].age,rikisidata[kantoushourikisikonbasho].kako_win[0],rikisidata[kantoushourikisikonbasho].kako_lost[0],15-(rikisidata[kantoushourikisikonbasho].kako_win[0]+rikisidata[kantoushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[kantoushourikisikonbasho].heyaid],rikisidata[kantoushourikisikonbasho].kantoushousuu);
				}else{
					DrawFormatString(10,80,CRWHITE,"敢闘賞　%s%d枚目 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]],rikisidata[kantoushourikisikonbasho].kako_bandukesuuji[0],namestring[kantoushourikisikonbasho],rikisidata[kantoushourikisikonbasho].age,rikisidata[kantoushourikisikonbasho].kako_win[0],rikisidata[kantoushourikisikonbasho].kako_lost[0],heyastring[rikisidata[kantoushourikisikonbasho].heyaid],rikisidata[kantoushourikisikonbasho].kantoushousuu);
				}
			}else{
				if ( (rikisidata[kantoushourikisikonbasho].kako_win[0]+rikisidata[kantoushourikisikonbasho].kako_lost[0])<15){
					DrawFormatString(10,80,CRWHITE,"敢闘賞　%s %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]],namestring[kantoushourikisikonbasho],rikisidata[kantoushourikisikonbasho].age,rikisidata[kantoushourikisikonbasho].kako_win[0],rikisidata[kantoushourikisikonbasho].kako_lost[0],15-(rikisidata[kantoushourikisikonbasho].kako_win[0]+rikisidata[kantoushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[kantoushourikisikonbasho].heyaid],rikisidata[kantoushourikisikonbasho].kantoushousuu);
				}else{
					DrawFormatString(10,80,CRWHITE,"敢闘賞　%s %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]],namestring[kantoushourikisikonbasho],rikisidata[kantoushourikisikonbasho].age,rikisidata[kantoushourikisikonbasho].kako_win[0],rikisidata[kantoushourikisikonbasho].kako_lost[0],heyastring[rikisidata[kantoushourikisikonbasho].heyaid],rikisidata[kantoushourikisikonbasho].kantoushousuu);
				}
			}
		}else{
			DrawString(10,80,"敢闘賞　該当なし",CRWHITE);
		}
		if (ginoushourikisikonbasho>=0 && ginoushourikisikonbasho<RIKISISUU){
			if (rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[ginoushourikisikonbasho].kako_bandukesuuji[0]==1){
				if ( (rikisidata[ginoushourikisikonbasho].kako_win[0]+rikisidata[ginoushourikisikonbasho].kako_lost[0])<15){
					DrawFormatString(10,100,CRWHITE,"技能賞　%s筆頭 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]],namestring[ginoushourikisikonbasho],rikisidata[ginoushourikisikonbasho].age,rikisidata[ginoushourikisikonbasho].kako_win[0],rikisidata[ginoushourikisikonbasho].kako_lost[0],15-(rikisidata[ginoushourikisikonbasho].kako_win[0]+rikisidata[ginoushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[ginoushourikisikonbasho].heyaid],rikisidata[ginoushourikisikonbasho].ginoushousuu);
				}else{
					DrawFormatString(10,100,CRWHITE,"技能賞　%s筆頭 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]],namestring[ginoushourikisikonbasho],rikisidata[ginoushourikisikonbasho].age,rikisidata[ginoushourikisikonbasho].kako_win[0],rikisidata[ginoushourikisikonbasho].kako_lost[0],heyastring[rikisidata[ginoushourikisikonbasho].heyaid],rikisidata[ginoushourikisikonbasho].ginoushousuu);
				}
			}else if (rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[ginoushourikisikonbasho].kako_bandukesuuji[0]!=1){
				if ( (rikisidata[ginoushourikisikonbasho].kako_win[0]+rikisidata[ginoushourikisikonbasho].kako_lost[0])<15){
					DrawFormatString(10,100,CRWHITE,"技能賞　%s%d枚目 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]],rikisidata[ginoushourikisikonbasho].kako_bandukesuuji[0],namestring[ginoushourikisikonbasho],rikisidata[ginoushourikisikonbasho].age,rikisidata[ginoushourikisikonbasho].kako_win[0],rikisidata[ginoushourikisikonbasho].kako_lost[0],15-(rikisidata[ginoushourikisikonbasho].kako_win[0]+rikisidata[ginoushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[ginoushourikisikonbasho].heyaid],rikisidata[ginoushourikisikonbasho].ginoushousuu);
				}else{
					DrawFormatString(10,100,CRWHITE,"技能賞　%s%d枚目 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]],rikisidata[ginoushourikisikonbasho].kako_bandukesuuji[0],namestring[ginoushourikisikonbasho],rikisidata[ginoushourikisikonbasho].age,rikisidata[ginoushourikisikonbasho].kako_win[0],rikisidata[ginoushourikisikonbasho].kako_lost[0],heyastring[rikisidata[ginoushourikisikonbasho].heyaid],rikisidata[ginoushourikisikonbasho].ginoushousuu);
				}
			}else{
				if ( (rikisidata[ginoushourikisikonbasho].kako_win[0]+rikisidata[ginoushourikisikonbasho].kako_lost[0])<15){
					DrawFormatString(10,100,CRWHITE,"技能賞　%s %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]],namestring[ginoushourikisikonbasho],rikisidata[ginoushourikisikonbasho].age,rikisidata[ginoushourikisikonbasho].kako_win[0],rikisidata[ginoushourikisikonbasho].kako_lost[0],15-(rikisidata[ginoushourikisikonbasho].kako_win[0]+rikisidata[ginoushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[ginoushourikisikonbasho].heyaid],rikisidata[ginoushourikisikonbasho].ginoushousuu);
				}else{
					DrawFormatString(10,100,CRWHITE,"技能賞　%s %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]],namestring[ginoushourikisikonbasho],rikisidata[ginoushourikisikonbasho].age,rikisidata[ginoushourikisikonbasho].kako_win[0],rikisidata[ginoushourikisikonbasho].kako_lost[0],heyastring[rikisidata[ginoushourikisikonbasho].heyaid],rikisidata[ginoushourikisikonbasho].ginoushousuu);
				}
			}
		}else{
			DrawString(10,100,"技能賞　該当なし",CRWHITE);
		}
	}else{
		if (skiphyojimode==1){
			if (yuushourikisikonbasho>=0 && yuushourikisikonbasho<RIKISISUU){
				if (rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[yuushourikisikonbasho].kako_bandukesuuji[0]==1){
					if ( (rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0])<15){
						DrawFormatString(0,440,CRWHITE,"先場所優勝　%s筆頭 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],15-(rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
					}else{
						DrawFormatString(0,440,CRWHITE,"先場所優勝　%s筆頭 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
					}
				}else if (rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[yuushourikisikonbasho].kako_bandukesuuji[0]!=1){
					if ( (rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0])<15){
						DrawFormatString(0,440,CRWHITE,"先場所優勝　%s%d枚目 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],rikisidata[yuushourikisikonbasho].kako_bandukesuuji[0],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],15-(rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
					}else{
						DrawFormatString(0,440,CRWHITE,"先場所優勝　%s%d枚目 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],rikisidata[yuushourikisikonbasho].kako_bandukesuuji[0],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
					}
				}else{
					if ( (rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0])<15){
						DrawFormatString(0,440,CRWHITE,"先場所優勝　%s %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],15-(rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
					}else{
						DrawFormatString(0,440,CRWHITE,"先場所優勝　%s %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
					}
				}
			}
			DrawString(0,5,"今場所の自部屋力士",CRWHITE);
			for (i=0;i<20;i++){
				if (shozokurikisisuu[0]<=i){break;}
				if (rikisidata[heyabandukejunid[0][i]].bandukenameid<=3){
					DrawFormatString(0,30+i*20,CRWHITE,"%s %s(%d)",bandukenamestring[rikisidata[heyabandukejunid[0][i]].bandukenameid],namestring[heyabandukejunid[0][i]],rikisidata[heyabandukejunid[0][i]].age);
				}else{
					DrawFormatString(0,30+i*20,CRWHITE,"%s%d %s(%d)",bandukenamestring[rikisidata[heyabandukejunid[0][i]].bandukenameid],rikisidata[heyabandukejunid[0][i]].bandukesuuji,namestring[heyabandukejunid[0][i]],rikisidata[heyabandukejunid[0][i]].age);
				}
				if (kyuujouflag[heyabandukejunid[0][i]]==1){
					DrawFormatString(200,30+i*20,CRWHITE,"休場%d勝%d敗",
					win_skip[heyabandukejunid[0][i]],
					lost_skip[heyabandukejunid[0][i]]);
				}else{
					DrawFormatString(200,30+i*20,CRWHITE,"%d勝%d敗",
					win_skip[heyabandukejunid[0][i]],
					lost_skip[heyabandukejunid[0][i]]);
				}
			}
			//黒く塗りつぶし
			DrawBox(300,0,639,426,CRBLACK,TRUE);
			DrawString(300,5,"番付上位20人",CRWHITE);
			for (i=0;i<20;i++){
				if (rikisidata[bandukejunid[i]].bandukenameid<=3){
					DrawFormatString(300,30+i*20,CRWHITE,"%s %s(%d)%s",bandukenamestring[rikisidata[bandukejunid[i]].bandukenameid],namestring[bandukejunid[i]],rikisidata[bandukejunid[i]].age,heyastring[rikisidata[bandukejunid[i]].heyaid]);
				}else{
					DrawFormatString(300,30+i*20,CRWHITE,"%s%d %s(%d)%s",bandukenamestring[rikisidata[bandukejunid[i]].bandukenameid],rikisidata[bandukejunid[i]].bandukesuuji,namestring[bandukejunid[i]],rikisidata[bandukejunid[i]].age,heyastring[rikisidata[bandukejunid[i]].heyaid]);
				}
				//黒く塗りつぶし
				DrawBox(540,30+i*20,639,30+i*20+19,CRBLACK,TRUE);
				if (kyuujouflag[bandukejunid[i]]==1){
					DrawFormatString(540,30+i*20,CRWHITE,"休場%d勝%d敗",
					win_skip[bandukejunid[i]],
					lost_skip[bandukejunid[i]]);
				}else{
					DrawFormatString(540,30+i*20,CRWHITE,"%d勝%d敗",
					win_skip[bandukejunid[i]],
					lost_skip[bandukejunid[i]]);
				}
			}

		}else{
			if ( (year>=1 && month>2) || year>=2){
				if (tournamentkekkahyojiflag_skip==1){
					DrawFormatString(10,117,CRWHITE,"ガチ杯　%s %s(%s部屋)",
					bandukenamestring[temp_tournament_bandukenameid],
					temp_tournament_namestring,
					temp_tournament_heyastring);
				}
				//最多勝力士表示
				if (year>=2 && month==1){
					fp = fopen("data/rekidai_saitashourikisi.dat","rb");
					// オープンできなかったらここで終了
					if( fp == NULL ){
						ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
						DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
						DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
						ScreenFlip() ;//裏画面を表画面にコピー
						WaitKey();
						mode=1;
						return;
					}
					//読み込み
					fseek( fp, -(sizeof(year)+sizeof(nenkansaitashourisuu)+sizeof(temp_namestring_saitashou)+sizeof(rikisidata[0].age)+sizeof(temp_heyastring_saitashou)+sizeof(nenkansaitashourikisihokanimoiruyoflag)), SEEK_END );
					//読み込み
					if (fread(&temp_year_saitashou,sizeof(year),1,fp)<1){
						ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
						DrawString( 250 , 240 - 32 , "最多勝ファイルの読み込みに失敗" , GetColor(255,255,255) );
						DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
						ScreenFlip() ;//裏画面を表画面にコピー
						WaitKey();
						mode=1;
						return;
					}
					fread(&temp_nenkansaitashourisuu,sizeof(nenkansaitashourisuu),1,fp);
					fread(temp_namestring_saitashou,sizeof(temp_namestring_saitashou),1,fp);
					fread(&temp_age_saitashou,sizeof(rikisidata[0].age),1,fp);
					fread(temp_heyastring_saitashou,sizeof(temp_heyastring_saitashou),1,fp);
					fread(&temp_nenkansaitashourikisihokanimoiruyoflag,sizeof(nenkansaitashourikisihokanimoiruyoflag),1,fp);
					fclose(fp);
					//if( ProcessMessage() == -1 ){mode=1;return;}// エラーが起きたらループから抜ける
					if (temp_nenkansaitashourikisihokanimoiruyoflag==1){
						DrawFormatString(10,117,CRWHITE,"年間最多勝　%d勝 %s(%d才)　%s部屋　他",
						temp_nenkansaitashourisuu,
						temp_namestring_saitashou,
						temp_age_saitashou,
						temp_heyastring_saitashou);
					}else{
						DrawFormatString(10,117,CRWHITE,"年間最多勝　%d勝 %s(%d才)　%s部屋",
						temp_nenkansaitashourisuu,
						temp_namestring_saitashou,
						temp_age_saitashou,
						temp_heyastring_saitashou);
					}
				}
				DrawString(30,135,"先場所の番付上位10人",CRWHITE);
				DrawString(30,160+10*25+4,"自部屋の最高位",CRWHITE);
				for (i=0;i<RIKISISUU;i++){
					//if( ProcessMessage() == -1 ){mode=1;return;}
					//自部屋力士もついでに表示
					if (jiheyarikisikonbasho==i){
						for (ii=0;ii<intaisuu;ii++){
							//if( ProcessMessage() == -1 ){mode=1;return;}
							if (intairikisikonbasho[ii]==i){
								DrawString(20-16,160+11*25,"引",CRRED);
								break;
							}
						}
						if (yuushourikisikonbasho==i){
							DrawString(20-16,160+11*25,"優",CRRED);
						}else{
							if (shukunshourikisikonbasho==i || kantoushourikisikonbasho==i || ginoushourikisikonbasho==i){
								DrawString(20-16,160+11*25,"三",CRRED);
							}
						}
						if (temp_bandukenameid_skip[i]<=3){
							if ( (kakobandukewin[i]+kakobandukelost[i])<15 ){
								DrawFormatString(20,160+11*25,CRWHITE,"%s %s(%d)%s %d勝%d敗%d休",
								bandukenamestring[temp_bandukenameid_skip[i]],
								temp_namestring_skip[i],
								temp_age_skip[i],
								temp_heyastring_skip[i],
								kakobandukewin[i],
								kakobandukelost[i],
								15-(kakobandukewin[i]+kakobandukelost[i]));
							}else{
								DrawFormatString(20,160+11*25,CRWHITE,"%s %s(%d)%s %d勝%d敗",
								bandukenamestring[temp_bandukenameid_skip[i]],
								temp_namestring_skip[i],
								temp_age_skip[i],
								temp_heyastring_skip[i],
								kakobandukewin[i],
								kakobandukelost[i]);
							}
						}else if (temp_bandukenameid_skip[i]<=5){
							if ( (kakobandukewin[i]+kakobandukelost[i])<15 ){
								DrawFormatString(20,160+11*25,CRWHITE,"%s%d %s(%d)%s %d勝%d敗%d休",
								bandukenamestring[temp_bandukenameid_skip[i]],
								temp_bandukesuuji_skip[i],
								temp_namestring_skip[i],
								temp_age_skip[i],
								temp_heyastring_skip[i],
								kakobandukewin[i],
								kakobandukelost[i],
								15-(kakobandukewin[i]+kakobandukelost[i]));
							}else{
								DrawFormatString(20,160+11*25,CRWHITE,"%s%d %s(%d)%s %d勝%d敗",
								bandukenamestring[temp_bandukenameid_skip[i]],
								temp_bandukesuuji_skip[i],
								temp_namestring_skip[i],
								temp_age_skip[i],
								temp_heyastring_skip[i],
								kakobandukewin[i],
								kakobandukelost[i]);
							}
						}else{
							if ( (kakobandukewin[i]+kakobandukelost[i])<7 ){
								DrawFormatString(20,160+11*25,CRWHITE,"%s%d %s(%d)%s %d勝%d敗%d休",
								bandukenamestring[temp_bandukenameid_skip[i]],
								temp_bandukesuuji_skip[i],
								temp_namestring_skip[i],
								temp_age_skip[i],
								temp_heyastring_skip[i],
								kakobandukewin[i],
								kakobandukelost[i],
								7-(kakobandukewin[i]+kakobandukelost[i]));
							}else{
								DrawFormatString(20,160+11*25,CRWHITE,"%s%d %s(%d)%s %d勝%d敗",
								bandukenamestring[temp_bandukenameid_skip[i]],
								temp_bandukesuuji_skip[i],
								temp_namestring_skip[i],
								temp_age_skip[i],
								temp_heyastring_skip[i],
								kakobandukewin[i],
								kakobandukelost[i]);
							}
						}
					}
					//先場所番付上位10人
					if (temp_bandukejun_skip[i]<10){
						for (ii=0;ii<intaisuu;ii++){
							//if( ProcessMessage() == -1 ){mode=1;return;}
							if (intairikisikonbasho[ii]==i){
								DrawString(20-16,160+temp_bandukejun_skip[i]*25,"引",CRRED);
								break;
							}
						}
						if (yuushourikisikonbasho==i){
							DrawString(20-16,160+temp_bandukejun_skip[i]*25,"優",CRRED);
						}else{
							if (shukunshourikisikonbasho==i || kantoushourikisikonbasho==i || ginoushourikisikonbasho==i){
								DrawString(20-16,160+temp_bandukejun_skip[i]*25,"三",CRRED);
							}
						}
						//番付四股名など
						DrawFormatString(20,160+temp_bandukejun_skip[i]*25,CRWHITE,"%s %s(%d)%s",
						bandukenamestring[temp_bandukenameid_skip[i]],
						temp_namestring_skip[i],
						temp_age_skip[i],
						temp_heyastring_skip[i]);
						//黒く塗りつぶし
						DrawBox(240-5,160+temp_bandukejun_skip[i]*25,420-16-17,160+temp_bandukejun_skip[i]*25+20,CRBLACK,TRUE);
						//勝敗部分だけ
						if ( (kakobandukewin[i]+kakobandukelost[i])<15 ){
							DrawFormatString(240,160+temp_bandukejun_skip[i]*25,CRWHITE,"%2d勝%2d敗%d休",
							kakobandukewin[i],
							kakobandukelost[i],
							15-(kakobandukewin[i]+kakobandukelost[i]));
						}else{
							DrawFormatString(240,160+temp_bandukejun_skip[i]*25,CRWHITE,"%2d勝%2d敗",
							kakobandukewin[i],
							kakobandukelost[i]);
						}
					}
				}
				DrawString(430,135,"今場所の番付上位10人",CRWHITE);
				DrawString(430,160+10*25+4,"自部屋の最高位",CRWHITE);
				if (rikisidata[heyabandukejunid[0][0]].bandukenameid<=3){
					DrawFormatString(420,160+11*25,CRWHITE,"%s %s(%d)%s",bandukenamestring[rikisidata[heyabandukejunid[0][0]].bandukenameid],namestring[heyabandukejunid[0][0]],rikisidata[heyabandukejunid[0][0]].age,heyastring[rikisidata[heyabandukejunid[0][0]].heyaid]);
				}else{
					DrawFormatString(420,160+11*25,CRWHITE,"%s%d %s(%d)%s",bandukenamestring[rikisidata[heyabandukejunid[0][0]].bandukenameid],rikisidata[heyabandukejunid[0][0]].bandukesuuji,namestring[heyabandukejunid[0][0]],rikisidata[heyabandukejunid[0][0]].age,heyastring[rikisidata[heyabandukejunid[0][0]].heyaid]);
				}
				if (rikisidata[heyabandukejunid[0][0]].bandukenameid<rikisidata[heyabandukejunid[0][0]].kako_bandukenameid[0] || (rikisidata[heyabandukejunid[0][0]].bandukenameid==rikisidata[heyabandukejunid[0][0]].kako_bandukenameid[0] && rikisidata[heyabandukejunid[0][0]].bandukesuuji<rikisidata[heyabandukejunid[0][0]].kako_bandukesuuji[0])){
					DrawString(420-16-16,160+11*25,"↑",CRUP);
				}
				if (rikisidata[heyabandukejunid[0][0]].bandukenameid>rikisidata[heyabandukejunid[0][0]].kako_bandukenameid[0] || (rikisidata[heyabandukejunid[0][0]].bandukenameid==rikisidata[heyabandukejunid[0][0]].kako_bandukenameid[0] && rikisidata[heyabandukejunid[0][0]].bandukesuuji>rikisidata[heyabandukejunid[0][0]].kako_bandukesuuji[0])){
					DrawString(420-16-16,160+11*25,"↓",CRDOWN);
				}
				for (i=0;i<10;i++){
					//if( ProcessMessage() == -1 ){mode=1;return;}
					DrawFormatString(420,160+i*25,CRWHITE,"%s %s(%d)%s",bandukenamestring[rikisidata[bandukejunid[i]].bandukenameid],namestring[bandukejunid[i]],rikisidata[bandukejunid[i]].age,heyastring[rikisidata[bandukejunid[i]].heyaid]);
					if (rikisidata[bandukejunid[i]].bandukenameid<rikisidata[bandukejunid[i]].kako_bandukenameid[0] || (rikisidata[bandukejunid[i]].bandukenameid==rikisidata[bandukejunid[i]].kako_bandukenameid[0] && rikisidata[bandukejunid[i]].bandukesuuji<rikisidata[bandukejunid[i]].kako_bandukesuuji[0])){
						DrawString(420-16-16,160+i*25,"↑",CRUP);
					}
					if (rikisidata[bandukejunid[i]].bandukenameid>rikisidata[bandukejunid[i]].kako_bandukenameid[0] || (rikisidata[bandukejunid[i]].bandukenameid==rikisidata[bandukejunid[i]].kako_bandukenameid[0] && rikisidata[bandukejunid[i]].bandukesuuji>rikisidata[bandukejunid[i]].kako_bandukesuuji[0])){
						DrawString(420-16-16,160+i*25,"↓",CRDOWN);
					}
					if (rikisidata[bandukejunid[i]].kadobanflag==1){
						DrawString(420-16,160+i*25,"角",CRWHITE);
					}
					for (ii=0;ii<shousinsuu;ii++){
						if (shousinrikisikonbasho[ii]==bandukejunid[i]){
							DrawString(420-16,160+i*25,"新",CRRED);
							break;
						}
					}
					for (ii=0;ii<kaerizakisuu;ii++){
						if (kaerizakirikisikonbasho[ii]==bandukejunid[i]){
							DrawString(420-16,160+i*25,"返",CRRED);
							break;
						}
					}
				}
				if (month<3){
					DrawFormatString(20,5,CRWHITE,"先場所(%d年%s場所)の結果(ゲーム再開直後は正しく表示できません)",year-1,normal_bashostring[5]);
				}else{
					DrawFormatString(20,5,CRWHITE,"先場所(%d年%s場所)の結果(ゲーム再開直後は正しく表示できません)",year,normal_bashostring[(int)((month-2)/2)]);
				}
				if (yuushourikisikonbasho>=0 && yuushourikisikonbasho<RIKISISUU){
					if (rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[yuushourikisikonbasho].kako_bandukesuuji[0]==1){
						if ( (rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0])<15){
							DrawFormatString(10,30,CRWHITE,"幕内最高優勝　%s筆頭 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],15-(rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
						}else{
							DrawFormatString(10,30,CRWHITE,"幕内最高優勝　%s筆頭 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
						}
					}else if (rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[yuushourikisikonbasho].kako_bandukesuuji[0]!=1){
						if ( (rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0])<15){
							DrawFormatString(10,30,CRWHITE,"幕内最高優勝　%s%d枚目 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],rikisidata[yuushourikisikonbasho].kako_bandukesuuji[0],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],15-(rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
						}else{
							DrawFormatString(10,30,CRWHITE,"幕内最高優勝　%s%d枚目 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],rikisidata[yuushourikisikonbasho].kako_bandukesuuji[0],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
						}
					}else{
						if ( (rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0])<15){
							DrawFormatString(10,30,CRWHITE,"幕内最高優勝　%s %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],15-(rikisidata[yuushourikisikonbasho].kako_win[0]+rikisidata[yuushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
						}else{
							DrawFormatString(10,30,CRWHITE,"幕内最高優勝　%s %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[yuushourikisikonbasho].kako_bandukenameid[0]],namestring[yuushourikisikonbasho],rikisidata[yuushourikisikonbasho].age,rikisidata[yuushourikisikonbasho].kako_win[0],rikisidata[yuushourikisikonbasho].kako_lost[0],heyastring[rikisidata[yuushourikisikonbasho].heyaid],rikisidata[yuushourikisikonbasho].kiroku_yuushoukaisuu);
						}
					}
				}
				if (shukunshourikisikonbasho>=0 && shukunshourikisikonbasho<RIKISISUU){
					if (rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[shukunshourikisikonbasho].kako_bandukesuuji[0]==1){
						if ( (rikisidata[shukunshourikisikonbasho].kako_win[0]+rikisidata[shukunshourikisikonbasho].kako_lost[0])<15){
							DrawFormatString(10,60,CRWHITE,"殊勲賞　%s筆頭 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]],namestring[shukunshourikisikonbasho],rikisidata[shukunshourikisikonbasho].age,rikisidata[shukunshourikisikonbasho].kako_win[0],rikisidata[shukunshourikisikonbasho].kako_lost[0],15-(rikisidata[shukunshourikisikonbasho].kako_win[0]+rikisidata[shukunshourikisikonbasho].kako_lost[0]),heyastring[rikisidata[shukunshourikisikonbasho].heyaid],rikisidata[shukunshourikisikonbasho].shukunshousuu);
						}else{
							DrawFormatString(10,60,CRWHITE,"殊勲賞　%s筆頭 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]],namestring[shukunshourikisikonbasho],rikisidata[shukunshourikisikonbasho].age,rikisidata[shukunshourikisikonbasho].kako_win[0],rikisidata[shukunshourikisikonbasho].kako_lost[0],heyastring[rikisidata[shukunshourikisikonbasho].heyaid],rikisidata[shukunshourikisikonbasho].shukunshousuu);
						}
					}else if (rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[shukunshourikisikonbasho].kako_bandukesuuji[0]!=1){
						if ( (rikisidata[shukunshourikisikonbasho].kako_win[0]+rikisidata[shukunshourikisikonbasho].kako_lost[0])<15){
							DrawFormatString(10,60,CRWHITE,"殊勲賞　%s%d枚目 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]],rikisidata[shukunshourikisikonbasho].kako_bandukesuuji[0],namestring[shukunshourikisikonbasho],rikisidata[shukunshourikisikonbasho].age,rikisidata[shukunshourikisikonbasho].kako_win[0],rikisidata[shukunshourikisikonbasho].kako_lost[0],15-(rikisidata[shukunshourikisikonbasho].kako_win[0]+rikisidata[shukunshourikisikonbasho].kako_lost[0]),heyastring[rikisidata[shukunshourikisikonbasho].heyaid],rikisidata[shukunshourikisikonbasho].shukunshousuu);
						}else{
							DrawFormatString(10,60,CRWHITE,"殊勲賞　%s%d枚目 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]],rikisidata[shukunshourikisikonbasho].kako_bandukesuuji[0],namestring[shukunshourikisikonbasho],rikisidata[shukunshourikisikonbasho].age,rikisidata[shukunshourikisikonbasho].kako_win[0],rikisidata[shukunshourikisikonbasho].kako_lost[0],heyastring[rikisidata[shukunshourikisikonbasho].heyaid],rikisidata[shukunshourikisikonbasho].shukunshousuu);
						}
					}else{
						if ( (rikisidata[shukunshourikisikonbasho].kako_win[0]+rikisidata[shukunshourikisikonbasho].kako_lost[0])<15){
							DrawFormatString(10,60,CRWHITE,"殊勲賞　%s %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]],namestring[shukunshourikisikonbasho],rikisidata[shukunshourikisikonbasho].age,rikisidata[shukunshourikisikonbasho].kako_win[0],rikisidata[shukunshourikisikonbasho].kako_lost[0],15-(rikisidata[shukunshourikisikonbasho].kako_win[0]+rikisidata[shukunshourikisikonbasho].kako_lost[0]),heyastring[rikisidata[shukunshourikisikonbasho].heyaid],rikisidata[shukunshourikisikonbasho].shukunshousuu);
						}else{
							DrawFormatString(10,60,CRWHITE,"殊勲賞　%s %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[shukunshourikisikonbasho].kako_bandukenameid[0]],namestring[shukunshourikisikonbasho],rikisidata[shukunshourikisikonbasho].age,rikisidata[shukunshourikisikonbasho].kako_win[0],rikisidata[shukunshourikisikonbasho].kako_lost[0],heyastring[rikisidata[shukunshourikisikonbasho].heyaid],rikisidata[shukunshourikisikonbasho].shukunshousuu);
						}
					}
				}else{
					DrawString(10,60,"殊勲賞　該当なし",CRWHITE);
				}
				if (kantoushourikisikonbasho>=0 && kantoushourikisikonbasho<RIKISISUU){
					if (rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[kantoushourikisikonbasho].kako_bandukesuuji[0]==1){
						if ( (rikisidata[kantoushourikisikonbasho].kako_win[0]+rikisidata[kantoushourikisikonbasho].kako_lost[0])<15){
							DrawFormatString(10,80,CRWHITE,"敢闘賞　%s筆頭 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]],namestring[kantoushourikisikonbasho],rikisidata[kantoushourikisikonbasho].age,rikisidata[kantoushourikisikonbasho].kako_win[0],rikisidata[kantoushourikisikonbasho].kako_lost[0],15-(rikisidata[kantoushourikisikonbasho].kako_win[0]+rikisidata[kantoushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[kantoushourikisikonbasho].heyaid],rikisidata[kantoushourikisikonbasho].kantoushousuu);
						}else{
							DrawFormatString(10,80,CRWHITE,"敢闘賞　%s筆頭 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]],namestring[kantoushourikisikonbasho],rikisidata[kantoushourikisikonbasho].age,rikisidata[kantoushourikisikonbasho].kako_win[0],rikisidata[kantoushourikisikonbasho].kako_lost[0],heyastring[rikisidata[kantoushourikisikonbasho].heyaid],rikisidata[kantoushourikisikonbasho].kantoushousuu);
						}
					}else if (rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[kantoushourikisikonbasho].kako_bandukesuuji[0]!=1){
						if ( (rikisidata[kantoushourikisikonbasho].kako_win[0]+rikisidata[kantoushourikisikonbasho].kako_lost[0])<15){
							DrawFormatString(10,80,CRWHITE,"敢闘賞　%s%d枚目 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]],rikisidata[kantoushourikisikonbasho].kako_bandukesuuji[0],namestring[kantoushourikisikonbasho],rikisidata[kantoushourikisikonbasho].age,rikisidata[kantoushourikisikonbasho].kako_win[0],rikisidata[kantoushourikisikonbasho].kako_lost[0],15-(rikisidata[kantoushourikisikonbasho].kako_win[0]+rikisidata[kantoushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[kantoushourikisikonbasho].heyaid],rikisidata[kantoushourikisikonbasho].kantoushousuu);
						}else{
							DrawFormatString(10,80,CRWHITE,"敢闘賞　%s%d枚目 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]],rikisidata[kantoushourikisikonbasho].kako_bandukesuuji[0],namestring[kantoushourikisikonbasho],rikisidata[kantoushourikisikonbasho].age,rikisidata[kantoushourikisikonbasho].kako_win[0],rikisidata[kantoushourikisikonbasho].kako_lost[0],heyastring[rikisidata[kantoushourikisikonbasho].heyaid],rikisidata[kantoushourikisikonbasho].kantoushousuu);
						}
					}else{
						if ( (rikisidata[kantoushourikisikonbasho].kako_win[0]+rikisidata[kantoushourikisikonbasho].kako_lost[0])<15){
							DrawFormatString(10,80,CRWHITE,"敢闘賞　%s %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]],namestring[kantoushourikisikonbasho],rikisidata[kantoushourikisikonbasho].age,rikisidata[kantoushourikisikonbasho].kako_win[0],rikisidata[kantoushourikisikonbasho].kako_lost[0],15-(rikisidata[kantoushourikisikonbasho].kako_win[0]+rikisidata[kantoushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[kantoushourikisikonbasho].heyaid],rikisidata[kantoushourikisikonbasho].kantoushousuu);
						}else{
							DrawFormatString(10,80,CRWHITE,"敢闘賞　%s %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[kantoushourikisikonbasho].kako_bandukenameid[0]],namestring[kantoushourikisikonbasho],rikisidata[kantoushourikisikonbasho].age,rikisidata[kantoushourikisikonbasho].kako_win[0],rikisidata[kantoushourikisikonbasho].kako_lost[0],heyastring[rikisidata[kantoushourikisikonbasho].heyaid],rikisidata[kantoushourikisikonbasho].kantoushousuu);
						}
					}
				}else{
					DrawString(10,80,"敢闘賞　該当なし",CRWHITE);
				}
				if (ginoushourikisikonbasho>=0 && ginoushourikisikonbasho<RIKISISUU){
					if (rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[ginoushourikisikonbasho].kako_bandukesuuji[0]==1){
						if ( (rikisidata[ginoushourikisikonbasho].kako_win[0]+rikisidata[ginoushourikisikonbasho].kako_lost[0])<15){
							DrawFormatString(10,100,CRWHITE,"技能賞　%s筆頭 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]],namestring[ginoushourikisikonbasho],rikisidata[ginoushourikisikonbasho].age,rikisidata[ginoushourikisikonbasho].kako_win[0],rikisidata[ginoushourikisikonbasho].kako_lost[0],15-(rikisidata[ginoushourikisikonbasho].kako_win[0]+rikisidata[ginoushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[ginoushourikisikonbasho].heyaid],rikisidata[ginoushourikisikonbasho].ginoushousuu);
						}else{
							DrawFormatString(10,100,CRWHITE,"技能賞　%s筆頭 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]],namestring[ginoushourikisikonbasho],rikisidata[ginoushourikisikonbasho].age,rikisidata[ginoushourikisikonbasho].kako_win[0],rikisidata[ginoushourikisikonbasho].kako_lost[0],heyastring[rikisidata[ginoushourikisikonbasho].heyaid],rikisidata[ginoushourikisikonbasho].ginoushousuu);
						}
					}else if (rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]==4 && rikisidata[ginoushourikisikonbasho].kako_bandukesuuji[0]!=1){
						if ( (rikisidata[ginoushourikisikonbasho].kako_win[0]+rikisidata[ginoushourikisikonbasho].kako_lost[0])<15){
							DrawFormatString(10,100,CRWHITE,"技能賞　%s%d枚目 %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]],rikisidata[ginoushourikisikonbasho].kako_bandukesuuji[0],namestring[ginoushourikisikonbasho],rikisidata[ginoushourikisikonbasho].age,rikisidata[ginoushourikisikonbasho].kako_win[0],rikisidata[ginoushourikisikonbasho].kako_lost[0],15-(rikisidata[ginoushourikisikonbasho].kako_win[0]+rikisidata[ginoushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[ginoushourikisikonbasho].heyaid],rikisidata[ginoushourikisikonbasho].ginoushousuu);
						}else{
							DrawFormatString(10,100,CRWHITE,"技能賞　%s%d枚目 %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]],rikisidata[ginoushourikisikonbasho].kako_bandukesuuji[0],namestring[ginoushourikisikonbasho],rikisidata[ginoushourikisikonbasho].age,rikisidata[ginoushourikisikonbasho].kako_win[0],rikisidata[ginoushourikisikonbasho].kako_lost[0],heyastring[rikisidata[ginoushourikisikonbasho].heyaid],rikisidata[ginoushourikisikonbasho].ginoushousuu);
						}
					}else{
						if ( (rikisidata[ginoushourikisikonbasho].kako_win[0]+rikisidata[ginoushourikisikonbasho].kako_lost[0])<15){
							DrawFormatString(10,100,CRWHITE,"技能賞　%s %s(%d才) %d勝%d敗%d休 %s部屋 %d回目",bandukenamestring[rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]],namestring[ginoushourikisikonbasho],rikisidata[ginoushourikisikonbasho].age,rikisidata[ginoushourikisikonbasho].kako_win[0],rikisidata[ginoushourikisikonbasho].kako_lost[0],15-(rikisidata[ginoushourikisikonbasho].kako_win[0]+rikisidata[ginoushourikisikonbasho].kako_lost[0]),heyastring[rikisidata[ginoushourikisikonbasho].heyaid],rikisidata[ginoushourikisikonbasho].ginoushousuu);
						}else{
							DrawFormatString(10,100,CRWHITE,"技能賞　%s %s(%d才) %d勝%d敗 %s部屋 %d回目",bandukenamestring[rikisidata[ginoushourikisikonbasho].kako_bandukenameid[0]],namestring[ginoushourikisikonbasho],rikisidata[ginoushourikisikonbasho].age,rikisidata[ginoushourikisikonbasho].kako_win[0],rikisidata[ginoushourikisikonbasho].kako_lost[0],heyastring[rikisidata[ginoushourikisikonbasho].heyaid],rikisidata[ginoushourikisikonbasho].ginoushousuu);
						}
					}
				}else{
					DrawString(10,100,"技能賞　該当なし",CRWHITE);
				}
			}
		}
	}
	ScreenFlip() ;//裏画面を表画面にコピー
	if( ProcessMessage() == -1 ){mode=1;return;}
	return;
}

void AIhyokajougeritu(void)
{
	FILE *fpwindow;
	int i;
HYOJI_AIhyokajougeritu:
	ClearDrawScreen();
	DrawBox(0,0,639,479,CRBACK,TRUE);
	DrawBox(0,0,640,480,CRLINE,TRUE);//大枠描画
	DrawBox(3,3,637,477,CRBACK,TRUE);
	//DrawBox(0,21,187,480,CRLINE,TRUE);
	//DrawBox(3,24,184,477,CRBACK,TRUE);
	//DrawBox(184,21,640,369,CRLINE,TRUE);
	//DrawBox(187,24,637,366,CRBACK,TRUE);
	//DrawBox(184,366,640,480,CRLINE,TRUE);
	//DrawBox(187,369,637,477,CRBACK,TRUE);
	DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分
	//DrawBox(3,76,183,475,CRTAB,TRUE);
	DrawStringToHandle(100,6,"　　　　　　　　　　AI評価上下率設定(全力士共通)",CRWHITE,FontHandle12);

	DrawString(x1[4],y1[4],"　　戻る",CRGREEN);


	DrawStringToHandle(187,24,"取組(稽古)相手の番付によって、評価の上下率を設定します",CRWHITE,FontHandle12);

	DrawStringToHandle(190,40,"プラス効果の評価アップ確率(左右クリックで変更)",CRWHITE,FontHandle12);
	i=0;
	DrawStringToHandle(190,55+i*15,"格下(rankも4つ以上も下)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,55+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_upkakuritu[i]);
	i++;
	DrawStringToHandle(190,55+i*15,"格下(rankも3つ下)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,55+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_upkakuritu[i]);
	i++;
	DrawStringToHandle(190,55+i*15,"格下(rankも2つ下)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,55+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_upkakuritu[i]);
	i++;
	DrawStringToHandle(190,55+i*15,"格下(rankも1つ下)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,55+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_upkakuritu[i]);
	i++;
	DrawStringToHandle(190,55+i*15,"格下(rankは同じ)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,55+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_upkakuritu[i]);
	i++;
	DrawStringToHandle(190,55+i*15,"格上(rankは同じ)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,55+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_upkakuritu[i]);
	i++;
	DrawStringToHandle(190,55+i*15,"格上(rankは1つ上)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,55+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_upkakuritu[i]);
	i++;
	DrawStringToHandle(190,55+i*15,"格上(rankは2つ上)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,55+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_upkakuritu[i]);
	i++;
	DrawStringToHandle(190,55+i*15,"格上(rankは3つ上)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,55+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_upkakuritu[i]);
	i++;
	DrawStringToHandle(190,55+i*15,"格上(rankは4つ以上も上)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,55+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_upkakuritu[i]);

	DrawStringToHandle(190,210,"マイナス効果の評価ダウン確率(左右クリックで変更)",CRWHITE,FontHandle12);
	i=0;
	DrawStringToHandle(190,225+i*15,"格下(rankも4つ以上も下)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,225+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_downkakuritu[i]);
	i++;
	DrawStringToHandle(190,225+i*15,"格下(rankも3つ下)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,225+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_downkakuritu[i]);
	i++;
	DrawStringToHandle(190,225+i*15,"格下(rankも2つ下)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,225+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_downkakuritu[i]);
	i++;
	DrawStringToHandle(190,225+i*15,"格下(rankも1つ下)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,225+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_downkakuritu[i]);
	i++;
	DrawStringToHandle(190,225+i*15,"格下(rankは同じ)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,225+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_downkakuritu[i]);
	i++;
	DrawStringToHandle(190,225+i*15,"格上(rankは同じ)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,225+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_downkakuritu[i]);
	i++;
	DrawStringToHandle(190,225+i*15,"格上(rankは1つ上)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,225+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_downkakuritu[i]);
	i++;
	DrawStringToHandle(190,225+i*15,"格上(rankは2つ上)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,225+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_downkakuritu[i]);
	i++;
	DrawStringToHandle(190,225+i*15,"格上(rankは3つ上)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,225+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_downkakuritu[i]);
	i++;
	DrawStringToHandle(190,225+i*15,"格上(rankは4つ以上も上)",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,225+i*15,CRGREEN,FontHandle12,"%3d％",hyoka_downkakuritu[i]);


	ScreenFlip();
	if( ProcessMessage() == -1 ){mode=1;return;}
	while(1)
	{
		for (i=0;i<10;i++){
			if (get_mouseclick(360,55+i*15,360+50,55+i*15+12) == 1){//左クリック
				if (hyoka_upkakuritu[i]<100){
					hyoka_upkakuritu[i]++;
				}else{
					hyoka_upkakuritu[i]=0;
				}
				WaitTimer(130);goto HYOJI_AIhyokajougeritu;
			}
			if (get_mouseclick(360,55+i*15,360+50,55+i*15+12) == 2){//右クリック
				if (hyoka_upkakuritu[i]>0){
					hyoka_upkakuritu[i]--;
				}else{
					hyoka_upkakuritu[i]=100;
				}
				WaitTimer(130);goto HYOJI_AIhyokajougeritu;
			}
			if (get_mouseclick(360,225+i*15,360+50,225+i*15+12) == 1){//左クリック
				if (hyoka_downkakuritu[i]<100){
					hyoka_downkakuritu[i]++;
				}else{
					hyoka_downkakuritu[i]=0;
				}
				WaitTimer(130);goto HYOJI_AIhyokajougeritu;
			}
			if (get_mouseclick(360,225+i*15,360+50,225+i*15+12) == 2){//右クリック
				if (hyoka_downkakuritu[i]>0){
					hyoka_downkakuritu[i]--;
				}else{
					hyoka_downkakuritu[i]=100;
				}
				WaitTimer(130);goto HYOJI_AIhyokajougeritu;
			}
		}
		if (get_mouseclick_list(4) == 1 || get_mouseclick_list(5)==1){
			fpwindow = fopen("data/AIhyoka_updownkakuritu.dat","wb");
			if( fpwindow == NULL ){
				mode=1;
				return ;	// エラーが起きたらループから抜ける
			}else{
				fwrite(hyoka_upkakuritu,sizeof(hyoka_upkakuritu),1,fpwindow);
				fwrite(hyoka_downkakuritu,sizeof(hyoka_downkakuritu),1,fpwindow);
			}
			fclose(fpwindow);
			WaitTimer(200);
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

void AIwazarandomritu(void)
{
	FILE *fpwindow;
	int i;
HYOJI_AIwazarandomritu:
	ClearDrawScreen();
	DrawBox(0,0,639,479,CRBACK,TRUE);
	DrawBox(0,0,640,480,CRLINE,TRUE);//大枠描画
	DrawBox(3,3,637,477,CRBACK,TRUE);
	//DrawBox(0,21,187,480,CRLINE,TRUE);
	//DrawBox(3,24,184,477,CRBACK,TRUE);
	//DrawBox(184,21,640,369,CRLINE,TRUE);
	//DrawBox(187,24,637,366,CRBACK,TRUE);
	//DrawBox(184,366,640,480,CRLINE,TRUE);
	//DrawBox(187,369,637,477,CRBACK,TRUE);
	DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分
	//DrawBox(3,76,183,475,CRTAB,TRUE);
	DrawStringToHandle(100,6,"　　　　　　　　　　AI技ランダム率設定(全力士共通)",CRWHITE,FontHandle12);

	DrawString(x1[4],y1[4],"　　戻る",CRGREEN);


	DrawStringToHandle(187,24,"本割直近６場所の対戦成績に応じてランダム率を設定します",CRWHITE,FontHandle12);

	DrawStringToHandle(190,40,"評価によらずにランダムで技を選択する率(左右クリックで変更)",CRWHITE,FontHandle12);
	DrawStringToHandle(190,56,"※取組中の技選択のたびにこの率で判断します",CRWHITE,FontHandle12);

	i=0;
	DrawStringToHandle(190,80+i*15,"負け越してない",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,80+i*15,CRGREEN,FontHandle12,"%3d％",waza_randomsentakuritu_makekosisuu[i]);
	i++;
	DrawStringToHandle(190,80+i*15,"１つ負け越し",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,80+i*15,CRGREEN,FontHandle12,"%3d％",waza_randomsentakuritu_makekosisuu[i]);
	i++;
	DrawStringToHandle(190,80+i*15,"２つ負け越し",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,80+i*15,CRGREEN,FontHandle12,"%3d％",waza_randomsentakuritu_makekosisuu[i]);
	i++;
	DrawStringToHandle(190,80+i*15,"３つ負け越し",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,80+i*15,CRGREEN,FontHandle12,"%3d％",waza_randomsentakuritu_makekosisuu[i]);
	i++;
	DrawStringToHandle(190,80+i*15,"４つ負け越し",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,80+i*15,CRGREEN,FontHandle12,"%3d％",waza_randomsentakuritu_makekosisuu[i]);
	i++;
	DrawStringToHandle(190,80+i*15,"５つ負け越し",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,80+i*15,CRGREEN,FontHandle12,"%3d％",waza_randomsentakuritu_makekosisuu[i]);
	i++;
	DrawStringToHandle(190,80+i*15,"６つ負け越し",CRWHITE,FontHandle12);
	DrawFormatStringToHandle(360,80+i*15,CRGREEN,FontHandle12,"%3d％",waza_randomsentakuritu_makekosisuu[i]);


	ScreenFlip();
	if( ProcessMessage() == -1 ){mode=1;return;}
	while(1)
	{
		for (i=0;i<7;i++){
			if (get_mouseclick(360,80+i*15,360+50,80+i*15+12) == 1){//左クリック
				if (waza_randomsentakuritu_makekosisuu[i]<100){
					waza_randomsentakuritu_makekosisuu[i]++;
				}else{
					waza_randomsentakuritu_makekosisuu[i]=0;
				}
				WaitTimer(130);goto HYOJI_AIwazarandomritu;
			}
			if (get_mouseclick(360,80+i*15,360+50,80+i*15+12) == 2){//右クリック
				if (waza_randomsentakuritu_makekosisuu[i]>0){
					waza_randomsentakuritu_makekosisuu[i]--;
				}else{
					waza_randomsentakuritu_makekosisuu[i]=100;
				}
				WaitTimer(130);goto HYOJI_AIwazarandomritu;
			}
		}
		if (get_mouseclick_list(4) == 1 || get_mouseclick_list(5)==1){
			fpwindow = fopen("data/AIwazarandomritu.dat","wb");
			if( fpwindow == NULL ){
				mode=1;
				return ;	// エラーが起きたらループから抜ける
			}else{
				fwrite(waza_randomsentakuritu_makekosisuu,sizeof(waza_randomsentakuritu_makekosisuu),1,fpwindow);
			}
			fclose(fpwindow);
			WaitTimer(200);
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


void AIkotenagesukuinage_shokiti(void)
{
	FILE *fpwindow;
HYOJI_AIkotenagesukuinage:
	ClearDrawScreen();
	DrawBox(0,0,639,479,CRBACK,TRUE);
	DrawBox(0,0,640,480,CRLINE,TRUE);//大枠描画
	DrawBox(3,3,637,477,CRBACK,TRUE);
	//DrawBox(0,21,187,480,CRLINE,TRUE);
	//DrawBox(3,24,184,477,CRBACK,TRUE);
	//DrawBox(184,21,640,369,CRLINE,TRUE);
	//DrawBox(187,24,637,366,CRBACK,TRUE);
	//DrawBox(184,366,640,480,CRLINE,TRUE);
	//DrawBox(187,369,637,477,CRBACK,TRUE);
	DrawBox(3,3,637,21,CRBACK,TRUE);//上部メニュー部分
	//DrawBox(3,76,183,475,CRTAB,TRUE);
	DrawStringToHandle(100,6,"　　　　　　　　　　AI小手投げ掬い投げ初期値設定(全力士共通)",CRWHITE,FontHandle12);

	DrawString(x1[4],y1[4],"　　戻る",CRGREEN);


	DrawStringToHandle(187,24,"AI評価のうち小手投掬い投の初期値を設定できます",CRWHITE,FontHandle12);

	DrawStringToHandle(190,40,"Ｄ評価スタートか他と同じＢ評価スタートか",CRWHITE,FontHandle12);
	DrawStringToHandle(190,72,"Ｂ評価スタートにすると最初は無謀な投げ乱発かも…",CRWHITE,FontHandle12);

	if (AIkotenagesukuinage_shokitizeroflag==0){
		DrawString(x1[10],y1[10],"初期値Ｂスタート",CRWHITE);
	}else{
		DrawString(x1[10],y1[10],"初期値Ｄスタート",CRWHITE);
	}
	DrawString(x1[12],y1[12],"初期値変更",CRGREEN);



	ScreenFlip();
	if( ProcessMessage() == -1 ){mode=1;return;}
	while(1)
	{
		if (get_mouseclick_list(12) == 1 || get_mouseclick_list(13)==1){
			if (AIkotenagesukuinage_shokitizeroflag==0){
				AIkotenagesukuinage_shokitizeroflag=1;
			}else{
				AIkotenagesukuinage_shokitizeroflag=0;
			}
			WaitTimer(130);goto HYOJI_AIkotenagesukuinage;
		}
		if (get_mouseclick_list(4) == 1 || get_mouseclick_list(5)==1){
			fpwindow = fopen("data/AIkotesukui.dat","wb");
			if( fpwindow == NULL ){
				mode=1;
				return ;	// エラーが起きたらループから抜ける
			}else{
				fwrite(&AIkotenagesukuinage_shokitizeroflag,sizeof(AIkotenagesukuinage_shokitizeroflag),1,fpwindow);
			}
			fclose(fpwindow);
			WaitTimer(200);
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
