#pragma once
#include "MouseRegion.h"
class MouseRegionVisual : public Element {
	MouseRegionVisual (Vector2 pos, Vector2 size): Element (pos, size) {

	}

	virtual void Update () override {
		Element::Update ();
	}

	virtual void SelfUpdate () override {
		Element::SelfUpdate ();
	}

	virtual void Draw () override {
		mregion->Draw ();

	}



};
