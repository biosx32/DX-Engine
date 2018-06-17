#pragma once

#include "Element.h"

class ItemManager {
public:
	vector<Element*> Items;

	void Add(Element* item) {
		Items.push_back(item);
	}

	void Remove(Element* e) {
		int index = 0;
		for (Element* Item : Items) {
			if (e == Item) {
				Items.erase(Items.begin() + index);
			}
			index++;
		}
	}
};
