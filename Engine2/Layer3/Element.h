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
		mregion = new MouseRegion (static_cast<BaseElement*>(this), 0);
		property.SetRel (pos);
		property.SetSize (size);
	}

	void DrawName ();
	void DrawBorder ();
	void DrawCorners ();

	virtual void Draw () override;
	virtual void SelfUpdate () override;
	virtual void Update () override;


};



