
#include "FloodfillMap.h"



FFPixel * FloodFillMap::GetNextSpritePixel()
{
	FFPixel* point = nullptr;

	while (1) {
		point = this->getPixelAt(lastpos.x, lastpos.y);

		if (point) {
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



PixelMap* FloodFillMap::GetGroupFrom(FFPixel* pixel) {
	if (!pixel) return nullptr;
	this->result_group = new vector<FPixel*>;

	stalledPixels.push_back(pixel);

	while (stalledPixels.size() > 0) {
		FFPixel* px = stalledPixels.back();
		stalledPixels.pop_back();
		this->CheckPixel(px);
	}
	PixelMap* result;

	if (result_group->size() > 0) {
		result = new PixelMap(result_group);
		delete result_group;
		return result;
	}

	return nullptr;
}

PixelMap* FloodFillMap::GetNextSpriteGroup()
{
	return GetGroupFrom(GetNextSpritePixel());
}

FFPixel * FloodFillMap::getPixelAt(int x, int y)
{
	if (x >= 0 &&
		y >= 0 &&
		x < width &&
		y < height) {
		return this->pixels[y*width + x];
	}

	return nullptr;
}


void FloodFillMap::CheckPixel(FFPixel* pixel) {
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


FloodFillMap::~FloodFillMap()
{
	for (int i = 0; i < pixelcount(); i++) {
		delete this->pixels[i];
	}

}

FloodFillMap::FloodFillMap(Bitmap * bmp)
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
