#pragma once
#include "Vectors.h"
#include "Mouse.h"
#include "Interface.h"


enum class ButtonState : int {
	normal = 0,
	hover = 1,
	press = 2,
	release = 3
};


class Button {
public:

	Vector2 pos;
	Vector2 size;
	ButtonState state = ButtonState::normal;

	RasterFont* font = nullptr;
	void(*function)() = nullptr;

	std::string text = "";

	virtual void Draw(Interface* out) = 0;

	Button(Vector2 position, Vector2 size, void(*function)(), string textsrc, RasterFont* font) :
		pos(position), size(size), text(textsrc), function(function), font(font) {}


	inline bool isHover(MouseClient mouse) {
		int mx = mouse.GetMouseX(), 
			my = mouse.GetMouseY();
		return mx >= pos.x && my >= pos.y && mx < pos.x + size.x && my < pos.y + size.y;
	}

	inline bool isPress(MouseClient mouse) {
		return mouse.LeftIsPressed();
	}

	virtual void RefreshFunction();
	virtual void RefreshClickState(MouseClient mouse);

	void RefreshState(MouseClient mouse) {
		this->RefreshClickState(mouse);
		this->RefreshFunction();
	}

};