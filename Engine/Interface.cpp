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
	this->DrawPixelSpecial(xoff, yoff, c, NULL, NULL, NULL);

}


void Interface::DrawLabel(int xoff, int yoff, Label * label)
{
	double rel_pos_x = 0;
	double rel_pos_y = 0;



	int char_width = label->Get_Bitmap_Char(0)->datagroup->width;
	int char_height = label->Get_Bitmap_Char(0)->datagroup->height;


	for (char* data = &label->text[0]; *data != 0; data++) {
		unsigned char udata = (unsigned char) *data;

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



void Interface::Draw_Bitmap(Bitmap* Bmp, int fx, int fy) {
	this->Draw_Bitmap(Bmp, fx, fy, 0);
}

void Interface::DrawPixelSpecial(int xoff, int yoff, Color c, int MODIF, int width, int height) {
	if (gfx == nullptr) return;

	int finalx = xoff;
	int finaly = yoff;

	if (MODIF & FLIP_HORIZONTALLY) {
		finalx = width - xoff;
	}

	if (MODIF & FLIP_VERTICALLY) {
		finaly = height - yoff;
	}


	#define SOFT_DRAW 1

	if (SOFT_DRAW &&
		(xoff >= gfx->ScreenWidth ||
			yoff >= gfx->ScreenHeight ||
			xoff < 0 ||
			yoff < 0)) {
		return;
	}

	gfx->PutPixel(finalx, finaly, c);
			
}

void Interface::Draw_Bitmap(Bitmap * Bmp, int fx, int fy, int MODIF)
{
	int width = Bmp->datagroup->width;
	int height = Bmp->datagroup->height;

	for (int yoff = 0; yoff < Bmp->datagroup->height; yoff++) {
		for (int xoff = 0; xoff < Bmp->datagroup->width; xoff++) {
			
			int finalx = fx + xoff;
			int finaly = fy + yoff;
			Color READ_COLOR = Bmp->datagroup->data[yoff* width + xoff];

			if (!Bmp->IsColorTransparent(READ_COLOR)) {
				DrawPixelSpecial(finalx, finaly, READ_COLOR, MODIF, width, height);
			}
		}
	}
}

void Interface::DrawSpritesheet(Spritesheet * sh, int xoff, int yoff)
{
	Color old = this->DrawShape->brush;
	this->DrawShape->SetBrushColor(Colors::Red);

	int sprw = sh->datagroup->data[0]->image->datagroup->width;
	int sprh = sh->datagroup->data[0]->image->datagroup->height;

	for (int y = 0; y < sh->datagroup->hcount; y++) {
		for (int x = 0; x < sh->datagroup->wcount; x++) {
			int i = y * sh->datagroup->wcount + x;
			int xdst = x* sprw + 1 * x ;
			int ydst = y* sprh + 1 * y;

		
			this->Draw_Bitmap(sh->datagroup->data[i]->image, xoff+ xdst, yoff+ ydst);
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
