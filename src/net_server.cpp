#include "DxLib.h"
#include <stdio.h>
#include "define.h"

extern int rikisi_higasi;//東力士画像
extern int rikisi_nisi;//西力士画像
extern int rikisi_high;//力士画像(上半身高)
extern int rikisi_middle;//力士画像(上半身中)
extern int rikisi_low;//力士画像(上半身低)
extern int rikisi_high_nisi;//力士画像(上半身高)
extern int rikisi_middle_nisi;//力士画像(上半身中)
extern int rikisi_low_nisi;//力士画像(上半身低)
extern int rikisi_lostbalance;//東力士画像(バランスロスト)
extern int rikisi_lostbalance_nisi;//東力士画像(バランスロスト)
extern int rikisi_lostbalance2;//東力士画像(バランスロスト)
extern int rikisi_lostbalance2_nisi;//東力士画像(バランスロスト)
extern int rikisi_high_megaten;//力士画像(上半身高)
extern int rikisi_middle_megaten;//力士画像(上半身中)
extern int rikisi_low_megaten;//力士画像(上半身低)
extern int rikisi_high_nisi_megaten;//力士画像(上半身高)
extern int rikisi_middle_nisi_megaten;//力士画像(上半身中)
extern int rikisi_low_nisi_megaten;//力士画像(上半身低)
extern int rikisihyoji_megatenflag;//目が点フラグ、1＞東が目が点、2＞西が目が点

extern int hand;//東力士左手
extern int hand_mawasi;//東力士左手廻し付き
extern int atama;//東力士頭
extern int rikisi_front_higasi;//力士画像(前から)
extern int rikisi_front_nisi;

extern int ketteisenflag;//決定戦の時は左の電光掲示板を表示しないようにするためのフラグ
extern int rikisigraphflag;
extern int rikisisentaku_id;//選択された力士ID
extern int WAIT;
extern char jikkyoustring[202];//実況string(余裕を持って100文字分)
extern char kimaritestring[32];//決まり手string(余裕を持って15文字分)
extern int WAIT_NYUURYOKU;//リアルモードのときの入力待ち時間
extern int soundflag;
extern int kansei_low;
extern int kansei_middle_r;//取り組み中の効果音
extern int kansei_middle_l;
extern int kansei_high_r;
extern int kansei_high_l;
extern int rikisihyoji_megatenflag;//目が点フラグ、1＞東が目が点、2＞西が目が点

extern char matatukihanasitaflag;

extern struct jouken_data joukendata[RIKISISUU];//構造体変数力士数分用意

extern int CheckHitKey_test(int);

extern int get_mouseclick(int x1,int y1,int x2,int y2);//座標(x1,y1)と(x2,y2)に囲まれたところで

//extern char higasi_aidata[AIDATABYTESUU];
//extern char nisi_aidata[AIDATABYTESUU];
extern int ito_higasi_tatiai_power;
extern int ito_nisi_tatiai_power;

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

extern int ichi_lastturn;//→ローカル変数ですでに使っていたがグローバルにした　土俵上の位置-4～+4、0が土俵中央、-4で東力士(サーバー)OUT、+4で西力士(クライアント)OUT
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

extern int offense_stamina;
extern int defense_stamina;
extern int turncount;//取組の戦闘中のターン数
extern int kougekiken;//東方力士の攻撃＞1、西の攻撃＞2
extern int offenseid;//攻撃側力士のID
extern int defenseid;//守備側力士のID
extern int wazapatternid_higasi;//東力士(サーバー)がこの取り組みで選択した技パターンID
extern int wazapatternid_nisi;
extern int wazaid_sentaku;//力士が選択した技ID
extern int tatiaipatternid_higasi;//東力士(サーバー)がこの取り組みで選択した立会いパターンID
extern int tatiaipatternid_nisi;

extern struct rikisi_data temp_rikisidata_higasi;//取組時バランス調整前のバックアップ用
extern struct rikisi_data temp_rikisidata_nisi;//バックアップ用
extern struct rikisi_data rikisidata[RIKISISUU];
extern struct bl_data bldata;//バランス調整用
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
extern int state_ichi;//土俵上での位置-4～+4、0が土俵中央、-4で東力士(サーバー)OUT、+4で西力士(クライアント)OUT
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

void net(int id);
void net_client(int id);
void net_server(int higasiid,int nisiid);
int fight_fight_server(int higasiid,int nisiid,int NetHandle);//東が勝なら1、西が勝なら2を返す
void rikisidatahyoji_main_net(int x,int yokozure,int AITE);
struct rikisi_data temp_backup_rikisidata_nisi;//バックアップ用
struct rikisi_data temp_backup_rikisidata_higasi;//バックアップ用
struct net_data netdata;

extern void fight_backscreen_net(int higasiid,int nisiid);

void net(int id)
{
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	DrawFormatString(187,369,CRWHITE,"%sを出稽古に出しますか",namestring[id]);
	DrawString(187,369+16,"クリックで選択してください。",CRWHITE);
	DrawString(x1[0],y1[0],"やっぱりやめる",CRGREEN);
	DrawString(x1[10],y1[10],"迎え撃つ(サーバーを立てる)",CRGREEN);
	DrawString(x1[20],y1[20],"出稽古に行く",CRGREEN);
	ScreenFlip() ;//裏画面を表画面にコピー
	// キー入力待ち(この一文を入れないとうまくいかないみたい)
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
	}
	while(1)
	{
		//GetKeys();
		if( get_mouseclick_list(0) == 1 || get_mouseclick_list(1) == 1 ){//
			return;
		}
		if( get_mouseclick_list(10) == 1 || get_mouseclick_list(11) == 1 ){//
			//higasiidはサーバー側、nisiidはクライアント側なので
			//nisiidが被らないように配慮して0か1をnisiidに
			if (id==0){
				net_server(id,1);
			}else{
				net_server(id,0);
			}
			return;
		}
		if( get_mouseclick_list(20) == 1 || get_mouseclick_list(21) == 1 ){//
			net_client(id);
			return;
		}
		// メッセージ処理
		if( ProcessMessage() == -1 ){
			mode=1;
			return;	// エラーが発生したらループを抜ける
		}
		Sleep(1);
	}
	
}

void net_client(int id)
{
	char netokflag;
	int i;
	int kaeri=0;
	char StrBuf[ 256 ] ;    // データバッファ
	IPDATA Ip ;        // 接続用ＩＰアドレスデータ
	int NetHandle ;    // ネットワークハンドル
	int DataLength ;        // 受信データ量保存用変数
	int portno=9850;
	int temp_higasiid;
	char temp_namestring_higasi[12];
	for (i=0;i<12;i++){
		temp_namestring_higasi[i]=0;
	}

 	// ＩＰアドレスを設定( ここにある４つのＩＰ値は仮です )
    Ip.d1 = 127 ;
    Ip.d2 = 0 ;
    Ip.d3 = 0   ;
    Ip.d4 = 1 ;


    // 通信を確立
    NetHandle = ConnectNetWork( Ip, portno ) ;

    // 確立が成功した場合のみ中の処理をする
    if( NetHandle != -1 )
    { 
        // データ送信
		ClearDrawScreen();
        DrawString( 540,0 , "クライアント" , CRPURPLE ) ;
        DrawString( 0 , 0 , "データを送信します" , CRWHITE ) ;
        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
		ScreenFlip();
        WaitKey() ;

        NetWorkSend( NetHandle , &rikisidata[id] , sizeof(rikisidata[id]));

		ClearDrawScreen();
        DrawString( 540,0 , "クライアント" , CRPURPLE ) ;
        DrawString( 0 , 0 , "サーバーからの送信を待ってます…" , CRWHITE ) ;
		ScreenFlip();
        // データがくるのを待つ
        while( !ProcessMessage() )
        {
            // 取得していない受信データ量を得る
            DataLength = GetNetWorkDataLength( NetHandle ) ;

            // 取得してない受信データ量が０じゃない場合はループを抜ける
            if( DataLength != 0 ) break ;
			Sleep(1);
        }
        // データ受信
        DataLength = GetNetWorkDataLength( NetHandle ) ;    // データの量を取得
		if (DataLength==sizeof(temp_rikisidata_higasi)){
	        NetWorkRecv( NetHandle , &temp_rikisidata_higasi , DataLength );    // データをバッファに取得
		}else{
			ClearDrawScreen();
	        DrawString( 540,0 , "クライアント" , CRPURPLE ) ;
	        DrawString( 0 , 0 , "データ受信に失敗しました" , CRRED ) ;
	        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
			ScreenFlip();
	        WaitKey() ;
			return;
		}

        // 受信した旨を描画
		ClearDrawScreen();
        DrawString( 540,0 , "クライアント" , CRPURPLE ) ;
        DrawString( 0 , 0 , "データ受信に成功しました！！" , CRRED ) ;
        DrawString( 0 , 400 , "Hit Any Keyで取組へ" , CRWHITE ) ;
		ScreenFlip();
        WaitKey() ;


		//取り組み中のデータいじりのためのバックアップ処理
		//temp_rikisidata_higasi=rikisidata[higasiid];
		temp_rikisidata_nisi=rikisidata[id];
		if (id==0){
			temp_higasiid=1;
			temp_backup_rikisidata_higasi=rikisidata[1];
			rikisidata[1]=temp_rikisidata_higasi;
			strcpy(temp_namestring_higasi,namestring[1]);
		}else{
			temp_higasiid=0;
			temp_backup_rikisidata_higasi=rikisidata[0];
			rikisidata[0]=temp_rikisidata_higasi;
			strcpy(temp_namestring_higasi,namestring[0]);
		}

		//西力士(クライアント)の立会いパターンの選択
		{
			int nerai_nisi,ikioi_nisi;
			////////////////立合い狙い入力/////////////////////////
		HYOJI_nerai:
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			fight_backscreen_net(temp_higasiid,id);//戦闘時用画面表示
			DrawFormatString(187,369,CRWHITE,"%sの立合いの狙いを左リストから",namestring[id]);
			DrawString(187,369+16,"クリックかキー押下で選択してください。",CRWHITE);
			DrawString(187,385+75,"力士名をクリックで能力表示",CRWHITE);
			DrawFormatString(x1[0],y1[0]-32,CRWHITE,"%s",namestring[id]);
			ii=0;DrawString(x1[ii*2],y1[ii*2],"突き押し　　　8",CRGREEN);
			ii++;DrawString(x1[ii*2],y1[ii*2],"右四つ　　　　6(O)",CRGREEN);
			ii++;DrawString(x1[ii*2],y1[ii*2],"左四つ　　　　4(U)",CRGREEN);
			ii++;DrawString(x1[ii*2],y1[ii*2],"両上手　　　　5(I)",CRGREEN);
			ii++;DrawString(x1[ii*2],y1[ii*2],"両差し　　　　2(K)",CRGREEN);
			ScreenFlip() ;//裏画面を表画面にコピー
			loopderuflag=0;
			// キー入力待ち(この一文を入れないとうまくいかないみたい)
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				Sleep(1);
			}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				Sleep(1);
			}
			while(1)
			{
				//GetKeys();
				if( CheckHitKey_test(KEY_INPUT_NUMPAD8) || CheckHitKey_test(KEY_INPUT_8)){//ENTERキーでループから抜けメニュー画面へ
					nerai_nisi=0;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD6) || CheckHitKey_test(KEY_INPUT_6) || CheckHitKey_test(KEY_INPUT_O)){//ENTERキーでループから抜けメニュー画面へ
					nerai_nisi=1;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD4) || CheckHitKey_test(KEY_INPUT_4) || CheckHitKey_test(KEY_INPUT_U)){//ENTERキーでループから抜けメニュー画面へ
					nerai_nisi=2;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD5) || CheckHitKey_test(KEY_INPUT_5) || CheckHitKey_test(KEY_INPUT_I)){//ENTERキーでループから抜けメニュー画面へ
					nerai_nisi=3;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD2) || CheckHitKey_test(KEY_INPUT_2) || CheckHitKey_test(KEY_INPUT_K)){//ENTERキーでループから抜けメニュー画面へ
					nerai_nisi=4;
					break;
				}
				for(ii=0;ii<5;ii++){
					if (get_mouseclick_list(ii*2) == 1 || get_mouseclick_list(ii*2+1) == 1){//左リスト上のをクリックしたら
						nerai_nisi=ii;
						loopderuflag=1;
						break;
					}
				}
				if (loopderuflag==1){
					break;
				}

				if (get_mouseclick(187,40,187+80,40+16)==1 || get_mouseclick(411,40,411+80,40+16)==1 ){
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawBox(0,0,639,479,CRBACK,TRUE);
					rikisidatahyoji_main_net(temp_higasiid,-187,id);
					SetFontSize(16);
					if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
					rikisidatahyoji_main_net(nisiid,+172,temp_higasiid);
					SetFontSize(16);
					if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
					DrawString(0,20,"　戻る(ESCキー)",CRGREEN);
					ScreenFlip();
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
					}
					while(1)
					{
						if(get_mouseclick(0,20,16*8,20+16) == 1 || CheckHitKey_test( KEY_INPUT_ESCAPE )==1){
							goto HYOJI_nerai;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 ){
							mode=1;
							return -1;	// エラーが発生したらループを抜ける
						}
						Sleep(1);
					}
				}
				// メッセージ処理
				if( ProcessMessage() == -1 ){
					mode=1;
					return -1;	// エラーが発生したらループを抜ける
				}
				Sleep(1);
			}
			///////////////立合い狙い送信/////////////////////////
	        NetWorkSend( NetHandle , &nerai_nisi , sizeof(nerai_nisi));

			ClearDrawScreen();
	        DrawString( 540,0 , "クライアント" , CRPURPLE ) ;
	        DrawString( 0 , 0 , "サーバーからの応答を待ってます…" , CRWHITE ) ;
			ScreenFlip();
	        // ok信号データ受信
	        // データがくるのを待つ
			netokflag=0;
	        while( !ProcessMessage() )
	        {
	            // 取得していない受信データ量を得る
	            DataLength = GetNetWorkDataLength( NetHandle ) ;

	            // 取得してない受信データ量が０じゃない場合はループを抜ける
	            if( DataLength != 0 ) break ;
				Sleep(1);
	        }
	        DataLength = GetNetWorkDataLength( NetHandle ) ;    // データの量を取得
			if (DataLength==sizeof(netokflag)){
		        NetWorkRecv( NetHandle , &netokflag , DataLength );    // データをバッファに取得
				if (netokflag!=1){
					ClearDrawScreen();
			        DrawString( 540,0 , "クライアント" , CRPURPLE ) ;
			        DrawString( 0 , 0 , "受信値が異常です" , CRRED ) ;
			        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
					ScreenFlip();
			        WaitKey() ;
					return;
				}
			}else{
				ClearDrawScreen();
		        DrawString( 540,0 , "クライアント" , CRPURPLE ) ;
		        DrawString( 0 , 0 , "データ受信に失敗しました" , CRRED ) ;
		        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
				ScreenFlip();
		        WaitKey() ;
				return;
			}

			////////////////立合い勢い入力/////////////////////////
	HYOJI_ikioi:
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			fight_backscreen_net(temp_higasiid,id);//戦闘時用画面表示
			DrawFormatString(187,369,CRWHITE,"%sの立会いの勢いを左リストから",namestring[id]);
			DrawString(187,369+16,"クリックかキー押下で選択してください。",CRWHITE);
			DrawString(187,369+32,"なお、異なる立会いの勢いになる場合もあります。",CRWHITE);
			//DrawString(187,369+48,"また、全力の立会いは余計にスタミナを消費します(-10)。",CRWHITE);
			DrawString(187,385+75,"力士名をクリックで能力表示",CRWHITE);
			DrawFormatString(x1[0],y1[0]-32,CRWHITE,"%s",namestring[id]);
			ii=0;DrawString(x1[ii*2],y1[ii*2],"全力　　　　　8",CRGREEN);
			ii++;DrawString(x1[ii*2],y1[ii*2],"強く　　　　　5(I)",CRGREEN);
			ii++;DrawString(x1[ii*2],y1[ii*2],"受け　　　　　2(K)",CRGREEN);
			ii++;DrawString(x1[ii*2],y1[ii*2],"変化　　　　　0(M)",CRGREEN);
			ScreenFlip() ;//裏画面を表画面にコピー
			loopderuflag=0;
			// キー入力待ち(この一文を入れないとうまくいかないみたい)
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				Sleep(1);
			}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				Sleep(1);
			}
			while(1)
			{
				//GetKeys();
				if( CheckHitKey_test(KEY_INPUT_NUMPAD8) || CheckHitKey_test(KEY_INPUT_8)){//ENTERキーでループから抜けメニュー画面へ
					ikioi_nisi=0;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD5) || CheckHitKey_test(KEY_INPUT_5) || CheckHitKey_test(KEY_INPUT_I)){//ENTERキーでループから抜けメニュー画面へ
					ikioi_nisi=1;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD2) || CheckHitKey_test(KEY_INPUT_2) || CheckHitKey_test(KEY_INPUT_K)){//ENTERキーでループから抜けメニュー画面へ
					ikioi_nisi=2;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD0) || CheckHitKey_test(KEY_INPUT_0) || CheckHitKey_test(KEY_INPUT_M)){//ENTERキーでループから抜けメニュー画面へ
					ikioi_nisi=3;
					break;
				}
				for(ii=0;ii<4;ii++){
					if (get_mouseclick_list(ii*2) == 1 || get_mouseclick_list(ii*2+1) == 1){//左リスト上のをクリックしたら
						ikioi_nisi=ii;
						loopderuflag=1;
						break;
					}
				}
				if (loopderuflag==1){
					break;
				}
				if (get_mouseclick(187,40,187+80,40+16)==1 || get_mouseclick(411,40,411+80,40+16)==1 ){
					ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
					DrawBox(0,0,639,479,CRBACK,TRUE);
					rikisidatahyoji_main_net(temp_higasiid,-187,id);
					SetFontSize(16);
					if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
					rikisidatahyoji_main_net(id,+172,temp_higasiid);
					SetFontSize(16);
					if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
					DrawString(0,20,"　戻る(ESCキー)",CRGREEN);
					ScreenFlip();
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
					}
					while(1)
					{
						if(get_mouseclick(0,20,16*8,20+16) == 1 || CheckHitKey_test( KEY_INPUT_ESCAPE )==1){
							goto HYOJI_ikioi;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 ){
							mode=1;
							return -1;	// エラーが発生したらループを抜ける
						}
						Sleep(1);
					}
				}
				// メッセージ処理
				if( ProcessMessage() == -1 ){
					mode=1;
					return -1;	// エラーが発生したらループを抜ける
				}
				Sleep(1);
			}
			///////////////立合い勢い送信/////////////////////////
	        NetWorkSend( NetHandle , &ikioi_nisi , sizeof(ikioi_nisi));

			ClearDrawScreen();
	        DrawString( 540,0 , "クライアント" , CRPURPLE ) ;
	        DrawString( 0 , 0 , "サーバーからの応答を待ってます…" , CRWHITE ) ;
			ScreenFlip();
	        // ok信号データ受信
	        // データがくるのを待つ
			netokflag=0;
	        while( !ProcessMessage() )
	        {
	            // 取得していない受信データ量を得る
	            DataLength = GetNetWorkDataLength( NetHandle ) ;

	            // 取得してない受信データ量が０じゃない場合はループを抜ける
	            if( DataLength != 0 ) break ;
				Sleep(1);
	        }
	        DataLength = GetNetWorkDataLength( NetHandle ) ;    // データの量を取得
			if (DataLength==sizeof(netokflag)){
		        NetWorkRecv( NetHandle , &netokflag , DataLength );    // データをバッファに取得
				if (netokflag!=1){
					ClearDrawScreen();
			        DrawString( 540,0 , "クライアント" , CRPURPLE ) ;
			        DrawString( 0 , 0 , "受信値が異常です" , CRRED ) ;
			        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
					ScreenFlip();
			        WaitKey() ;
					return;
				}
			}else{
				ClearDrawScreen();
		        DrawString( 540,0 , "クライアント" , CRPURPLE ) ;
		        DrawString( 0 , 0 , "データ受信に失敗しました" , CRRED ) ;
		        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
				ScreenFlip();
		        WaitKey() ;
				return;
			}
		}

		//表示ルーチンへ
		while(1){


			// メッセージ処理
			if( ProcessMessage() == -1 )
			{
				mode=1;
				return ;	// エラーが起きたらループから抜ける
			}
			Sleep(1);
		}

		//バックアップからの戻し
	//	rikisidata[higasiid]=temp_rikisidata_higasi;
		rikisidata[id]=temp_rikisidata_nisi;
		if (id==0){
			rikisidata[1]=temp_backup_rikisidata_higasi;
			strcpy(namestring[1],temp_namestring_higasi);
		}else{
			rikisidata[0]=temp_backup_rikisidata_higasi;
			strcpy(namestring[0],temp_namestring_higasi);
		}

		// 接続を断つ
		CloseNetWork( NetHandle ) ;


    }else{
		ClearDrawScreen();
        DrawString( 540,0 , "クライアント" , CRPURPLE ) ;
        DrawString( 0 , 0 , "サーバーに接続できませんでした" , CRWHITE ) ;
        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
		ScreenFlip();
        WaitKey() ;
		return;
	}


	return;

}

