#pragma once
#include "Vectors.h"
#include "Mouse.h"
#include "Element.h"

namespace MouseState {
	enum Type
	{
		none = 0,
		hovered = 1,
		pressed = 2
	};
}

class MouseRegion : public Element {

public:
	int state = 0;
	int click_count = 0;
	void(*function)() = nullptr;

	MouseRegion(Vector2 pos, Vector2 size) : Element(pos,size) {
		this->name = "MouseRegion";

	}
public:
	
	virtual void Update(){	
		if (isHover()) {
			if (isPress()) {
				state = MouseState::pressed;
				io->mhelper->LockMouse(this->ID);
			}
			else {
				state = MouseState::hovered;
				if (io->mhelper->IsActive(this->ID)) {
					click_count += 1;
				}
			}
		} else { state = MouseState::none; }

		if (GetClick()) {
			if (function) { function(); }
		}
	
	}

	virtual bool isHover() {
		Vector2 mPos = Vector2(io->mouse->GetMouseX(), io->mouse->GetMouseY());
		Vector2 ePos = GetAbs();
		return mPos.x >= ePos.x && mPos.y >= ePos.y && mPos.x < ePos.x + size.x && mPos.y < ePos.y + size.y;
	}

	virtual bool isPress() {
		if (io->mouse->LeftIsPressed()) {
			if (isHover()) {
				return (!io->mhelper->IsBlocked(this->ID));
			}
		}
		return false;
	}

	bool IsClick() {
		if (click_count > 0) {
			return true;
		}
		return false;
	}

	bool GetClick() {
		if (click_count > 0) {
			click_count--;
			return true;
		}
		return false;
	}


};






