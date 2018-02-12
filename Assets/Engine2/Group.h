#pragma once

#include "ItemManager.h"
#include "ManageableElement.h"

class GroupBox: public ItemManager, public ManageableElement {

protected:
	void Draw() override {
		io->out->paint->rectangleBorder(GetPos().x, GetPos().y, size.x, size.y, Colors::Red, 2);

	}

	void Update() override {

	}
public:

	Vector2 size;
	Color bkclr= Colors::Gray;

	void Add(ManageableElement* item) {
		if (item->ID == this->ID) return;
		ItemManager::Add(item);
		item->parent = this;
	}

	GroupBox(Vector2 pos, Vector2 size): ManageableElement(pos),size(size) {
	}



};
