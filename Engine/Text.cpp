#include "Text.h"



int Label::Load(Spritesheet* sh) {
	this->sprite_sheet = sh;
	return 0;
}


Label::~Label()
{
}

Label::Label(Spritesheet * sh)
{
	this->Load(sh);
}


Sprite * Label::Get_Bitmap_Char(unsigned int c)
{
	int max = sizeof(translate) / sizeof(char);
	int index = translate[c%max];
	return this->sprite_sheet->sprites[index];
}

void Label::setText(char* text) {

	strcpy_s(this->text, text);
	this->text[txmax - 1] = 0;
}