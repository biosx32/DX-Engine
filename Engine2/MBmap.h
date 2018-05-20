#pragma once

#include "Element.h"
#include "BMap.h"

class MBmap : public Element, public Bitmap {
public:
	Vector2 size;
	MBmap(Vector2 pos, const char* FileName, Vector2 size) : Bitmap(FileName), Element(pos), size(size) {}
	MBmap(Vector2 pos, const char* FileName, Color c, Vector2 size) : Bitmap(FileName, c), Element(pos), size(size) {}

	void Update() override {

	}

	void Draw() override {
		io->out->DrawBitmap(this, this->pos.x, pos.y, size.x, size.y);
	}
};
