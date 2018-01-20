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


Bitmap scaling("..\\Resources\\test_RGB.bmp",ColorARGB(255,177, 244, 177));

Game::Game( HWND hWnd,KeyboardServer& kServer,const MouseServer& mServer )
:	gfx( hWnd ),
	audio( hWnd ),
	kbd( kServer ),
	mouse( mServer )
{
	srand( (unsigned int)time( NULL ) );
}








Vector2* locked = nullptr;
Grid grid(80, 0, 30);
TrianglePoly* poly = new TrianglePoly(Vector2(307, 147),Vector2(468, 137), Vector2(442, 367));

Button Scale2x = Button(100, 240, 140, 40, "Scale 2.0x", &DOS_BLACK);
Button Scale05x = Button(100, 200, 140, 40, "Scale 0.5x", &DOS_BLACK);
Button RotateP15 = Button(100, 280, 140, 40, "Rotate 15*", &DOS_BLACK);
Button RotateN15 = Button(100, 320, 140, 40, "Rotate -15*", &DOS_BLACK);
float scale = 0;


Vector2 mouseOld(0, 0);
Vector2 mousePosition(0, 0);
Vector2 mouseDifference(0,0);



Label MousePosLabel(0, 72, &DOS_BLACK, "NO_MOUSE_UPDATE");
DebugGUI debuggui = DebugGUI();

void Game::Initialise() {
	out = new TestInterface(&gfx);
	srand(time(0));
}

void Game::ComposeFrame() {

	
	out->DrawLabel(&MousePosLabel);
	grid.Draw(out);
	
	
	poly->Draw(out);

	Scale2x.Draw(out);
	Scale05x.Draw(out);
	RotateP15.Draw(out);
	RotateN15.Draw(out);

	debuggui.Draw(out);

}

void Game::UpdateModel()
{
	debuggui.UpdateFrameInfo();


	mousePosition.x = mouse.GetMouseX();
	mousePosition.y = mouse.GetMouseY();
	mouseDifference.x = mousePosition.x - mouseOld.x;
	mouseDifference.y = mousePosition.y - mouseOld.y;
	mouseOld = mousePosition;
	MousePosLabel.SetText("MouseX: %3.0f + %3.0f\nMouseY: %3.0f + %3.0f\0", mousePosition.x, mouseDifference.x, mousePosition.y, mouseDifference.y);

	if (locked)
	{
		locked->x += (float)mouseDifference.x;
		locked->y += (float)mouseDifference.y;
	}


	Scale05x.RefreshState(mouse);
	Scale2x.RefreshState(mouse);
	RotateP15.RefreshState(mouse);
	RotateN15.RefreshState(mouse);

	if (Scale05x.isRelease(mouse)) {
		poly->Scale(Vector2(0.5, 0.5));
	}
	if (Scale2x.isRelease(mouse)) {
		poly->Scale(Vector2(2, 2));

	}if (RotateP15.isRelease(mouse)) {
		poly->RotateRad(15);
	}
	if (RotateN15.isRelease(mouse)) {
		poly->RotateRad(-15);
	}




	if (mouse.LeftIsPressed()) {
		Vector2* checkVerts[] = { poly->v1,poly->v2, poly->v3, poly->origin };
		Vector2* closest = nullptr;
		float closest_dis = 100000;
		for (int i = 0; i < sizeof(checkVerts) / sizeof(closest); i++) {
			Vector2* pos = checkVerts[i];
			float dis = pos->DistanceFrom(mousePosition);
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

}


