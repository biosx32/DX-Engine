#ifndef __FLOODFILL_H__
#define __FLOODFILL_H__
#include "Colors.h"
#include "Interface.h"
#include "BMap.h"
#include <vector>


using std::vector;

class PixelContainer {
protected:
	vector<FFPixel*> stalledPixels;
	vector<FFPixel*> temp_checks;
	FFPixel** pixels;

	int lastpos = 0;
	int get_pixelcount() { return width * height; }
	
	FFPixel * getPixelAt(int x, int y);
	FFPixel* GetNextSpritePixel();
	vector<FPixel*>* GetGroupFrom(FFPixel * pixel);
	void CheckPixel(FFPixel * pixel);

public:
	int width;
	int height;
	
	void Load(Bitmap* bmp);
	void Draw(Interface* out, int fx, int fy);

	
	vector<FPixel*>* GetNextSpriteGroup();
	

};




#endif