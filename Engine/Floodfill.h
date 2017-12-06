#ifndef __FLOODFILL_H__
#define __FLOODFILL_H__
#include "Colors.h"
#include "Interface.h"
#include "BMap.h"

enum PixelState {
	background, checked, pending, raw
};

class FFPixel {
public:
	FFPixel(int x, int y, Color c, int state);
	int x, y;
	Color color;

	int state;

};

class PixelContainer {
public:
	int pixelcount;
	int width;
	int height;
	
	Color transparency = 0x00b1f4b1;

	void Load(Bitmap* bmp);
	void Draw(Interface* out, int fx, int fy);


	FFPixel** pixels;
	FFPixel* getFirstPixel();

	FFPixel* getPixelAt(int x, int y);


	bool IsColorBackground(Color c);

	void StartVirus(FFPixel * pixel);

	FFPixel * GetPending();

	void CheckPixel(FFPixel * pixel);

};




#endif