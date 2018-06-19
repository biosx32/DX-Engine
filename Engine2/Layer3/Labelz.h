#pragma once
#include "Element.h"
#include <string>
#include "BitmapFont.h"
#include "GlobalObjects.h"

using std::string;

class Label: public Element {
public:
	string text = "THANOS_SNAPS_HIS_FINGERS";

	Label(Vector2 position, const char* newtext)
          : Element (position,0)
          , text(newtext)
        {}

        Label(Vector2 position, const char* newtext, BitmapFont* NFONT)
          : Element (position,0)
          , text(newtext)
        {
			property.font = (NFONT);
		}

	void Update() {}
	void Draw() {
		PrintText (draw, property.GetAbs (), property.font, property.fontSize, text);
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
