#include "GuiBuilder.h"

RasterFont DOS_BLACK_MINI("..\\Assets\\Resources\\Fonts\\DOS_FONT_BLACK_MINI.bin");
RasterFont DOS_BLACK("..\\Assets\\Resources\\Fonts\\DOS_FONT_BLACK.bin");
RasterFont DOS_WHITE_MINI("..\\Assets\\Resources\\Fonts\\DOS_FONT_WHITE_MINI.bin");
RasterFont DOS_WHITE("..\\Assets\\Resources\\Fonts\\DOS_FONT_WHITE.bin");

void GUI::InitGUI() {
	this->buttonManager = new ButtonManager();
}

void GUI::Update() {
	this->buttonManager->SetIO(mouse, out);
	buttonManager->Update();
}

void GUI::Draw() {
	this->buttonManager->SetIO(mouse, out);
	buttonManager->Draw();
}


