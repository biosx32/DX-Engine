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


void drawFastVLine(Interface out, int x0, int y0, int width) {
	for (int i = 0; i < width; i++) {
		out.DrawPixel(x0 + i, y0, Colors::Green);
	}
}
void drawFastHLine(Interface out, int x0, int y0, int height) {
	for (int i = 0; i < height; i++) {
		out.DrawPixel(x0, y0 + i, Colors::Green);
	}
}

void drawcircle(Interface out, int x0, int y0, int radius)
{
	int x = radius - 1;
	int y = 0; int dx = 1; int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y)
	{
		out.DrawPixel(x0 + x, y0 + y, Colors::Cyan);
		out.DrawPixel(x0 + y, y0 + x, Colors::Cyan);
		out.DrawPixel(x0 - y, y0 + x, Colors::Cyan);
		out.DrawPixel(x0 - x, y0 + y, Colors::Cyan);
		out.DrawPixel(x0 - x, y0 - y, Colors::Cyan);
		out.DrawPixel(x0 - y, y0 - x, Colors::Cyan);
		out.DrawPixel(x0 + y, y0 - x, Colors::Cyan);
		out.DrawPixel(x0 + x, y0 - y, Colors::Cyan);

		if (err <= 0)
		{	y++;
			err += dy;
			dy += 2;
		}
		if (err > 0)
		{	 x--;
			dx += 2;
			err += (-radius << 1) + dx;
		}
	}
}
void drawline(Interface out, int x0, int y0, int width, int height)
{
	int dx, dy, p, x, y,t, y1, x1;

	x1 = t = x0 + width;
	
	if (x1 < x0) {
		x1 = x0;
		x0 = t;
	}
	y1 = t = y0 + height;
	
	if (y1 < y0) {
		y1 = y0;
		y0 = t;
	}


	dx = x1 - x0; 
	dy = y1 - y0;

	if (dy == 0) return drawFastVLine(out, x0, y0, width);
	if (dx == 0) return drawFastHLine(out, x0, y0, height);

	x = x0;  
	y = y0;
	p = 2 * dy - dx;

	while (x<x1){
		if (p >= 0) {
			out.DrawPixel(x, y,Colors::Green);
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		else {
			out.DrawPixel(x, y, Colors::Green);
			p = p + 2 * dy;
		}
		x = x + 1;
	}
}

void drawrectangle(Interface out, int x0, int y0, int width, int height) {
	int w2 = width / 2; int h2 = height / 2;
	drawline(out, x0 - w2, y0 - h2, 0, height);
	drawline(out, x0 + w2, y0 - h2, 0, height);

	drawline(out, x0 - w2, y0 - h2, width, 0);
	drawline(out, x0 - w2, y0 + h2, width, 0);

}

TransparentBitmap img;
Spritesheet sh(16,16);
Label j;

void Game::Initialise() {
	out.set_graphics(&gfx);
	
	img.Load("FONT\\small.bmp");
	
	sh.Load(&img);
	j.Load(&sh);

	out.set_font(&j);
}

void Game::UpdateModel()
{
}
//test2

float p = 1.0;
void Game::ComposeFrame()
{
	p += 0.0025;
	out.Draw_Bitmap(sh.BitmapImage, 370, 50);
	j.setText("TEXTO_123");
	p += 0.0025;
	out.Draw_Bitmap(sh.BitmapImage, 370, 50);
	out.DrawLabel(30, 30);
	out.DrawLabel(30, 60, &j);
	for (int y = 0; y < sh.hcount; y++) {
		for (int x = 0; x < sh.wcount; x++) {
			int i = y * sh.wcount + x;
			int xdst = x*sh.SpriteData[i]->BitmapData->width * p;
			int ydst = y*sh.SpriteData[i]->BitmapData->height * p;

			out.Draw_Bitmap(&TransparentBitmap(sh.SpriteData[i]), 30 + xdst, 80 + ydst);
		}
	}

}
