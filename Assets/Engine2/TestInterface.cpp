#include "TestInterface.h"
#include "TrianglePoly.h"

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








void Grid::Draw(Interface * out)
{
	for (int r = 1; r < 5; r++) {
		out->paint->circle(x + mid * size, y + mid * size, r, Colors::Black);
		out->paint->circle(x + mid * size + 1, y + mid * size, r, Colors::Black);



	}
	for (int ty = 0; ty < wc; ty++) {
		for (int tx = 0; tx < wc; tx++) {
			out->paint->rectangleBorder(x + tx * size, y + ty * size, size, size, Colors::Black,1);

		}
	}

}

