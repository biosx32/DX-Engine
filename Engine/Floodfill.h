#ifndef __FLOODFILL_H__
#define __FLOODFILL_H__
#include "Colors.h"
#include "Interface.h"
#include "BMap.h"
#include <vector>

namespace pxstate
{
	enum Type
	{
		background = 1, checked = 2, unchecked = ~background & ~checked
	};
};



class FFPixel {
public:
	int state;
	int x, y;
	Color color;

	FFPixel(int x, int y, Color c, int state);
	

};

class PixelContainer {
public:
	int pixelcount;
	int width;
	int height;
	int lastpos = 0;
	int groups = 0;
	
	Color transparency = 0x00b1f4b1;
	std::vector<FFPixel*> stalledPixels;
	FFPixel** pixels;


	void Load(Bitmap* bmp);
	void Draw(Interface* out, int fx, int fy);

	FFPixel* getFirstRawPixel();
	FFPixel*  GetStalled();
	FFPixel * getPixelAt(int x, int y);

	bool IsColorBackground(Color c);
	
	unsigned int GetPendingPixelsCount();
	bool HasPendingPixels();

	void IteratePendingPixels();
	void CheckPixel(FFPixel * pixel);
	void AddToPending(FFPixel * pixel);

	

};




#endif