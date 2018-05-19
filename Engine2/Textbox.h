#pragma once
#include "Element.h"
#include "GlobalObjects.h"

class TextBox : public MouseRegion {
public:
	BitmapFont* DFONT = &DOS_BLACK;
	int wmax;
	char text[4096] = "DEFAULT_TEXT";
	int textsize = 0;
	bool isSelected = false;
	TextBox(Vector2 pos, int wmax) : MouseRegion(pos, Size(0,0)), wmax(wmax) {
		this->size = Size(wmax * DFONT->charw, DFONT->charh);
		this->text[wmax] = 0;
	}

	/*bool isHover()  {
		int mx = mouse->GetMouseX(),
			my = mouse->GetMouseY();
		return mx >= GetAbsolutePos().x && my >= GetAbsolutePos().y && mx < GetAbsolutePos().x + size.x && my < GetAbsolutePos().y + size.y;
	}*/


	void UpdateIsSelected(IOgroup* iog) {
		if (iog->mouse->LeftIsPressed()) {
			if (isHover()) {
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
				textsize = textsize > 0 ? textsize - 1 : 0;
			}
			else if (testc >= 33 && testc < 127) {
				text[textsize++] = testc;
			}
			else if (test == VK_SPACE) {
				text[textsize++] = ' ';
			}

			kbd->FlushBuffers();
		}
		textsize = textsize <= wmax ? textsize : wmax;
		this->text[textsize] = 0;

	}

	void Update() override {
		UpdateIsSelected(io);
		if (isSelected) {
			UpdateCheckKey(io);
		}
		
	}

	void Draw() override {
		const int border = 2;
		io->out->paint->rectangle(GetPos().x - border, GetPos().y, size.x + border * 2, size.y, Colors::White);
		io->out->paint->rectangleBorder(GetPos().x - border, GetPos().y, size.x + border*2, size.y, Colors::Black, border);
		io->out->PrintText(GetPos().x, GetPos().y, DFONT, text);
		if (this->isSelected) {
			int x = textsize * DFONT->charw;
			io->out->paint->rectangle(x + GetPos().x, GetPos().y, 4, DFONT->charh, Colors::Red);
		}
	
	}
};