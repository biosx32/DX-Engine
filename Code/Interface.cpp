#include "Interface.h"

#define SOFT_DRAW 1

Interface::Interface(D3DGraphics* gfx)
{
	this->gfx = gfx;
	this->Painter = new Draw();
	this->Painter->setOutInterface(this);
}

void Interface::DrawPixel(int xoff, int yoff, Color c) {

	if (SOFT_DRAW) {
		if (xoff >= SCREENWIDTH ||
			yoff >= SCREENHEIGHT ||
			xoff < 0 ||
			yoff < 0) {
			return;
		}
	}




	this->gfx->PutPixel(xoff, yoff, c);

}


void Interface::PrintText(int x, int y, char * text, double scale, FontType* font)
{
	double rel_pos_x = 0;
	double rel_pos_y = 0;


	char buffer[256];
	strcpy_s(buffer, text);

	for (int i = 0; buffer[i] != 0; i++) {
		int chr = buffer[i];
		float charw = font->sprite_sheet->wsize * scale/1.25;
		float charh = font->sprite_sheet->hsize * scale;

		if (chr == '\x20') {
			rel_pos_x += charw;
		}

		else if (chr == '\n') { // \\x10
			rel_pos_y += charh;
			rel_pos_x = 0;
		}

		if (chr < 33) {
			continue;
		}


		TransparentBitmap* CharBitmap = font->GetCharacterRepr(chr);


		int destx = (int)(x + rel_pos_x);
		int desty = (int)(y + rel_pos_y);

		DrawBitmapM(CharBitmap, destx, desty, scale, scale);
		//this->Painter->rectangle(destx, desty, charw, charh, 0xFFFF0000);
		rel_pos_x += charw;

	}
}



void Interface::DrawBitmapM(Bitmap * Bmp, int xoff, int yoff, float mx, float my)
{
	if (!(mx > 0 && my > 0)) return;

	int width = Bmp->width;
	int height = Bmp->height;
	int draw_width = Bmp->width * mx;
	int draw_height = Bmp->height * my;

	//int magnifx = (1 / mx) > 0 ? (1 / mx) : 1;

	for (int y = 0; y < draw_height; y++) {
		int srcy = y / my;
		for (int x = 0; x < draw_width; x++) {
			int srcx = x / mx;


			Color *pixel = Bmp->GetDataPtr(srcx, srcy);
			if (!Bmp->IsColorTransparent(*pixel)) {
				DrawPixelM(xoff + x, yoff + y, *pixel, 1);
			}

		}

	}



	/*
	int width = Bmp->width;
	int height = Bmp->height;

	int neighbors = (int)(1 / m);
	if (neighbors == 0) neighbors = m;

	int draw_width  = (int) (Bmp->width * m);
	int draw_height = (int) (Bmp->height * m);



	int blendpx=0, RT=0, GT=0, BT=0;


	for (int y = 0; y < draw_height; y++) {
	for (int x = 0; x < draw_width; x++) {
	int srcx = (int) (x * (1/m));
	int srcy = (int) (y * (1/m));

	int RT= GT= BT= blendpx = 0;

	for (int nx = 0; nx < neighbors; nx++) {
	for (int ny = 0; ny < neighbors; ny++) {
	int nxo = nx - neighbors / 2;
	int nyo = ny - neighbors / 2;

	Color* neighbor = Bmp->GetDataPtr(srcx - nxo, srcy - nyo);
	if (neighbor == nullptr) {
	continue;
	}

	if (!Bmp->IsColorTransparent(*neighbor)) {
	blendpx += 1;
	RT += neighbor->GetR(); GT += neighbor->GetG(); BT += neighbor->GetB();
	}




	}
	}
	if (blendpx == 0) continue;
	RT /= blendpx; GT /= blendpx; BT /= blendpx;

	Color READ_COLOR = Colors::MakeRGB(RT, GT, BT);

	int dstx = (int)((xoff + x) * m);
	int dsty = (int)((yoff + y) * m);

	if (!Bmp->IsColorTransparent(READ_COLOR)) {
	if (m <= 1) {
	this->DrawPixelM(dstx, dsty, READ_COLOR,1);
	}
	else {
	this->DrawPixelM(dstx, dsty, READ_COLOR, 1);
	}

	}

	}
	}*/
}

void Interface::DrawBitmap(Bitmap* Bmp, int fx, int fy) {
	for (int yoff = 0; yoff < Bmp->height; yoff++) {
		for (int xoff = 0; xoff < Bmp->width; xoff++) {
			int finalx = fx + xoff;
			int finaly = fy + yoff;
			Color Pixel = *Bmp->GetDataPtr(xoff, yoff);
			if (!Bmp->IsColorTransparent(Pixel)) {
					DrawPixel(finalx, finaly, Pixel);
			}
		}
	}
}






void Interface::DrawSprite(MySprite * VBmp, int fx, int fy)
{
	for (std::vector<FPixel*>::iterator it = VBmp->pixels->begin(); it != VBmp->pixels->end(); ++it) {
		this->DrawPixel(fx + (*it)->x, fy + (*it)->y, (*it)->color);
	}
}


void Interface::FillScreen(Color color)
{
	if (gfx) {
		this->Painter->rectangle_fill(0, 0, SCREENWIDTH - 1, SCREENHEIGHT - 1, color);
	}
}

void Interface::DrawPixelM(int xoff, int yoff, Color c, int m)
{
#define SOFT_DRAW 1

	xoff *= m;
	yoff *= m;

	for (int y = 0; y < m; y++) {
		for (int x = 0; x < m; x++) {

			int finalx = xoff + x;
			int finaly = yoff + y;

			if (SOFT_DRAW) {
				if (finalx >= SCREENWIDTH ||
					finaly >= SCREENHEIGHT ||
					finalx < 0 ||
					finaly < 0) {
					return;
				}
			}

			gfx->PutPixel(finalx, finaly, c);

		}
	}

}
