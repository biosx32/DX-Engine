#pragma once

template <class T>
class Manager {
public:
	vector<T*> Items;
	typename vector<T*>::iterator Iter;

	~Manager() {
		for (T* ItemPtr : Items) {
			delete ItemPtr;
		}
		Items.clear();
	}


	void Add(T item) {
		T* b = &item;
		Items.push_back(b);

	}

	void Remove(T item) {
		T* itemAddr = &item;
		int index = 0;
		for (T* ItemPtr: Items) {
			if (itemAddr == ItemPtr) {
				DebugPrint << "Delete item At: " << index << console;
			}
			index++;
		}
	}

	void Update() {
		for (T* ItemPtr : Items) {
			UpdateOne(*ItemPtr);
		}
	}

	void Draw() {
		for (T* ItemPtr : Items) {
			DrawOne(*ItemPtr);
		}
	}

	virtual void UpdateOne(T one) = 0;
	virtual void DrawOne(T one) = 0;


	Manager() {}


};