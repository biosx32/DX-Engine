#include "Static.h"
#include "Func3.h"
#include <string>
#include "Vectors.h"

void PrintText(GFXDraw* draw, Vector2 pos, std::string text,BitmapFont font) {

	double rel_pos_x = 0;
	double rel_pos_y = 0;
	float charw = DFONT->charw;
	float charh = DFONT->charh;

	for ( auto it = text.begin() ; it < text.end(); it++)
	{
		char chr = *it;


		if (chr == '\x20') {
			rel_pos_x += charw;
		}

		else if (chr == '\n') { // \\x10
			rel_pos_y += charh;
			rel_pos_x = 0;
		}

		if (chr < DFONT->offset) {
			continue;
		}

		Bitmap* CharBitmap = DFONT->GetCharacterRepr(chr);


		int destx = (int)(x + rel_pos_x);
		int desty = (int)(y + rel_pos_y);


		draw->DrawBitmap(CharBitmap, destx, desty);
		//this->Painter->rectangle(destx, desty, charw, charh, 0xFFFF0000);
		rel_pos_x += charw;
	}


}
}