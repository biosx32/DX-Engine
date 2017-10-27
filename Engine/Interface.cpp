#include "Interface.h"

void Interface::set_graphics(Graphics* gfx) { 
	this->gfx = gfx; 
}
void Interface::DrawPixel(int x, int y, Color c) { 
	if (gfx == nullptr) {
		return;
	}
	gfx->PutPixel(x, y, c);
	
}

void Interface::DrawText(char * str, int x, int y)
{
	double POS_COUNTER = 0;
	Bitmap*  BCHR;

	this->TextObj->setText(str);
	char* chr = &TextObj->text[0];
	
	do {
		BCHR = TextObj->Get_Bitmap_Char(*chr);
		Draw_Bitmap(BCHR, x + (int) POS_COUNTER, y);
		
		if (*chr >= '0' && *chr <= '9') POS_COUNTER += BCHR->IMG_WIDTH * 0.20;
		else if (*chr >= 'A' && *chr <= 'Z') POS_COUNTER += BCHR->IMG_WIDTH * 0.05;
		POS_COUNTER += BCHR->IMG_WIDTH * 0.65;


	} while (*chr++);


}

void Interface::set_font(Text * txt)
{
	this->TextObj = txt;
}

void Interface::Draw_Bitmap(Bitmap* B, int fx, int fy) {
	int x, y, r, g, b;

	unsigned char* ptr;

	for (int i = 0; i < B->IMG_PIXEL_COUNT; i++) {		
		ptr = &B->Data[i*3];

		b = *ptr; g = *(ptr + 1); r = *(ptr + 2);

		READ_COLOR.dword = b + (g << 8) + (r << 16);

		if (READ_COLOR.dword != B->TRANSPARENCY_KEY.dword) {
			x = i % B->IMG_WIDTH;
			y = i / B->IMG_HEIGHT;
			DrawPixel(x + fx, y + fy, this->READ_COLOR);
		}

	}

}