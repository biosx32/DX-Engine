#pragma once
#include "Mouse.h"
enum class MouseState : int {
	normal = 0,
	hover = 1,
	press = 2,
	release = 3
};
class MouseEventObject {
public:
	MouseState state = MouseState::normal;
	MouseEventObject(){}

	virtual bool isHover(MouseClient* mouse) = 0;
	
	void UpdateMouseState(MouseClient* mouse) {
		if (!isHover(mouse)) {
			state = MouseState::normal;
		}
		else {
			if (mouse->LeftIsPressed()) {
				state = MouseState::press;
			}
			else {
				if (state == MouseState::press) {
					state = MouseState::release;
				}
				else {
					state = MouseState::hover;
				}
			}
		}
	}

};