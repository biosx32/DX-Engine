#ifndef __FLOODFILL_H__
#define __FLOODFILL_H__
#include "Colors.h"
#include "Interface.h"
#include "BMap.h"
#include <vector>


using std::vector;

class PixelContainer {
public:
	int width;
	int height;
	int lastpos = 0;

	constexpr int gpixelcount();
	
	vector<FFPixel*> stalledPixels;
	FFPixel** pixels;
	vector<FFPixel*> temp_checks;

	void Load(Bitmap* bmp);
	void Draw(Interface* out, int fx, int fy);

	FFPixel* getFirstRawPixel();
	FFPixel*  GetStalled();
	vector<FPixel*>* ProcessGroup(FFPixel * pixel);
	FFPixel * getPixelAt(int x, int y);

	void CheckPixel(FFPixel * pixel);

	

};




#endif