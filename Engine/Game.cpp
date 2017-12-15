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



void Game::Initialise() {
	out.set_graphics(&gfx);
	

	/*while (container.getFirstRawPixel() != nullptr) {
		container.CheckPixel(container.getFirstRawPixel());
		while (container.IteratePendingPixels());
		
	}*/

	
	
}

Label j(&sh);
Label framecounter(&sh);

Spritesheet* p;

FFPixel* tst = nullptr;
VectorBitmap* jozo = nullptr;
void Game::ComposeFrame()
{

	
	
	if (jozo) out.Draw_Bitmap(jozo, 550, 0);
	for (int i = 0; i < container.pixelcount(); i++) {
		tst = container.pixels[i];
		if (tst->state & pxstate::background) {
			out.DrawPixel(tst->x, tst->y, 0x000000);
		}
		else if (tst->state & pxstate::checked) {
			out.DrawPixel(tst->x, tst->y, 0x0000FF);
		}
		else {
			out.DrawPixel(tst->x, tst->y, tst->color);
		}
		
	}

	for (int i = 1; i <= container.width / container.gridsize; i++) {
		for (int j = 1; j <= container.height / container.gridsize; j++) {
			int im = i * container.gridsize;
			int jm = j * container.gridsize;
			out.DrawPixel(im,   jm +1, Colors::Magenta);
			out.DrawPixel(im,   jm ,   Colors::Magenta);
			out.DrawPixel(im+1, jm +1, Colors::Magenta);
			out.DrawPixel(im+1, jm ,   Colors::Magenta);

		}
	}

	out.DrawShape->SetBrushColor(Colors::Green);
	out.DrawShape->circle(container.lastpos.x, container.lastpos.y, 15);


		//out.DrawLabel(0,  0, &framecounter);
	
}


void Game::UpdateModel()
{
	if (wnd.mouse.LeftIsPressed()) {
//		Sleep(30);
		VectorBitmap* temp = container.GetGroupFrom(container.getPixelAt(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()));;
		jozo = temp ? temp : jozo;
	}

	//framecounter.setText(getFrameNumber());
}


