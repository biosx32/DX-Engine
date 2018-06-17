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
#include "ColorButton.h"
#include "CheckBox.h"


MouseRegion mregion (Pos (30, 30), Size (100, 100));
MouseRegion mregion2 (Pos (70, 30), Size (100, 100));
MouseRegion mregion3 (Pos (300, 150), Size (100, 100));
ImageButton p (Pos(500,400),0,std::string("Nejake tlacidlo").c_str(),Size(120,120)); 

void Game::Initialise() {
	SetDebugIO (io);
}
CheckBox j = CheckBox (Pos (170, 170),"bekej");
void Game::UpdateModel () {
	//BaseElement::FullUpdate ();
	mregion.Update ();
	mregion2.Update ();
	mregion3.Update ();
	j.Update ();
	p.Update ();
	io->mhelper->Refresh ();

}


void Game::ComposeFrame() {

	//BaseElement::FullDraw();
	p.Draw ();
	mregion.Draw ();
	mregion2.Draw ();
	mregion3.Draw ();
	j.Draw ();
	PrintText (draw, Pos (300, 300), &DOS_BLACK, "Click count: %4d",mregion.click_count);
	DrawFrameInfo ();


}

