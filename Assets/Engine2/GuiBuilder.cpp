#include "GuiBuilder.h"



void GUI::Init() {
	this->btnManager = new ButtonManager(ioif);
	managers.push_back(btnManager);
}

void GUI::Update() {

	for (ManagerBase* man : managers) {
		man->Update();
	}

}

void GUI::Draw() {

	for (ManagerBase* man : managers) {
		man->Draw();
	}

}


