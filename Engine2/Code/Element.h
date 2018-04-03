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

};


class Element {
public:
	static int ElementCount;
	static IOgroup* io;

public:
	Element * parent = nullptr;
	int ID;

public:
	Vector2 pos;
	bool visible = true;
	
public:
	int GetDepth() {
		if (parent) {
			return parent->GetDepth() + 1;
		}
		return 0;
	}
	Vector2 GetAbsolutePos() {
		if (parent) {
			return this->pos + parent->GetAbsolutePos();
		}
		else {
			return pos;
		}
	}

	virtual void Update() = 0;
	virtual void Draw() = 0;

	Element(Vector2 Pos):pos(Pos){
		ID = ElementCount++;
	}
};



