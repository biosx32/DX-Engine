
#include "Drawing.h"

void Painter::FastHLine(int x0, int y0, int width, Color c) {
	for (int i = 0; i < width; i++) {
		DrawPixel(x0 + i, y0, c);
	}
}
void Painter::FastVLine(int x0, int y0, int height, Color c) {
	for (int i = 0; i < height; i++) {
		DrawPixel(x0, y0 + i, c);
	}
}

void Painter::DrawPixel(int xoff, int yoff, Color c)
{
	#define SOFT_DRAW 1

	if (SOFT_DRAW) {
		if (xoff >= SCREENWIDTH ||
			yoff >= SCREENHEIGHT ||
			xoff < 0 ||
			yoff < 0) {
			return;
		}
	}

	this->gfx->PutPixel(xoff, yoff, c);
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

void Painter::circle(int x0, int y0, int radius, Color c)
{
	int rSquared = radius * radius;
	int xPivot = (int)(radius * 0.707107f + 0.5f);
	for (int x = 0; x <= xPivot; x++)
	{
		int y = (int)(sqrt((float)(rSquared - x * x)) + 0.5f);
		DrawPixel(x0 + x, y0 + y, c);
		DrawPixel(x0 - x, y0 + y, c);
		DrawPixel(x0 + x, y0 - y, c);
		DrawPixel(x0 - x, y0 - y, c);
		DrawPixel(x0 + y, y0 + x, c);
		DrawPixel(x0 - y, y0 + x, c);
		DrawPixel(x0 + y, y0 - x, c);
		DrawPixel(x0 - y, y0 - x, c);
	}
}
void Painter::circle(int x, int y, int rad, Color c, bool fill)
{
	if (!fill) return circle(x, y, rad, c);
	for (int r = 1; r < rad; r++) {
		circle(x, y, r, c);
		circle(x + 1, y, r, c);
	}
}

void Painter::line(int x1, int y1, int x2, int y2, Color c)
{

	int dx = x2 - x1;
	int dy = y2 - y1;

	if (dy == 0 && dx == 0)
	{
		DrawPixel(x1, y1, c);
	}

	else if (abs(dy) > abs(dx))
	{
		if (dy < 0)
		{
			int temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		float m = (float)dx / (float)dy;
		float b = x1 - m * y1;
		for (int y = y1; y <= y2; y = y + 1)
		{
			int x = (int)(m*y + b + 0.5f);
			DrawPixel(x, y, c);
		}
	}
	else
	{
		if (dx < 0)
		{
			int temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		float m = (float)dy / (float)dx;
		float b = y1 - m * x1;
		for (int x = x1; x <= x2; x = x + 1)
		{
			int y = (int)(m*x + b + 0.5f);
			DrawPixel(x, y, c);
		}
	}
}

void Painter::line(int x1, int y1, int x2, int y2, Color c, int width)
{
	width = 2;
	for (int i = 0; i < width; i++) {
		int delta = -width / 2 + i;
		line(x1, y1+delta, x2, y2 + delta, c);
		line(x1+delta, y1, x2+delta, y2, c);
	}
}

void Painter::rectangle(int x0, int y0, int width, int height, Color c ) {
	FastHLine(x0, y0, width, c);
	FastHLine(x0, y0 + height, width, c);

	FastVLine(x0, y0, height,c);
	FastVLine(x0 + width, y0, height,c);


}

void Painter::rectangle(int xoff, int yoff, int width, int height, Color c, bool fill)
{
	if (!fill) return rectangle(xoff, yoff, width, height, c);
	for (int i = 0; i < height; i++) {
		this->FastHLine(xoff, yoff + i, width, c);
	}

}


