/****************************************************************************************** 
 *	Chili DirectX Framework Version 12.10.21											  *	
 *	Game.cpp																			  *
 *	Copyright 2012 PlanetChili.net														  *
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
#include "Game.h"

TransparentBitmap img("IMAGES\\FONTMAP_SMALL.bmp", Colors::MakeARGB(255,177, 244, 177));
Label framecounter(&img, 16, 16);
TransparentBitmap scaling("IMAGES\\RGB_TEST.bmp", Colors::MakeARGB(255,177, 244, 177));

Game::Game( HWND hWnd,KeyboardServer& kServer,const MouseServer& mServer )
:	gfx( hWnd ),
	audio( hWnd ),
	kbd( kServer ),
	mouse( mServer )
{
	srand( (unsigned int)time( NULL ) );
}


void Game::Initialise() {
	out = new TestInterface(&gfx);
}


float scale = 0;
void Game::ComposeFrame() {

	//out.DrawBitmapM(&scaling, 0, 0, scale);

	framecounter.setText(getFrameNumber());
	scale += 0.25;
	if (scale > 2) scale = 0;
	float m = scale * 0.5* SCREENWIDTH / scaling.width;;

	out->DrawPixel(0, 0, 0);
	out->DrawBitmapM(&scaling, 0, 0, m*(float) mouse.GetMouseX() / SCREENWIDTH,
		m*(float) mouse.GetMouseY() / SCREENHEIGHT);



	//out->DrawBitmapM(&scaling, 0, 0, 2,2);
	//out.DrawLabel( (int) 1, (int) 1, &framecounter, 0.85);

}

void Game::UpdateModel()
{


}


