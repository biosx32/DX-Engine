#pragma once
#include "..\Engine2\ClickableRectangle.h"
#include "..\Engine2\TestInterface.h"
class VScrollBar: public MouseRegion {
public:
	float value = 0.0f;
	bool locked = false;
	MouseRegion scroll;
	VScrollBar(Pos pos, Size size): MouseRegion(pos,size), scroll(pos, Size(size.x, 8)) {

	}
	void Update(IOgroup* IOG) {
		if (scroll.isHover(*IOG->mouse) && scroll.isPress(*IOG->mouse)) {
			locked = true;
		}

		if (!scroll.isPress(*IOG->mouse)) {
			locked = false;
		}

		if (locked) {
			int ypos = IOG->mouse->GetMouseY();
			if (ypos - pos.y < 0) ypos = pos.y;
			else if (ypos - pos.y + scroll.size.y > size.y) ypos = pos.y + size.y -scroll.size.y;
			scroll.pos.y = ypos;
		}

		value = (scroll.pos.y - pos.y) / (size.y-scroll.size.y);
	}

	void Draw(Interface* out) {
		IOG->out->paint->rectangle(scroll.pos.x + 1, scroll.pos.y, scroll.size.x - 1, scroll.size.y, Colors::Green);
		IOG->out->paint->rectangleBorder(pos.x, pos.y, size.x, size.y, Colors::GreenDark, 1);
		
	}
};


class HScrollBar : public MouseRegion {
public:
	float value = 0.0f;
	bool locked = false;
	MouseRegion scroll;
	HScrollBar(Pos pos, Size size) : MouseRegion(pos, size), scroll(pos, Size(8, size.y)) {

	}
	void Update(IOgroup* IOG) {
		if (scroll.isHover(*IOG->mouse) && scroll.isPress(*IOG->mouse)) {
			locked = true;
		}

		if (!scroll.isPress(*IOG->mouse)) {
			locked = false;
		}

		if (locked) {
			int xpos = IOG->mouse->GetMouseX();
			if (xpos - pos.x < 0) xpos = pos.x;
			else if (xpos - pos.x +scroll.size.x> size.x) xpos = pos.x + size.x-scroll.size.x;
			scroll.pos.x = xpos;
		}

		value = (scroll.pos.x - pos.x) / (size.x-scroll.size.x);
	}

	void Draw(Interface* out) {
	
		IOG->out->paint->rectangle(scroll.pos.x, scroll.pos.y, scroll.size.x, scroll.size.y, Colors::Green);
		IOG->out->paint->rectangleBorder(scroll.pos.x, scroll.pos.y, scroll.size.x, scroll.size.y, Colors::Green,3);
		IOG->out->paint->rectangleBorder(pos.x, pos.y, size.x, size.y, Colors::GreenDark, 1);
	}
};
