#pragma once

#include <time.h>
#include "Labelz.h"
#include "Painter.h"

#ifndef  __PROG__HEADER_
#define __PROG__HEADER_ ("Sprite Saver")
#endif // ! __PROG__HEADER_

extern IOgroup * io;
extern GFXDraw * draw ;

extern int FPS_frame;
extern float FPS_elapsed_from_last_update;
extern clock_t begin;

extern Label FRA_label;
extern Label FPS_label;
extern Label EPS_label;
extern Label MousePosLabel;
extern Label ProgramNameLabel;

void PrintProgramHeader ();
void _UpdateFrameInfo ();

void PrintOthers ();
void SetDebugIO (IOgroup* ios);
void DrawFrameInfo ();
