#pragma once
#include "Element.h"
#include "Vectors.h"
#include "IOgroup.h"

class ScrollBar : public Element {
public:
	float value = 0.0f;
	ScrollBar (Pos pos, Size size): Element (pos, size) {
		property.fontSize = 0.8f;
		property.name = "SB";
	}

	virtual float GetValue () = 0;

	void SelfUpdate () {

		Vector2 pos = property.GetAbs ();

		if (io->mhelper->IsMouseUsedBy (property.ID)) {
			value = GetValue ();
			if (value > 1) { value = 1; }
			else if (value < 0) { value = 0; }
		}
	}

	void Update () {
		Element::Update ();
	}

	void SetValue (float a) {
		this->value = a;
	}

	virtual void Draw () = 0;

};

class VScrollBar: public ScrollBar {
public:
	VScrollBar (Pos pos, Size size): ScrollBar (pos, size) {
	}

	float GetValue () override {
		return (-property.GetAbs ().x + io->mouse->GetMouseX ()) / property.GetSize().x;
	}

	void Draw () override {
		Vector2 pos = property.GetAbs ();
		Vector2 size = property.GetSize ();

		GFXRestDraw restricted (draw->gfx, pos, size);

		restricted.paint->rectangleBorder (pos.x, pos.y, size.x, size.y, Colors::GreenLime, 2);
		restricted.paint->rectangleBorder (pos.x + value * size.x - 10 / 2, pos.y, 10, size.y, Colors::GreenDark, 3);
		restricted.paint->circleBorder (pos.x + value * size.x, pos.y + size.y / 2, size.y / 1.3, Colors::GreenDark, 3);

		string text = sprintfToString ("%s -val: %1.3f",property.name.c_str(),value);

		int posx = property.GetAbsX () + property.GetSize ().x / 2 - 0.5 * text.size () * property.font->charw * property.fontSize.w;
		int posy = property.GetAbsY () + property.GetSize ().y / 2 - property.font->charh * property.fontSize.h /2;
		PrintText (draw, V2 (posx, posy), property.font, property.fontSize, text);

	}
};


class HScrollBar : public ScrollBar {
public:
	HScrollBar (Pos pos, Size size): ScrollBar (pos, size) {
	}

	float GetValue () override {
		return (-property.GetAbs ().y + io->mouse->GetMouseY ()) / property.GetSize ().y;
	}

	void Draw () override {
		Vector2 pos = property.GetAbs ();
		Vector2 size = property.GetSize ();

		GFXRestDraw restricted (draw->gfx, pos, size);

		restricted.paint->rectangleBorder (pos.x, pos.y, size.x, size.y, Colors::GreenLime, 2);

		restricted.paint->rectangleBorder (pos.x , pos.y + value * size.y - 10 / 2, size.x, 10, Colors::GreenDark, 3);
		restricted.paint->circleBorder (pos.x + size.x / 2, pos.y + value * size.y , size.x / 1.3, Colors::GreenDark, 3);

		string text = sprintfToString ("%1.2f", value);

		int posx = property.GetAbsX () + property.GetSize ().x / 2 - 0.5 * text.size()* property.font->charw * property.fontSize.w;
		int posy = property.GetAbsY () + property.GetSize ().y / 2 - 0.5 * property.font->charh * property.fontSize.h;
		PrintText (draw, V2 (posx, posy), property.font, property.fontSize, text);

	}
};
