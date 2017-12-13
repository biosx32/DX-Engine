#ifndef __FLOODFILL_H__
#define __FLOODFILL_H__
#include "Colors.h"
#include "Interface.h"
#include "BMap.h"
#include <vector>


using std::vector;

class PixelContainer {
protected:
	int get_pixelcount() { return width * height; }
	int lastpos = 0;
	FFPixel ** pixels;
	vector<FFPixel*> stalledPixels;
	vector<FFPixel*> temp_checks;

protected:
	
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