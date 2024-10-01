

#ifndef SDLGG_H
#define SDLGG_H

#ifndef SDL_CPLUSPLUS
#ifdef __cplusplus
extern "C" {
#endif
#endif

enum SDpaintType {
	SD_PAINT_NONE = 0,
	SD_PAINT_COLOR = 1,
	SD_PAINT_LINEAR_GRADIENT = 2,
	SD_PAINT_RADIAL_GRADIENT = 3
};

enum SDspreadType {
	SD_SPREAD_PAD = 0,
	SD_SPREAD_REFLECT = 1,
	SD_SPREAD_REPEAT = 2
};

enum SDlineJoin {
	SD_JOIN_MITER = 0,
	SD_JOIN_ROUND = 1,
	SD_JOIN_BEVEL = 2
};

enum SDlineCap {
	SD_CAP_BUTT = 0,
	SD_CAP_ROUND = 1,
	SD_CAP_SQUARE = 2
};

enum SDfillRule {
	SD_FILLRULE_NONZERO = 0,
	SD_FILLRULE_EVENODD = 1
};

enum SDflags {
	SD_FLAGS_VISIBLE = 0x01
};

typedef struct SDgradientStop {
	unsigned int color;
	float offset;
} SDgradientStop;

typedef struct SDgradient {
	float xform[6];
	char spread;
	float fx, fy;
	int nstops;
	SDgradientStop stops[1];
} SDgradient;

typedef struct SDpaint {
	char type;
	union {
		unsigned int color;
		SDgradient* gradient;
	};
} SDpaint;

typedef struct SDpath
{
	float* pts;					// Cubic bezier points: x0,y0, [cpx1,cpx1,cpx2,cpy2,x1,y1], ...
	int npts;					// Total number of bezier points.
	char closed;				// Flag indicating if shapes should be treated as closed.
	float bounds[4];			// Tight bounding box of the shape [minx,miny,maxx,maxy].
	struct SDpath* next;		// Pointer to next path, or NULL if last element.
} SDpath;

typedef struct SDshape
{
	char id[64];				// Optional 'id' attr of the shape or its group
	SDpaint fill;				// Fill paint
	SDpaint stroke;			// Stroke paint
	float opacity;				// Opacity of the shape.
	float strokeWidth;			// Stroke width (scaled).
	float strokeDashOffset;		// Stroke dash offset (scaled).
	float strokeDashArray[8];			// Stroke dash array (scaled).
	char strokeDashCount;				// Number of dash values in dash array.
	char strokeLineJoin;		// Stroke join type.
	char strokeLineCap;			// Stroke cap type.
	float miterLimit;			// Miter limit
	char fillRule;				// Fill rule, see SDfillRule.
	unsigned char flags;		// Logical or of SD_FLAGS_* flags
	float bounds[4];			// Tight bounding box of the shape [minx,miny,maxx,maxy].
	SDpath* paths;			// Linked list of paths in the image.
	struct SDshape* next;		// Pointer to next shape, or NULL if last element.
} SDshape;

typedef struct SDimage
{
	float width;				// Width of the image.
	float height;				// Height of the image.
	SDshape* shapes;			// Linked list of shapes in the image.
} SDimage;

// Parses SVG file from a file, returns SVG image as paths.
SDimage* sdParseFromFile(const char* filename, const char* units, float dpi);

// Parses SVG file from a null terminated string, returns SVG image as paths.
// Important note: changes the string.
SDimage* sdParse(char* input, const char* units, float dpi);

// Duplicates a path.
SDpath* sdDuplicatePath(SDpath* p);

// Deletes an image.
void sdDelete(SDimage* image);

#ifndef SDL_CPLUSPLUS
#ifdef __cplusplus
}
#endif
#endif

#endif

#include "lib/png.h"

struct sdImage
{
public:
	int    Width;
	int    Height;
	unsigned char *lpData;
};

bool LoadImageRes(char *Buffer, sdImage *lpImageData, float fScale = 1.0);
bool LoadPngRes(unsigned char *lpAddress,int BufferLen, sdImage *lpImageData);

