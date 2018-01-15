#include "TestInterface.h"

void TestInterface::DrawPixelContainer(PixelContainer* src, int fx, int fy)
{
	FFPixel* ReadPixel;
	for (int yoff = 0; yoff < src->height; yoff++) {
		for (int xoff = 0; xoff < src->width; xoff++) {

			ReadPixel = src->pixels[yoff* src->width + xoff];

			if (ReadPixel->state & pxstate::checked) {
				this->DrawPixel(xoff + fx, yoff + fy, 0xAC0000);
			}

			else if (ReadPixel->state & pxstate::background) {
				this->DrawPixel(xoff + fx, yoff + fy, Colors::MakeARGB(255,177, 244, 177));
			}

			else {
				this->DrawPixel(xoff + fx, yoff + fy, ReadPixel->color);
			}

		}

	}

}



void TestInterface::DrawSpritesheet(SymetricSpriteSheet * sh, int xoff, int yoff)
{
	int sprw = sh->sprites[0]->width;
	int sprh = sh->sprites[0]->height;


	for (int y = 0; y < sh->hcount; y++) {
		for (int x = 0; x < sh->wcount; x++) {
			int i = y * sh->wcount + x;
			int xdst = x* sprw + 1 * x ;
			int ydst = y* sprh + 1 * y;


	this->DrawBitmap(sh->sprites[i], xoff+ xdst, yoff+ ydst);
	this->Painter->FastVLine(xoff + xdst, yoff + ydst, sprh+1,0xFFFFFF);
	this->Painter->FastHLine(xoff + xdst, yoff + ydst, sprw+1,0xFFFFFF);
	}
	}


}

Vertex::Vertex(Grid * par, float x, float y) :parent(par) { 
	c = Colors::Blue; _x = +parent->mid + x; _y = +parent->mid - y; 
}

void Vertex::Draw(Interface * out)
{
	for (int r = 1; r < 5; r++) {
		out->Painter->circle(rx(), ry(), r, c);
		out->Painter->circle(rx() + 1, ry(), r, c);

	}

	char buffer[256];
	sprintf(buffer, "(%2.2f,%2.2f)", x(), y());
	out->PrintText(rx() + 15+25, ry() - DOS_BLACK.sprite_sheet->hsize / 4, buffer, 0.2, &DOS_BLACK);
	out->Painter->line(rx(), ry(), rx()+10, ry()-13, this->c);
	out->Painter->FastHLine(rx() + 10, ry() - 13, 30, this->c);

}

TrianglePoly::TrianglePoly(Grid * parent, float x, float y, float xx, float yy, float xxx, float yyy)
{
	a = new Vertex(parent, x, y);
	b = new Vertex(parent, xx, yy);
	c = new Vertex(parent, xxx, yyy);
	float xr = (x + xx + xxx) / 3;
	float yr = (y + yy + yyy) / 3;
	origin = new Vertex(parent, xr, yr);
	origin->c = Colors::Red;
}

void TrianglePoly::Draw(Interface * out)
{


	for (int i = 0; i < 3; i++) {
		out->Painter->line(a->rx(), a->ry() + i, b->rx(), b->ry() + i, Colors::Green);
		out->Painter->line(a->rx(), a->ry() + i, c->rx(), c->ry() + i, Colors::Green);
		out->Painter->line(c->rx(), c->ry() + i, b->rx(), b->ry() + i, Colors::Green);
	}
	a->Draw(out); b->Draw(out); c->Draw(out);
	origin->Draw(out);



}

void Grid::Draw(Interface * out)
{
	for (int r = 1; r < 5; r++) {
		out->Painter->circle(x + mid * wc, y + mid * wc, r, Colors::Black);
		out->Painter->circle(x + mid * wc + 1, y + mid * wc, r, Colors::Black);



	}
	for (int ty = 0; ty < wc; ty++) {
		for (int tx = 0; tx < wc; tx++) {
			out->Painter->rectangle(x + tx * size, y + ty * size, size, size, Colors::Black);

		}
	}

}
