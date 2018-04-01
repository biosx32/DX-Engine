#pragma once
#include "..\Engine2\Vectors.h"
#include "..\Engine2\GlobalObjects.h"
#include "..\Engine2\TestInterface.h"
#include "..\Engine2\MouseRegion.h"
#include "ScrollBars.h"
class ListBoxItem {
public:
	std::string text;
	ListBoxItem(std::string ptext) {
		text = ptext;
	}
};

class ListBox: public ElementExtended {
public:
	MouseRegion mregion;
	std::vector<ListBoxItem> items;
	int selectedIndex = -1;
	int offset = 0;

	VScrollBar sc;
	ListBox(Pos ppos, Size psize): ElementExtended(ppos,psize),
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

	void Draw() {
		this->DrawBorder(out);
		if (items.size() < 1) {
			this->DrawName(out);
		}

		if (scrollbarvisible()) {
			sc.Draw();
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
			int drawindex = selectedIndex-offset;
			if (selectedIndex >= offset && selectedIndex < offset + drawMax) {
				out->paint->rectangleBorder(pos.x, pos.y + 3 + drawindex * font->charh, size.x - 15, font->charh, Colors::Cyan, 2);
			}
			
		}
	}

	void Update() {
		mregion.Update();
		sc.Update();
		if (scrollbarvisible()) {
			offset = items.size() * sc.value;
		}
		else { offset = 0; }


		if (mregion.GetRegionState() == RegionState::press) {
			io->mhelper->LockMouse(mregion.ID);
		}

		if (mregion.GetRegionState() == RegionState::release) {
			io->mhelper->FreeMouse();
		}

		if (this->mregion.isPress()) {
	
			

			Vector2 rpos = io->mhelper->position-pos;
			int yoff = rpos.y - 3;
			int possibleIndex = (yoff / font->charh)+offset;
		
		
			if (isValidIndex(possibleIndex)) {
				selectedIndex = possibleIndex;
			}
			else if (possibleIndex > items.size()) {
				selectedIndex = -1;
			}
		}
	}
};