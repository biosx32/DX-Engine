#include "TestInterface.h"

void TestInterface::DrawPixelContainer(PixelContainer* src, int fx, int fy)
{
	FFPixel* ReadPixel;
	for (int yoff = 0; yoff < src->height; yoff++) {
		for (int xoff = 0; xoff < src->width; xoff++) {

			ReadPixel = src->pixels[yoff* src->width + xoff];

			if (ReadPixel->state & pxstate::checked) {
				paint->DrawPixel(xoff + fx, yoff + fy, 0xAC0000);
			}

			else if (ReadPixel->state & pxstate::background) {
				paint->DrawPixel(xoff + fx, yoff + fy, ColorARGB(255,177, 244, 177));
			}

			else {
				paint->DrawPixel(xoff + fx, yoff + fy, ReadPixel->color);
			}

		}

	}

}



void TestInterface::DrawSpritesheet(FixedSpriteArray * sh, int xoff, int yoff)
{
	int sprw = sh->sprites[0]->width;
	int sprh = sh->sprites[0]->height;


	for (int y = 0; y < sh->hcount; y++) {
		for (int x = 0; x < sh->wcount; x++) {
			int i = y * sh->wcount + x;
			int xdst = x* sprw + 1 * x ;
			int ydst = y* sprh + 1 * y;


	this->DrawBitmap(sh->sprites[i], xoff+ xdst, yoff+ ydst);
	paint->FastVLine(xoff + xdst, yoff + ydst, sprh+1,0xFFFFFF);
	paint->FastHLine(xoff + xdst, yoff + ydst, sprw+1,0xFFFFFF);
	}
	}


}

void TestInterface::DrawLabel(Label * label)
{
	this->PrintText(label->x, label->y, label->font, label->text);
}






TrianglePoly::TrianglePoly(Vector2 vs1, Vector2 vs2, Vector2 vs3)
{
	v1 = new Vector2(vs1);
	v2 = new Vector2(vs2);
	v3 = new Vector2(vs3);

	float xr = maximum(v1->x, v2->x, v3->x)/2 + minimum(v1->x, v2->x, v3->x) /2;
	float yr = maximum(v1->y, v2->y, v3->y) / 2 + minimum(v1->y, v2->y, v3->y) / 2;
	origin = new Vector2(xr, yr);
}

void TrianglePoly::Draw(Interface * out)
{
	

	out->paint->line(v1->x, v1->y, v2->x, v2->y, Colors::Black,6);
	out->paint->line(v1->x, v1->y, v3->x, v3->y, Colors::Black, 6);
	out->paint->line(v3->x, v3->y, v2->x, v2->y, Colors::Black, 6);


	this->DrawVertex(v1, out, Colors::DarkGreen);
	this->DrawVertex(v2, out, Colors::DarkGreen);
	this->DrawVertex(v3, out, Colors::DarkGreen);
	this->DrawVertex(origin, out, Colors::Red);

}




void Grid::Draw(Interface * out)
{
	for (int r = 1; r < 5; r++) {
		out->paint->circle(x + mid * size, y + mid * size, r, Colors::Black);
		out->paint->circle(x + mid * size + 1, y + mid * size, r, Colors::Black);



	}
	for (int ty = 0; ty < wc; ty++) {
		for (int tx = 0; tx < wc; tx++) {
			out->paint->rectangle(x + tx * size, y + ty * size, size, size, Colors::Black);

		}
	}

}

