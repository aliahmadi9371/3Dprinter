#include "ImageView.h"

#define  BK_RGB RGB(20,120,20)

char graph2[8192];

ImageView::ImageView(void)
	:bMouse(0),
	cx(0),
	cy(0),
	mode(1)
{
	Screen_cx = 1920;
	Screen_cy = 1080;
	image1.lpData = 0;
}

ImageView::~ImageView(void)
{
}

void ImageView::Create(int x,int y ,int cx,int cy)
{
	this->pos_x   = x;
	this->pos_y   = y;
	this->cx      = cx;
	this->cy      = cy;

//	BYTE data[2000] = { 0 };
//	BITMAPINFOHEADER *bh = (BITMAPINFOHEADER*)data;
//	//RGBQUAD *pal = (RGBQUAD*)(data + sizeof(*bh));
//	bh->biSize = sizeof(*bh);
//	bh->biWidth = Screen_cx;
//	bh->biHeight = Screen_cy;
//	bh->biPlanes = 1;
//	bh->biBitCount = 32;
//	bh->biClrUsed = bh->biClrImportant = 256;
//	bmp1 = CreateDIBSection(0, (BITMAPINFO*)bh, DIB_RGB_COLORS, (void**)&bmpbuf, NULL, 0);

//	hdc1 = CreateCompatibleDC(0);
//	SelectObject(hdc1, bmp1);
}

void ImageView::ChangeSize(int cx, int cy)
{
	this->cx = cx;
	this->cy = cy;
}

//void ImageView::Draw(HDC hdcPare)
//{
//	BitBlt(hdcPare, pos_x, pos_y, cx, cy, hdc1, 0, 0, SRCCOPY);
//}

void ImageView::ChangeBkColor(unsigned int BkgColor)
{
	this->SlcBkgCol = BkgColor;
	int indx = 0;
	int yy = Screen_cy - 1;
//	int  *lpbmpbuf = (int *)bmpbuf;
//	for (int j = 0; j < cy; j++)
//	{
//		for (int i = 0; i < cx;i++)
//		{
//			lpbmpbuf[yy*Screen_cx + i] = this->SlcBkgCol;
//		}
//		yy--;
//	}
}

void ImageView::ChangeImage(char *buffer, int size)
{
    if (image1.lpData != 0)
    {
        delete image1.lpData;
//		free(image1.lpData);
        image1.lpData = 0;
    }
//    LoadImageRes(buffer, &image1, 1.0);
//	int indx = 0;
//	int yy = Screen_cy - 1;
//	for (int j = 0; j < cy; j++)
//	{
//		for (int i = 0; i < cx * 4; i += 4)
//		{
//			bmpbuf[yy*Screen_cx * 4 + i] = image1.lpData[indx+2];
//			bmpbuf[yy*Screen_cx * 4 + i + 1] = image1.lpData[indx + 1];
//			bmpbuf[yy*Screen_cx * 4 + i + 2] = image1.lpData[indx];
//			bmpbuf[yy*Screen_cx * 4 + i + 3] = image1.lpData[indx + 3];
//			indx += 4;
//		}
//		yy--;
//	}
}


