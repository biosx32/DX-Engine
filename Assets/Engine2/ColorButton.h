#pragma once
#include "Button.h"
#include "Colors.h"


class ColorButton : public Button {
public:
	void Draw(Interface* out) {
		Color drawColor = GetStateColor();
		int charcnt = strlen(text);
		int textw = charcnt * font->charw;
		out->paint->rectangle(x, y, w, h, drawColor);
		out->paint->rectangleBorder(x, y, w, h, Colors::Black, 2);
		int textY = y + h / 2 - font->charh / 2;
		int textX = x + (this->w - textw) / 2;
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

	ColorButton(int x, int y, int w, int h, char* src, RasterFont* font, void(*function)()) :
		Button(x,y,w,h,src,font,function){
	}

};