#pragma once
#include "..\Engine2\Vectors.h"
#include "..\Engine2\GlobalObjects.h"
#include "..\Engine2\TestInterface.h"
#include "..\Engine2\ClickableRectangle.h"
#include "ScrollBars.h"
class ListBoxItem {
public:
	std::string text;
	ListBoxItem(std::string ptext) {
		text = ptext;
	}
};

class ListBox: public HelperElement {
public:
	MouseRegion mregion;
	BitmapFont* font = &DOS_WHITE_MINI;
	std::vector<ListBoxItem> items;
	int selectedIndex = -1;
	int offset = 0;

	VScrollBar sc;
	ListBox(Vector2 ppos, Vector2 psize):
		mregion(ppos, Size(psize.x - 15,psize.y)), sc(Pos(ppos.x + psize.x - 15, ppos.y), Size(15, psize.y))
	{
		name = "Empty ListBox";
		pos = ppos; size = psize;
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
		int canDraw = size.y / font->charh;
		return (items.size() > canDraw);
	}

	bool isValidIndex() {
		return selectedIndex >= 0 && selectedIndex < items.size();
	}

	bool isValidIndex(int which) {
		return which >= 0 && which < items.size();
	}

	void Draw(Interface* out) {
		this->DrawBorder(out);
		if (items.size() < 1) {
			this->DrawName(out);
		}

		if (scrollbarvisible()) {
			sc.Draw(out);
			out->PrintText(200, 00, &DOS_BLACK, &std::string("Val: %.2f"), sc.value);
		}

		int drawMax =(size.y + font->charh - 1) / font->charh;
		int offsetRemaining = items.size() - offset;
		for (int i = 0; i < drawMax; i++) {
			int pickIndex = i + offset;
			if (pickIndex >= items.size()) {
				continue;
			}
			out->PrintText(pos.x+5, pos.y+3 + font->charh * i, font, items.at(pickIndex).text);
		}
		if (isValidIndex()) {
			out->paint->rectangleBorder(pos.x, pos.y+3  + selectedIndex * font->charh, size.x-15, font->charh, Colors::Cyan, 2);
		}
	}

	void Update(IOgroup* IOG) {
		mregion.Update(*IOG->mouse);
		sc.Update(IOG);
		if (scrollbarvisible()) {
			offset = items.size() * sc.value;
		}
		else { offset = 0; }
		if (mregion.isHover(*IOG->mouse) && mregion.isPress(*IOG->mouse) && sc.locked == false) {
			IOG->mhelper->Refresh();
			Vector2 rpos = IOG->mhelper->position-pos;
			int yoff = rpos.y - 3;
			int possibleIndex = (yoff / font->charh);
		
		
			if (isValidIndex(possibleIndex)) {
				selectedIndex = possibleIndex;
			}
			else if (possibleIndex > items.size()) {
				selectedIndex = -1;
			}
		}
	}
};