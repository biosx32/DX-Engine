#pragma once
#include "Element.h"
#include <string>
using std::string;
#include "BitmapFont.h"
#include "GlobalObjects.h"

class Label: public Element {
public:
	string text = "";
	BitmapFont* DFONT = &DOS_BLACK;

	Label(Vector2 position, const char* newtext): Element(position), text(newtext) {	}
	Label(Vector2 position, const char* newtext, BitmapFont* DFONT) : Element(position), text(newtext), DFONT(DFONT) {}

	void Update() {}
	void Draw() {
		io->out->PrintText(this->pos.x, this->pos.y, this->DFONT, this->text);
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
