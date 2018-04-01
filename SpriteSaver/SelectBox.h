#pragma once
#include "..\Engine2\Vectors.h"
#include "..\Engine2\TestInterface.h"
#include "..\Engine2\ElementExtended.h"
class SelectBox: public ElementExtended  {
public:

	SelectBox(Vector2 p1):ElementExtended(Pos(p1.x, p1.y), Size(0,0)) {
		pos = p1;
	}

	void Update() {}

	void Update(Vector2 p2){
		size = p2 - pos;
	}

	void Draw() {
		if (size.x == 0 && size.y == 0) {
			return;
		}
		this->DrawBorder(out);
		this->DrawCorners(out);
		
	
	}
};