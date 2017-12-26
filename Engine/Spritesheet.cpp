#include "Spritesheet.h"




SpritesheetVec::SpritesheetVec(TransparentBitmap * BitmapImage)
{
	PixelContainer* temp = new PixelContainer(BitmapImage);
	while (1) {
		VectorBitmap* naw = temp->GetNextSpriteGroup();
		if (naw == nullptr) {
			break;
		}
		else {
			this->sprites.push_back(naw);
		}
	}

}

SpritesheetVec::SpritesheetVec(TransparentBitmap * BitmapImage, int wcount, int hcount)

{	
	float wsize = BitmapImage->width / float(wcount);
	float hsize = BitmapImage->height / float(hcount);

	for (int hi = 0; hi < hcount; hi++) {
		for (int wi = 0; wi < wcount; wi++) {
			int x = (int)(wi * wsize);
			int y =(int)( hi * hsize);
			TransparentBitmap* cutsprite = BitmapImage->GetBitmapPart(x, y, (int)wsize, (int)hsize);
			VectorBitmap* vbmp = new VectorBitmap(cutsprite);
			this->sprites.push_back(vbmp);
		}
	}

	
}

SpritesheetVec::~SpritesheetVec() {
	for (std::vector<VectorBitmap*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
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



VectorBitmap* PixelContainer::GetGroupFrom(FFPixel* pixel) {
	if (!pixel) return nullptr;
	this->result_group = new vector<FPixel*>;

	stalledPixels.push_back(pixel);

	while (stalledPixels.size() > 0) {
		FFPixel* px = stalledPixels.back();
		stalledPixels.pop_back();
		this->CheckPixel(px);
	}
	VectorBitmap* result;

	if (result_group->size() > 0) {
		result = new VectorBitmap(result_group);
		delete result_group;
		return result;
	}
	
	return nullptr;
}

VectorBitmap* PixelContainer::GetNextSpriteGroup()
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

PixelContainer::PixelContainer(TransparentBitmap * bmp)
{
	this->width = bmp->width;
	this->height = bmp->height;
	this->pixels = new FFPixel*[pixelcount()];
	this->lastpos = Vector2(gridsize, gridsize);

	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width; x++) {
			int i = y * width + x;
			Color color = *bmp->data[i];

			int state = 0;
			if (bmp->IsColorTransparent(color)) {
				state |= pxstate::background;
			}

			pixels[i] = new FFPixel(x, y, color, state);

		}
	}
}

Spritesheet::Spritesheet(TransparentBitmap * BitmapImage, int wcount, int hcount)
{
	float wsize = BitmapImage->width / float(wcount);
	float hsize = BitmapImage->height / float(hcount);

	this->sprites = new TransparentBitmap*[wcount*hcount];
	for (int hi = 0; hi < hcount; hi++) {
		for (int wi = 0; wi < wcount; wi++) {
			int x = (int)(wi * wsize);
			int y = (int)(hi * hsize);
			TransparentBitmap* cutsprite = BitmapImage->GetBitmapPart(x, y, (int)wsize, (int)hsize);
			this->sprites[hcount * hi + wi] = cutsprite;
		}
	}
}

Spritesheet::~Spritesheet()
{
	for (int i = 0; i < this->count; i++) {
		delete this->sprites[i];
	}
}
