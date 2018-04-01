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

class MouseRegion {
public:
	Vector2 pos;
	Vector2 size;
	int state = 0;

	MouseRegion(Vector2 ppos, Vector2 psize){
		pos = ppos; size = psize;
	}

	bool isHover(MouseClient mouse) {
		Vector2 mPos = Vector2(mouse.GetMouseX(), mouse.GetMouseY());
		return mPos.x >= pos.x && mPos.y >= pos.y && mPos.x < pos.x + size.x && mPos.y < pos.y + size.y;
	}

	bool isPress(MouseClient mouse) {
		return mouse.LeftIsPressed();
	}

	void Update(MouseClient mouse) {

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