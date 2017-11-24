#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stdio.h>
#include "Colors.h"
#include "Func.h"


#define ERROR_IO_READ -1
#define ERROR_EMPTY_FILE 1


class BitmapDS {
public:
	
	BitmapDS(int width, int height);
	BitmapDS(int width, int height, Color* data);
	~BitmapDS();

	int width;
	int height;
	Color * ptr;

};

class Bitmap {
public:

	Bitmap();


	BitmapDS* BitmapData;
	Color transparent_color;
	
	//virtual BitmapDS* get_sprite(int loc_x, int loc_y, int WIDTH, int HEIGHT) final;

	virtual int Load(char* FileName);
};

#endif
