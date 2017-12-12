#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__
#include "Bmap.h"
#include "Interface.h"


class Sprite {
public:
	Sprite(TransparentBitmap* TBmp);
	Sprite(vector<FPixel*>* src);
	TransparentBitmap* image = nullptr;
};

class SpritesheetDG {
public:
	~SpritesheetDG();

	int spritecount;
	vector<Sprite*>* data = nullptr;
	;; TODO: vector sprites : Loading by converting bitmap to vector bitmap or
		;; only using floodfill
		;; should sprite be vector or transparentbitmap
	void Load(TransparentBitmap* BitmapImage, int wcount, int hcount);
	void Load(vector<FPixel*>* src);

};

class Spritesheet {
public:
	Spritesheet();
	Spritesheet(TransparentBitmap* BitmapImage, int wcount, int hcount);
	~Spritesheet();

	SpritesheetDG* datagroup = nullptr;

	void Load(TransparentBitmap* BitmapImage, int wcount, int hcount)
	void RemoveSpriteData();
};









#endif
