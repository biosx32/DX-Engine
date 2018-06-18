#pragma once
#include "Vectors.h"
#include "Mouse.h"
#include "Element.h"
#include "MouseRegion.h"
#include "GlobalObjects.h"



class Button: public ConstructElement {
public:

	BitmapFont* DFONT = &DOS_WHITE;
	void(*function)() = nullptr;
	std::string text = "";
	MouseRegion* mregion = nullptr;

	Button(Vector2 position, Vector2 size, void(*function)(), string textsrc) :
		ConstructElement(position,size), text(textsrc), function(function){
		mregion = new MouseRegion (position, size);
		mregion->function = function;
	}



	virtual void Draw() = 0;
	virtual void Update () {
		mregion->Update ();
	}

};

#include "ImageButton.h"
#include "ColorButton.h"
