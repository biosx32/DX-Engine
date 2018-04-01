#pragma once
#include "Vectors.h"
#include "Mouse.h"
#include "Element.h"

namespace ButtonState {
	enum Type
	{
		normal = 0,
		hover = 1,
		press = 2,
		release = 3
	};
}

class MouseRegion: public Element {
public:
	Vector2 size;
	int state = 0;

	MouseRegion(Vector2 ppos, Vector2 psize): Element(ppos){
		size = psize;
	}

	bool isHover() {
		Vector2 mPos = Vector2(io->mouse->GetMouseX(), io->mouse->GetMouseY());
		return mPos.x >= pos.x && mPos.y >= pos.y && mPos.x < pos.x + size.x && mPos.y < pos.y + size.y;
	}

	bool isPress() {
		return io->mouse->LeftIsPressed();
	}
	void Draw(){}
	void Update() {

		if (!isHover()) {
			state = ButtonState::normal;
		}

		else { //!isHover(mouse)
			if (isPress()) {
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