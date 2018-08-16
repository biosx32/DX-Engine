#pragma once
#include "Layer0.h"

class MouseHelper {

protected:
	Vector2 mouseOld = Vector2(0, 0);

public:
	MouseClient* mouse = nullptr;
	Vector2 mouseDelta = Vector2(0, 0);
	Vector2 position = Vector2(0, 0);
	int lockedobject = -1;

	MouseHelper(MouseClient* mouse):mouse(mouse){}

	void LockMouse(int id) {
		lockedobject = id;
	}

	void ReleaseLock() {
		lockedobject = -1;
	}

	bool IsMouseNotLocked() {
		return lockedobject == -1;
	}

	bool CanBeUsedBy(int i) {
		return lockedobject == i || lockedobject == -1;
	}

	bool IsMouseUsedBy(int i) {
		return lockedobject == i;
	}

	void Refresh () {
	

		position = Vector2 (mouse->GetMouseX (), mouse->GetMouseY ());
		mouseDelta = position - mouseOld;
		mouseOld = position;

		if (mouse->LeftIsPressed ()) {
			if (IsMouseNotLocked ()) {
				lockedobject = -2;
			}
		}

		else{
			lockedobject = -1;
		}

		
		
	}
};