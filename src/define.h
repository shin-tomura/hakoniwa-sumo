#define INPUTSUU 115//能力値37*2+立合いフラグ1+立合い後の状況40＝115
//#define HIDDENSUU 50//中間層の数
#define OUTPUTSUU 29//立会狙い5+立会勢い4+技選択(22-2(なしと中間処理)=20)＝29

#define AIDATABYTESUU 386//一人分のaidataバイト数
						//aidataの一つの要素数/4（割り切れなければ+1）
#define AIDATATATIAIBYTESUU 5//tatiaipatternid_higasiとnisiの0~19を2ビットで格納予定なので20種類/4
#define TOSIYORISUU 400
#define ITIMONSUU 54
#define TOSIYORI_RETIREAGE 65

#define RETIREMAXFILESUU 1000
#define SIKONA_ATO 100
#define SICHOUSONSUU 2724
#define GANNEN 1//このゲームの元年
#define DEATHAGE 41//強制的に引退させる年齢
#define WAZAPATTERNSUU 100
#define TATIAIPATTERNSUU 20
#define PI	3.1415926535897932384626433832795f
#define RIKISISUU 708
#define RIKISISUU_MAKUUTI 40
#define RIKISISUU_JYUURYOU 28
#define RIKISISUU_MAKUSITA 120
#define RIKISISUU_SANDANME 200
#define RIKISISUU_JONIDAN 240
#define RIKISISUU_JONOKUTI 80
#define HEYASUU 54
#define CRUP GetColor(150,150,255)//自部屋力士の能力値がアップ
#define CRDOWN GetColor(255,150,150)
#define CREQUAL GetColor(190,190,190)
#define CRTARGET GetColor(40,120,70)//
#define CRBLACK GetColor(0,0,0)//黒色
#define CRTAB GetColor(104,126,82)
#define CRWHITE GetColor(190,190,190)//白色
//#define CRWHITE GetColor(0,0,0)//白色→色変えた
//#define CRGREEN GetColor(0,255,0)//緑色
#define CRGRAY GetColor(120,120,120)
#define CRGREEN GetColor(0,230,0)
#define CRRED GetColor(230,0,0)//赤色
#define CRPURPLE GetColor(196,0,204)//紫色
#define CRLINE GetColor(150,150,150)//線の色
#define CRKEIJIBANON GetColor(70,184,109)//電光掲示板が光っているときの色
#define CRKEIJIBANOFF GetColor(158,152,171)//電光掲示板の光ってないときの色
#define CRBACK GetColor(0,0,0)
#define FONTSIZE_YOKODUNA 24;//24がMAX
#define FONTSIZE_OOZEKI 22;
#define FONTSIZE_SEKIWAKE 18;
#define FONTSIZE_KOMUSUBI 17;
#define FONTSIZE_MAEGASIRA 16;
#define FONTSIZE_JYUURYOU 14;
#define FONTSIZE_MAKUSITA 12;
#define FONTSIZE_SANDANME 11;
#define FONTSIZE_JONIDAN 10;
#define FONTSIZE_JONOKUTI 9;

