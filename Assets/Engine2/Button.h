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

class Button {
public:
	int x, y, w, h;
	int state = 0;
	void(*function)() = nullptr;
	const static int bfsz = 1024;
	char text[bfsz];
	RasterFont* font;

	virtual void Draw(Interface* out) = 0;

	Button(int x, int y, int w, int h, char* src, RasterFont* font, void(*function)()) :
		x(x), y(y), w(w), h(h), font(font), function(function) {
		strcpy_s(text, src);
		text[bfsz - 1] = 0;
	}

	bool isHover(MouseClient mouse) {
		int mx = mouse.GetMouseX(), my = mouse.GetMouseY();
		return mx >= x && my >= y && mx < x + w && my < y + h;
	}

	bool isPress(MouseClient mouse) {
		return mouse.LeftIsPressed();
	}

	

	void RefreshFunction();
	void RefreshClickState(MouseClient mouse);
	void RefreshState(MouseClient mouse) {
		this->RefreshClickState(mouse);
		this->RefreshFunction();
	}

};