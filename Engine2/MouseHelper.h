#pragma once
#include "Element.h"
class MouseHelper {

protected:
	Vector2 mouseOld = Vector2(0, 0);

public:
	MouseClient* mouse = nullptr;
	bool grag_stae = false;
	Vector2 mouseDelta = Vector2(0, 0);
	Vector2 position = Vector2(0, 0);

	int lockedobject = -1;

	MouseHelper(MouseClient* mouse):mouse(mouse){}
	void LockMouse(int id) {
		lockedobject = id;
	}

	bool IsFree() {
		return lockedobject == -1;
	}

	bool IsBlocked(int i) {
		return lockedobject != i && !IsFree();
	}

	void Refresh() {
		position = Vector2(mouse->GetMouseX(), mouse->GetMouseY());
		mouseDelta = position - mouseOld;
		mouseOld = position;
		if (!mouse->LeftIsPressed()) {
			lockedobject = -1;
		}
	}
};