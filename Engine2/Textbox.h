#pragma once
#include "Element.h"
#include "GlobalObjects.h"
#include "MouseEventObject.h"
class TextBox : public ManageableElement, public MouseEventObject {
public:
	BitmapFont* font = &DOS_BLACK;
	int wmax;
	char text[4096] = "DEFAULT_TEXT";
	int textsize = 0;
	bool isSelected = false;
	Vector2 size = Vector2(0, 0);
	TextBox(Vector2 pos, int wmax) : ManageableElement(pos), wmax(wmax) {
		this->size = Size(wmax * font->charw, font->charh);
		this->text[wmax] = 0;
	}

	bool isHover(MouseClient* mouse) override {
		int mx = mouse->GetMouseX(),
			my = mouse->GetMouseY();
		return mx >= GetPos().x && my >= GetPos().y && mx < GetPos().x + size.x && my < GetPos().y + size.y;
	}


	void UpdateIsSelected(IOgroup* iog) {
		if (iog->mouse->LeftIsPressed()) {
			if (isHover(iog->mouse)) {
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
		io->out->PrintText(GetPos().x, GetPos().y, font, text);
		if (this->isSelected) {
			int x = textsize * font->charw;
			io->out->paint->rectangle(x + GetPos().x, GetPos().y, 4, font->charh, Colors::Red);
		}
	
	}
};