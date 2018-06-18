
#include "Element.h"
#include "Static.h"

int Element::ElementCount = 0;
IOgroup* Element::io = nullptr;
GFXDraw* Element::draw = nullptr;

void ConstructElement::Draw()
{
      DrawName();
      DrawBorder();
      DrawCorners();
}

void ConstructElement::Update()
{
}

void ConstructElement::DrawName()
{
  Vector2 pos = property.GetAbs();
  Vector2 size = property.size;

  Vector2 lpos =
    Pos(pos.x + size.x / 2 - DFONT->charw * property.name.size() / 2,
        pos.y + size.y / 2 - DFONT->charh / 2);
  PrintText(draw, lpos, property.name, DFONT);
}

void
ConstructElement::DrawBorder()
{
  Vector2 pos = property.GetAbs();
  Vector2 size = property.GetSize();
  draw->paint->FastHLine(pos.x, pos.y, size.x, Colors::GreenLime);
  draw->paint->FastHLine(pos.x, pos.y + size.y, size.x, Colors::GreenLime);
  draw->paint->FastVLine(pos.x, pos.y, size.y, Colors::GreenLime);
  draw->paint->FastVLine(pos.x + size.x, pos.y, size.y, Colors::GreenLime);
}

void
ConstructElement::DrawCorners()
{
  int fl = 6;       // box size;
  int of = -fl / 2; // offset
  Vector2 pos = property.GetAbs();
  Vector2 size = property.GetSize();
  draw->paint->rectangle(of + pos.x, of + pos.y, fl, fl, Colors::Blue);
  draw->paint->rectangle(of + pos.x, of + pos.y + size.y, fl, fl, Colors::Blue);
  draw->paint->rectangle(of + pos.x + size.x, of + pos.y, fl, fl, Colors::Blue);
  draw->paint->rectangle(
    of + pos.x + size.x, of + pos.y + size.y, fl, fl, Colors::Blue);
}
Element::Element()
{
  property.ID = ElementCount++;
  Container::Elements.push_back(this);
}

#include "GlobalObjects.h"
BitmapFont* Element::DFONT = &DOS_WHITE;