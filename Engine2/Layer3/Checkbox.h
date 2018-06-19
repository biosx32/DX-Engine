#pragma once
#include "Element.h"
#include "GlobalObjects.h"
#include "MouseRegion.h"

class CheckBox : public Element
{
public:
	bool checked = false;
	static const int radius = 12;
	std::string text = "";

	void Toggle() {
		checked = !checked;
	}

	virtual void Update () {
		Element::Update ();
	
	}

	virtual void SelfUpdate () {
		if (mregion->GetClick ()) {
			Toggle ();
		}
	}

	CheckBox(Vector2 position, string text): 
		Element(position, radius * 2), text(text)
	{
		property.name = "Some checkbox";
	}



	void Draw() override{
		Vector2 pos = property.GetAbs();
		
		draw->paint->rectangle(pos.x, pos.y, radius * 2, radius * 2, Colors::White);

		if (checked) {
			draw->paint->rectangle(pos.x, pos.y, radius * 2, radius * 2, Colors::GreenDark);
			draw->paint->line(pos.x, pos.y, pos.x + radius * 2, pos.y + radius * 2, Colors::White,3);
			draw->paint->line(pos.x, pos.y + radius * 2, pos.x + radius * 2, pos.y , Colors::White,4);
		}
		else if (mregion->state > MouseState::none) {
			int bit = radius * 0.45;
			draw->paint->rectangle (pos.x + bit, pos.y + bit, radius*2 - bit*1.5, radius * 2 - bit*1.6, Colors::Green);
		}


		draw->paint->rectangleBorder(pos.x, pos.y, radius * 2, radius * 2, Colors::Black, 3);
		draw->paint->rectangleBorder(pos.x, pos.y, radius * 2, radius * 2, Colors::White, 1);
	
		PrintText(draw, Pos(pos.x + radius * 2.34, pos.y + radius /3), property.font,property.fontSize, text);
	}


};