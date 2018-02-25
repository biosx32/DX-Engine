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

IOgroup* IOG = nullptr;
DebugGUI* DebugInfo = nullptr;
GUI * MainGUI = nullptr;
GroupBox* ukazka_tlacidla = nullptr;
GroupBox* ukazka_textove_pole = nullptr;

void TlacidloAction() {
	ukazka_tlacidla->bkclr = Colors::Red;
}

void TlacidloAction2() {
	ukazka_tlacidla->bkclr = Colors::TKEY;
}
void TlacidloAction3() {
	ukazka_tlacidla->bkclr = Colors::Blue;
}
void TlacidloAction4() {
	ukazka_tlacidla->bkclr = Colors::Green;
}

void BuildTlacidlaGroup() {
	ukazka_tlacidla = new GroupBox(Pos(10, 100), Size(200, 300), Colors::Green);
	ukazka_tlacidla->Add(new Label(Pos(5, 5), "Tlacidla:", &DOS_BLACK_HUGE));
	ukazka_tlacidla->Add(new ImageButton(Pos(30, 30 + 50), TlacidloAction, "Cervena"));
	ukazka_tlacidla->Add(new ColorButton(Pos(30, 150 + 50), TlacidloAction2, "Biela",Size(100,30) ));
	ukazka_tlacidla->Add(new ImageButton(Pos(30, 70 + 50), TlacidloAction4, "Zelena"));
	ukazka_tlacidla->Add(new ColorButton(Pos(30, 110 + 50), TlacidloAction3, "Modra", Size(100,30)));
}

void BuildTextBoxGroup() {
	ukazka_textove_pole = new GroupBox(Pos(230, 100), Size(300, 150), Colors::GrayLight);
	ukazka_textove_pole->Add(new Label(Pos(5, 5), "Textove pole:", &DOS_BLACK_HUGE));
	ukazka_textove_pole->Add(new TextBox(Pos(30, 30 + 50), 16));
	ukazka_textove_pole->Add(new TextBox(Pos(30, 30 + 50+30), 6));
}

void BuildTestGUI() {

	MainGUI = new CleanGUI(IOG);

	BuildTlacidlaGroup();
	BuildTextBoxGroup();

	MainGUI->Add(ukazka_tlacidla);
	MainGUI->Add(ukazka_textove_pole);
	MainGUI->Add(new CheckBox(Pos(230, 280), "Check box A"));
	MainGUI->Add(new CheckBox(Pos(230, 310), "Check box B"));
	MainGUI->Add(new CheckBox(Pos(230, 340), "Check box C"));
	MainGUI->Add(new Label(Pos(550, 100),"Prvy riadok\nDruhy riadok", &DOS_WHITE));
	MainGUI->Add(new Label(Pos(550, 200), "Obycajny text", &DOS_WHITE));
	MainGUI->Add(new Label(Pos(550, 250), "Obycajny text", &DOS_BLACK));
	MainGUI->Add(new Label(Pos(550, 230), "Obycajny text", &DOS_WHITE_MINI));
	MainGUI->Add(new Label(Pos(550, 280), "Obycajny text", &DOS_BLACK_MINI));
}


void Game::Initialise() {
	srand(time(0));
	PixelDest screen = PixelDest(&gfx);
	out = new TestInterface(screen);
	IOG = new IOgroup();
	IOG->mouse = &mouse;
	IOG->out = out;
	IOG->kbd = &kbd;
	IOG->mhelper = new MouseHelper(&mouse);
	DebugInfo = new DebugGUI(IOG);
	BuildTestGUI();
}

void Game::ComposeFrame() {
	MainGUI->Draw();
	DebugInfo->FPS_label->Draw();
}

void Game::UpdateModel()
{

	IOG->Update();
	DebugInfo->Update();
	MainGUI->Update();
}


