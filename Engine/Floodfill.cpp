#include "Floodfill.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>  

void PixelContainer::Draw(Interface * out, int fx, int fy)
{
	int color_background = Color(0,0,0).dword; //black
	int color_checked = Color(51, 204, 51).dword; //green
	int color_stalled = Color(102, 102, 153).dword; //gray

	FFPixel* ReadPixel;
	for (int yoff = 0; yoff < height; yoff++) {
		for (int xoff = 0; xoff < width; xoff++) {

			ReadPixel = pixels[yoff* width + xoff];
	
			if (ReadPixel->state & pxstate::checked) {
				if ((ReadPixel->group % 3) ==0) {
					out->DrawPixel(xoff + fx, yoff + fy, 0xFF0000);
				}
				else if ((ReadPixel->group %  3) ==1) {
					out->DrawPixel(xoff + fx, yoff + fy, 0xFF00);
				}
				else if ((ReadPixel->group %3) == 2) {
					out->DrawPixel(xoff + fx, yoff + fy, 0xFF);
				}

				else {
					out->DrawPixel(xoff + fx, yoff + fy, color_checked);
				}
			}
			else if (ReadPixel->state & pxstate::background) {
				out->DrawPixel(xoff + fx, yoff + fy, color_background);
			}
			else {
				out->DrawPixel(xoff + fx, yoff + fy, ReadPixel->color);
			}

		}
	
	}

}

FFPixel * PixelContainer::getFirstRawPixel()
{

	for (int i = lastpos; i < pixelcount; i++) {
		if (! (pixels[i]->state & pxstate::checked || 
			   pixels[i]->state & pxstate::background)) {
			lastpos = i;
			return pixels[i];
			
		}
	}

	return nullptr;
}



bool PixelContainer::IsColorBackground(Color c)
{

	return c.dword == transparency.dword;
}

FFPixel* PixelContainer::GetStalled() {
	FFPixel* result = nullptr;
	if (this->GetPendingPixelsCount() > 0) {
		result = stalledPixels.back();
		stalledPixels.pop_back();
	}
	
	return result;
}


unsigned int PixelContainer::GetPendingPixelsCount()
{
	return (unsigned int) stalledPixels.size();
}

bool PixelContainer::HasPendingPixels()
{
	return this->GetPendingPixelsCount() > 0;
}

void PixelContainer::IteratePendingPixels() {	
	while (this->HasPendingPixels()) {
		this->CheckPixel(this->GetStalled());
	}
}

FFPixel * PixelContainer::getPixelAt(int x, int y)
{
	if (x >= 0 && 
		y >= 0 &&
		  x < width && 
	      y < height) {
		return this->pixels[y*width + x];
	}

	return nullptr;
}

TransparentBitmap ** PixelContainer::GetGroup()
{
	TransparentBitmap** spritegroups = new TransparentBitmap*[groups];

	for (int i = 0; i < pixelcount;i++) {
		
	}
}

void PixelContainer::CheckPixel(FFPixel* pixel) {
	
	if (pixel->state & pxstate::skip) {
		return;
	}

	pixel->state |= pxstate::checked;

	FFPixel* neighbors[4] = {
		getPixelAt(pixel->x - 1, pixel->y),
		getPixelAt(pixel->x + 1, pixel->y),
		getPixelAt(pixel->x, pixel->y - 1),
		getPixelAt(pixel->x, pixel->y + 1)
	};

	for (int i = 0; i < 4; i++) {
		if (neighbors[i]) {
			if (!(neighbors[i]->state & pxstate::skip)) {
				neighbors[i]->group = pixel->group;
				this->AddToPending(neighbors[i]);
				
			}
		}
	}

}


void PixelContainer::AddToPending(FFPixel* pixel) {
	stalledPixels.push_back(pixel);
}


void PixelContainer::Load(Bitmap * bmp)
{
	this->width = bmp->datagroup->width;
	this->height = bmp->datagroup->height;
	this->pixelcount = bmp->datagroup->pixelcount;
	this->pixels = new FFPixel*[pixelcount];


	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width; x++) {
			int i = y*width + x;
			Color c = bmp->datagroup->data[i];
			int state = 0;

			if (IsColorBackground(c)) {
				state |= pxstate::background;
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
	this->group = -1;
	this->state = state;
}
