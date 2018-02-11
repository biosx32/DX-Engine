#ifndef _GUI_BUILDER_H__N__
#define _GUI_BUILDER_H__N__
#include "Manager.h"

class GUI {
public:
	Manager * manager = nullptr;
	IoGroup* iog = nullptr;
	

	virtual void BuildGUI() {}
	virtual void SelfUpdate() {}
	virtual void SelfDraw() {}

	virtual void Update() {
		if (manager) {
			manager->Update();
		}
		SelfUpdate();
	}
	virtual void Draw() {
		if (manager) {
			manager->Draw();
		}
		SelfDraw();
	}


	GUI(IoGroup* iog): iog(iog) {
		this->manager = new Manager(iog);
		this->BuildGUI();
	}

};

#endif



