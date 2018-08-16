#pragma once
#include "Layer0.h"
#include "MouseHelper.h"

struct IOgroup {
public:
	D3DGraphics* gfx = nullptr;
	MouseClient* mouse = nullptr;
	KeyboardClient* kbd = nullptr;
	MouseHelper* mhelper = nullptr;
	
	void UpdateIO() {
		mhelper->Refresh();
	}

	IOgroup(D3DGraphics* pgfx, MouseClient* pmouse, KeyboardClient* pkbd) :
		gfx(pgfx), mouse(pmouse), kbd(pkbd),
		mhelper(new MouseHelper(pmouse)) {
	}

	~IOgroup () {
		delete mhelper;
	}

};
