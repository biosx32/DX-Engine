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
				this->DrawPixel(xoff + fx, yoff + fy, Colors::MakeRGB(177, 244, 177));
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


	for (int y = 0; y < sh->; y++) {
		for (int x = 0; x < sh->datagroup->wcount; x++) {
			int i = y * sh->datagroup->wcount + x;
			int xdst = x* sprw + 1 * x ;
			int ydst = y* sprh + 1 * y;


	this->Draw_Bitmap(sh->datagroup->data[i]->image, xoff+ xdst, yoff+ ydst);
	this->Painter->FastVLine(xoff + xdst, yoff + ydst, sprh+1);
	this->Painter->FastHLine(xoff + xdst, yoff + ydst, sprw+1);
	}
	}

	this->Painter->SetBrushColor(old);*/
}