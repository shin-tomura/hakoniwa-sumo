extern void sikona_kouhosuu(void);
extern void shousaidata_higasi(int junban[20],int higasiid,int nisiid);
extern void shousaidata_nisi(int junban[20],int higasiid,int nisi);
extern void sikona_c(void);
extern void tosiyori(void);
extern void retirerikisihyoji_rikisiid(int x);
extern void retirerikisi_rikisiid(int x);
extern void retirenew(void);
extern void retirerikisi_new(int hyojiheyaid);//引数はプレイヤーの部屋の代わりに表示する部屋のID
extern void retirerikisi_hyoji(long ichijouhou,long ichijouhou_jiheya,long ichijouhou_saikoui);
extern int del_data_csv(void);
extern int del_data_dat(void);
extern int del_save_csv(int num);//引数はセーブスロット番号
extern int del_save_dat(int num);//引数はセーブスロット番号
extern void itimondatahyoji(int itimonID);
extern void menu_itimon(void);
extern void tosiyoridatahyoji(int tosiyoriID);
extern void menu_tosiyori(void);
extern void tosiyorimeihenkou(int x);
extern void torikumisakusei1_kyuujou(void);//初日
extern void torikumisakusei2_kyuujou(void);//2日目以降
extern void bandukesakusei_kyuujou(void);//
extern void kyuujou(void);//場所ごとの休場力士の決定ルーチン
extern void kyuujou_tochuu(void);//その日ごとの休場力士の決定ルーチン
extern void kyuujouhyoji(int x);//現役力士の休場履歴表示
extern void kyuujoushousaisettei_hyoji(void);
extern void kyuujoushousaisettei(void);
extern void shozokurekihyoji(int x);
extern void itimonisekidokuritugouryuu(int heyaid);//一門移籍独立合流処理
extern void itimonnusininaru(int heyaid);//一門主になる処理

extern void kiroku_wazadata(char wazaid,int id1,int id2,char id1_higasiornisi,char tatiaigoflag);
extern void wazabunsekihyoji(int id);

extern void chokuzen(void);
extern void hozon_aidata(int higasiid,int nisiid,int winid);

extern void kaiwa_start(void);

extern void edit_rikisiaidata(int x);

extern void csv_kaiwa_read(void);

extern void csvinput_kaiwa(void);
extern void csvoutput_kaiwa(void);

extern void AIkeiko(int higasiid,int nisiid);
extern void torikumimaekeiko(int x);
extern void aikeikochuuhyoji(void);

/*
extern void net_client(int id);
extern void net_server(int higasiid,int nisiid);
extern int fight_fight_server(int higasiid,int nisiid);//東が勝なら1、西が勝なら2を返す
extern void net(int id);
*/