#define BUTTONUP_X1 148//UPボタンの表示位置
#define BUTTONUP_Y1 78//
#define BUTTONUP_X2 165//
#define BUTTONUP_Y2 95//
#define BUTTONDOWN_X1 166//DOWNボタンの表示位置
#define BUTTONDOWN_Y1 78//
#define BUTTONDOWN_X2 183//
#define BUTTONDOWN_Y2 95//
#define BUTTONUPFAST_X1 601//UPFASTボタンの表示位置
#define BUTTONUPFAST_Y1 62//
#define BUTTONUPFAST_X2 618//
#define BUTTONUPFAST_Y2 79//
#define BUTTONDOWNFAST_X1 619//DOWNFASTボタンの表示位置
#define BUTTONDOWNFAST_Y1 62//
#define BUTTONDOWNFAST_X2 636//
#define BUTTONDOWNFAST_Y2 79//
#define BUTTONKENSAKULEFT_MOJI "検索"//ボタンAに表示する文字
#define BUTTONKENSAKULEFT_X1 111//メニューボタンAの表示位置、左上(3,3)、右下(92,20)
#define BUTTONKENSAKULEFT_Y1 78//
#define BUTTONKENSAKULEFT_X2 143//
#define BUTTONKENSAKULEFT_Y2 93//
#define BUTTONKENSAKURIGHT_MOJI "検索"//ボタンAに表示する文字
#define BUTTONKENSAKURIGHT_X1 598//メニューボタンAの表示位置、左上(3,3)、右下(92,20)
#define BUTTONKENSAKURIGHT_Y1 62//
#define BUTTONKENSAKURIGHT_X2 630//
#define BUTTONKENSAKURIGHT_Y2 77//
#define BUTTONA_MOJI "ＭＥＮＵ"//ボタンAに表示する文字
#define BUTTONA_X1 3//メニューボタンAの表示位置、左上(3,3)、右下(92,20)
#define BUTTONA_Y1 5//
#define BUTTONA_X2 92//
#define BUTTONA_Y2 20//
#define BUTTONB_MOJI "相撲部屋 "//ボタンBに表示する文字
#define BUTTONB_X1 93//メニューボタンBの表示位置
#define BUTTONB_Y1 5//
#define BUTTONB_X2 182//
#define BUTTONB_Y2 20//
#define BUTTONC_MOJI "力士情報"//ボタンCに表示する文字
#define BUTTONC_X1 183//メニューボタンCの表示位置、
#define BUTTONC_Y1 5//
#define BUTTONC_X2 272//
#define BUTTONC_Y2 20//
#define BUTTOND_MOJI "番付表示"//ボタンDに表示する文字
#define BUTTOND_X1 273//メニューボタンDの表示位置、
#define BUTTOND_Y1 5//
#define BUTTOND_X2 362//
#define BUTTOND_Y2 20//
#define BUTTONE_MOJI "記録台帳"//ボタンEに表示する文字
#define BUTTONE_X1 363//メニューボタンEの表示位置、
#define BUTTONE_Y1 5//
#define BUTTONE_X2 452//
#define BUTTONE_Y2 20//
#define BUTTONF_MOJI "ニュース"//ボタンFに表示する文字
#define BUTTONF_X1 453//メニューボタンFの表示位置、
#define BUTTONF_Y1 5//
#define BUTTONF_X2 542//
#define BUTTONF_Y2 20//
#define BUTTONG_MOJI "進む＞＞"//ボタンGに表示する文字
#define BUTTONG_X1 543//メニューボタンGの表示位置、
#define BUTTONG_Y1 5//
#define BUTTONG_X2 632//
#define BUTTONG_Y2 20//
#define BUTTONG2_MOJI "　戻る　"//ボタンG2に表示する文字
#define BUTTON_MOJI_REALMODE "テレ"//
#define BUTTON_MOJI_RETIRE "引退"//
#define BUTTON_MOJI_YAO "交渉"//
#define BUTTON_MOJI_EDIT "編集"//
#define BUTTON_MOJI_SAKUSENHENKOU "作戦"//
#define BUTTON_MOJI_JOUKENHENKOU0 "既定"//
#define BUTTON_MOJI_JOUKENHENKOU1 "簡易"//
#define BUTTON_MOJI_JOUKENHENKOU2 "詳細"//
#define BUTTON_MOJI_JOUKENHENKOU3 "本人"//
#define BUTTON_MOJI_JOUKENHENKOU4 "deep"//

////////////////////////////////////////////////////////////////////
#define jflagSHURUISUU 16
#define typeSHURUISUU 10
#define HUMANSUU 10
#define MAXFILESUU 1000
#define HYOUJOUSHURUISUU 11
#define WADAISUU 6//話題の種類
#define AISUU 1000//id0～32767のうちのAIの数、若い番号の方から採番する0～707が力士のAIのidで力士IDと一致
					//708～999が一般AI
#define KENSAKUHOJISUU 10//検索用の序列化データのの保持数
#define KENSAKUFUKASA 10//いくつ前の発言まで追っかけていくか。少なくとも3以上にしないと、一つのキャッチボールすらとらえられないので注意
#define MAXMOJISUU_kaiwa 51//半角文字換算
#define KAKOHYOJISUU 100//タイムライン上の過去の発言の表示数
						//ちなみにAIにはkako_str[KAKOHYOJISUU]で同じ発言防止処理をしている


