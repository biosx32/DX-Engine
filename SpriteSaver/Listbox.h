#pragma once
#include "Static.h"
#include "Vectors.h"
#include "ElementExtended.h"
#include "GlobalObjects.h"
#include "MouseRegion.h"
#include "ScrollBars.h"
#include <string>
class ListBoxItem {
public:
	std::string text;
	ListBoxItem(std::string ptext) {
		text = ptext;
	}
};

class ListBox: public Element {
public:
	MouseRegion mregion;
	std::vector<ListBoxItem> items;
	int selectedIndex = -1;
	int offset = 0;

	BitmapFont* DFONT = &DOS_BLACK_MINI;

	VScrollBar sc;
	ListBox(Pos ppos, Size psize): Element(ppos,psize),
		mregion(ppos, Size(psize.x - 15,psize.y)), sc(Pos(ppos.x + psize.x - 15, ppos.y), Size(15, psize.y))
	{
		name = "Empty ListBox";
	}

	void Add(std::string item) {
		ListBoxItem temp = ListBoxItem(item);
		items.push_back(temp);
	}
	void DeleteSelected() {
		if (isValidIndex()) {
			items.erase(items.begin() + selectedIndex);
		}
		
		selectedIndex = -1;
	}
	bool scrollbarvisible() {
		int canDraw = size.y / DFONT->charh;
		return (items.size() > canDraw);
	}

	bool isValidIndex() {
		return selectedIndex >= 0 && selectedIndex < items.size();
	}

	bool isValidIndex(int which) {
		return which >= 0 && which < items.size();
	}

	void Draw() {
		Vector2 pos = GetAbs();
		this->DrawBorder();
		if (items.size() < 1) {
			this->DrawName();
		}

		if (scrollbarvisible()) {
			sc.Draw();
			io->out->PrintText(200, 00, &DOS_BLACK, std::string("Val: %.2f"), sc.value);
		}

		int drawMax =(size.y + DFONT->charh - 1) / DFONT->charh;
		int offsetRemaining = items.size() - offset;
		for (int i = 0; i < drawMax; i++) {
			int pickIndex = i + offset;
			if (pickIndex >= items.size()) {
				continue;
			}
			io->out->PrintText(pos.x+5, pos.y+3 + DFONT->charh * i, DFONT, items.at(pickIndex).text);
		}
		if (isValidIndex()) {
			int drawindex = selectedIndex-offset;
			if (selectedIndex >= offset && selectedIndex < offset + drawMax) {
				io->out->paint->rectangleBorder(pos.x, pos.y + 3 + drawindex * DFONT->charh, size.x - 15, DFONT->charh, Colors::Cyan, 2);
			}
			
		}
	}


	void Update() {
		mregion.Update();
		sc.Update();
		if (scrollbarvisible()) {
			offset = items.size() * sc.value;
			if (this->mregion.isHover()) {
				float piece = 1.0f / items.size();
				if (io->mouse->WheelUp() &&  sc.value - piece>= 0) {
					sc.SetValue(sc.value - piece);

				}

				if (io->mouse->WheelDown() && sc.value + piece <= 1) {
					sc.SetValue(sc.value + piece);
				}

			}
		}
		else { offset = 0; }

		mregion.Update();

		if (this->mregion.isPress()) {
	
			Vector2 pos = GetAbs();

			Vector2 rpos = io->mhelper->position-pos;
			int yoff = rpos.y - 3;
			int possibleIndex = (yoff / DFONT->charh)+offset;
		
		
			if (isValidIndex(possibleIndex)) {
				selectedIndex = possibleIndex;
			}
			else if (possibleIndex > items.size()) {
				selectedIndex = -1;
			}
		}
	}
};