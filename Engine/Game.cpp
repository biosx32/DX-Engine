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
TransparentBitmap HumanImg("SPRITESHEET\\Spritesheet1-512x512.bmp");
TransparentBitmap HumanImg2("SPRITESHEET\\Spritesheet1-512x512-2.bmp");
Spritesheet sh(&img, 16,16);
Spritesheet Human(&HumanImg, 12, 7);
Spritesheet Human2(&HumanImg2, 12, 7);



void Game::Initialise() {
	out.set_graphics(&gfx);
}

void Game::UpdateModel()
{
}

int spritenow = 0;
int spriteMax = Human.Data->hcount * Human.Data->wcount;
void Game::ComposeFrame()
{

	/*Bitmap*  current = Human.Data->ptr[spritenow];
	out.Draw_Bitmap(current, 0, 0);

	spritenow++;
	spritenow %= spriteMax;*/

	out.DrawSpritesheet(&Human, 0, 0);
	out.DrawSpritesheet(&Human2, 532, 0);
}
