#pragma once
#include "Layer2.h"

using std::string;

class Label: public BaseElement {
public:
	Label (Vector2 position): 
		BaseElement ("Label",position, 0){}

	Label(Vector2 position, std::string text): 
		BaseElement ("Label",position,0){
		property.text = text;
		}

	void Update() {}
	void Draw() {
		PrintText (draw, property.GetAbs (), property.font, property.fontSize, property.text);
	}

	void SetText (std::string text) {
		property.text = text;
	}

	int GetWidth () {
		return property.font->charw * LongestLineInString(property.text);
	}int GetHeight () {
		return property.font->charh * (1+CharacterCountInString (property.text, '\n'));
	}

};
