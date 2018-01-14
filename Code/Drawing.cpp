
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
	int rSquared = radius * radius;
	int xPivot = (int)(radius * 0.707107f + 0.5f);
	for (int x = 0; x <= xPivot; x++)
	{
		int y = (int)(sqrt((float)(rSquared - x * x)) + 0.5f);
		out->DrawPixel(x0 + x, y0 + y, c);
		out->DrawPixel(x0 - x, y0 + y, c);
		out->DrawPixel(x0 + x, y0 - y, c);
		out->DrawPixel(x0 - x, y0 - y, c);
		out->DrawPixel(x0 + y, y0 + x, c);
		out->DrawPixel(x0 - y, y0 + x, c);
		out->DrawPixel(x0 + y, y0 - x, c);
		out->DrawPixel(x0 - y, y0 - x, c);
	}
}
void Draw::line(int x1, int y1, int x2, int y2, Color c)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	if (dy == 0 && dx == 0)
	{
		out->DrawPixel(x1, y1, c);
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
			out->DrawPixel(x, y, c);
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
			out->DrawPixel(x, y, c);
		}
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

