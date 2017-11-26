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


void Interface::DrawLabel(int x, int y, Label * label)
{
	double POS_COUNTER_X = 0;
	double POS_COUNTER_Y = 0;
	//cache variables
	int BASE_W;
	TransparentBitmap*  B;
	char* ptr = &label->text[0];

	while (*ptr++ != 0) {
		

		B = new TransparentBitmap(label->Get_Bitmap_Char(*(ptr - 1)));
		BASE_W = B->BitmapData->width;

		if (*(ptr - 1) == '\n') {
			POS_COUNTER_Y += B->BitmapData->height;
			POS_COUNTER_X = 0;
			continue;
		}

		Draw_Bitmap(B, x + (int)POS_COUNTER_X, POS_COUNTER_Y+ y);
		POS_COUNTER_X += BASE_W * 0.65;

		if (*ptr >= '0' && *ptr <= '9') POS_COUNTER_X += BASE_W * 0.20;
		else if (*ptr >= 'A' && *ptr <= 'Z') POS_COUNTER_X += BASE_W * 0.05;
	}
}



void Interface::Draw_Bitmap(Bitmap* B, int fx, int fy) {
	Color READ_COLOR;
	for (int y = 0; y < B->BitmapData->height; y++) {
		for (int x = 0; x < B->BitmapData->width; x++) {

			READ_COLOR = B->BitmapData->ptr[y* B->BitmapData->width + x];
			if (B->IsColorVisible(READ_COLOR) == 1) {
				DrawPixel(x + fx , y + fy, READ_COLOR);
			}

			
		}
	}
}
