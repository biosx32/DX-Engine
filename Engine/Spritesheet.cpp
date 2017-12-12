#include "Spritesheet.h"


Spritesheet::Spritesheet()
{
}

Spritesheet::Spritesheet(TransparentBitmap * BitmapImage, int wcount, int hcount)
{
	this->Load(BitmapImage, wcount, hcount);
}

Spritesheet::~Spritesheet() {
	this->RemoveSpriteData();
}


void Spritesheet::Load(TransparentBitmap * BitmapImage, int wcount, int hcount)
{
	this->datagroup = new SpritesheetDG();
	this->datagroup->Load(BitmapImage, wcount, hcount);
}



void Spritesheet::RemoveSpriteData()
{
	delete this->datagroup;
	this->datagroup = nullptr;

}

SpritesheetDG::~SpritesheetDG()
{
	delete[] data;
	this->data = nullptr;
}

void SpritesheetDG::Load(TransparentBitmap * BitmapImage, int wcount, int hcount)
{

	this->wcount = wcount;
	this->hcount = hcount;
	this->spritecount  = wcount * hcount;
	this->data = new Sprite*[spritecount];

	float sprite_width = BitmapImage->datagroup->width / (float) wcount;
	float sprite_height = BitmapImage->datagroup->height / (float) hcount;

	for (int y = 0; y < hcount; y++) {
		for (int x = 0; x < wcount; x++) {
			int xdst = (int) sprite_width * x;
			int ydst = (int) sprite_width * y;
			this->data[y * wcount + x] = new Sprite(BitmapImage->GetBitmapPart(xdst, ydst, (int)sprite_width, (int)sprite_height));
		}
	}
}

void SpritesheetDG::Load(vector<FPixel*>* src)
{
	int width = 0;
	int height = 0;
	int min_x, min_y, max_x, max_y;

	max_x = min_x = (*src->begin())->x;
	max_y = min_y = (*src->begin())->y;


	for (std::vector<FPixel*>::iterator it = src->begin(); it != src->end(); ++it)
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

	width = max_x - min_x;
	height = max_y - min_y;

	int offsetx = max_x - width;
	int offsety = max_y - height;

	for (std::vector<FPixel*>::iterator it = src->begin(); it != src->end(); ++it)
	{
		FPixel* current = *it;
		current->x -= offsetx;
		current->y -= offsety;
	}

	this->
	this->datagroup = new VectorBitmapDS(width, height);
	this->datagroup->pixels = src;
}

Sprite::Sprite(TransparentBitmap * TBmp)
{
	this->image = TBmp;
}

Sprite::Sprite(vector<FPixel*>* src)
{

	int width, height, min_x, min_y, max_x, max_y;

	max_x = min_x = (*src->begin())->x;
	max_y = min_y = (*src->begin())->y;


	for (std::vector<FPixel*>::iterator it = src->begin(); it != src->end(); ++it)
	{
		FPixel* current = *it;
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

	width = max_x - min_x;
	height = max_y - min_y;

	int offsetx = max_x - width;
	int offsety = max_y - height;

	for (std::vector<FPixel*>::iterator it = src->begin(); it != src->end(); ++it)
	{
		FPixel* current = *it;
		current->x -= offsetx;
		current->y -= offsety;
	}


	this->image = new TransparentBitmap(width, height, 0x00b1f4b1);

	for (std::vector<FPixel*>::iterator it = src->begin(); it != src->end(); ++it)
	{
		FPixel* current = *it;
		int i = current->y * width + current->x;
		this->image->datagroup->data[i] = current->color;
	}


}
