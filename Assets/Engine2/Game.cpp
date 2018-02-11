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

DebugGUI* debuggui = nullptr;
GUI*TestGUI = nullptr;
ImageButton* TestImgButton = new ImageButton(Vector2(400, 150), 0, "HAHAHA");
IoGroup* IOG = nullptr;

void AddJozef() {
	Vector2 Pos= Vector2(rand()%800,rand()%600);
	Button* random = new ImageButton(Pos, 0, "Random");
	TestGUI->manager->Add(random);

}
void Game::Initialise() {
	srand(time(0));
	PixelDest screen = PixelDest(&gfx);
	out = new TestInterface(screen);
	
	IOG = new IoGroup();
	IOG->mouse = &mouse;
	IOG->out = out;
	IOG->kbd = &kbd;
	debuggui = new DebugGUI(IOG);
	TestGUI = new GUI(IOG);
	
	TestImgButton->display = ImageDisplay::scale_middle;
	TestGUI->manager->Add(TestImgButton);
	TestGUI->manager->Add(new ImageButton(Pos(235, 360), AddJozef, "Add Jozef"));
	TestGUI->manager->Add(new ImageButton(Pos(500,150),  0,"Scale 2.0x"));
	TestGUI->manager->Add(new ImageButton(Pos(500,280),  0, "Scale 0.5x"));
	TestGUI->manager->Add(new ImageButton(Pos(500,410),  0, "Rotate 15*"));
	TestGUI->manager->Add(new ImageButton(Pos(500,540),  0, "Rotate -15*"));


	TestGUI->manager->Add(new TextBox(Pos(200, 250), 15));
}

void Game::ComposeFrame() {
	debuggui->Draw();
	TestGUI->Draw();
}

void Game::UpdateModel()
{
	debuggui->Update();
	TestGUI->Update();
}


