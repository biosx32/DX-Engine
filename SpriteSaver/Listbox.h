#pragma once
#include "..\Engine2\Vectors.h"
#include "..\Engine2\GlobalObjects.h"
#include "..\Engine2\TestInterface.h"

class ListBoxItem {public:
	std::string text;
	ListBoxItem(std::string ptext) {
		text = ptext;
	}
};

class ListBox: public HelperElement {
public:
	std::string name = "ListBox";
	BitmapFont* font = &DOS_WHITE;
	std::vector<ListBoxItem> items;
	ListBox(Vector2 ppos, Vector2 psize) {
		pos = ppos; size = psize;
	}

	void Add(std::string item) {
		ListBoxItem temp = ListBoxItem(item);
		items.push_back(temp);
	}
	void DeleteAt(int index) {
		items.erase(items.begin() + index);
	}

	void Draw(Interface* out){
		this->DrawBorder(out);
		this->DrawName(out);
		int canDraw = size.y / font->charh;
		for (int i = 0; i < canDraw, items.size()>0; i++) {
			out->PrintText(pos.x, pos.y + font->charh * i, font, items.at(i).text);
		}
	}
};