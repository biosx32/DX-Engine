#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__
#include "Bmap.h"

class Vector2 {
public:
	int x=0, y=0;
	Vector2() {}
	Vector2(int x, int y): x(x), y(y){}
};


namespace pxstate
{
	enum Type
	{
		background = 1, checked = 2, skip = (background | checked)
	};
};


class Spritesheet{
public:
	vector<VectorBitmap*> sprites;
public:
	Spritesheet(TransparentBitmap* BitmapImage);
	Spritesheet(TransparentBitmap* BitmapImage, int wcount, int hcount);
	~Spritesheet();
	
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
	Vector2 lastpos;
	FFPixel ** pixels;
	int width;
	int height;
	inline int pixelcount() { return width * height; }
public:
	~PixelContainer();
	FFPixel* getPixelAt(int x, int y);
	FFPixel* GetNextSpritePixel();
	VectorBitmap* GetGroupFrom(FFPixel * pixel);
	PixelContainer(TransparentBitmap* bmp);
	void Load(TransparentBitmap* bmp);
	VectorBitmap* GetNextSpriteGroup();
	

};





#endif
