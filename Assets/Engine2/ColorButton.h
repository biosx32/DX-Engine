#pragma once
#include "Button.h"
#include "Colors.h"


class ColorButton : public Button {
public:
	void Draw(Interface* out) {
		Color drawColor = GetStateColor();
		
		out->paint->rectangle(pos.x, pos.y, size.x, size.y, drawColor);
		out->paint->rectangleBorder(pos.x, pos.y, size.x, size.y, Colors::Black, 2);

		int textWidth = text.size() * font->charw;
		int textY = pos.y + size.y / 2 - font->charh / 2;
		int textX = pos.x + (size.x - textWidth) / 2;
		out->PrintText(textX, textY, font, text);

	}

	Color GetStateColor() {
		switch (state) {
		case ButtonState::normal:
			return Colors::LightLightGray;

		case ButtonState::hover:
			return Colors::LightGray;

		case ButtonState::press:
			return Colors::Gray;

		case ButtonState::release:
			return Colors::Red;

		default:
			return Colors::White;
		}
	}

	ColorButton(Vector2 position, Vector2 size, void(*function)(), string textsrc) :
		Button(position,size,function,textsrc){
	}

};