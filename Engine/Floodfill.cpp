#include "Floodfill.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>  

void PixelContainer::Draw(Interface * out, int fx, int fy)
{
	int color_background = Color(0,0,0).dword; //black
	int color_checked = Color(51, 204, 51).dword; //green
	int color_pending = Color(255, 51, 0).dword; //red
	int color_raw = Color(255, 255, 255).dword; //white
	int color_review = Color(102, 102, 153).dword; //gray

	FFPixel* ReadPixel;



	for (int yoff = 0; yoff < height; yoff++) {
		for (int xoff = 0; xoff < width; xoff++) {

			ReadPixel = pixels[yoff* width + xoff];

			if (ReadPixel->state == pixelstate::background) {
				out->DrawPixelM(xoff + fx, yoff + fy, color_background);
			}
			else if (ReadPixel->state == pixelstate::checked) {
				out->DrawPixelM(xoff + fx, yoff + fy, color_checked);
			}
			else if (ReadPixel->state == pixelstate::raw) {
				out->DrawPixelM(xoff + fx, yoff + fy, color_raw);
			}
			else if (ReadPixel->state == pixelstate::stalled) {
				out->DrawPixelM(xoff + fx, yoff + fy, color_review);
			}
			else if (ReadPixel->state == pixelstate::pending) {
				out->DrawPixelM(xoff + fx, yoff + fy, color_pending);
			}
			else {
				out->DrawPixelM(xoff + fx, yoff + fy, ReadPixel->color);
			}

		}
	
	}

}

FFPixel * PixelContainer::getFirstRawPixel()
{
	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width; x++) {
			FFPixel* ptr = pixels[y*width + x];

			if (ptr->state == pixelstate::raw) {
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

FFPixel* PixelContainer::GetStalled() {
	FFPixel* result = nullptr;
	if (stalledPixels.size() > 0) {
		result = stalledPixels.back();
		stalledPixels.pop_back();
	}
	
	return result;
}

void PixelContainer::FillEmptySearchers() {
	for (int i = 0; i < maxp; i++) {
		if (pending[i] == nullptr) {
			pending[i] = GetStalled();
		}

		else if (pending[i]->state != pixelstate::pending) {
			pending[i] = GetStalled();
		}
	}

}
void PixelContainer::StepPending() {

	FillEmptySearchers();

	for (int i = 0; i < maxp; i++) {
		if (pending[i] != nullptr) {

			PendingProcess(pending[i]);
		}
	}
}

void PixelContainer::PendingProcess(FFPixel* pixel) {
	pixel->state = pixelstate::checked;

	int px = pixel->x;
	int py = pixel->y;

	FFPixel* arr[4] = {
		getPixelAt(px - 1, py),
		getPixelAt(px + 1, py),
		getPixelAt(px, py - 1),
		getPixelAt(px, py + 1)
	};

	for (int i = 0; i < 4; i++) {
		if (!arr[i]) continue;


		if (arr[i]->state & (pixelstate::raw)) {
			this->AddToStalled(arr[i]);
		}
		
	}

}


void PixelContainer::AddToStalled(FFPixel* pixel) {
	pixel->state = pixelstate::stalled;
	stalledPixels.push_back(pixel);
}




void PixelContainer::Load(Bitmap * bmp)
{
	this->width = bmp->BitmapData->width;
	this->height = bmp->BitmapData->height;
	this->pixelcount = width*height;
	this->pixels = new FFPixel*[pixelcount];


	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width; x++) {
			int i = y*width + x;
			Color c = bmp->BitmapData->ptr[i];
			int state = 0;

			if (IsColorBackground(c)) {
				state |= pixelstate::background;
				state |= pixelstate::checked;
			}

			else {
				state |= pixelstate::raw;
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
