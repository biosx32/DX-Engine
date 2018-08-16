#pragma once

#include "Layer3.h"

#ifndef  __PROG__HEADER_
#define __PROG__HEADER_ ("Sprite Saver")
#endif // ! __PROG__HEADER_


extern int FPS_frame;
extern float FPS_elapsed_from_last_update;
extern clock_t begin;
extern const int UpdatesPerSecond;
extern const int FrameLimit;
extern const int UpdateEveryN;
extern float FPS_result;

extern IOgroup * io;
extern GFXDraw * draw ;

extern int FPS_frame;
extern float FPS_elapsed_from_last_update;
extern clock_t begin;

extern Label* FRA_label;
extern Label* FPS_label;
extern Label* EPS_label;
extern Label* MousePosLabel;
extern Label* ProgramNameLabel;


void CreateDebugUI ();
void SetDebugIO (IOgroup* ios);

void UpdateHeader ();

void UpdateFrameInfo ();

void UpdateDebugInfo ();