void net_server(int higasiid,int nisiid)//higasiidはサーバー側の力士画像ID、nisiidはhigasiidが0でなければ0、0なら1
{
	int i;
	int kaeri=0;
	//char StrBuf[ 256 ] ;    // データバッファ
	IPDATA Ip ;        // 接続用ＩＰアドレスデータ
	int NetHandle , LostHandle ;    // ネットワークハンドル
	int DataLength ;        // 受信データ量保存用変数
	int portno=9850;
	char temp_namestring_nisi[12];
	for (i=0;i<12;i++){
		temp_namestring_nisi[i]=0;
	}
	//取り組み中のデータいじりのためのバックアップ処理
	temp_rikisidata_higasi=rikisidata[higasiid];
	//temp_rikisidata_nisi=rikisidata[nisiid];
	temp_backup_rikisidata_nisi=rikisidata[nisiid];
	strcpy(temp_namestring_nisi,namestring[nisiid]);;

	////////////////クライアントからデータ取り込み///////////////////
	// 接続してくるのを待つ状態にする
    PreparationListenNetWork( portno ) ;

	ClearDrawScreen();
    DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
    DrawString( 0 , 0 , "相手の接続待ちです…\n\nESCでキャンセル" , CRWHITE ) ;
	ScreenFlip();
    // 接続してくるかＥＳＣキーが押されるまでループ
    NetHandle = -1 ;
    while( !ProcessMessage() && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
    {
        // 新しい接続があったらそのネットワークハンドルを得る
        NetHandle = GetNewAcceptNetWork() ;
        if( NetHandle != -1 ) break ;
		Sleep(1);
    }

    // 接続されていたら次に進む
    if( NetHandle != -1 )
    {
        // 接続の受付を終了する
        StopListenNetWork() ;

        // 接続してきたマシンのＩＰアドレスを得る
        GetNetWorkIP( NetHandle , &Ip ) ;

        // データが送られて来るまで待つ
        while( !ProcessMessage() )
        {
            // 取得していない受信データ量が０以外のときはループから抜ける
            if( GetNetWorkDataLength( NetHandle ) != 0 ) break ;
			Sleep(1);
        }
        // データ受信
        DataLength = GetNetWorkDataLength( NetHandle ) ;    // データの量を取得
		if (DataLength==sizeof(temp_rikisidata_nisi)){
	        NetWorkRecv( NetHandle , &temp_rikisidata_nisi , DataLength );    // データをバッファに取得
			rikisidata[nisiid]=temp_rikisidata_nisi;
		}else{
			ClearDrawScreen();
	        DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
	        DrawString( 0 , 0 , "データ受信に失敗しました" , CRRED ) ;
	        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
			ScreenFlip();
	        WaitKey() ;
			return;
		}

        // データを受信した旨表示描画
		ClearDrawScreen();
        DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
        DrawString( 0 , 0 , "データ受信に成功しました！！" , CRWHITE ) ;
        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
		ScreenFlip();
        WaitKey() ;

		ClearDrawScreen();
        DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
        DrawString( 0 , 0 , "今度はこちらのデータを送信します" , CRWHITE ) ;
        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
		ScreenFlip();
        WaitKey() ;

        // データを送信
        NetWorkSend( NetHandle , &rikisidata[higasiid] , sizeof(rikisidata[higasiid]));

		ClearDrawScreen();
        DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
        DrawString( 0 , 0 , "取組へ進みます…" , CRWHITE ) ;
		ScreenFlip();

		//三役以上ボーナス処理省略
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

		//取り組みの核心ルーチン呼び出し
		ketteisenflag=1;//左の電光掲示板を表示しないようにするフラグ
		kaeri=fight_fight_server(higasiid,nisiid,NetHandle);
		ketteisenflag=0;//左の電光掲示板を表示しないようにするフラグ

		if( ProcessMessage() == -1 ){mode=1;return;}

		if (mode==1){
			return;
		}

		//
		if (kaeri==-1){
			ClearDrawScreen();
	        DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
	        DrawString( 0 , 400 , "取組中に不測の終了" , CRWHITE ) ;
	        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
			ScreenFlip();
	        WaitKey() ;
		}else{
			if (kaeri==1){//東方の勝ち
				ClearDrawScreen();
		        DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
		        DrawFormatString( 0 , 16,CRWHITE,"%s(サーバー)の勝ち" , namestring[higasiid] ) ;
		        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
				ScreenFlip();
		        WaitKey() ;
			}else{
				ClearDrawScreen();
		        DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
		        DrawFormatString( 0 , 16,CRWHITE,"%s(クライアント)の勝ち" , namestring[nisiid] ) ;
		        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
				ScreenFlip();
		        WaitKey() ;
			}
		}
		//バックアップからの戻し
		rikisidata[higasiid]=temp_rikisidata_higasi;
	//	rikisidata[nisiid]=temp_rikisidata_nisi;
		rikisidata[nisiid]=temp_backup_rikisidata_nisi;
		strcpy(namestring[nisiid],temp_namestring_nisi);

        // 相手が通信を切断するまで待つ
        while( !ProcessMessage() )
        {
            // 新たに切断されたネットワークハンドルを得る
            LostHandle = GetLostNetWork() ;

            // 切断された接続が今まで通信してた相手だった場合ループを抜ける
            if( LostHandle == NetHandle ) break ;
			Sleep(1);
        }
        // 切断確認表示
		ClearDrawScreen();
        DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
        DrawString( 0 , 16 , "相手が通信を無事切断しました" , CRWHITE ) ;
        DrawString( 0 , 400 , "Hit Any Keyで戻ります" , CRWHITE ) ;
		ScreenFlip();
        WaitKey() ;

	}

	return;
}

int fight_fight_server(int higasiid,int nisiid,int NetHandle)//東が勝なら1、西が勝なら2を返す
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

	if( ProcessMessage() == -1 ){mode=1;return 0;}

	//////////////////////////////////////////////////////////////////////

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
//	joukendata_temp_higasi=joukendata[higasiid];
//	joukendata_temp_nisi=joukendata[nisiid];
//	joukendata2_temp_higasi=joukendata2[higasiid];
//	joukendata2_temp_nisi=joukendata2[nisiid];
	matatukihanasitaflag=0;
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
	
	//東力士(サーバー)の技パターンの選択
	wazapatternid_higasi=rikisidata[higasiid].motiwazapattern[0];

	//西力士(クライアント)の技パターンの選択
	wazapatternid_nisi=rikisidata[nisiid].motiwazapattern[0];

	//東力士(サーバー)の立会いパターンの選択
	{
		////////////////立合い狙い入力/////////////////////////
	HYOJI_nerai:
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
		DrawFormatString(187,369,CRWHITE,"%sの立合いの狙いを左リストから",namestring[rikisidata[higasiid].nameid]);
		DrawString(187,369+16,"クリックかキー押下で選択してください。",CRWHITE);
		DrawString(187,385+75,"力士名をクリックで能力表示",CRWHITE);
		DrawFormatString(x1[0],y1[0]-32,CRWHITE,"%s",namestring[rikisidata[higasiid].nameid]);
		ii=0;DrawString(x1[ii*2],y1[ii*2],"突き押し　　　8",CRGREEN);
		ii++;DrawString(x1[ii*2],y1[ii*2],"右四つ　　　　6(O)",CRGREEN);
		ii++;DrawString(x1[ii*2],y1[ii*2],"左四つ　　　　4(U)",CRGREEN);
		ii++;DrawString(x1[ii*2],y1[ii*2],"両上手　　　　5(I)",CRGREEN);
		ii++;DrawString(x1[ii*2],y1[ii*2],"両差し　　　　2(K)",CRGREEN);
		ScreenFlip() ;//裏画面を表画面にコピー
		loopderuflag=0;
		// キー入力待ち(この一文を入れないとうまくいかないみたい)
		while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
			Sleep(1);
		}
		while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
			Sleep(1);
		}
		while(1)
		{
			//GetKeys();
			if( CheckHitKey_test(KEY_INPUT_NUMPAD8) || CheckHitKey_test(KEY_INPUT_8)){//ENTERキーでループから抜けメニュー画面へ
				nerai_higasi=0;
				break;
			}
			if( CheckHitKey_test(KEY_INPUT_NUMPAD6) || CheckHitKey_test(KEY_INPUT_6) || CheckHitKey_test(KEY_INPUT_O)){//ENTERキーでループから抜けメニュー画面へ
				nerai_higasi=1;
				break;
			}
			if( CheckHitKey_test(KEY_INPUT_NUMPAD4) || CheckHitKey_test(KEY_INPUT_4) || CheckHitKey_test(KEY_INPUT_U)){//ENTERキーでループから抜けメニュー画面へ
				nerai_higasi=2;
				break;
			}
			if( CheckHitKey_test(KEY_INPUT_NUMPAD5) || CheckHitKey_test(KEY_INPUT_5) || CheckHitKey_test(KEY_INPUT_I)){//ENTERキーでループから抜けメニュー画面へ
				nerai_higasi=3;
				break;
			}
			if( CheckHitKey_test(KEY_INPUT_NUMPAD2) || CheckHitKey_test(KEY_INPUT_2) || CheckHitKey_test(KEY_INPUT_K)){//ENTERキーでループから抜けメニュー画面へ
				nerai_higasi=4;
				break;
			}
			for(ii=0;ii<5;ii++){
				if (get_mouseclick_list(ii*2) == 1 || get_mouseclick_list(ii*2+1) == 1){//左リスト上のをクリックしたら
					nerai_higasi=ii;
					loopderuflag=1;
					break;
				}
			}
			if (loopderuflag==1){
				break;
			}

			if (get_mouseclick(187,40,187+80,40+16)==1 || get_mouseclick(411,40,411+80,40+16)==1 ){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawBox(0,0,639,479,CRBACK,TRUE);
				rikisidatahyoji_main_net(higasiid,-187,nisiid);
				SetFontSize(16);
				if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
				rikisidatahyoji_main_net(nisiid,+172,higasiid);
				SetFontSize(16);
				if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
				DrawString(0,20,"　戻る(ESCキー)",CRGREEN);
				ScreenFlip();
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
				}
				while(1)
				{
					if(get_mouseclick(0,20,16*8,20+16) == 1 || CheckHitKey_test( KEY_INPUT_ESCAPE )==1){
						goto HYOJI_nerai;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 ){
						mode=1;
						return -1;	// エラーが発生したらループを抜ける
					}
					Sleep(1);
				}
			}
			// メッセージ処理
			if( ProcessMessage() == -1 ){
				mode=1;
				return -1;	// エラーが発生したらループを抜ける
			}
			Sleep(1);
		}
		////////////////立合い勢い入力/////////////////////////
