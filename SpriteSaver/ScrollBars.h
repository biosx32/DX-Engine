#pragma once
#include "..\Engine2\ClickableRectangle.h"
#include "..\Engine2\TestInterface.h"
class ScrollBar: public MouseRegion {
public:
	float value = 0.0f;
	bool locked = false;
	MouseRegion scroll;
	ScrollBar(Pos pos, Size size): MouseRegion(pos,size), scroll(pos, Size(size.x, 8)) {

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
			else if (ypos - pos.y >= size.y) ypos = pos.y + size.y - 1;
			scroll.pos.y = ypos;
		}

		value = (scroll.pos.y - pos.y) / size.y;
	}

	void Draw(Interface* out) {
		IOG->out->paint->rectangleBorder(pos.x + size.x - 15, pos.y, 15, size.y, Colors::Red, 1);
		IOG->out->paint->rectangle(scroll.pos.x, scroll.pos.y - scroll.size.y / 2, scroll.size.x, scroll.size.y, Colors::Red);
	}
};