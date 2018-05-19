#pragma once
#include "Static.h"
#include "Bmap.h"
#include "GlobalObjects.h"
#include "PixelMap.h"
#include "Painter.h"

using std::string;
#define TXT_BUFFER_SIZE 4096

class BitmapFont;
class VectorSpriteSheet;

class Interface: public Painter {
public:
	BitmapFont * DFONT = &DOS_WHITE;
	Painter* paint = this;
	virtual void DrawPixel(int xoff, int yoff, Color c) = 0;

	void DrawBitmap(Bitmap * Bmp, int xoff, int yoff, float mx, float my)
	{
		if (!(mx > 0 && my > 0)) return;

		int width = Bmp->width;
		int height = Bmp->height;
		int draw_width = Bmp->width * mx;
		int draw_height = Bmp->height * my;

		for (int y = 0; y < draw_height; y++) {
			int srcy = y / my;
			for (int x = 0; x < draw_width; x++) {
				int srcx = x / mx;
				Color *pixel = Bmp->GetPixelPointer(srcx, srcy);
				if (!Bmp->GetIsBackground(*pixel)) {
					
					DrawPixel(xoff + x, yoff + y, *pixel);
			
				}


			}

		}

	};
	void DrawBitmap(Bitmap* Bmp, int fx, int fy) {

		for (int yoff = 0; yoff < Bmp->height; yoff++) {
			for (int xoff = 0; xoff < Bmp->width; xoff++) {
				int finalx = fx + xoff;
				int finaly = fy + yoff;
				Color Pixel = *Bmp->GetPixelPointer(xoff, yoff);
				if (!Bmp->GetIsBackground(Pixel)) {
					DrawPixel(finalx, finaly, Pixel);
				}
			}
		}

	}
	void DrawSprite(PixelMap* VBmp, int fx, int fy) {
		for (std::vector<FPixel*>::iterator it = VBmp->pixels->begin(); it != VBmp->pixels->end(); ++it) {
			DrawPixel(fx + (*it)->x, fy + (*it)->y, (*it)->color);
		}
	}
	void PrintText(int x, int y, BitmapFont* DFONT, string fmt, ...) {
		char buffer[TXT_BUFFER_SIZE];
		va_list args;
		va_start(args, fmt);
		int rc = vsnprintf(buffer, TXT_BUFFER_SIZE, fmt.c_str(), args);
		va_end(args);
		fmt = buffer;

		double rel_pos_x = 0;
		double rel_pos_y = 0;

		for (char chr : fmt) {

			float charw = DFONT->charw;
			float charh = DFONT->charh;

			if (chr == '\x20') {
				rel_pos_x += charw;
			}

			else if (chr == '\n') { // \\x10
				rel_pos_y += charh;
				rel_pos_x = 0;
			}

			if (chr < DFONT->offset) {
				continue;
			}

			Bitmap* CharBitmap = DFONT->GetCharacterRepr(chr);


			int destx = (int)(x + rel_pos_x);
			int desty = (int)(y + rel_pos_y);

			DrawBitmap(CharBitmap, destx, desty);
			//this->Painter->rectangle(destx, desty, charw, charh, 0xFFFF0000);
			rel_pos_x += charw;
		}
	}
	void FillScreen(Color color) {
		rectangle(0, 0, SCREENWIDTH - 1, SCREENHEIGHT - 1, color);
	}

	
};


class GFXInterface: public Interface {
public:
	D3DGraphics * gfx;
	GFXInterface(D3DGraphics* gfx): gfx(gfx) {}

	void DrawPixel(int xoff, int yoff, Color c) {
		if (!gfx ||
			xoff >= SCREENWIDTH ||
			yoff >= SCREENHEIGHT ||
			xoff < 0 ||
			yoff < 0) {
			return;
		}
		this->gfx->PutPixel(xoff, yoff, c);
	}
};

class BMPInterface : public Interface {
public:
	Bitmap* bmp;
	BMPInterface(Bitmap* bmp) : bmp(bmp) {}

	void DrawPixel(int xoff, int yoff, Color c) {
		Color * dst = bmp->GetPixelPointer(xoff, yoff);
		if (dst != nullptr) {
			*dst = c;
		}
	}
};





