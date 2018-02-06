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
	vector<ManagerBase*> managers;
	ButtonManager* btnManager = nullptr;
	IO_interface ioif;

	void Update();
	void Draw();
	void Init();

	GUI(IO_interface ioif): ioif(ioif) {
		this->Init();
	}

};

#endif



