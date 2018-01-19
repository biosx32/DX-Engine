#ifndef __INTERFACE_H__
#define __INTERFACE_H__


#include "Colors.h"
#include "D3DGraphics.h"
#include "Bmap.h"
#include "Text.h"
#include "Drawing.h"

class Painter;
class FontType;
class VectorSpriteSheet;
class Interface {
public:
	Painter * paint;
	
public:
	Interface(D3DGraphics* gfx);

	void DrawBitmapM(Bitmap* bmp, int fx, int fy, float mx, float my);
	void DrawBitmap(Bitmap* bmp, int fx, int fy);
	void DrawSprite(MySprite* VBmp, int fx, int fy);
	void PrintText(int x, int y, char* text, double scale, FontType* font);
	void FillScreen(Color color);

};

#endif