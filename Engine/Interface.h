#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include "Graphics.h"
#include "Bmap.h"
#include "Text.h"
#include "Graphical.h"
#include <string.h>

class Draw;

class Interface {
public:
	Interface();

	void set_graphics(Graphics* gfx);
	void DrawPixel(int x, int y, Color c);
	void DrawLabel(int x, int y, Label* label);
	void Draw_Bitmap(Bitmap* B, int fx, int fy);
	void DrawSpritesheet(Spritesheet* sh, int xoff, int yoff);
	Draw* DrawShape;

protected:
	Graphics* gfx = nullptr;
	
};

#endif