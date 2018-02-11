#pragma once
#include "PixelMap.h"
#include "Vectors.h"

class FloodFillMap {

protected:
	vector<FFPixel*> stalledPixels;
	vector<FPixel*>* result_group;
	void CheckPixel(FFPixel * pixel);

public:
	const int gridsize = 6;
	Vector2 lastpos = Vector2(0, 0);
	FFPixel ** pixels;
	int width;
	int height;
	inline int pixelcount() { return width * height; }

public:
	~FloodFillMap();
	FloodFillMap(Bitmap* bmp);
	FFPixel* getPixelAt(int x, int y);
	FFPixel* GetNextSpritePixel();
	PixelMap* GetGroupFrom(FFPixel * pixel);
	PixelMap* GetNextSpriteGroup();
};
