
#include "slcread.h"


FILE * infile;
FILE * outfile;
FILE * outfileerm;

char inbuffer[8192];

char headertext[MAXHEADERSIZE];

double minx = 0;
double maxx = 0;
double miny = 0;
double maxy = 0;
double minz = 0;
double maxz = 0;
char XBound[64];

char YBound[64];
char ZBound[64];
float scalefactor = 1.0f;

unsigned int numslices = 0;

unsigned int numboundries = 0;
unsigned int numvertices = 0;
unsigned int numgaps = 0;
unsigned int minzlevel = 0;


struct __Vector2 minb;
struct __Vector2 maxb;


int ImportSlcInfo(char *SlcFileName, struct __Job3D *jobinfo)
{
    float x;
    float y;

	int headersize = 0;
	int len = 0;
	float readfloat;

	numboundries = 0;
	numslices = 0;

	infile = fopen (SlcFileName, "rb");
	len = fread(headertext,1,MAXHEADERSIZE,infile);
	fclose(infile);

	char* token = strtok(headertext, " ");
	for (int i=0;i<20;i++)
	{
		token = strtok(NULL, " ");
		if (strcmp(token,"INCH")==0)
		{
			scalefactor = 25.4f;
		}
		else if (strcmp(token,"-EXTENTS")==0)
		{
			token = strtok(NULL, " ");
			sprintf(XBound,"%s",token);
			token = strtok(NULL, " ");
			sprintf(YBound,"%s",token);
			token = strtok(NULL, " ");
			sprintf(ZBound,"%s",token);
			token = strtok(XBound, ","); minx = atof(token);
			token = strtok(NULL, ",");   maxx = atof(token);
			token = strtok(YBound, ","); miny = atof(token);
			token = strtok(NULL, ",");   maxy = atof(token);
			token = strtok(ZBound, ","); minz = atof(token);
			token = strtok(NULL, ",");   maxz = atof(token);
			break;
		}
	}
	//printf("%f - %f \r\n",minx,maxx);  printf("%f - %f \r\n",miny,maxy);  printf("%f - %f \r\n",minz,maxz);

	infile = fopen (SlcFileName, "rb");

	jobinfo->points = new  __Points[MAXPOINTS];

   while (headersize <= MAXHEADERSIZE)
   { 
	    len = fread (inbuffer,1,1,infile);
	    headersize++;
	    if (inbuffer[0] == 0x0d)
	    {
			len = fread (inbuffer,1,1,infile);
			headersize++;
			if (inbuffer[0] == 0x0a)
			{
				len = fread (inbuffer,1,1,infile);
				headersize++;
				if (inbuffer[0] == 0x1a)
				{
					break;
				}
			}
	    }
   }
   len = fread (inbuffer,1,256,infile);    //skip 256 bytes


   len = fread (inbuffer,1,1,infile);
   int tableentries = inbuffer[0];

	for (int t = 0; t < tableentries; t++)
	{
		len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
		len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
		len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
		len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);		
	}

   minb.X=minx;  minb.Y=miny;
   maxb.X=maxx;  maxb.Y=maxy;

   int t_index = 0;

	bool boundsdetermined = 0;
	while (numboundries != 0xffffffff)
	{
		len = fread (inbuffer,1,4,infile);  memcpy(&minzlevel,inbuffer,4);
		len = fread (inbuffer,1,4,infile);  memcpy(&numboundries,inbuffer,4);

		if (numboundries == 0xffffffff)
		{
			break;
		}
		numslices++;

 	 	for (int b = 0; b < numboundries; b++)
		{
			len = fread (inbuffer,1,4,infile);  memcpy(&numvertices,inbuffer,4);
			len = fread (inbuffer,1,4,infile);  memcpy(&numgaps,inbuffer,4);
			for (int v = 0; v < numvertices; v++)
			{
				len = fread (inbuffer,1,4,infile);  memcpy(&x,inbuffer,4);
				len = fread (inbuffer,1,4,infile);  memcpy(&y,inbuffer,4);

				x *= scalefactor;
				y *= scalefactor;

				jobinfo->points[t_index].fX = x;
				jobinfo->points[t_index].fY = y;
				jobinfo->points[t_index].VertNum = v;
				jobinfo->points[t_index].Slice = numslices;
				t_index++;

				if (x > maxb.X)
					maxb.X = x;
				if (y > maxb.Y)
					maxb.Y = y;
				if (x < minb.X)
					minb.X = x;
				if (y < minb.Y)
					minb.Y = y;
				boundsdetermined = true;
			} 
		}
		
	}
	//printf("\r\n numslices: %d \r\n",numslices);
	fclose(infile);
	jobinfo->fMaxX = maxb.X;
	jobinfo->fMaxY = maxb.Y;
	jobinfo->iNumSlices = numslices;
	jobinfo->iTotalVerts = t_index;
	return numslices;
}

