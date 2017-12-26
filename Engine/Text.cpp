#include "Text.h"



Label::~Label()
{
}

Label::Label(TransparentBitmap * bmp, int wcount, int hcount)
{
	this->sprite_sheet = new Spritesheet(bmp, wcount, hcount);

}



TransparentBitmap * Label::GetCharacterRepr(unsigned int c)
{
	int index = translate[c%txmax];
	return this->sprite_sheet->sprites[index];
}

void Label::setText(char* text) {

	strcpy_s(this->text, text);
	this->text[txmax - 1] = 0;
}