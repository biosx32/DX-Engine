#pragma once

template <class T>
class Manager {
public:
	typedef T MTYPE;

	vector<T> items;
	typename vector<T>::iterator Iter;

	void Add(T btn) {
		items.push_back(btn);
	}

	void Update() {
		for (std::vector<T>::iterator it = items.begin(); it != items.end(); ++it) {
			UpdateOne(*it);
		}
	}

	void Draw() {
		for (std::vector<T>::iterator it = items.begin(); it != items.end(); ++it) {
			DrawOne(*it);
		}
	}

	virtual void UpdateOne(T one) = 0;
	virtual void DrawOne(T one) = 0;


	Manager() {}

	~Manager() {
		for (std::vector<T>::iterator it = items.begin(); it != items.end(); ++it) {
			delete (*it);
		}
	}

};