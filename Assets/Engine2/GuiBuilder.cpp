#include "GuiBuilder.h"

RasterFont DOS_BLACK_MINI("..\\Assets\\Resources\\Fonts\\DOS_FONT_BLACK_MINI.bin");
RasterFont DOS_BLACK("..\\Assets\\Resources\\Fonts\\DOS_FONT_BLACK.bin");
RasterFont DOS_WHITE_MINI("..\\Assets\\Resources\\Fonts\\DOS_FONT_WHITE_MINI.bin");
RasterFont DOS_WHITE("..\\Assets\\Resources\\Fonts\\DOS_FONT_WHITE.bin");

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


