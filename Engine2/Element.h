#pragma once
#include "IOgroup.h"

class BaseElement {
public:
	static int ElementCount;
	static IOgroup* io;
	static BitmapFont * DFONT;

public:
	int ID = -1;
	std::string name = "Default name";
	bool enabled = true;
	bool visible = true;


	BaseElement() {
		ID = ElementCount++;
	}

	
};

class PosElement {
private:
	Vector2 pos;
public:
	PosElement* parent = nullptr;

	PosElement(Vector2 pos):
		pos(pos){
	}

	Vector2 GetAbs() {
		if (parent) {
			return this->pos + parent->GetAbs();
		}
		else {
			return pos;
		}
	}
	
	void SetRel(Vector2 pos) { this->pos = pos; }

	Vector2 GetRel() {
		return pos;
	
	}

};

class SizeElement {
public:
	Vector2 size;
	SizeElement(Vector2 size):
		size(size) {
	}
};

class IElement: public BaseElement, public PosElement, public SizeElement {
public:
	Vector2 size;
	IElement(Vector2 pos, Vector2 size):
		PosElement(pos), SizeElement(size) {
	}

	virtual void Update() = 0;
};

class Element: public IElement {

public:
	virtual void Update() = 0;
	virtual void Draw() { DrawName(); DrawBorder(); DrawCorners(); }

	Element(Vector2 pos, Vector2 size) :
		IElement(pos, size) {
	}


	void DrawName() {
		Vector2 pos = GetAbs();
		io->out->PrintText(pos.x + size.x / 2 - 
							DFONT->charw*name.size() / 2,
							pos.y + size.y / 2 - DFONT->charh / 2, 
							DFONT, this->name);
	}
	void DrawBorder() {
		Vector2 pos = GetAbs();
		io->out->paint->FastHLine(pos.x, pos.y, size.x, Colors::GreenLime);
		io->out->paint->FastHLine(pos.x, pos.y + size.y, size.x, Colors::GreenLime);
		io->out->paint->FastVLine(pos.x, pos.y, size.y, Colors::GreenLime);
		io->out->paint->FastVLine(pos.x + size.x, pos.y, size.y, Colors::GreenLime);
	}
	void DrawCorners() {
		int fl = 6; //box size;
		int of = -fl / 2; // offset
		Vector2 pos = GetAbs();
		io->out->paint->rectangle(of + pos.x, of + pos.y, fl, fl, Colors::Blue);
		io->out->paint->rectangle(of + pos.x, of + pos.y + size.y, fl, fl, Colors::Blue);
		io->out->paint->rectangle(of + pos.x + size.x, of + pos.y, fl, fl, Colors::Blue);
		io->out->paint->rectangle(of + pos.x + size.x, of + pos.y + size.y, fl, fl, Colors::Blue);
	}

};



