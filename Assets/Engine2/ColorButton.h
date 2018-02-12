#pragma once
#include "Button.h"
#include "Colors.h"


class ColorButton : public Button {
public:
	void Draw() override {
		Color drawColor = GetStateColor();
		
		io->out->paint->rectangle(GetPos().x, GetPos().y, size.x, size.y, drawColor);
		io->out->paint->rectangleBorder(GetPos().x, GetPos().y, size.x, size.y, Colors::Black, 2);

		int textWidth = text.size() * font->charw;
		int textY = GetPos().y + size.y / 2 - font->charh / 2;
		int textX = GetPos().x + (size.x - textWidth) / 2;
		io->out->PrintText(textX, textY, font, text);

	}

	Color GetStateColor() {
		switch (state) {
		case MouseState::normal:
			return Colors::GrayLightLight;

		case MouseState::press:
			return Colors::Gray;

		default: //hover or release
			return Colors::GrayLight;
		}
	}

	ColorButton(Vector2 position, void(*function)(), string textsrc, Vector2 size) :
		Button(position,size,function,textsrc){
	}

};