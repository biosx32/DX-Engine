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


TransparentBitmap scaling("..\\Resources\\test_RGB.bmp", Colors::MakeARGB(255,177, 244, 177));

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

	float m = 0.5* SCREENWIDTH / scaling.width;;
	out->PrintText(1, 1, getFrameNumber(), 0.25, &DOS_BLACK);

	Grid grid(100, 100, 20);
	grid.Draw(out);
	TrianglePoly* poly = new TrianglePoly(&grid, -2.5,-2.5, 2.5, -2.5, 0,2.5);
	poly->Draw(out);
	delete poly;


	out->Painter->line(300, 300, mouse.GetMouseX(), mouse.GetMouseY(), Colors::Red);

}

void Game::UpdateModel()
{


}


