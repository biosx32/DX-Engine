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

Bitmap* spritesheet = new Bitmap("..\\Assets\\Resources\\test_SPRITES.bmp");


IOgroup* IOG = nullptr;
TestInterface* out = nullptr;



bool hasBullet = true;
#include "SelectBox.h"
#include "Listbox.h"
SelectBox test = SelectBox(Vector2(0, 0));
ListBox* lbox = new ListBox(Pos(100, 100), Size(500, 200));

void Game::Initialise() {
	srand(time(0));
	PixelDest screen = PixelDest(&gfx);
	out = new TestInterface(screen);
	IOG = new IOgroup(out,&mouse,&kbd,new MouseHelper(&mouse));
	lbox->Add("1-st item");
	lbox->Add("2-nd item");
	lbox->Add("3-rd item");
	lbox->Add("4-th item");
	for (int i = 5; i < 100; i++) {
		char text[400] = {};
		sprintf_s(text, "%d-th item", i);
		lbox->Add(text);
	}
	Element::io = IOG;

}
void PrintProgramHeader(IOgroup* IOG) {
	IOG->out->paint->rectangleBorder(0, 0, 170, 25, Colors::Red, 3);
	IOG->out->PrintText(5, 0, &DOS_WHITE, std::string("Sprite Saver"));
}
HScrollBar j = HScrollBar(Pos(150, 380), Size(100, 20));

void Game::ComposeFrame() {
	
	if (mouse.LeftIsPressed()) {
		if (hasBullet == true) {
			hasBullet = false;
			test.pos = IOG->mhelper->position;
			test.size = Size(0, 0);
		}
		else {
			test.Update(IOG->mhelper->position);
		}
		
	}
	else {
		hasBullet = true;
	}

	
	//out->DrawBitmap(spritesheet, 0, 0);
	test.Draw();
	out->PrintText(5, 35, &DOS_WHITE, out->LabelizeVector(test.pos, "Pos"));
	out->PrintText(5, 70, &DOS_WHITE, out->LabelizeVector(test.size, "Size"));
	lbox->Draw();


	out->PrintText(10, 350, &DOS_WHITE, out->LabelizeVector(Vector2(j.value, 0), "Scroll"));
	lbox->Update();
	j.Update();
	j.Draw();
	out->PrintText(10, 380, &DOS_WHITE, IOG->mhelper->IsFree() ? "AVAILABLE" : "TAKEN");
	///////////////////////////////////////////
	PrintProgramHeader(IOG);
	
}

void Game::UpdateModel()
{

	IOG->mhelper->Refresh();
}


