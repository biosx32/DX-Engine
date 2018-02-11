#pragma once



class Manager {
public:
	IoGroup* iog = nullptr;
	vector<Manageable*> Items;

	Manager(IoGroup* iog) :iog(iog) {}

	void UpdateOne(Manageable* e) {
		e->Update(iog);
	}
    void DrawOne(Manageable* e) {
		e->Draw(iog);
	}


	void Update() {
		if (!iog) return;
		for (int i = 0; i < Items.size();i++) {
			this->UpdateOne(Items[i]);
		}
	}

	void Draw() {
		if (!iog) return;
		for (int i = 0; i < Items.size(); i++) {
			this->DrawOne(Items[i]);
		}
	}	
	


	void Add(Manageable* item) {
		Items.push_back(item);
	}

	void Remove(Manageable* e) {
		int index = 0;
		for (Manageable* Item : Items) {
			if (e == Item) {
				Items.erase(Items.begin() + index);
			}
			index++;
		}
	}
};