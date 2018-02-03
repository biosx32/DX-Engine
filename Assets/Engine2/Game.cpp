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

Game::Game( HWND hWnd,KeyboardServer& kServer,const MouseServer& mServer )
:	gfx( hWnd ),
	audio( hWnd ),
	kbd( kServer ),
	mouse( mServer )
{
	srand( (unsigned int)time( NULL ) );
}

Grid grid(80, 0, 30);
ButtonManager* MyButtons = nullptr;
DebugGUI* debuggui;

void Game::Initialise() {
	PixelDest screen = PixelDest(&gfx);
	out = new TestInterface(screen);
	MyButtons = new ButtonManager(&mouse);
	debuggui = new DebugGUI(&mouse);
	srand(time(0));
}

void Game::ComposeFrame() {
	
	grid.Draw(out);
	MyButtons->Draw(out);
	debuggui->Draw(out);

}

void Game::UpdateModel()
{
	MyButtons->RefreshState();
	debuggui->Update();
	

}


