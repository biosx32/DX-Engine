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

#include "D3DGraphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Sound.h"
#include "Timer.h"
#include "FrameTimer.h"
#include "SurfaceSequence.h"

#include "OutputStream.h"
#include "Bmap.h"
#include "Func.h"
#include "Spritesheet.h"
#include "RasterFont.h"
#include "Drawing.h"
#include "VectorBitmap.h"
#include "Interface.h"
#include "TestInterface.h"
#include "DebugGUI.h"
#include "ConfigFile.h"
#include "GuiBuilder.h"
#include "TrianglePoly.h"
#include "ColorButton.h"
#include <thread>

class Game
{
public:
	Game( HWND hWnd,KeyboardServer& kServer,const MouseServer& mServer );
	~Game() {}

	void UpdateGraphics() {
		gfx.BeginFrame();
		ComposeFrame();
		gfx.EndFrame();
	}

	void Go() {
		UpdateModel();
		UpdateGraphics();
		
		
	}
	void Initialise();
	TestInterface* out;

private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */

	/********************************/
private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	MouseClient mouse;
	DSound audio;
	/********************************/
	/*  User Variables              */
	/********************************/
};