#include "Spritesheet.h"




VectorSpriteSheet::VectorSpriteSheet(Bitmap * BitmapImage)
{
	PixelContainer* temp = new PixelContainer(BitmapImage);
	while (1) {
		MySprite* naw = temp->GetNextSpriteGroup();
		if (naw == nullptr) {
			break;
		}
		else {
			this->sprites.push_back(naw);
		}
	}

}


VectorSpriteSheet::~VectorSpriteSheet() {
	for (std::vector<MySprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
	{
		delete *it;
	}
}



FFPixel * PixelContainer::GetNextSpritePixel()
{
	FFPixel* point = nullptr;

	while (1) {
		point = this->getPixelAt(lastpos.x, lastpos.y);

		if(point) {
			if (!(point->state & pxstate::skip)) {
				return point;
			}
		}

		if (lastpos.y > height) {
			return nullptr;
		}
		
		lastpos.x += gridsize;

		if (!point) {
			lastpos.x = 0;
			lastpos.y += gridsize;
		}

	}
	


		

	
	return nullptr;
}



MySprite* PixelContainer::GetGroupFrom(FFPixel* pixel) {
	if (!pixel) return nullptr;
	this->result_group = new vector<FPixel*>;

	stalledPixels.push_back(pixel);

	while (stalledPixels.size() > 0) {
		FFPixel* px = stalledPixels.back();
		stalledPixels.pop_back();
		this->CheckPixel(px);
	}
	MySprite* result;

	if (result_group->size() > 0) {
		result = new MySprite(result_group);
		delete result_group;
		return result;
	}
	
	return nullptr;
}

MySprite* PixelContainer::GetNextSpriteGroup()
{
	return GetGroupFrom(GetNextSpritePixel());
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





void PixelContainer::CheckPixel(FFPixel* pixel) {
	if (pixel->state & pxstate::skip) {
		return;
	}

	pixel->state |= pxstate::checked;

	const int neighborcount = 4;
	FFPixel* neighbors[neighborcount] = {
		getPixelAt(pixel->x - 1, pixel->y),
		getPixelAt(pixel->x + 1, pixel->y),
		getPixelAt(pixel->x, pixel->y - 1),
		getPixelAt(pixel->x, pixel->y + 1)
	};

	for (int i = 0; i < neighborcount; i++) {
		if (!neighbors[i]) { continue; }

		if (!(neighbors[i]->state & pxstate::skip)) {
			stalledPixels.push_back(neighbors[i]);
		}
	}

	FPixel* this_conv = new FPixel(*pixel);
	this->result_group->push_back(this_conv);


}


PixelContainer::~PixelContainer()
{
	for (int i = 0; i < pixelcount(); i++) {
		delete this->pixels[i];
	}

}

PixelContainer::PixelContainer(Bitmap * bmp)
{
	this->width = bmp->width;
	this->height = bmp->height;
	this->pixels = new FFPixel*[pixelcount()];
	this->lastpos = Vector2(gridsize, gridsize);

	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width; x++) {
			int i = y * width + x;
			Color color = bmp->data[i];

			int state = 0;
			if (bmp->GetIsBackground(color)) {
				state |= pxstate::background;
			}

			pixels[i] = new FFPixel(x, y, color, state);

		}
	}
}



FixedSpriteArray::FixedSpriteArray(Bitmap * sourceImage, int wcount, int hcount, float m_size):
	wcount(wcount),hcount(hcount)
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

FixedSpriteArray::~FixedSpriteArray()
{
	for (int i = 0; i < this->count(); i++) {
		delete this->sprites[i];
	}
}
