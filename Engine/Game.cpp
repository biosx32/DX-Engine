/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"



Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}


TransparentBitmap img("FONT\\small.bmp", Colors::MakeRGB(177, 244, 177));
Spritesheet sh(&img);



TransparentBitmap SpriteImage("SPRITESHEET\\sprite3.bmp", Colors::MakeRGB(177, 244, 177));
PixelContainer container(&SpriteImage);



int idx=0;
VectorBitmap* test = nullptr;
void Game::Initialise() {
	out.set_graphics(&gfx);

	
	test = container.GetNextSpriteGroup();
	
	/*while (container.getFirstRawPixel() != nullptr) {
		container.CheckPixel(container.getFirstRawPixel());
		while (container.IteratePendingPixels());
		
	}*/

	
	
}

Label j(&sh);
Label framecounter(&sh);

Spritesheet* p;

FFPixel* tst = nullptr;
void Game::ComposeFrame()
{

	Bitmap* Bmp = &SpriteImage;
	int width = Bmp->width;
	int height = Bmp->height;

	for (int yoff = 0; yoff < Bmp->height; yoff++) {
		for (int xoff = 0; xoff < Bmp->width; xoff++) {

			int finalx = 0 + xoff;
			int finaly = 0 + yoff;
			Color READ_COLOR = Bmp->data[yoff* width + xoff];

			if (!Bmp->IsColorTransparent(READ_COLOR)) {
				out.DrawPixel(finalx, finaly, READ_COLOR);
			}
			else {
				out.DrawPixel(finalx, finaly, 0xFF0000);
			}
		}
	}

	/*for (int i = 0; i < container.get_pixelcount(); i++) {
		tst = container.pixels[i];



		if (tst->state & pxstate::background) {
			out.DrawPixel(tst->x, tst->y, 0x0000FF);
		}
		else if (tst->state & pxstate::checked) {
			out.DrawPixel(tst->x, tst->y, 0x00FF00);
		}
		else {
			out.DrawPixel(tst->x, tst->y, tst->color);
		}
		
	}*/

	if (wnd.mouse.LeftIsPressed()) {
		Sleep(30);
		container.GetNextSpriteGroup();
	}
		//out.DrawLabel(0,  0, &framecounter);
	
}


void Game::UpdateModel()
{


	//framecounter.setText(getFrameNumber());
}


