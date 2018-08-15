#include "Static.h"
#include "BaseElement.h"

IOgroup* BaseElement::io = nullptr;
GFXDraw* BaseElement::draw = nullptr;
BitmapFont* BaseElement::DFONT = nullptr;

BaseElement::BaseElement(std::string classname)
{
	if (!class_map.count (classname)) {
		this->class_map.insert (std::pair<std::string, int> (classname, 0));
	}
	
  property.ID = class_map.at(classname)++;
  Container::Elements.push_back(this);
}

