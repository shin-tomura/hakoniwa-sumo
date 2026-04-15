#include "DxLib.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include "sub.h"
#include "define.h"
#include "MT.h"
extern int HIDDENSUU;
double label_input[OUTPUTSUU];
double atai_input[INPUTSUU];
double atai_hidden[1024];
double atai_output[OUTPUTSUU];
double back_hidden[1024];
double back_output[OUTPUTSUU];

extern double eta;
double randommax_omomi;
double randommin_omomi;
double randommax_sikiiti;
double randommin_sikiiti;

int deep_higasi_tatiai_power;
int deep_nisi_tatiai_power;
int deep_higasi_tatiai_nerai;
int deep_nisi_tatiai_nerai;

int deep_offenseid[100];
int deep_defenseid[100];
extern int offenseid;
extern int defenseid;
//int deep_offense_stamina[100];
//int deep_defense_stamina[100];

int deep_defense_action_zengo[100];//defense_action_zengo
int deep_offense_state_jouge[100];//offense_state_jouge
int deep_defense_state_jouge[100];//defense_state_jouge
int deep_offense_state_balance[100];//offense_state_balance
int deep_defense_state_balance[100];//defense_state_balance
int deep_offense_state_migiude[100];//offense_state_migiude
int deep_defense_state_migiude[100];//defense_state_migiude
int deep_offense_state_hidariude[100];//offense_state_hidariude
int deep_defense_state_hidariude[100];//defense_state_hidariude
int deep_state_ichi[100];//state_ichi
int deep_state_kyori[100];//state_kyori
int deep_wazaid_sentaku[100];//wazaid_sentakuだけどイレギュラー処理は違うかも
int deep_joukyourireki1[100];
int deep_joukyourireki2[100];

extern struct rikisi_data rikisidata[RIKISISUU];//力士データ用構造体変数708人分用意

extern int higasi_tatiai_power; extern int nisi_tatiai_power;
extern int higasi_tatiai_nerai; extern int nisi_tatiai_nerai;

//extern int offense_stamina;
//extern int defense_stamina;

extern int defense_action_zengo;
extern int offense_state_balance;
extern int defense_state_balance;
extern int offense_state_jouge;
extern int defense_state_jouge;
extern int offense_state_migiude;
extern int offense_state_hidariude;
extern int defense_state_migiude;
extern int defense_state_hidariude;
extern int state_kyori;
extern int state_ichi;//土俵上での位置-4～+4、0が土俵中央、-4で東力士OUT、+4で西力士OUT
extern int chokuzen_defense_action_zengo;
extern int chokuzen_state_kyori;
extern int chokuzen_offense_state_migiude;
extern int chokuzen_offense_state_hidariude;
extern int chokuzen_defense_state_migiude;
extern int chokuzen_defense_state_hidariude;
extern int chokuzen_offense_state_jouge;
extern int chokuzen_defense_state_jouge;
extern int chokuzen_offense_state_balance;
extern int chokuzen_defense_state_balance;

extern int mode;
extern long aidata_fichi[22][5][2][2][2][2][4];//aidataのファイル記録位置
									//技ＩＤ	四つ	自分右廻し	自分左廻し	相手右廻し	相手左廻し	上体比較
									//上体は3→相手の圧力なしかバランス崩れ、2→自分の方が低い、1→同じ、0→自分の方が高い
extern int MAE_STATE_UDE;
extern int UWATE_STATE_UDE;
extern int SITATE_STATE_UDE;
extern int UWATETUKAMI_STATE_UDE;
extern int SITATETUKAMI_STATE_UDE;
extern int FAR_STATE_KYORI;
extern int MIDDLE_STATE_KYORI;
extern int NEAR_STATE_KYORI;

/////main.cppでextern///////////////////////////////////////////////////
//int deep_torikumisuu;//v_suu
int deep_winmitomenaiflag;
int deep_wazacount;//各取組ごとのvideo_suu、取組中に動きがあるたびにカウントする、記録用変数に代入するとき用のカウント変数
int deep_wazacount_far;
int deep_wazacount_near;
int deep_winhigasiornisi;
int deep_winid;
int deep_lostid;
void deep_tatiaidainyuu(void);
void deep_wazachokuzendainyuu(void);
void deep_wazadainyuu(int);
void deep_input(void);
void deep_shokika(void);
void deep_save(void);
int deep_sentaku_tatiai_nerai(int,int);
int deep_sentaku_tatiai_power(int,int);
int deep_sentaku_waza(int,int,int);
double omomi_input_hidden[INPUTSUU][1024];
double omomi_hidden_output[1024][OUTPUTSUU];
double sikiiti_hidden[1024];
double sikiiti_output[OUTPUTSUU];
double gosatotal_tatiai;
double gosatotal_waza;
double NOWGOSA_tatiai;
double NOWGOSA_waza;
int deep_wazacounttotal;//取組中に動きがあるたびにカウントする、記録用変数に代入するとき用のカウント変数
int deep_tatiaicounttotal;//各取組ごと
int deep_wazacountfartotal;
int deep_wazacountneartotal;
int ataritotal_tatiai_nerai;
int ataritotal_tatiai_power;
int ataritotal_waza_far;
int ataritotal_waza_near;
double NOWSEIKAIRITU_tatiai_nerai;
double NOWSEIKAIRITU_tatiai_power;
double NOWSEIKAIRITU_waza_far;
double NOWSEIKAIRITU_waza_near;
/////main.cppでextern終わり/////////////////////////////////////////////

void deep_output(void);
void deep_study(char,char);
int damewazahandan(int);//(技ID)組手廻しの有無であり得ない技の場合は-1が返る

//シグモイド関数
double sigmoid(double x) {
    return 1.0/(1.0+exp(-x));
}


void deep_save(void){
	FILE *fpwindow;
	fpwindow = fopen("data/deep.dat","wb");
	if( fpwindow == NULL ){
		mode=1;return ;// エラーが起きたらループから抜ける
	}
	fwrite(omomi_input_hidden,sizeof(omomi_input_hidden),1,fpwindow);
	fwrite(omomi_hidden_output,sizeof(omomi_hidden_output),1,fpwindow);
	fwrite(sikiiti_hidden,sizeof(sikiiti_hidden),1,fpwindow);
	fwrite(sikiiti_output,sizeof(sikiiti_output),1,fpwindow);
	fclose(fpwindow);
	return;
}