struct human_data{
	char type;//0→既定値、1→力士言葉タイプ、２→男言葉タイプ、3→女言葉タイプなど
};

struct ai_data{
	char sekkyokusei;//3人以上での会話の場合の発言率に関係
	char hyoujou_konomi[HYOUJOUSHURUISUU];//AIは相手のどんな表情を好む
										//のかの表情ごとの好み度合い、表情の種類分
										//AIの性格をこれで変えられるはず
	//ここまではkaiwadataに記録しなくても良いはず
	//ここから下はkaiwadataに記録するもの
	char type;//0→既定値、1→力士言葉タイプ、２→男言葉タイプ、3→女言葉タイプなど
};

struct wrikisi_data{
	int wrikisiid;//話題対象力士ID(画像ID)
	char sumoflag;//ビット処理で勝ち負け状況を記録
					//左から１番目→今日の勝ちフラグ
					//2番目→今日の負けフラグ
					//3番目→休場中フラグ
					//4番目→注射勝ちフラグ
					//5番目→注射負けフラグ
					//6番目→
					//7番目→
					//8番目→
	char suu_winlost;//上位4ビットに勝ち星数、下位4ビットに負け数
	char nokoribansuu;//上位4ビットに残り番数

};
//////////////////////////////////////////////////////////////////////////////////////////////////


#define	b00000000 0x00
#define	b00000001 0x01
#define	b00000010 0x02
#define	b00000011 0x03
#define	b00000100 0x04
#define	b00000101 0x05
#define	b00000110 0x06
#define	b00000111 0x07
#define	b00001000 0x08
#define	b00001001 0x09
#define	b00001010 0x0a
#define	b00001011 0x0b
#define	b00001100 0x0c
#define	b00001101 0x0d
#define	b00001110 0x0e
#define	b00001111 0x0f

#define	b00010000 0x10
#define	b00010001 0x11
#define	b00010010 0x12
#define	b00010011 0x13
#define	b00010100 0x14
#define	b00010101 0x15
#define	b00010110 0x16
#define	b00010111 0x17
#define	b00011000 0x18
#define	b00011001 0x19
#define	b00011010 0x1a
#define	b00011011 0x1b
#define	b00011100 0x1c
#define	b00011101 0x1d
#define	b00011110 0x1e
#define	b00011111 0x1f

#define	b00100000 0x20
#define	b00100001 0x21
#define	b00100010 0x22
#define	b00100011 0x23
#define	b00100100 0x24
#define	b00100101 0x25
#define	b00100110 0x26
#define	b00100111 0x27
#define	b00101000 0x28
#define	b00101001 0x29
#define	b00101010 0x2a
#define	b00101011 0x2b
#define	b00101100 0x2c
#define	b00101101 0x2d
#define	b00101110 0x2e
#define	b00101111 0x2f

#define	b00110000 0x30
#define	b00110001 0x31
#define	b00110010 0x32
#define	b00110011 0x33
#define	b00110100 0x34
#define	b00110101 0x35
#define	b00110110 0x36
#define	b00110111 0x37
#define	b00111000 0x38
#define	b00111001 0x39
#define	b00111010 0x3a
#define	b00111011 0x3b
#define	b00111100 0x3c
#define	b00111101 0x3d
#define	b00111110 0x3e
#define	b00111111 0x3f

#define	b01000000 0x40
#define	b01000001 0x41
#define	b01000010 0x42
#define	b01000011 0x43
#define	b01000100 0x44
#define	b01000101 0x45
#define	b01000110 0x46
#define	b01000111 0x47
#define	b01001000 0x48
#define	b01001001 0x49
#define	b01001010 0x4a
#define	b01001011 0x4b
#define	b01001100 0x4c
#define	b01001101 0x4d
#define	b01001110 0x4e
#define	b01001111 0x4f

#define	b01010000 0x50
#define	b01010001 0x51
#define	b01010010 0x52
#define	b01010011 0x53
#define	b01010100 0x54
#define	b01010101 0x55
#define	b01010110 0x56
#define	b01010111 0x57
#define	b01011000 0x58
#define	b01011001 0x59
#define	b01011010 0x5a
#define	b01011011 0x5b
#define	b01011100 0x5c
#define	b01011101 0x5d
#define	b01011110 0x5e
#define	b01011111 0x5f

