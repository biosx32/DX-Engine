#include "Spritesheet.h"

Spritesheet::~Spritesheet() {
	delete[] SPRITE_DATA;
}

void Spritesheet::_initialise(char* FileName, int W_COUNT, int H_COUNT)
{
	SH_W_COUNT = W_COUNT;
	SH_H_COUNT = H_COUNT;


	SH_SLOTS_MAX = (W_COUNT*H_COUNT);
	SH_SPRITE_W = (IMG_WIDTH / W_COUNT);
	SH_SPRITE_H = (IMG_HEIGHT / H_COUNT);

	if (!IMG_LOADED) return;

	SPRITE_DATA = new Bitmap*[SH_SLOTS_MAX];
	for (int i = 0; i < SH_SLOTS_MAX; i++) {
		int slot_x = i % W_COUNT;
		int slot_y = i / W_COUNT;

		int loc_x = slot_x * SH_SPRITE_W;
		int loc_y = slot_y * SH_SPRITE_H;

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
