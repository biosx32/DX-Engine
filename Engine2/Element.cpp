
#include "Static.h"
#include "Element.h"

int BaseElement::ElementCount = 0;
IOgroup* BaseElement::io = nullptr;
BitmapFont * BaseElement::DFONT = &DOS_WHITE;
std::vector<BaseElement*> BaseElement::Elements = std::vector<BaseElement*>;