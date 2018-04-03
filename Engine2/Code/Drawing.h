#pragma once

#include "Bmap.h"
#include "CustomMath.h"



class Painter {
public:
	Painter(PixelDest pxd): pxd(pxd) {};
public:
	void FastHLine(int x, int y, int w, Color c);
	void FastVLine(int x, int y, int h, Color c);

public:
	void line(int x1, int y1, int x2, int y2, Color c);
	void line(int x1, int y1, int x2, int y2, Color c, int width);

    void circleBorder(int x, int y, int diam, Color c, int width);
	void circle(int x, int y, int diam, Color c);

	void rectangleBorder( int x, int y, int w, int h, Color c, int r);
	void rectangle(int x, int y, int w, int h, Color c);

	void ellipseBorder(int xoff, int yoff, int width, int height, Color c, int r);
	void ellipse(int xoff, int yoff, int width, int height, Color c);

};

