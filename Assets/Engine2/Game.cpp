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

TextBox* tbox = nullptr;
CheckBox* CheckBox1 = nullptr;



void AddButton() {
	ImageButton* random = new ImageButton(Pos(0, 0), 0, tbox->text);
	int maxx = 800 - random->font->charw * random->text.length();
	int maxy = 600 - random->font->charh;

	Vector2 pos = Vector2(rand() % maxx, rand() % maxy);
	random->rel_pos = pos;
	if (CheckBox1->checked) {
		random->display = ImageDisplay::scale_middle;
	}
	MainGUI->Add(random);

}



void BuildTestGUI() {
	tbox = new TextBox(Pos(200, 250), 15);
	CheckBox1 = new CheckBox(Pos(10, 10), "Check box");
	
	MainGUI = new CleanGUI(IOG);
//	MainGUI->Add(CheckBox1);
//	MainGUI->Add(new ImageButton(Pos(235, 360), AddButton, "Add Random"));
//	MainGUI->Add(tbox);
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


