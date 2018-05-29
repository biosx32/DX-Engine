#pragma once
#include "Mouse.h"
#include "Interface.h"
#include "Keyboard.h"
#include "MouseHelper.h"

struct IOgroup {
public:
	D3DGraphics* gfx = nullptr;
	GFXInterface* out = nullptr;
	MouseClient* mouse = nullptr;
	KeyboardClient* kbd = nullptr;
	MouseHelper* mhelper = nullptr;
	
	void UpdateIO() {
		mhelper->Refresh();
	}

	IOgroup(D3DGraphics* pgfx, MouseClient* pmouse, KeyboardClient* pkbd) :
		gfx(pgfx), mouse(pmouse), kbd(pkbd),
		mhelper(new MouseHelper(pmouse)), out(new GFXInterface(pgfx)) {
	}

};
