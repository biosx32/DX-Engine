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





Bitmap TEST("..\\Resources\\advanced.bmp", Colors::Green);
Bitmap* Compress = TEST.GetBitmapPart (0, 0, TEST.width, TEST.height,1);

VScrollBar* VarA = nullptr;
HScrollBar* VarB = nullptr;


VScrollBar* RA = nullptr;
VScrollBar* GA = nullptr;
VScrollBar* BA = nullptr;


Color A = Colors::Black;

#define _DEBUG 0
#include "GameDebug.h"

Label* slabel = nullptr;

void Game::Initialise() {
	
	if (_DEBUG) {
		SetDebugIO (io);
		CreateDebugUI ();
	}


	VarA=new VScrollBar (Pos (500, 200), Size (200, 30));
	VarA->property.name = "VarA";
	VarA->value = 0.5f;
	RA = new VScrollBar (Pos (400, 20), Size (100, 20)); RA->property.name = "R";
	GA = new VScrollBar (Pos (400, 50), Size (100, 20)); GA->property.name = "G";
	BA = new VScrollBar (Pos (400, 80), Size (100, 20)); BA->property.name = "B";
	


}

void Game::UpdateModel () {
	Container::FullUpdate ();
	A = (int)(RA->value * 255) << 16 | (int)(GA->value * 255) << 8 | (int)(BA->value * 255);	
	Compress->bckclr = A;
	Compress->bckclr_tre = VarA->value;

}


void Game::ComposeFrame() {
	if (_DEBUG) {
		UpdateDebugInfo ();
	}

	
	Container::FullDraw ();
	Element::draw->DrawBitmap (Compress, 30, 30, 1, 1);

	Element::draw->paint->rectangle (100, 300, 50, 50, A);


}

