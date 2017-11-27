#include "Interface.h"

void Interface::set_graphics(Graphics* gfx) { 
	this->gfx = gfx; 
	if (gfx != nullptr) {
		Graphics_loaded = YES;
	}
}
void Interface::DrawPixel(int xoff, int yoff, Color c) { 
	if (!(Graphics_loaded == YES)) {
		return;
	}
	gfx->PutPixel(xoff, yoff, c);
	
}


void Interface::DrawLabel(int xoff, int yoff, Label * label)
{
	double rel_pos_x = 0;
	double rel_pos_y = 0;



	int char_width = label->Get_Bitmap_Char(0)->BitmapData->width;
	int char_height = label->Get_Bitmap_Char(0)->BitmapData->height;

	char* ptr = &label->text[0];

	while (*ptr++ != 0) {
		
		Bitmap* BitmapChar = label->Get_Bitmap_Char(*(ptr - 1));
		char_width = BitmapChar->BitmapData->width;

		if (*(ptr - 1) == '\n') {
			rel_pos_y += char_height;
			rel_pos_x = 0;
			continue;
		}

		Draw_Bitmap(BitmapChar, rel_pos_x + xoff, rel_pos_y + yoff);
		
		if (true) {
			rel_pos_x += char_width * 0.65;
		
			if (*ptr >= '0' && *ptr <= '9') {
				rel_pos_x += char_width * 0.20;
			}
			else if (*ptr >= 'A' && *ptr <= 'Z') {
				rel_pos_x += char_width * 0.05;
			}
		}
	}
}



void Interface::Draw_Bitmap(Bitmap* BitmapChar, int fx, int fy) {
	Color READ_COLOR;
	for (int yoff = 0; yoff < BitmapChar->BitmapData->height; yoff++) {
		for (int xoff = 0; xoff < BitmapChar->BitmapData->width; xoff++) {

			READ_COLOR = BitmapChar->BitmapData->ptr[yoff* BitmapChar->BitmapData->width + xoff];
			if (!BitmapChar->IsColorTransparent(READ_COLOR)) {
				DrawPixel(xoff + fx , yoff + fy, READ_COLOR);
			}

			
		}
	}
}
