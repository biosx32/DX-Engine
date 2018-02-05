#pragma once
#include "Bmap.h"


class Sprite {
	float scalex;
	float scaley;

	Bitmap* image = nullptr;
	Sprite(char* FileName, Color bkclr, float sx, float sy):
		scalex(sx), scaley(sy) {
		this->image = new Bitmap(FileName, bkclr);
	}


	~Sprite(){
		if (image) delete image;
	}
};