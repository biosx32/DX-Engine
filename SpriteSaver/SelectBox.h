#pragma once
#include "..\Engine2\Vectors.h"
#include "..\Engine2\TestInterface.h"
#include "HelperElement.h"
class SelectBox: public HelperElement {
public:

	SelectBox(Vector2 p1) {
		pos = p1;
	}

	void Update(Vector2 p2){
		size = p2 - pos;
	}

	void Draw(Interface* out) {
		if (size.x < 0 && size.y < 0) {
			return;
		}
		this->DrawBorder(out);
		this->DrawCorners(out);
		
	
	}
};