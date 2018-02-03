#ifndef __MY_DRAWING_H__
#define __MY_DRAWING_H__
#include "D3DGraphics.h"
#include  "Colors.h"
#include "Bmap.h"
#include <math.h>
#include "CustomMath.h"

class PixelDest {
public:
	D3DGraphics* gfx = nullptr;
	Bitmap* bmp = nullptr;

	PixelDest(Bitmap* bmp) :bmp(bmp),gfx(nullptr) {}
	PixelDest(D3DGraphics* gfx) :gfx(gfx),bmp(nullptr) {}

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

	void rectangleBorder( int x, int y, int w, int h, Color c, int r);
	void rectangle(int x, int y, int w, int h, Color c);

	void ellipseBorder(int xoff, int yoff, int width, int height, Color c);
};


#endif 
