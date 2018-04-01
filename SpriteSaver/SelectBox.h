#pragma once
#include "..\Engine2\Vectors.h"
#include "..\Engine2\TestInterface.h"
#include "..\Engine2\ElementExtended.h"
class SelectBox: public ElementExtended  {
public:

	SelectBox(Vector2 p1):ElementExtended(Pos(p1.x, p1.y), Size(0,0)) {
		pos = p1;
	}

	Vector2 GetStart() {
		return Vector2(min(pos.x, pos.x + size.x),
			min(pos.y, pos.y + size.y));
	}
	Vector2 GetSize() {
		return Vector2(abs(size.x), abs(size.y));
	}
	Vector2 GetEnd() {
		return Vector2(max(pos.x, pos.x + size.x),
			max(pos.y, pos.y + size.y));
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