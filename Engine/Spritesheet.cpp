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

void Spritesheet::_initialise(char* FileName, int W_COUNT, int H_COUNT)
{

	int slot_x, slot_y, loc_x, loc_y;
	
	
	for (int i = 0; i < SH_SLOTS_MAX; i++) {
		slot_x = i % W_COUNT;
		slot_y = i / W_COUNT;

		loc_x = slot_x * SH_SPRITE_W;
		loc_y = slot_y * SH_SPRITE_H;

		SPRITE_DATA[i] = this->get_sprite(loc_x, loc_y, this->SH_SPRITE_W, this->SH_SPRITE_H);

	}
}

Spritesheet::Spritesheet(char* FileName, int W_COUNT, int H_COUNT): 
	Bitmap(FileName) {
	_initialise(FileName, W_COUNT, H_COUNT);
}

Spritesheet::Spritesheet(char* FileName, int W_COUNT, int H_COUNT, int ColorReplaceMode, int ReplaceColor, int NewColor):
	Bitmap(FileName)
{
	COLOR_REPLACE_MODE = ColorReplaceMode;
	FROM_REPLACE_KEY.dword = ReplaceColor;
	TO_REPLACE_KEY.dword = NewColor;
	_initialise(FileName, W_COUNT, H_COUNT);
}
