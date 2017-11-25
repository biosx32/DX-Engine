#include "Spritesheet.h"

Spritesheet::Spritesheet(int wcount, int hcount)
{
	this->wcount = wcount;
	this->hcount = hcount;
}

Spritesheet::~Spritesheet() {
	
	if (this->SpriteData) {
		delete[] SpriteData;
	}
}

void Spritesheet::Load(Bitmap * BitmapImage)
{
	int SpriteCount = wcount * hcount;


	this->BitmapImage = BitmapImage;
	this->SpriteData = new (Bitmap*[SpriteCount]);
	
	int OneSpriteWidth = BitmapImage->BitmapData->width / wcount;
	int OneSpriteHeight = BitmapImage->BitmapData->height / hcount;

	for (int y = 0; y < hcount; y++) {
		for (int x = 0; x < wcount; x++) {
			this->SpriteData[y * wcount + x] = BitmapImage->GetBitmapPart(x * OneSpriteWidth, y * OneSpriteHeight, OneSpriteWidth, OneSpriteHeight);
		}
	}
}
