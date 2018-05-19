#ifndef _GUI_BUILDER_H__N__
#define _GUI_BUILDER_H__N__
#include "GuiElementManager.h"

class GUI: public GuiElementManager {

protected:
	virtual void Build() = 0;
	virtual void SelfUpdate() = 0;
	virtual void SelfDraw() = 0;
public:
	GUI(IOgroup* io): GuiElementManager(io) {}

};

class CleanGUI: public GUI {

protected:
	void Build() override {};
	void SelfUpdate() override {};
	void SelfDraw() override {};
public:
	CleanGUI(IOgroup* iog) : GUI(iog) {}
};

#endif



