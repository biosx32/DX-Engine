#pragma once
#include <vector>
#include "Button.h"
#include "Mouse.h"
#include "Interface.h"
#include "Manager.h"

using std::vector;

class ButtonManager : public Manager<Button> {
public:
	
	using Manager::Manager;
	void UpdateOne(ItemsType* item) override {
		if (ioif.mouse) {
			(*item).RefreshState(*ioif.mouse);
		}
	}

	void DrawOne(ItemsType* item) override {
		if (ioif.out) {
			(*item).Draw(ioif.out);
		}
	}
	
};