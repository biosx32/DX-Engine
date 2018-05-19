#pragma once
#include "Element.h"
#include "GlobalObjects.h"
#include "MouseRegion.h"

class CheckBox : public MouseRegion {
public:
	bool checked = false;
	const int radius = 15;
	std::string text = "";
	BitmapFont* DFONT = &DOS_BLACK;
	CheckBox(Vector2 position, const char* text): MouseRegion(position, Size(0,0)), text(text) {
		size = Size(radius * 2, radius * 2);
	}


	void Update() {
		if (this->GetMouseState()  == MouseState::release) {
		checked = !checked;
		}
	}

	void Draw() {
		io->out->paint->rectangle(GetPos().x, GetPos().y, radius * 2, radius * 2, Colors::White);
		if (checked) {
			io->out->paint->rectangle(GetPos().x, GetPos().y, radius * 2, radius * 2, Colors::GreenDark);
			io->out->paint->line(GetPos().x, GetPos().y, GetPos().x + radius * 2, GetPos().y + radius * 2, Colors::White,2);
			io->out->paint->line(GetPos().x, GetPos().y + radius * 2, GetPos().x + radius * 2, GetPos().y , Colors::White,2);

		
		}
		io->out->paint->rectangleBorder(GetPos().x, GetPos().y, radius * 2, radius * 2, Colors::Black, 3);
		io->out->paint->rectangleBorder(GetPos().x, GetPos().y, radius * 2, radius * 2, Colors::White, 1);
		io->out->PrintText(GetPos().x + radius * 2.34, GetPos().y + radius /3, DFONT, text);


	}


};