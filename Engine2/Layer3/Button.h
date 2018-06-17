#pragma once
#include "Vectors.h"
#include "Mouse.h"
#include "Element.h"
#include "GlobalObjects.h"


class Button : public MouseRegion {
public:

	BitmapFont* DFONT = &DOS_WHITE;
	void(*function)() = nullptr;
	std::string text = "";

	Button(Vector2 position, Vector2 size, void(*function)(), string textsrc) :
		MouseRegion(position,size), text(textsrc), function(function){}


	void UpdateOnClick(){
		if (IsClick()) {
			GetClick();
			if (function) {
				function();
			}
		}
	}


	virtual void Draw() = 0;
	virtual void Update() = 0;

};

#include "ImageButton.h"
#include "ColorButton.h"
