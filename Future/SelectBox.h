#pragma once
#include "Layer4.h"

class SelectBox: public BaseElement, public HasDefaultMregion  {
public:

	SelectBox(Vector2 pos, V2 size): BaseElement ("SelectBox",pos,size), HasDefaultMregion(this) {
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
		mregion->Update ();
		if (mregion->isLockedByParent()) {
			property.SetRel (property.GetAbs() + BaseElement::io->mhelper->mouseDelta);
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