void deep_input(void){
//勝った方の力士の立会いと繰り出した技を全部学習させる
	//int i=0;
	int ii=0;int winid=0;int lostid=0;
	int inputcount=0;int labelcount=0;
	char choufukuflag=0;
	//if (deep_winmitomenaiflag!=1 && deep_winid!=999 && rikisidata[deep_winid].yao_win==0 && rikisidata[deep_lostid].yao_win==0){
	if (deep_winid!=999 && rikisidata[deep_winid].yao_win==0 && rikisidata[deep_lostid].yao_win==0){
		winid=deep_winid;
		lostid=deep_lostid;
/////負けない技選択なので逆にする//
//winid=deep_lostid;
//lostid=deep_winid;
///////////////////////////	

//項目
		//atai_inputに能力値代入37種類(intiki、mahou、バランス調整も適用後の能力値)
		inputcount=0;
		atai_input[inputcount]=(rikisidata[winid].sinchou-170.0)/50.0;inputcount++;
		atai_input[inputcount]=(rikisidata[winid].taijuu-70.0)/180.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].sekkyokusei/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].binshousei/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].tossinryoku/99.0;inputcount++;
		atai_input[inputcount]=(rikisidata[winid].kerutikara-100.0)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].migiwanryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].hidariwanryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].balance/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].tatiaigijutu/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].tuki/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].migiwakikatasa/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].hidariwakikatasa/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].ategai/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].migikaesi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].hidarikaesi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].migisibori/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].hidarisibori/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].migikakaekomi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].hidarikakaekomi/99.0;inputcount++;
		atai_input[inputcount]=(rikisidata[winid].hikituke-100.0)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].migiakuryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].hidariakuryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].stamina/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].konjou/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].nebari/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].asihakobi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].juunansei/99.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;//atai_input[inputcount]=(100-rikisidata[winid].zunou)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].migiuwatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].hidariuwatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].migisitatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].hidarisitatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].migikotenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].hidarikotenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].migisukuinage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[winid].hidarisukuinage/99.0;inputcount++;
//項目
		//能力値代入負けた方37種類(intiki、mahou、バランス調整も適用後の能力値)
		atai_input[inputcount]=(rikisidata[lostid].sinchou-170.0)/50.0;inputcount++;
		atai_input[inputcount]=(rikisidata[lostid].taijuu-70.0)/180.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].sekkyokusei/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].binshousei/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].tossinryoku/99.0;inputcount++;
		atai_input[inputcount]=(rikisidata[lostid].kerutikara-100.0)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].migiwanryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].hidariwanryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].balance/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].tatiaigijutu/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].tuki/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].migiwakikatasa/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].hidariwakikatasa/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].ategai/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].migikaesi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].hidarikaesi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].migisibori/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].hidarisibori/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].migikakaekomi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].hidarikakaekomi/99.0;inputcount++;
		atai_input[inputcount]=(rikisidata[lostid].hikituke-100.0)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].migiakuryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].hidariakuryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].stamina/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].konjou/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].nebari/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].asihakobi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].juunansei/99.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;//atai_input[inputcount]=(100-rikisidata[lostid].zunou)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].migiuwatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].hidariuwatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].migisitatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].hidarisitatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].migikotenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].hidarikotenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].migisukuinage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[lostid].hidarisukuinage/99.0;inputcount++;
//項目
		//立会だよという列のフラグに1を代入
		atai_input[inputcount]=1.0;inputcount++;
//項目
		//立会い狙い5種類 勝った方だけ
		//int TUKIOSI_TATIAI_NERAI=0;
		//int MIGIYOTU_TATIAI_NERAI=1;
		//int HIDARIYOTU_TATIAI_NERAI=2;
		//int RYOUUWATE_TATIAI_NERAI=3;
		//int MOROZASI_TATIAI_NERAI=4;
		labelcount=0;
		if (deep_winhigasiornisi==1){
			if (deep_higasi_tatiai_nerai==0){
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_higasi_tatiai_nerai==1){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_higasi_tatiai_nerai==2){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_higasi_tatiai_nerai==3){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_higasi_tatiai_nerai==4){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
			}
		}else{
			if (deep_nisi_tatiai_nerai==0){
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_nisi_tatiai_nerai==1){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_nisi_tatiai_nerai==2){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_nisi_tatiai_nerai==3){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_nisi_tatiai_nerai==4){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
			}
		}
//項目
		//立会い勢い4種類 勝った方だけ
		//int ZENRYOKU_TATIAI_POWER=0;
		//int NORMAL_TATIAI_POWER=1;
		//int UKERU_TATIAI_POWER=2;
		//int HENKA_TATIAI_POWER=3;
		if (deep_winhigasiornisi==1){
			if (deep_higasi_tatiai_power==0){
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_higasi_tatiai_power==1){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_higasi_tatiai_power==2){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_higasi_tatiai_power==3){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
			}
		}else{
			if (deep_nisi_tatiai_power==0){
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_nisi_tatiai_power==1){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_nisi_tatiai_power==2){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
			}else if (deep_nisi_tatiai_power==3){
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.0;labelcount++;
				label_input[labelcount]=0.5;labelcount++;
			}
		}
//項目
		//立合い時は残りのinput（立合い後の状況）はすべて0.0
		for (ii=inputcount;ii<INPUTSUU;ii++){//video_suu[i]はその取組の記録コマ数
			atai_input[ii]=0.0;
		}
//項目
		//立合い時は残りのlabel（技選択）はすべて0.0
		for (ii=labelcount;ii<OUTPUTSUU;ii++){//video_suu[i]はその取組の記録コマ数
			label_input[ii]=0.0;
		}
//項目
		//立会時の出力と誤差逆伝播(学習)
		deep_output();
		deep_study(1,0);//立合いの学習なら1を渡す、その次は技の学習の場合の間合いフラグだからここでは関係ない




