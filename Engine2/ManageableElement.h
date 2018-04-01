#pragma once

#include "Element.h"
#include "OutputStream.h"
class ManageableElement : public Element {
protected:
	static int ElementCount;

protected:
	virtual void Update() = 0;
	virtual void Draw() = 0;

public:
	int ID, pDepth;
	ManageableElement* parent = nullptr;
	IOgroup * io = nullptr;

	bool HasParent() {
		return parent != nullptr;
	}

	int GetDepth() {
		if (!HasParent()) { return 0; }
		else { return parent->GetDepth() + 1; }
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
		else { OutputStream() << "No IO group for manageable item" << console; }
	}

	void Draw(IOgroup* io) {
		this->io = io;
		if (io) { Draw(); }
		else { OutputStream() << "No IO group for manageable item" << console; }
	}

	ManageableElement(Vector2 Pos) : Element(Pos), pDepth(0) {
		ID = ElementCount++;
	}
};

