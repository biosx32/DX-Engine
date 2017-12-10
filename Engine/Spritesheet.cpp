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

Sprite::Sprite(TransparentBitmap * TBmp)
{
	this->image = TBmp;
}
