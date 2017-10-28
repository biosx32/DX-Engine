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

char* const translate = { "\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff"
};
Text MEDIUM("FONT\\medium.bmp", 16, 16, translate, 0xffffff, 0x99ceff);

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



void Game::Initialise() {
	out.set_graphics(&gfx);
	out.set_font(&MEDIUM);
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

void Game::UpdateModel()
{
}



void Game::ComposeFrame()
{
	out.DrawText("Jebek",0,0);

}
