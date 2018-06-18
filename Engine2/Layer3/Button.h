#pragma once
#include "Vectors.h"
#include "Mouse.h"
#include "Element.h"
#include "MouseRegion.h"
#include "GlobalObjects.h"



class Button: public Element {
public:

	BitmapFont* DFONT = &DOS_WHITE;
	void(*function)() = nullptr;
	std::string text = "";

	Button(Vector2 position, Vector2 size, void(*function)(), string textsrc) :
		Element (position,size), text(textsrc), function(function){
		mregion->function = function;
	}



	virtual void Draw() = 0;
	virtual void Update () {
		Element::Update ();
	}
	virtual  void SelfUpdate(){}

};

#include "ImageButton.h"
#include "ColorButton.h"
