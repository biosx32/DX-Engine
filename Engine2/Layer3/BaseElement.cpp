#include "BaseElement.h"

IOgroup* BaseElement::io = nullptr;
GFXDraw* BaseElement::draw = nullptr;

std::map<std::string, int> BaseElement::class_map = std::map<std::string,int>();

BaseElement::BaseElement(std::string classname): BaseElement(classname, 0, 25)
{
	
}

BaseElement::BaseElement (std::string classname, V2 pos, Vector2 size)
{
	property.SetRel (pos);
	property.SetSize (size);

	if (!class_map.count (classname)) { 
		//Add counter for this class name if it doesn't exist already
		this->class_map.insert (std::pair<std::string, int> (classname, 0));
	}

	property.ID = class_map.at (classname)++;
	property.class_name = classname;
	property.name = FormatString ("%s%d",property.class_name, property.ID);
	Container::Elements.push_back (this);
}
