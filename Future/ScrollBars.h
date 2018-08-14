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

class VScrollBar : public ScrollBar {
public:
	VScrollBar (Pos pos, Size size): ScrollBar (pos, size) {
	}

	float GetValue () override {
		return (-property.GetAbs ().x + io->mouse->GetMouseX ()) / property.GetSize ().x;
	}

	void Draw () override {
		Vector2 pos = property.GetAbs ();
		Vector2 size = property.GetSize ();
		GFXDraw restricted (draw->gfx, pos, size);

		for (int i = 1; i <= size.x; i++) {
			if (!(i % 4)) {
				draw->paint->FastVLine (pos.x + i, pos.y + size.y / 4, size.y / 2, Colors::Gray);
			}
		}
		draw->paint->rectangleBorder (pos.x, pos.y, size.x, size.y, Colors::Gray, 1);

		draw->paint->rectangleBorder (pos.x, pos.y + size.y /2 , size.x, 0, Colors::Black, 3);
		draw->paint->rectangleBorder (pos.x, pos.y + 3 * size.y / 15, 0, size.y / 1.667, Colors::Black, 2);
		draw->paint->rectangleBorder (pos.x + size.x, pos.y + 3*size.y / 15, 0, size.y / 1.667, Colors::Black, 2);

		int csize = 8; int he = csize / 2;
		int x = pos.x + value * size.x - he;
		int y = pos.y + 1 * size.y / 20;
		int h = size.y / 1.112;
		int w = csize;
		restricted.paint->rectangleBorder (x, y, w,h, Colors::GreenDark, 3);

		string text = sprintfToString ("%s: %1.3f", property.name.c_str (), value);

		int posx = property.GetAbsX () + property.GetSize ().x / 2 - 0.5 * text.size () * property.font->charw * property.fontSize.w;
		int posy = property.GetAbsY () + property.GetSize ().y / 2 - property.font->charh * property.fontSize.h / 2;
		PrintText (draw, V2 (posx, posy-size.h/2), property.font, property.fontSize, text);
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
		GFXDraw restricted (draw->gfx, pos, size);

		for (int i = 1; i <= size.y; i++) {
			if (!(i % 4)) {
				draw->paint->FastHLine (pos.x + size.x / 4, pos.y + i, size.x / 2, Colors::Gray);
			}
		}
		draw->paint->rectangleBorder (pos.x, pos.y, size.x, size.y, Colors::Gray, 1);

		draw->paint->rectangleBorder (pos.x + size.x /2, pos.y, 0, size.y, Colors::Black, 3);
		draw->paint->rectangleBorder (pos.x + 3 * size.x / 15, pos.y,size.x / 1.667,0, Colors::Black, 2);
		draw->paint->rectangleBorder (pos.x + 3 * size.x / 15, pos.y + size.y, size.x / 1.667, 0, Colors::Black, 2);
	
		int csize = 8; int he = csize / 2;
		//int x = pos.x + value * size.x - he;
		int x = pos.x + 1 * size.x / 20;
		int y = pos.y + value * size.y - he;
		int h = csize; ;
		int w = size.x / 1.112;
		restricted.paint->rectangleBorder (x, y, w, h, Colors::GreenDark, 3);

		
		string text = sprintfToString ("%s: %1.3f", property.name.c_str (), value);

		int posx = property.GetAbsX () + property.GetSize ().x / 2 - 0.5 * text.size () * property.font->charw * property.fontSize.w;
		int posy = property.GetAbsY () + property.GetSize ().y / 2 - property.font->charh * property.fontSize.h / 2;
		PrintText (draw, V2 (posx, posy - size.h / 2), property.font, property.fontSize, text);
		

	}
};