int ExportFrameToSVG(struct __Job3D *jobinfo, int iSlice,int ImageCX,int ImageCY,float fPixelSize, char *OutFileName)
{
	int aa = 0;
	int jj = 0;
	while (aa < MAXPOINTS)
	{
		if (jobinfo->points[aa].Slice == iSlice)
			break;
		aa++;
	}
	
	outfile = fopen(OutFileName, "w+");
	fprintf(outfile, "<svg xmlns='http://www.w3.org/2000/svg' version='1.0' width='%d' height='%d'>\r\n", ImageCX, ImageCY);
	fprintf(outfile, "<rect x='0' y='0' width='%d' height='%d' style='fill:black;stroke:blue;stroke-width:0;' />\r\n", ImageCX, ImageCY);
	fprintf(outfile, "<path d='");

	jj = 0;
	while (jobinfo->points[aa].Slice == iSlice)
	{
		if (jobinfo->points[aa].VertNum == 0)
			fprintf(outfile, "M%.3f %.3f ", (jobinfo->points[aa].fX*(1.0 / fPixelSize)), (jobinfo->points[aa].fY*(1.0 / fPixelSize)));
		else
			fprintf(outfile, "L%.3f %.3f ", (jobinfo->points[aa].fX*(1.0 / fPixelSize)), (jobinfo->points[aa].fY*(1.0 / fPixelSize)));
		aa++;
	}

	fprintf(outfile, "Z' fill='white' />\r\n");
	fprintf(outfile, "</svg>\r\n");
	fclose(outfile);
	return 0;
}

int ExportPatternToMem(int index,int ImageCX, int ImageCY, float fPixelSize, unsigned int BkgColor, char *OutBuffer)
{
	int aa = 0;
	int jj = 0;
	int size = 0;
	int zz = 0;

	zz = sprintf(OutBuffer+size, "<svg width='%d' height='%d'>\r\n", ImageCX, ImageCY);
	size += zz;
	zz = sprintf(OutBuffer+size, "<rect x='0' y='0' width='%d' height='%d' style='fill:#%x;stroke-width:0;' />\r\n", ImageCX, ImageCY, BkgColor);
	size += zz;


	int xx = ImageCX/30;
	int yy = ImageCY/30;

	int tmpv = 0;
	if (index == 1)
	{
		for (int i=0;i<31;i++)
		{
			tmpv = i*xx;
			if (i==30) tmpv-=1;
			zz = sprintf(OutBuffer+size, "<rect x='%d' y='%d' width='%d' height='%d' style='fill:white;stroke-width:0;' />\r\n", tmpv,0,1,ImageCY);
			size += zz;
		}
		for (int i=0;i<31;i++)
		{
			tmpv = i*yy;
			if (i==30) tmpv-=1;
			zz = sprintf(OutBuffer+size, "<rect x='%d' y='%d' width='%d' height='%d' style='fill:white;stroke-width:0;' />\r\n", 0,tmpv,ImageCX,1);
			size += zz;
		}
	}
	else if (index == 2)
	{
		zz = sprintf(OutBuffer+size, "<rect x='%d' y='%d' width='%d' height='%d' style='fill:white;stroke-width:0;' />\r\n", 200,200,600,500);
		size += zz;
	}
	else if (index == 3)
	{
		zz = sprintf(OutBuffer+size, "<circle cx='%d' cy='%d' r='%d' style='fill:white;stroke-width:0;' />\r\n", 200,200,100);
		size += zz;
	}
	else if (index == 4)
	{
		zz = sprintf(OutBuffer+size, "<circle cx='%d' cy='%d' r='%d' fill'white' />\r\n", ImageCX/2,ImageCY/2,ImageCY/2);
		size += zz;
	}
	zz = sprintf(OutBuffer + size, "</svg>\r\n");
	size += zz;
	return size;
}


int ExportFrameToMem(struct __Job3D *jobinfo, int iSlice, int ImageCX, int ImageCY, float fPixelSize, unsigned int BkgColor, char *OutBuffer,float X_Shift,float Y_Shift)
{
	int aa = 0;
	int jj = 0;
	int size = 0;
	int zz = 0;
	while (aa < MAXPOINTS)
	{
		if (jobinfo->points[aa].Slice == iSlice)
			break;
		aa++;
	}

	zz = sprintf(OutBuffer+size, "<svg width='%d' height='%d'>\r\n", ImageCX, ImageCY);
	size += zz;
	zz = sprintf(OutBuffer+size, "<rect x='0' y='0' width='%d' height='%d' style='fill:#%x;stroke-width:0;' />\r\n", ImageCX, ImageCY, BkgColor);
	size += zz;
	zz = sprintf(OutBuffer+size, "<path d='");
	size += zz;


	jj = 0;
	while (jobinfo->points[aa].Slice == iSlice)
	{
		if (jobinfo->points[aa].VertNum == 0)
			zz = sprintf(OutBuffer + size, "M%.3f %.3f ", (jobinfo->points[aa].fX*(1.0 / fPixelSize))+X_Shift, (jobinfo->points[aa].fY*(1.0 / fPixelSize))+Y_Shift);
		else
			zz = sprintf(OutBuffer + size, "L%.3f %.3f ", (jobinfo->points[aa].fX*(1.0 / fPixelSize))+X_Shift, (jobinfo->points[aa].fY*(1.0 / fPixelSize))+Y_Shift);
		size += zz;
		aa++;
	}


	zz = sprintf(OutBuffer + size, "Z' fill='white' />\r\n");
	size += zz;


	zz = sprintf(OutBuffer + size, "</svg>\r\n");
	size += zz;
	return size;
}

