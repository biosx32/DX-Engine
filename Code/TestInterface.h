#ifndef __T_INTERF_H__
#define __T_INTERF_H__
#include "Interface.h"


class TestInterface : public Interface {
public:
	TestInterface(D3DGraphics* gfx): Interface(gfx){}
	void DrawPixelContainer(PixelContainer * src, int fx, int fy);
	void DrawSpritesheet(SymetricSpriteSheet* sh, int xoff, int yoff);


};
#endif