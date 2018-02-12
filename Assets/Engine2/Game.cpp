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
#include "Checkbox.h"
#include "Group.h"
DebugGUI* debuggui = nullptr;
GUI*TestGUI = nullptr;
IOgroup* IOG = nullptr;
TextBox* tbox = nullptr;
CheckBox* CheckBox1 = nullptr;
GroupBox* gb = nullptr;
GroupBox* gb2 = nullptr;
void AddButton() {
	ImageButton* random = new ImageButton(Pos(0,0), 0, tbox->text);
	int maxx = 800- random->font->charw * random->text.length();
	int maxy = 600 - random->font->charh;
	
	Vector2 pos= Vector2(rand()%maxx,rand()%maxy);
	random->rel_pos = pos;
	if (CheckBox1->checked) {
		random->display = ImageDisplay::scale_middle;
	}
	TestGUI->Add(random);

}

void Game::Initialise() {
	srand(time(0));
	PixelDest screen = PixelDest(&gfx);
	out = new TestInterface(screen);
	tbox = new TextBox(Pos(200, 250), 15);
	IOG = new IOgroup();
	IOG->mouse = &mouse;
	IOG->out = out;
	IOG->kbd = &kbd;
	IOG->mhelper = new MouseHelper(&mouse);


	CheckBox1 = new CheckBox(Pos(10, 10), "Map corners");
	debuggui = new DebugGUI(IOG);
	gb = new GroupBox(Pos(30, 30), Size(400, 400));
	gb2 = new GroupBox(Pos(100, 100), Size(200, 200));
	gb2->Add(CheckBox1);
	ManageableElement* m = new ImageButton(Pos(20, 30), 0, "EEE");
	gb2->Add(m);
	gb->Add(gb2);
	TestGUI = new CleanGUI(IOG);
	TestGUI->Add(gb);
	TestGUI->Add(gb2);

	TestGUI->Add(m);
	TestGUI->Add(CheckBox1);
	TestGUI->Add(new ImageButton(Pos(235, 360), AddButton, "Add Random"));
	TestGUI->Add(new ImageButton(Pos(500,150),  0,"Scale 2.0x"));
	TestGUI->Add(new ImageButton(Pos(500,280),  0, "Scale 0.5x"));
	TestGUI->Add(new ImageButton(Pos(500,410),  0, "Rotate 15*"));
	TestGUI->Add(new ImageButton(Pos(500,540),  0, "Rotate -15*"));


	TestGUI->Add(tbox);
}

void Game::ComposeFrame() {
	TestGUI->Draw();
	debuggui->Draw();
}

void Game::UpdateModel()
{

	IOG->Update();
	debuggui->Update();
	TestGUI->Update();
}


