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







Vector2 oldMousePos = Vector2(0, 0);
Vector2* locked = nullptr;
Grid grid(80, 0, 30);
TrianglePoly polystat = TrianglePoly(&grid, 307, 147,468, 137, 442, 367);
Button test = Button(100, 200, 140, 40, "Rotate  90", &DOS_BLACK);
Button test2 = Button(100, 250, 140, 40, "Rotate -90", &DOS_BLACK);
float scale = 0;
void Game::Initialise() {
	out = new TestInterface(&gfx);
	srand(time(0));
}
float deg = 0;
void Game::ComposeFrame() {

	float m = 0.5* SCREENWIDTH / scaling.width;;
	out->PrintText(1, 1, getFrameNumber(), 0.25, &DOS_BLACK);


	grid.Draw(out);
	TrianglePoly* poly = &polystat;

	Vector2 mousePosition = Vector2(mouse.GetMouseX(), mouse.GetMouseY());
	Vector2 difference = Vector2(mousePosition.x - oldMousePos.x, mousePosition.y - oldMousePos.y);
	char buff[235];
	sprintf_s(buff, "Diff, x:%2.1f, y:%2.1f", difference.x, difference.y);
	out->PrintText(100, 0, buff, 0.25, &DOS_BLACK);
	oldMousePos = mousePosition;

	deg = deg*1.0001+  0.0001;
	poly->Rotate(deg);


	test.RefreshState(mouse);
	test2.RefreshState(mouse);

	if (test.isRelease(mouse)) {
		polystat.Scale(Vector2(0.5, 0.5));
	}
	if (test2.isRelease(mouse)) {
		polystat.Scale(Vector2(2, 2));
	}

	



	if (locked)
	{
		locked->x += (float)difference.x ;
		locked->y += (float)difference.y;
	}


	
	test2.Draw(out);
	test.Draw(out);
	if (mouse.LeftIsPressed()) {
		
	
			Vector2* checkVerts[] = { poly->a1,poly->a2, poly->a3, poly->origin };
			Vector2* closest = nullptr;
			float closest_dis = 100000;
			for (int i = 0; i < sizeof(checkVerts) /sizeof(closest); i++) {
				Vector2* pos = checkVerts[i];
				float dis = pos->GetSquareDistance(mousePosition);
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


