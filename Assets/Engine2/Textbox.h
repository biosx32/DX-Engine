#pragma once
#include "Element.h"
#include "GlobalObjects.h"
class TextBox : public Manageable {
public:
	BitmapFont* font = &DOS_BLACK;
	int wmax;
	char buffer[4096];
	int textsize = 0;
	bool isSelected = false;
	Vector2 size = Vector2(0, 0);
	TextBox(Vector2 pos, int wmax) : Manageable(pos), wmax(wmax) {
		this->size = Size(wmax * font->charw, font->charh);
	}

	inline bool isHover(IoGroup* iog) {
		int mx = iog->mouse->GetMouseX(),
			my = iog->mouse->GetMouseY();
		return mx >= pos.x && my >= pos.y && mx < pos.x + size.x && my < pos.y + size.y;
	}

	inline bool isPress(IoGroup*  iog) {
		return iog->mouse->LeftIsPressed();
	}

	void UpdateIsSelected(IoGroup* iog) {
		if (isPress(iog)) {
			if (isHover(iog)) {
				isSelected = true;
				iog->kbd->FlushBuffers();
			}
			else
			{
				isSelected = false;
			}
		}
	}

	void UpdateCheckKey(IoGroup* iog) {
		KeyboardClient* kbd = iog->kbd;
		char test = kbd->PeekKey();
		char testc = kbd->PeekChar();

		if (test != 0) {

			if (test == VK_BACK) {
				textsize = textsize > 0 ? textsize - 1 : 0;
			}
			else if (testc >= 33 && testc < 127) {
				buffer[textsize++] = testc;
			}
			else if (test == VK_SPACE) {
				buffer[textsize++] = ' ';
			}

			kbd->FlushBuffers();
		}
		textsize = textsize <= wmax ? textsize : wmax;
		this->buffer[textsize] = 0;

	}

	void Update(IoGroup* iog) override {
		UpdateIsSelected(iog);
		if (isSelected) {
			UpdateCheckKey(iog);
		}
		
	}

	void Draw(IoGroup* iog) override {
		const int border = 2;
		iog->out->paint->rectangleBorder(pos.x - border, pos.y, size.x + border*2, size.y, Colors::Black, border);
		iog->out->PrintText(pos.x, pos.y, font, buffer);
		if (this->isSelected) {
			int x = textsize * font->charw;
			iog->out->paint->rectangle(x + pos.x, pos.y, 4, font->charh, Colors::Red);
		}
	
	}
};