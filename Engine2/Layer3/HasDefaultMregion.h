#pragma once
#include "MouseRegion.h"
#include "BaseElement.h"

class HasDefaultMregion {
public:
	MouseRegion* mregion = nullptr;

	HasDefaultMregion (BaseElement* parent) {
		mregion = new MouseRegion (parent, 0, parent->property.GetSize ());
	}
};