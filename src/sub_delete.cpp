#include "DxLib.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include "define.h"

extern int mode;


int del_data_csv(void);
int del_data_dat(void);
int del_save_csv(int num);//引数はセーブスロット番号
int del_save_dat(int num);//引数はセーブスロット番号


int del_save_dat(int num)//引数はセーブスロット番号
{
	HANDLE hSearch;
	WIN32_FIND_DATA fd;
	int i=0;
	char filename[MAX_PATH+1];
	char temp_str[MAX_PATH+1];
	for (i=0;i<MAX_PATH+1;i++){
		if( ProcessMessage() == -1 ){mode=1;return 0;}
		filename[i]=0;
		temp_str[i]=0;
	}
///////////////////////////////ここがフォルダ相対指定、下にもう一つあるよ////////////
	sprintf(temp_str,"save\\save%d\\dat\\*.*",num);
	hSearch = FindFirstFile( _T(temp_str), &fd );
	if( hSearch == INVALID_HANDLE_VALUE ){
		//もうファイルがないので削除完了
		FindClose(hSearch);
		return 1;
	}
	while(1){
		if( ProcessMessage() == -1 ){mode=1;return 0;}
		if (strcmp(fd.cFileName,".")!=0 && strcmp(fd.cFileName,"..")!=0){
///////////////////////////////ここがフォルダ相対指定、上にもう一つあるよ////////////
			sprintf(filename,"save/save%d/dat/",num);
			strcat(filename,fd.cFileName);
/*ClearDrawScreen();
DrawFormatString(187,369,CRWHITE,"%sを削除します",filename);
ScreenFlip();
WaitKey();
*/
			DeleteFile(filename);
			if( ProcessMessage() == -1 ){mode=1;return 0;}
		}
		//ファイルがなくなるまで削除し続ける
		if( !FindNextFile( hSearch, &fd ) )
		{
			if( GetLastError() == ERROR_NO_MORE_FILES )
			{
				FindClose( hSearch );
				return 1;    // 列挙終了
			}
			else
			{
				FindClose( hSearch );
				return 0;    // エラー
			}
		}
	}
}

int del_save_csv(int num)//引数はセーブスロット番号
{
	HANDLE hSearch;
	WIN32_FIND_DATA fd;
	int i=0;
	char filename[MAX_PATH+1];
	char temp_str[MAX_PATH+1];
	for (i=0;i<MAX_PATH+1;i++){
		if( ProcessMessage() == -1 ){mode=1;return 0;}
		filename[i]=0;
		temp_str[i]=0;
	}
///////////////////////////////ここがフォルダ相対指定、下にもう一つあるよ////////////
	sprintf(temp_str,"save\\save%d\\csv\\*.*",num);
	hSearch = FindFirstFile( _T(temp_str), &fd );
	if( hSearch == INVALID_HANDLE_VALUE ){
		//もうファイルがないので削除完了
		FindClose(hSearch);
		return 1;
	}
	while(1){
		if( ProcessMessage() == -1 ){mode=1;return 0;}
		if (strcmp(fd.cFileName,".")!=0 && strcmp(fd.cFileName,"..")!=0){
///////////////////////////////ここがフォルダ相対指定、上にもう一つあるよ////////////
			sprintf(filename,"save/save%d/csv/",num);
			strcat(filename,fd.cFileName);
/*ClearDrawScreen();
DrawFormatString(187,369,CRWHITE,"%sを削除します",filename);
ScreenFlip();
WaitKey();
*/
			DeleteFile(filename);
			if( ProcessMessage() == -1 ){mode=1;return 0;}
		}
		//ファイルがなくなるまで削除し続ける
		if( !FindNextFile( hSearch, &fd ) )
		{
			if( GetLastError() == ERROR_NO_MORE_FILES )
			{
				FindClose( hSearch );
				return 1;    // 列挙終了
			}
			else
			{
				FindClose( hSearch );
				return 0;    // エラー
			}
		}
	}
}


int del_data_csv(void)
{
	HANDLE hSearch;
	WIN32_FIND_DATA fd;
	int i=0;
	char filename[MAX_PATH+1];
	for (i=0;i<MAX_PATH+1;i++){
		if( ProcessMessage() == -1 ){mode=1;return 0;}
		filename[i]=0;
	}
///////////////////////////////ここがフォルダ相対指定、下にもう一つあるよ////////////
	hSearch = FindFirstFile( _T("data\\csv\\*.*"), &fd );
	if( hSearch == INVALID_HANDLE_VALUE ){
		//もうファイルがないので削除完了
		FindClose(hSearch);
		return 1;
	}
	while(1){
		if( ProcessMessage() == -1 ){mode=1;return 0;}
		if (strcmp(fd.cFileName,".")!=0 && strcmp(fd.cFileName,"..")!=0){
///////////////////////////////ここがフォルダ相対指定、上にもう一つあるよ////////////
			strcpy(filename,"data/csv/");
			strcat(filename,fd.cFileName);
/*ClearDrawScreen();
DrawFormatString(187,369,CRWHITE,"%sを削除します",filename);
ScreenFlip();
WaitKey();
*/
			DeleteFile(filename);
			if( ProcessMessage() == -1 ){mode=1;return 0;}
		}
		//ファイルがなくなるまで削除し続ける
		if( !FindNextFile( hSearch, &fd ) )
		{
			if( GetLastError() == ERROR_NO_MORE_FILES )
			{
				FindClose( hSearch );
				return 1;    // 列挙終了
			}
			else
			{
				FindClose( hSearch );
				return 0;    // エラー
			}
		}
	}
}

int del_data_dat(void)
{
	HANDLE hSearch;
	WIN32_FIND_DATA fd;
	int i=0;
	char filename[MAX_PATH+1];
	for (i=0;i<MAX_PATH+1;i++){
		if( ProcessMessage() == -1 ){mode=1;return 0;}
		filename[i]=0;
	}
///////////////////////////////ここがフォルダ相対指定、下にもう一つあるよ////////////
	hSearch = FindFirstFile( _T("data\\dat\\*.*"), &fd );
	if( hSearch == INVALID_HANDLE_VALUE ){
		//もうファイルがないので削除完了
		FindClose(hSearch);
		return 1;
	}
	while(1){
		if( ProcessMessage() == -1 ){mode=1;return 0;}
		if (strcmp(fd.cFileName,".")!=0 && strcmp(fd.cFileName,"..")!=0){
///////////////////////////////ここがフォルダ相対指定、上にもう一つあるよ////////////
			strcpy(filename,"data/dat/");
			strcat(filename,fd.cFileName);
/*ClearDrawScreen();
DrawFormatString(187,369,CRWHITE,"%sを削除します",filename);
ScreenFlip();
WaitKey();
*/
			DeleteFile(filename);
			if( ProcessMessage() == -1 ){mode=1;return 0;}
		}
		//ファイルがなくなるまで削除し続ける
		if( !FindNextFile( hSearch, &fd ) )
		{
			if( GetLastError() == ERROR_NO_MORE_FILES )
			{
				FindClose( hSearch );
				return 1;    // 列挙終了
			}
			else
			{
				FindClose( hSearch );
				return 0;    // エラー
			}
		}
	}
}
