#include "Spritesheet.h"


Spritesheet::Spritesheet(Bitmap * BitmapImage, int wcount, int hcount)
{
	this->Load(BitmapImage, wcount, hcount);
}

Spritesheet::~Spritesheet() {
	this->RemoveSpriteData();
}


void Spritesheet::Load(Bitmap * BitmapImage, int wcount, int hcount)
{
	this->Data = new SpritesheetDS();
	this->Data->Load(BitmapImage, wcount, hcount);
}

void Spritesheet::RemoveSpriteData()
{
	delete this->Data;
	this->Data = nullptr;

}

SpritesheetDS::~SpritesheetDS()
{
	delete[] ptr;
	this->ptr = nullptr;
}

void SpritesheetDS::Load(Bitmap * BitmapImage, int wcount, int hcount)
{

	this->wcount = wcount;
	this->hcount = hcount;
	int sprite_count = wcount * hcount;

	this->BitmapImage = BitmapImage;

	
	this->ptr = new (Bitmap*[sprite_count]);

	int sprite_width = BitmapImage->BitmapData->width / wcount;
	int sprite_height = BitmapImage->BitmapData->height / hcount;

	for (int y = 0; y < hcount; y++) {
		for (int x = 0; x < wcount; x++) {
			this->ptr[y * wcount + x] = BitmapImage->GetBitmapPart(x * sprite_width, y * sprite_height, sprite_width, sprite_height);
		}
	}
}
