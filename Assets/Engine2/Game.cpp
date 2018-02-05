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
DebugGUI* debuggui = nullptr;
GUI*test = nullptr;


Bitmap button = Bitmap("..\\Assets\\Resources\\Buttons\\test.bmp",Colors::White);
void Game::Initialise() {
	PixelDest screen = PixelDest(&gfx);
	out = new TestInterface(screen);
	debuggui = new DebugGUI(&mouse);
	test = new GUI();
	srand(time(0));
	button.tolerance = 0.001f;

	test->buttonManager->Add(new Button(150, 0, 135, 40, "Scale 2.0x", &DOS_BLACK, nullptr));
	test->buttonManager->Add(new Button(280, 0, 135, 40, "Scale 0.5x", &DOS_BLACK_MINI, nullptr));
	test->buttonManager->Add(new Button(410, 0, 135, 40, "Rotate 15*", &DOS_WHITE, nullptr));
	test->buttonManager->Add(new Button(540, 0, 135, 40, "Rotate -15*", &DOS_WHITE_MINI, nullptr));
	test->out = out;
	test->mouse = &mouse;

}

void Game::ComposeFrame() {
	out->DrawBitmap(&button, 50, 100, 0.25, 0.25);
	out->DrawBitmap(&button, 50, 150, 0.5, 0.25);
	out->DrawBitmap(&button, 50, 200, 0.99, 0.25);
	grid.Draw(out);
	debuggui->Draw(out);
	test->Draw();
}



void Game::UpdateModel()
{
	
	debuggui->Update();
	test->Update();
}