//項目
		//////ここからは立合いが終わって普通の技の場合////

		for (ii=0;ii<100;ii++){
			deep_joukyourireki1[ii]=0;
			deep_joukyourireki2[ii]=0;
		}
		if (deep_wazacount<99){//maxコマ超えてしまったのは除外
		//{
		/*	//負けの原因の技だけ学習させるため
			int iii=0;int joukyouakkaflag[100];
			for (iii=0;iii<100;iii++){
				joukyouakkaflag[iii]=0;
			}
			for (iii=0;iii<deep_wazacount-1;iii++){
				if (deep_offenseid[iii]==deep_lostid){
					if (deep_offense_state_jouge[iii]>deep_offense_state_jouge[iii+1] 
					|| deep_defense_state_jouge[iii]<deep_defense_state_jouge[iii+1] 
					|| deep_offense_state_balance[iii]>deep_offense_state_balance[iii+1] 
					|| deep_defense_state_balance[iii]<deep_defense_state_balance[iii+1]
					){
						joukyouakkaflag[iii]=1;
					}
					if (deep_offense_state_migiude[iii]>=3){
						if (deep_offense_state_migiude[iii+1]<=2){
							joukyouakkaflag[iii]=1;
						}
					}
					if (deep_offense_state_hidariude[iii]>=3){
						if (deep_offense_state_hidariude[iii+1]<=2){
							joukyouakkaflag[iii]=1;
						}
					}
				}
			}
			for (iii=deep_wazacount-1;iii>=0;iii--){
				if (deep_offenseid[iii]==deep_lostid){
					joukyouakkaflag[iii]=1;break;
				}
			}
			*/
			for (ii=0;ii<deep_wazacount;ii++){//video_suu[i]はその取組の記録コマ数
				//if (joukyouakkaflag[ii]==1){//負けの原因の技だけ学習させるため
				if (deep_offenseid[ii]==deep_winid){//勝った方が攻撃のときだけ学習させるため
				//if (deep_offenseid[ii]==deep_lostid){//負けた方が攻撃のときだけ学習させるため
					{//重複状況での複数入力回避
						int temp_state_ichi=0;int count=0;
						deep_joukyourireki1[ii]=
						10000*deep_wazaid_sentaku[ii]+
						1000*deep_offense_state_jouge[ii]+
						100*deep_defense_state_jouge[ii]+
						10*deep_offense_state_balance[ii]+
						deep_defense_state_balance[ii];
						if (deep_winhigasiornisi==2){
							temp_state_ichi=deep_state_ichi[ii]*-1;
						}else{
							temp_state_ichi=deep_state_ichi[ii];
						}
						deep_joukyourireki2[ii]=
						1000000*deep_defense_action_zengo[ii]+
						100000*deep_offense_state_migiude[ii]+
						10000*deep_offense_state_hidariude[ii]+
						1000*deep_defense_state_migiude[ii]+
						100*deep_defense_state_hidariude[ii]+
						10*temp_state_ichi+
						deep_state_kyori[ii];
						choufukuflag=0;
						if (ii>0){
							for (count=0;count<ii;count++){
								if (deep_joukyourireki1[ii]==deep_joukyourireki1[count] && deep_joukyourireki2[ii]==deep_joukyourireki2[count]){
									choufukuflag=1;
									break;
								}
							}
						}
					}
					if (choufukuflag==1) continue;//ループ先頭に戻る

					
					//video_wazaid_sentaku[i][ii]でiiが0～21のときが通常の技選択、その場合は
					if (deep_wazaid_sentaku[ii]>0 && deep_wazaid_sentaku[ii]<22 && deep_wazaid_sentaku[ii]!=3){
		//項目
						//能力値はそのまま変更なしなので代入処理なし
						inputcount=74;
		//項目
						//立会だよという列のフラグに0を代入
						atai_input[inputcount]=0.0;inputcount++;
		//項目
						//上体の上下3種類*自分と相手で2＝6
						//int HIGH_STATE_JOUGE=0;
						//int MIDDLE_STATE_JOUGE=1;
						//int LOW_STATE_JOUGE=2;
						//自分の上体
						if (deep_offense_state_jouge[ii]==0){
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if (deep_offense_state_jouge[ii]==1){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if (deep_offense_state_jouge[ii]==2){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
						}
						//相手の上体
						if (deep_defense_state_jouge[ii]==0){
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if (deep_defense_state_jouge[ii]==1){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if (deep_defense_state_jouge[ii]==2){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
						}
		//項目
						//バランス、10がMAXで、0で倒れて負け→10で割って0.0～1.0の数値に変換*自分と相手で2＝2
						//自分のバランス
						atai_input[inputcount]=((double)(deep_offense_state_balance[ii]))/10.0;inputcount++;
						//相手のバランス
						atai_input[inputcount]=((double)(deep_defense_state_balance[ii]))/10.0;inputcount++;
		//項目
						//腕の状態（上手か下手か、廻しの有無）5種類*自分と相手で2*右腕左腕で2＝20
						//int MAE_STATE_UDE=0;//間合いが近くない場合
						//int UWATE_STATE_UDE=1;
						//int SITATE_STATE_UDE=2;
						//int UWATETUKAMI_STATE_UDE=3;
						//int SITATETUKAMI_STATE_UDE=4;
						//自分右腕
						if (deep_offense_state_migiude[ii]==0){
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_offense_state_migiude[ii]==1){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_offense_state_migiude[ii]==2){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_offense_state_migiude[ii]==3){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_offense_state_migiude[ii]==4){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
						}
						//自分左腕
						if (deep_offense_state_hidariude[ii]==0){
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_offense_state_hidariude[ii]==1){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_offense_state_hidariude[ii]==2){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_offense_state_hidariude[ii]==3){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_offense_state_hidariude[ii]==4){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
						}
						//相手右腕
						if (deep_defense_state_migiude[ii]==0){
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_defense_state_migiude[ii]==1){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_defense_state_migiude[ii]==2){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_defense_state_migiude[ii]==3){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_defense_state_migiude[ii]==4){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
						}
						//相手左腕
						if (deep_defense_state_hidariude[ii]==0){
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_defense_state_hidariude[ii]==1){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_defense_state_hidariude[ii]==2){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_defense_state_hidariude[ii]==3){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if(deep_defense_state_hidariude[ii]==4){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
						}
		//項目
						//土俵上での位置-4～+4、0が土俵中央、-4で東力士OUTで東の負け、+4で西力士OUTで西の負け
						//勝ったのが東か西かによって変換し-4でout、+4で勝ちに統一した後、onehotに→-3～+3の7種類
						if (deep_winhigasiornisi==2){
							deep_state_ichi[ii]*=-1;
						}
						if (deep_state_ichi[ii]==-3){
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if (deep_state_ichi[ii]==-2){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if (deep_state_ichi[ii]==-1){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if (deep_state_ichi[ii]==0){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if (deep_state_ichi[ii]==1){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if (deep_state_ichi[ii]==2){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if (deep_state_ichi[ii]==3){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
						}
						if (deep_winhigasiornisi==2){
							//元に戻す
							deep_state_ichi[ii]*=-1;
						}
		//項目
						//距離（間合い）→3種類
						//int FAR_STATE_KYORI=0;
						//int MIDDLE_STATE_KYORI=1;
						//int NEAR_STATE_KYORI=2;
						if (deep_state_kyori[ii]==0){
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if (deep_state_kyori[ii]==1){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
						}else if (deep_state_kyori[ii]==2){
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=0.0;inputcount++;
							atai_input[inputcount]=1.0;inputcount++;
						}
		//項目
						//圧力前後
						int MAE_ACTION_ZENGO=0;
						int NASI_ACTION_ZENGO=1;
						int USIRO_ACTION_ZENGO=2;
						if (deep_defense_action_zengo[ii]==0){
							atai_input[inputcount]=1.0;inputcount++;
						}else{
							atai_input[inputcount]=0.0;inputcount++;
						}
		//項目
						//turncountの代用でdeep_wazacountすなわちここではii
						atai_input[inputcount]=((double)(ii))/99.0;inputcount++;

		//項目
						//label立会狙い5+立会勢い4はすべて0.0
						for (labelcount=0;labelcount<9;labelcount++){
							label_input[labelcount]=0.0;
						}
						labelcount=9;
		//項目
						//label選択技22種類-技なし-中間＝20種類(1,2,4~21)
						if (deep_wazaid_sentaku[ii]==1){
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==2){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==4){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==5){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==6){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==7){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==8){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==9){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==10){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==11){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==12){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==13){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==14){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==15){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==16){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==17){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==18){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==19){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==20){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
						}else if (deep_wazaid_sentaku[ii]==21){
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=0.0;labelcount++;
							label_input[labelcount]=1.0;labelcount++;
						}
		//項目
						//技選択時の出力と誤差逆伝播(学習)
						deep_output();
						if (deep_wazaid_sentaku[ii]==1 || deep_wazaid_sentaku[ii]==2){
							deep_study(0,1);//技の学習なら0を渡す、その次は間合いが遠いときは1
						}else{
							deep_study(0,0);//技の学習なら0を渡す、その次は間合いが遠いときは1
						}
					}//if (deep_wazaid_sentaku[ii]>0 && deep_wazaid_sentaku[ii]<22 && deep_wazaid_sentaku[ii]!=3の終わり括弧
				}//勝った方だけ学ぶif終端
			}//for (ii=0;ii<deep_wazacount;ii++){//video_suu[i]はその取組の記録コマ数
		}//カンストになってない取組だけ
	}//if (deep_winid!=999){


	return;
}

void deep_shokika(void){
	int Ninputunit=0;int Nhiddenunit=0;int Noutputunit=0;
	//重みと閾値をランダムで初期化
	randommax_omomi=0.1;
	randommin_omomi=-0.1;
	randommax_sikiiti=0.1;
	randommin_sikiiti=-0.1;
	for (Ninputunit=0;Ninputunit<INPUTSUU;Ninputunit++){
		for (Nhiddenunit=0;Nhiddenunit<HIDDENSUU;Nhiddenunit++){
			omomi_input_hidden[Ninputunit][Nhiddenunit]=(randommax_omomi - randommin_omomi) * genrand_real3() + randommin_omomi;
		}
	}
	for (Nhiddenunit=0;Nhiddenunit<HIDDENSUU;Nhiddenunit++){
		for (Noutputunit=0;Noutputunit<OUTPUTSUU;Noutputunit++){
			omomi_hidden_output[Nhiddenunit][Noutputunit]=(randommax_omomi - randommin_omomi) * genrand_real3() + randommin_omomi;
		}
	}
	for (Nhiddenunit=0;Nhiddenunit<HIDDENSUU;Nhiddenunit++){
		sikiiti_hidden[Nhiddenunit]=(randommax_sikiiti - randommin_sikiiti) * genrand_real3() + randommin_sikiiti;
	}
	for (Noutputunit=0;Noutputunit<OUTPUTSUU;Noutputunit++){
		sikiiti_output[Noutputunit]=(randommax_sikiiti - randommin_sikiiti) * genrand_real3() + randommin_sikiiti;
	}
	return;
}

void deep_output(void){
	int Ninputunit=0;int Nhiddenunit=0;int Noutputunit=0;
	double unitsum=0.0;double softmax_max=0.0;double softmax_expsum=0.0;
	//隠れ層の出力処理sigmoid
	for (Nhiddenunit=0;Nhiddenunit<HIDDENSUU;Nhiddenunit++){
		unitsum=sikiiti_hidden[Nhiddenunit];
		for (Ninputunit=0;Ninputunit<INPUTSUU;Ninputunit++){
			unitsum += atai_input[Ninputunit] * omomi_input_hidden[Ninputunit][Nhiddenunit];
		}
		//シグモイド関数呼び出し
		if (unitsum<-500){
			unitsum=0.0;
		}else if (unitsum>500){
			unitsum=1.0;
		}else{
			unitsum=sigmoid(unitsum);
		}
		atai_hidden[Nhiddenunit]=unitsum;
		//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	//出力層sigmoid
	for (Noutputunit=0;Noutputunit<OUTPUTSUU;Noutputunit++){
		unitsum=sikiiti_output[Noutputunit];
		for (Nhiddenunit=0;Nhiddenunit<HIDDENSUU;Nhiddenunit++){
			unitsum += atai_hidden[Nhiddenunit] * omomi_hidden_output[Nhiddenunit][Noutputunit];
		}
		//シグモイド関数呼び出し
		if (unitsum<-500){
			unitsum=0.0;
		}else if (unitsum>500){
			unitsum=1.0;
		}else{
			unitsum=sigmoid(unitsum);
		}
		atai_output[Noutputunit]=unitsum;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	return;
}

void deep_study(char tatiaiflag,char kyorifarflag){//tatiaiflagが１のときは立合いの学習、0は技の学習、kyorifarflagが1のときは間合いが遠いときの技の学習
	int Ninputunit=0;int Nhiddenunit=0;int Noutputunit=0;
	double x1=0.0;double atai_max=0.0; int ataimax_unitnum=0;double label_max=0.0; int labelmax_unitnum=0;
	//学習率調整
	//eta=0.001;
	/*if (tatiaiflag==1){
		eta=0.01;
	}else{
		if (deep_wazacount>10){
			eta=1.0/(deep_wazacount*10.0);
		}else{
			eta=0.01;
		}
	}*/
	//学習達成度の確認のための誤差（感覚的にわかりやすい絶対値誤差で）
	if (tatiaiflag==1){
		for (Noutputunit=0;Noutputunit<OUTPUTSUU;Noutputunit++){
			gosatotal_tatiai+=fabs(label_input[Noutputunit]-atai_output[Noutputunit]);
		}
	}else{
		for (Noutputunit=0;Noutputunit<OUTPUTSUU;Noutputunit++){
			gosatotal_waza+=fabs(label_input[Noutputunit]-atai_output[Noutputunit]);
		}
	}
	//学習達成度の確認のためのmax値での正解率算出のためのあたりの数
	if (tatiaiflag==1){
		//立合い狙い
		atai_max=-1000000.0;label_max=-1000000.0;
		for (Noutputunit=0;Noutputunit<5;Noutputunit++){
			if (atai_max<atai_output[Noutputunit]){
				atai_max=atai_output[Noutputunit];
				ataimax_unitnum=Noutputunit;
			}
			if (label_max<label_input[Noutputunit]){
				label_max=label_input[Noutputunit];
				labelmax_unitnum=Noutputunit;
			}
		}
		if (ataimax_unitnum==labelmax_unitnum) ataritotal_tatiai_nerai++;
		//立合い勢い
		atai_max=-1000000.0;label_max=-1000000.0;
		for (Noutputunit=5;Noutputunit<9;Noutputunit++){
			if (atai_max<atai_output[Noutputunit]){
				atai_max=atai_output[Noutputunit];
				ataimax_unitnum=Noutputunit;
			}
			if (label_max<label_input[Noutputunit]){
				label_max=label_input[Noutputunit];
				labelmax_unitnum=Noutputunit;
			}
		}
		if (ataimax_unitnum==labelmax_unitnum) ataritotal_tatiai_power++;
	}else{
		if (kyorifarflag==1){//間合いが遠いときの技
			atai_max=-1000000.0;label_max=-1000000.0;
			for (Noutputunit=9;Noutputunit<11;Noutputunit++){
				if (atai_max<atai_output[Noutputunit]){
					atai_max=atai_output[Noutputunit];
					ataimax_unitnum=Noutputunit;
				}
				if (label_max<label_input[Noutputunit]){
					label_max=label_input[Noutputunit];
					labelmax_unitnum=Noutputunit;
				}
			}
			if (ataimax_unitnum==labelmax_unitnum) ataritotal_waza_far++;
			deep_wazacount_far++;
		}else{//間合いが近いときの技
			atai_max=-1000000.0;label_max=-1000000.0;
			for (Noutputunit=11;Noutputunit<29;Noutputunit++){
				if (atai_max<atai_output[Noutputunit]){
					atai_max=atai_output[Noutputunit];
					ataimax_unitnum=Noutputunit;
				}
				if (label_max<label_input[Noutputunit]){
					label_max=label_input[Noutputunit];
					labelmax_unitnum=Noutputunit;
				}
			}
			if (ataimax_unitnum==labelmax_unitnum) ataritotal_waza_near++;
			deep_wazacount_near++;
		}
	}
	//////誤差逆伝播///////////
	//出力層での誤差softmax+交差エントロピー誤差もしくはsigmoid+交差エントロピー
	for (Noutputunit=0;Noutputunit<OUTPUTSUU;Noutputunit++){
		back_output[Noutputunit]=label_input[Noutputunit]-atai_output[Noutputunit];
	}
	//中間層での誤差sigmoid
	for (Nhiddenunit=0;Nhiddenunit<HIDDENSUU;Nhiddenunit++){
		x1=0.0;
		for (Noutputunit=0;Noutputunit<OUTPUTSUU;Noutputunit++){
			x1 += back_output[Noutputunit] * omomi_hidden_output[Nhiddenunit][Noutputunit];
		}
		back_hidden[Nhiddenunit] = atai_hidden[Nhiddenunit] * (1.0-atai_hidden[Nhiddenunit]) * x1;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//隠れ層から出力層の重み修正
	for (Nhiddenunit=0;Nhiddenunit<HIDDENSUU;Nhiddenunit++){
		for (Noutputunit=0;Noutputunit<OUTPUTSUU;Noutputunit++){
			x1 = eta * atai_hidden[Nhiddenunit] * back_output[Noutputunit];
			omomi_hidden_output[Nhiddenunit][Noutputunit] += x1;
		}
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//入力層から隠れ層の重み修正
	for (Ninputunit=0;Ninputunit<INPUTSUU;Ninputunit++){
		for (Nhiddenunit=0;Nhiddenunit<HIDDENSUU;Nhiddenunit++){
			x1 = eta * atai_input[Ninputunit] * back_hidden[Nhiddenunit];
			omomi_input_hidden[Ninputunit][Nhiddenunit] += x1;
		}
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	//出力層のバイアス修正
	for (Noutputunit=0;Noutputunit<OUTPUTSUU;Noutputunit++){
		x1 = eta * back_output[Noutputunit];
		sikiiti_output[Noutputunit] += x1;
	}
	//隠れ層のバイアス修正
	for (Nhiddenunit=0;Nhiddenunit<HIDDENSUU;Nhiddenunit++){
		x1 = eta * back_hidden[Nhiddenunit];
		sikiiti_hidden[Nhiddenunit] += x1;
	}
	//if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	return;
}


void deep_tatiaidainyuu(void){

	deep_higasi_tatiai_power=higasi_tatiai_power;
	deep_nisi_tatiai_power=nisi_tatiai_power;
	deep_higasi_tatiai_nerai=higasi_tatiai_nerai;
	deep_nisi_tatiai_nerai=nisi_tatiai_nerai;

	return;
}

void deep_wazachokuzendainyuu(void){
	deep_offenseid[deep_wazacount]=offenseid;
	deep_defenseid[deep_wazacount]=defenseid;
	//deep_offense_stamina[deep_wazacount]=offense_stamina;
	//deep_defense_stamina[deep_wazacount]=defense_stamina;
	deep_defense_action_zengo[deep_wazacount]=defense_action_zengo;//defense_action_zengo
	deep_state_ichi[deep_wazacount]=state_ichi;//state_ichi
	deep_state_kyori[deep_wazacount]=state_kyori;//state_kyori
	deep_offense_state_jouge[deep_wazacount]=offense_state_jouge;//offense_state_jouge
	deep_defense_state_jouge[deep_wazacount]=defense_state_jouge;//defense_state_jouge
	deep_offense_state_balance[deep_wazacount]=offense_state_balance;//offense_state_balance
	deep_defense_state_balance[deep_wazacount]=defense_state_balance;//defense_state_balance
	deep_offense_state_migiude[deep_wazacount]=offense_state_migiude;//offense_state_migiude
	deep_defense_state_migiude[deep_wazacount]=defense_state_migiude;//defense_state_migiude
	deep_offense_state_hidariude[deep_wazacount]=offense_state_hidariude;//offense_state_hidariude
	deep_defense_state_hidariude[deep_wazacount]=defense_state_hidariude;//defense_state_hidariude

	return;
}

void deep_wazadainyuu(int wazaid_sentaku){

	deep_wazaid_sentaku[deep_wazacount]=wazaid_sentaku;//wazaid_sentakuだけどイレギュラー処理は違うかも

	//立合い後に技を出すようになってからは加算処理→turncount++のところにもっていった
	/*if (deep_wazacount<99){
		deep_wazacount++;
	}*/

	return;
}

int deep_sentaku_tatiai_nerai(int jibunid,int aiteid){
	int i=0;int ii=0;double temp_ataimax=0.0;int temp_kotaemax=0;
	int inputcount=0;
//項目
		//atai_inputに能力値代入37種類(intiki、mahou、バランス調整も適用後の能力値)
		inputcount=0;
		atai_input[inputcount]=(rikisidata[jibunid].sinchou-170.0)/50.0;inputcount++;
		atai_input[inputcount]=(rikisidata[jibunid].taijuu-70.0)/180.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].sekkyokusei/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].binshousei/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].tossinryoku/99.0;inputcount++;
		atai_input[inputcount]=(rikisidata[jibunid].kerutikara-100.0)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migiwanryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidariwanryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].balance/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].tatiaigijutu/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].tuki/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migiwakikatasa/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidariwakikatasa/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].ategai/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migikaesi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidarikaesi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migisibori/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidarisibori/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migikakaekomi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidarikakaekomi/99.0;inputcount++;
		atai_input[inputcount]=(rikisidata[jibunid].hikituke-100.0)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migiakuryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidariakuryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].stamina/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].konjou/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].nebari/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].asihakobi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].juunansei/99.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;//atai_input[inputcount]=(100-rikisidata[jibunid].zunou)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migiuwatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidariuwatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migisitatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidarisitatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migikotenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidarikotenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migisukuinage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidarisukuinage/99.0;inputcount++;
//項目
		//能力値代入負けた方37種類(intiki、mahou、バランス調整も適用後の能力値)
		atai_input[inputcount]=(rikisidata[aiteid].sinchou-170.0)/50.0;inputcount++;
		atai_input[inputcount]=(rikisidata[aiteid].taijuu-70.0)/180.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].sekkyokusei/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].binshousei/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].tossinryoku/99.0;inputcount++;
		atai_input[inputcount]=(rikisidata[aiteid].kerutikara-100.0)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migiwanryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidariwanryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].balance/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].tatiaigijutu/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].tuki/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migiwakikatasa/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidariwakikatasa/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].ategai/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migikaesi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidarikaesi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migisibori/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidarisibori/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migikakaekomi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidarikakaekomi/99.0;inputcount++;
		atai_input[inputcount]=(rikisidata[aiteid].hikituke-100.0)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migiakuryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidariakuryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].stamina/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].konjou/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].nebari/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].asihakobi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].juunansei/99.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;//atai_input[inputcount]=(100-rikisidata[aiteid].zunou)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migiuwatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidariuwatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migisitatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidarisitatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migikotenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidarikotenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migisukuinage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidarisukuinage/99.0;inputcount++;
