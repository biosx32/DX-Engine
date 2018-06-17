#pragma once
#include "Colors.h"
#include "Bmap.h"
#include "BitmapFont.h"
#include <string>

#define TXT_BUFFER_SIZE 4096
using std::string;

class Painter {
public:
	void DrawPixelM(int xoff, int yoff, Color c, int m) {
		xoff *= m;
		yoff *= m;

		for (int y = 0; y < m; y++) {
			for (int x = 0; x < m; x++) {

				int finalx = xoff + x;
				int finaly = yoff + y;

				DrawPixel(finalx, finaly, c);

			}
		}
	}
	virtual void DrawPixel(int xoff, int yoff, Color c) = 0;

public:
	void FastHLine(int x, int y, int w, Color c) {
		if (w < 0) {
			x += w;
			w = -w;
		}
		for (int i = 0; i < w; i++) {
			DrawPixel(x + i, y, c);
		}
	}
	void FastVLine(int x, int y, int h, Color c) {
		if (h < 0) {
			y += h;
			h = -h;
		}
		for (int i = 0; i < h; i++) {
			DrawPixel(x, y + i, c);
		}
	}

	void line(int x1, int y1, int x2, int y2, Color c, int width) {
		int dstx = x2 - x1;
		int dsty = y2 - y1;

		DrawPixel(x2, y2, width);
		DrawPixel(x1, y1, width);

		if (dsty == 0 && dstx == 0) {

		}

		else if (abs(dsty) > abs(dstx))
		{
			if (dsty < 0)
			{
				Swap(&x1, &x2);
				Swap(&y1, &y2);
			}

			float m = (float)dstx / (float)dsty;
			float b = x1 - m * y1;
			for (int y = y1; y <= y2; y = y + 1)
			{
				int x = (int)(m*y + b + 0.5f);
				FastVLine(x, y, width, c);
				FastHLine(x, y, width, c);
			}

		}
		else
		{
			if (dstx < 0)
			{
				Swap(&x1, &x2);
				Swap(&y1, &y2);
			}
			float m = (float)dsty / (float)dstx;
			float b = y1 - m * x1;
			for (int x = x1; x <= x2; x = x + 1)
			{
				int y = (int)(m*x + b + 0.5f);
				FastVLine(x, y, width, c);
				FastHLine(x, y, width, c);
			}
		}
	}
	void line(int x1, int y1, int x2, int y2, Color c) {
		this->line(x1, y1, x2, y2, c, 1);
	}

	void circleBorder(int x0, int y0, int diam, Color c, int width) {
		int rad = diam / 2;
		for (int radius = rad; radius > rad - width; radius--) {
			float r2 = radius * radius;
			int center = (int)(radius * 0.707107f + 0.5f);
			for (int x = 0; x <= center; x++) {

				int y = (int)sqrt((r2 - x * x));
				for (int i = 0; i < 2; y++, i++) {
					DrawPixel(x0 + x, y0 + y, c);
					DrawPixel(x0 + x, y0 - y, c);
					DrawPixel(x0 + y, y0 + x, c);
					DrawPixel(x0 + y, y0 - x, c);

					DrawPixel(x0 - x, y0 + y, c);
					DrawPixel(x0 - x, y0 - y, c);
					DrawPixel(x0 - y, y0 + x, c);
					DrawPixel(x0 - y, y0 - x, c);
				}

			}
		}
	}
	void circle(int x, int y, int diam, Color c) {
		for (int i = 1; i <= diam; i++) {
			circleBorder(x, y, i, c, diam);
		}
		
	}

	void rectangleBorder(int x0, int y0, int width, int height, Color c, int r) {
		for (int i = 0; i < r; i++) {
			int OF = i;
			FastHLine(x0, y0 + OF, width, c);
			FastHLine(x0, y0 + height - OF, width, c);
			FastVLine(x0 + OF, y0, height, c);
			FastVLine(x0 + width - OF, y0, height, c);
		}
	}
	void rectangle(int xoff, int yoff, int width, int height, Color c) {
		for (int i = 0; i < height; i++) {
			this->FastHLine(xoff, yoff + i, width, c);
		}
	}

	void ellipseBorder(int xoff, int yoff, int width, int height, Color c, int r) {
		for (int i = 0; i < r; i++) {
			int delta = i;
			int xoff = xoff + delta;
			int yoff = yoff + delta;

			int size = width * width;
			int hsquared = height * height;
			int fa2 = 4 * size, fb2 = 4 * hsquared;
			int x, y, th;

			y = height;
			th = 2 * hsquared + size * (1 - 2 * height);


			for (x = 0; hsquared*x <= size * y; x++)
			{
				DrawPixel(xoff + x, yoff + y, c);
				DrawPixel(xoff - x, yoff + y, c);
				DrawPixel(xoff + x, yoff - y, c);
				DrawPixel(xoff - x, yoff - y, c);
				if (th >= 0)
				{
					th += fa2 * (1 - y);
					y--;
				}
				th += hsquared * ((4 * x) + 6);
			}

			y = 0;
			th = 2 * size + hsquared * (1 - 2 * width);
			for (x = width; size*y <= hsquared * x; y++)
			{
				DrawPixel(xoff + x, yoff + y, c);
				DrawPixel(xoff - x, yoff + y, c);
				DrawPixel(xoff + x, yoff - y, c);
				DrawPixel(xoff - x, yoff - y, c);
				if (th >= 0)
				{
					th += fb2 * (1 - x);
					x--;
				}
				th += size * ((4 * y) + 6);
			}
		}
	}
	void ellipse(int xoff, int yoff, int width, int height, Color c) {
		for (int y = -height; y <= height; y++) {
			for (int x = -width; x <= width; x++) {
				double dx = (double)x / (double)width;
				double dy = (double)y / (double)height;
				if (dx*dx + dy * dy <= 1)
					DrawPixel(xoff + x, yoff + y, c);
			}
		}
	}


};




class Drawer: protected Painter {

public:
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
	/*void DrawSprite(PixelMap* VBmp, int fx, int fy) {
	for (std::vector<FPixel*>::iterator it = VBmp->pixels->begin(); it != VBmp->pixels->end(); ++it) {
	DrawPixel(fx + (*it)->x, fy + (*it)->y, (*it)->color);
	}
	}*/
	
	void Fill(Color color) {
		rectangle(0, 0, SCREENWIDTH - 1, SCREENHEIGHT - 1, color);
	}
};

class GFXDraw: public Drawer {
public:
	D3DGraphics * gfx;
	GFXDraw(D3DGraphics* gfx): gfx(gfx) {}

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

class BMPDraw : public Drawer {
public:
	Bitmap* bmp;
	BMPDraw(Bitmap* bmp) : bmp(bmp) {}

	void DrawPixel(int xoff, int yoff, Color c) {
		Color * dst = bmp->GetPixelPointer(xoff, yoff);
		if (dst != nullptr) {
			*dst = c;
		}
	}
};


