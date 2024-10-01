#ifndef SLCREAD_H
#define SLCREAD_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXHEADERSIZE 2048
#define MAXPOINTS 50 * 1024 * 1024

struct __Vector2
{
	float X;
	float Y;
};

struct __Points
{
	float fX;
	float fY;
	unsigned short Slice;
	unsigned short VertNum;
};

struct __Job3D
{
	float fMaxX;
	float fMaxY;
	unsigned short iNumSlices;
	unsigned int   iTotalVerts;
	struct __Points *points;
};


int  ImportSlcInfo(char *SlcFileName, struct __Job3D *jobinfo);
int ExportPatternToMem(int index,int ImageCX, int ImageCY, float fPixelSize, unsigned int BkgColor, char *OutBuffer);
int  ExportFrameToSVG(struct __Job3D *jobinfo, int iSlice, int ImageCX, int ImageCY, float fPixelSize, char *OutFileName);
int  ExportFrameToMem(struct __Job3D *jobinfo, int iSlice, int ImageCX, int ImageCY, float fPixelSize, unsigned int BkgColor, char *OutBuffer,float X_Shift,float Y_Shift);
void ExportSlcFileToSVG(char *SlcFileName, char *OutFileName,float fPixelSize,int img_cx,int img_cy);
void ExportSlcFileToSVGErm(char *SlcFileName, char *OutFileName,float fPixelSize,int img_cx,int img_cy,float X_Shift,float Y_Shift);
void ExportJobFile(struct __Job3D *jobinfo, char *OutFileName);
void OpenJobFile(char *JobFileName,struct __Job3D *jobinfo);

#endif
