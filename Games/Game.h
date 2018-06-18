/****************************************************************************************** 
 *	Chili DirectX Framework Version 12.10.21											  *	
 *	Game.h																				  *
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
#pragma once

#include "Element.h"
#include "Layer0.h"

#include "IOGroup.h"

class Game
{
private:
	void ComposeFrame();
	void UpdateModel();

private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	MouseClient mouse;
	DSound audio;
	IOgroup* io;

public:
	Game(HWND hWnd, KeyboardServer& kServer, const MouseServer& mServer)
		:gfx(hWnd),
		audio(hWnd),
		kbd(kServer),
		mouse(mServer)
	{
		io = new IOgroup(&gfx, &mouse, &kbd);
		Element::io = io;
		Element::draw = new GFXDraw (io->gfx);

		srand((unsigned int)time(NULL));
		Initialise();
	}

	~Game() {}

	void Go() {
		gfx.BeginFrame();
		UpdateModel();
		ComposeFrame();
		gfx.EndFrame();


	}

	void Initialise();
};


#define __DEBUG__ 1

#include "GameDebug.h"