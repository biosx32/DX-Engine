#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__
#include "Bmap.h"
#include "Vectors.h"

class BitmapArray {
public:
	Bitmap ** sprites;
	int wcount, hcount, wsize, hsize;
	int count() { return wcount * hcount; }
	Bitmap** GetAddrOfBitmapPointer(int x, int y) { return (x >= 0 && y >= 0 && x < wcount && y < hcount) ? &this->sprites[y * wcount + x] : nullptr; }
public:
	BitmapArray(Bitmap* BitmapImage, int wcount, int hcount) :
		BitmapArray(BitmapImage, wcount, hcount, 1) {}
	BitmapArray(Bitmap* BitmapImage, int wcount, int hcount, float size);
	~BitmapArray();
};


#endif
