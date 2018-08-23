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

#define _DEBUG 1
#include "SelectBox.h"
SelectBox* A = nullptr;
Bitmap*q = nullptr;
Label*j = nullptr;

int clickcount = 0;
void UpScr () {
	clickcount++;
}

void Game::Initialise() {
	
	if (_DEBUG) {
		SetDebugIO (io);
		CreateDebugUI ();
	}

	A = new SelectBox (100, 200);
	j = new Label (300);
	q = new Bitmap ("..\\RESOURCES\\test_RGB.bmp");
}



void Game::UpdateModel () {
	Container::FullUpdate ();
	std::string result = FormatString ("%s\n%s\n%s%s", LabelizeVector(A->property.GetSize (),"SIZE").c_str(),
		LabelizeVector(A->GetStart (),"START").c_str (),LabelizeVector( A->GetEnd (),"END")).c_str ();
	j->SetText (result);
}


void Game::ComposeFrame() {
	float mx = (A->GetSize ().x) ? A->GetSize ().toAbs ().x / q->width : 0;
	float my = (A->GetSize ().y) ? A->GetSize ().toAbs ().y / q->height : 0;
	BaseElement::draw->DrawBitmap (q, A->GetStart ().x, A->GetStart ().y, mx, my);
	Container::FullDraw ();
	if (_DEBUG) {
		UpdateDebugInfo ();
	}
	std::string mystring = "AAA\nBBB";
	int csize = DOS_BLACK_MINI.charw * mystring.length();
	int vsize = DOS_BLACK_MINI.charh * (1+CharacterCountInString (mystring, '\n'));
	BaseElement::draw->paint->rectangleBorder (120 - csize/2,120 - vsize/2,csize,vsize,Colors::Red,3);
	PrintTextAlign (BaseElement::draw, 120, &DOS_BLACK_MINI, 1, ALIGN_VH, mystring);
	BaseElement::draw->paint->ellipse (30, 30, 30, 30, ColorARGB (127, 255, 0, 0));
	BaseElement::draw->paint->ellipse (50, 50, 30, 30, ColorARGB (127, 255, 0, 0));

	
	
}