//項目
		//立会だよという列のフラグに1を代入
		atai_input[inputcount]=1.0;inputcount++;
//項目
		//立合い時は残りのinput（立合い後の状況）はすべて0.0
		for (ii=inputcount;ii<INPUTSUU;ii++){//video_suu[i]はその取組の記録コマ数
			atai_input[ii]=0.0;
		}

		//立会時の出力
		deep_output();


//項目
		//立会い狙い5種類 勝った方だけ
		//int TUKIOSI_TATIAI_NERAI=0;
		//int MIGIYOTU_TATIAI_NERAI=1;
		//int HIDARIYOTU_TATIAI_NERAI=2;
		//int RYOUUWATE_TATIAI_NERAI=3;
		//int MOROZASI_TATIAI_NERAI=4;
	{
		int shuruisuu=0;int minid=0;int maxid=0;
		int count=0;int i=0;
		//0~4の5種類
		shuruisuu=5;minid=0;maxid=4;
		i=GetRand(shuruisuu-1)+minid;
		temp_ataimax=-10000000.0;
		while(1){
			if (temp_ataimax<atai_output[i]){
				temp_ataimax=atai_output[i];
				temp_kotaemax=i;
			}
			count++;
			i++;
			if (count>=shuruisuu) break;
			if (i>maxid){
				i=minid;
			}
		}
		temp_kotaemax-=minid;
	}
	/*{//負けないためにmin値を取る
		int shuruisuu=0;int minid=0;int maxid=0;
		int count=0;int i=0;
		//0~4の5種類
		shuruisuu=5;minid=0;maxid=4;
		i=GetRand(shuruisuu-1)+minid;
		temp_ataimax=10000000.0;
		while(1){
			if (temp_ataimax>atai_output[i]){
				temp_ataimax=atai_output[i];
				temp_kotaemax=i;
			}
			count++;
			i++;
			if (count>=shuruisuu) break;
			if (i>maxid){
				i=minid;
			}
		}
		//変換
		temp_kotaemax-=minid;
	}*/

		//if (temp_ataimax<0.1){//やたら低いなら
		//	temp_kotaemax=GetRand(4);
		//}

