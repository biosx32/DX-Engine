#include "Static.h"
#include "Element.h"

std::vector<BaseElement*> BaseElement::Elements = std::vector<BaseElement*>();
int BaseElement::ElementCount = 0;
IOgroup* BaseElement::io = nullptr;
BitmapFont * BaseElement::DFONT = &DOS_WHITE;
GFXDraw* BaseElement::draw = nullptr;
