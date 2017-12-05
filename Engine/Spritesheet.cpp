#include "Spritesheet.h"


Spritesheet::Spritesheet()
{
}

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

void Spritesheet::Load(Bitmap * BitmapImage)
{
	this->Data = new SpritesheetDS();
	this->Data->Load(BitmapImage);
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
	this->count  = wcount * hcount;

	this->BitmapImage = BitmapImage;
	this->ptr = new (Bitmap*[count]);

	int sprite_width = BitmapImage->BitmapData->width / wcount;
	int sprite_height = BitmapImage->BitmapData->height / hcount;

	for (int y = 0; y < hcount; y++) {
		for (int x = 0; x < wcount; x++) {
			this->ptr[y * wcount + x] = BitmapImage->GetBitmapPart(x * sprite_width, y * sprite_height, sprite_width, sprite_height);
		}
	}
}

void SpritesheetDS::Load(Bitmap * BitmapImage)
{
	this->wcount = 0;
	this->hcount = 0;

	this->BitmapImage = BitmapImage;
	
// idea is -find first collision, then flood all points, into some list,
	//then find topleft topright - bounds, and then make all background color, then go to next first
	//this->count = number of sprites;
	this->ptr = new (Bitmap*[count]);

	//this->ptr[y * wcount + x] = BitmapImage->GetBitmapPart(x * sprite_width, y * sprite_height, sprite_width, sprite_height);
		
	
}

