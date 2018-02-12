#pragma once

#include "ItemManager.h"
#include "ManageableElement.h"

class GroupBox: public ItemManager, public ManageableElement {

public:
	
	void Draw() override {
		int depth = GetDepth();
		Color colors[] = {Colors::Black, Colors::Red, Colors::Green};
		depth %= sizeof(colors) / sizeof(colors[0]);
		io->out->paint->rectangle(GetPos().x, GetPos().y, size.x, size.y, colors[depth]);

	}

	void Update() override {

	}

	Vector2 size;
	Color bkclr= Colors::Gray;

	void Add(ManageableElement* item) {
		if (item->ID == this->ID) return;
		ItemManager::Add(item);
		item->parent = this;
		item->pDepth = this->pDepth + 1;
	}

	GroupBox(Vector2 pos, Vector2 size): ManageableElement(pos),size(size) {
	}



};
