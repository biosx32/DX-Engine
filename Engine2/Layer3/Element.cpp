#include "Static.h"
#include "Element.h"


void Element::Draw ()
{
	DrawName ();
	DrawBorder ();
	DrawCorners ();
}

void Element::SelfUpdate ()
{
}


void Element::Update ()
{
	mregion->Update ();
}

void Element::DrawName ()
{

	Vector2 pos = property.GetAbs ();
	Vector2 size = property.size;

	Vector2 lpos =
		Pos (pos.x + size.x / 2 - DFONT->charw * property.name.size () / 2,
			pos.y + size.y / 2 - DFONT->charh / 2);
	PrintText (draw, lpos, property.name, DFONT);
}

void
Element::DrawBorder ()
{
	Vector2 pos = property.GetAbs ();
	Vector2 size = property.GetSize ();
	draw->paint->FastHLine (pos.x, pos.y, size.x, Colors::GreenLime);
	draw->paint->FastHLine (pos.x, pos.y + size.y, size.x, Colors::GreenLime);
	draw->paint->FastVLine (pos.x, pos.y, size.y, Colors::GreenLime);
	draw->paint->FastVLine (pos.x + size.x, pos.y, size.y, Colors::GreenLime);
}

void
Element::DrawCorners ()
{
	int fl = 6;       // box size;
	int of = -fl / 2; // offset
	Vector2 pos = property.GetAbs ();
	Vector2 size = property.GetSize ();
	draw->paint->rectangle (of + pos.x, of + pos.y, fl, fl, Colors::Blue);
	draw->paint->rectangle (of + pos.x, of + pos.y + size.y, fl, fl, Colors::Blue);
	draw->paint->rectangle (of + pos.x + size.x, of + pos.y, fl, fl, Colors::Blue);
	draw->paint->rectangle (
		of + pos.x + size.x, of + pos.y + size.y, fl, fl, Colors::Blue);
}
