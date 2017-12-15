#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__
#include "Bmap.h"
#include "Interface.h"



class Spritesheet{
public:
	Spritesheet(TransparentBitmap* BitmapImage);
	~Spritesheet();
	vector<VectorBitmap*> sprites;
};


class FFPixel : public FPixel {
public:
	int state;
	FFPixel(int x, int y, Color c, int state) : FPixel(x, y, c), state(state) {}
};

class PixelContainer {
protected:
	int lastpos = 0;

	
	vector<FFPixel*> stalledPixels;
	vector<FPixel*>* result_group;

protected:
	FFPixel* getPixelAt(int x, int y);
	void CheckPixel(FFPixel * pixel);

public:
	FFPixel ** pixels;
	int width;
	int height;
	int get_pixelcount() { return width * height; }
public:
	~PixelContainer();
	FFPixel* GetNextSpritePixel();
	VectorBitmap* GetGroupFrom(FFPixel * pixel);
	PixelContainer(TransparentBitmap* bmp);
	void Load(TransparentBitmap* bmp);
	VectorBitmap* GetNextSpriteGroup();
	

};





#endif
