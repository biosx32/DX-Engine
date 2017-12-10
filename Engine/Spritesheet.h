#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__
#include "Bmap.h"
#include "Interface.h"

class Interface;
class SpritesheetDS {
public:
	~SpritesheetDS();

	int wcount;
	int hcount;
	int count;
	Bitmap* BitmapImage = nullptr;
	Bitmap** data = nullptr;
	void Load(Bitmap* BitmapImage, int wcount, int hcount);
	void Load(Bitmap* BitmapImage);

};

class Spritesheet {
public:
	Spritesheet();
	Spritesheet(Bitmap* BitmapImage, int wcount, int hcount);
	~Spritesheet();
	SpritesheetDS* datagroup = nullptr;

	void Load(Bitmap* BitmapImage, int wcount, int hcount);
	void Load(Bitmap* BitmapImage);
	void RemoveSpriteData();
};









#endif
