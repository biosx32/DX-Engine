#pragma once
#include "Vectors.h"
#include "Element.h"

class SelectBox: public Element  {
public:

	SelectBox(Vector2 pos, V2 size): Element(pos,size) {
		property.name = "SELECT_BOX";
	}

	Vector2 GetStart() {
		Vector2 pos = property.GetAbs ();
		Vector2 size = property.GetSize ();
		return Vector2(min(pos.x, pos.x + size.x),
			           min(pos.y, pos.y + size.y));
	}
	Vector2 GetSize() {
		return property.GetSize ();
	}
	Vector2 GetEnd() {
		Vector2 pos = property.GetAbs ();
		Vector2 size = property.GetSize ();
		return Vector2(max(pos.x, pos.x + size.x),
			max(pos.y, pos.y + size.y));
	}

	void Update () {
		Element::Update ();
		if (mregion->isLockedByParent()) {
			property.SetRel (property.GetAbs() +Element::io->mhelper->mouseDelta);
		}
	}

	void Draw() {
		Vector2 size = property.GetSize ();
		if (size.x == 0 && size.y == 0) {
			return;
		}
		this->DrawBorder();
		this->DrawCorners();
		mregion->Draw ();
		
	
	}
};