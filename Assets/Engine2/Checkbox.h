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
		io->out->paint->rectangle(GetPos().x, GetPos().y, radius * 2, radius * 2, Colors::White);
		if (checked) {
			io->out->paint->rectangle(GetPos().x, GetPos().y, radius * 2, radius * 2, Colors::GreenDark);
			io->out->paint->line(GetPos().x, GetPos().y, GetPos().x + radius * 2, GetPos().y + radius * 2, Colors::White,2);
			io->out->paint->line(GetPos().x, GetPos().y + radius * 2, GetPos().x + radius * 2, GetPos().y , Colors::White,2);

		
		}
		io->out->paint->rectangleBorder(GetPos().x, GetPos().y, radius * 2, radius * 2, Colors::Black, 3);
		io->out->paint->rectangleBorder(GetPos().x, GetPos().y, radius * 2, radius * 2, Colors::White, 1);
		io->out->PrintText(GetPos().x + radius * 2.34, GetPos().y + radius /3, font, text);


	}


};