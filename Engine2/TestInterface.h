#ifndef __T_INTERF_H__
#define __T_INTERF_H__
#include "Interface.h"
#include "FloodfillMap.h"

#include "Vectors.h"
#include "Labelz.h"
#include "Mouse.h"
#include <stdio.h>

class TestInterface : public Interface {
public:
	TestInterface(PixelDest dest) : Interface(dest) {}
	void DrawPixelContainer(FloodFillMap * src, int fx, int fy);
	void DrawSpritesheet(BitmapArray* sh, int xoff, int yoff);
};


class Grid {
public:
	int x, y, size;
	int mid;
	const int wc = 20;
	Grid(int x, int y, int size) : x(x), y(y), size(size) { mid = wc / 2; }
	void Draw(Interface* out);
};

#endif