#define	b01100000 0x60
#define	b01100001 0x61
#define	b01100010 0x62
#define	b01100011 0x63
#define	b01100100 0x64
#define	b01100101 0x65
#define	b01100110 0x66
#define	b01100111 0x67
#define	b01101000 0x68
#define	b01101001 0x69
#define	b01101010 0x6a
#define	b01101011 0x6b
#define	b01101100 0x6c
#define	b01101101 0x6d
#define	b01101110 0x6e
#define	b01101111 0x6f

#define	b01110000 0x70
#define	b01110001 0x71
#define	b01110010 0x72
#define	b01110011 0x73
#define	b01110100 0x74
#define	b01110101 0x75
#define	b01110110 0x76
#define	b01110111 0x77
#define	b01111000 0x78
#define	b01111001 0x79
#define	b01111010 0x7a
#define	b01111011 0x7b
#define	b01111100 0x7c
#define	b01111101 0x7d
#define	b01111110 0x7e
#define	b01111111 0x7f

#define	b10000000 0x80
#define	b10000001 0x81
#define	b10000010 0x82
#define	b10000011 0x83
#define	b10000100 0x84
#define	b10000101 0x85
#define	b10000110 0x86
#define	b10000111 0x87
#define	b10001000 0x88
#define	b10001001 0x89
#define	b10001010 0x8a
#define	b10001011 0x8b
#define	b10001100 0x8c
#define	b10001101 0x8d
#define	b10001110 0x8e
#define	b10001111 0x8f

#define	b10010000 0x90
#define	b10010001 0x91
#define	b10010010 0x92
#define	b10010011 0x93
#define	b10010100 0x94
#define	b10010101 0x95
#define	b10010110 0x96
#define	b10010111 0x97
#define	b10011000 0x98
#define	b10011001 0x99
#define	b10011010 0x9a
#define	b10011011 0x9b
#define	b10011100 0x9c
#define	b10011101 0x9d
#define	b10011110 0x9e
#define	b10011111 0x9f

#define	b10100000 0xa0
#define	b10100001 0xa1
#define	b10100010 0xa2
#define	b10100011 0xa3
#define	b10100100 0xa4
#define	b10100101 0xa5
#define	b10100110 0xa6
#define	b10100111 0xa7
#define	b10101000 0xa8
#define	b10101001 0xa9
#define	b10101010 0xaa
#define	b10101011 0xab
#define	b10101100 0xac
#define	b10101101 0xad
#define	b10101110 0xae
#define	b10101111 0xaf

#define	b10110000 0xb0
#define	b10110001 0xb1
#define	b10110010 0xb2
#define	b10110011 0xb3
#define	b10110100 0xb4
#define	b10110101 0xb5
#define	b10110110 0xb6
#define	b10110111 0xb7
#define	b10111000 0xb8
#define	b10111001 0xb9
#define	b10111010 0xba
#define	b10111011 0xbb
#define	b10111100 0xbc
#define	b10111101 0xbd
#define	b10111110 0xbe
#define	b10111111 0xbf


#define	b11000000 0xc0
#define	b11000001 0xc1
#define	b11000010 0xc2
#define	b11000011 0xc3
#define	b11000100 0xc4
#define	b11000101 0xc5
#define	b11000110 0xc6
#define	b11000111 0xc7
#define	b11001000 0xc8
#define	b11001001 0xc9
#define	b11001010 0xca
#define	b11001011 0xcb
#define	b11001100 0xcc
#define	b11001101 0xcd
#define	b11001110 0xce
#define	b11001111 0xcf

#define	b11010000 0xd0
#define	b11010001 0xd1
#define	b11010010 0xd2
#define	b11010011 0xd3
#define	b11010100 0xd4
#define	b11010101 0xd5
#define	b11010110 0xd6
#define	b11010111 0xd7
#define	b11011000 0xd8
#define	b11011001 0xd9
#define	b11011010 0xda
#define	b11011011 0xdb
#define	b11011100 0xdc
#define	b11011101 0xdd
#define	b11011110 0xde
#define	b11011111 0xdf

