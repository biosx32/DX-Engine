#pragma once

#include "Element.h"
class ManageableElement : public Element {
protected:
	static int ElementCount;

protected:
	virtual void Update() = 0;
	virtual void Draw() = 0;

public:
	int ID;
	ManageableElement* parent = nullptr;
	IOgroup * io = nullptr;

	inline bool HasParent() {
		return parent != nullptr;
	}

	Vector2 GetPos() {
		if (this->HasParent()) {
			return this->rel_pos + parent->GetPos();
		}
		else {
			return rel_pos;
		}
	}

	void Update(IOgroup* io) {
		this->io = io;
		if (io) { Update(); }
	}

	void Draw(IOgroup* io) {
		this->io = io;
		if (io) { Draw(); }
	}

	ManageableElement(Vector2 Pos) : Element(Pos) {
		ID = ElementCount++;
	}
};

