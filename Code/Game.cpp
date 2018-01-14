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

TransparentBitmap img("..\\Resources\\DOS_FONT_22_5.bmp", Colors::MakeARGB(255,255, 255, 255));
Label framecounter(&img, 22, 5);
TransparentBitmap scaling("..\\Resources\\RGB_TEST.bmp", Colors::MakeARGB(255,177, 244, 177));

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
	srand(time(0));
}


float scale = 0;
void Game::ComposeFrame() {

	//out.DrawBitmapM(&scaling, 0, 0, scale);
	
	framecounter.setText(getFrameNumber());
	float m = 0.5* SCREENWIDTH / scaling.width;;
	Label* ptr = &framecounter;
	out->DrawLabel( 1,  1, ptr, 0.25);
	out->Painter->line(std::rand()%800, std::rand() % 600, mouse.GetMouseX(), mouse.GetMouseY(),Colors::MakeARGB(0,255,255,255));



}

void Game::UpdateModel()
{


}


