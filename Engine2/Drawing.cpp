
#include "Drawing.h"

void Painter::FastHLine(int x0, int y0, int width, Color c) {
	if (width < 0) {
		x0 += width;
		width = -width;
	}
	for (int i = 0; i < width; i++) {
		DrawPixel(x0 + i, y0, c);
	}
}
void Painter::FastVLine(int x0, int y0, int height, Color c) {
	if (height < 0) {
		y0 += height;
		height = -height;
	}
	for (int i = 0; i < height; i++) {
		DrawPixel(x0, y0 + i, c);
	}
}

void Painter::DrawPixel(int xoff, int yoff, Color c)
{
	this->pxd.DrawPixel(xoff, yoff, c);
}

void Painter::ellipse(int ox, int oy, int width, int height, Color c)
{

	for(int y=-height; y<=height; y++) {
    for(int x=-width; x<=width; x++) {
        double dx = (double)x / (double)width;
        double dy = (double)y / (double)height;
        if(dx*dx+dy*dy <= 1)
            DrawPixel(ox+x, oy+y,c);
    }
}

}


void Painter::ellipseBorder(int x, int y, int owidth, int oheight, Color c, int r)
{


	for (int i = 0; i < r; i++) {
		int delta = i;
		int xoff = x + delta;
		int yoff = y + delta;

		int width = owidth;
		int height = oheight;

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


void Painter::DrawPixel(int xoff, int yoff, Color c, int m)
{
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

void Painter::circleBorder(int x0, int y0, int diam, Color c,int width)
{
	int rad = diam / 2;
	for (int radius = rad; radius > rad - width; radius--) {
		float r2 = radius * radius;
		int center = (int)(radius * 0.707107f + 0.5f);
		for (int x = 0; x <= center; x++){

			int y = (int)sqrt((r2 - x * x));
			for (int i = 0; i < 2; y++,i++) {
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
void Painter::circle(int x, int y, int diam, Color c)
{
	circleBorder(x, y, diam, c, diam);
}

void Painter::line(int x1, int y1, int x2, int y2, Color c)
{
	this->line(x1, y1, x2, y2, c, 1);


}

void Painter::line(int x1, int y1, int x2, int y2, Color c, int width)
{
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

void Painter::rectangleBorder(int x0, int y0, int width, int height, Color c, int r) {


	for (int i = 0; i < r; i++) {
		int OF = i;
		FastHLine(x0, y0 + OF, width, c);
		FastHLine(x0, y0 + height - OF, width, c);
		FastVLine(x0 + OF, y0, height, c);
		FastVLine(x0 + width - OF, y0, height, c);
	}
	
}

void Painter::rectangle(int xoff, int yoff, int width, int height, Color c)
{
	for (int i = 0; i < height; i++) {
		this->FastHLine(xoff, yoff + i, width, c);
	}

}

void PixelDest::DrawPixel(int xoff, int yoff, Color c)
{
	if (gfx) {
		if (1) {
			if (xoff >= SCREENWIDTH ||
				yoff >= SCREENHEIGHT ||
				xoff < 0 ||
				yoff < 0) {
				return;
			}
		}

		this->gfx->PutPixel(xoff, yoff, c);
	}

	else if (bmp) {
		Color * dst = bmp->GetPixelPointer(xoff, yoff);
		if (dst != nullptr) {
			*dst = c;
		}
	}
}

void PixelDest::DrawPixel(int xoff, int yoff, Color c, int m)
{
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
