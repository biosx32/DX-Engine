#pragma once
#include "Vectors.h"
#include "Mouse.h"
#include "Interface.h"

namespace ButtonState {
	enum Type
	{
		normal = 0,
		hover = 1,
		press = 2,
		release = 3
	};
}

class BaseButton {
public:
	int x, y, w, h;
	int state = 0;
	void(*function)() = nullptr;
	const static int bfsz = 1024;
	char text[bfsz];
	RasterFont* font;


	BaseButton(int x, int y, int w, int h, char* src, RasterFont* font, void(*function)()) :
		x(x), y(y), w(w), h(h), font(font), function(function) {
		strcpy_s(text, src);
		text[bfsz - 1] = 0;
	}

	bool isHover(MouseClient mouse) {
		Vector2 mousePosition = Vector2(mouse.GetMouseX(), mouse.GetMouseY());
		return mousePosition.x >= x && mousePosition.y >= y && mousePosition.x < x + w && mousePosition.y < y + h;
	}

	inline bool isPress(MouseClient mouse) {
		return mouse.LeftIsPressed();
	}

	virtual void Draw(Interface* out) = 0;

	void RefreshFunction() {
		if (state == ButtonState::release) {
			if (function) {
				function();
			}
		}
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


	void RefreshState(MouseClient mouse) {
		this->RefreshClickState(mouse);
		this->RefreshFunction();
	}

};