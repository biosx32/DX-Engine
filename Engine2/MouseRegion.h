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

	int click_count = 0;
	bool was_pressed = false;
	MouseRegion(Vector2 ppos) : Element(ppos, Vector2(3,3), "MouseRegion") {}
public:

	virtual void Draw() {
		BasicDraw();
	}
	virtual void Update() {}

	virtual bool isHover() = 0;
	virtual bool isPress() {
		if (!io->mhelper->IsBlocked(this->ID) && isHover()) {
			return io->mouse->LeftIsPressed();
		}
		return false;
	}
	int GetMouseState() {
		if (isHover()) {
			if (isPress()) {
				was_pressed = true;
				return MouseState::pressed;
			}
			else {
				if (was_pressed) {
					click_count += 1;
					was_pressed = false;

				}
				return MouseState::hovered;
			}
		}
		return MouseState::none;
	}

	bool HasClick() {
		return click_count > 0;
	}

	void ReleaseOneClick() { if (HasClick()) click_count--; }
	void ReleaseAllClick() { click_count = 0; }

};


class MouseRegionR : public MouseRegion {
public:
	Vector2 size;
	MouseRegionR(Vector2 pos, Vector2 size): MouseRegion(pos), size(size) {}

	virtual bool isHover() {
		Vector2 mPos = Vector2(io->mouse->GetMouseX(), io->mouse->GetMouseY());
		return mPos.x >= pos.x && mPos.y >= pos.y && mPos.x < pos.x + size.x && mPos.y < pos.y + size.y;
	}
};




