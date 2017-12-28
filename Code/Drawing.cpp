
#include "Drawing.h"

void Draw::FastHLine(int x0, int y0, int width, Color c) {
	for (int i = 0; i < width; i++) {
		out->DrawPixel(x0 + i, y0, c);
	}
}
void Draw::FastVLine(int x0, int y0, int height, Color c) {
	for (int i = 0; i < height; i++) {
		out->DrawPixel(x0, y0 + i, c);
	}
}

void Draw::circle(int x0, int y0, int radius, Color c)
{
	int x = radius - 1;
	int y = 0; int dx = 1; int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y)
	{
		out->DrawPixel(x0 + x, y0 + y, c);
		out->DrawPixel(x0 + y, y0 + x, c);
		out->DrawPixel(x0 - y, y0 + x, c);
		out->DrawPixel(x0 - x, y0 + y, c);
		out->DrawPixel(x0 - x, y0 - y, c);
		out->DrawPixel(x0 - y, y0 - x, c);
		out->DrawPixel(x0 + y, y0 - x, c);
		out->DrawPixel(x0 + x, y0 - y, c);

		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}
		if (err > 0)
		{
			x--;
			dx += 2;
			err += (-radius << 1) + dx;
		}
	}
}
void Draw::line(int x0, int y0, int width, int height, Color c)
{
	int dx, dy, p, x, y, t, y1, x1;

	x1 = t = x0 + width;

	if (x1 < x0) {
		x1 = x0;
		x0 = t;
	}
	y1 = t = y0 + height;

	if (y1 < y0) {
		y1 = y0;
		y0 = t;
	}


	dx = x1 - x0;
	dy = y1 - y0;

	if (dy == 0) return FastHLine(x0, y0, width, c);
	if (dx == 0) return FastVLine(x0, y0, height, c);

	x = x0;
	y = y0;
	p = 2 * dy - dx;

	while (x<x1) {
		if (p >= 0) {
			this->out->DrawPixel(x, y, c);
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		else {
			this->out->DrawPixel(x, y, c);
			p = p + 2 * dy;
		}
		x = x + 1;
	}
}

void Draw::rectangle(int x0, int y0, int width, int height, Color c ) {
	line(x0, y0, 0, height, c);
	line(x0 + width, y0, 0, height, c);

	line(x0, y0, width, 0, c);
	line(x0, y0 + height, width, 0,c);

}

void Draw::rectangle_fill(int xoff, int yoff, int width, int height, Color c)
{
	for (int i = 0; i < height; i++) {
		this->FastHLine(xoff, yoff + i, width, c);
	}

}

void Draw::Draw::setOutInterface(Interface* out)
{
	this->out = out;
}

