#include "Interface.h"

#define SOFT_DRAW 1

Interface::Interface(Graphics* gfx)
{
	this->gfx = gfx;
	this->Painter = new Draw();
	this->Painter->setOutInterface(this);
}

void Interface::DrawPixel(int xoff, int yoff, Color c) { 

	if (SOFT_DRAW) {
		if (xoff >= gfx->ScreenWidth ||
			yoff >= gfx->ScreenHeight ||
			xoff < 0 ||
			yoff < 0) {
			return;
		}
	}

	gfx->PutPixel(xoff, yoff, c);

}




void Interface::DrawLabel(int xoff, int yoff, Label * label, double scale)
{
	double rel_pos_x = 0;
	double rel_pos_y = 0;

	for (int i = 0; i < label->txmax; i++) {
		int chr = label->text[i];

		if (chr == '\0') {
			continue;
		}

		TransparentBitmap* CharacterRepr = label->GetCharacterRepr(chr);

		double charw = CharacterRepr->width*scale;
		double charh = CharacterRepr->height*scale;

		int destx = (int) (xoff + rel_pos_x);
		int desty = (int) (yoff + rel_pos_y);

		double gap = 3 * scale;


		Draw_Bitmap_M(CharacterRepr, destx, desty, scale);


		this->Painter->rectangle(destx, desty,charw, charh,Colors::White);

		rel_pos_x += charw + gap;

		if (chr == '\x20') {
			rel_pos_x += 4 * gap;

		}

		if (chr == '\n') {
			rel_pos_y += charh;
			rel_pos_x = 0;
			continue;
		}
	
	}

}



void Interface::Draw_Bitmap_M(Bitmap * Bmp, int xoff, int yoff, float m)
{
	if (!(m > 0)) return;
	
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
				if (m <=1) {
					this->DrawPixelM(dstx, dsty, READ_COLOR,1);
				}
				else {
					this->DrawPixelM(dstx, dsty, Colors::White,1);
				}
					
			}
			else {
				this->DrawPixelM(dstx, dsty, Colors::White, 1);
			}
			


			

		}
	}


}

void Interface::Draw_Bitmap(Bitmap* Bmp, int fx, int fy) {
	for (int yoff = 0; yoff < Bmp->height; yoff++) {
		for (int xoff = 0; xoff < Bmp->width; xoff++) {
			int finalx = fx + xoff;
			int finaly = fy + yoff;
			Color READ_COLOR = *Bmp->GetDataPtr(xoff, yoff);
			if (!Bmp->IsColorTransparent(READ_COLOR)) {
				DrawPixel(finalx, finaly, READ_COLOR);
			}
		}
	}
}



Interface::Interface(Graphics * gfx)
{
	this->gfx = gfx;
}


void Interface::Draw_Bitmap(Sprite * VBmp, int fx, int fy)
{
	for (std::vector<FPixel*>::iterator it = VBmp->pixels->begin(); it != VBmp->pixels->end(); ++it) {
		this->DrawPixel(fx + (*it)->x, fy + (*it)->y, (*it)->color);
	}
}

void Interface::Draw_Bitmap(Sprite * VBmp, int fx, int fy, int MODIF)
{

}


void Interface::FillScreen(Color color)
{
	if (gfx) {
		this->Painter->rectangle_fill(0, 0, gfx->ScreenWidth - 1, gfx->ScreenHeight - 1, color);
	}
}

void Interface::DrawPixelM(int xoff, int yoff, Color c, int m)
{
	#define SOFT_DRAW 1

	for (int y = 0; y < m; y++) {
		for (int x = 0; x < m; x++) {
	
			int finalx = xoff + x;
			int finaly = yoff + y;

			if (SOFT_DRAW) {
				if(finalx >= gfx->ScreenWidth ||
					finaly >= gfx->ScreenHeight ||
					finalx < 0 ||
					finaly < 0) {
				return;
				}   	
			}

			gfx->PutPixel(finalx, finaly, c);

		}
	}

}
