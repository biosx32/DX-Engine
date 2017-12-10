
#include "Drawing.h"

void Draw::FastVLine(int x0, int y0, int width) {
	for (int i = 0; i < width; i++) {
		this->out->DrawPixel(x0 + i, y0, brush);
	}
}
void Draw::FastHLine(int x0, int y0, int height) {
	for (int i = 0; i < height; i++) {
		this->out->DrawPixel(x0, y0 + i, brush);
	}
}

void Draw::circle(int x0, int y0, int radius)
{
	int x = radius - 1;
	int y = 0; int dx = 1; int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y)
	{
		this->out->DrawPixel(x0 + x, y0 + y, brush);
		this->out->DrawPixel(x0 + y, y0 + x, brush);
		this->out->DrawPixel(x0 - y, y0 + x, brush);
		this->out->DrawPixel(x0 - x, y0 + y, brush);
		this->out->DrawPixel(x0 - x, y0 - y, brush);
		this->out->DrawPixel(x0 - y, y0 - x, brush);
		this->out->DrawPixel(x0 + y, y0 - x, brush);
		this->out->DrawPixel(x0 + x, y0 - y, brush);

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
void Draw::line(int x0, int y0, int width, int height)
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

	if (dy == 0) return FastVLine(x0, y0, width);
	if (dx == 0) return FastHLine(x0, y0, height);

	x = x0;
	y = y0;
	p = 2 * dy - dx;

	while (x<x1) {
		if (p >= 0) {
			this->out->DrawPixel(x, y, brush);
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		else {
			this->out->DrawPixel(x, y, brush);
			p = p + 2 * dy;
		}
		x = x + 1;
	}
}

void Draw::rectangle(int x0, int y0, int width, int height) {
	int w2 = width / 2; int h2 = height / 2;
	line(x0 - w2, y0 - h2, 0, height);
	line(x0 + w2, y0 - h2, 0, height);

	line(x0 - w2, y0 - h2, width, 0);
	line(x0 - w2, y0 + h2, width, 0);

}

void Draw::Draw::setOutInterface(Interface* out)
{
	this->out = out;
}

void Draw::SetBrushColor(Color color)
{
	this->brush = color;
}
