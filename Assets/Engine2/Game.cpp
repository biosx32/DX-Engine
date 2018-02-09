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

Grid grid(80, 0, 30);
DebugGUI* debuggui = nullptr;
GUI*test = nullptr;


Bitmap button = Bitmap("..\\Assets\\Resources\\Buttons\\test.bmp",Colors::White);


string j = "aa";

//Vector2 position, Vector2 size, void(*function)(), char* textsrc, RasterFont* font
Button* TestButton = new ColorButton(Vector2(100,300), Vector2(135,40),nullptr,(char*)j.c_str());
ImageButton* TestImgButton = new ImageButton(Vector2(400, 150), 0, "HAHAHA");

void RemoveJozef() {
	if (test->btnManager->Items.size() > 0) {
		test->btnManager->Items.pop_back();
	}
	
}

void AddJozef() {
	Vector2 pos= Vector2(rand()%800,rand()%600);
	
	Button* random = new ImageButton(pos, 0, "Random");
	test->btnManager->Add(random);

}


void Game::Initialise() {
	PixelDest screen = PixelDest(&gfx);
	out = new TestInterface(screen);
	debuggui = new DebugGUI(&mouse);

	IO_interface IOIF;
	IOIF.mouse = &mouse;
	IOIF.out = out;

	test = new GUI(IOIF);
	srand(time(0));
	button.tolerance = 0.001f;
	out->Test("blah");
	TestImgButton->display = ImageDisplay::scale_middle;
	test->btnManager->Add(TestImgButton);
	test->btnManager->Add(TestButton);
	test->btnManager->Add(new ImageButton(pos(235,300), RemoveJozef,  "Delete Jozef"));
	test->btnManager->Add(new ImageButton(pos(235, 360), AddJozef, "Add Jozef"));
	test->btnManager->Add(new ImageButton(pos(500,150),  0,"Scale 2.0x"));
	test->btnManager->Add(new ImageButton(pos(500,280),  0, "Scale 0.5x"));
	test->btnManager->Add(new ImageButton(pos(500,410),  0, "Rotate 15*"));
	test->btnManager->Add(new ImageButton(pos(500,540),  0, "Rotate -15*"));


	
}

void Game::ComposeFrame() {
	grid.Draw(out);
	debuggui->Draw(out);
	test->Draw();
	
}



void Game::UpdateModel()
{
	
	debuggui->Update();
	test->Update();
}


