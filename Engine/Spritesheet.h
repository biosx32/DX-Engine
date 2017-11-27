#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__
#include "Bmap.h"

class SpritesheetDS {
public:
	~SpritesheetDS();

	int wcount;
	int hcount;
	Bitmap* BitmapImage;
	Bitmap** ptr;
	void Load(Bitmap* BitmapImage, int wcount, int hcount);
};

class Spritesheet {
public:
	Spritesheet() = delete;
	Spritesheet(Bitmap* BitmapImage, int wcount, int hcount);
	~Spritesheet();
	SpritesheetDS* Data;

	void Load(Bitmap* BitmapImage, int wcount, int hcount);
	void RemoveSpriteData();
};


#endif