//項目
		//立会い勢い4種類 勝った方だけ
		//int ZENRYOKU_TATIAI_POWER=0;
		//int NORMAL_TATIAI_POWER=1;
		//int UKERU_TATIAI_POWER=2;
		//int HENKA_TATIAI_POWER=3;
		
		//

	return temp_kotaemax;
}

int deep_sentaku_tatiai_power(int jibunid,int aiteid){
	int i=0;int ii=0;double temp_ataimax=0.0;int temp_kotaemax=0;
	int inputcount=0;
//項目
		//atai_inputに能力値代入37種類(intiki、mahou、バランス調整も適用後の能力値)
		inputcount=0;
		atai_input[inputcount]=(rikisidata[jibunid].sinchou-170.0)/50.0;inputcount++;
		atai_input[inputcount]=(rikisidata[jibunid].taijuu-70.0)/180.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].sekkyokusei/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].binshousei/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].tossinryoku/99.0;inputcount++;
		atai_input[inputcount]=(rikisidata[jibunid].kerutikara-100.0)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migiwanryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidariwanryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].balance/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].tatiaigijutu/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].tuki/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migiwakikatasa/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidariwakikatasa/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].ategai/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migikaesi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidarikaesi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migisibori/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidarisibori/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migikakaekomi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidarikakaekomi/99.0;inputcount++;
		atai_input[inputcount]=(rikisidata[jibunid].hikituke-100.0)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migiakuryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidariakuryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].stamina/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].konjou/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].nebari/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].asihakobi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].juunansei/99.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;//atai_input[inputcount]=(100-rikisidata[jibunid].zunou)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migiuwatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidariuwatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migisitatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidarisitatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migikotenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidarikotenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].migisukuinage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[jibunid].hidarisukuinage/99.0;inputcount++;
