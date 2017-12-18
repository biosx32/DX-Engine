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


void Interface::DrawPixelContainer(PixelContainer* src, int fx, int fy)
{

	FFPixel* ReadPixel;
	for (int yoff = 0; yoff < src->height; yoff++) {
		for (int xoff = 0; xoff < src->width; xoff++) {

			ReadPixel = src->pixels[yoff* src->width + xoff];

			if (ReadPixel->state & pxstate::checked) {
				this->DrawPixel(xoff + fx, yoff + fy, 0x00FF00);
			}

			else if (ReadPixel->state & pxstate::background) {
				this->DrawPixel(xoff + fx, yoff + fy, Colors::MakeRGB(177, 244, 177));
			}

			else {
				this->DrawPixel(xoff + fx, yoff + fy, ReadPixel->color);
			}

		}

	}

}


void Interface::DrawLabel(int xoff, int yoff, Label * label)
{

	this->DrawShape->SetBrushColor(Colors::Red);

	double rel_pos_x = 0;
	double rel_pos_y = 0;

	for (int i = 0; i < label->txmax; i++) {
		int chr = label->text[i];

		if (chr == '\0') {
			continue;
		}

		VectorBitmap* CharacterRepr = label->GetCharacterRepr(chr);

		int charw = CharacterRepr->width;
		int charh = CharacterRepr->height;

		int destx = (int) (xoff + rel_pos_x);
		int desty = (int) (yoff + rel_pos_y);

		int gap = 3;


		Draw_Bitmap(CharacterRepr, destx, desty);

		//this->DrawShape->rectangle(destx, desty,charw, 24);

		rel_pos_x += charw + gap;

		if (chr == '\x20') {
			rel_pos_x += 4 * gap;

		}

		if (chr == '\n') {
			rel_pos_y += charh;
			rel_pos_x = 0;
			continue;
		}


		/*if (chr >= 'A' && chr <= 'Z' ||
			chr >= 'a' && chr <= 'z') {
			rel_pos_x -= basew * 0.25;
		}

		if (chr >= 'A' && chr <= 'Z' ||
			chr >= 'a' && chr <= 'z') {
			rel_pos_x -= basew * 0.25;
		}*/

/*		else if (chr == '\10') {
			rel_pos_x += 20.25;
		}

		if (chr >= '0' && chr <= '9') {
			rel_pos_x += char_width * 0.20;
		}
		*/


	
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
		   (finalx >= gfx->ScreenWidth ||
			finaly >= gfx->ScreenHeight ||
			finalx < 0 ||
			finaly < 0)) {
		return;
	}

	gfx->PutPixel(finalx, finaly, c);
			
}

void Interface::Draw_Bitmap(Bitmap * Bmp, int fx, int fy, int MODIF)
{
	int width = Bmp->width;
	int height = Bmp->height;

	for (int yoff = 0; yoff < Bmp->height; yoff++) {
		for (int xoff = 0; xoff < Bmp->width; xoff++) {
			
			int finalx = fx + xoff;
			int finaly = fy + yoff;
			Color READ_COLOR = Bmp->data[yoff* width + xoff];

			if (!Bmp->IsColorTransparent(READ_COLOR)) {
				DrawPixelSpecial(finalx, finaly, READ_COLOR, MODIF, width, height);
			}
		}
	}
}

void Interface::Draw_Bitmap(VectorBitmap * VBmp, int fx, int fy)
{
	this->Draw_Bitmap(VBmp, fx, fy, NULL);
}

void Interface::Draw_Bitmap(VectorBitmap * VBmp, int fx, int fy, int MODIF)
{
	for (std::vector<FPixel*>::iterator it = VBmp->pixels->begin(); it != VBmp->pixels->end(); ++it) {
		int width = VBmp->width;
		int height = VBmp->height;

		this->DrawPixelSpecial(fx + (*it)->x, fy + (*it)->y, (*it)->color, MODIF, width, height);
	}
}

void Interface::DrawSpritesheet(Spritesheet * sh, int xoff, int yoff)
{
	/*Color old = this->DrawShape->brush;
	this->DrawShape->SetBrushColor(Colors::Red);

	int sprw = sh->sprites[0]->width;
	int sprh = sh->sprites[0]->height;

	REIMPLEMENT TODO
	
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
	
	this->DrawShape->SetBrushColor(old);*/
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
