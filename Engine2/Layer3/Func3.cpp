#include "Static.h"
#include "Func3.h"

void PrintText(GFXDraw* draw, Vector2 pos, BitmapFont* font, Size scale, std::string text) {
	
	double rel_pos_x = 0;
	double rel_pos_y = 0;
	float charw = font->charw * scale.x;
	float charh = font->charh * scale.y;

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


		draw->DrawBitmap(CharBitmap, destx, desty, scale.w, scale.h);
		//draw->paint->rectangleBorder(destx, desty, charw*scale.w, charh*scale.h, 0xFF00FFFF,1);
		rel_pos_x += charw;
	}

}

void PrintText (GFXDraw * draw, Vector2 pos, BitmapFont* font, Size scale, const char *fmt, ...) {
	va_list args;
	va_start (args, fmt);
	const int size = 32768;
	char buffer[size];
	int rc = vsnprintf (buffer, size - 1, fmt, args);
	std::string text = string (buffer);
	va_end (args);
	PrintText (draw, pos, font, scale, text);
}