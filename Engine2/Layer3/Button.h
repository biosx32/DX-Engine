#pragma once
#include "Layer2.h"
#include "BaseElement.h"
#include "HasDefaultMregion.h"



class Button: public BaseElement, public HasDefaultMregion {
public:

	BitmapFont* DFONT = &DOS_WHITE;
	void(*function)() = nullptr;

	Button(Vector2 position, Vector2 size, void(*function)(), string textsrc) :
		BaseElement ("Button", position,size), HasDefaultMregion(this){
		property.text = textsrc;
		mregion->function = function;
	}

};

#include "ImageButton.h"
#include "ColorButton.h"
