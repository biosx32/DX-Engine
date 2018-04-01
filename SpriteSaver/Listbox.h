#pragma once
#include "..\Engine2\Vectors.h"
#include "..\Engine2\GlobalObjects.h"
#include "..\Engine2\TestInterface.h"
#include "..\Engine2\ClickableRectangle.h"

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
	ListBox(Vector2 ppos, Vector2 psize):
		mregion(ppos,psize)
	{
		name = "ListBox";
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

	bool isValidIndex() {
		return selectedIndex >= 0 && selectedIndex < items.size();
	}

	bool isValidIndex(int which) {
		return which >= 0 && which < items.size();
	}

	void Draw(Interface* out){
		this->DrawBorder(out);
		this->DrawName(out);
		int canDraw = size.y / font->charh;
		for (int i = 0; i < canDraw, i < items.size(); i++) {
			out->PrintText(pos.x+5, pos.y+3 + font->charh * i, font, items.at(i).text);
		}
		if (isValidIndex()) {
			out->paint->rectangleBorder(pos.x, pos.y+3  + selectedIndex * font->charh, size.x, font->charh, Colors::Cyan, 2);
		}
	}

	void Update(IOgroup* IOG) {
		mregion.Update(*IOG->mouse);

		if (mregion.isHover(*IOG->mouse) && mregion.isPress(*IOG->mouse)) {
			IOG->mhelper->Refresh();
			Vector2 rpos = IOG->mhelper->GetPosition()-pos;
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