//項目
		//能力値代入負けた方37種類(intiki、mahou、バランス調整も適用後の能力値)
		atai_input[inputcount]=(rikisidata[aiteid].sinchou-170.0)/50.0;inputcount++;
		atai_input[inputcount]=(rikisidata[aiteid].taijuu-70.0)/180.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].sekkyokusei/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].binshousei/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].tossinryoku/99.0;inputcount++;
		atai_input[inputcount]=(rikisidata[aiteid].kerutikara-100.0)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migiwanryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidariwanryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].balance/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].tatiaigijutu/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].tuki/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migiwakikatasa/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidariwakikatasa/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].ategai/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migikaesi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidarikaesi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migisibori/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidarisibori/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migikakaekomi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidarikakaekomi/99.0;inputcount++;
		atai_input[inputcount]=(rikisidata[aiteid].hikituke-100.0)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migiakuryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidariakuryoku/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].stamina/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].konjou/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].nebari/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].asihakobi/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].juunansei/99.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;//atai_input[inputcount]=(100-rikisidata[aiteid].zunou)/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migiuwatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidariuwatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migisitatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidarisitatenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migikotenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidarikotenage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].migisukuinage/99.0;inputcount++;
		atai_input[inputcount]=rikisidata[aiteid].hidarisukuinage/99.0;inputcount++;
