#include "Floodfill.h"

void PixelContainer::Draw(Interface * out, int fx, int fy)
{
	FFPixel* ReadPixel;
	for (int yoff = 0; yoff < height; yoff++) {
		for (int xoff = 0; xoff < width; xoff++) {

			ReadPixel = pixels[yoff* width + xoff];

			if (ReadPixel->state == PixelState::background) {
				out->DrawPixel(xoff + fx, yoff + fy, Color(122, 255, 111));
				
			}
			else if (ReadPixel->state == PixelState::checked) {
				out->DrawPixel(xoff + fx, yoff + fy, Color(255, 0, 0));
			}
			else if (ReadPixel->state == PixelState::pending) {
				out->DrawPixel(xoff + fx, yoff + fy, Color(0, 255, 255));
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

			if (ptr->state == PixelState::raw) {
				return ptr;
			}

		}
	}

	return nullptr;
}

FFPixel * PixelContainer::getPixelAt(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return this->pixels[y*width + x];
	}

	return nullptr;
}




bool PixelContainer::IsColorBackground(Color c)
{
	return c.dword == transparency.dword;
}

void PixelContainer::StartVirus(FFPixel* pixel) {
	CheckPixel(pixel);

	while (true) {
		FFPixel* next = GetPending();
		if (next == nullptr) {
			break;
		}

		CheckPixel(pixel);
	}

}


FFPixel* PixelContainer::GetPending() {
	for (int i = 0; i < pixelcount; i++) {
		if (pixels[i]->state == PixelState::pending) {
			return pixels[i];
		}
	}
	return nullptr;
}

void PixelContainer::CheckPixel(FFPixel * pixel)
{

	if (pixel->state == PixelState::background || pixel->state == PixelState::checked) {
		return;
	}

	pixel->state = PixelState::checked;
	

	int px = pixel->x;
	int py = pixel->y;

	FFPixel* arr[4] = { getPixelAt(px - 1, py),
		getPixelAt(px + 1, py),
		getPixelAt(px, py - 1),
	nullptr//	getPixelAt(px, py + 1),

	};

	for (int i = 0; i < 4; i++) {
		FFPixel* neighbor = arr[i];

		if (neighbor ==nullptr) {
			continue;
		}
		
		if (neighbor->state == PixelState::raw) {
			neighbor->state = PixelState::pending;
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
			int state = PixelState::raw;

			if (IsColorBackground(c)) {
				state = PixelState::background;
			}
			
			pixels[i] = new FFPixel(x, y, c, state);

		}
	}

}

FFPixel::FFPixel(int x, int y, Color c, int state)
{
	this->x = x;
	this->y = y;
	this->color = c;
	this->state = state;
}
