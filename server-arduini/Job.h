#ifndef JOB_H
#define JOB_H

#include <iostream>

using namespace std;

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
    __Points *points;
    string Name = "";
    double Size = 0;
    uint16_t id;
};


#endif // JOB_H
