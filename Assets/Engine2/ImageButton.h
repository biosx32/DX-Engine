#pragma once
#include "Button.h"
#include "Bmap.h"
#include "RasterFont.h"


class ImageButton : Button {
	Bitmap* image;
	void Draw(Interface* out) {
		int charcnt = strlen(text);
		int textw = charcnt * font->charw; 
		int textY = y + h / 2 - font->charh / 2;
		int textX = x + (this->w - textw) / 2;
		out->PrintText(textX, textY, font, text);

		
	}


	ImageButton(int x, int y, int w, int h, char* src, RasterFont* font, void(*function)(), Bitmap* image) :
		Button(x, y, w, h, src, font, function), image(image) {
	}
};