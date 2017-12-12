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



TransparentBitmap SpriteImage("SPRITESHEET\\sprite3.bmp");
PixelContainer container;




VectorBitmap jj;


int idx=0;
void Game::Initialise() {
	out.set_graphics(&gfx);
	container.Load(&SpriteImage);

	jj.Load(container.GetNextSpriteGroup());
	

	/*while (container.getFirstRawPixel() != nullptr) {
		container.CheckPixel(container.getFirstRawPixel());
		while (container.IteratePendingPixels());
		
	}*/

	
	
}

Label j(&sh);
Label framecounter(&sh);


void Game::ComposeFrame()
{
	out.DrawLabel(0,  gfx.ScreenHeight - framecounter.sprite_sheet->datagroup->data[0]->image->datagroup->height, &framecounter);
	out.Draw_Bitmap(&jj, 0, 0);
}


void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		jj.Load(container.GetNextSpriteGroup());
		
	}

	framecounter.setText(getFrameNumber());
}


