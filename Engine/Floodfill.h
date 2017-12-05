#ifndef __FLOODFILL_H__
#define __FLOODFILL_H__
#include "Colors.h"
#include "Interface.h"
#include "BMap.h"

class FFPixel {
public:
	FFPixel(int x, int y, Color c);
	int group;
	int x, y;
	Color color;
	bool checked = false;

};

class PixelContainer {
public:
	int pixelcount;
	int width;
	int height;

	int GroupIter=0;
	
	Color transparency = 0x00b1f4b1;

	void Load(Bitmap* bmp);
	void Draw(Interface* out, int fx, int fy);


	FFPixel** pixels;
	FFPixel* getFirstPixel();

	bool IsPixelBackground(FFPixel* ptr);

	void CheckNeighbors(FFPixel * pixel);

};




#endif