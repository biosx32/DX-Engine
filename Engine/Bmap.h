#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stdio.h>
#include <math.h>  
#include "Colors.h"
#include "Func.h"

class BitmapDS {
public:
	
	BitmapDS(int width, int height);
	~BitmapDS();
	int width = 0, height = 0, pixelcount = 0;
	Color * data;
};

class Bitmap;
class Bitmap {
public:
	Bitmap();
	Bitmap(char* FileName);
	Bitmap(int width, int height);
	~Bitmap();

	BitmapDS* datagroup = nullptr;

	int Load(char* FileName);
	virtual bool IsColorTransparent(Color color) { return 0; }
	virtual Bitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT);
};

class TransparentBitmap : public Bitmap {
public:
	TransparentBitmap() : Bitmap() {}
	TransparentBitmap(Bitmap* bmp) : Bitmap(*bmp) {}
	TransparentBitmap(char* FileName) : Bitmap(FileName) {}
	TransparentBitmap(int width, int height) : Bitmap(width, height) {}

	double tolerance = 0.001f;
	Color transparency = 0x00b1f4b1; // 177,244,177

	TransparentBitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT) override;
	bool IsColorTransparent(Color color) override;
	
};







#endif
