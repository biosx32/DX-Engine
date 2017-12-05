#include "Floodfill.h"
FFPixel::FFPixel()
{

}

bool FFPixel::IsBackgroundColor()
{
	return this->color.dword == this->backgroundcolor.dword;
}

void PixelContainer::Draw(Interface * out, int fx, int fy)
{
	FFPixel ReadPixel;
	for (int yoff = 0; yoff < height; yoff++) {
		for (int xoff = 0; xoff < width; xoff++) {

			ReadPixel = pixels[yoff* width + xoff];

			if (ReadPixel.IsBackgroundColor() == false) {
				out->DrawPixel(xoff + fx, yoff + fy, ReadPixel.color);
			}
			else {
				out->DrawPixel(xoff + fx, yoff + fy, Color(122, 255, 111));
			}

		}
	}
}

void PixelContainer::Load(TransparentBitmap * bmp)
{
	this->width = bmp->BitmapData->width;
	this->height = bmp->BitmapData->height;
	this->transparency = bmp->transparency;

	this->pixelcount = width*height;

	this->pixels = new FFPixel[pixelcount];
	for (int i = 0; i < pixelcount; i++) {
		pixels[i].color = bmp->BitmapData->ptr[i];
		if (pixels[i].color.dword == transparency.dword) {
			pixels[i].backgroundcolor = this->transparency;
		}
	}
}