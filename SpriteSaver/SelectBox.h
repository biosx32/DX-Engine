#pragma once
#include "Vectors.h"
#include "Element.h"

class SelectBox: public Element  {
public:

	SelectBox(Vector2 p1): Element(p1, Vector2(50,50)) {
	
	}

	Vector2 GetStart() {
		Vector2 pos = GetAbs();
		return Vector2(min(pos.x, pos.x + size.x),
			           min(pos.y, pos.y + size.y));
	}
	Vector2 GetSize() {
		Vector2 pos = GetAbs();
		return Vector2(abs(size.x), abs(size.y));
	}
	Vector2 GetEnd() {
		Vector2 pos = GetAbs();
		return Vector2(max(pos.x, pos.x + size.x),
			max(pos.y, pos.y + size.y));
	}

	void Update() {}

	void Update(Vector2 p2){
		Vector2 pos = GetAbs();
		size = p2 - pos;
	}

	void Draw() {
		if (size.x == 0 && size.y == 0) {
			return;
		}
		this->DrawBorder();
		this->DrawCorners();
		
	
	}
};