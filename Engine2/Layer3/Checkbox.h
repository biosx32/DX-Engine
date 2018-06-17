#pragma once
#include "Element.h"
#include "GlobalObjects.h"
#include "MouseRegion.h"

class CheckBox : public BaseElement, public PosElement {
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
		PosElement(position)
	{
		this->text = text;
		mregion = new MouseRegion (position, Vector2 (30, 30));
		mregion->name = "";
		Vector2 size = Vector2(radius * 2, radius * 2);

	}



	void Draw() {
		Vector2 pos = GetAbs();

		draw->paint->rectangle(pos.x, pos.y, radius * 2, radius * 2, Colors::White);
		if (checked) {
			draw->paint->rectangle(pos.x, pos.y, radius * 2, radius * 2, Colors::GreenDark);
			draw->paint->line(pos.x, pos.y, pos.x + radius * 2, pos.y + radius * 2, Colors::White,2);
			draw->paint->line(pos.x, pos.y + radius * 2, pos.x + radius * 2, pos.y , Colors::White,2);

		
		}
		draw->paint->rectangleBorder(pos.x, pos.y, radius * 2, radius * 2, Colors::Black, 3);
		draw->paint->rectangleBorder(pos.x, pos.y, radius * 2, radius * 2, Colors::White, 1);
	

		PrintText(draw,pos.x + radius * 2.34, pos.y + radius /3, text, DFONT);
		mregion->Draw ();

	}


};