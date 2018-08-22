#pragma once
#include "BaseElement.h"
#include "GlobalObjects.h"
#include "MouseRegion.h"
#include "AutoMouseRegion.h"

class CheckBox : public BaseElement, public AutoMouseRegion
{
public:
	bool checked = false;
	static const int radius = 12;


	void Toggle() {
		checked = !checked;
	}

	virtual void Update () {
		if (mregion->GetClick ()) {
			Toggle ();
		}
	}

	virtual void SelfUpdate () {
	
	}

	CheckBox(Vector2 position, string text): 
		BaseElement("Checkbox",position, radius * 2),AutoMouseRegion(this)
	{
		property.fontSize = .85f;
		property.text = text;

	}



	void Draw() override{
		Vector2 pos = property.GetAbs();
		
		draw->paint->rectangle(pos.x, pos.y, radius * 2, radius * 2, Colors::White);

		if (checked) {
			draw->paint->rectangle(pos.x, pos.y, radius * 2, radius * 2, Colors::GreenDark);
			draw->paint->line(pos.x, pos.y, pos.x + radius * 2-1, pos.y + radius * 2-1 , Colors::White,1);
			draw->paint->line(pos.x, pos.y + radius * 2-1, pos.x + radius * 2 -1, pos.y , Colors::White,1);
		}
		if (mregion->statesave > MouseState::none) {
			int bit = radius * 0.45;
			draw->paint->rectangle (pos.x + bit, pos.y + bit, radius*2 - bit*1.5, radius * 2 - bit*1.6, Colors::Green);
		}

		draw->paint->rectangleBorder (pos.x, pos.y, radius * 2, radius * 2, Colors::Black, 3);
		draw->paint->rectangleBorder (pos.x, pos.y, radius * 2, radius * 2, Colors::White, 1);

	
		
		PrintText(draw, Pos(pos.x + radius * 2.34, pos.y + radius - property.font->charh*property.fontSize.h/2 ), 
			property.font,property.fontSize, property.text);
	}


};