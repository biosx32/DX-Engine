#ifndef _GUI_BUILDER_H__N__
#define _GUI_BUILDER_H__N__

#include "Vectors.h"
#include "Mouse.h"
#include "Colors.h"
#include "RasterFont.h"
#include "TestInterface.h"
#include "Button.h"
#include <vector>
using std::vector;


extern RasterFont DOS_BLACK_MINI;
extern RasterFont DOS_BLACK;


class ButtonManager {
public:
	MouseClient* mouse;
	vector<Button*> buttons;
	

	void Init() {
		buttons.push_back(new Button(150, 0, 135, 40, "Scale 2.0x", &DOS_BLACK, nullptr));
		buttons.push_back(new Button(280, 0, 135, 40, "Scale 0.5x", &DOS_BLACK, nullptr));
		buttons.push_back(new Button(410, 0, 135, 40, "Rotate 15*", &DOS_BLACK, nullptr));
		buttons.push_back(new Button(540, 0, 135, 40, "Rotate -15*", &DOS_BLACK, nullptr));
	}

	void RefreshState() {
		for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
			(*it)->RefreshState(*mouse);
			if ((*it)->isRelease(*mouse)) {
				if ((*it)->function) {
					(*it)->function();
				}
			}
		}

	
	}

	void Draw(Interface* out) {
		for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
			(*it)->Draw(out);
		}
	}

	ButtonManager(MouseClient* mouse) {
		this->mouse = mouse;
		this->Init();
	}

	~ButtonManager(){
		for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
			delete (*it);
		}
	}
};

#endif