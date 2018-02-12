#pragma once
#include "Mouse.h"
#include "Interface.h"
#include "Keyboard.h"
#include "Vectors.h"
#include "MouseHelper.h"

struct IOgroup {
public:
	Interface * out = nullptr;
	MouseClient* mouse = nullptr;
	KeyboardClient* kbd = nullptr;
	MouseHelper* mhelper = nullptr;

	void Update() {
		mhelper->Update();
	}
};

class Element {
public:
	Element * ElementInfo = this;
	Vector2 rel_pos;
	bool visible = true;
	
	virtual void Update(IOgroup* ig) = 0;
	Element(Vector2 Pos):rel_pos(Pos){}
};



