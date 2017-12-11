#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stdio.h>
#include <math.h>  
#include "Colors.h"
#include "Func.h"
#include <vector>

namespace pxstate
{
	enum Type
	{
		background = 1, checked = 2, skip = (background | checked)
	};
};

class FPixel {
public:
	int x, y;
	Color color;
	FPixel(int x, int y, Color c);
};


class FFPixel: public FPixel {
public:
	int state, group;
	FFPixel(int x, int y, Color c, int state);
};


class BitmapDS {
public:
	
	BitmapDS(int width, int height);
	~BitmapDS();
	int width = 0, height = 0, pixelcount = 0;
	Color * data;
};



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

class VectorBitmapDS {
public:

	VectorBitmapDS();
	VectorBitmapDS(std::vector<FPixel*>* src);
	~VectorBitmapDS();
	int width, height;
	std::vector<FPixel*>* pixels;

	void UpdateWH(); //update width and height variables

	int size();
	
};

class VectorBitmap {
public:
	VectorBitmapDS* datagroup = nullptr;
	~VectorBitmap();
	VectorBitmap();
	VectorBitmap(std::vector<FPixel*>* src);
};







#endif
