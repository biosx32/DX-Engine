#include "Text.h"


Label::Label()
{
}

int Label::Load(Spritesheet* sh) {
	this->SpriteSheetData = sh;
	return 0;
}


Bitmap* Label::Get_Bitmap_Char(int c) {
	int max = sizeof(translate) / sizeof(char);
	int index = translate[c%max];
	return SpriteSheetData->SpriteData[index];

}

void Label::setText(char* text) {
	strcpy_s(this->text, text);
}