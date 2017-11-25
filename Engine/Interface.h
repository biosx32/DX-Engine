#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include "Graphics.h"
#include "Bmap.h"
//#include "Label.h"
#include <string.h>

#define YES 177


class Interface {
public:
	void set_graphics(Graphics* gfx);
//	void set_font(Label* txt);
	void DrawPixel(int x, int y, Color c);
//	void DrawText(char* str, int x, int y);
	void Draw_Bitmap(Bitmap* B, int fx, int fy);

protected:
	Graphics* gfx;
//	Label* TextObj;
	unsigned char Graphics_loaded;

	Color READ_COLOR;
	
};

#endif