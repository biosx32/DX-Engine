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
	MouseHelper(MouseClient* mouse):mouse(mouse){}

	void Update() {
		position = Vector2(mouse->GetMouseX(), mouse->GetMouseY());
		mouseDelta = position - mouseOld;
		mouseOld = position;
	}
};