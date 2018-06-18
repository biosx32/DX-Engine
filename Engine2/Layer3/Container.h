#pragma once
#include <vector>


class Container {
public:
	friend class Element;
	static std::vector<Element*> Elements;

	

	static void FullUpdate ();
	static void FullDraw ();
};
#include "Element.h"
