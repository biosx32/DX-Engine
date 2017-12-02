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
Animation run(9, &Human2, 4,11);
Animation walk(4, &Human2, 32, 39);
Animation idle(1, &Human2, 64, 64);


void Game::Initialise() {
	out.set_graphics(&gfx);
}

void Game::UpdateModel()
{
}

bool running = false;
bool moving = false;
bool left = false;
bool right = false;
int x = 300;
int y = 300;

int modif = 0;

void Game::ComposeFrame()
{

	running = wnd.kbd.KeyIsPressed(VK_CONTROL);

	left = wnd.kbd.KeyIsPressed(VK_LEFT);
	right = wnd.kbd.KeyIsPressed(VK_RIGHT);

	moving = left || right;

	

	if (left) modif |= FLIP_HORIZONTALLY;
	if (right) modif &= ~FLIP_HORIZONTALLY;

	Animation * state;
	if (!moving) { state = &idle; }
	else if (!running) { state = &walk; 
	if (left) x--;
	if (right) x++;
	
	
	}
	else if (running) { state = &run; 
	
	if (left) x-=3;
	if (right) x+=3;
	}

	state->Step();
	Bitmap*  player = state->GetCurrent();
	out.Draw_Bitmap(player, x, y,modif);
	
}
