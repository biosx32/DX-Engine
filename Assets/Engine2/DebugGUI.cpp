#include "DebugGUI.h"


void DebugGUI::UpdateFrameInfo()
{
	const int UpdatesPerSecond = 30;
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
	FRA_label->SetText("Frame: %02d", FPS_frame);
	EPS_label->SetText("EPS: %0.4f", FPS_real_elapsed);
	FPS_label->SetText("FPS: %2.3f", FPS_fps);
}