#pragma once
#include "PixelMap.h"
#include "FloodfillMap.h"
class VectorSpriteSheet {
public:
	vector<PixelMap*> sprites;
public:
	VectorSpriteSheet(Bitmap* BitmapImage);
	~VectorSpriteSheet();

};