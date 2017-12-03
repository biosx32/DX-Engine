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
Animation walkup(4, &Human2, 48, 55);
Animation walkdown(4, &Human2, 56, 63);


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
bool up = false;
bool down = false;
float x = 300;
float y = 300;

int modif = 0;

void Game::ComposeFrame()
{

	running = wnd.kbd.KeyIsPressed(VK_CONTROL);
	left = wnd.kbd.KeyIsPressed(VK_LEFT);
	right = wnd.kbd.KeyIsPressed(VK_RIGHT);
	up = wnd.kbd.KeyIsPressed(VK_UP);
	down = wnd.kbd.KeyIsPressed(VK_DOWN);
	moving = left || right;

	float spdx = 0;
	float spdy = 0;


	if (left) modif |= FLIP_HORIZONTALLY;
	if (right) modif &= ~FLIP_HORIZONTALLY;

	if (left) {
		spdx = -1;
		if (running) spdx = -2;
	}
	
	if (right) {
		spdx = 1;
		if (running) spdx = 2;
	}

	if (up) {
		spdy = -0.5;
		if (running) spdy = -1;
	}

	if (down) {
		spdy = 0.5;
		if (running) spdy = 1;
	}


	Animation * state;

	state = &idle;

	if (moving) {
		state = &walk;
	}

	if (running) {
		state = &run;
	}

	if (up) state = &walkup;
	if (down) state = &walkdown;
    
	if (!running && (up || down)) {
		state->FPS = 4;
	}

	if (running && (up||down)) {
		state->FPS = 8;
	}

	x += spdx;
	y += spdy;



	state->Step();
	Bitmap*  player = state->GetCurrent();
	out.Draw_Bitmap(player, (int)x, (int)y,modif);
	
}
