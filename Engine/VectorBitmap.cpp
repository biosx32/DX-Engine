#include "VectorBitmap.h"
VectorBitmap::VectorBitmap(vector<FPixel*>* src)
{
	this->pixels = new vector<FPixel*>(*src);
	this->ComputeSize();
	this->NormalizeV();
	this->NormalizeH();
}

VectorBitmap::VectorBitmap(TransparentBitmap * src)
{

	this->pixels = new vector<FPixel*>;


	for (int y = 0; y < src->height; y++) {
		for (int x = 0; x < src->width; x++) {
			Color test_color = *src->GetDataPtr(x, y);

			if (!src->IsColorTransparent(test_color)) {
				pixels->push_back(new FPixel(x, y, test_color));
			}


		}
	}


	for (int i = 0; i < src->pixelcount(); i++) {
		int x = i % src->width;
		int y = i / src->width;

		Color test_color = *src->data[i];
		if (!src->IsColorTransparent(test_color)) {
			pixels->push_back(new FPixel(x, y, t));
		}
	}

	this->ComputeSize();

}

void VectorBitmap::ComputeSize() {
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

VectorBitmap::~VectorBitmap()
{
	for (std::vector<FPixel*>::iterator it = pixels->begin(); it != pixels->end(); ++it)
	{
		delete *it;
	}
}

void VectorBitmap::NormalizeV()
{
	for (std::vector<FPixel*>::iterator it = pixels->begin(); it != pixels->end(); ++it)
	{
		FPixel* current = *it;
		current->y -= offy;
	}
	offy = 0;

}

void VectorBitmap::NormalizeH()
{

	for (std::vector<FPixel*>::iterator it = pixels->begin(); it != pixels->end(); ++it)
	{
		FPixel* current = *it;
		current->x -= offx;
	}

	offx = 0;
}
