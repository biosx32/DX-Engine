#pragma once
#include "Layer2.h"
#include "BaseElement.h"
#include "AutoMouseRegion.h"

class TextBox : public BaseElement, public AutoMouseRegion {
public:
	int wmax;
	bool isSelected = false;
	TextBox(Vector2 pos, int wmax): BaseElement("TextBox", pos, 0), AutoMouseRegion(this) {
		this->wmax = wmax;
		
	}

	/*bool isHover()  {
		int mx = mouse->GetMouseX(),
			my = mouse->GetMouseY();
		return mx >= GetAbsolutePos().x && my >= GetAbsolutePos().y && mx < GetAbsolutePos().x + size.x && my < GetAbsolutePos().y + size.y;
	}*/


	void UpdateIsSelected(IOgroup* iog) {
		if (iog->mouse->LeftIsPressed()) {
			if (mregion->isHover()) {
				isSelected = true;
				iog->kbd->FlushBuffers();
			}
			else
			{
				isSelected = false;
			}
		}
	}

	void UpdateCheckKey(IOgroup* iog) {
		KeyboardClient* kbd = iog->kbd;
		char test = kbd->PeekKey();
		char testc = kbd->PeekChar();

		if (test != 0) {

			if (test == VK_BACK) {
				property.text.pop_back ();
			}
			else if (testc >= 33 && testc < 127) {
				property.text += testc;
			}
			else if (test == VK_SPACE) {
				property.text += ' ';
			}

			kbd->FlushBuffers();
		}

		property.text = property.text.substr (0,wmax);

	}

	void Update() override {
		property.size = (wmax * property.font->charw, property.font->charh);
		mregion->size = property.size;

		UpdateIsSelected(io);
		if (isSelected) {
			UpdateCheckKey(io);
		}
		
	}

	void Draw() override {
		const int border = 2;
		Vector2 pos = property.GetAbs ();
		V2 size = property.GetSize ();
		draw->paint->rectangle(pos.x - border, pos.y, size.x + border * 2, size.y, Colors::White);
		draw->paint->rectangleBorder(pos.x - border, pos.y, size.x + border*2, size.y, Colors::Black, border);
		PrintText(draw, pos, property.font,property.fontSize, property.text);
		if (this->isSelected) {
			int x = property.text.size() * property.font->charw;
			draw->paint->rectangle(x + pos.x, pos.y, 4, property.font->charh, Colors::Red);
		}
	
	}
};