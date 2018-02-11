#include "BitmapArray.h"

BitmapArray::BitmapArray(Bitmap * sourceImage, int wcount, int hcount, float m_size) :
	wcount(wcount), hcount(hcount)
{

	int src_wsize = sourceImage->width / wcount;
	int src_hsize = sourceImage->height / hcount;
	this->wsize = src_wsize * m_size;
	this->hsize = src_hsize * m_size;

	this->sprites = new Bitmap*[this->count()];

	for (int y = 0; y < hcount; y++) {
		for (int x = 0; x < wcount; x++) {
			int srcX = x * src_wsize;
			int srcY = y * src_hsize;
			Bitmap* newBitmap = sourceImage->GetBitmapPart(srcX, srcY, src_wsize, src_hsize, m_size);

			*this->GetAddrOfBitmapPointer(x, y) = newBitmap;
		}
	}
}

BitmapArray::~BitmapArray()
{
	for (int i = 0; i < this->count(); i++) {
		delete this->sprites[i];
	}
}