HYOJI_ikioi:
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
		DrawFormatString(187,369,CRWHITE,"%sの立会いの勢いを左リストから",namestring[rikisidata[higasiid].nameid]);
		DrawString(187,369+16,"クリックかキー押下で選択してください。",CRWHITE);
		DrawString(187,369+32,"なお、異なる立会いの勢いになる場合もあります。",CRWHITE);
		//DrawString(187,369+48,"また、全力の立会いは余計にスタミナを消費します(-10)。",CRWHITE);
		DrawString(187,385+75,"力士名をクリックで能力表示",CRWHITE);
		DrawFormatString(x1[0],y1[0]-32,CRWHITE,"%s",namestring[rikisidata[higasiid].nameid]);
		ii=0;DrawString(x1[ii*2],y1[ii*2],"全力　　　　　8",CRGREEN);
		ii++;DrawString(x1[ii*2],y1[ii*2],"強く　　　　　5(I)",CRGREEN);
		ii++;DrawString(x1[ii*2],y1[ii*2],"受け　　　　　2(K)",CRGREEN);
		ii++;DrawString(x1[ii*2],y1[ii*2],"変化　　　　　0(M)",CRGREEN);
		ScreenFlip() ;//裏画面を表画面にコピー
		loopderuflag=0;
		// キー入力待ち(この一文を入れないとうまくいかないみたい)
		while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
			Sleep(1);
		}
		while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
			Sleep(1);
		}
		while(1)
		{
			//GetKeys();
			if( CheckHitKey_test(KEY_INPUT_NUMPAD8) || CheckHitKey_test(KEY_INPUT_8)){//ENTERキーでループから抜けメニュー画面へ
				ikioi_higasi=0;
				break;
			}
			if( CheckHitKey_test(KEY_INPUT_NUMPAD5) || CheckHitKey_test(KEY_INPUT_5) || CheckHitKey_test(KEY_INPUT_I)){//ENTERキーでループから抜けメニュー画面へ
				ikioi_higasi=1;
				break;
			}
			if( CheckHitKey_test(KEY_INPUT_NUMPAD2) || CheckHitKey_test(KEY_INPUT_2) || CheckHitKey_test(KEY_INPUT_K)){//ENTERキーでループから抜けメニュー画面へ
				ikioi_higasi=2;
				break;
			}
			if( CheckHitKey_test(KEY_INPUT_NUMPAD0) || CheckHitKey_test(KEY_INPUT_0) || CheckHitKey_test(KEY_INPUT_M)){//ENTERキーでループから抜けメニュー画面へ
				ikioi_higasi=3;
				break;
			}
			for(ii=0;ii<4;ii++){
				if (get_mouseclick_list(ii*2) == 1 || get_mouseclick_list(ii*2+1) == 1){//左リスト上のをクリックしたら
					ikioi_higasi=ii;
					loopderuflag=1;
					break;
				}
			}
			if (loopderuflag==1){
				break;
			}
			if (get_mouseclick(187,40,187+80,40+16)==1 || get_mouseclick(411,40,411+80,40+16)==1 ){
				ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
				DrawBox(0,0,639,479,CRBACK,TRUE);
				rikisidatahyoji_main_net(higasiid,-187,nisiid);
				SetFontSize(16);
				if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
				rikisidatahyoji_main_net(nisiid,+172,higasiid);
				SetFontSize(16);
				if( ProcessMessage() == -1 ){mode=1;return -1;}// エラーが起きたらループから抜ける
				DrawString(0,20,"　戻る(ESCキー)",CRGREEN);
				ScreenFlip();
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
				}
				while(1)
				{
					if(get_mouseclick(0,20,16*8,20+16) == 1 || CheckHitKey_test( KEY_INPUT_ESCAPE )==1){
						goto HYOJI_ikioi;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 ){
						mode=1;
						return -1;	// エラーが発生したらループを抜ける
					}
					Sleep(1);
				}
			}
			// メッセージ処理
			if( ProcessMessage() == -1 ){
				mode=1;
				return -1;	// エラーが発生したらループを抜ける
			}
			Sleep(1);
		}

		//////////////////立ち合いパターンＩＤ確定///////////////
		tatiaipatternid_higasi=nerai_higasi*4+ikioi_higasi;
		//気負いで全力が受け、変化が受け
		if (tatiaipatternid_higasi%4==0){
			if (GetRand(1)==0){
				tatiaipatternid_higasi+=2;
				kioi_flag_higasi=1;
			}
		}else if (tatiaipatternid_higasi%4==3){
			if (GetRand(1)==0){
				tatiaipatternid_higasi--;
				chuucho_flag_higasi=1;
			}
		}
	}

	//西力士(クライアント)の立会いパターンの選択
	{
		//立合いの狙い受信
        // データが送られて来るまで待つ
        while( !ProcessMessage() )
        {
            // 取得していない受信データ量が０以外のときはループから抜ける
            if( GetNetWorkDataLength( NetHandle ) != 0 ) break ;
			Sleep(1);
        }
        // データ受信
        DataLength = GetNetWorkDataLength( NetHandle ) ;    // データの量を取得
		if (DataLength==sizeof(nerai_nisi)){
	        NetWorkRecv( NetHandle , &nerai_nisi , DataLength );    // データをバッファに取得
			if (nerai_nisi<0 || nerai_nisi>4){
				ClearDrawScreen();
		        DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
		        DrawString( 0 , 0 , "受信値が変です" , CRRED ) ;
		        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
				ScreenFlip();
		        WaitKey() ;
				return -1;
			}
		}else{
			ClearDrawScreen();
	        DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
	        DrawString( 0 , 0 , "データ受信に失敗しました" , CRRED ) ;
	        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
			ScreenFlip();
	        WaitKey() ;
			return -1;
		}
        // 受信ＯＫデータを送信
		netokflag=1;
        NetWorkSend( NetHandle , &netokflag , sizeof(netokflag));

		//立合いの狙い受信
        // データが送られて来るまで待つ
        while( !ProcessMessage() )
        {
            // 取得していない受信データ量が０以外のときはループから抜ける
            if( GetNetWorkDataLength( NetHandle ) != 0 ) break ;
			Sleep(1);
        }
        // データ受信
        DataLength = GetNetWorkDataLength( NetHandle ) ;    // データの量を取得
		if (DataLength==sizeof(ikioi_nisi)){
	        NetWorkRecv( NetHandle , &ikioi_nisi , DataLength );    // データをバッファに取得
			if (ikioi_nisi<0 || ikioi_nisi>3){
				ClearDrawScreen();
		        DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
		        DrawString( 0 , 0 , "受信値が変です" , CRRED ) ;
		        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
				ScreenFlip();
		        WaitKey() ;
				return -1;
			}
		}else{
			ClearDrawScreen();
	        DrawString( 540,0 , "サーバー" , CRPURPLE ) ;
	        DrawString( 0 , 0 , "データ受信に失敗しました" , CRRED ) ;
	        DrawString( 0 , 400 , "Hit Any Key" , CRWHITE ) ;
			ScreenFlip();
	        WaitKey() ;
			return -1;
		}
        // 受信ＯＫデータを送信
		netokflag=1;
        NetWorkSend( NetHandle , &netokflag , sizeof(netokflag));

		tatiaipatternid_nisi=nerai_nisi*4+ikioi_nisi;
		//気負いで全力が受け、変化が受け
		if (tatiaipatternid_nisi%4==0){
			if (GetRand(1)==0){
				tatiaipatternid_nisi+=2;
				kioi_flag_nisi=1;
			}
		}else if (tatiaipatternid_nisi%4==3){
			if (GetRand(1)==0){
				tatiaipatternid_nisi--;
				chuucho_flag_nisi=1;
			}
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
/*
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
*/
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

	//ネット対戦のために一時的にスタミナ回復
	rikisidata[higasiid].stamina=50;
	rikisidata[nisiid].stamina=50;

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
	
	/////////////立ち合い後の表示/////////////////
	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
	if (kioi_flag_higasi==1){
		DrawFormatString(187,369,CRWHITE,"%sは気負いすぎてしまったか。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr1,"%sは気負いすぎてしまったか。",namestring[rikisidata[higasiid].nameid]);
	}
	if (kioi_flag_nisi==1){
		DrawFormatString(187,428,CRWHITE,"%sは気負いすぎてしまったか。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr4,"%sは気負いすぎてしまったか。",namestring[rikisidata[nisiid].nameid]);
	}
	if (chuucho_flag_higasi==1){
		DrawFormatString(187,369,CRWHITE,"%sは躊躇してしまったか。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr1,"%sは躊躇してしまったか。",namestring[rikisidata[higasiid].nameid]);
	}
	if (chuucho_flag_nisi==1){
		DrawFormatString(187,428,CRWHITE,"%sは躊躇してしまったか。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr4,"%sは躊躇してしまったか。",namestring[rikisidata[nisiid].nameid]);
	}
	if (yowaki_flag_higasi==1){
		DrawFormatString(187,369,CRWHITE,"%sは積極性を欠く弱気の立会いだ。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr1,"%sは積極性を欠く弱気の立会いだ。",namestring[rikisidata[higasiid].nameid]);
	}
	if (yowaki_flag_nisi==1){
		DrawFormatString(187,428,CRWHITE,"%sは積極性を欠く弱気の立会いだ。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr4,"%sは積極性を欠く弱気の立会いだ。",namestring[rikisidata[nisiid].nameid]);
	}
	if (pride_flag_higasi==1){
		DrawFormatString(187,369,CRWHITE,"%sはプライドから変化はできない。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr1,"%sはプライドから変化はできない。",namestring[rikisidata[higasiid].nameid]);
	}
	if (pride_flag_nisi==1){
		DrawFormatString(187,428,CRWHITE,"%sはプライドから変化はできない。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr4,"%sはプライドから変化はできない。",namestring[rikisidata[nisiid].nameid]);
	}

	if (higasi_tatiai_power==ZENRYOKU_TATIAI_POWER){
		DrawFormatString(187,385,CRWHITE,"%sは素晴らしい踏み込みだ。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr2,"%sは素晴らしい踏み込みだ。",namestring[rikisidata[higasiid].nameid]);
	}else if(higasi_tatiai_power==NORMAL_TATIAI_POWER){
		DrawFormatString(187,385,CRWHITE,"%sは強く踏み込んでいった。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr2,"%sは強く踏み込んでいった。",namestring[rikisidata[higasiid].nameid]);
	}else if(higasi_tatiai_power==UKERU_TATIAI_POWER){
		DrawFormatString(187,385,CRWHITE,"%sはやや受けの立会いのようだ。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr2,"%sはやや受けの立会いのようだ。",namestring[rikisidata[higasiid].nameid]);
	}else{
		DrawFormatString(187,385,CRWHITE,"%sは立会いで変化した。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr2,"%sは立会いで変化した。",namestring[rikisidata[higasiid].nameid]);
	}
	if (nisi_tatiai_power==ZENRYOKU_TATIAI_POWER){
		DrawFormatString(187,444,CRWHITE,"%sは素晴らしい踏み込みだ。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr5,"%sは素晴らしい踏み込みだ。",namestring[rikisidata[nisiid].nameid]);
	}else if(nisi_tatiai_power==NORMAL_TATIAI_POWER){
		DrawFormatString(187,444,CRWHITE,"%sは強く踏み込んでいった。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr5,"%sは強く踏み込んでいった。",namestring[rikisidata[nisiid].nameid]);
	}else if(nisi_tatiai_power==UKERU_TATIAI_POWER){
		DrawFormatString(187,444,CRWHITE,"%sはやや受けの立会いのようだ。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr5,"%sはやや受けの立会いのようだ。",namestring[rikisidata[nisiid].nameid]);
	}else{
		DrawFormatString(187,444,CRWHITE,"%sは立会いで変化した。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr5,"%sは立会いで変化した。",namestring[rikisidata[nisiid].nameid]);
	}
	if (higasi_tatiai_nerai==TUKIOSI_TATIAI_NERAI){
		DrawFormatString(187,401,CRWHITE,"%sは突き押し狙いのようだ。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr3,"%sは突き押し狙いのようだ。",namestring[rikisidata[higasiid].nameid]);
	}else if(higasi_tatiai_nerai==MIGIYOTU_TATIAI_NERAI){
		DrawFormatString(187,401,CRWHITE,"%sは右四つに組みたがっているようだ。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr3,"%sは右四つに組みたがっているようだ。",namestring[rikisidata[higasiid].nameid]);
	}else if(higasi_tatiai_nerai==HIDARIYOTU_TATIAI_NERAI){
		DrawFormatString(187,401,CRWHITE,"%sは左四つに組みたがっているようだ。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr3,"%sは左四つに組みたがっているようだ。",namestring[rikisidata[higasiid].nameid]);
	}else if(higasi_tatiai_nerai==RYOUUWATE_TATIAI_NERAI){
		DrawFormatString(187,401,CRWHITE,"%sは両方から抱え込むのを狙っていそうだ。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr3,"%sは両方から抱え込むのを狙っていそうだ。",namestring[rikisidata[higasiid].nameid]);
	}else{
		DrawFormatString(187,401,CRWHITE,"%sは両差し狙いのようだ。",namestring[rikisidata[higasiid].nameid]);
		sprintf(netdata.netstr3,"%sは両差し狙いのようだ。",namestring[rikisidata[higasiid].nameid]);
	}
	if (nisi_tatiai_nerai==TUKIOSI_TATIAI_NERAI){
		DrawFormatString(187,460,CRWHITE,"%sは突き押し狙いのようだ。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr6,"%sは突き押し狙いのようだ。",namestring[rikisidata[nisiid].nameid]);
	}else if(nisi_tatiai_nerai==MIGIYOTU_TATIAI_NERAI){
		DrawFormatString(187,460,CRWHITE,"%sは右四つに組みたがっているようだ。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr6,"%sは右四つに組みたがっているようだ。",namestring[rikisidata[nisiid].nameid]);
	}else if(nisi_tatiai_nerai==HIDARIYOTU_TATIAI_NERAI){
		DrawFormatString(187,460,CRWHITE,"%sは左四つに組みたがっているようだ。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr6,"%sは左四つに組みたがっているようだ。",namestring[rikisidata[nisiid].nameid]);
	}else if(nisi_tatiai_nerai==RYOUUWATE_TATIAI_NERAI){
		DrawFormatString(187,460,CRWHITE,"%sはあえて懐に飛び込ませたがっているようだ。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr6,"%sはあえて懐に飛び込ませたがっているようだ。",namestring[rikisidata[nisiid].nameid]);
	}else{
		DrawFormatString(187,460,CRWHITE,"%sは両差し狙いのようだ。",namestring[rikisidata[nisiid].nameid]);
		sprintf(netdata.netstr6,"%sは両差し狙いのようだ。",namestring[rikisidata[nisiid].nameid]);
	}
	ScreenFlip() ;//裏画面を表画面にコピー

	//netdata送信






	starttime = GetNowCount() ;
	// キー入力待ち(この一文を入れないとうまくいかないみたい)
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
		if( GetNowCount() - starttime > WAIT){
			break;
		}
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
		if( GetNowCount() - starttime > WAIT){
			break;
		}
	}
	while(1)
	{

		if( GetNowCount() - starttime > WAIT*2){
			break;
		}

		Sleep(1);
		if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
			break;
		}
		if (get_mouseclick( 187 , 120 , 637 , 366 )){
			break;
		}
		// メッセージ処理
		if( ProcessMessage() == -1 )
		{
			mode=1;
			return 0;	// エラーが起きたらループから抜ける
		}
	}


	//負けの判定
	if (state_ichi<-3 || state_ichi>3 || offense_state_balance<1 || defense_state_balance<1){
		//表示
		strcpy(kimaritestring,"叩き込み");
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
		DrawFormatString(187,369,CRWHITE,"%sと%sの取り組みは立会い変化で勝負あり。",namestring[rikisidata[higasiid].nameid],namestring[rikisidata[nisiid].nameid]);
		ScreenFlip() ;//裏画面を表画面にコピー
		starttime = GetNowCount() ;
		// キー入力待ち(この一文を入れないとうまくいかないみたい)
		while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
			Sleep(1);
		}
		while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
			Sleep(1);
		}
		while(1)
		{
/*
			if( GetNowCount() - starttime > WAIT){
				break;
			}
*/
			if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
				break;
			}
			if (get_mouseclick( 187 , 120 , 637 , 366 )){
				break;
			}
			// メッセージ処理
			if( ProcessMessage() == -1 ){
				mode=1;
				return -1;	// エラーが発生したらループを抜ける
			}
			Sleep(1);
		}
	}
	if (state_ichi<-3){//東が土俵から出て西の勝ち
		return 2;
	}else if (state_ichi>3){//西が土俵から出て東の勝ち
		return 1;
	}else if (offense_state_balance<1){//以下相手のバランス崩れて勝ち
		if (offenseid==higasiid){
			return 2;
		}else{
			return 1;
		}
	}else if (defense_state_balance<1){
		if (defenseid==higasiid){
			return 2;
		}else{
			return 1;
		}
	}

	ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
	fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
	DrawFormatString(187,369,CRWHITE,"立会いは%sの方が優勢のようです。",namestring[rikisidata[offenseid].nameid]);
	ScreenFlip() ;//裏画面を表画面にコピー
	starttime = GetNowCount() ;
	// キー入力待ち(この一文を入れないとうまくいかないみたい)
	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
		Sleep(1);
		if( GetNowCount() - starttime > WAIT){
			break;
		}
	}
	while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
		Sleep(1);
		if( GetNowCount() - starttime > WAIT){
			break;
		}
	}
	while(1)
	{
		if( GetNowCount() - starttime > WAIT){
			break;
		}
		Sleep(1);
		if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
			break;
		}
		if (get_mouseclick( 187 , 120 , 637 , 366 )){
			break;
		}
		// メッセージ処理
		if( ProcessMessage() == -1 )
		{
			mode=1;
			return 0;	// エラーが起きたらループから抜ける
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
		///////////////
		turncount++;
		wazatrycount=0;
		////////////////

		////////////////東力士(サーバー)の技選択/////////////////////////
		//ここに選択画面
		if (state_kyori==FAR_STATE_KYORI){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
			DrawFormatString(187,369,CRWHITE,"%sが繰り出す技をクリックまたはキー入力で",namestring[rikisidata[offenseid].nameid]);
			DrawString(187,369+16,"テレパシーとして伝えてください。",CRWHITE);
			DrawFormatString(x1[0],y1[0]-32,CRWHITE,"%s",namestring[rikisidata[offenseid].nameid]);
			ii=0;
			iii=8;DrawFormatString(x1[ii*2],y1[ii*2],CRGREEN,"突き　　　　　%d",iii);ii++;
			iii=5;DrawFormatString(x1[ii*2],y1[ii*2],CRGREEN,"あてがい　　　%d(I)",iii);ii++;
			ScreenFlip() ;//裏画面を表画面にコピー
			nyuuryokuti=0;
			starttime = GetNowCount() ;
			loopderuflag=0;
			while(1)
			{
				for(ii=0;ii<2;ii++){
					if (get_mouseclick_list(ii*2) == 1 || get_mouseclick_list(ii*2+1) == 1){//左リスト上のをクリックしたら
						nyuuryokuti=ii+1;
						loopderuflag=1;
						break;
					}
				}
				if (loopderuflag==1){
					break;
				}
				if( GetNowCount() - starttime > WAIT_NYUURYOKU){
					nyuuryokuti=0;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD8) || CheckHitKey_test(KEY_INPUT_8)){//ENTERキーでループから抜けメニュー画面へ
					nyuuryokuti=1;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD5) || CheckHitKey_test(KEY_INPUT_5) || CheckHitKey_test(KEY_INPUT_I)){//ENTERキーでループから抜けメニュー画面へ
					nyuuryokuti=2;
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode=1;
					return 0;	// エラーが起きたらループから抜ける
				}
				Sleep(1);
			}
			wazaid_sentaku=nyuuryokuti;
		}else if(state_kyori==NEAR_STATE_KYORI){
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
			DrawFormatString(187,369,CRWHITE,"%sが繰り出す技をクリックまたはキー入力で",namestring[rikisidata[offenseid].nameid]);
			DrawString(187,369+16,"テレパシーとして伝えてください。",CRWHITE);
			DrawFormatString(x1[0],y1[0]-32,CRWHITE,"%s",namestring[rikisidata[offenseid].nameid]);
			ii=0;
			iii=8;DrawFormatString(x1[ii*2],y1[ii*2],CRGREEN,"寄り　　　　　%d",iii);ii++;
			iii=5;DrawFormatString(x1[ii*2],y1[ii*2],CRGREEN,"現状維持　　　%d(I)",iii);ii++;
			ii++;
			iii=9;DrawFormatString(x1[ii*2],y1[ii*2],CRGREEN,"右からの投げ　%d",iii);ii++;
			if (offense_state_migiude!=UWATETUKAMI_STATE_UDE && offense_state_migiude!=SITATETUKAMI_STATE_UDE){
				iii=6;DrawFormatString(x1[ii*2],y1[ii*2],CRGREEN,"右の廻し狙い　%d(O)",iii);ii++;
			}else{
				iii=6;DrawFormatString(x1[ii*2],y1[ii*2],CRGRAY,"右の廻し狙い　%d(O)",iii);ii++;
			}
			iii=3;DrawFormatString(x1[ii*2],y1[ii*2],CRGREEN,"右の巻き替え　%d(L)",iii);ii++;
			ii++;
			iii=7;DrawFormatString(x1[ii*2],y1[ii*2],CRGREEN,"左からの投げ　%d",iii);ii++;
			if (offense_state_hidariude!=UWATETUKAMI_STATE_UDE && offense_state_hidariude!=SITATETUKAMI_STATE_UDE){
				iii=4;DrawFormatString(x1[ii*2],y1[ii*2],CRGREEN,"左の廻し狙い　%d(U)",iii);ii++;
			}else{
				iii=4;DrawFormatString(x1[ii*2],y1[ii*2],CRGRAY,"左の廻し狙い　%d(U)",iii);ii++;
			}
			iii=1;DrawFormatString(x1[ii*2],y1[ii*2],CRGREEN,"左の巻き替え　%d(J)",iii);ii++;
			ScreenFlip() ;//裏画面を表画面にコピー
			nyuuryokuti=0;
			starttime = GetNowCount() ;
			loopderuflag=0;
			while(1)
			{
				if( GetNowCount() - starttime > WAIT_NYUURYOKU){
					nyuuryokuti=0;
					break;
				}
				if (get_mouseclick_list(0) || get_mouseclick_list(1)){//左リスト上のをクリックしたら
					nyuuryokuti=8;
					break;
				}
				if (get_mouseclick_list(2) || get_mouseclick_list(3)){//左リスト上のをクリックしたら
					nyuuryokuti=5;
					break;
				}
				//9
				if (get_mouseclick_list(6) || get_mouseclick_list(7)){//左リスト上のをクリックしたら
					if (offense_state_migiude==UWATETUKAMI_STATE_UDE) nyuuryokuti=14;
					if (offense_state_migiude==UWATE_STATE_UDE) nyuuryokuti=18;
					if (offense_state_migiude==SITATETUKAMI_STATE_UDE) nyuuryokuti=16;
					if (offense_state_migiude==SITATE_STATE_UDE) nyuuryokuti=20;
					break;
				}
				//6
				if (get_mouseclick_list(8) || get_mouseclick_list(9)){//左リスト上のをクリックしたら
					if (offense_state_migiude!=UWATETUKAMI_STATE_UDE && offense_state_migiude!=SITATETUKAMI_STATE_UDE){
						if (offense_state_migiude==UWATE_STATE_UDE) nyuuryokuti=4;
						if (offense_state_migiude==SITATE_STATE_UDE) nyuuryokuti=6;
						break;
					}
				}
				//3
				if (get_mouseclick_list(10) || get_mouseclick_list(11)){//左リスト上のをクリックしたら
					if (offense_state_migiude==UWATETUKAMI_STATE_UDE) nyuuryokuti=12;
					if (offense_state_migiude==UWATE_STATE_UDE) nyuuryokuti=12;
					if (offense_state_migiude==SITATETUKAMI_STATE_UDE) nyuuryokuti=10;
					if (offense_state_migiude==SITATE_STATE_UDE) nyuuryokuti=10;
					break;
				}
				//7
				if (get_mouseclick_list(14) || get_mouseclick_list(15)){//左リスト上のをクリックしたら
					if (offense_state_hidariude==UWATETUKAMI_STATE_UDE) nyuuryokuti=15;
					if (offense_state_hidariude==UWATE_STATE_UDE) nyuuryokuti=19;
					if (offense_state_hidariude==SITATETUKAMI_STATE_UDE) nyuuryokuti=17;
					if (offense_state_hidariude==SITATE_STATE_UDE) nyuuryokuti=21;
					break;
				}
				//4
				if (get_mouseclick_list(16) || get_mouseclick_list(17)){//左リスト上のをクリックしたら
					if (offense_state_hidariude!=UWATETUKAMI_STATE_UDE && offense_state_hidariude!=SITATETUKAMI_STATE_UDE){
						if (offense_state_hidariude==UWATE_STATE_UDE) nyuuryokuti=5;
						if (offense_state_hidariude==SITATE_STATE_UDE) nyuuryokuti=7;
						break;
					}
				}
				//1
				if (get_mouseclick_list(18) || get_mouseclick_list(19)){//左リスト上のをクリックしたら
					if (offense_state_hidariude==UWATETUKAMI_STATE_UDE) nyuuryokuti=13;
					if (offense_state_hidariude==UWATE_STATE_UDE) nyuuryokuti=13;
					if (offense_state_hidariude==SITATETUKAMI_STATE_UDE) nyuuryokuti=11;
					if (offense_state_hidariude==SITATE_STATE_UDE) nyuuryokuti=11;
					break;
				}
				//GetKeys();
				if( CheckHitKey_test(KEY_INPUT_NUMPAD8) || CheckHitKey_test(KEY_INPUT_8)){//ENTERキーでループから抜けメニュー画面へ
					nyuuryokuti=8;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD5) || CheckHitKey_test(KEY_INPUT_5) || CheckHitKey_test(KEY_INPUT_I)){//ENTERキーでループから抜けメニュー画面へ
					nyuuryokuti=9;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD9) || CheckHitKey_test(KEY_INPUT_9)){//ENTERキーでループから抜けメニュー画面へ
					if (offense_state_migiude==UWATETUKAMI_STATE_UDE) nyuuryokuti=14;
					if (offense_state_migiude==UWATE_STATE_UDE) nyuuryokuti=18;
					if (offense_state_migiude==SITATETUKAMI_STATE_UDE) nyuuryokuti=16;
					if (offense_state_migiude==SITATE_STATE_UDE) nyuuryokuti=20;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD6) || CheckHitKey_test(KEY_INPUT_6) || CheckHitKey_test(KEY_INPUT_O)){//ENTERキーでループから抜けメニュー画面へ
					if (offense_state_migiude!=UWATETUKAMI_STATE_UDE && offense_state_migiude!=SITATETUKAMI_STATE_UDE){
						if (offense_state_migiude==UWATE_STATE_UDE) nyuuryokuti=4;
						if (offense_state_migiude==SITATE_STATE_UDE) nyuuryokuti=6;
						break;
					}
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD3) || CheckHitKey_test(KEY_INPUT_3) || CheckHitKey_test(KEY_INPUT_L)){//ENTERキーでループから抜けメニュー画面へ
					if (offense_state_migiude==UWATETUKAMI_STATE_UDE) nyuuryokuti=12;
					if (offense_state_migiude==UWATE_STATE_UDE) nyuuryokuti=12;
					if (offense_state_migiude==SITATETUKAMI_STATE_UDE) nyuuryokuti=10;
					if (offense_state_migiude==SITATE_STATE_UDE) nyuuryokuti=10;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD7) || CheckHitKey_test(KEY_INPUT_7)){//ENTERキーでループから抜けメニュー画面へ
					if (offense_state_hidariude==UWATETUKAMI_STATE_UDE) nyuuryokuti=15;
					if (offense_state_hidariude==UWATE_STATE_UDE) nyuuryokuti=19;
					if (offense_state_hidariude==SITATETUKAMI_STATE_UDE) nyuuryokuti=17;
					if (offense_state_hidariude==SITATE_STATE_UDE) nyuuryokuti=21;
					break;
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD4) || CheckHitKey_test(KEY_INPUT_4) || CheckHitKey_test(KEY_INPUT_U)){//ENTERキーでループから抜けメニュー画面へ
					if (offense_state_hidariude!=UWATETUKAMI_STATE_UDE && offense_state_hidariude!=SITATETUKAMI_STATE_UDE){
						if (offense_state_hidariude==UWATE_STATE_UDE) nyuuryokuti=5;
						if (offense_state_hidariude==SITATE_STATE_UDE) nyuuryokuti=7;
						break;
					}
				}
				if( CheckHitKey_test(KEY_INPUT_NUMPAD1) || CheckHitKey_test(KEY_INPUT_1) || CheckHitKey_test(KEY_INPUT_J)){//ENTERキーでループから抜けメニュー画面へ
					if (offense_state_hidariude==UWATETUKAMI_STATE_UDE) nyuuryokuti=13;
					if (offense_state_hidariude==UWATE_STATE_UDE) nyuuryokuti=13;
					if (offense_state_hidariude==SITATETUKAMI_STATE_UDE) nyuuryokuti=11;
					if (offense_state_hidariude==SITATE_STATE_UDE) nyuuryokuti=11;
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode=1;
					return 0;	// エラーが起きたらループから抜ける
				}
				Sleep(1);
			}
			wazaid_sentaku=nyuuryokuti;
		}else{//距離中間の場合
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
			if (waza(wazaid_sentaku,higasiid,nisiid)==-1){
				wazaid_sentaku=-1;
			}else{
				if (state_ichi<-4) state_ichi=-4;
				if (state_ichi>4) state_ichi=4;
			}
			///////////実況///////////////
			if (ichi_lastturn<state_ichi){
				if (soundflag==1){
					PlaySoundMem( kansei_middle_l , DX_PLAYTYPE_BACK ) ;
				}
			}else if (ichi_lastturn>state_ichi){
				if (soundflag==1){
					PlaySoundMem( kansei_middle_r , DX_PLAYTYPE_BACK ) ;
				}
			}
			ClearDrawScreen();
			fight_backscreen_net(higasiid,nisiid);
			DrawFormatString(187,369,CRWHITE,"%s", namestring[rikisidata[offenseid].nameid]);
			DrawFormatString(187,385,CRWHITE,"%s", jikkyoustring);
			ScreenFlip();
			Sleep(1);
			starttime = GetNowCount() ;
			// キー入力待ち(この一文を入れないとうまくいかないみたい)
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while(1)
			{
				if( GetNowCount() - starttime > WAIT){
					break;
				}
				Sleep(1);
				if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
					break;
				}
				if (get_mouseclick( 187 , 120 , 637 , 366 )){
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode=1;
					return 0;	// エラーが起きたらループから抜ける
				}
			}
		}else{
			ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
			fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
			DrawFormatString(187,369,CRWHITE,"%sはどうすればいいかわからない(エラーかも)", namestring[rikisidata[offenseid].nameid]);
			ScreenFlip() ;//裏画面を表画面にコピー
			starttime = GetNowCount() ;
			// キー入力待ち(この一文を入れないとうまくいかないみたい)
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while(1)
			{
				if( GetNowCount() - starttime > WAIT){
					break;
				}
				Sleep(1);
				if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
					break;
				}
				if (get_mouseclick( 187 , 120 , 637 , 366 )){
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode=1;
					return 0;	// エラーが起きたらループから抜ける
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
				strcpy(kimaritestring,"引落とし");
				ClearDrawScreen();
				fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
				DrawFormatString(187,369,CRWHITE,"おっと押し込んでいる%sの足がついていかない！",namestring[rikisidata[nisiid].nameid]);
				ScreenFlip();
				starttime = GetNowCount() ;
				// キー入力待ち(この一文を入れないとうまくいかないみたい)
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
					if( GetNowCount() - starttime > WAIT){
						break;
					}
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
					if( GetNowCount() - starttime > WAIT){
						break;
					}
				}
				while(1)
				{
					if( GetNowCount() - starttime > WAIT){
						break;
					}
					Sleep(1);
					if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
						break;
					}
					if (get_mouseclick( 187 , 120 , 637 , 366 )){
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 )
					{
						mode=1;
						return 0;	// エラーが起きたらループから抜ける
					}
				}

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
				strcpy(kimaritestring,"引落とし");
				ClearDrawScreen();
				fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
				DrawFormatString(187,369,CRWHITE,"おっと押し込んでいる%sの足がついていかない！",namestring[rikisidata[higasiid].nameid]);
				ScreenFlip();
				starttime = GetNowCount() ;
				// キー入力待ち(この一文を入れないとうまくいかないみたい)
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
					if( GetNowCount() - starttime > WAIT){
						break;
					}
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
					if( GetNowCount() - starttime > WAIT){
						break;
					}
				}
				while(1)
				{
					if( GetNowCount() - starttime > WAIT){
						break;
					}
					Sleep(1);
					if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
						break;
					}
					if (get_mouseclick( 187 , 120 , 637 , 366 )){
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 )
					{
						mode=1;
						return 0;	// エラーが起きたらループから抜ける
					}
				}

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
						ClearDrawScreen();
						fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
						DrawFormatString(187,369,CRWHITE,"%s　土俵際なんとか堪えました。",namestring[rikisidata[higasiid].nameid]);
						ScreenFlip();
						starttime = GetNowCount() ;
						// キー入力待ち(この一文を入れないとうまくいかないみたい)
						while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
							Sleep(1);
							if( GetNowCount() - starttime > WAIT){
								break;
							}
						}
						while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
							Sleep(1);
							if( GetNowCount() - starttime > WAIT){
								break;
							}
						}
						while(1)
						{
							if( GetNowCount() - starttime > WAIT){
								break;
							}
							Sleep(1);
							if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
								break;
							}
							if (get_mouseclick( 187 , 120 , 637 , 366 )){
								break;
							}
							// メッセージ処理
							if( ProcessMessage() == -1 )
							{
								mode=1;
								return 0;	// エラーが起きたらループから抜ける
							}
						}
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
						ClearDrawScreen();
						fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
						DrawFormatString(187,369,CRWHITE,"%s　土俵際粘って残しました。",namestring[rikisidata[higasiid].nameid]);
						ScreenFlip();
						starttime = GetNowCount() ;
						// キー入力待ち(この一文を入れないとうまくいかないみたい)
						while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
							Sleep(1);
							if( GetNowCount() - starttime > WAIT){
								break;
							}
						}
						while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
							Sleep(1);
							if( GetNowCount() - starttime > WAIT){
								break;
							}
						}
						while(1)
						{
							if( GetNowCount() - starttime > WAIT){
								break;
							}
							Sleep(1);
							if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
								break;
							}
							if (get_mouseclick( 187 , 120 , 637 , 366 )){
								break;
							}
							// メッセージ処理
							if( ProcessMessage() == -1 )
							{
								mode=1;
								return 0;	// エラーが起きたらループから抜ける
							}
						}
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
						ClearDrawScreen();
						fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
						DrawFormatString(187,369,CRWHITE,"%s　土俵際驚異の粘りだ！またまた残った！",namestring[rikisidata[higasiid].nameid]);
						ScreenFlip();
						starttime = GetNowCount() ;
						// キー入力待ち(この一文を入れないとうまくいかないみたい)
						while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
							Sleep(1);
							if( GetNowCount() - starttime > WAIT){
								break;
							}
						}
						while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
							Sleep(1);
							if( GetNowCount() - starttime > WAIT){
								break;
							}
						}
						while(1)
						{
							if( GetNowCount() - starttime > WAIT){
								break;
							}
							Sleep(1);
							if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
								break;
							}
							if (get_mouseclick( 187 , 120 , 637 , 366 )){
								break;
							}
							// メッセージ処理
							if( ProcessMessage() == -1 )
							{
								mode=1;
								return 0;	// エラーが起きたらループから抜ける
							}
						}
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
						ClearDrawScreen();
						fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
						DrawFormatString(187,369,CRWHITE,"%s　土俵際なんとか堪えました。",namestring[rikisidata[nisiid].nameid]);
						ScreenFlip();
						starttime = GetNowCount() ;
						// キー入力待ち(この一文を入れないとうまくいかないみたい)
						while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
							Sleep(1);
							if( GetNowCount() - starttime > WAIT){
								break;
							}
						}
						while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
							Sleep(1);
							if( GetNowCount() - starttime > WAIT){
								break;
							}
						}
						while(1)
						{
							if( GetNowCount() - starttime > WAIT){
								break;
							}
							Sleep(1);
							if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
								break;
							}
							if (get_mouseclick( 187 , 120 , 637 , 366 )){
								break;
							}
							// メッセージ処理
							if( ProcessMessage() == -1 )
							{
								mode=1;
								return 0;	// エラーが起きたらループから抜ける
							}
						}
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
						ClearDrawScreen();
						fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
						DrawFormatString(187,369,CRWHITE,"%s　土俵際粘って残しました。",namestring[rikisidata[nisiid].nameid]);
						ScreenFlip();
						starttime = GetNowCount() ;
						// キー入力待ち(この一文を入れないとうまくいかないみたい)
						while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
							Sleep(1);
							if( GetNowCount() - starttime > WAIT){
								break;
							}
						}
						while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
							Sleep(1);
							if( GetNowCount() - starttime > WAIT){
								break;
							}
						}
						while(1)
						{
							if( GetNowCount() - starttime > WAIT){
								break;
							}
							Sleep(1);
							if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
								break;
							}
							if (get_mouseclick( 187 , 120 , 637 , 366 )){
								break;
							}
							// メッセージ処理
							if( ProcessMessage() == -1 )
							{
								mode=1;
								return 0;	// エラーが起きたらループから抜ける
							}
						}
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
						ClearDrawScreen();
						fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
						DrawFormatString(187,369,CRWHITE,"%s　土俵際驚異の粘りだ！またまた残った！",namestring[rikisidata[nisiid].nameid]);
						ScreenFlip();
						starttime = GetNowCount() ;
						// キー入力待ち(この一文を入れないとうまくいかないみたい)
						while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
							Sleep(1);
							if( GetNowCount() - starttime > WAIT){
								break;
							}
						}
						while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
							Sleep(1);
							if( GetNowCount() - starttime > WAIT){
								break;
							}
						}
						while(1)
						{
							if( GetNowCount() - starttime > WAIT){
								break;
							}
							Sleep(1);
							if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
								break;
							}
							if (get_mouseclick( 187 , 120 , 637 , 366 )){
								break;
							}
							// メッセージ処理
							if( ProcessMessage() == -1 )
							{
								mode=1;
								return 0;	// エラーが起きたらループから抜ける
							}
						}
					}
				}
			}
		}else if(state_kyori==FAR_STATE_KYORI){
			if (state_ichi<-3 && GetRand(rikisidata[higasiid].binshousei)>GetRand(rikisidata[nisiid].binshousei)){
				if (GetRand(rikisidata[higasiid].binshousei*5)>GetRand(rikisidata[nisiid].binshousei*sisuu_binshou_gyakuten)){
					state_ichi=-3;
					offense_state_balance=-1;
					strcpy(kimaritestring,"突落とし");
					ClearDrawScreen();
					fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
					DrawFormatString(187,369,CRWHITE,"%s　土俵際素早い動きで逆転だ！",namestring[rikisidata[higasiid].nameid]);
					ScreenFlip();
					starttime = GetNowCount() ;
					// キー入力待ち(この一文を入れないとうまくいかないみたい)
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
						if( GetNowCount() - starttime > WAIT){
							break;
						}
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
						if( GetNowCount() - starttime > WAIT){
							break;
						}
					}
					while(1)
					{
						if( GetNowCount() - starttime > WAIT){
							break;
						}
						Sleep(1);
						if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
							break;
						}
						if (get_mouseclick( 187 , 120 , 637 , 366 )){
							break;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 )
						{
							mode=1;
							return 0;	// エラーが起きたらループから抜ける
						}
					}
				}else if (GetRand(rikisidata[higasiid].binshousei*10)>GetRand(rikisidata[nisiid].binshousei*sisuu_binshou_mawarikomi)){
					state_ichi=-2;
					ClearDrawScreen();
					fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
					DrawFormatString(187,369,CRWHITE,"%s　土俵際素早い動きでなんとか回り込んだ",namestring[rikisidata[higasiid].nameid]);
					ScreenFlip();
					starttime = GetNowCount() ;
					// キー入力待ち(この一文を入れないとうまくいかないみたい)
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
						if( GetNowCount() - starttime > WAIT){
							break;
						}
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
						if( GetNowCount() - starttime > WAIT){
							break;
						}
					}
					while(1)
					{
						if( GetNowCount() - starttime > WAIT){
							break;
						}
						Sleep(1);
						if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
							break;
						}
						if (get_mouseclick( 187 , 120 , 637 , 366 )){
							break;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 )
						{
							mode=1;
							return 0;	// エラーが起きたらループから抜ける
						}
					}
				}
			}else if (state_ichi>3 && GetRand(rikisidata[higasiid].binshousei)<GetRand(rikisidata[nisiid].binshousei)){
				if (GetRand(rikisidata[higasiid].binshousei*sisuu_binshou_gyakuten)<GetRand(rikisidata[nisiid].binshousei*5)){
					state_ichi=3;
					offense_state_balance=-1;
					strcpy(kimaritestring,"突落とし");
					ClearDrawScreen();
					fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
					DrawFormatString(187,369,CRWHITE,"%s　土俵際素早い動きで逆転だ！",namestring[rikisidata[nisiid].nameid]);
					ScreenFlip();
					starttime = GetNowCount() ;
					// キー入力待ち(この一文を入れないとうまくいかないみたい)
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
						if( GetNowCount() - starttime > WAIT){
							break;
						}
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
						if( GetNowCount() - starttime > WAIT){
							break;
						}
					}
					while(1)
					{
						if( GetNowCount() - starttime > WAIT){
							break;
						}
						Sleep(1);
						if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
							break;
						}
						if (get_mouseclick( 187 , 120 , 637 , 366 )){
							break;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 )
						{
							mode=1;
							return 0;	// エラーが起きたらループから抜ける
						}
					}
				}else if (GetRand(rikisidata[higasiid].binshousei*sisuu_binshou_mawarikomi)<GetRand(rikisidata[nisiid].binshousei*10)){
					state_ichi=2;
					ClearDrawScreen();
					fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
					DrawFormatString(187,369,CRWHITE,"%s　土俵際素早い動きでなんとか回り込んだ",namestring[rikisidata[nisiid].nameid]);
					ScreenFlip();
					starttime = GetNowCount() ;
					// キー入力待ち(この一文を入れないとうまくいかないみたい)
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
						if( GetNowCount() - starttime > WAIT){
							break;
						}
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
						if( GetNowCount() - starttime > WAIT){
							break;
						}
					}
					while(1)
					{
						if( GetNowCount() - starttime > WAIT){
							break;
						}
						Sleep(1);
						if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
							break;
						}
						if (get_mouseclick( 187 , 120 , 637 , 366 )){
							break;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 )
						{
							mode=1;
							return 0;	// エラーが起きたらループから抜ける
						}
					}
				}

			}
		}
				
		//負けの判定
		if (state_ichi<-3){//東が土俵から出て西の勝ち
			return 2;
		}else if (state_ichi>3){//西が土俵から出て東の勝ち
			return 1;
		}else if (offense_state_balance<1){//以下相手のバランス崩れて勝ち
			if (offenseid==higasiid){
				return 2;
			}else{
				return 1;
			}
		}else if (defense_state_balance<1){
			if (defenseid==higasiid){
				return 2;
			}else{
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
					ClearDrawScreen();
					fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
					DrawFormatString(187,369,CRWHITE,"おっと、%sは相手の突きに思わず顎を上げてしまった。",namestring[rikisidata[defenseid].nameid]);
					ScreenFlip();
					starttime = GetNowCount() ;
					// キー入力待ち(この一文を入れないとうまくいかないみたい)
					while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
						Sleep(1);
						if( GetNowCount() - starttime > WAIT){
							break;
						}
					}
					while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
						Sleep(1);
						if( GetNowCount() - starttime > WAIT){
							break;
						}
					}
					while(1)
					{
						if( GetNowCount() - starttime > WAIT){
							break;
						}
						Sleep(1);
						if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
							break;
						}
						if (get_mouseclick( 187 , 120 , 637 , 366 )){
							break;
						}
						// メッセージ処理
						if( ProcessMessage() == -1 )
						{
							mode=1;
							return 0;	// エラーが起きたらループから抜ける
						}
					}
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
		if (matatukihanasitaflag==1){
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
			ClearDrawScreen();
			fight_backscreen_net(higasiid,nisiid);
			DrawFormatString(187,369,CRWHITE,"%s", namestring[rikisidata[offenseid].nameid]);
			DrawFormatString(187,385,CRWHITE,"%s", jikkyoustring);
			ScreenFlip();
			starttime = GetNowCount() ;
			// キー入力待ち(この一文を入れないとうまくいかないみたい)
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while(1)
			{
				if( GetNowCount() - starttime > WAIT){
					break;
				}
				Sleep(1);
				if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
					break;
				}
				if (get_mouseclick( 187 , 120 , 637 , 366 )){
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode=1;
					return 0;	// エラーが起きたらループから抜ける
				}
			}
			rikisihyoji_megatenflag=0;
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
			}
		//守備側が大きくバランスを崩された場合の連続攻撃を受ける処理
		}else if (defense_state_balance<(int)(rikisidata[defenseid].balance/10)+1
		 && defense_state_balance<6){
			ClearDrawScreen();
			fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
			DrawFormatString(187,369,CRWHITE,"%sの体勢が大きく崩れている",namestring[rikisidata[defenseid].nameid]);
			ScreenFlip();
			starttime = GetNowCount() ;
			// キー入力待ち(この一文を入れないとうまくいかないみたい)
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while(1)
			{
				if( GetNowCount() - starttime > WAIT){
					break;
				}
				Sleep(1);
				if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
					break;
				}
				if (get_mouseclick( 187 , 120 , 637 , 366 )){
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode=1;
					return 0;	// エラーが起きたらループから抜ける
				}
			}
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
			ClearDrawScreen();
			fight_backscreen_net(higasiid,nisiid);//戦闘時用画面表示
			DrawFormatString(187,369,CRWHITE,"%s　連続攻撃のチャンス！",namestring[rikisidata[defenseid].nameid]);
			ScreenFlip();
			starttime = GetNowCount() ;
			// キー入力待ち(この一文を入れないとうまくいかないみたい)
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while(1)
			{
				if( GetNowCount() - starttime > WAIT){
					break;
				}
				Sleep(1);
				if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
					break;
				}
				if (get_mouseclick( 187 , 120 , 637 , 366 )){
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode=1;
					return 0;	// エラーが起きたらループから抜ける
				}
			}
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
			if (defenseid==higasiid){
				rikisihyoji_megatenflag=1;
			}else{
				rikisihyoji_megatenflag=2;
			}
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
			ClearDrawScreen();
			fight_backscreen_net(higasiid,nisiid);
			DrawFormatString(187,369,CRWHITE,"%s", namestring[rikisidata[offenseid].nameid]);
			DrawFormatString(187,385,CRWHITE,"%s", jikkyoustring);
			ScreenFlip();
			starttime = GetNowCount() ;
			// キー入力待ち(この一文を入れないとうまくいかないみたい)
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while(1)
			{
				if( GetNowCount() - starttime > WAIT){
					break;
				}
				Sleep(1);
				if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
					break;
				}
				if (get_mouseclick( 187 , 120 , 637 , 366 )){
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode=1;
					return 0;	// エラーが起きたらループから抜ける
				}
			}
			rikisihyoji_megatenflag=0;
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
		//という処理は両者リアルモードなのでやらない
		//空欄


		}
		//スタミナ切れ処理
		if (defense_stamina<0){
			rikisidata[defenseid].kerutikara=(int)(rikisidata[defenseid].kerutikara/2)+1;
			defense_state_jouge=HIGH_STATE_JOUGE;
			if (defense_action_zengo==MAE_ACTION_ZENGO){
				defense_action_zengo=NASI_ACTION_ZENGO;
			}
			defense_action_sayuu=NASI_ACTION_SAYUU;
			ClearDrawScreen();
			fight_backscreen_net(higasiid,nisiid);
			if (defenseid==higasiid && staminagirehyojiflag_higasi==0){
				DrawFormatString(187,369,CRWHITE,"%sはスタミナが切れてきたようです", namestring[rikisidata[defenseid].nameid]);
				DrawString(187,385,"上体が浮いてきて、棒立ちになってきた",CRWHITE);
				ScreenFlip();
				starttime = GetNowCount() ;
				// キー入力待ち(この一文を入れないとうまくいかないみたい)
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
					if( GetNowCount() - starttime > WAIT){
						break;
					}
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
					if( GetNowCount() - starttime > WAIT){
						break;
					}
				}
				while(1)
				{
					if( GetNowCount() - starttime > WAIT){
						break;
					}
					Sleep(1);
					if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
						break;
					}
					if (get_mouseclick( 187 , 120 , 637 , 366 )){
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 )
					{
						mode=1;
						return 0;	// エラーが起きたらループから抜ける
					}
				}
				staminagirehyojiflag_higasi=1;
			}
			if (defenseid==nisiid && staminagirehyojiflag_nisi==0){
				DrawFormatString(187,369,CRWHITE,"%sはスタミナが切れてきたようです", namestring[rikisidata[defenseid].nameid]);
				DrawString(187,385,"上体が浮いてきて、棒立ちになってきた",CRWHITE);
				ScreenFlip();
				starttime = GetNowCount() ;
				// キー入力待ち(この一文を入れないとうまくいかないみたい)
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
					if( GetNowCount() - starttime > WAIT){
						break;
					}
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
					if( GetNowCount() - starttime > WAIT){
						break;
					}
				}
				while(1)
				{
					if( GetNowCount() - starttime > WAIT){
						break;
					}
					Sleep(1);
					if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
						break;
					}
					if (get_mouseclick( 187 , 120 , 637 , 366 )){
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 )
					{
						mode=1;
						return 0;	// エラーが起きたらループから抜ける
					}
				}
				staminagirehyojiflag_nisi=1;
			}
		}
		if (offense_stamina<0){
			rikisidata[offenseid].kerutikara=(int)(rikisidata[offenseid].kerutikara/2)+1;
			offense_state_jouge=HIGH_STATE_JOUGE;
			if (offense_action_zengo==MAE_ACTION_ZENGO){
				offense_action_zengo=NASI_ACTION_ZENGO;
			}
			offense_action_sayuu=NASI_ACTION_SAYUU;
			ClearDrawScreen();
			fight_backscreen_net(higasiid,nisiid);
			if (offenseid==higasiid && staminagirehyojiflag_higasi==0){
				DrawFormatString(187,369,CRWHITE,"%sはスタミナが切れてきたようです", namestring[rikisidata[offenseid].nameid]);
				DrawString(187,385,"上体が浮いてきて、棒立ちになってきた",CRWHITE);
				ScreenFlip();
				starttime = GetNowCount() ;
				// キー入力待ち(この一文を入れないとうまくいかないみたい)
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
					if( GetNowCount() - starttime > WAIT){
						break;
					}
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
					if( GetNowCount() - starttime > WAIT){
						break;
					}
				}
				while(1)
				{
					if( GetNowCount() - starttime > WAIT){
						break;
					}
					Sleep(1);
					if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
						break;
					}
					if (get_mouseclick( 187 , 120 , 637 , 366 )){
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 )
					{
						mode=1;
						return 0;	// エラーが起きたらループから抜ける
					}
				}
				staminagirehyojiflag_higasi=1;
			}
			if (offenseid==nisiid && staminagirehyojiflag_nisi==0){
				DrawFormatString(187,369,CRWHITE,"%sはスタミナが切れてきたようです", namestring[rikisidata[offenseid].nameid]);
				DrawString(187,385,"上体が浮いてきて、棒立ちになってきた",CRWHITE);
				ScreenFlip();
				starttime = GetNowCount() ;
				// キー入力待ち(この一文を入れないとうまくいかないみたい)
				while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
					Sleep(1);
					if( GetNowCount() - starttime > WAIT){
						break;
					}
				}
				while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
					Sleep(1);
					if( GetNowCount() - starttime > WAIT){
						break;
					}
				}
				while(1)
				{
					if( GetNowCount() - starttime > WAIT){
						break;
					}
					Sleep(1);
					if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
						break;
					}
					if (get_mouseclick( 187 , 120 , 637 , 366 )){
						break;
					}
					// メッセージ処理
					if( ProcessMessage() == -1 )
					{
						mode=1;
						return 0;	// エラーが起きたらループから抜ける
					}
				}
				staminagirehyojiflag_nisi=1;
			}
		}
		if (defense_stamina<-5){
			defense_state_balance=0;
			strcpy(kimaritestring,"叩き込み");
			ClearDrawScreen();
			fight_backscreen_net(higasiid,nisiid);
			DrawFormatString(187,369,CRWHITE,"%sは遂に完全にスタミナが切れたようです", namestring[rikisidata[defenseid].nameid]);
			DrawString(187,385,"前につんのめったところを叩かれました！",CRWHITE);
			ScreenFlip();
			starttime = GetNowCount() ;
			// キー入力待ち(この一文を入れないとうまくいかないみたい)
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while(1)
			{
				if( GetNowCount() - starttime > WAIT){
					break;
				}
				Sleep(1);
				if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
					break;
				}
				if (get_mouseclick( 187 , 120 , 637 , 366 )){
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode=1;
					return 0;	// エラーが起きたらループから抜ける
				}
			}
			if (defenseid==higasiid){
				return 2;
			}else{
				return 1;
			}
		}else if (offense_stamina<-5){
			offense_state_balance=0;
			strcpy(kimaritestring,"叩き込み");
			ClearDrawScreen();
			fight_backscreen_net(higasiid,nisiid);
			DrawFormatString(187,369,CRWHITE,"%sは遂に完全にスタミナが切れたようです", namestring[rikisidata[offenseid].nameid]);
			DrawString(187,385,"前につんのめったところを叩かれました！",CRWHITE);
			ScreenFlip();
			starttime = GetNowCount() ;
			// キー入力待ち(この一文を入れないとうまくいかないみたい)
			while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while( ProcessMessage() == 0 && CheckHitKeyAll() == 0 ){
				Sleep(1);
				if( GetNowCount() - starttime > WAIT){
					break;
				}
			}
			while(1)
			{
				if( GetNowCount() - starttime > WAIT){
					break;
				}
				Sleep(1);
				if( CheckHitKey_test( KEY_INPUT_NUMPADENTER )==1 || CheckHitKey_test( KEY_INPUT_RETURN )==1){//ENTERキーでループから抜け実際の取組へ
					break;
				}
				if (get_mouseclick( 187 , 120 , 637 , 366 )){
					break;
				}
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					mode=1;
					return 0;	// エラーが起きたらループから抜ける
				}
			}
			if (offenseid==higasiid){
				return 2;
			}else{
				return 1;
			}
		}

		Sleep(1);
		
		if( ProcessMessage() == -1 )
		{
			mode=1;
			return 0;	// エラーが起きたらループから抜ける
		}
	}
	
}

