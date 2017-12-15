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


TransparentBitmap img("FONT\\small.bmp",Colors::MakeRGB(177, 244, 177));
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



	for (int i = 0; i < container.pixelcount(); i++) {
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
		
	}

	for (int i = 1; i <= container.width / 16; i++) {
		for (int j = 1; j <= container.height / 16; j++) {
			out.DrawPixel(i*16, j*16, Colors::Cyan);
		}
	}
		//out.DrawLabel(0,  0, &framecounter);
	
}


void Game::UpdateModel()
{
	if (wnd.mouse.LeftIsPressed()) {
		Sleep(30);
		container.GetNextSpriteGroup();
	}

	//framecounter.setText(getFrameNumber());
}


