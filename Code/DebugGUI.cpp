#include "DebugGUI.h"


void DebugGUI::UpdateFrameInfo()
{
	const int UpdatesPerSecond = 4;
	const int FrameLimit = 60;
	const int UpdateEveryN = 60 / UpdatesPerSecond;


	FPS_frame++;
	if (FPS_frame > FrameLimit) FPS_frame = 1;

	if (FPS_frame % UpdateEveryN == 0) {
		clock_t end = clock();
		FPS_elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		begin = end;
	}

	double FPS_fps = UpdateEveryN / FPS_elapsed_secs;
	FRA_label->SetText("Frame: %02d", FPS_frame);
	EPS_label->SetText("EPS: %1.3f", FPS_elapsed_secs);
	FPS_label->SetText("FPS: %2.3f", FPS_fps);
}