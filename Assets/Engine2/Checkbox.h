#pragma once
#include "Element.h"
#include "GlobalObjects.h"
class CheckBox : public ManageableElement, public MouseEventObject {
public:
	bool checked = false;
	const int radius = 15;
	std::string text = "";
	BitmapFont* font = &DOS_BLACK;
	CheckBox(Vector2 position, char* text): ManageableElement(position), text(text) {

	}

	bool isHover(MouseClient* mouse) override {
		return (GetSquareDistance1(mouse->GetMouseX(), GetPos().x+radius) + GetSquareDistance1(mouse->GetMouseY(), GetPos().y+radius)) < radius*radius;
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
		if (checked) {
			io->out->paint->rectangle(GetPos().x + radius/2.75, GetPos().y + radius/2.75, radius*1.45, radius*1.45, Colors::GreenDark);
		}
		io->out->paint->rectangleBorder(GetPos().x, GetPos().y, radius * 2, radius * 2, Colors::Black, 3);
		io->out->PrintText(GetPos().x + radius * 2.34, GetPos().y + radius /3, font, text);


	}


};