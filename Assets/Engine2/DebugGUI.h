#ifndef __DEBUG_GUI_H__
#define __DEBUG_GUI_H__
#include <time.h>
#include "TestInterface.h"
#include "Labelz.h"
#include <vector>
class DebugGUI {
protected:
	int FPS_frame = 0;
	float FPS_elapsed_from_last_update = 0;
	clock_t begin = -1;
	MouseClient* mouse;
	Vector2 mouseOld;
public:
	Label * MousePosLabel;
	Label* FRA_label;
	Label* FPS_label;
	Label* EPS_label;
	std::vector<Label*> AutoDrawL;

	

	void Init() {
		FRA_label = new Label(0, 0, &DOS_BLACK, "NO_FRAME_UPDATE");
		FPS_label = new Label(0, 24, &DOS_BLACK, "NO_FPS_UPDATE");
		EPS_label = new Label(0, 48, &DOS_BLACK, "NO_EPS_UPDATE");
	    MousePosLabel = new Label(0, 72, &DOS_BLACK, "NO_MOUSE_UPDATE");
		
		AutoDrawL.push_back(FRA_label);
		AutoDrawL.push_back(FPS_label);
		AutoDrawL.push_back(EPS_label);
		AutoDrawL.push_back(MousePosLabel);
	}

	DebugGUI(MouseClient* mouse){
		mouseOld= Vector2(0, 0);
		this->mouse = mouse;
		Init();
	}
	
	void Update() {
		UpdateFrameInfo();
		Vector2 mousepos = Vector2(mouse->GetMouseX(), mouse->GetMouseY());
		float diffx = mousepos.x - mouseOld.x;
		float diffy = mousepos.y - mouseOld.y;
		mouseOld = mousepos;
		MousePosLabel->SetText("MouseX: %3.0f + %3.0f\nMouseY: %3.0f + %3.0f\0", mousepos.x, diffx, mousepos.y, diffy);
		
	}

	void UpdateFrameInfo();

	void Draw(TestInterface *out) {
		
		
		
		for (std::vector<Label*>::iterator it = AutoDrawL.begin(); it != AutoDrawL.end(); ++it) {
			out->DrawLabel(*it);
		}
	}

};

#endif