#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__
#include "Bmap.h"

class Spritesheet {
public:
	Spritesheet() = delete;
	Spritesheet(int W_COUNT, int H_COUNT);
	~Spritesheet();

	int wcount;
	int hcount;
	Color transparency = 0xb1b1f4b1;
	Bitmap* BitmapImage;
	Bitmap** SpriteData;
	
	void Load(Bitmap* BitmapImage);
};


#endif
