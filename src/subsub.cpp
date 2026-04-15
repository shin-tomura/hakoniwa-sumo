#include "DxLib.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include "define.h"



extern int mode;

void tosiyori(void)//CSVファイルは正規のがあることを前提として、変換処理のみ
{
	int i,ii,totalbytesuu,mojibytesuu,breakflag;
	char ch;

	FILE *fpsikona;
	FILE *fpsikona2;

//////////////////////
	fpsikona = fopen("data/namestring_riji.csv","rb");
	if( fpsikona == NULL ){
		fclose(fpsikona);
		fpsikona = fopen("data/namestring_riji.csv","w");
		fprintf(fpsikona,"理事長\n");
		fprintf(fpsikona,"第壱部長\n");
		fprintf(fpsikona,"第弐部長\n");
		fprintf(fpsikona,"第参部長\n");
		fprintf(fpsikona,"第四部長\n");
		fprintf(fpsikona,"第五部長\n");
		fprintf(fpsikona,"第六部長\n");
		fprintf(fpsikona,"第七部長\n");
		fprintf(fpsikona,"第八部長\n");
		fprintf(fpsikona,"第九部長\n");
		fclose(fpsikona);
		fpsikona = fopen("data/namestring_riji.csv","rb");
	}
	fpsikona2 = fopen("data/namestring_riji.dat","wb");

	mojibytesuu=0;
	totalbytesuu=0;
	breakflag=0;
	while(1)
	{
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (totalbytesuu>=TOSIYORISUU*21){//理事10人×20バイト(全角5文字分)だけどデータ的に21バイト
			ch=0x00;
			fseek(fpsikona2,-1,SEEK_CUR);
			fwrite(&ch,sizeof(ch),1,fpsikona2);
			break;
		}
		mojibytesuu=0;
		while(1){
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (mojibytesuu>=20){
				ch=0x00;
				fwrite(&ch,sizeof(ch),1,fpsikona2);
				//fwrite(&ch,sizeof(ch),1,fpsikona2);//12バイトにするためもう一度
				fseek(fpsikona,+1,SEEK_CUR);
				totalbytesuu++;
				totalbytesuu++;
				break;
			}else{
				if (fread(&ch,sizeof(ch),1,fpsikona)>=1){
					if (ch==0x0d){
						ch=0x00;
						for (i=mojibytesuu;i<21;i++){//12バイトにするため
							fwrite(&ch,sizeof(ch),1,fpsikona2);
							totalbytesuu++;
						}
						break;
					}else if(ch==0x0a){

					}else{
						fwrite(&ch,sizeof(ch),1,fpsikona2);
						mojibytesuu++;
						totalbytesuu++;
					}
				}else{
					breakflag=1;
					break;
				}
			}
		}
		if (breakflag==1) break;
	}

	fclose(fpsikona);
	fclose(fpsikona2);

	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

//////////////////////
	fpsikona = fopen("data/namestring_tosiyori_genekisikona.csv","rb");
	if( fpsikona == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗ここ？" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return ;
	}
	fpsikona2 = fopen("data/namestring_tosiyori_genekisikona.dat","wb");
	if( fpsikona2 == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return ;
	}

	mojibytesuu=0;
	totalbytesuu=0;
	breakflag=0;
	while(1)
	{
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (totalbytesuu>=TOSIYORISUU*12){//10バイト(全角5文字分)だけどデータ的に12バイト
			ch=0x00;
			fseek(fpsikona2,-1,SEEK_CUR);
			fwrite(&ch,sizeof(ch),1,fpsikona2);
			break;
		}
		mojibytesuu=0;
		while(1){
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (mojibytesuu>=10){
				ch=0x00;
				fwrite(&ch,sizeof(ch),1,fpsikona2);
				fwrite(&ch,sizeof(ch),1,fpsikona2);//12バイトにするためもう一度
				fseek(fpsikona,+1,SEEK_CUR);
				totalbytesuu++;
				totalbytesuu++;
				break;
			}else{
				if (fread(&ch,sizeof(ch),1,fpsikona)>=1){
					if (ch==0x0d){
						ch=0x00;
						for (i=mojibytesuu;i<12;i++){//12バイトにするため
							fwrite(&ch,sizeof(ch),1,fpsikona2);
							totalbytesuu++;
						}
						break;
					}else if(ch==0x0a){

					}else{
						fwrite(&ch,sizeof(ch),1,fpsikona2);
						mojibytesuu++;
						totalbytesuu++;
					}
				}else{
					breakflag=1;
					break;
				}
			}
		}
		if (breakflag==1) break;
	}

	fclose(fpsikona);
	fclose(fpsikona2);

	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

//////////////////////
	fpsikona = fopen("data/namestring_tosiyori.csv","rb");
	if( fpsikona == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗ここ？" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return ;
	}
	fpsikona2 = fopen("data/namestring_tosiyori.dat","wb");
	if( fpsikona2 == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return ;
	}

	mojibytesuu=0;
	totalbytesuu=0;
	breakflag=0;
	while(1)
	{
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (totalbytesuu>=TOSIYORISUU*12){//10バイト(全角5文字分)だけどデータ的に12バイト
			ch=0x00;
			fseek(fpsikona2,-1,SEEK_CUR);
			fwrite(&ch,sizeof(ch),1,fpsikona2);
			break;
		}
		mojibytesuu=0;
		while(1){
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (mojibytesuu>=10){
				ch=0x00;
				fwrite(&ch,sizeof(ch),1,fpsikona2);
				fwrite(&ch,sizeof(ch),1,fpsikona2);//12バイトにするためもう一度
				fseek(fpsikona,+1,SEEK_CUR);
				totalbytesuu++;
				totalbytesuu++;
				break;
			}else{
				if (fread(&ch,sizeof(ch),1,fpsikona)>=1){
					if (ch==0x0d){
						ch=0x00;
						for (i=mojibytesuu;i<12;i++){//12バイトにするため
							fwrite(&ch,sizeof(ch),1,fpsikona2);
							totalbytesuu++;
						}
						break;
					}else if(ch==0x0a){

					}else{
						fwrite(&ch,sizeof(ch),1,fpsikona2);
						mojibytesuu++;
						totalbytesuu++;
					}
				}else{
					breakflag=1;
					break;
				}
			}
		}
		if (breakflag==1) break;
	}

	fclose(fpsikona);
	fclose(fpsikona2);

	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける


}

