#pragma once
//#include <windows.h>
//#include <commdlg.h>
//#include <commctrl.h>
#include <stdio.h>
#include "sdlg.h"

#pragma comment(lib, "sdlgc.lib")

class ImageView
{
public:
	char buff[64];
	int  TmpData;

	int pos_x;
	int pos_y;
	int cx;
	int cy;
	int Screen_cx;
	int Screen_cy;
	char mode;
	bool bMouse;

//	HDC   hdc1;
//	HBITMAP bmp1;
//	CHAR  *bmpbuf;

	unsigned int SlcBkgCol;

	sdImage image1;


public:
	ImageView(void);
	~ImageView(void);
	void Create(int x,int y ,int cx,int cy);
	void ChangeSize(int cx, int cy);
//	void Draw(HDC hdcPare);
	void ChangeBkColor(unsigned int BkgColor);
	void ChangeImage(char *buffer, int size);
};

