#ifndef __DEBUG_GUI_H__
#define __DEBUG_GUI_H__
#include <time.h>
#include "TestInterface.h"
#include "Label.h"
#include "GUI.h"
#include <vector>
#include "Vectors.h"


class DebugGUI: public GUI {
protected:
	int FPS_frame = 0;
	float FPS_elapsed_from_last_update = 0;
	clock_t begin = -1;
	Vector2 mouseOld = Vector2(0,0);
public:
	Label* MousePosLabel;
	Label* FRA_label;
	Label* FPS_label;
	Label* EPS_label;

	DebugGUI(IoGroup* ig) : GUI(ig) { BuildGUI(); }

	void BuildGUI() override {
		FRA_label = new Label(Pos(0, 0),"NO_FRAME_UPDATE");
		FPS_label = new Label(Pos(0, 24), "NO_FPS_UPDATE");
		EPS_label = new Label(Pos(0, 48), "NO_EPS_UPDATE");
	    MousePosLabel = new Label(Pos(0, 72), "NO_MOUSE_UPDATE");
		
		manager->Add(FRA_label);
		manager->Add(FPS_label);
		manager->Add(EPS_label);
		manager->Add(MousePosLabel);
	}
	
	void UpdateFrameInfo() {
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

	void SelfUpdate() {
		UpdateFrameInfo();
		Vector2 mousepos = Vector2(iog->mouse->GetMouseX(), iog->mouse->GetMouseY());
		float diffx = mousepos.x - mouseOld.x;
		float diffy = mousepos.y - mouseOld.y;
		mouseOld = mousepos;
		MousePosLabel->SetText("MouseX: %3.0f + %3.0f\nMouseY: %3.0f + %3.0f\0", mousepos.x, diffx, mousepos.y, diffy);
	}

	

};

#endif