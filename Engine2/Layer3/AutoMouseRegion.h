#pragma once
#include "MouseRegion.h"
#include "BaseElement.h"

class AutoMouseRegion {
public:
	MouseRegion* mregion = nullptr;

	AutoMouseRegion (BaseElement* parent) {
		mregion = new MouseRegion (parent, 0);
	}
};