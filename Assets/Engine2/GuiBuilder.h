#ifndef _GUI_BUILDER_H__N__
#define _GUI_BUILDER_H__N__

#include "Vectors.h"
#include "Mouse.h"
#include "Colors.h"
#include "RasterFont.h"
#include "TestInterface.h"
#include "Button.h"
#include "ButtonManager.h"
#include <vector>
using std::vector;

extern RasterFont DOS_BLACK_MINI;
extern RasterFont DOS_BLACK     ;
extern RasterFont DOS_WHITE_MINI;
extern RasterFont DOS_WHITE     ;

class GUI {
public:

	MouseClient* mouse = nullptr;
	ButtonManager* buttonManager = nullptr;
	Interface* out = nullptr;

	void InitGUI();
	void Update();
	void Draw();
	GUI(){
		InitGUI();
	}
};

#endif



