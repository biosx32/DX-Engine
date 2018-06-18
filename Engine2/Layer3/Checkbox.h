#pragma once
#include "Element.h"
#include "GlobalObjects.h"
#include "MouseRegion.h"

class CheckBox : public ConstructElement
{
public:
	bool checked = false;
	const int radius = 15;
	std::string text = "";
	MouseRegion* mregion = nullptr;

	void Toggle() {
		checked = !checked;
	}

	virtual void Update () {
		mregion->Update ();
		if (mregion->GetClick ()) {
			Toggle ();
		}
	}

	CheckBox(Vector2 position, const char* text): 
		ConstructElement(position, 0)
	{
		this->text = text;
		mregion = new MouseRegion (position, Vector2 (30, 30));
		mregion->property.name = this->text + "_MREGION";
		Vector2 size = Vector2(radius * 2, radius * 2);

	}



	void Draw() override{
		Vector2 pos = property.GetAbs();

		draw->paint->rectangle(pos.x, pos.y, radius * 2, radius * 2, Colors::White);

		if (checked) {
			draw->paint->rectangle(pos.x, pos.y, radius * 2, radius * 2, Colors::GreenDark);
			draw->paint->line(pos.x, pos.y, pos.x + radius * 2, pos.y + radius * 2, Colors::White,2);
			draw->paint->line(pos.x, pos.y + radius * 2, pos.x + radius * 2, pos.y , Colors::White,2);
		}
		else if (mregion->state > MouseState::none) {
			draw->paint->rectangle (pos.x + radius * 0.5, pos.y+ radius * 0.5, radius * 1.25, radius * 1.25, Colors::Green);
		}


		draw->paint->rectangleBorder(pos.x, pos.y, radius * 2, radius * 2, Colors::Black, 3);
		draw->paint->rectangleBorder(pos.x, pos.y, radius * 2, radius * 2, Colors::White, 1);
	

		PrintText(draw,pos.x + radius * 2.34, pos.y + radius /3, text, DFONT);

	}


};