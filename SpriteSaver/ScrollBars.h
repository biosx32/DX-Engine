#pragma once
#include "MouseRegion.h"
#include "Vectors.h"
#include "IOgroup.h"
class VScrollBar: public MouseRegion {
public:
	float value = 0.0f;
	MouseRegionR scroll;
	
	VScrollBar(Pos pos, Size size): MouseRegionR(pos,size), scroll(pos, Size(size.x, 16)) {

	}
	void Update() {

		if (scroll.GetMouseState() == MouseState::pressed) {
			io->mhelper->LockMouse(scroll.ID);
		}

		if (scroll.GetMouseState() == MouseState::release) {
			io->mhelper->FreeMouse();
		}

		if (io->mouse->LeftIsPressed() && io->mhelper->lockedobject == scroll.ID) {
			int ypos = io->mouse->GetMouseY();
			if (ypos - pos.y < 0) ypos = pos.y;
			else if (ypos - pos.y + scroll.size.y > size.y) ypos = pos.y + size.y -scroll.size.y;
			scroll.pos.y = ypos;
		}

		value = (scroll.pos.y - pos.y) / (size.y-scroll.size.y);
	}

	void SetValue(float a) {
		this->value = a;
		scroll.pos.y = pos.y +  (size.y - scroll.size.y)*value;
	}

	void Draw() {
		io->out->paint->rectangle(scroll.pos.x + 1, scroll.pos.y, scroll.size.x - 1, scroll.size.y, Colors::Green);
		io->out->paint->rectangleBorder(scroll.pos.x, scroll.pos.y, scroll.size.x - 1, scroll.size.y, Colors::GreenDark,2);
		io->out->paint->rectangleBorder(pos.x, pos.y, size.x, size.y, Colors::GreenDark, 1);
		
	}
};


class HScrollBar : public MouseRegion {
public:
	float value = 0.0f;
	MouseRegion scroll;
	HScrollBar(Pos pos, Size size) : MouseRegion(pos, size), scroll(pos, Size(16, size.y)) {
	}
	void Update() {

		if (scroll.GetMouseState() == MouseState::pressed) {
			io->mhelper->LockMouse(scroll.ID);
		}

		if (scroll.GetMouseState() == MouseState::release) {
			io->mhelper->FreeMouse();
		}

		if (io->mouse->LeftIsPressed() && io->mhelper->lockedobject == scroll.ID) {
			int xpos = io->mouse->GetMouseX() - scroll.size.x/2;
			if (xpos - pos.x < 0) xpos = pos.x;
			else if (xpos - pos.x +scroll.size.x >= size.x) xpos = pos.x + size.x -scroll.size.x;
			scroll.pos.x = xpos;
		}

		value = (scroll.pos.x - pos.x) / (size.x-scroll.size.x);
	}



	void Draw() {
	
		io->out->paint->rectangle(scroll.pos.x, scroll.pos.y, scroll.size.x, scroll.size.y, Colors::Green);
		io->out->paint->rectangleBorder(scroll.pos.x, scroll.pos.y, scroll.size.x, scroll.size.y, Colors::GreenDark,2);
		io->out->paint->rectangleBorder(pos.x, pos.y, size.x, size.y, Colors::GreenDark, 1);
	}
};
