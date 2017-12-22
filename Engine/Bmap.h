#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stdio.h>
#include <math.h>  
#include "Colors.h"
#include "Func.h"

class Bitmap {
public:
	int width, height;
	Color bkclr, *data;

	inline int pixelcount() { return width * height; }
	inline virtual bool IsColorTransparent(Color color) { return 0; }

public:
	Bitmap(char* FileName);
	Bitmap(int width, int height, Color bkclr);
	~Bitmap();

	virtual Bitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT);
};


class TransparentBitmap : public Bitmap {
public:
	double tolerance = 0.0000001;
	bool IsColorTransparent(Color color) override;
	
public:
	TransparentBitmap(Bitmap* bmp);
	TransparentBitmap(char* FileName, Color transp);
	TransparentBitmap(int width, int height, Color transp);

	TransparentBitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT) override;
	
};



#endif
