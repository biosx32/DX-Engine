#include "BaseElement.h"

void BaseElement::DrawName ()
{

	Vector2 pos = property.GetAbs ();
	Vector2 size = property.size;
	V2 center = GetCenterOf (pos, size);
	PrintTextAlign (draw, center, property.font, property.fontSize, ALIGN_VH, property.name);

}

void BaseElement::DrawBorder ()
{
	Vector2 pos = property.GetAbs ();
	Vector2 size = property.GetSize ();
	draw->paint->FastHLine (pos.x, pos.y, size.x, Colors::GreenLime);
	draw->paint->FastHLine (pos.x, pos.y + size.y, size.x, Colors::GreenLime);
	draw->paint->FastVLine (pos.x, pos.y, size.y, Colors::GreenLime);
	draw->paint->FastVLine (pos.x + size.x, pos.y, size.y, Colors::GreenLime);
}

void BaseElement::DrawCorners ()
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
