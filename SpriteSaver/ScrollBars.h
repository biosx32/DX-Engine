#pragma once
#include "MouseRegion.h"
#include "Vectors.h"
#include "IOgroup.h"
class VScrollBar: public MouseRegion {
public:
	float value = 0.0f;
	MouseRegion scroll;
	
	VScrollBar(Pos pos, Size size): MouseRegion(pos,size), scroll(pos, Size(size.x, 16)) {

	}
	void Update() {
		Vector2 spos = scroll.GetAbs();
		Vector2 pos = GetAbs();

		scroll.Update();

		if (io->mouse->LeftIsPressed() && io->mhelper->IsActive(scroll.ID)) {
			int ypos = io->mouse->GetMouseY();
			if (ypos - pos.y < 0) ypos = pos.y;
			else if (ypos - pos.y + scroll.size.y > size.y) ypos = pos.y + size.y -scroll.size.y;
			Vector2 npos = Vector2(spos.x, ypos);
			scroll.SetRel(npos);
		//	scroll.pos.y = ypos;
		}

		value = (spos.y - pos.y) / (size.y-scroll.size.y);
	}

	void SetValue(float a) {
		this->value = a;
		Vector2 spos = scroll.GetAbs();
		Vector2 pos = GetAbs();
		spos.y = pos.y +  (size.y - scroll.size.y)*value;
		scroll.SetRel(spos);
	}

	void Draw() {
		Vector2 spos = scroll.GetAbs();
		Vector2 pos = GetAbs();
		io->out->paint->rectangle(spos.x + 1, spos.y, scroll.size.x - 1, scroll.size.y, Colors::Green);
		io->out->paint->rectangleBorder(spos.x, spos.y, scroll.size.x - 1, scroll.size.y, Colors::GreenDark,2);
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
		Vector2 pos = GetAbs();
		Vector2 spos = scroll.GetAbs();
		scroll.Update();


		if (io->mouse->LeftIsPressed() && io->mhelper->IsActive(scroll.ID)) {
			int xpos = io->mouse->GetMouseX() - scroll.size.x/2;
			if (xpos - pos.x < 0) xpos = pos.x;
			else if (xpos - pos.x +scroll.size.x >= size.x) xpos = pos.x + size.x -scroll.size.x;
			Vector2 npos = Vector2(xpos, spos.y);
			scroll.SetRel(npos);

		}

		value = (spos.x - pos.x) / (size.x-scroll.size.x);
	}



	void Draw() {
		Vector2 spos =scroll.GetAbs();
		Vector2 pos = GetAbs();
		io->out->paint->rectangle(spos.x, spos.y, scroll.size.x, scroll.size.y, Colors::Green);
		io->out->paint->rectangleBorder(spos.x, spos.y, scroll.size.x, scroll.size.y, Colors::GreenDark,2);
		io->out->paint->rectangleBorder(pos.x, pos.y, size.x, size.y, Colors::GreenDark, 1);
	}
};
