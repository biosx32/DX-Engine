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
Spritesheet sh(&img,16,16);
Label framecounter(&img,16,16);


TransparentBitmap SpriteImage("SPRITESHEET\\descent_mini.bmp", Colors::MakeRGB(255, 255, 255));

PixelContainer* container=nullptr;

void Game::Initialise() {
	out.set_graphics(&gfx);
	out.DrawShape->SetBrushColor(Colors::Blue);

	SpriteImage.tolerance = 0.0001f;
	container = new PixelContainer(&SpriteImage);
	
	
}

VectorBitmap* todraw = nullptr;

void Game::ComposeFrame()
{
	out.DrawShape->rectangle_fill(0, 0, gfx.ScreenWidth-1, gfx.ScreenHeight-1);

	out.DrawPixelContainer(container, 0, 0);
    
	out.DrawLabel(0,  500, &framecounter);
	//out.Draw_Bitmap(&SpriteImage,0,0);
	if (todraw) {
		out.Draw_Bitmap(todraw, 550, 50);
	}
}

void Game::UpdateModel()
{
	if (wnd.mouse.LeftIsPressed()) {
		
		VectorBitmap* next = nullptr;

		while (1) {
			next = container->GetNextSpriteGroup();
			if (!next) break;
			if (next->pixels->size() > 9999) {
				todraw = next;
				Sleep(10);
				break;
			}
			
		}

		
		
		
	}
	framecounter.setText(getFrameNumber());
}


