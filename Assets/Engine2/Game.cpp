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

IOgroup* IOG = nullptr;
DebugGUI* DebugInfo = nullptr;
GUI * MainGUI = nullptr;
TestInterface* out = nullptr;
void BuildTestGUI() {

	MainGUI = new CleanGUI(IOG);
	MainGUI->Add(new Label(Pos(15, 10), "Bitmapa", &DOS_BLACK_HUGE));
	MainGUI->Add(new MBmap(Pos(15, 60), "..\\Assets\\Resources\\test_RGB.bmp", Size(1, 1)));
	MainGUI->Add(new Label(Pos(15 + 350, 10), "Bitmapa 2.0x ", &DOS_BLACK_HUGE));
	MainGUI->Add(new MBmap(Pos(15 + 350, 60), "..\\Assets\\Resources\\test_RGB.bmp", Size(2, 2)));
	MainGUI->Add(new Label(Pos(15, 10 + 200), "Bitmapa 0.5x", &DOS_BLACK_HUGE));
	MainGUI->Add(new MBmap(Pos(15, 60 + 200), "..\\Assets\\Resources\\test_RGB.bmp", Size(0.5, 0.5)));
	MainGUI->Add(new Label(Pos(15, 10 + 330), "Transparentna ", &DOS_BLACK_HUGE));
	MainGUI->Add(new MBmap(Pos(15, 60 + 330), "..\\Assets\\Resources\\test_RGB.bmp", Colors::TKEY,Size(1, 1)));

}


void Game::Initialise() {
	srand(time(0));
	PixelDest screen = PixelDest(&gfx);
	out = new TestInterface(screen);
	IOG = new IOgroup();
	IOG->mouse = &mouse;
	IOG->out = out;
	IOG->kbd = &kbd;
	IOG->mhelper = new MouseHelper(&mouse);
	DebugInfo = new DebugGUI(IOG);
	BuildTestGUI();
}

void Game::ComposeFrame() {
	MainGUI->Draw();
	DebugInfo->FPS_label->Draw();
}

void Game::UpdateModel()
{

	IOG->Update();
	DebugInfo->Update();
	MainGUI->Update();
}


