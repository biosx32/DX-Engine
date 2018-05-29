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

void AddBox();
SelectBox test = SelectBox(Vector2(0, 0));
ListBox lbox = ListBox(Pos(100, 150), Size(500, 400));
ColorButton k = ColorButton(Pos(550, 0), AddBox, "Add", Size(100, 30));

void PrintProgramHeader(Interface* out) {
	out->paint->rectangleBorder(0, SCREENHEIGHT - DOS_WHITE.charh, 170, 25, Colors::Red, 3);
	
	out->PrintText(5, SCREENHEIGHT - DOS_WHITE.charh, &DOS_WHITE, std::string("Sprite Saver"));
}

void AddBox() {
	std::string app = "";
	app.append(LabelizeVector(test.GetStart(), "Start"));
	app.append(" :: ");
	app.append(LabelizeVector(test.GetSize(), "Size"));

	lbox.Add(app);
}


Element TEM = Element(Pos(30, 30), Size(100, 100));
void Game::Initialise() {

}

void Game::UpdateModel()
{
	BaseElement::FullUpdate();

}

void Game::ComposeFrame() {

	BaseElement::FullDraw();
	TEM.Draw();


	io->out->PrintText(5, 35, &DOS_WHITE, LabelizeVector(test.GetStart(), "Start"));
	io->out->PrintText(5, 70, &DOS_WHITE, LabelizeVector(test.GetEnd(), "End"));
	io->out->PrintText(5, 100, &DOS_WHITE,LabelizeVector(test.GetSize(), "Size"));
	///////////////////////////////////////////
	PrintProgramHeader(io->out);


	io->out->PrintText(5, 180, &DOS_WHITE, "LOCKED ID: %d", io->mhelper->lockedobject);

}

