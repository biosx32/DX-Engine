#pragma once
#include "Element.h"
#include <string>
#include "BitmapFont.h"
#include "GlobalObjects.h"

using std::string;

class Label: public BaseElement, public PosElement {
public:
	string text = "";
	BitmapFont* DFONT = &DOS_BLACK;
	
	Label(Vector2 position, const char* newtext): PosElement(position), text(newtext) {	}
	Label(Vector2 position, const char* newtext, BitmapFont* DFONT) : PosElement(position), text(newtext), DFONT(DFONT) {}

	void Update() {}
	void Draw() {
		
		PrintText (draw, GetAbs (), text, DFONT);
	}




	void SetText(const char *fmt, ...){
		va_list args;
		va_start(args, fmt);
		const int size = 32768;
		char buffer[size];
		int rc = vsnprintf(buffer, size - 1, fmt, args);
		text = string(buffer);
		va_end(args);
	}
};
