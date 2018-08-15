#pragma once
#include "Element.h"
#include <string>
#include "BitmapFont.h"
#include "GlobalObjects.h"

using std::string;

class Label: public Element {
public:
	Label (Vector2 position)
		: Element (position, 0)
		
	{
		SetClassName ("Label");
	}
	Label(Vector2 position, std::string text)
          : Element (position,0)
          , text(newtext)
        {
		SetClassName ("Label");
		}

        Label(Vector2 position, const char* newtext, BitmapFont* NFONT)
          : Element (position,0)
          , text(newtext)
        {
			SetClassName ("Label");
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

	int GetWidth () {
		return property.font->charw * LongestLineInString(text);
	}int GetHeight () {
		return property.font->charh * (1+CharacterCountInString (text, '\n'));
	}

};
