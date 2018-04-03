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
#include "Static.h"
#include "Game.h"

#include "SelectBox.h"
#include "Listbox.h"
#include "ColorButton.h"
#include "CheckBox.h"






void Game::UpdateModel()
{

}

void Game::ComposeFrame() {

}


/*
IOgroup* IOG = nullptr;
TestInterface* out = nullptr;

SelectBox test = SelectBox(Vector2(0, 0));
ListBox lbox = ListBox(Pos(10, 40), Size(500, 400));
CheckBox a = CheckBox(Pos(0, 0), std::string("WTF").c_str());

void Game::Initialise() {
	srand(time(0));
	PixelDest screen = PixelDest(&gfx);
	out = new TestInterface(screen);
	IOG = new IOgroup(out, &mouse, &kbd, new MouseHelper(&mouse));
	Element::io = IOG;

}
void PrintProgramHeader(IOgroup* IOG) {
	IOG->out->paint->rectangleBorder(0, 0, 170, 25, Colors::Red, 3);
	IOG->out->PrintText(5, 0, &DOS_WHITE, std::string("Sprite Saver"));
}


void AddBox() {
	std::string app = "";
	app.append(out->LabelizeVector(test.GetStart(), "Start"));
	app.append(" :: ");
	app.append(out->LabelizeVector(test.GetSize(), "Size"));
	hasBullet = true;
	lbox.Add(app);
}
ColorButton k = ColorButton(Pos(550, 0), AddBox, "Add", Size(100, 30));

void Game::UpdateModel()
{
	k.Update();
	IOG->mhelper->Refresh();
}

void Game::ComposeFrame() {
	a.Update();
	k.Update();
	lbox.Update();
	//out->DrawBitmap(spritesheet, 0, 0);
	test.Draw();
	lbox.Draw();
	k.Draw();
	out->PrintText(5, 35, &DOS_WHITE, out->LabelizeVector(test.GetStart(), "Start"));
	out->PrintText(5, 70, &DOS_WHITE, out->LabelizeVector(test.GetEnd(), "End"));
	out->PrintText(5, 100, &DOS_WHITE, out->LabelizeVector(test.GetSize(), "Size"));
	///////////////////////////////////////////
	PrintProgramHeader(IOG);
	a.Draw();
}




*/