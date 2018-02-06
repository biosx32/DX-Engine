#pragma once

struct IO_interface {
	Interface* out = nullptr;
	MouseClient* mouse = nullptr;
};


class ManagerBase {
public:
	IO_interface ioif;
	ManagerBase(IO_interface ioif) : ioif(ioif) {}
	virtual void Update() =0;
	virtual void Draw() = 0;
};

template <class T>
class Manager : public ManagerBase {
public:

	typedef T ItemsType;
	vector<ItemsType*> Items;
	using ManagerBase::ManagerBase;

	void Update() override{
		for (int i = 0; i < Items.size();i++) {
			this->UpdateOne(Items[i]);
		}
	}

	void Draw() override {
		for (int i = 0; i < Items.size(); i++) {
			this->DrawOne(Items[i]);
		}
	}	
	
	virtual void UpdateOne(ItemsType* one) = 0;
	virtual void DrawOne(ItemsType* one) = 0;

	void Add(ItemsType* item) {
		Items.push_back(item);
	}

	void Remove(ItemsType* eitem) {
		int index = 0;
		for (ItemsType* Item : Items) {
			if (eitem == Item) {
				Items.erase(Items.begin() + index);
			}
			index++;
		}
	}



};