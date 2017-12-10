#include "Interface.h"

Interface::Interface()
{
	this->DrawShape = new Draw();
	this->DrawShape->setOutInterface(this);
}

void Interface::set_graphics(Graphics* gfx) {
	this->gfx = gfx; 
}
void Interface::DrawPixel(int xoff, int yoff, Color c) { 
	int softdraw = 1;

	if (gfx == nullptr) return;

	if ( softdraw && (xoff>= gfx->ScreenWidth || xoff < 0 || yoff >= gfx->ScreenHeight || yoff < 0)) return;
	gfx->PutPixel(xoff, yoff, c);
	
}


void Interface::DrawLabel(int xoff, int yoff, Label * label)
{
	double rel_pos_x = 0;
	double rel_pos_y = 0;



	int char_width = label->Get_Bitmap_Char(0)->datagroup->width;
	int char_height = label->Get_Bitmap_Char(0)->datagroup->height;


	for (char* data = &label->text[0]; *data != 0; data++) {
		unsigned char udata = (unsigned char) *data;
		data++;
		Bitmap* BitmapChar = label->Get_Bitmap_Char(udata);
		char_width = BitmapChar->datagroup->width;

		if (*(data - 1) == '\n') {
			rel_pos_y += char_height;
			rel_pos_x = 0;
			continue;
		}

		Draw_Bitmap(BitmapChar, (int) (rel_pos_x + xoff), (int)
			(rel_pos_y + yoff));
		
		if (true) {
			rel_pos_x += char_width * 0.65;
		
			if (*data >= '0' && *data <= '9') {
				rel_pos_x += char_width * 0.20;
			}
			else if (*data >= 'A' && *data <= 'Z') {
				rel_pos_x += char_width * 0.05;
			}
		}
	}
}



void Interface::Draw_Bitmap(Bitmap* BitmapChar, int fx, int fy) {
	Color READ_COLOR;
	for (int yoff = 0; yoff < BitmapChar->datagroup->height; yoff++) {
		for (int xoff = 0; xoff < BitmapChar->datagroup->width; xoff++) {

			READ_COLOR = BitmapChar->datagroup->data[yoff* BitmapChar->datagroup->width + xoff];
			if (!BitmapChar->IsColorTransparent(READ_COLOR)) {
				DrawPixel(xoff + fx , yoff + fy, READ_COLOR);
			}

			
		}
	}
}

void Interface::Draw_Bitmap(Bitmap * Bmp, int fx, int fy, int MODIF)
{
	
	Color READ_COLOR;
	int finalx; int finaly;

	for (int yoff = 0; yoff < Bmp->datagroup->height; yoff++) {
		for (int xoff = 0; xoff < Bmp->datagroup->width; xoff++) {
			
			finalx = fx + xoff;
			if (MODIF & FLIP_HORIZONTALLY) {
				finalx = fx + Bmp->datagroup->width - xoff;
			}
			
			
			finaly = yoff + fy;
			if (MODIF & FLIP_VERTICALLY) {
				finaly = fy + Bmp->datagroup->height - yoff;
			}

			READ_COLOR = Bmp->datagroup->data[yoff* Bmp->datagroup->width + xoff];
			if (!Bmp->IsColorTransparent(READ_COLOR)) {
				DrawPixel(finalx, finaly, READ_COLOR);
			}


		}
	}
}

void Interface::DrawSpritesheet(Spritesheet * sh, int xoff, int yoff)
{
	Color old = this->DrawShape->brush;
	this->DrawShape->SetBrushColor(Colors::Red);

	int sprw = sh->datagroup->data[0]->datagroup->width;
	int sprh = sh->datagroup->data[0]->datagroup->height;

	for (int y = 0; y < sh->datagroup->hcount; y++) {
		for (int x = 0; x < sh->datagroup->wcount; x++) {
			int i = y * sh->datagroup->wcount + x;
			int xdst = x* sprw + 1 * x ;
			int ydst = y* sprh + 1 * y;

		
			this->Draw_Bitmap(sh->datagroup->data[i], xoff+ xdst, yoff+ ydst);
			this->DrawShape->FastHLine(xoff + xdst, yoff + ydst, sprh+1);
			this->DrawShape->FastVLine(xoff + xdst, yoff + ydst, sprw+1);
		}
	}

	this->DrawShape->SetBrushColor(old);
}

void Interface::DrawPixelM(int xoff, int yoff, Color c)
{
	int m = 4;
	xoff *= m;
	yoff *= m;
	for (int y = 0; y < m; y++) {
		for (int x = 0; x < m; x++) {
			this->DrawPixel(x + xoff, y + yoff, c);
		}
	}

}