void rikisidatahyoji_main_net(int x,int yokozure,int AITE)
{
	int i,ii;
	int x1_gazou=0;
	int y1_gazou=0;
	int x2_gazou=0;
	int y2_gazou=0;
	int x3_gazou=0;
	int y3_gazou=0;
	int x4_gazou=0;
	int y4_gazou=0;
	int shukushou_tate_gazou=0;
	int shukushou_yoko_gazou=0;
	int rikisi_front_temp=0;
	int xh=0;
	char temp_filename[MAX_PATH];
	for (i=0;i<MAX_PATH;i++){
		temp_filename[i]=0;
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}


	if (yokozure<0){//東力士
		SetFontSize( 12 ) ;
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

/*
		if (temp_rikisidata_higasi.realmodeflag==1){//「ver2.44」
			DrawString(187+48+yokozure,88+2,"テレパシーON",CRRED
			);
		}else{
			if ((superrikisisuu[2]==0 && tokuiwazahyojiflag==1) || (superrikisisuu[2]!=2 && temp_rikisidata_higasi.heyaid==myheyaid)){
				if (joukendata[x].joukenflag==0){
					DrawFormatString(187+48+yokozure,88+2,CRWHITE,"%s",
					wazapattern_string[temp_rikisidata_higasi.motiwazapattern[0]]
					);
				}else if (joukendata[x].joukenflag==1){
					DrawFormatString(187+48+yokozure,88+2,CRWHITE,"%s",
					sakusenname[x]
					);
				}else if (joukendata[x].joukenflag==2){
					DrawFormatString(187+48+yokozure,88+2,CRWHITE,"%s",
					joukendata[x].joukenname
					);
				}else if (joukendata[x].joukenflag==3){
					DrawFormatString(187+48+yokozure,88+2,CRWHITE,"%sが自分で判断",
					namestring[x]
					);
				}
			}else{
				if (superrikisisuu[2]!=2 && tokuiwazahyojiflag==1){
					if (joukendata[x].joukenflag==0){
						DrawFormatString(187+yokozure,88+2,CRWHITE,"好作戦 %s",
						wazapattern_string[temp_rikisidata_higasi.motiwazapattern[0]]
						);
					}else if (joukendata[x].joukenflag==1){
						DrawFormatString(187+yokozure,88+2,CRWHITE,"好作戦 %s",
						sakusenname[x]
						);
					}else if (joukendata[x].joukenflag==2){
						DrawFormatString(187+yokozure,88+2,CRWHITE,"好作戦 %s",
						joukendata[x].joukenname
						);
					}else if (joukendata[x].joukenflag==3){
						DrawFormatString(187+yokozure,88+2,CRWHITE,"%sが自分で判断",
						namestring[x]
						);
					}
				}
			}
		}
*/
		DrawFormatString(187+yokozure,104,CRWHITE,"身長　 %3d",
		temp_rikisidata_higasi.sinchou
		);
		DrawFormatString(187+yokozure,120,CRWHITE,"体重　 %3d",
		temp_rikisidata_higasi.taijuu
		);
		DrawFormatString(187+yokozure,136,CRWHITE,"積極性 %3d",
		temp_rikisidata_higasi.sekkyokusei
		);
		DrawFormatString(187+yokozure,152,CRWHITE,"敏捷性 %3d",
		temp_rikisidata_higasi.binshousei
		);
		DrawFormatString(187+yokozure,168,CRWHITE,"突進力 %3d",
		temp_rikisidata_higasi.tossinryoku
		);
		DrawFormatString(187+yokozure,184,CRWHITE,"蹴る力 %3d",
		temp_rikisidata_higasi.kerutikara
		);
		DrawFormatString(187+yokozure,200,CRWHITE,"右腕力 %3d",
		temp_rikisidata_higasi.migiwanryoku
		);
		DrawFormatString(187+yokozure,216,CRWHITE,"左腕力 %3d",
		temp_rikisidata_higasi.hidariwanryoku
		);
		DrawFormatString(187+yokozure,232,CRWHITE,"バラン %3d",
		temp_rikisidata_higasi.balance
		);
		DrawFormatString(187+yokozure,248,CRWHITE,"立会術 %3d",
		temp_rikisidata_higasi.tatiaigijutu
		);
		DrawFormatString(187+yokozure,264,CRWHITE,"突き　 %3d",
		temp_rikisidata_higasi.tuki
		);
		DrawFormatString(187+yokozure,280,CRWHITE,"右脇堅 %3d",
		temp_rikisidata_higasi.migiwakikatasa
		);
		DrawFormatString(187+yokozure,296,CRWHITE,"左脇堅 %3d",
		temp_rikisidata_higasi.hidariwakikatasa
		);
		DrawFormatString(187+yokozure,312,CRWHITE,"あてが %3d",
		temp_rikisidata_higasi.ategai
		);
		DrawFormatString(187+yokozure,328,CRWHITE,"右返し %3d",
		temp_rikisidata_higasi.migikaesi
		);
		DrawFormatString(187+yokozure,344,CRWHITE,"左返し %3d",
		temp_rikisidata_higasi.hidarikaesi
		);
		DrawFormatString(287+yokozure,104,CRWHITE,"右絞り %3d",
		temp_rikisidata_higasi.migisibori
		);
		DrawFormatString(287+yokozure,120,CRWHITE,"左絞り %3d",
		temp_rikisidata_higasi.hidarisibori
		);
		DrawFormatString(287+yokozure,136,CRWHITE,"右抱込 %3d",
		temp_rikisidata_higasi.migikakaekomi
		);
		DrawFormatString(287+yokozure,152,CRWHITE,"左抱込 %3d",
		temp_rikisidata_higasi.hidarikakaekomi
		);
		DrawFormatString(287+yokozure,168,CRWHITE,"ひきつ %3d",
		temp_rikisidata_higasi.hikituke
		);
		DrawFormatString(287+yokozure,184,CRWHITE,"右握力 %3d",
		temp_rikisidata_higasi.migiakuryoku
		);
		DrawFormatString(287+yokozure,200,CRWHITE,"左握力 %3d",
		temp_rikisidata_higasi.hidariakuryoku
		);
		DrawFormatString(287+yokozure,216,CRWHITE,"スタミ %3d",
		temp_rikisidata_higasi.stamina
		);
		DrawFormatString(287+yokozure,232,CRWHITE,"根性　 %3d",
		temp_rikisidata_higasi.konjou
		);
		DrawFormatString(287+yokozure,248,CRWHITE,"粘り　 %3d",
		temp_rikisidata_higasi.nebari
		);
		DrawFormatString(287+yokozure,264,CRWHITE,"足運び %3d",
		temp_rikisidata_higasi.asihakobi
		);
		DrawFormatString(287+yokozure,280,CRWHITE,"柔軟性 %3d",
		temp_rikisidata_higasi.juunansei
		);
		DrawFormatString(287+yokozure,296,CRWHITE,"頑固　 %3d",
		100-temp_rikisidata_higasi.zunou
		);
		DrawFormatString(387+yokozure,104,CRWHITE,"右上投%3d",
		temp_rikisidata_higasi.migiuwatenage
		);
		DrawFormatString(387+yokozure,120,CRWHITE,"左上投%3d",
		temp_rikisidata_higasi.hidariuwatenage
		);
		DrawFormatString(387+yokozure,136,CRWHITE,"右下投%3d",
		temp_rikisidata_higasi.migisitatenage
		);
		DrawFormatString(387+yokozure,152,CRWHITE,"左下投%3d",
		temp_rikisidata_higasi.hidarisitatenage
		);
		DrawFormatString(387+yokozure,168,CRWHITE,"右小投%3d",
		temp_rikisidata_higasi.migikotenage
		);
		DrawFormatString(387+yokozure,184,CRWHITE,"左小投%3d",
		temp_rikisidata_higasi.hidarikotenage
		);
		DrawFormatString(387+yokozure,200,CRWHITE,"右掬投%3d",
		temp_rikisidata_higasi.migisukuinage
		);
		DrawFormatString(387+yokozure,216,CRWHITE,"左掬投%3d",
		temp_rikisidata_higasi.hidarisukuinage
		);

		//力士画像表示
		if (rikisigraphflag==1){
			shukushou_tate_gazou=(int)(220-temp_rikisidata_higasi.sinchou)*2/3;
			shukushou_yoko_gazou=(int)((250-temp_rikisidata_higasi.taijuu)/2);
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
			sprintf(temp_filename,"rikisigraph/rikisi%d.png\0",x);
			rikisi_front_temp = LoadGraph( temp_filename ) ;
			DrawModiGraph(x1_gazou+yokozure,y1_gazou ,	x2_gazou+yokozure,y2_gazou , x3_gazou+yokozure,y3_gazou , x4_gazou+yokozure,y4_gazou , rikisi_front_temp , TRUE ) ;
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}else{//西力士
		SetFontSize( 12 ) ;
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

/*		if (temp_rikisidata_nisi.realmodeflag==1){//「ver2.44」
			DrawString(187+48+yokozure,88+2,"テレパシーON",CRRED
			);
		}else{
			if ((superrikisisuu[2]==0 && tokuiwazahyojiflag==1) || (superrikisisuu[2]!=2 && temp_rikisidata_nisi.heyaid==myheyaid)){
				if (joukendata[x].joukenflag==0){
					DrawFormatString(187+48+yokozure,88+2,CRWHITE,"%s",
					wazapattern_string[temp_rikisidata_nisi.motiwazapattern[0]]
					);
				}else if (joukendata[x].joukenflag==1){
					DrawFormatString(187+48+yokozure,88+2,CRWHITE,"%s",
					sakusenname[x]
					);
				}else if (joukendata[x].joukenflag==2){
					DrawFormatString(187+48+yokozure,88+2,CRWHITE,"%s",
					joukendata[x].joukenname
					);
				}else if (joukendata[x].joukenflag==3){
					DrawFormatString(187+48+yokozure,88+2,CRWHITE,"%sが自分で判断",
					namestring[x]
					);
				}
			}else{
				if (superrikisisuu[2]!=2 && tokuiwazahyojiflag==1){
					if (joukendata[x].joukenflag==0){
						DrawFormatString(187+yokozure,88+2,CRWHITE,"好作戦 %s",
						wazapattern_string[temp_rikisidata_nisi.motiwazapattern[0]]
						);
					}else if (joukendata[x].joukenflag==1){
						DrawFormatString(187+yokozure,88+2,CRWHITE,"好作戦 %s",
						sakusenname[x]
						);
					}else if (joukendata[x].joukenflag==2){
						DrawFormatString(187+yokozure,88+2,CRWHITE,"好作戦 %s",
						joukendata[x].joukenname
						);
					}else if (joukendata[x].joukenflag==3){
						DrawFormatString(187+yokozure,88+2,CRWHITE,"%sが自分で判断",
						namestring[x]
						);
					}
				}
			}
		}
*/
		DrawFormatString(187+yokozure,104,CRWHITE,"身長　 %3d",
		temp_rikisidata_nisi.sinchou
		);
		DrawFormatString(187+yokozure,120,CRWHITE,"体重　 %3d",
		temp_rikisidata_nisi.taijuu
		);
		DrawFormatString(187+yokozure,136,CRWHITE,"積極性 %3d",
		temp_rikisidata_nisi.sekkyokusei
		);
		DrawFormatString(187+yokozure,152,CRWHITE,"敏捷性 %3d",
		temp_rikisidata_nisi.binshousei
		);
		DrawFormatString(187+yokozure,168,CRWHITE,"突進力 %3d",
		temp_rikisidata_nisi.tossinryoku
		);
		DrawFormatString(187+yokozure,184,CRWHITE,"蹴る力 %3d",
		temp_rikisidata_nisi.kerutikara
		);
		DrawFormatString(187+yokozure,200,CRWHITE,"右腕力 %3d",
		temp_rikisidata_nisi.migiwanryoku
		);
		DrawFormatString(187+yokozure,216,CRWHITE,"左腕力 %3d",
		temp_rikisidata_nisi.hidariwanryoku
		);
		DrawFormatString(187+yokozure,232,CRWHITE,"バラン %3d",
		temp_rikisidata_nisi.balance
		);
		DrawFormatString(187+yokozure,248,CRWHITE,"立会術 %3d",
		temp_rikisidata_nisi.tatiaigijutu
		);
		DrawFormatString(187+yokozure,264,CRWHITE,"突き　 %3d",
		temp_rikisidata_nisi.tuki
		);
		DrawFormatString(187+yokozure,280,CRWHITE,"右脇堅 %3d",
		temp_rikisidata_nisi.migiwakikatasa
		);
		DrawFormatString(187+yokozure,296,CRWHITE,"左脇堅 %3d",
		temp_rikisidata_nisi.hidariwakikatasa
		);
		DrawFormatString(187+yokozure,312,CRWHITE,"あてが %3d",
		temp_rikisidata_nisi.ategai
		);
		DrawFormatString(187+yokozure,328,CRWHITE,"右返し %3d",
		temp_rikisidata_nisi.migikaesi
		);
		DrawFormatString(187+yokozure,344,CRWHITE,"左返し %3d",
		temp_rikisidata_nisi.hidarikaesi
		);
		DrawFormatString(287+yokozure,104,CRWHITE,"右絞り %3d",
		temp_rikisidata_nisi.migisibori
		);
		DrawFormatString(287+yokozure,120,CRWHITE,"左絞り %3d",
		temp_rikisidata_nisi.hidarisibori
		);
		DrawFormatString(287+yokozure,136,CRWHITE,"右抱込 %3d",
		temp_rikisidata_nisi.migikakaekomi
		);
		DrawFormatString(287+yokozure,152,CRWHITE,"左抱込 %3d",
		temp_rikisidata_nisi.hidarikakaekomi
		);
		DrawFormatString(287+yokozure,168,CRWHITE,"ひきつ %3d",
		temp_rikisidata_nisi.hikituke
		);
		DrawFormatString(287+yokozure,184,CRWHITE,"右握力 %3d",
		temp_rikisidata_nisi.migiakuryoku
		);
		DrawFormatString(287+yokozure,200,CRWHITE,"左握力 %3d",
		temp_rikisidata_nisi.hidariakuryoku
		);
		DrawFormatString(287+yokozure,216,CRWHITE,"スタミ %3d",
		temp_rikisidata_nisi.stamina
		);
		DrawFormatString(287+yokozure,232,CRWHITE,"根性　 %3d",
		temp_rikisidata_nisi.konjou
		);
		DrawFormatString(287+yokozure,248,CRWHITE,"粘り　 %3d",
		temp_rikisidata_nisi.nebari
		);
		DrawFormatString(287+yokozure,264,CRWHITE,"足運び %3d",
		temp_rikisidata_nisi.asihakobi
		);
		DrawFormatString(287+yokozure,280,CRWHITE,"柔軟性 %3d",
		temp_rikisidata_nisi.juunansei
		);
		DrawFormatString(287+yokozure,296,CRWHITE,"頑固　 %3d",
		100-temp_rikisidata_nisi.zunou
		);
		DrawFormatString(387+yokozure,104,CRWHITE,"右上投%3d",
		temp_rikisidata_nisi.migiuwatenage
		);
		DrawFormatString(387+yokozure,120,CRWHITE,"左上投%3d",
		temp_rikisidata_nisi.hidariuwatenage
		);
		DrawFormatString(387+yokozure,136,CRWHITE,"右下投%3d",
		temp_rikisidata_nisi.migisitatenage
		);
		DrawFormatString(387+yokozure,152,CRWHITE,"左下投%3d",
		temp_rikisidata_nisi.hidarisitatenage
		);
		DrawFormatString(387+yokozure,168,CRWHITE,"右小投%3d",
		temp_rikisidata_nisi.migikotenage
		);
		DrawFormatString(387+yokozure,184,CRWHITE,"左小投%3d",
		temp_rikisidata_nisi.hidarikotenage
		);
		DrawFormatString(387+yokozure,200,CRWHITE,"右掬投%3d",
		temp_rikisidata_nisi.migisukuinage
		);
		DrawFormatString(387+yokozure,216,CRWHITE,"左掬投%3d",
		temp_rikisidata_nisi.hidarisukuinage
		);

		//力士画像表示
		if (rikisigraphflag==1){
			shukushou_tate_gazou=(int)(220-temp_rikisidata_nisi.sinchou)*2/3;
			shukushou_yoko_gazou=(int)((250-temp_rikisidata_nisi.taijuu)/2);
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
			sprintf(temp_filename,"rikisigraph/rikisi%d.png\0",x);
			rikisi_front_temp = LoadGraph( temp_filename ) ;
			DrawModiGraph(x1_gazou+yokozure,y1_gazou ,	x2_gazou+yokozure,y2_gazou , x3_gazou+yokozure,y3_gazou , x4_gazou+yokozure,y4_gazou , rikisi_front_temp , TRUE ) ;
		}
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	}
	
	return;
}

void fight_backscreen_net(int higasiid,int nisiid)
{
	int i;
	int shukushou_tate_higasi=0;
	int shukushou_tate_nisi=0;
	int shukushou_yoko_higasi=0;
	int shukushou_yoko_nisi=0;
	int x1_higasi=0;//土俵位置を示す力士の座標変数
	int y1_higasi=0;
	int x2_higasi=0;
	int y2_higasi=0;
	int x3_higasi=0;
	int y3_higasi=0;
	int x4_higasi=0;
	int y4_higasi=0;
	int x1_nisi=0;
	int y1_nisi=0;
	int x2_nisi=0;
	int y2_nisi=0;
	int x3_nisi=0;
	int y3_nisi=0;
	int x4_nisi=0;
	int y4_nisi=0;
	int x_higasi_lefthand_uwate=386;
	int y_higasi_lefthand_uwate=123;
	int x_higasi_lefthand_sitate=386;
	int y_higasi_lefthand_sitate=123+24;
	int x_higasi_righthand_uwate=386+16;
	int y_higasi_righthand_uwate=123+74+24;
	int x_higasi_righthand_sitate=386+16;
	int y_higasi_righthand_sitate=123+74;
	int x_nisi_righthand_uwate=405;
	int y_nisi_righthand_uwate=123;
	int x_nisi_righthand_sitate=405;
	int y_nisi_righthand_sitate=123+24;
	int x_nisi_lefthand_uwate=405+16;
	int y_nisi_lefthand_uwate=123+74+24;
	int x_nisi_lefthand_sitate=405+16;
	int y_nisi_lefthand_sitate=123+74;



	//game_main_backscreen();//基本画面表示
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


	//電光掲示板表示
	//SetFontSize(12);
	//if( ProcessMessage() == -1 ){mode=1;return ;}
	DrawStringToHandle(12,6,"取　組　文　字　中　継",CRWHITE,FontHandle12);
//本当はここでモードと難易度表示
/*	DrawFormatStringToHandle(12,6,CRWHITE,FontHandle12,"%6d年",year);//年数、開催場所、○○日目表示
	if (superrikisisuu[2]==0 && superrikisisuu[6]==0){
		DrawStringToHandle(3,24,"箱庭小相撲",CRWHITE,FontHandle12);
	}else if (superrikisisuu[2]==1){
		DrawStringToHandle(3,24,"育成小相撲",CRWHITE,FontHandle12);
	}else if (superrikisisuu[2]==0 && superrikisisuu[6]==1){
		DrawStringToHandle(3,24,"縛箱小相撲",CRWHITE,FontHandle12);
	}
	DrawFormatStringToHandle(93,24,CRWHITE,FontHandle12,"%6d年",year);//年数、開催場所、○○日目表示
*/
	DrawFormatString(187,24+16,CRGREEN,"%s",//四股名表示
	namestring[rikisidata[higasiid].nameid]);
	DrawFormatString(411,24+16,CRGREEN,"%s",//相手の四股名表示
	namestring[rikisidata[nisiid].nameid]);
	DrawFormatString(187,24+16+16,CRWHITE,"%d才",
	rikisidata[higasiid].age);
	DrawFormatString(411,24+16+16,CRWHITE,"%d才",
	rikisidata[nisiid].age);

	//力士画像表示
	shukushou_tate_higasi=(int)(220-temp_rikisidata_higasi.sinchou)*2/3;
	shukushou_tate_nisi=(int)(220-temp_rikisidata_nisi.sinchou)*2/3;
	shukushou_yoko_higasi=(int)((250-temp_rikisidata_higasi.taijuu)/2);
	shukushou_yoko_nisi=(int)((250-temp_rikisidata_nisi.taijuu)/2);

	if (shukushou_tate_higasi<0){shukushou_tate_higasi=0;}
	if (shukushou_tate_nisi<0){shukushou_tate_nisi=0;}
	if (shukushou_yoko_higasi<0){shukushou_yoko_higasi=0;}
	if (shukushou_yoko_nisi<0){shukushou_yoko_nisi=0;}

	if (offenseid==higasiid){
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

	x1_higasi=187+shukushou_yoko_higasi;
	y1_higasi=120+shukushou_tate_higasi;
	x2_higasi=x1_higasi+128-shukushou_yoko_higasi;
	y2_higasi=y1_higasi;
	x3_higasi=x2_higasi;
	y3_higasi=y1_higasi+128-shukushou_tate_higasi;
	x4_higasi=x1_higasi;
	y4_higasi=y3_higasi;
	x1_nisi=508;
	y1_nisi=120+shukushou_tate_nisi;
	x2_nisi=x1_nisi+128-shukushou_yoko_nisi;
	y2_nisi=y1_nisi;
	x3_nisi=x2_nisi;
	y3_nisi=y1_nisi+128-shukushou_tate_nisi;
	x4_nisi=x1_nisi;
	y4_nisi=y3_nisi;

	DrawBox( 187 , 120 , 637 , 366 , GetColor(99,137,66) , TRUE) ;
	//力士の大きさをわかりやすいように表示
		DrawModiGraph(x1_higasi,y1_higasi ,	x2_higasi,y2_higasi , x3_higasi,y3_higasi , x4_higasi,y4_higasi , rikisi_front_higasi , TRUE ) ;//東力士
		DrawModiGraph(x1_nisi,y1_nisi ,	x2_nisi,y2_nisi , x3_nisi,y3_nisi , x4_nisi,y4_nisi , rikisi_front_nisi , TRUE ) ;//西力士
	
	//力士画像で位置を表示
	if (higasi_state_balance<(int)(rikisidata[higasiid].balance/10)+1
	 && higasi_state_balance<6){
	 	if (higasi_state_balance<1){
			DrawModiGraph( 400+state_ichi*32-16-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334 , 400+state_ichi*32-16-(x2_higasi-x1_higasi) , 334 , rikisi_lostbalance , TRUE ) ;
			//DrawGraph(400+state_ichi*32-64-16 , 270 , rikisi_lostbalance , TRUE ) ;//東力士
	 	}else{
			DrawModiGraph( 400+state_ichi*32-16-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334 , 400+state_ichi*32-16-(x2_higasi-x1_higasi) , 334 , rikisi_lostbalance2 , TRUE ) ;
	 	}
		//DrawString(187,136,"バランス崩れ",CRRED);
	}else if (state_kyori==FAR_STATE_KYORI){
		if (higasi_state_jouge==HIGH_STATE_JOUGE){
			if (rikisihyoji_megatenflag==1){
				DrawModiGraph( 400+state_ichi*32-16-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334 , 400+state_ichi*32-16-(x2_higasi-x1_higasi) , 334 , rikisi_high_megaten , TRUE ) ;
			}else{
				DrawModiGraph( 400+state_ichi*32-16-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334 , 400+state_ichi*32-16-(x2_higasi-x1_higasi) , 334 , rikisi_high , TRUE ) ;
				//DrawGraph(400+state_ichi*32-64-16 , 270 , rikisi_high , TRUE ) ;//東力士
			}
		}else if (higasi_state_jouge==MIDDLE_STATE_JOUGE){
			if (rikisihyoji_megatenflag==1){
				DrawModiGraph( 400+state_ichi*32-16-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334 , 400+state_ichi*32-16-(x2_higasi-x1_higasi) , 334 , rikisi_middle_megaten , TRUE ) ;
			}else{
				DrawModiGraph( 400+state_ichi*32-16-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334 , 400+state_ichi*32-16-(x2_higasi-x1_higasi) , 334 , rikisi_middle , TRUE ) ;
			}
		}else{
			if (rikisihyoji_megatenflag==1){
				DrawModiGraph( 400+state_ichi*32-16-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334 , 400+state_ichi*32-16-(x2_higasi-x1_higasi) , 334 , rikisi_low_megaten , TRUE ) ;
			}else{
				DrawModiGraph( 400+state_ichi*32-16-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32-16 , 334 , 400+state_ichi*32-16-(x2_higasi-x1_higasi) , 334 , rikisi_low , TRUE ) ;
			}
		}
	}else{
		if (higasi_state_jouge==HIGH_STATE_JOUGE){
			if (rikisihyoji_megatenflag==1){
				DrawModiGraph( 400+state_ichi*32-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32 , 334 , 400+state_ichi*32-(x2_higasi-x1_higasi) , 334 , rikisi_high_megaten , TRUE ) ;
			}else{
				DrawModiGraph( 400+state_ichi*32-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32 , 334 , 400+state_ichi*32-(x2_higasi-x1_higasi) , 334 , rikisi_high , TRUE ) ;
				//DrawGraph(400+state_ichi*32-64 , 270 , rikisi_high , TRUE ) ;//東力士
			}
		}else if (higasi_state_jouge==MIDDLE_STATE_JOUGE){
			if (rikisihyoji_megatenflag==1){
				DrawModiGraph( 400+state_ichi*32-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32 , 334 , 400+state_ichi*32-(x2_higasi-x1_higasi) , 334 , rikisi_middle_megaten , TRUE ) ;
			}else{
				DrawModiGraph( 400+state_ichi*32-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32 , 334 , 400+state_ichi*32-(x2_higasi-x1_higasi) , 334 , rikisi_middle , TRUE ) ;
			}
		}else{
			if (rikisihyoji_megatenflag==1){
				DrawModiGraph( 400+state_ichi*32-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32 , 334 , 400+state_ichi*32-(x2_higasi-x1_higasi) , 334 , rikisi_low_megaten , TRUE ) ;
			}else{
				DrawModiGraph( 400+state_ichi*32-(x2_higasi-x1_higasi), 334-(y4_higasi-y1_higasi) , 400+state_ichi*32 , 334-(y4_higasi-y1_higasi) , 400+state_ichi*32 , 334 , 400+state_ichi*32-(x2_higasi-x1_higasi) , 334 , rikisi_low , TRUE ) ;
			}
		}
	}
	if (nisi_state_balance<(int)(rikisidata[nisiid].balance/10)+1
	 && nisi_state_balance<6){
	 	if (nisi_state_balance<1){
			DrawModiGraph( 400+state_ichi*32+16, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32+16 , 334 , rikisi_lostbalance_nisi , TRUE ) ;
			//DrawTurnGraph(400+state_ichi*32+16 , 270 , rikisi_lostbalance , TRUE ) ;//西力士
	 	}else{
			DrawModiGraph( 400+state_ichi*32+16, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32+16 , 334 , rikisi_lostbalance2_nisi , TRUE ) ;
	 	}
		//DrawString(535,136,"バランス崩れ",CRRED);
	}else if (state_kyori==FAR_STATE_KYORI){
		if (nisi_state_jouge==HIGH_STATE_JOUGE){
			if (rikisihyoji_megatenflag==2){
				DrawModiGraph( 400+state_ichi*32+16, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32+16 , 334 , rikisi_high_nisi_megaten , TRUE ) ;
			}else{
				DrawModiGraph( 400+state_ichi*32+16, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32+16 , 334 , rikisi_high_nisi , TRUE ) ;
				//DrawTurnGraph(400+state_ichi*32+16 , 270 , rikisi_high , TRUE ) ;//西力士
			}
		}else if (nisi_state_jouge==MIDDLE_STATE_JOUGE){
			if (rikisihyoji_megatenflag==2){
				DrawModiGraph( 400+state_ichi*32+16, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32+16 , 334 , rikisi_middle_nisi_megaten , TRUE ) ;
			}else{
				DrawModiGraph( 400+state_ichi*32+16, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32+16 , 334 , rikisi_middle_nisi , TRUE ) ;
			}
		}else{
			if (rikisihyoji_megatenflag==2){
				DrawModiGraph( 400+state_ichi*32+16, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32+16 , 334 , rikisi_low_nisi_megaten , TRUE ) ;
			}else{
				DrawModiGraph( 400+state_ichi*32+16, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+16+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32+16 , 334 , rikisi_low_nisi , TRUE ) ;
			}
		}
	}else{
		if (nisi_state_jouge==HIGH_STATE_JOUGE){
			if (rikisihyoji_megatenflag==2){
				DrawModiGraph( 400+state_ichi*32, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32 , 334 , rikisi_high_nisi_megaten , TRUE ) ;
			}else{
				DrawModiGraph( 400+state_ichi*32, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32 , 334 , rikisi_high_nisi , TRUE ) ;
				//DrawTurnGraph(400+state_ichi*32 , 270 , rikisi_high , TRUE ) ;//西力士
			}
		}else if (nisi_state_jouge==MIDDLE_STATE_JOUGE){
			if (rikisihyoji_megatenflag==2){
				DrawModiGraph( 400+state_ichi*32, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32 , 334 , rikisi_middle_nisi_megaten , TRUE ) ;
			}else{
				DrawModiGraph( 400+state_ichi*32, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32 , 334 , rikisi_middle_nisi , TRUE ) ;
			}
		}else{
			if (rikisihyoji_megatenflag==2){
				DrawModiGraph( 400+state_ichi*32, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32 , 334 , rikisi_low_nisi_megaten , TRUE ) ;
			}else{
				DrawModiGraph( 400+state_ichi*32, 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+(x2_nisi-x1_nisi) , 334-(y4_nisi-y1_nisi) , 400+state_ichi*32+(x2_nisi-x1_nisi) , 334 , 400+state_ichi*32 , 334 , rikisi_low_nisi , TRUE ) ;
			}
		}
	}
	//四つの状態表示＿手の画像
	if (higasi_state_hidariude==UWATE_STATE_UDE){//東左手
		DrawGraph(x_higasi_lefthand_uwate,y_higasi_lefthand_uwate, hand , TRUE ) ;
	}else if(higasi_state_hidariude==UWATETUKAMI_STATE_UDE){
		DrawGraph(x_higasi_lefthand_uwate,y_higasi_lefthand_uwate, hand_mawasi , TRUE ) ;
	}else if (higasi_state_hidariude==SITATE_STATE_UDE){
		DrawGraph(x_higasi_lefthand_sitate,y_higasi_lefthand_sitate, hand , TRUE ) ;
	}else if(higasi_state_hidariude==SITATETUKAMI_STATE_UDE){
		DrawGraph(x_higasi_lefthand_sitate,y_higasi_lefthand_sitate, hand_mawasi , TRUE ) ;
	}
	if (higasi_state_migiude==UWATE_STATE_UDE){//東右手
		DrawRotaGraph(x_higasi_righthand_uwate,y_higasi_righthand_uwate,1.0,PI, hand , TRUE,TRUE ) ;
	}else if(higasi_state_migiude==UWATETUKAMI_STATE_UDE){
		DrawRotaGraph(x_higasi_righthand_uwate,y_higasi_righthand_uwate,1.0,PI, hand_mawasi , TRUE,TRUE ) ;
	}else if (higasi_state_migiude==SITATE_STATE_UDE){
		DrawRotaGraph(x_higasi_righthand_sitate,y_higasi_righthand_sitate,1.0,PI, hand , TRUE,TRUE ) ;
	}else if(higasi_state_migiude==SITATETUKAMI_STATE_UDE){
		DrawRotaGraph(x_higasi_righthand_sitate,y_higasi_righthand_sitate,1.0,PI, hand_mawasi , TRUE,TRUE ) ;
	}
	if (nisi_state_migiude==UWATE_STATE_UDE){//西右手
		DrawTurnGraph(x_nisi_righthand_uwate,y_nisi_righthand_uwate, hand , TRUE ) ;
	}else if(nisi_state_migiude==UWATETUKAMI_STATE_UDE){
		DrawTurnGraph(x_nisi_righthand_uwate,y_nisi_righthand_uwate, hand_mawasi , TRUE) ;
	}else if (nisi_state_migiude==SITATE_STATE_UDE){
		DrawTurnGraph(x_nisi_righthand_sitate,y_nisi_righthand_sitate, hand , TRUE ) ;
	}else if(nisi_state_migiude==SITATETUKAMI_STATE_UDE){
		DrawTurnGraph(x_nisi_righthand_sitate,y_nisi_righthand_sitate, hand_mawasi , TRUE) ;
	}
	if (nisi_state_hidariude==UWATE_STATE_UDE){//西左手
		DrawRotaGraph(x_nisi_lefthand_uwate,y_nisi_lefthand_uwate,1.0,PI, hand , TRUE ) ;
	}else if(nisi_state_hidariude==UWATETUKAMI_STATE_UDE){
		DrawRotaGraph(x_nisi_lefthand_uwate,y_nisi_lefthand_uwate,1.0,PI, hand_mawasi , TRUE ) ;
	}else if (nisi_state_hidariude==SITATE_STATE_UDE){
		DrawRotaGraph(x_nisi_lefthand_sitate,y_nisi_lefthand_sitate,1.0,PI, hand , TRUE ) ;
	}else if(nisi_state_hidariude==SITATETUKAMI_STATE_UDE){
		DrawRotaGraph(x_nisi_lefthand_sitate,y_nisi_lefthand_sitate,1.0,PI, hand_mawasi , TRUE ) ;
	}
	//四つの状態表示＿頭の画像
	if (higasi_state_hidariude==UWATE_STATE_UDE && higasi_state_migiude==UWATE_STATE_UDE){//両上手
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==UWATETUKAMI_STATE_UDE && higasi_state_migiude==UWATE_STATE_UDE){//両上手
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==UWATE_STATE_UDE && higasi_state_migiude==UWATETUKAMI_STATE_UDE){//両上手
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==UWATETUKAMI_STATE_UDE && higasi_state_migiude==UWATETUKAMI_STATE_UDE){//両上手
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==SITATE_STATE_UDE && higasi_state_migiude==SITATE_STATE_UDE){//両差し
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==SITATETUKAMI_STATE_UDE && higasi_state_migiude==SITATE_STATE_UDE){//両差し
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==SITATE_STATE_UDE && higasi_state_migiude==SITATETUKAMI_STATE_UDE){//両差し
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==SITATETUKAMI_STATE_UDE && higasi_state_migiude==SITATETUKAMI_STATE_UDE){//両差し
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==UWATE_STATE_UDE && higasi_state_migiude==SITATE_STATE_UDE){//右四つ
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-32)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==UWATETUKAMI_STATE_UDE && higasi_state_migiude==SITATE_STATE_UDE){//右四つ
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-32)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==UWATE_STATE_UDE && higasi_state_migiude==SITATETUKAMI_STATE_UDE){//右四つ
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-32)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==UWATETUKAMI_STATE_UDE && higasi_state_migiude==SITATETUKAMI_STATE_UDE){//右四つ
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-32)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==SITATE_STATE_UDE && higasi_state_migiude==UWATE_STATE_UDE){//左四つ
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-0)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==SITATETUKAMI_STATE_UDE && higasi_state_migiude==UWATE_STATE_UDE){//左四つ
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-0)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==SITATE_STATE_UDE && higasi_state_migiude==UWATETUKAMI_STATE_UDE){//左四つ
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-0)/2), atama , TRUE ) ;
	}else if (higasi_state_hidariude==SITATETUKAMI_STATE_UDE && higasi_state_migiude==UWATETUKAMI_STATE_UDE){//左四つ
		DrawGraph(x_higasi_lefthand_uwate-32,(int)((y_higasi_lefthand_uwate+y_higasi_righthand_uwate-0)/2), atama , TRUE ) ;
	}
	if (nisi_state_hidariude==UWATE_STATE_UDE && nisi_state_migiude==UWATE_STATE_UDE){//両上手
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==UWATETUKAMI_STATE_UDE && nisi_state_migiude==UWATE_STATE_UDE){//両上手
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==UWATE_STATE_UDE && nisi_state_migiude==UWATETUKAMI_STATE_UDE){//両上手
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==UWATETUKAMI_STATE_UDE && nisi_state_migiude==UWATETUKAMI_STATE_UDE){//両上手
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==SITATE_STATE_UDE && nisi_state_migiude==SITATE_STATE_UDE){//両差し
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==SITATETUKAMI_STATE_UDE && nisi_state_migiude==SITATE_STATE_UDE){//両差し
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==SITATE_STATE_UDE && nisi_state_migiude==SITATETUKAMI_STATE_UDE){//両差し
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==SITATETUKAMI_STATE_UDE && nisi_state_migiude==SITATETUKAMI_STATE_UDE){//両差し
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-16)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==UWATE_STATE_UDE && nisi_state_migiude==SITATE_STATE_UDE){//右四つ
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-0)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==UWATETUKAMI_STATE_UDE && nisi_state_migiude==SITATE_STATE_UDE){//右四つ
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-0)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==UWATE_STATE_UDE && nisi_state_migiude==SITATETUKAMI_STATE_UDE){//右四つ
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-0)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==UWATETUKAMI_STATE_UDE && nisi_state_migiude==SITATETUKAMI_STATE_UDE){//右四つ
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-0)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==SITATE_STATE_UDE && nisi_state_migiude==UWATE_STATE_UDE){//左四つ
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-32)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==SITATETUKAMI_STATE_UDE && nisi_state_migiude==UWATE_STATE_UDE){//左四つ
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-32)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==SITATE_STATE_UDE && nisi_state_migiude==UWATETUKAMI_STATE_UDE){//左四つ
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-32)/2), atama , TRUE ) ;
	}else if (nisi_state_hidariude==SITATETUKAMI_STATE_UDE && nisi_state_migiude==UWATETUKAMI_STATE_UDE){//左四つ
		DrawTurnGraph(x_nisi_lefthand_uwate+16,(int)((y_nisi_lefthand_uwate+y_nisi_righthand_uwate-32)/2), atama , TRUE ) ;
	}

/*
	//スタミナ表示
	if (defenseid==higasiid){
		DrawFormatString(187,120,CRWHITE,"スタミナ　%2d",defense_stamina);
		DrawFormatString(535,120,CRWHITE,"スタミナ　%2d",offense_stamina);
	}else{
		DrawFormatString(187,120,CRWHITE,"スタミナ　%2d",offense_stamina);
		DrawFormatString(535,120,CRWHITE,"スタミナ　%2d",defense_stamina);
	}
*/
	//rikisihyoji_megatenflag=0;

	return;
}

