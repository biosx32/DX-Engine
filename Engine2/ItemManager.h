#pragma once

#include "ManageableElement.h"

class ItemManager {
public:
	vector<ManageableElement*> Items;

	void Add(ManageableElement* item) {
		Items.push_back(item);
	}

	void Remove(ManageableElement* e) {
		int index = 0;
		for (ManageableElement* Item : Items) {
			if (e == Item) {
				Items.erase(Items.begin() + index);
			}
			index++;
		}
	}
};
