#pragma once
#include "Mouse.h"
#include "Interface.h"
#include "Keyboard.h"
#include "Vectors.h"

struct IoGroup {
public:
	Interface * out = nullptr;
	MouseClient* mouse = nullptr;
	KeyboardClient* kbd = nullptr;
};

class Element {

protected:
	Vector2 pos;
	bool visible = true;
	Element* ElementInfo = this;
	virtual void Update(IoGroup* ig) = 0;
	Element(Vector2 Pos):pos(Pos){}
};

class Manageable : public Element {
protected:
	static int ElementCount;
public:
	int ID;
	virtual void Update(IoGroup* ig) = 0;
	virtual void Draw(IoGroup* ig) = 0;

	Manageable(Vector2 Pos) :Element(Pos) {
		ID = ElementCount++;
	}
};


