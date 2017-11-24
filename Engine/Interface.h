#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include "Graphics.h"
#include "Bmap.h"
//#include "Text.h"
#include <string.h>

#define YES 177


class Interface {
public:
	void set_graphics(Graphics* gfx);
//	void set_font(Text* txt);
	void DrawPixel(int x, int y, Color c);
//	void DrawText(char* str, int x, int y);
	void Draw_Bitmap(Bitmap* B, int fx, int fy);

protected:
	Graphics* gfx;
//	Text* TextObj;
	unsigned char Graphics_loaded;

	Color READ_COLOR;
	
};

#endif