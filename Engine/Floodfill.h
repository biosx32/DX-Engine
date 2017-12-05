#ifndef __FLOODFILL_H__
#define __FLOODFILL_H__
#include "Colors.h"
#include "Interface.h"
#include "BMap.h"

class FFPixel {
public:
	FFPixel();
	int x, y;
	Color color;
	Color backgroundcolor;

	bool IsBackgroundColor();
	bool CheckedNeighbors = false;

};

class PixelContainer {
public:
	int pixelcount;
	int width;
	int height;
	FFPixel* pixels;

	Color transparency = 0x00b1f4b1;

	void Load(TransparentBitmap* bmp);
	void Draw(Interface* out, int fx, int fy);
};




#endif