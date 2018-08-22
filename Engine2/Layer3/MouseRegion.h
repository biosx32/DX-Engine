#pragma once
#include "Layer2.h"
#include "BaseElement.h"


namespace MouseState {
	enum Type
	{
		none = 0,
		hovered = 1,
		pressed = 2
	};
}

class MouseRegion {
public:
	static int _IDC;
	BaseElement * parent = nullptr;
	BitmapFont* DFONT = &DOS_BLACK;
	Vector2 offset, size;
	string name = "MOUSE_REGION";
	int ID;

public:

	int statesave = 0;
	int click_count = 0;
	void (*function)() = nullptr;


	MouseRegion (BaseElement* parent, Vector2 offset): parent (parent), offset (offset), ID (_IDC++) {
	}

	MouseRegion (BaseElement* parent, Vector2 offset, V2 size): parent (parent), offset (offset),
		size (size), const_size (true), ID (_IDC++) {

	}


protected:
	bool const_size = false;



public:
	void Draw ();
	void Update ();


	virtual bool isHover ();
	virtual bool isPress ();


	bool IsClick () {
		return click_count > 0;
	}

	bool GetClick () {
		return click_count > 0 ? click_count-- : false;
	}

	bool isLockedOn () {
		return BaseElement::io->mhelper->IsMouseUsedBy (this->ID);
	}

	Vector2 GetStartPos () {
		return parent->property.GetAbs () - size / 2 + offset;
	}

};







