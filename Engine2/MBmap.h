#pragma once

#include "ManageableElement.h"
#include "BMap.h"

class MBmap : public ManageableElement, public Bitmap {
public:
	Vector2 size;
	MBmap(Vector2 pos, const char* FileName, Vector2 size) : Bitmap(FileName), ManageableElement(pos), size(size) {}
	MBmap(Vector2 pos, const char* FileName, Color c, Vector2 size) : Bitmap(FileName, c), ManageableElement(pos), size(size) {}

	void Update() override {

	}

	void Draw() override {
		io->out->DrawBitmap(this, this->GetPos().x, GetPos().y, size.x, size.y);
	}
};
