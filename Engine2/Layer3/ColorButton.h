#pragma once
#include "Button.h"
#include "Colors.h"


class ColorButton : public Button {
public:
	void Draw() override {
		Color drawColor = GetStateColor();
          Vector2 pos = property.GetAbs();
                draw->paint->rectangle(
                  pos.x, pos.y, property.size.x, property.size.y, drawColor);
                draw->paint->rectangleBorder(pos.x,
                                             pos.y,
                                             property.size.x,
                                             property.size.y,
                                             Colors::Black,
                                             2);

		int textWidth = text.size() * DFONT->charw;
                int textY = pos.y + property.size.y / 2 - DFONT->charh / 2;
                int textX = pos.x + (property.size.x - textWidth) / 2;
		PrintText(draw, textX, textY, text,DFONT);

	}

	Color GetStateColor() {
		switch (mregion->state) {
		case MouseState::none:
			return Colors::GrayLightLight;

		case MouseState::pressed:
			return Colors::Gray;

		default:
			return Colors::GrayLight;
		}
	}


	ColorButton(Vector2 position, void(*function)(), string textsrc, Vector2 size) :
		Button(position,size,function,textsrc){
	}



};