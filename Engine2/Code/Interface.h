#pragma once
#include "Static.h"
#include "Bmap.h"

using std::string;
#define TXT_BUFFER_SIZE 4096

class BitmapFont;
class VectorSpriteSheet;

namespace interfacens {
	struct GraphicalOutput {
		D3DGraphics* gfx,
			Bitmap* bmp
	};
}
using namespace interfacens;

class Interface {
public:
	interfacens::GraphicalOutput GOUT;
public:

	Interface(D3DGraphics* gfx) {
		paint = new Painter(dest);
	}
	BitmapFont * font = &DOS_WHITE;

	void DrawBitmap(Bitmap* bmp, int fx, int fy, float mx, float my);
	void DrawBitmap(Bitmap* bmp, int fx, int fy);
	void DrawSprite(PixelMap* VBmp, int fx, int fy);
	void PrintText(int x, int y, BitmapFont* font, string fmt, ...);
	void FillScreen(Color color);


	void DrawPixel(int xoff, int yoff, Color c) = 0;
	void DrawPixel(int xoff, int yoff, Color c, = 0;

};


class GFXInterface {
public:
	Painter *paint;
	
public:
	Interface(Graphics* gfx) { 
		paint = new Painter(dest); 
	}
	BitmapFont * font = &DOS_WHITE;

	void DrawBitmap(Bitmap* bmp, int fx, int fy, float mx, float my);
	void DrawBitmap(Bitmap* bmp, int fx, int fy);
	void DrawSprite(PixelMap* VBmp, int fx, int fy);
	void PrintText(int x, int y, BitmapFont* font, string fmt, ...);
	void FillScreen(Color color);


	void DrawPixel(int xoff, int yoff, Color c);
	void DrawPixel(int xoff, int yoff, Color c, int m);

};