#define	b11100000 0xe0
#define	b11100001 0xe1
#define	b11100010 0xe2
#define	b11100011 0xe3
#define	b11100100 0xe4
#define	b11100101 0xe5
#define	b11100110 0xe6
#define	b11100111 0xe7
#define	b11101000 0xe8
#define	b11101001 0xe9
#define	b11101010 0xea
#define	b11101011 0xeb
#define	b11101100 0xec
#define	b11101101 0xed
#define	b11101110 0xee
#define	b11101111 0xef

#define	b11110000 0xf0
#define	b11110001 0xf1
#define	b11110010 0xf2
#define	b11110011 0xf3
#define	b11110100 0xf4
#define	b11110101 0xf5
#define	b11110110 0xf6
#define	b11110111 0xf7
#define	b11111000 0xf8
#define	b11111001 0xf9
#define	b11111010 0xfa
#define	b11111011 0xfb
#define	b11111100 0xfc
#define	b11111101 0xfd
#define	b11111110 0xfe
#define	b11111111 0xff

struct keiko_data{
	int keikoryou[50];//各能力値ごとの稽古量
	char setteibalance[50];//設定画面で設定したバランス、1左マックス、5中央、9右マックス
};
struct kako_data{
	int nouryokuti[50];
};

struct jouken_data{
	int motitatiaipattern_sakusen[5];
	char motitatiaipattern_jouken[5];
	char joukenflag;//0>デフォルト 1>ユーザー定義(簡易) 2>ユーザー定義(詳細)
	char joukenname[32];
	char joukenwazaid[2][100];//条件別に選択する技、[間合い、0＞far、1＞near][優先順位]
	char jouken[2][11][100];//条件定義、[間合い、0＞far、1＞near][条件の種類][優先順位]
	char joukensentakuritu[2][100];//選択率
};
struct jouken_data2{
	char joukenmaxtrysuu[2][100];//最大試行回数、1から10回、0だと試行回数無制限(表記上は99にするけどね)
};
struct tosiyori_data{//ID0～105は通常年寄、200～299功績一代年寄、300～399期間限定一代年寄
	int age;
	char category;//1Ａカテ、2Ｂカテ、3Ｃカテ、4一代年寄、5元横綱５年期間限定一代年寄、6元大関3年期間限定一代年寄
	int startyear;//就任年（期間限定一代年寄用）
	char shozokuheyaid;//0～53所属部屋ＩＤ、-1空名跡、以下のカッコ以下はやめてすべて-1で統一(-2年寄(一代年寄含)が重複取得（または戻り先として予約）している名跡の場合、-3現役力士が取得（後継者を予定）)
	//int shozokuheyaid_tuusan;//所属部屋通算ＩＤ、-1空名跡、以下のカッコ以下はやめてすべて-1で統一(-2年寄(一代年寄含)が重複取得（または戻り先として予約）している名跡の場合、-3現役力士が取得（後継者を予定）)
	char shozokuitimonid;//0～53所属一門ＩＤ、-1空名跡、以下のカッコ以下はやめてすべて-1で統一(-2年寄(一代年寄含)が重複取得（または戻り先として予約）している名跡の場合、-3現役力士が取得（後継者を予定）)
	//int shozokuitimonid_tuusan;//所属一門通算ＩＤ、-1空名跡、以下のカッコ以下はやめてすべて-1で統一(-2年寄(一代年寄含)が重複取得（または戻り先として予約）している名跡の場合、-3現役力士が取得（後継者を予定）)
	int rikisiid;//現役時の通算力士ＩＤ
	char sikona[12];//現役時四股名
	char sishouflag;//師匠の場合は1
	char namestring[12];//年寄名跡名
	int jinbou;//人望、理事選挙に影響
	char rijiflag;//下位4ビット→0平年寄、1理事長,10までは理事、11副理事、12役員待遇委員、13委員、14主任
					//上位4ビット→0ノーマル、1審判部所属(審判委員)
	int keishousha_rikisiid;//継承者指名受けたか現役力士で株取得した力士ＩＤ（0～707であって通算力士ＩＤではない）、-1は未指名
	int keishousha_tosiyoriid;//継承者指名の年寄ＩＤ（一代年寄の200番台を予定)、-1は未指名
	//継承者指名済みの年寄とレンタル年寄との区別は師匠かどうか(sishouflagが1なら継承者指名済み、0ならレンタル年寄)
	//keishousha_rikisiidに0～707かつshozokuheyaidとshozokuitimonidに0～53が入っている場合は、現役力士が取得株をレンタルしているということだと思う
};
struct itimon_data{
	char namestring[12];
	char shuheyaid;//一門の主部屋のＩＤ、-1は空一門
	int itimonid_tuusan;//通算部屋ID
	int startyear;//一門創設年
	char startmonth;//一門創設月
};
struct heya_data{
	int hpoint;//部屋ポイント
	char yaoflag;//八百長をやる部屋かどうかのフラグ
	int kpoint[HEYASUU];//他の部屋への貸しポイント数
	int keikoryou;//トレーニング量
	char jikosaiko_bandukenameid;
	char jikosaiko_bandukesuuji;
	int yuushoukaisuu;
	int yokodunasuu;
	int heyaid_tuusan;//通算部屋ID
	int startyear;
	char startmonth;
};
struct rikisi_data{
	int rikisiid;//力士の通算のID番号(全員違う番号)
	int nameid;//四股名のID
	int hometownid;//出身地のID
	char heyaid;//所属相撲部屋のＩＤ
	//int heyaid_tuusan;//所属相撲部屋の通算部屋ID
	int age;//年齢
	int age_roukastart;//老化開始年齢
	int hatudohyo_year;//初土俵
	char hatudohyo_month;//初土俵
	int bandukejun;//番付の順位
	char bandukehigasiornisi;//番付が東か西か、1→東、2→西
	char bandukenameid;//番付の名前のＩＤ番号、横綱＞0、大関＞1、関脇＞2、小結＞3、前頭＞4
						//十両＞5、幕下＞6、三段目＞7、序二段＞8、序の口＞9
	char bandukesuuji;//番付の後につく数字の数　例、前頭１３枚目の13
	int ginoushousuu;
	int kantoushousuu;
	int shukunshousuu;//殊勲賞受賞回数
	int kinbosisuu;//金星総数(三役が勝っても入れない)
	int kinbosisuu_konbasho;//今場所の金星数(殊勲賞の目安のためなので小結・関脇が勝った場合も入れる)
	int ginbosisuu_konbasho;//今場所の銀星数(殊勲賞の目安のためなので小結・関脇が勝った場合も入れる、大関に勝った数)
	int makuuti_win;
	int makuuti_lost;
	char jikosaiko_bandukenameid;//自己最高位
	char jikosaiko_bandukesuuji;
	char jikosaiko_tournament;//0＞未出場、1＞１回戦負け、10＞優勝
	int yuushoukaisuu_tournament;
	char kako_yuushouflag[180];//過去180場所で優勝した場所は1
	char kako_bandukehigasiornisi[180];//過去180場所の番付が東か西か、-1で未記録
	char kako_bandukenameid[180];		//[0]が先場所、[17]が18場所前
	char kako_bandukesuuji[180];
	char kako_win[180];
	char kako_lost[180];
	int kako_turncountkonbasho[6][15];//過去6場所15日間の各取組の所要ターン数
	char kako_kimaritekonbasho[6][15][9];//過去6場所15日間の各取組の決まり手
	char kako_winkonbasho[6][15];//過去6場所15日間の各取組の決まり手
	char kako_lostkonbasho[6][15];//過去6場所15日間の各取組の決まり手
	int kako_aitekonbasho[180][15];//過去180場所15日間の各取組の決まり手
	int kiroku_yuushoukaisuu;//通算優勝回数
	int kiroku_renshou;//連勝記録
	int kiroku_renpai;//連敗記録
	int now_renshou;
	int now_renpai;
	int rikisibetu_wintotal[RIKISISUU];//力士ID別の対戦成績（勝ち星）
	int rikisibetu_losttotal[RIKISISUU];//力士ID別の対戦成績(負け数）
	int turncountkonbasho[15];//初日から15日目までの(0～14)取組の所要ターン数
	char kimaritekonbasho[15][9];//初日から15日目まで(0～14)の決まり手string
	char winkonbasho[15];//初日から15日目まで(0～14)で、勝ちなら1が入る、一応念のためint
	char lostkonbasho[15];////初日から15日目まで(0～14)で、負けなら1が入る、9999を入れる時があったけどやめた
	char retirekonbasho;//当場所引退力士は1、いろいろな場面で当場所引退力士をイレギュラー処理しなければならないのでlostkonbasho[0]に9999入れる対応をやめたため
	int aitekonbasho[15];////初日から15日目まで(0～14)の相手のrikisiid、幕下以下で取組ない日は-1
	int torikumijun[15];//初日から14日目まで(0～14)の取り組みの出番の順番、取り組みがない日は-1
	int wintotal;//通算勝ち星
	int losttotal;//通算負け数
	char oozekiyuushouorjunyuushou[3];//過去2場所で、大関での優勝か準優勝があったかどうか
									//[0]が今場所、[1]が先場所で
									//1＞優勝、2＞準優勝
	char sanyakuwin[3];//過去3場所の関脇での勝ち星、[0]が今場所[1]先場所[2]先々場所
	char kadobanflag;//角番大関フラグ、1＞角番大関
	char kadobankaraotitaflag;//１で大関を陥落して最初の場所
	char hadoozekiflag;//大関経験があるかどうかのフラグ
	char torikumimiruflag;//1でこの力士の取組を見る
	char realmodeflag;//1でこの力士の取り組みを実戦で行う
	int motiwazapattern[5];//技パターンID、各力士ごとの持ち技パターンは最大５種類
	int motiwazapattern_sentakuritu[5];//[]内は技パターンID、各持ち技パターンの選択率
	int motitatiaipattern[5];//立会いパターンID、各力士ごとの立会いパターンは最大５種類
	int motitatiaipattern_sentakuritu[5];//[]内は立会いパターンID、各立会いパターンの選択率
	char soujukuflag;//早熟フラグ、1＞早熟、2＞超早熟
	char superrikisiflag;//AIの取組前自動稽古回数
	int sinchou;
	int sinchou_max;
	int taijuu;
	int taijuu_max;
	int sekkyokusei;
	int binshousei;
	int binshousei_natural;
	int tossinryoku;
	int tossinryoku_max;
	int kerutikara;
	int kerutikara_max;
	int migiwanryoku;
	int migiwanryoku_max;
	int hidariwanryoku;
	int hidariwanryoku_max;
	int balance;
	int balance_max;
	int tatiaigijutu;
	int tatiaigijutu_max;
	int tuki;
	int tuki_max;
	int migiwakikatasa;
	int migiwakikatasa_max;
	int hidariwakikatasa;
	int hidariwakikatasa_max;
	int ategai;
	int ategai_max;
	int migikaesi;
	int migikaesi_max;
	int hidarikaesi;
	int hidarikaesi_max;
	int migisibori;
	int migisibori_max;
	int hidarisibori;
	int hidarisibori_max;
	int migikakaekomi;
	int migikakaekomi_max;
	int hidarikakaekomi;
	int hidarikakaekomi_max;
	int hikituke;
	int hikituke_max;
	int migiakuryoku;
	int migiakuryoku_max;
	int hidariakuryoku;
	int hidariakuryoku_max;
	int stamina;
	int stamina_natural;
	int konjou;
	int nebari;//土俵際の粘り
	int nebari_max;
	int zunou;//頭脳(ゲーム内の表示は「頑固」)、COM力士の技パターン選択に影響
	int migiuwatenage;
	int migiuwatenage_max;
	int hidariuwatenage;
	int hidariuwatenage_max;
	int migisitatenage;
	int migisitatenage_max;
	int hidarisitatenage;
	int hidarisitatenage_max;
	int migikotenage;
	int migikotenage_max;
	int hidarikotenage;
	int hidarikotenage_max;
	int migisukuinage;
	int migisukuinage_max;
	int hidarisukuinage;
	int hidarisukuinage_max;
	int asihakobi;
	int asihakobi_max;
	int juunansei;
	int juunansei_max;
	int wazaritu_tukidasi;
	int wazaritu_yorikiri;
	int wazaritu_migiuwatenage;
	int wazaritu_hidariuwatenage;
	int wazaritu_migisitatenage;
	int wazaritu_hidarisitatenage;
	int wazaritu_migikotenage;
	int wazaritu_hidarikotenage;
	int wazaritu_migisukuinage;
	int wazaritu_hidarisukuinage;
	int wazaritu_sonota;
	int wazaritu_tukidasisuu;
	int wazaritu_yorikirisuu;
	int wazaritu_migiuwatenagesuu;
	int wazaritu_hidariuwatenagesuu;
	int wazaritu_migisitatenagesuu;
	int wazaritu_hidarisitatenagesuu;
	int wazaritu_migikotenagesuu;
	int wazaritu_hidarikotenagesuu;
	int wazaritu_migisukuinagesuu;
	int wazaritu_hidarisukuinagesuu;
	int wazaritu_sonotasuu;
	char yao_win;//八百長でかつ予定のフラグ
	char yaowinkonbasho[15];//初日から15日目まで(0～14)で、注射済みなら1が入る、
	char heyastarflag;//部屋の中のスターのフラグ、最優先で八百長で勝たせるように同じ部屋の力士が協力する
	char rinneflag;//輪廻フラグ、1だと能力値のみ輪廻する
};

