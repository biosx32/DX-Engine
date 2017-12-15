#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stdio.h>
#include <math.h>  
#include "Colors.h"
#include "Func.h"
#include <vector>

using std::vector;

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
	FPixel(int x, int y, Color c): x(x), y(y), color(c) {}
};


class Bitmap {
protected:
	void Load(int width, int height, Color bkclr);
	void Load(char* FileName);
public:
	int width, height;
	Color bkclr, *data;
	int constexpr pixelcount() { return width * height; }

public:
	Bitmap(char* FileName) { this->Load(FileName); }
	Bitmap(int width, int height, Color bkclr);
	~Bitmap() { delete[] this->data; }


public: 
	virtual bool IsColorTransparent(Color color) { return 0; }
	virtual Bitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT);
};


class TransparentBitmap : public Bitmap {
public:
	double tolerance = 0.001f;
public:
	TransparentBitmap(Bitmap* bmp) : Bitmap(*bmp) {}
	TransparentBitmap(char* FileName) : Bitmap(FileName) {}
	TransparentBitmap(int width, int height, Color transp) : Bitmap(width, height, transp) {};

	TransparentBitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT) override;
	bool IsColorTransparent(Color color) override;
	
};


class VectorBitmap {

protected:
	void Normalise();
	int offx, offy;

public:
	int width, height;
	std::vector<FPixel*>* pixels;

public:
	VectorBitmap(vector<FPixel*>* src) {this->Load(src);}
	VectorBitmap(TransparentBitmap* src);
	~VectorBitmap();

	void Load(std::vector<FPixel*>* src);

	
};







#endif
