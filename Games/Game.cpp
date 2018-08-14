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
#include "Container.h"
#include "Game.h"
#include "ColorButton.h"
#include "CheckBox.h"
#include "ScrollBars.h"
#include "Bmap.h"
#include "Func.h"

#define _DEBUG 0
#include "GameDebug.h"


void Game::Initialise() {
	
	if (_DEBUG) {
		SetDebugIO (io);
		CreateDebugUI ();
	}
	new Element (330, 330);
}

void Game::UpdateModel () {
	Container::FullUpdate ();


}


void Game::ComposeFrame() {
	Container::FullDraw ();

	if (_DEBUG) {
		UpdateDebugInfo ();
	}
	std::string mystring = "AAA\nBBB";
	int csize = DOS_BLACK_MINI.charw * mystring.length();
	int vsize = DOS_BLACK_MINI.charh * (1+CharacterCountInString (mystring, '\n'));
	Element::draw->paint->rectangleBorder (120 - csize/2,120 - vsize/2,csize,vsize,Colors::Red,3);
	PrintTextAlign (Element::draw, 120, &DOS_BLACK_MINI, 1, ALIGN_VH, mystring);
	Element::draw->paint->ellipse (30, 30, 30, 30, ColorARGB (127, 255, 0, 0));
	Element::draw->paint->ellipse (50, 50, 30, 30, ColorARGB (127, 255, 0, 0));

}

