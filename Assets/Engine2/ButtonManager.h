#pragma once
#include <vector>
#include "Button.h"
#include "Mouse.h"
#include "Interface.h"
#include "Manager.h"

using std::vector;
typedef Button* ManagerType;

class ButtonManager : public Manager<ManagerType> {
public:
	MouseClient * mouse = nullptr;
	Interface* out = nullptr;

	void UpdateOne(ManagerType item) {
		if (mouse) {
			item->RefreshState(*mouse);
		}
	}

	void DrawOne(ManagerType item) {
		if (out) {
			item->Draw(out);
		}
	}

	void SetIO(MouseClient* mouse, Interface* out){
		this->mouse = mouse;
		this->out = out;
	}
	
};