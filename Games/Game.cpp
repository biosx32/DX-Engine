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


void Game::Initialise() {
	SetDebugIO (io);
	CreateDebugUI ();

	new ImageButton(Pos (500, 400), 0, std::string ("Nejake tlacidlo").c_str (), Size (120, 120));
	new CheckBox (Pos (170, 170), "bekej");
	new VScrollBar (Pos (100, 200), Size (200, 30));
	new VScrollBar (Pos (100, 300), Size (200, 30));
	new HScrollBar (Pos (300, 100), Size (30, 200));

}

void Game::UpdateModel () {
	Container::FullUpdate ();

}


void Game::ComposeFrame() {

	Container::FullDraw ();
	UpdateDebugInfo ();


}

