#include "Static.h"
#include "Func3.h"

void PrintText(GFXDraw* draw, Vector2 pos, std::string text,BitmapFont* font) {

	double rel_pos_x = 0;
	double rel_pos_y = 0;
	float charw = font->charw;
	float charh = font->charh;

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

		if (chr < font->offset) {
			continue;
		}

		Bitmap* CharBitmap = font->GetCharacterRepr(chr);


		int destx = (int)(pos.x + rel_pos_x);
		int desty = (int)(pos.y + rel_pos_y);


		draw->DrawBitmap(CharBitmap, destx, desty);
		//this->Painter->rectangle(destx, desty, charw, charh, 0xFFFF0000);
		rel_pos_x += charw;
	}

}

void PrintText (GFXDraw * draw, int x, int y, std::string text, BitmapFont * font) {
	Vector2 pos = Vector2 (x, y);
	PrintText (draw, pos, text, font);
}
