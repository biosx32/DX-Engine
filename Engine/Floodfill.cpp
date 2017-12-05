#include "Floodfill.h"

void PixelContainer::Draw(Interface * out, int fx, int fy)
{
	FFPixel* ReadPixel;
	for (int yoff = 0; yoff < height; yoff++) {
		for (int xoff = 0; xoff < width; xoff++) {

			ReadPixel = pixels[yoff* width + xoff];

			if (this->IsPixelBackground(ReadPixel)) {
				out->DrawPixel(xoff + fx, yoff + fy, Color(122, 255, 111));
				
			}
			else if (ReadPixel->checked) {
				out->DrawPixel(xoff + fx, yoff + fy, Color(255, 255, 111));
			}
			else {
				out->DrawPixel(xoff + fx, yoff + fy, ReadPixel->color);
			}

		}
	}
}

FFPixel * PixelContainer::getFirstPixel()
{
	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width; x++) {
		FFPixel* ptr = pixels[y*width + x];

		if (!this->IsPixelBackground(ptr) && !ptr->checked) {
			return ptr;
		}
	}
	}
	return nullptr;
}

bool PixelContainer::IsPixelBackground(FFPixel* ptr)
{
	return ptr->color.dword == this->transparency.dword;
}

void PixelContainer::CheckNeighbors(FFPixel * pixel)
{
	int nx, ny;
	
	FFPixel* neighbor;

	pixel->checked = true;
	pixel->group = GroupIter;

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {


			ny = y - 1 + pixel->y;
			nx = x - 1 + pixel->x;

			if (nx < 0 || nx >= width || ny<0 || ny>= height) {
				continue;

			}

			
			neighbor = this->pixels[ny * width + nx];

			if (neighbor == nullptr) {
				DebugBreak();
			}
			if (neighbor == pixel) {
				continue;
			}

			if (!neighbor->checked && !this->IsPixelBackground(neighbor)) {
				this->CheckNeighbors(neighbor);
			}


		}
	}



}



void PixelContainer::Load(Bitmap * bmp)
{
	this->width = bmp->BitmapData->width;
	this->height = bmp->BitmapData->height;
	this->pixelcount = width*height;
	this->pixels = new FFPixel *[pixelcount];

	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width; x++) {
			int i = y*width + x;
			Color c = bmp->BitmapData->ptr[i];
			pixels[i] = new FFPixel(x, y, c);

		}
	}

}

FFPixel::FFPixel(int x, int y, Color c)
{
	this->x = x;
	this->y = y;
	this->color = c;
}
