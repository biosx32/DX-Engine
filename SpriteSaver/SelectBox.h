#pragma once
#include "..\Engine2\Vectors.h"
#include "..\Engine2\TestInterface.h"
class SelectBox {
public:
	Vector2 pos;
	Vector2 size;

	SelectBox(Vector2 p1) {
		pos = p1;
	}

	void Update(Vector2 p2){
		size = p2 - pos;
	}

	void Draw(Interface* out) {
		int fl = 5; //box size;
		int of = -fl / 2; // offset

		out->paint->FastHLine(pos.x, pos.y, size.x, Colors::GreenLime);
		out->paint->FastHLine(pos.x, pos.y + size.y, size.x, Colors::GreenLime);
		out->paint->FastVLine(pos.x, pos.y, size.y, Colors::GreenLime);
		out->paint->FastVLine(pos.x + size.x, pos.y, size.y, Colors::GreenLime);

		out->paint->rectangle(of+pos.x, of + pos.y, fl, fl, Colors::Blue);
		out->paint->rectangle(of + pos.x, of + pos.y + size.y, fl, fl, Colors::Blue);
		out->paint->rectangle(of + pos.x + size.x, of + pos.y, fl, fl, Colors::Blue);
		out->paint->rectangle(of + pos.x + size.x, of + pos.y + size.y, fl, fl, Colors::Blue);
		
	
	}
};