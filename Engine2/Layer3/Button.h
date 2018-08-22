#pragma once
#include "Layer2.h"
#include "BaseElement.h"
#include "AutoMouseRegion.h"



class Button: public BaseElement, public AutoMouseRegion {
public:

	BitmapFont* DFONT = &DOS_WHITE;
	void(*function)() = nullptr;

	Button(Vector2 position, Vector2 size, void(*function)(), string textsrc) :
		BaseElement ("Button", position,size), AutoMouseRegion(this){
		property.text = textsrc;
		mregion->function = function;
	}

	void Update () {
		mregion->Update ();
	}

};

#include "ImageButton.h"
#include "ColorButton.h"
