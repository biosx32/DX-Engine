#pragma once
#include <vector>
#include "Button.h"
#include "Mouse.h"
#include "Interface.h"
#include "Manager.h"

using std::vector;
class ButtonManager : public Manager<Button*> {
public:
	MouseClient * mouse = nullptr;
	Interface* out = nullptr;

	void UpdateOne(MTYPE btn) {
		if (mouse) {
			btn->RefreshState(*mouse);
		}
	}

	void DrawOne(MTYPE btn) {
		if (out) {
			btn->Draw(out);
		}
	}

	void SetIO(MouseClient* mouse, Interface* out){
		this->mouse = mouse;
		this->out = out;
	}
	
};