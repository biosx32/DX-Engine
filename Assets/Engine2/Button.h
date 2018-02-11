#ifndef __BUTTON_H__
#define __BUTTON_H__
#include "Vectors.h"
#include "Mouse.h"
#include "Manager.h"
#include "Interface.h"
#include "GlobalObjects.h"


enum class ButtonState : int {
	normal = 0,
	hover = 1,
	press = 2,
	release = 3
};


class Button : public Manageable{
public:

	Vector2 size;
	ButtonState state = ButtonState::normal;
	BitmapFont* font = &DOS_WHITE;


	void(*function)() = nullptr;

	std::string text = "";

	virtual void Draw(IoGroup* iog) = 0;

	Button(Vector2 position, Vector2 size, void(*function)(), string textsrc) :
		Manageable(position), size(size), text(textsrc), function(function){}


	inline bool isHover(MouseClient* mouse) {
		int mx = mouse->GetMouseX(), 
			my = mouse->GetMouseY();
		return mx >= pos.x && my >= pos.y && mx < pos.x + size.x && my < pos.y + size.y;
	}

	inline bool isPress(MouseClient*  mouse) {
		return mouse->LeftIsPressed();
	}

	virtual void UpdateOnClick(){
		if (state == ButtonState::release) {
			if (function) {
				function();
			}
		}
	}

	virtual void UpdateClickState(MouseClient* mouse) {
		if (!isHover(mouse)) {
			state = ButtonState::normal;
		}
		else {
			if (isPress(mouse)) {
				state = ButtonState::press;
			}
			else {
				if (state == ButtonState::press) {
					state = ButtonState::release;
				}
				else {
					state = ButtonState::hover;
				}
			}
		}
	}

	void Update(IoGroup* iog) {
		this->UpdateClickState(iog->mouse);
		this->UpdateOnClick();
	}

};
#endif