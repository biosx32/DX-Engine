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

	IOgroup(Interface* pout, MouseClient* pmouse, KeyboardClient* pkbd, MouseHelper* pmhelper) {
		out = pout;
		mouse = pmouse;
		kbd = pkbd;
		mhelper = pmhelper;
	}

	void Update() {
		mhelper->Refresh();
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



