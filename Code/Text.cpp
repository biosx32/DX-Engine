#include "Text.h"

TransparentBitmap img("..\\Resources\\DOS_FONT_BLACK_22_5.bmp", Colors::MakeARGB(255, 0, 0, 255));
FontType DOS_BLACK(&img, 22, 5);

FontType::~FontType()
{
}

FontType::FontType(TransparentBitmap * bmp, int wcount, int hcount)
{
	this->sprite_sheet = new SymetricSpriteSheet(bmp, wcount, hcount);

}

TransparentBitmap * FontType::GetCharacterRepr(unsigned int c)
{
	if (sprite_sheet->count < 1) {
		prints << "Attempt to access wrong font" << msgbox;
		exit(-1);
	}
	int fix = (-33 + c) % sprite_sheet->count;
	int index = translate[fix];
	return this->sprite_sheet->sprites[index];
}
