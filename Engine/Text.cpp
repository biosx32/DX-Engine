#include "Text.h"


Label::Label()
{
}

int Label::Load(Spritesheet* sh) {
	this->SpriteSheetData = sh;
	return 0;
}


Bitmap* Label::Get_Bitmap_Char(int c) {
	int index = 0;
	int maxChars = SpriteSheetData->wcount * SpriteSheetData->hcount;

	for (index = 0; index < maxChars; index++) {
		if (c == translate[index]) {
			break;
		}
	}

	return SpriteSheetData->SpriteData[index];

}

void Label::setText(char* text) {
	strcpy_s(this->text, text);
}