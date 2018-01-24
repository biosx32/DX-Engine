#ifndef _GUI_BUILDER_H__N__
#define _GUI_BUILDER_H__N__

#include "Vectors.h"
#include "..\Assets\Mouse.h"
#include "Colors.h"
#include "FontType.h"
#include "TestInterface.h"
#include <vector>
using std::vector;

class ClickableRectangle {
public:
	int x, y, w, h;
	bool depressed;

	ClickableRectangle(int x, int y, int w, int h) :x(x), y(y), w(w), h(h), depressed(false) {}

	bool isHover(MouseClient mouse) {
		Vector2 mousePosition = Vector2(mouse.GetMouseX(), mouse.GetMouseY());
		return mousePosition.x >= x && mousePosition.y >= y && mousePosition.x < x + w && mousePosition.y < y + h;
	}

	bool isPress(MouseClient mouse) {
		Vector2 mousePosition = Vector2(mouse.GetMouseX(), mouse.GetMouseY());
		return isHover(mouse) && mouse.LeftIsPressed();
	}

	bool isRelease(MouseClient mouse) {
		if (!mouse.LeftIsPressed()) {
			bool r = depressed;
			r = isHover(mouse) ? r : false;
			depressed = false;
			return r == true;
		}
		return false;
	}

	void RefreshState(MouseClient mouse) {
		if (isPress(mouse)) {
			depressed = true;
		}
	}


};

class Button : public ClickableRectangle {
public:
	Color clr;
	const static int bfsz = 256;
	char text[bfsz];
	FontType* font;
	void (*function)();

	void Draw(Interface* out) {
		int charcnt = strlen(text);
		int textw = charcnt * font->sprite_sheet->wsize;
		float s = (float)w / textw;
		out->paint->rectangle(x, y, w, h, clr, true);

		for (int i = 0; i < 2; i++) {
			out->paint->rectangle(x + i, y + i, w - i * 2, h - i * 2, Colors::Black);
		}

		int textY = y + h / 2 - s * font->sprite_sheet->hsize / 2;
		int textX = x + s * textw*0.1;
		out->PrintText(textX, textY, font, text);

	}

	void RefreshState(MouseClient mouse) {
		this->ClickableRectangle::RefreshState(mouse);
		this->RefreshColors(mouse);
	}



	void RefreshColors(MouseClient mouse) {
		clr = Colors::LightGray;
		if (isHover(mouse)) {
			clr = Colors::Gray;
		}
		if (depressed && isHover(mouse)) {
			clr = Colors::Blue;
		}
	}

	Button(int x, int y, int w, int h, char* src, FontType* font, void (*function)()) : ClickableRectangle(x, y, w, h), font(font), clr(Colors::LightGray) {
		strcpy_s(text, src);
		text[bfsz - 1] = 0;
		this->function = function;
	}




};

extern TrianglePoly* poly;

void ScalePoly20x();
void ScalePoly05x();

void RotatePolyP15();
void RotatePolyN15();
class ButtonManager {
public:
	vector<Button*> buttons;




	void Init() {
		buttons.push_back(new Button(100, 240, 140, 40, "Scale 2.0x", &DOS_BLACK, &ScalePoly20x));
		buttons.push_back(new Button(100, 200, 140, 40, "Scale 0.5x", &DOS_BLACK, &ScalePoly05x));
		buttons.push_back(new Button(100, 280, 140, 40, "Rotate 15*", &DOS_BLACK,  &RotatePolyP15));
		buttons.push_back(new Button(100, 320, 140, 40, "Rotate -15*", &DOS_BLACK, &RotatePolyN15));
	}

	void RefreshState(MouseClient mouse) {
		for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
			(*it)->RefreshState(mouse);
			if ((*it)->isRelease(mouse)) {
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

	ButtonManager() {
		this->Init();
	}


	~ButtonManager(){
		for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
			delete (*it);
		}
	}
};

#endif