//項目
		//立会だよという列のフラグに1を代入
		atai_input[inputcount]=1.0;inputcount++;
//項目
		//立合い時は残りのinput（立合い後の状況）はすべて0.0
		for (ii=inputcount;ii<INPUTSUU;ii++){//video_suu[i]はその取組の記録コマ数
			atai_input[ii]=0.0;
		}

		//立会時の出力
		deep_output();

//項目
		//立会い狙い5種類 勝った方だけ
		//int TUKIOSI_TATIAI_NERAI=0;
		//int MIGIYOTU_TATIAI_NERAI=1;
		//int HIDARIYOTU_TATIAI_NERAI=2;
		//int RYOUUWATE_TATIAI_NERAI=3;
		//int MOROZASI_TATIAI_NERAI=4;

//項目
		//立会い勢い4種類 勝った方だけ
		//int ZENRYOKU_TATIAI_POWER=0;
		//int NORMAL_TATIAI_POWER=1;
		//int UKERU_TATIAI_POWER=2;
		//int HENKA_TATIAI_POWER=3;
	{
		int shuruisuu=0;int minid=0;int maxid=0;
		int count=0;int i=0;
		//5~8の4種類
		shuruisuu=4;minid=5;maxid=8;
		i=GetRand(shuruisuu-1)+minid;
		temp_ataimax=-10000000.0;
		while(1){
			if (temp_ataimax<atai_output[i]){
				temp_ataimax=atai_output[i];
				temp_kotaemax=i;
			}
			count++;
			i++;
			if (count>=shuruisuu) break;
			if (i>maxid){
				i=minid;
			}
		}
		//変換
		temp_kotaemax-=minid;
	}
	/*{//負けないためにmin値をとる
		int shuruisuu=0;int minid=0;int maxid=0;
		int count=0;int i=0;
		//5~8の4種類
		shuruisuu=4;minid=5;maxid=8;
		i=GetRand(shuruisuu-1)+minid;
		temp_ataimax=10000000.0;
		while(1){
			if (temp_ataimax>atai_output[i]){
				temp_ataimax=atai_output[i];
				temp_kotaemax=i;
			}
			count++;
			i++;
			if (count>=shuruisuu) break;
			if (i>maxid){
				i=minid;
			}
		}
		//変換
		temp_kotaemax-=minid;
	}*/

		//if (temp_ataimax<0.1){//やたら低いなら
		//	temp_kotaemax=GetRand(3)+5;
		//}

	return temp_kotaemax;
}

int deep_sentaku_waza(int jibunid,int aiteid,int offensehigasiornisi){
	int i=0;int ii=0;double temp_ataimax=0.0;int temp_kotaemax=0;
	int inputcount=0;int labelcount=0;
//項目
	//atai_inputに能力値代入37種類(intiki、mahou、バランス調整も適用後の能力値)
	inputcount=0;
	atai_input[inputcount]=(rikisidata[jibunid].sinchou-170.0)/50.0;inputcount++;
	atai_input[inputcount]=(rikisidata[jibunid].taijuu-70.0)/180.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].sekkyokusei/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].binshousei/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].tossinryoku/99.0;inputcount++;
	atai_input[inputcount]=(rikisidata[jibunid].kerutikara-100.0)/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].migiwanryoku/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].hidariwanryoku/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].balance/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].tatiaigijutu/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].tuki/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].migiwakikatasa/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].hidariwakikatasa/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].ategai/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].migikaesi/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].hidarikaesi/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].migisibori/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].hidarisibori/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].migikakaekomi/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].hidarikakaekomi/99.0;inputcount++;
	atai_input[inputcount]=(rikisidata[jibunid].hikituke-100.0)/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].migiakuryoku/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].hidariakuryoku/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].stamina/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].konjou/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].nebari/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].asihakobi/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].juunansei/99.0;inputcount++;
	atai_input[inputcount]=0.0;inputcount++;//atai_input[inputcount]=(100-rikisidata[jibunid].zunou)/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].migiuwatenage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].hidariuwatenage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].migisitatenage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].hidarisitatenage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].migikotenage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].hidarikotenage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].migisukuinage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[jibunid].hidarisukuinage/99.0;inputcount++;
//項目
	//能力値代入負けた方37種類(intiki、mahou、バランス調整も適用後の能力値)
	atai_input[inputcount]=(rikisidata[aiteid].sinchou-170.0)/50.0;inputcount++;
	atai_input[inputcount]=(rikisidata[aiteid].taijuu-70.0)/180.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].sekkyokusei/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].binshousei/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].tossinryoku/99.0;inputcount++;
	atai_input[inputcount]=(rikisidata[aiteid].kerutikara-100.0)/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].migiwanryoku/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].hidariwanryoku/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].balance/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].tatiaigijutu/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].tuki/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].migiwakikatasa/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].hidariwakikatasa/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].ategai/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].migikaesi/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].hidarikaesi/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].migisibori/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].hidarisibori/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].migikakaekomi/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].hidarikakaekomi/99.0;inputcount++;
	atai_input[inputcount]=(rikisidata[aiteid].hikituke-100.0)/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].migiakuryoku/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].hidariakuryoku/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].stamina/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].konjou/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].nebari/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].asihakobi/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].juunansei/99.0;inputcount++;
	atai_input[inputcount]=0.0;inputcount++;//atai_input[inputcount]=(100-rikisidata[aiteid].zunou)/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].migiuwatenage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].hidariuwatenage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].migisitatenage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].hidarisitatenage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].migikotenage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].hidarikotenage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].migisukuinage/99.0;inputcount++;
	atai_input[inputcount]=rikisidata[aiteid].hidarisukuinage/99.0;inputcount++;
//項目
	//立会だよという列のフラグに0を代入
	atai_input[inputcount]=0.0;inputcount++;

