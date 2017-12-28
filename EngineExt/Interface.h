#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include "Graphics.h"
#include "Bmap.h"
#include "Text.h"
#include "Drawing.h"
#include <string.h>

#define FLIP_HORIZONTALLY 1
#define FLIP_VERTICALLY 2
#define CW_90 4
#define CW_180 8
#define CW_270 16
#define CCW_90 CW_270
#define CCW_180 CW_180
#define CCW_270 CW_90

class Draw;
class Label;
class VectorSpriteSheet;
class Interface {
public:
	Draw * Painter;
	Graphics* gfx;
public:
	Interface(Graphics* gfx);

	void DrawPixel(int xoff, int yoff, Color c);
	void DrawPixelM(int xoff, int yoff, Color c, int m);

	void DrawBitmapM(Bitmap* bmp, int fx, int fy, float mx, float my);
	void DrawBitmap(Bitmap* bmp, int fx, int fy);
	void DrawSprite(Sprite* VBmp, int fx, int fy);
	void DrawLabel(int x, int y, Label* label, double scale);
	
	void FillScreen(Color color);
	
};

#endif