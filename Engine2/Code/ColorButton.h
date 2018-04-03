#pragma once
#include "Button.h"
#include "Colors.h"


class ColorButton : public Button {
public:
	void Draw() override {
		Color drawColor = GetStateColor();
		
		io->out->paint->rectangle(GetAbsolutePos().x, GetAbsolutePos().y, size.x, size.y, drawColor);
		io->out->paint->rectangleBorder(GetAbsolutePos().x, GetAbsolutePos().y, size.x, size.y, Colors::Black, 2);

		int textWidth = text.size() * font->charw;
		int textY = GetAbsolutePos().y + size.y / 2 - font->charh / 2;
		int textX = GetAbsolutePos().x + (size.x - textWidth) / 2;
		io->out->PrintText(textX, textY, font, text);

	}

	Color GetStateColor() {
		switch (state) {
		case RegionState::normal:
			return Colors::GrayLightLight;

		case RegionState::press:
			return Colors::Gray;

		default:
			return Colors::GrayLight;
		}
	}

	void Update() {
		UpdateMouseRegionState();
		this->UpdateOnClick();
	   
	}

	ColorButton(Vector2 position, void(*function)(), string textsrc, Vector2 size) :
		Button(position,size,function,textsrc){
	}



};