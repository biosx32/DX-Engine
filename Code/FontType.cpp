#include "FontType.h"

FontType DOS_BLACK("..\\Resources\\DOS_FONT_WHITE_22_5.bmp", 22, 5, 0.25, Colors::Blue);
FontType DOS_BLACK_MINI("..\\Resources\\DOS_FONT_WHITE_22_5.bmp", 22, 5, 0.2, Colors::Blue);

FontType::FontType(char* image_src,int wcount, int hcount, float size, Color bckclr)
{
	Bitmap* font_bitmap = new Bitmap(image_src,bckclr);
	this->sprite_sheet = new FixedSpriteArray(font_bitmap, wcount, hcount,size);
	delete font_bitmap;

}

Bitmap * FontType::GetCharacterRepr(unsigned int c)
{
	int fix = (-33 + c) % sprite_sheet->count();
	int index = translate[fix];
	return this->sprite_sheet->sprites[index];
}
