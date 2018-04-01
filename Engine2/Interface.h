#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "Drawing.h"
#include "Colors.h"
#include "D3DGraphics.h"
#include "Bmap.h"
#include "BitmapFont.h"
#include "PixelMap.h"
#include "GlobalObjects.h"

using std::string;
#define TXT_BUFFER_SIZE 4096

class BitmapFont;
class VectorSpriteSheet;
class Interface {
public:
	Painter *paint;
	
public:
	Interface(PixelDest dest) { 
		paint = new Painter(dest); 
	}
	BitmapFont * font = &DOS_WHITE;

	void DrawBitmap(Bitmap* bmp, int fx, int fy, float mx, float my);
	void DrawBitmap(Bitmap* bmp, int fx, int fy);
	void DrawSprite(PixelMap* VBmp, int fx, int fy);
	void PrintText(int x, int y, BitmapFont* font, string fmt, ...);
	void FillScreen(Color color);

};

#endif