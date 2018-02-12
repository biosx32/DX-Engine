#ifndef __BUTTON_H__
#define __BUTTON_H__
#include "Vectors.h"
#include "Mouse.h"
#include "MouseEventObject.h"
#include "Interface.h"
#include "GlobalObjects.h"


class Button : public ManageableElement, public MouseEventObject {
public:

	Vector2 size;
	BitmapFont* font = &DOS_WHITE;
	void(*function)() = nullptr;
	std::string text = "";

	

	Button(Vector2 position, Vector2 size, void(*function)(), string textsrc) :
		ManageableElement(position), size(size), text(textsrc), function(function){}


	virtual bool isHover(MouseClient* mouse) override {
		int mx = mouse->GetMouseX(), 
			my = mouse->GetMouseY();
		return mx >= GetPos().x && my >= GetPos().y && mx < GetPos().x + size.x && my < GetPos().y + size.y;
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
#endif