void ExportSlcFileToSVG(char *SlcFileName, char *OutFileName,float fPixelSize,int img_cx,int img_cy)
{
    float x;
    float y;


	int headersize = 0;
	int len = 0;
	float readfloat;

	int nSlices = 0;

	char svgName[256];

	numboundries = 0;


	infile = fopen (SlcFileName, "rb");


   while (headersize <= MAXHEADERSIZE)
   { 
	    len = fread (inbuffer,1,1,infile);
	    headersize++;
	    if (inbuffer[0] == 0x0d)
	    {
			len = fread (inbuffer,1,1,infile);
			headersize++;
			if (inbuffer[0] == 0x0a)
			{
				len = fread (inbuffer,1,1,infile);
				headersize++;
				if (inbuffer[0] == 0x1a)
				{
					break;
				}
			}
	    }
   }
   len = fread (inbuffer,1,256,infile);    //skip 256 bytes


   len = fread (inbuffer,1,1,infile);
   int tableentries = inbuffer[0];

	for (int t = 0; t < tableentries; t++)
	{
		len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
		len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
		len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
		len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);		
	}

   minb.X=minx;  minb.Y=miny;
   maxb.X=maxx;  maxb.Y=maxy;

	bool boundsdetermined = 0;
	while (numboundries != 0xffffffff)
	{
		len = fread (inbuffer,1,4,infile);  memcpy(&minzlevel,inbuffer,4);
		len = fread (inbuffer,1,4,infile);  memcpy(&numboundries,inbuffer,4);

		if (numboundries == 0xffffffff)
		{
			break;
		}
		nSlices++;

		sprintf(svgName, "%s%d.svg", OutFileName,nSlices);
        outfile = fopen (svgName, "w+");

	    fprintf(outfile, "<svg xmlns='http://www.w3.org/2000/svg' version='1.0' width='%d' height='%d'>\r\n", img_cx,img_cy);
		fprintf(outfile, "<rect x='0' y='0' width='%d' height='%d' style='fill:black;stroke:blue;stroke-width:0;' />\r\n",img_cx,img_cy);
	    fprintf(outfile, "<path d='");
 	 	for (int b = 0; b < numboundries; b++)
		{
			len = fread (inbuffer,1,4,infile);  memcpy(&numvertices,inbuffer,4);
			len = fread (inbuffer,1,4,infile);  memcpy(&numgaps,inbuffer,4);

			for (int v = 0; v < numvertices; v++)
			{
				len = fread (inbuffer,1,4,infile);  memcpy(&x,inbuffer,4);
				len = fread (inbuffer,1,4,infile);  memcpy(&y,inbuffer,4);

				x *= scalefactor;
				y *= scalefactor;

				if (v==0)
					fprintf(outfile, "M%.3f %.3f ",(x*(1.0/fPixelSize)),(y*(1.0/fPixelSize)));
				else
					fprintf(outfile, "L%.3f %.3f ",(x*(1.0/fPixelSize)),(y*(1.0/fPixelSize)));

				if (x > maxb.X)
					maxb.X = x;
				if (y > maxb.Y)
					maxb.Y = y;
				if (x < minb.X)
					minb.X = x;
				if (y < minb.Y)
					minb.Y = y;
				boundsdetermined = true;
			} 
		}
		fprintf(outfile, "Z' fill='white' />\r\n");
   		fprintf(outfile, "</svg>\r\n");
   		fclose(outfile);
	}

	fclose(infile);
}

