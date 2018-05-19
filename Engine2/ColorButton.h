#pragma once
#include "Button.h"
#include "Colors.h"


class ColorButton : public Button {
public:
	void Draw() override {
		Color drawColor = GetStateColor();
		
		io->out->paint->rectangle(GetPos().x, GetPos().y, size.x, size.y, drawColor);
		io->out->paint->rectangleBorder(GetPos().x, GetPos().y, size.x, size.y, Colors::Black, 2);

		int textWidth = text.size() * DFONT->charw;
		int textY = GetPos().y + size.y / 2 - DFONT->charh / 2;
		int textX = GetPos().x + (size.x - textWidth) / 2;
		io->out->PrintText(textX, textY, DFONT, text);

	}

	Color GetStateColor() {
		switch (this->GetMouseState()) {
		case MouseState::none:
			return Colors::GrayLightLight;

		case MouseState::pressed:
			return Colors::Gray;

		default:
			return Colors::GrayLight;
		}
	}

	void Update() {
		this->UpdateOnClick();
	}

	ColorButton(Vector2 position, void(*function)(), string textsrc, Vector2 size) :
		Button(position,size,function,textsrc){
	}



};