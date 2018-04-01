#ifndef __BUTTON_H__
#define __BUTTON_H__
#include "Vectors.h"
#include "Mouse.h"
#include "Element.h"
#include "MouseEventObject.h"
#include "Interface.h"
#include "GlobalObjects.h"


class Button : public Element, public MouseEventObject {
public:

	Vector2 size;
	BitmapFont* font = &DOS_WHITE;
	void(*function)() = nullptr;
	std::string text = "";

	

	Button(Vector2 position, Vector2 size, void(*function)(), string textsrc) :
		Element(position), size(size), text(textsrc), function(function){}


	virtual bool isHover(MouseClient* mouse) override {
		int mx = mouse->GetMouseX(), 
			my = mouse->GetMouseY();
		return mx >= GetAbsolutePos().x && my >= GetAbsolutePos().y && mx < GetAbsolutePos().x + size.x && my < GetAbsolutePos().y + size.y;
	}

	virtual void UpdateOnClick(){
		if (state == MouseState::release) {
			if (function) {
				function();
			}
		}
	}


	virtual void Draw() = 0;

	void Update() {
		this->UpdateMouseState(io->mouse);
		this->UpdateOnClick();
	}

};

#include "ImageButton.h"
#include "ColorButton.h"

#endif