void ExportSlcFileToSVGErm(char *SlcFileName, char *OutFileName,float fPixelSize,int img_cx,int img_cy,float X_Shift,float Y_Shift)
{
    float x;
    float y;


	int headersize = 0;
	int len = 0;
	float readfloat;

	int nSlices = 0;

	char svgName[256];

	numboundries = 0;


	infile = fopen (SlcFileName, "rb");


   while (headersize <= MAXHEADERSIZE)
   { 
	    len = fread (inbuffer,1,1,infile);
	    headersize++;
	    if (inbuffer[0] == 0x0d)
	    {
			len = fread (inbuffer,1,1,infile);
			headersize++;
			if (inbuffer[0] == 0x0a)
			{
				len = fread (inbuffer,1,1,infile);
				headersize++;
				if (inbuffer[0] == 0x1a)
				{
					break;
				}
			}
	    }
   }

   len = fread (inbuffer,1,256,infile);    //skip 256 bytes


   len = fread (inbuffer,1,1,infile);
   int tableentries = inbuffer[0];

	for (int t = 0; t < tableentries; t++)
	{
		len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
		len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
		len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
		len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);		
	}

    minb.X=minx;  minb.Y=miny;
    maxb.X=maxx;  maxb.Y=maxy;

	bool boundsdetermined = 0;
	while (numboundries != 0xffffffff)
	{
		len = fread (inbuffer,1,4,infile);  memcpy(&minzlevel,inbuffer,4);
		len = fread (inbuffer,1,4,infile);  memcpy(&numboundries,inbuffer,4);

		if (numboundries == 0xffffffff)
		{
			break;
		}
		nSlices++;


		sprintf(svgName, "%s%d.svg", OutFileName,nSlices);
        outfile = fopen (svgName, "w+");

		sprintf(svgName, "%s%d-Erm.svg", OutFileName,nSlices);
        outfileerm = fopen (svgName, "w+");


	    fprintf(outfile, "<svg xmlns='http://www.w3.org/2000/svg' version='1.0' width='%d' height='%d'>\r\n", img_cx,img_cy);
		fprintf(outfile, "<rect x='0' y='0' width='%d' height='%d' style='fill:black;stroke:blue;stroke-width:0;' />\r\n",img_cx,img_cy);
	    fprintf(outfile, "<path d='");

		fprintf(outfileerm, "<svg xmlns='http://www.w3.org/2000/svg' version='1.0' width='%d' height='%d'>\r\n", img_cx,img_cy);
		fprintf(outfileerm, "<rect x='0' y='0' width='%d' height='%d' style='fill:black;stroke:blue;stroke-width:0;' />\r\n",img_cx,img_cy);
	    fprintf(outfileerm, "<path d='");

 	 	for (int b = 0; b < numboundries; b++)
		{
			len = fread (inbuffer,1,4,infile);  memcpy(&numvertices,inbuffer,4);
			len = fread (inbuffer,1,4,infile);  memcpy(&numgaps,inbuffer,4);

			for (int v = 0; v < numvertices; v++)
			{
				len = fread (inbuffer,1,4,infile);  memcpy(&x,inbuffer,4);
				len = fread (inbuffer,1,4,infile);  memcpy(&y,inbuffer,4);

				x *= scalefactor;
				y *= scalefactor;

				if (v==0)
				{
					fprintf(outfile, "M%.3f %.3f ",(x*(1.0/fPixelSize)),(y*(1.0/fPixelSize)));
					fprintf(outfileerm, "M%.3f %.3f ",(x*(1.0/fPixelSize))+X_Shift,(y*(1.0/fPixelSize))+Y_Shift);
				}
				else
				{
					fprintf(outfile, "L%.3f %.3f ",(x*(1.0/fPixelSize)),(y*(1.0/fPixelSize)));
					fprintf(outfileerm, "L%.3f %.3f ",(x*(1.0/fPixelSize))+X_Shift,(y*(1.0/fPixelSize))+Y_Shift);
				}
				if (x > maxb.X)
					maxb.X = x;
				if (y > maxb.Y)
					maxb.Y = y;
				if (x < minb.X)
					minb.X = x;
				if (y < minb.Y)
					minb.Y = y;
				boundsdetermined = true;
			} 
		}

		fprintf(outfile, "Z' fill='white' />\r\n");
   		fprintf(outfile, "</svg>\r\n");
   		fclose(outfile);

		fprintf(outfileerm, "Z' fill='white' />\r\n");
   		fprintf(outfileerm, "</svg>\r\n");
   		fclose(outfileerm);
	}

	fclose(infile);
}



void ExportJobFile(struct __Job3D *jobinfo, char *OutFileName)
{
	FILE * outfile;
	outfile = fopen (OutFileName, "wb");

	fwrite (jobinfo,1,sizeof(jobinfo),outfile);
	fwrite (jobinfo->points,1,jobinfo->iTotalVerts*sizeof(__Points),outfile);

	fclose(outfile);
}


void OpenJobFile(char *JobFileName,struct __Job3D *jobinfo)
{
	FILE * file;
	file = fopen (JobFileName, "rb");
	fread (jobinfo,1,sizeof(jobinfo),file);
	fread (jobinfo->points,1,jobinfo->iTotalVerts*sizeof(__Points),outfile);
	fclose(file);
}