void sikona_c(void){
	int i,ii,totalbytesuu,mojibytesuu,breakflag;
	char ch;
	int line;
	int suu_sikona_c_mae_heya;
	int suu_sikona_c_mae_hometown;

	FILE *fpcsv;
	FILE *fpsikona;
	FILE *fpsikona2;
	suu_sikona_c_mae_hometown=54;
	suu_sikona_c_mae_heya=54*2;
	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

	fpcsv = fopen("data/heyabetu/namestring_heyabetu.csv","r");
	if( fpcsv == NULL ){
		fclose(fpcsv);
		fpcsv = fopen("data/heyabetu/namestring_heyabetu.csv","w");
fprintf(fpcsv,"箱庭\n");
fprintf(fpcsv,"箱\n");
fprintf(fpcsv,"山\n");
fprintf(fpcsv,"王\n");
fprintf(fpcsv,"花\n");
fprintf(fpcsv,"龍\n");
fprintf(fpcsv,"川\n");
fprintf(fpcsv,"栄\n");
fprintf(fpcsv,"海\n");
fprintf(fpcsv,"光\n");
fprintf(fpcsv,"妖\n");
fprintf(fpcsv,"蛇\n");
fprintf(fpcsv,"寅\n");
fprintf(fpcsv,"獣\n");
fprintf(fpcsv,"肉\n");
fprintf(fpcsv,"塊\n");
fprintf(fpcsv,"児\n");
fprintf(fpcsv,"兄\n");
fprintf(fpcsv,"弟\n");
fprintf(fpcsv,"坊\n");
fprintf(fpcsv,"忍\n");
fprintf(fpcsv,"希\n");
fprintf(fpcsv,"望\n");
fprintf(fpcsv,"男\n");
fprintf(fpcsv,"侍\n");
fprintf(fpcsv,"呪\n");
fprintf(fpcsv,"岬\n");
fprintf(fpcsv,"抗\n");
fprintf(fpcsv,"頭\n");
fprintf(fpcsv,"東\n");
fprintf(fpcsv,"西\n");
fprintf(fpcsv,"南\n");
fprintf(fpcsv,"北\n");
fprintf(fpcsv,"空\n");
fprintf(fpcsv,"恵\n");
fprintf(fpcsv,"雄\n");
fprintf(fpcsv,"勇\n");
fprintf(fpcsv,"金\n");
fprintf(fpcsv,"福\n");
fprintf(fpcsv,"冠\n");
fprintf(fpcsv,"怒\n");
fprintf(fpcsv,"星\n");
fprintf(fpcsv,"泉\n");
fprintf(fpcsv,"皇\n");
fprintf(fpcsv,"美\n");
fprintf(fpcsv,"紅\n");
fprintf(fpcsv,"虹\n");
fprintf(fpcsv,"風\n");
fprintf(fpcsv,"剛\n");
fprintf(fpcsv,"豪\n");
fprintf(fpcsv,"郷\n");
fprintf(fpcsv,"里\n");
fprintf(fpcsv,"剣\n");
fprintf(fpcsv,"凄\n");
fprintf(fpcsv,"牙\n");
fprintf(fpcsv,"恐\n");
fprintf(fpcsv,"悟\n");
fprintf(fpcsv,"桜\n");
fprintf(fpcsv,"笑\n");
fprintf(fpcsv,"力\n");
fprintf(fpcsv,"閃\n");
fprintf(fpcsv,"竜\n");
fprintf(fpcsv,"兜\n");
fprintf(fpcsv,"唸\n");
fprintf(fpcsv,"斬\n");
fprintf(fpcsv,"清\n");
fprintf(fpcsv,"理\n");
fprintf(fpcsv,"盛\n");
fprintf(fpcsv,"祭\n");
fprintf(fpcsv,"頂\n");
fprintf(fpcsv,"雪\n");
fprintf(fpcsv,"雨\n");
fprintf(fpcsv,"晴\n");
fprintf(fpcsv,"雷\n");
fprintf(fpcsv,"嵐\n");
fprintf(fpcsv,"朝\n");
fprintf(fpcsv,"童\n");
fprintf(fpcsv,"鷹\n");
fprintf(fpcsv,"誉\n");
fprintf(fpcsv,"聖\n");
fprintf(fpcsv,"賊\n");
fprintf(fpcsv,"精\n");
fprintf(fpcsv,"蜜\n");
fprintf(fpcsv,"鳳\n");
fprintf(fpcsv,"魁\n");
fprintf(fpcsv,"暴\n");
fprintf(fpcsv,"熱\n");
fprintf(fpcsv,"稼\n");
fprintf(fpcsv,"舞\n");
fprintf(fpcsv,"厳\n");
fprintf(fpcsv,"興\n");
fprintf(fpcsv,"錦\n");
fprintf(fpcsv,"曙\n");
fprintf(fpcsv,"翼\n");
fprintf(fpcsv,"爆\n");
fprintf(fpcsv,"麗\n");
fprintf(fpcsv,"鷲\n");
fprintf(fpcsv,"馬\n");
fprintf(fpcsv,"鳥\n");
fprintf(fpcsv,"楽\n");
fprintf(fpcsv,"優\n");
fprintf(fpcsv,"蘭\n");
fprintf(fpcsv,"白\n");
fprintf(fpcsv,"赤\n");
fprintf(fpcsv,"青\n");
fprintf(fpcsv,"黒\n");
fprintf(fpcsv,"緑\n");
fprintf(fpcsv,"紫\n");

	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

		fclose(fpcsv);
	}else{
		line=0;
		while((ch = fgetc(fpcsv)) != EOF) 
		{
			if(ch == '\n'){
				++line;
			}
			if (line>suu_sikona_c_mae_heya) break;
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		fclose(fpcsv);

//		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
//		DrawFormatString( 250 , 272 - 32 ,CRGREEN, "line数 %d" ,line );
//		ScreenFlip() ;//裏画面を表画面にコピー
//		WaitKey();

		fpcsv = fopen("data/heyabetu/namestring_heyabetu.csv","a");
		while(1){
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"箱庭\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"箱\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"山\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"王\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"山\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"王\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"花\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"龍\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"川\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"栄\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"海\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"光\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"妖\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"蛇\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"寅\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"獣\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"肉\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"塊\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"児\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"兄\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"弟\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"坊\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"忍\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"希\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"望\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"男\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"侍\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"呪\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"岬\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"抗\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"頭\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"東\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"西\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"南\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"北\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"空\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"恵\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"雄\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"勇\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"金\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"福\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"冠\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"怒\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"星\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"泉\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"皇\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"美\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"紅\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"虹\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"風\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"剛\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"豪\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"郷\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"里\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"剣\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"凄\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"牙\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"恐\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"悟\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"桜\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"笑\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"力\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"閃\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"竜\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"兜\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"唸\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"斬\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"清\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"理\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"盛\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"祭\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"頂\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"雪\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"雨\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"晴\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"雷\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"嵐\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"朝\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"童\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"鷹\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"誉\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"聖\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"賊\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"精\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"蜜\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"鳳\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"魁\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"暴\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"熱\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"稼\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"舞\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"厳\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"興\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"錦\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"曙\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"翼\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"爆\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"麗\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"鷲\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"馬\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"鳥\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"楽\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"優\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"蘭\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"鷲\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"馬\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"鳥\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"楽\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"優\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"蘭\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"白\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"赤\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"青\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"黒\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"緑\n");line++;
if (line>suu_sikona_c_mae_heya-1) break;fprintf(fpcsv,"紫\n");line++;

			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		fclose(fpcsv);
	}


	/////////////////////////////////////////////////
	fpsikona = fopen("data/heyabetu/namestring_heyabetu.csv","rb");
	if( fpsikona == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗ここ？" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return ;
	}
	fpsikona2 = fopen("data/heyabetu/namestring_heyabetu.dat","wb");
	if( fpsikona2 == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return ;
	}

	mojibytesuu=0;
	totalbytesuu=0;
	breakflag=0;
	while(1)
	{
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (totalbytesuu>=suu_sikona_c_mae_heya*5){//5バイト(全角2文字分)
			ch=0x00;
			fseek(fpsikona2,-1,SEEK_CUR);
			fwrite(&ch,sizeof(ch),1,fpsikona2);
			break;
		}
		mojibytesuu=0;
		while(1){
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (mojibytesuu>=4){
				ch=0x00;
				fwrite(&ch,sizeof(ch),1,fpsikona2);
				fseek(fpsikona,+1,SEEK_CUR);
				totalbytesuu++;
				break;
			}else{
				if (fread(&ch,sizeof(ch),1,fpsikona)>=1){
					if (ch==0x0d){
						ch=0x00;
						for (i=mojibytesuu;i<5;i++){
							fwrite(&ch,sizeof(ch),1,fpsikona2);
							totalbytesuu++;
						}
						break;
					}else if(ch==0x0a){

					}else{
						fwrite(&ch,sizeof(ch),1,fpsikona2);
						mojibytesuu++;
						totalbytesuu++;
					}
				}else{
					breakflag=1;
					break;
				}
			}
		}
		if (breakflag==1) break;
	}

	fclose(fpsikona);
	fclose(fpsikona2);

	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

/*///////////////////都道府県別mae四股名///////////////////////////////////////////////////////////////////
	fpcsv = fopen("data/namestring_c_mae_hometown.csv","r");
	if( fpcsv == NULL ){
		fclose(fpcsv);
		fpcsv = fopen("data/namestring_c_mae_hometown.csv","w");
fprintf(fpcsv,"箱庭\n");
fprintf(fpcsv,"北海\n");
fprintf(fpcsv,"青森\n");
fprintf(fpcsv,"岩手\n");
fprintf(fpcsv,"宮城\n");
fprintf(fpcsv,"秋田\n");
fprintf(fpcsv,"山形\n");
fprintf(fpcsv,"福島\n");
fprintf(fpcsv,"群馬\n");
fprintf(fpcsv,"栃木\n");
fprintf(fpcsv,"茨城\n");
fprintf(fpcsv,"埼玉\n");
fprintf(fpcsv,"千葉\n");
fprintf(fpcsv,"東京\n");
fprintf(fpcsv,"神奈\n");
fprintf(fpcsv,"新潟\n");
fprintf(fpcsv,"富山\n");
fprintf(fpcsv,"石川\n");
fprintf(fpcsv,"福井\n");
fprintf(fpcsv,"山梨\n");
fprintf(fpcsv,"長野\n");
fprintf(fpcsv,"岐阜\n");
fprintf(fpcsv,"静岡\n");
fprintf(fpcsv,"愛知\n");
fprintf(fpcsv,"三重\n");
fprintf(fpcsv,"滋賀\n");
fprintf(fpcsv,"京都\n");
fprintf(fpcsv,"大阪\n");
fprintf(fpcsv,"兵庫\n");
fprintf(fpcsv,"奈良\n");
fprintf(fpcsv,"和歌\n");
fprintf(fpcsv,"鳥取\n");
fprintf(fpcsv,"島根\n");
fprintf(fpcsv,"岡山\n");
fprintf(fpcsv,"広島\n");
fprintf(fpcsv,"山口\n");
fprintf(fpcsv,"徳島\n");
fprintf(fpcsv,"香川\n");
fprintf(fpcsv,"愛媛\n");
fprintf(fpcsv,"高知\n");
fprintf(fpcsv,"福岡\n");
fprintf(fpcsv,"佐賀\n");
fprintf(fpcsv,"長崎\n");
fprintf(fpcsv,"熊本\n");
fprintf(fpcsv,"大分\n");
fprintf(fpcsv,"宮崎\n");
fprintf(fpcsv,"鹿児\n");
fprintf(fpcsv,"沖縄\n");
fprintf(fpcsv,"蒙古\n");
fprintf(fpcsv,"欧州\n");
fprintf(fpcsv,"米国\n");
fprintf(fpcsv,"亜細\n");
fprintf(fpcsv,"南米\n");
fprintf(fpcsv,"阿弗\n");

	if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける

		fclose(fpcsv);
	}else{
		line=0;
		while((ch = fgetc(fpcsv)) != EOF) 
		{
			if(ch == '\n'){
				++line;
			}
			if (line>suu_sikona_c_mae_hometown) break;
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		fclose(fpcsv);

//		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
//		DrawFormatString( 250 , 272 - 32 ,CRGREEN, "line数 %d" ,line );
//		ScreenFlip() ;//裏画面を表画面にコピー
//		WaitKey();

		fpcsv = fopen("data/namestring_c_mae_hometown.csv","a");
		while(1){
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"箱庭\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"北海\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"青森\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"岩手\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"宮城\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"秋田\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"山形\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"福島\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"群馬\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"栃木\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"茨城\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"埼玉\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"千葉\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"東京\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"神奈\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"新潟\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"富山\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"石川\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"福井\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"山梨\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"長野\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"岐阜\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"静岡\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"愛知\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"三重\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"滋賀\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"京都\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"大阪\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"兵庫\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"奈良\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"和歌\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"鳥取\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"島根\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"岡山\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"広島\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"山口\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"徳島\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"香川\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"愛媛\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"高知\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"福岡\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"佐賀\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"長崎\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"熊本\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"大分\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"宮崎\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"鹿児\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"沖縄\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"蒙古\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"欧州\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"米国\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"亜細\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"南米\n");line++;
if (line>suu_sikona_c_mae_hometown-1) break;fprintf(fpcsv,"阿弗\n");line++;

			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		}
		fclose(fpcsv);
	}


	/////////////////////////////////////////////////
	fpsikona = fopen("data/namestring_c_mae_hometown.csv","rb");
	if( fpsikona == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗2?" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return ;
	}
	fpsikona2 = fopen("data/namestring_c_mae_hometown.dat","wb");
	if( fpsikona2 == NULL ){
		ClearDrawScreen() ;//裏画面をクリア(コピーした後は裏画面をクリアしないといけないらしい)
		DrawString( 250 , 240 - 32 , "ファイルオープンに失敗" , GetColor(255,255,255) );
		DrawString( 250 , 272 - 32 , "Hit any key" , GetColor(255,255,255) );
		ScreenFlip() ;//裏画面を表画面にコピー
		WaitKey();
		return ;
	}

	mojibytesuu=0;
	totalbytesuu=0;
	breakflag=0;
	while(1)
	{
		if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
		if (totalbytesuu>=suu_sikona_c_mae_hometown*5){//5バイト(全角2文字分)
			ch=0x00;
			fseek(fpsikona2,-1,SEEK_CUR);
			fwrite(&ch,sizeof(ch),1,fpsikona2);
			break;
		}
		mojibytesuu=0;
		while(1){
			if( ProcessMessage() == -1 ){mode=1;return ;}// エラーが起きたらループから抜ける
			if (mojibytesuu>=4){
				ch=0x00;
				fwrite(&ch,sizeof(ch),1,fpsikona2);
				fseek(fpsikona,+1,SEEK_CUR);
				totalbytesuu++;
				break;
			}else{
				if (fread(&ch,sizeof(ch),1,fpsikona)>=1){
					if (ch==0x0d){
						ch=0x00;
						for (i=mojibytesuu;i<5;i++){
							fwrite(&ch,sizeof(ch),1,fpsikona2);
							totalbytesuu++;
						}
						break;
					}else if(ch==0x0a){

					}else{
						fwrite(&ch,sizeof(ch),1,fpsikona2);
						mojibytesuu++;
						totalbytesuu++;
					}
				}else{
					breakflag=1;
					break;
				}
			}
		}
		if (breakflag==1) break;
	}

	fclose(fpsikona);
	fclose(fpsikona2);
	*/

}