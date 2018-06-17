#pragma once
#include "IOgroup.h"
#include "Painter.h"
#include "Labelz.h"

class BaseElement {
protected:
	static GFXDraw* draw;

public:
	static int ElementCount;
	static IOgroup* io;
	static BitmapFont * DFONT;
	static std::vector<BaseElement*> Elements;

	static void FullUpdate() { io->UpdateIO();  for (int i = 0; i < Elements.size(); i++) { Elements.at(i)->Update(); } }
	static void FullDraw() { for (int i = 0; i < Elements.size(); i++) { Elements.at(i)->Draw(); } }



public:
	int ID = -1;
	std::string name = "Default name";
	bool enabled = true;
	bool visible = true;

	virtual void Update() = 0;
	virtual void Draw() = 0;

	BaseElement()
	{
		ID = ElementCount++;
		Elements.push_back(this);
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


class Element: public BaseElement, public PosElement, public SizeElement {

public:
	virtual void Update() {}
	virtual void Draw()  { if (this->visible) { DrawName(); DrawBorder(); DrawCorners(); } }

	Label* nameLabel = nullptr;

	Element(Vector2 pos, Vector2 size) :
		PosElement(pos), SizeElement(size) {
		Vector2 lpos = Pos (pos.x + size.x / 2 - DFONT->charw*name.size () / 2,
							pos.y + size.y / 2 - DFONT->charh / 2);

		nameLabel = new Label(pos, this->name.c_str());
	
	}


	void DrawName() {
		nameLabel->Draw ();
	}
	void DrawBorder() {
		Vector2 pos = GetAbs();
		draw->paint->FastHLine(pos.x, pos.y, size.x, Colors::GreenLime);
		draw->paint->FastHLine(pos.x, pos.y + size.y, size.x, Colors::GreenLime);
		draw->paint->FastVLine(pos.x, pos.y, size.y, Colors::GreenLime);
		draw->paint->FastVLine(pos.x + size.x, pos.y, size.y, Colors::GreenLime);
	}
	void DrawCorners() {
		int fl = 6; //box size;
		int of = -fl / 2; // offset
		Vector2 pos = GetAbs();
		draw->paint->rectangle(of + pos.x, of + pos.y, fl, fl, Colors::Blue);
		draw->paint->rectangle(of + pos.x, of + pos.y + size.y, fl, fl, Colors::Blue);
		draw->paint->rectangle(of + pos.x + size.x, of + pos.y, fl, fl, Colors::Blue);
		draw->paint->rectangle(of + pos.x + size.x, of + pos.y + size.y, fl, fl, Colors::Blue);
	}

};



