#ifndef __MY_DRAWING_H__
#define __MY_DRAWING_H__
#include "..\Assets\D3DGraphics.h"
#include  "Colors.h"
#include "Bmap.h"
#include <math.h>

class PixelDest {
public:
	D3DGraphics* gfx;
	Bitmap* bmp;

	PixelDest(Bitmap* bmp) :bmp(bmp),gfx(0) {}
	PixelDest(D3DGraphics* gfx) :gfx(gfx),bmp(0) {}

	void DrawPixel(int xoff, int yoff, Color c);
	void DrawPixel(int xoff, int yoff, Color c, int m);
};

class Painter {
public:
	PixelDest pxd;
	Painter(PixelDest pxd): pxd(pxd) {};
public:
	void FastHLine(int x, int y, int w, Color c);
	void FastVLine(int x, int y, int h, Color c);
	void DrawPixel(int xoff, int yoff, Color c);
	void DrawPixel(int xoff, int yoff, Color c, int m);
public:
	void line(int x1, int y1, int x2, int y2, Color c);
	void line(int x1, int y1, int x2, int y2, Color c, int width);
    void circle(int x, int y, int rad, Color c);
	void circle(int x, int y, int rad, Color c, bool fill);
	void rectangle( int x, int y, int w, int h, Color c);
	void rectangle(int x, int y, int w, int h, Color c, bool fill);
};


#endif 
