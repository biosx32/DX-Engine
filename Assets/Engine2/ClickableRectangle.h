#pragma once
#include "Vectors.h"
#include "Mouse.h"
class ClickableRectangle {
public:
	int x, y, w, h;
	bool depressed;

	ClickableRectangle(int x, int y, int w, int h) :x(x), y(y), w(w), h(h), depressed(false) {}

	bool isHover(MouseClient mouse) {
		Vector2 mousePosition = Vector2(mouse.GetMouseX(), mouse.GetMouseY());
		return mousePosition.x >= x && mousePosition.y >= y && mousePosition.x < x + w && mousePosition.y < y + h;
	}

	bool isPress(MouseClient mouse) {
		Vector2 mousePosition = Vector2(mouse.GetMouseX(), mouse.GetMouseY());
		return isHover(mouse) && mouse.LeftIsPressed();
	}

	bool isRelease(MouseClient mouse) {
		if (!mouse.LeftIsPressed()) {
			bool r = depressed;
			r = isHover(mouse) ? r : false;
			depressed = false;
			return r == true;
		}
		return false;
	}

	void RefreshState(MouseClient mouse) {
		if (isPress(mouse)) {
			depressed = true;
		}
	}


};