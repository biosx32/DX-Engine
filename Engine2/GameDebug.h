#pragma once

#include <time.h>
#include "Labelz.h"
#include <vector>
#include "Vectors.h"
#include "D3DGraphics.h"
#include "Colors.h"
#include "MouseHelper.h"
#include "Painter.h"
#ifndef  __PROG__HEADER_
#define __PROG__HEADER_ ("Sprite Saver")
#endif // ! __PROG__HEADER_

IOgroup* io = BaseElement::io;
GFXDraw* draw = new GFXDraw (io->gfx);

int FPS_frame = 0;
float FPS_elapsed_from_last_update = 0;
clock_t begin = -1;

Label* FRA_label = new Label(Pos(0, 24),"NO_FRAME_UPDATE", &DOS_BLACK_MINI);
Label* FPS_label = new Label(Pos(0, 0), "NO_FPS_UPDATE",&DOS_BLACK_MINI);
Label* EPS_label = new Label(Pos(0, 48), "NO_EPS_UPDATE", &DOS_BLACK_MINI);
Label* MousePosLabel = new Label(Pos(0, 72), "NO_MOUSE_UPDATE", &DOS_BLACK_MINI);



void PrintProgramHeader() {
	draw->paint->rectangleBorder(0, SCREENHEIGHT - DOS_WHITE.charh, 170, 25, Colors::Red, 3);
	draw->PrintText(5, SCREENHEIGHT - DOS_WHITE.charh, &DOS_WHITE, std::string(__PROG__HEADER_));
}

void _UpdateFrameInfo() {
	const int UpdatesPerSecond = 5;
	const int FrameLimit = 60;
	const int UpdateEveryN = 60 / UpdatesPerSecond;


	FPS_frame++;
	if (FPS_frame > FrameLimit) FPS_frame = 1;

	if (FPS_frame % UpdateEveryN == 0) {
		clock_t end = clock();
		FPS_elapsed_from_last_update = double(end - begin) / CLOCKS_PER_SEC;
		begin = end;
	}
	float FPS_real_elapsed = FPS_elapsed_from_last_update / UpdateEveryN;
	float FPS_fps = UpdateEveryN / FPS_elapsed_from_last_update;
	FPS_fps = FPS_fps > 1000 ? 0 : FPS_fps;
	FRA_label->SetText("Frame: %02d", FPS_frame);
	EPS_label->SetText("EPS: %0.4f", FPS_real_elapsed);
	FPS_label->SetText("FPS: %2.3f", FPS_fps);
	MousePosLabel->SetText("MouseX: %3.0f + %3.0f\nMouseY: %3.0f + %3.0f\0", 
						   io->mhelper->position.x, io->mhelper->mouseDelta.x, 
						   io->mhelper->position.y, io->mhelper->mouseDelta.y);

}

void PrintOthers () {
	FRA_label->Draw()
	FPS_label->draw ();
	EPS_label->draw ();

	l* FRA_label = new Label(Pos(0, 24),"NO_FRAME_UPDATE", &DOS_BLACK_MINI);
	Label* FPS_label = new Label(Pos(0, 0), "NO_FPS_UPDATE",&DOS_BLACK_MINI);
	Label* EPS_label = new Label(Pos(0, 48), "NO_EPS_UPDATE", &DOS_BLACK_MINI);
	Label* MousePosLabel = new Label(Pos(0, 72), "NO_MOUSE_UPDATE", &DOS_BLACK_MINI);
}

void DrawFrameInfo () {
	_UpdateFrameInfo ();
	PrintProgramHeader ();
	PrintOthers ();
}



