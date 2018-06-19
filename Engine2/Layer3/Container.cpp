#include "Static.h"
#include "Container.h"

std::vector<BaseElement*> Container::Elements;



void Container::FullDraw ()
{
	{
		for (int i = 0; i < Elements.size (); i++) {
			if (Elements.at (i)->property.visible) { 
				Elements.at (i)->Draw (); 
			};
		}
	}
}
void Container::FullUpdate ()
{
		
		for (int i = 0; i < Elements.size (); i++) { Elements.at (i)->AutoUpdate(); }
		BaseElement::io->UpdateIO ();
}


