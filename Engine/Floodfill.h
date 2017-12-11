#ifndef __FLOODFILL_H__
#define __FLOODFILL_H__
#include "Colors.h"
#include "Interface.h"
#include "BMap.h"
#include <vector>



class PixelContainer {
public:
	int pixelcount;
	int width;
	int height;
	int lastpos = 0;
	int groups = 0;
	
	std::vector<FFPixel*> stalledPixels;
	FFPixel** pixels;
	std::vector<FFPixel*>* groupsvec;


	void Load(Bitmap* bmp);
	void Draw(Interface* out, int fx, int fy);

	FFPixel* getFirstRawPixel();
	FFPixel*  GetStalled();
	FFPixel * getPixelAt(int x, int y);

	void GetGroup();

	void IteratePendingPixels();
	void CheckPixel(FFPixel * pixel);

	

};




#endif