#include "Text.h"



int Label::Load(Spritesheet* sh) {
	this->sprite_sheet = sh;
	return 0;
}


Label::~Label()
{
	delete this->sprite_sheet;
	this->sprite_sheet = nullptr;
}

Label::Label(Spritesheet * sh)
{
	this->Load(sh);
}

Bitmap* Label::Get_Bitmap_Char(int c) {
	int max = sizeof(translate) / sizeof(char);
	int index = translate[c%max];
	return sprite_sheet->Data->ptr[index];

}

void Label::setText(char* text) {
	strcpy_s(this->text, text);
}