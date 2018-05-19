#pragma once
#include "IOgroup.h"


class Element {
protected:
	BitmapFont * DFONT = &DOS_WHITE;

public:
	static int ElementCount;
	static IOgroup* io;

public:
	Element * parent = nullptr;
	std::string name = "Element";
	Vector2 pos, size = Vector2(1, 1);
	bool visible = true;
	int ID;

public:
	Element(Vector2 Pos, Vector2 display_size, std::string name) :pos(Pos), size(display_size), name(name) {
		ID = ElementCount++;
	}

private:
	void DrawName() {
		io->out->PrintText(parent->pos.x + parent->size.x / 2 - DFONT->charw*name.size() / 2, parent->pos.y + parent->parent->size.y / 2 - DFONT->charh / 2, DFONT, this->name);
	}

	void DrawBorder() {
		io->out->paint->FastHLine(parent->pos.x, parent->pos.y, parent->size.x, Colors::GreenLime);
		io->out->paint->FastHLine(parent->pos.x, parent->pos.y + parent->size.y, parent->size.x, Colors::GreenLime);
		io->out->paint->FastVLine(parent->pos.x, parent->pos.y, parent->size.y, Colors::GreenLime);
		io->out->paint->FastVLine(parent->pos.x + parent->size.x, parent->pos.y, parent->size.y, Colors::GreenLime);
	}

	void DrawCorners() {
		int fl = 6; //box parent->size;
		int of = -fl / 2; // offset
		io->out->paint->rectangle(of + parent->pos.x, of + parent->pos.y, fl, fl, Colors::Blue);
		io->out->paint->rectangle(of + parent->pos.x, of + parent->pos.y + parent->size.y, fl, fl, Colors::Blue);
		io->out->paint->rectangle(of + parent->pos.x + parent->size.x, of + parent->pos.y, fl, fl, Colors::Blue);
		io->out->paint->rectangle(of + parent->pos.x + parent->size.x, of + parent->pos.y + parent->size.y, fl, fl, Colors::Blue);
	}
protected:
	void BasicDraw() {
		DrawName(); DrawBorder(); DrawCorners();
	}
public:

	virtual void Update() = 0;
	virtual void Draw() { BasicDraw(); }

	
	/*int GetDepth() {
		if (parent) {
			return parent->GetDepth() + 1;
		}
		return 0;
	}*/

	Vector2 GetPos() {
		if (parent) {
			return this->pos + parent->GetPos();
		}
		else {
			return pos;
		}
	}




};



