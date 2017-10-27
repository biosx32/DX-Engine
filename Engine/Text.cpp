#include "Text.h"


Text::Text(char* FileName, int W_COUNT, int H_COUNT, char* translate, int replaceColor, int newColor) : 
	Spritesheet(FileName, W_COUNT, H_COUNT, ANY_COLOR ,replaceColor, newColor) {
	this->translate = translate;
}

Bitmap* Text::Get_Bitmap_Char(char c) {
	int index = 0;

	for (index = 0; index < this->SH_SLOTS_MAX; index++) {
		if (c == translate[index]) {
			break;
		}
	}

	return SPRITE_DATA[index];

}

void Text::setText(char* text) {
	strcpy_s(this->text, text);
}