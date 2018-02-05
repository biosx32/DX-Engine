#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "Drawing.h"
#include "Colors.h"
#include "D3DGraphics.h"
#include "Bmap.h"
#include "RasterFont.h"

#define TXT_BUFFER_SIZE 1024

class RasterFont;
class VectorSpriteSheet;
class Interface {
public:
	Painter *paint;
	
public:
	Interface(PixelDest dest) { 
		paint = new Painter(dest); 
	}

	void DrawBitmap(Bitmap* bmp, int fx, int fy, float mx, float my);
	void DrawBitmap(Bitmap* bmp, int fx, int fy);
	void DrawSprite(FPixelMap* VBmp, int fx, int fy);
	void PrintText(int x, int y, RasterFont* font, char * text);
	void PrintText(int x, int y, RasterFont* font, const char *fmt, ...);
	void FillScreen(Color color);

};

#endif