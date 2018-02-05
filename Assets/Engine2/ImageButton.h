#pragma once
#include "Button.h"
#include "Bmap.h"
#include "RasterFont.h"


class ImageButton : BaseButton {
	Bitmap* image;
	void Draw(Interface* out) {
		// TODO
	}


	ImageButton(int x, int y, int w, int h, char* src, RasterFont* font, void(*function)(), Bitmap* image) :
		BaseButton(x, y, w, h, src, font, function), image(image) {
	}
};