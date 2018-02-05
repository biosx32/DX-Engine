#pragma once
#include "Vectors.h"
#include "Mouse.h"

namespace ButtonState {
	enum Type
	{
		normal = 0,
		hover = 1,
		press = 2,
		release = 3
	};
}

class ClickableRectangle {
public:
	int x, y, w, h;
	int state = 0;


	ClickableRectangle(int x, int y, int w, int h) :x(x), y(y), w(w), h(h) {}

	bool isHover(MouseClient mouse) {
		Vector2 mousePosition = Vector2(mouse.GetMouseX(), mouse.GetMouseY());
		return mousePosition.x >= x && mousePosition.y >= y && mousePosition.x < x + w && mousePosition.y < y + h;
	}

	inline bool isPress(MouseClient mouse) {
		return mouse.LeftIsPressed();
	}

	void RefreshClickState(MouseClient mouse) {

		if (!isHover(mouse)) {
			state = ButtonState::normal;
		}

		else { //!isHover(mouse)
			if (isPress(mouse)) {
				state = ButtonState::press;
			}

			else { // !isPress(mouse)
				if (state == ButtonState::press) {
					state = ButtonState::release;
				}
				else { //state != ButtonState::press
					state = ButtonState::hover;
				}
			}

		}

		
		
		
		

		
	}


};