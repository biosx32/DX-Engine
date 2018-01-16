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


TransparentBitmap scaling("..\\Resources\\test_RGB.bmp", Colors::MakeARGB(255,177, 244, 177));

Game::Game( HWND hWnd,KeyboardServer& kServer,const MouseServer& mServer )
:	gfx( hWnd ),
	audio( hWnd ),
	kbd( kServer ),
	mouse( mServer )
{
	srand( (unsigned int)time( NULL ) );
}


void Game::Initialise() {
	out = new TestInterface(&gfx);
	srand(time(0));
}

float scale = 0;



Vector2 oldMousePos = Vector2(0, 0);
Vertex* locked = nullptr;
Grid grid(80, 0, 30);
TrianglePoly polystat = TrianglePoly(&grid, -2.5, -2.5, 2.5, -2.5, 0, 2.5);
Button test = Button(100, 200, 100, 100, "Javaskript", &DOS_BLACK);
void Game::ComposeFrame() {

	float m = 0.5* SCREENWIDTH / scaling.width;;
	out->PrintText(1, 1, getFrameNumber(), 0.25, &DOS_BLACK);


	grid.Draw(out);


	TrianglePoly* poly = &polystat;


	out->Painter->line(300, 300, mouse.GetMouseX(), mouse.GetMouseY(), Colors::Red);

	Vector2 mousePosition = Vector2(mouse.GetMouseX(), mouse.GetMouseY());
	Vector2 difference = Vector2(mousePosition.x - oldMousePos.x, mousePosition.y - oldMousePos.y);
	char buff[235];
	sprintf_s(buff, "Diff, x:%d, y:%d", difference.x, difference.y);
	out->PrintText(100, 0, buff, 0.25, &DOS_BLACK);
	oldMousePos = mousePosition;


	




	test.clr = Colors::LightGray;
	if (test.isHover(mouse)) {
		test.clr = Colors::Gray;
	}
	
	test.RefreshState(mouse);


	if (test.isRelease(mouse)) {
		prints << "error" << msgbox << clear;
	}

	



	if (locked)
	{
		locked->_x += (float)difference.x / locked->parent->size;
		locked->_y += (float)difference.y / locked->parent->size;
	}


	
	
	test.Draw(out);
	if (mouse.LeftIsPressed()) {
		
	
			Vertex* checkVerts[] = { poly->a,poly->b, poly->c, poly->origin };
			Vertex* closest = nullptr;
			float closest_dis = 100000;
			for (int i = 0; i < sizeof(checkVerts) /sizeof(Vertex*); i++) {
				Vector2 pos = checkVerts[i]->GetPosition();
				float dis = pos.DistanceCompare(mousePosition);
				if (dis < closest_dis) {
					closest_dis = dis;
					closest = checkVerts[i];
				}
			
			}
			if (closest && sqrt(closest_dis) < 10) {
				locked = closest;

				
			}
	}

	else {
		locked = nullptr;
	}



	poly->Draw(out);

}

void Game::UpdateModel()
{


}


