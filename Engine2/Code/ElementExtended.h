#pragma once
#include "Element.h"
class ElementExtended : public Element {
public:
	Vector2 size;
	ElementExtended(Pos pos, Size size) :Element(pos), size(size){}


	std::string name = "HelperElement";
	BitmapFont* font = &DOS_WHITE;

	void DrawName(Interface* out) {
		out->PrintText(pos.x + size.x / 2 - font->charw*name.size() / 2, pos.y + size.y / 2 - font->charh / 2, font, this->name);
	}

	void DrawBorder(Interface* out) {
		out->paint->FastHLine(pos.x, pos.y, size.x, Colors::GreenLime);
		out->paint->FastHLine(pos.x, pos.y + size.y, size.x, Colors::GreenLime);
		out->paint->FastVLine(pos.x, pos.y, size.y, Colors::GreenLime);
		out->paint->FastVLine(pos.x + size.x, pos.y, size.y, Colors::GreenLime);
	}

	void DrawCorners(Interface* out) {
		int fl = 6; //box size;
		int of = -fl / 2; // offset
		out->paint->rectangle(of + pos.x, of + pos.y, fl, fl, Colors::Blue);
		out->paint->rectangle(of + pos.x, of + pos.y + size.y, fl, fl, Colors::Blue);
		out->paint->rectangle(of + pos.x + size.x, of + pos.y, fl, fl, Colors::Blue);
		out->paint->rectangle(of + pos.x + size.x, of + pos.y + size.y, fl, fl, Colors::Blue);
	}
};