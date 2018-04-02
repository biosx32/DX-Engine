#pragma once
#include "Element.h"
#include "GlobalObjects.h"
#include "MouseRegion.h"

class CheckBox : public MouseRegion {
public:
	bool checked = false;
	const int radius = 15;
	std::string text = "";
	BitmapFont* font = &DOS_BLACK;
	CheckBox(Vector2 position, const char* text): MouseRegion(position, Size(0,0)), text(text) {
		size = Size(radius * 2, radius * 2);
	}


	void Update() {
		if (this->GetRegionState()  == RegionState::release) {
		checked = !checked;
		}
	}

	void Draw() {
		io->out->paint->rectangle(GetAbsolutePos().x, GetAbsolutePos().y, radius * 2, radius * 2, Colors::White);
		if (checked) {
			io->out->paint->rectangle(GetAbsolutePos().x, GetAbsolutePos().y, radius * 2, radius * 2, Colors::GreenDark);
			io->out->paint->line(GetAbsolutePos().x, GetAbsolutePos().y, GetAbsolutePos().x + radius * 2, GetAbsolutePos().y + radius * 2, Colors::White,2);
			io->out->paint->line(GetAbsolutePos().x, GetAbsolutePos().y + radius * 2, GetAbsolutePos().x + radius * 2, GetAbsolutePos().y , Colors::White,2);

		
		}
		io->out->paint->rectangleBorder(GetAbsolutePos().x, GetAbsolutePos().y, radius * 2, radius * 2, Colors::Black, 3);
		io->out->paint->rectangleBorder(GetAbsolutePos().x, GetAbsolutePos().y, radius * 2, radius * 2, Colors::White, 1);
		io->out->PrintText(GetAbsolutePos().x + radius * 2.34, GetAbsolutePos().y + radius /3, font, text);


	}


};