#include "Interface.h"

void Interface::set_graphics(Graphics* gfx) { 
	this->gfx = gfx; 
	if (gfx != nullptr) {
		Graphics_loaded = YES;
	}
}
void Interface::DrawPixel(int x, int y, Color c) { 
	if (!(Graphics_loaded == YES)) {
		return;
	}
	gfx->PutPixel(x, y, c);
	
}

void Interface::DrawText(char * str, int x, int y)
{
	
	double POS_COUNTER = 0;
	
	//cache variables
	int BASE_W;
	Bitmap*  B;
	this->TextObj->setText(str);
	char* ptr = &TextObj->text[0];
		
	while(*ptr++ != 0){
		B = TextObj->Get_Bitmap_Char(* (ptr - 1));
		BASE_W = B->width;
		Draw_Bitmap(B, x + (int) POS_COUNTER, y);
		POS_COUNTER += BASE_W * 0.65;

		if (*ptr >= '0' && *ptr <= '9') POS_COUNTER += BASE_W * 0.20;
		else if (*ptr >= 'A' && *ptr <= 'Z') POS_COUNTER += BASE_W * 0.05;
	}

}

void Interface::set_font(Text * txt)
{
	this->TextObj = txt;
}

void Interface::Draw_Bitmap(Bitmap* B, int fx, int fy) {
	//cache variables
	int r;
	int g;
	int b;
	unsigned char* ptr;
	
	for (int y = 0; y < B->height; y++) {
		for (int x = 0; x < B->width; x++) {
			ptr = &B->Data[y* B->IMG_LINE_SIZE + x * 3];
			
			r = *ptr++;
			g = *ptr++;
			b = *ptr;

			READ_COLOR.dword = (b << 16) + (g << 8) + r;


			if (READ_COLOR.dword == B->transparent_color.dword) {
				continue;
			}

			DrawPixel(x + fx, y + fy, READ_COLOR);
			
			
		}
	}
}
