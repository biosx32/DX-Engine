#include "Static.h"
#include "BaseElement.h"

int BaseElement::ElementCount = 0;
IOgroup* BaseElement::io = nullptr;
GFXDraw* BaseElement::draw = nullptr;
BitmapFont* BaseElement::DFONT = nullptr;

BaseElement::BaseElement()
{
  property.ID = ElementCount++;
  Container::Elements.push_back(this);
}

