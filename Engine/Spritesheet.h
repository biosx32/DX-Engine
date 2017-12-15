#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__
#include "Bmap.h"
#include "Interface.h"



class Spritesheet{
public:
	Spritesheet(TransparentBitmap* BitmapImage);
	~Spritesheet();
	vector<Sprite*> sprites;
};


class FFPixel : public FPixel {
public:
	int state;
	FFPixel(int x, int y, Color c, int state) : FPixel(x, y, c), state(state) {}
};

class PixelContainer {
protected:
	int lastpos = 0;
	int get_pixelcount() { return width * height; }

	FFPixel ** pixels;
	vector<FFPixel*> stalledPixels;
	vector<FPixel*>* result_group;

protected:
	
	FFPixel* getPixelAt(int x, int y);
	FFPixel* GetNextSpritePixel();
	VectorBitmap* GetGroupFrom(FFPixel * pixel);
	void CheckPixel(FFPixel * pixel);

public:
	int width;
	int height;

public:
	~PixelContainer();
	PixelContainer(TransparentBitmap* bmp);
	void Load(TransparentBitmap* bmp);
	VectorBitmap* GetNextSpriteGroup();
	

};





#endif
