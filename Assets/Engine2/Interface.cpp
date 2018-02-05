#include "Interface.h"



void Interface::PrintText(int x, int y, RasterFont* font, const char *fmt, ...) {
		char buffer[TXT_BUFFER_SIZE];
		va_list args;
		va_start(args, fmt);
		int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);
		va_end(args);
		PrintText(x, y, font, buffer);
}
void Interface::PrintText(int x, int y, RasterFont* font, char * text)
{
	double rel_pos_x = 0;
	double rel_pos_y = 0;


	char buffer[TXT_BUFFER_SIZE];
	strcpy_s(buffer, text);

	for (int i = 0; buffer[i] != 0; i++) {
		char chr = buffer[i];

		float charw = font->charw;
		float charh = font->charh;

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


		int destx = (int)(x + rel_pos_x);
		int desty = (int)(y + rel_pos_y);

		DrawBitmap(CharBitmap, destx, desty);
		//this->Painter->rectangle(destx, desty, charw, charh, 0xFFFF0000);
		rel_pos_x += charw;

	}
}



void Interface::DrawBitmap(Bitmap * Bmp, int xoff, int yoff, float mx, float my)
{
	if (!(mx > 0 && my > 0)) return;

	int width = Bmp->width;
	int height = Bmp->height;
	int draw_width = Bmp->width * mx;
	int draw_height = Bmp->height * my;

	for (int y = 0; y < draw_height; y++) {
		int srcy = y / my;
		for (int x = 0; x < draw_width; x++) {
			int srcx = x / mx;
			Color *pixel = Bmp->GetPixelPointer(srcx, srcy);
			if (!Bmp->GetIsBackground(*pixel)) {
				paint->DrawPixel(xoff + x, yoff + y, *pixel, 1);
			}

		}

	}

}

void Interface::DrawBitmap(Bitmap* Bmp, int fx, int fy) {
	
	for (int yoff = 0; yoff < Bmp->height; yoff++) {
		for (int xoff = 0; xoff < Bmp->width; xoff++) {
			int finalx = fx + xoff;
			int finaly = fy + yoff;
			Color Pixel = *Bmp->GetPixelPointer(xoff, yoff);
			if (!Bmp->GetIsBackground(Pixel)) {
				paint->DrawPixel(finalx, finaly, Pixel);
			}
		}
	}

}






void Interface::DrawSprite(FPixelMap * VBmp, int fx, int fy)
{
	for (std::vector<FPixel*>::iterator it = VBmp->pixels->begin(); it != VBmp->pixels->end(); ++it) {
		paint->DrawPixel(fx + (*it)->x, fy + (*it)->y, (*it)->color);
	}
}


void Interface::FillScreen(Color color)
{
	paint->rectangle(0, 0, SCREENWIDTH - 1, SCREENHEIGHT - 1, color);

}

