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





Bitmap TEST("..\\Resources\\advanced2.bmp", Colors::Green);
Bitmap* Compress = TEST.GetBitmapPart (0, 0, TEST.width, TEST.height,1);

VScrollBar* VarA = nullptr;
HScrollBar* VarB = nullptr;


VScrollBar* RA = nullptr;
VScrollBar* GA = nullptr;
VScrollBar* BA = nullptr;
VScrollBar* RB = nullptr;
VScrollBar* GB = nullptr;
VScrollBar* BB = nullptr;

Color A = Colors::Black;
Color B = Colors::Black;
Color C = Colors::Black;

#define _DEBUG 0
#include "GameDebug.h"

Label* slabel = nullptr;

void Game::Initialise() {
	
	if (_DEBUG) {
		SetDebugIO (io);
		CreateDebugUI ();
	}

	slabel = new Label (Pos (20, 350), "DEFTEXT");

	VarA=new VScrollBar (Pos (500, 200), Size (200, 30));
	VarA->property.name = "VarA";
	VarA->value = 0.5f;
	VarB=new HScrollBar (Pos (500, 300), Size (30, 200));
	VarB->property.name = "VarB";
	VarB->value = 0.5f;
	RA = new VScrollBar (Pos (400, 20), Size (100, 20)); RA->property.name = "R";
	GA = new VScrollBar (Pos (400, 50), Size (100, 20)); GA->property.name = "G";
	BA = new VScrollBar (Pos (400, 80), Size (100, 20)); BA->property.name = "B";
	
	RB = new VScrollBar (Pos (400, 120), Size (100, 20)); RB->property.name = "R";
	GB = new VScrollBar (Pos (400, 150), Size (100, 20)); GB->property.name = "G";
	BB = new VScrollBar (Pos (400, 180), Size (100, 20)); BB->property.name = "B";



}

void Game::UpdateModel () {
	Container::FullUpdate ();
	A = (int)(RA->value * 255) << 16 | (int)(GA->value * 255) << 8 | (int)(BA->value * 255);
	SRGB AA = SRGB (A);

	SRGB norm = AA.normalized ();
	
	B = norm.r << 16 | norm.g << 8 | norm.b;
	//B = (int)(RB->value * 255) << 16 | (int)(GB->value * 255) << 8 | (int)(BB->value * 255);



	float sim = 1;
	C = (int)(sim * 255) << 16 | (int)(sim * 255) << 8 | (int)(sim * 255);
	slabel->SetText ("%d,%d,%d to\n %d,%d,%d", AA.r,AA.g,AA.b,norm.r,norm.g,norm.b);

	Compress->varA = VarA->value;
	Compress->varB = VarB->value;
	Compress->bckclr = A;

}


void Game::ComposeFrame() {
	if (_DEBUG) {
		UpdateDebugInfo ();
	}

	
	Container::FullDraw ();
	Element::draw->DrawBitmap (Compress, 30, 30, 1, 1);

	Element::draw->paint->rectangle (100, 160, 50, 50, A);
	Element::draw->paint->rectangle (170, 160, 50, 50, B);
	Element::draw->paint->rectangle (240, 160, 50, 50, C);


}

