#include "Static.h"
#include "MouseRegion.h"

void MouseRegion::Draw()
{

  Color c = Colors::Red;

  if (state == MouseState::pressed)
    c = Colors::Green;
  if (state == MouseState::hovered)
    c = Colors::Blue;

  draw->paint->circleBorder(property.GetAbsX() + property.size.x / 2,
                            property.GetAbsY() + property.size.y / 2,
                            property.size.x,
                            c,
                            1);
  draw->paint->circleBorder(property.GetAbsX() + property.size.x / 2,
                            property.GetAbsY() + property.size.y / 2,
                            1 * property.size.x / 3,
                            c,
                            1);

  ConstructElement::Draw();
}