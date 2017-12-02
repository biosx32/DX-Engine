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


TransparentBitmap img("FONT\\small.bmp");
Spritesheet sh(&img, 16, 16);

TransparentBitmap HumanImg("SPRITESHEET\\Spritesheet1-512x512.bmp");
Spritesheet Human(&HumanImg, 12, 7);

TransparentBitmap Human2IMG("SPRITESHEET\\sprite3.bmp");
Spritesheet Human2(&Human2IMG, 8, 9);
Animation anim1(60, &Human2, 4,11);
Animation anim2(7, &Human2, 31, 39);

void Game::Initialise() {
	out.set_graphics(&gfx);
}

void Game::UpdateModel()
{
}


void Game::ComposeFrame()
{
	anim1.Step(); 
	anim2.Step();


	Bitmap*  a1 = anim1.GetCurrent();
	Bitmap*  a2 = anim2.GetCurrent();

	out.Draw_Bitmap(a1, 30, 30);
	out.Draw_Bitmap(a2, 80, 30);
	
}
