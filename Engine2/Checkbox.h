#pragma once
#include "Element.h"
#include "GlobalObjects.h"
#include "MouseEventObject.h"


class CheckBox : public Element, public MouseEventObject {
public:
	bool checked = false;
	const int radius = 15;
	std::string text = "";
	BitmapFont* font = &DOS_BLACK;
	CheckBox(Vector2 position, char* text): Element(position), text(text) {

	}

	bool isHover(MouseClient* mouse) override {
		return (GetSquareDistance1(mouse->GetMouseX(), GetAbsolutePos().x+radius) + GetSquareDistance1(mouse->GetMouseY(), GetAbsolutePos().y+radius)) < radius*radius;
	}

	void UpdateCheck(){
		if (this->state == MouseState::release) {
			checked = !checked;
		}
	}

	void Update() {
		this->UpdateMouseState(io->mouse);
		UpdateCheck();
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