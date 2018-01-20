#ifndef __DEBUG_GUI_H__
#define __DEBUG_GUI_H__
#include <time.h>
#include "TestInterface.h"
#include "Labelz.h"
#include <vector>
class DebugGUI {
protected:
	int FPS_frame = 0;
	float FPS_elapsed_secs = 0;
	clock_t begin = 0;

public:
	Label* MousePosLabel;
	Label* FRA_label;
	Label* FPS_label;
	Label* EPS_label;
	std::vector<Label*> AutoDrawL;
	

	DebugGUI(){
		FRA_label = new Label(0, 0, &DOS_BLACK, "NO_FRAME_UPDATE");
		AutoDrawL.push_back(FRA_label);
		FPS_label = new Label(0, 24, &DOS_BLACK, "NO_FPS_UPDATE");
		AutoDrawL.push_back(FPS_label);
		EPS_label = new Label(0, 48, &DOS_BLACK, "NO_EPS_UPDATE");
		AutoDrawL.push_back(EPS_label);
	}

	void UpdateFrameInfo();

	void Draw(TestInterface *out) {
		for (std::vector<Label*>::iterator it = AutoDrawL.begin(); it != AutoDrawL.end(); ++it) {
			out->DrawLabel(*it);
		}
	}

};

#endif