//項目
	//上体の上下3種類*自分と相手で2＝6
	//int HIGH_STATE_JOUGE=0;
	//int MIDDLE_STATE_JOUGE=1;
	//int LOW_STATE_JOUGE=2;
	//自分の上体
	if (offense_state_jouge==0){
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if (offense_state_jouge==1){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if (offense_state_jouge==2){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
	}
	//相手の上体
	if (defense_state_jouge==0){
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if (defense_state_jouge==1){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if (defense_state_jouge==2){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
	}
//項目
	//バランス、10がMAXで、0で倒れて負け→10で割って0.0～1.0の数値に変換*自分と相手で2＝2
	//自分のバランス
	atai_input[inputcount]=((double)(offense_state_balance))/10.0;inputcount++;
	//相手のバランス
	atai_input[inputcount]=((double)(defense_state_balance))/10.0;inputcount++;
//項目
	//腕の状態（上手か下手か、廻しの有無）5種類*自分と相手で2*右腕左腕で2＝20
	//int MAE_STATE_UDE=0;//間合いが近くない場合
	//int UWATE_STATE_UDE=1;
	//int SITATE_STATE_UDE=2;
	//int UWATETUKAMI_STATE_UDE=3;
	//int SITATETUKAMI_STATE_UDE=4;
	//自分右腕
	if (offense_state_migiude==0){
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(offense_state_migiude==1){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(offense_state_migiude==2){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(offense_state_migiude==3){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(offense_state_migiude==4){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
	}
	//自分左腕
	if (offense_state_hidariude==0){
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(offense_state_hidariude==1){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(offense_state_hidariude==2){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(offense_state_hidariude==3){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(offense_state_hidariude==4){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
	}
	//相手右腕
	if (defense_state_migiude==0){
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(defense_state_migiude==1){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(defense_state_migiude==2){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(defense_state_migiude==3){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(defense_state_migiude==4){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
	}
	//相手左腕
	if (defense_state_hidariude==0){
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(defense_state_hidariude==1){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(defense_state_hidariude==2){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(defense_state_hidariude==3){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if(defense_state_hidariude==4){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
	}
//項目
	//土俵上での位置-4～+4、0が土俵中央、-4で東力士OUTで東の負け、+4で西力士OUTで西の負け
	//攻撃が東か西かによって変換し-4でout、+4で勝ちに統一した後、onehotに→-3～+3の7種類
	if (offensehigasiornisi==2){
		state_ichi*=-1;
	}
	if (state_ichi==-3){
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if (state_ichi==-2){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if (state_ichi==-1){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if (state_ichi==0){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if (state_ichi==1){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if (state_ichi==2){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if (state_ichi==3){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
	}
	if (offensehigasiornisi==2){
		//元に戻す
		state_ichi*=-1;
	}
//項目
	//距離（間合い）→3種類
	//int FAR_STATE_KYORI=0;
	//int MIDDLE_STATE_KYORI=1;
	//int NEAR_STATE_KYORI=2;
	if (state_kyori==0){
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if (state_kyori==1){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
	}else if (state_kyori==2){
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=0.0;inputcount++;
		atai_input[inputcount]=1.0;inputcount++;
	}
//項目
	//圧力前後
	//int MAE_ACTION_ZENGO=0;
	//int NASI_ACTION_ZENGO=1;
	//int USIRO_ACTION_ZENGO=2;
	if (defense_action_zengo==0){
		atai_input[inputcount]=1.0;inputcount++;
	}else{
		atai_input[inputcount]=0.0;inputcount++;
	}

//項目
	//turncountの代用でdeep_wazacount
	atai_input[inputcount]=((double)(deep_wazacount))/99.0;inputcount++;

	//出力
	deep_output();

//項目
	//label立会狙い5+立会勢い4はすべて0.0
//項目
	//label選択技22種類-技なし-中間＝20種類(1,2,4~21)
	temp_ataimax=-10000000.0;
	if (state_kyori==0){//FAR_STATE_KYORIなら
		int shuruisuu=0;int minid=0;int maxid=0;
		int count=0;int i=0;
		//9~10の2種類
		shuruisuu=2;minid=9;maxid=10;
		i=GetRand(shuruisuu-1)+minid;
		temp_ataimax=-10000000.0;
		while(1){
			if (temp_ataimax<atai_output[i]){
				temp_ataimax=atai_output[i];
				temp_kotaemax=i;
			}
			count++;
			i++;
			if (count>=shuruisuu) break;
			if (i>maxid){
				i=minid;
			}
		}
		/*//9~10の2種類//負けないためにmin値をとる
		shuruisuu=2;minid=9;maxid=10;
		i=GetRand(shuruisuu-1)+minid;
		temp_ataimax=10000000.0;
		while(1){
			if (temp_ataimax>atai_output[i]){
				temp_ataimax=atai_output[i];
				temp_kotaemax=i;
			}
			count++;
			i++;
			if (count>=shuruisuu) break;
			if (i>maxid){
				i=minid;
			}
		}*/
		//wazaidに変換
		temp_kotaemax-=8;
	}else if(state_kyori==1){//MIDDLE_STATE_KYORI飛んでこないはずなのだけど念のため
		temp_kotaemax=3;//中間処理
	}else{//NEAR_STATE_KYORI
		int shuruisuu=0;int minid=0;int maxid=0;
		int count=0;int i=0;
		//11~28の18種類
		shuruisuu=18;minid=11;maxid=28;
		i=GetRand(shuruisuu-1)+minid;
		temp_ataimax=-10000000.0;
		while(1){
			if (temp_ataimax<atai_output[i]){
				temp_ataimax=atai_output[i];
				temp_kotaemax=i;
			}
			count++;
			i++;
			if (count>=shuruisuu) break;
			if (i>maxid){
				i=minid;
			}
		}
		/*//11~28の18種類//負けないためにmin値をとる
		shuruisuu=18;minid=11;maxid=28;
		i=GetRand(shuruisuu-1)+minid;
		temp_ataimax=10000000.0;
		while(1){
			if (temp_ataimax>atai_output[i]){
				if (damewazahandan(i-7)!=-1){//-1が返るときはあり得ない技
					temp_ataimax=atai_output[i];
					temp_kotaemax=i;
				}
			}
			count++;
			i++;
			if (count>=shuruisuu) break;
			if (i>maxid){
				i=minid;
			}
		}*/
		//wazaidに変換
		temp_kotaemax-=7;
		/*//組手廻しの有無からありえない技の選択を避ける処理
		if (damewazahandan(temp_kotaemax)==-1){//-1が返るときはあり得ない技
			int loopcount=0;
			for (loopcount=0;loopcount<10000;loopcount++){//念のため無限ループ回避
				temp_kotaemax=GetRand(17)+4;
				if (damewazahandan(temp_kotaemax)!=-1){//-1が返るときはあり得ない技
					break;
				}
			}
		}*/
	}

	return temp_kotaemax;
}

int damewazahandan(int temp_wazaid){//組手廻しの有無であり得ない技の場合は-1が返る
	int yotu=0;int jibunmigimawasi=0;int jibunhidarimawasi=0;int aitemigimawasi=0;int aitehidarimawasi=0;int joutaiflag=0;
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
	//if (defense_action_zengo==NASI_ACTION_ZENGO
	//	|| (defense_state_balance<(int)(rikisidata[defenseid].balance/10)+1
	//			 && defense_state_balance<6)){//前に圧力がかかっていない状態か大きくバランスを崩した状態
	//	joutaiflag=3;//
	//}else if (offense_state_jouge>defense_state_jouge){//自低
	//	joutaiflag=2;//
	//}else if (offense_state_jouge==defense_state_jouge){//自低
		joutaiflag=1;//
	//}else{
	//	joutaiflag=0;//
	//}

	return aidata_fichi[temp_wazaid][yotu][jibunmigimawasi][jibunhidarimawasi][aitemigimawasi][aitehidarimawasi][joutaiflag];
}
