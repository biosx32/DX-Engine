#pragma once
#include "Vectors.h"
#include "BaseElement.h"
#include "Func3.h"

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
	BaseElement * parent = nullptr;
	Vector2 offset, size;
	string name = "MOUSE_REGION";

public:

	int state = 0;
	int click_count = 0;
	void(*function)() = nullptr;
	

	MouseRegion (BaseElement* parent, Vector2 offset):parent (parent), offset (offset) {
	}

	MouseRegion (BaseElement* parent, Vector2 offset, V2 size):parent (parent), 
		offset (offset),size(size), const_size(true) {
	}


protected:
	bool const_size = false;



public:
    void Draw();
	void Update ();

	virtual bool isHover ();
	virtual bool isPress ();

	bool IsClick() {
		return click_count > 0;
	}

	bool GetClick() {
		return click_count > 0 ? click_count-- : false;
	}


};







