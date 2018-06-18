#pragma once
#include <vector>

class Container {
public:
	friend class BaseElement;
	static std::vector<BaseElement*> Elements;

	

	static void FullUpdate ();
	static void FullDraw ();
};
#include "BaseElement.h"
