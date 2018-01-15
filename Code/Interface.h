#ifndef __INTERFACE_H__
#define __INTERFACE_H__


#include "Colors.h"
#include "D3DGraphics.h"
#include "Bmap.h"
#include "Text.h"
#include "Drawing.h"

class Draw;
class FontType;
class VectorSpriteSheet;
class Interface {
public:
	Draw * Painter;
	D3DGraphics* gfx;
public:
	Interface(D3DGraphics* gfx);

	void DrawPixel(int xoff, int yoff, Color c);
	void DrawPixelM(int xoff, int yoff, Color c, int m);

	void DrawBitmapM(Bitmap* bmp, int fx, int fy, float mx, float my);
	void DrawBitmap(Bitmap* bmp, int fx, int fy);
	void DrawSprite(MySprite* VBmp, int fx, int fy);
	void PrintText(int x, int y, char* text, double scale, FontType* font);
	void FillScreen(Color color);

};

#endif