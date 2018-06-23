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



#define __DEBUG__ 1
#ifdef __DEBUG__
#include "GameDebug.h"
#endif

Bitmap TEST("..\\Resources\\advanced.bmp", Colors::Green);
Bitmap* Compress = TEST.GetBitmapPart (0, 0, TEST.width, TEST.height,1);

VScrollBar* VarA = nullptr;
HScrollBar* VarB = nullptr;

Label * SimA = nullptr;
void Game::Initialise() {
	SetDebugIO (io);
	CreateDebugUI ();

	VarA=new VScrollBar (Pos (500, 200), Size (200, 30));
	VarA->property.name = "VarA";
	VarB=new HScrollBar (Pos (500, 300), Size (30, 200));
	VarB->property.name = "VarB";

	SimA = new Label (Pos (400, 400), "Textos");
}

void Game::UpdateModel () {
	Container::FullUpdate ();

	Compress->varA = VarA->value;
	Compress->varB = VarB->value;
	SimA->text = sprintfToString ("SimA: %3.8f", Compress->simA);

}


void Game::ComposeFrame() {

	//Element::draw->DrawBitmap (&TEST,30,30,1,1);
	//if (FPS_result> 50) {
		
	//}

	Container::FullDraw ();
	Element::draw->DrawBitmap (Compress, 30, 30, 1, 1);
	UpdateDebugInfo ();


}

