#include "VectorBitmap.h"
FPixelMap::FPixelMap(vector<FPixel*>* src)
{
	this->pixels = new vector<FPixel*>(*src);
	this->ComputeSize();
	this->NormalizeV();
	this->NormalizeH();
}

FPixelMap::FPixelMap(Bitmap * src)
{
	this->pixels = new vector<FPixel*>;
	for (int y = 0; y < src->height; y++) {
		for (int x = 0; x < src->width; x++) {
			Color test_color = *src->GetPixelPointer(x, y);

			if (!src->GetIsBackground(test_color)) {
				pixels->push_back(new FPixel(x, y, test_color));
			}


		}
	}

	this->ComputeSize();

}

void FPixelMap::ComputeSize() {
	if (this->pixels->size() < 1) {
		width = height = offx = offy = 0;
		return;
	}

	int min_x, min_y, max_x, max_y;

	max_x = min_x = (*this->pixels->begin())->x;
	max_y = min_y = (*this->pixels->begin())->y;


	for (std::vector<FPixel*>::iterator it = pixels->begin(); it != pixels->end(); ++it)
	{
		FPixel* current = *it;
		if (current->x < min_x) {
			min_x = current->x;
		}
		else if (current->x > max_x) {
			max_x = current->x;
		}

		if (current->y < min_y) {
			min_y = current->y;
		}

		else if (current->y > max_y) {
			max_y = current->y;
		}
	}

	this->width = max_x - min_x + 1;
	this->height = max_y - min_y + 1;

	this->offx = min_x;
	this->offy = min_y;
}

FPixelMap::~FPixelMap()
{
	for (std::vector<FPixel*>::iterator it = pixels->begin(); it != pixels->end(); ++it)
	{
		delete *it;
	}
}

void FPixelMap::NormalizeV()
{
	for (std::vector<FPixel*>::iterator it = pixels->begin(); it != pixels->end(); ++it)
	{
		FPixel* current = *it;
		current->y -= offy;
	}
	offy = 0;

}

void FPixelMap::NormalizeH()
{

	for (std::vector<FPixel*>::iterator it = pixels->begin(); it != pixels->end(); ++it)
	{
		FPixel* current = *it;
		current->x -= offx;
	}

	offx = 0;
}
