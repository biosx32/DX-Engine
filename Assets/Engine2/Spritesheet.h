#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__
#include "Bmap.h"
#include "VectorBitmap.h"
#include "Vectors.h"
using std::vector;

namespace pxstate
{
	enum Type
	{
		background = 1, checked = 2, skip = (background | checked)
	};
};


class VectorSpriteSheet{
public:
	vector<MySprite*> sprites;
public:
	VectorSpriteSheet(Bitmap* BitmapImage);
	~VectorSpriteSheet();
	
};

class FixedSpriteArray {
public:
	Bitmap ** sprites;
	int wcount, hcount, wsize, hsize;
	int count() { return wcount * hcount; }
	Bitmap** GetAddrOfBitmapPointer(int x, int y) { return (x >= 0 && y >= 0 && x < wcount && y < hcount) ? &this->sprites[y * wcount + x] : nullptr; }
public:
	FixedSpriteArray(Bitmap* BitmapImage, int wcount, int hcount) :
		FixedSpriteArray(BitmapImage, wcount, hcount, 1) {}
	FixedSpriteArray(Bitmap* BitmapImage, int wcount, int hcount, float size);
	~FixedSpriteArray();
};



class FFPixel : public FPixel {
public:
	int state;
	FFPixel(int x, int y, Color c, int state) : FPixel(x, y, c), state(state) {}
};

class PixelContainer {
protected:
	
	
	vector<FFPixel*> stalledPixels;
	vector<FPixel*>* result_group;

protected:
	
	void CheckPixel(FFPixel * pixel);

public:
	const int gridsize = 6;
	Vector2 lastpos = Vector2(0,0);
	FFPixel ** pixels;
	int width;
	int height;
	inline int pixelcount() { return width * height; }

public:
	~PixelContainer();
	PixelContainer(Bitmap* bmp);
	FFPixel* getPixelAt(int x, int y);
	FFPixel* GetNextSpritePixel();
	MySprite* GetGroupFrom(FFPixel * pixel);
	MySprite* GetNextSpriteGroup();
	

};





#endif