struct bl_data{//バランス調整用
	int sinchou;
	int sinchou_bunbo;
	int taijuu;
	int taijuu_bunbo;
	int sekkyokusei;
	int sekkyokusei_bunbo;
	int binshousei;
	int binshousei_bunbo;
	int tossinryoku;
	int tossinryoku_bunbo;
	int kerutikara;
	int kerutikara_bunbo;
	int migiwanryoku;
	int migiwanryoku_bunbo;
	int hidariwanryoku;
	int hidariwanryoku_bunbo;
	int balance;
	int balance_bunbo;
	int tatiaigijutu;
	int tatiaigijutu_bunbo;
	int tuki;
	int tuki_bunbo;
	int migiwakikatasa;
	int migiwakikatasa_bunbo;
	int hidariwakikatasa;
	int hidariwakikatasa_bunbo;
	int ategai;
	int ategai_bunbo;
	int migikaesi;
	int migikaesi_bunbo;
	int hidarikaesi;
	int hidarikaesi_bunbo;
	int migisibori;
	int migisibori_bunbo;
	int hidarisibori;
	int hidarisibori_bunbo;
	int migikakaekomi;
	int migikakaekomi_bunbo;
	int hidarikakaekomi;
	int hidarikakaekomi_bunbo;
	int hikituke;
	int hikituke_bunbo;
	int migiakuryoku;
	int migiakuryoku_bunbo;
	int hidariakuryoku;
	int hidariakuryoku_bunbo;
	int stamina;
	int stamina_bunbo;
	int konjou;
	int konjou_bunbo;
	int nebari;
	int nebari_bunbo;
	int migiuwatenage;
	int migiuwatenage_bunbo;
	int hidariuwatenage;
	int hidariuwatenage_bunbo;
	int migisitatenage;
	int migisitatenage_bunbo;
	int hidarisitatenage;
	int hidarisitatenage_bunbo;
	int migikotenage;
	int migikotenage_bunbo;
	int hidarikotenage;
	int hidarikotenage_bunbo;
	int migisukuinage;
	int migisukuinage_bunbo;
	int hidarisukuinage;
	int hidarisukuinage_bunbo;
	int asihakobi;
	int asihakobi_bunbo;
	int juunansei;
	int juunansei_bunbo;
	int zunou;
	int zunou_bunbo;
	int zenryokuritu;//立会いの全力の割合
	int tuyokuritu;
	int ukeritu;
	int henkaritu;
	int yobi[10];//予備
};

struct net_data{
	char netstr1[101];
	char netstr2[101];
	char netstr3[101];
	char netstr4[101];
	char netstr5[101];
	char netstr6[101];
	int stamina_higasi;
	int stamina_nisi;
	int offenseid;
	int defenseid;
	int offense_state_jouge;
	int defense_state_jouge;
	int offense_state_balance;
	int defense_state_balance;
	int offense_state_migiude;
	int offense_state_hidariude;
	int defense_state_migiude;
	int defense_state_hidariude;
	int rikisihyoji_megatenflag;
	int state_ichi;
	int state_kyori;
};
