#pragma once
#include "BaseElement.h"
#include "Func3.h" //FOR PRINT TEXT
#include "MouseRegion.h"


class Element : public BaseElement
{
public:

	MouseRegion* mregion = nullptr;

	Element (Vector2 pos, Vector2 size)
	{
		property.SetRel (pos);
		property.SetSize (size);
		mregion = new MouseRegion (static_cast<BaseElement*>(this), 0);
		
	}

	void DrawBasic () { DrawName (); DrawBorder (); DrawCorners (); }
	virtual void Draw () override;
	void Update ();

protected:
	void DrawName ();
	void DrawBorder ();
	void DrawCorners ();
};



