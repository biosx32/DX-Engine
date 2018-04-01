#pragma once
#include "Vectors.h"
#include "Mouse.h"
#include "Element.h"

namespace RegionState {
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

	int GetRegionState() { 
		Update();
		return state; 
	}

	bool isHover() {
		Vector2 mPos = Vector2(io->mouse->GetMouseX(), io->mouse->GetMouseY());
		return mPos.x >= pos.x && mPos.y >= pos.y && mPos.x < pos.x + size.x && mPos.y < pos.y + size.y;
	}

	bool isPress() {
		return io->mouse->LeftIsPressed() && isHover();
	}

	void Draw(){}
	void Update() {

		if (!isHover()) {
			state = RegionState::normal;
		}

		else { 
			
			if (isPress()) {
				state = RegionState::press;
			}

			else { 
				if (state == RegionState::press) {
					state = RegionState::release;
				}
				else {
					state = RegionState::hover;
				}
			}

		}

		
	}


};