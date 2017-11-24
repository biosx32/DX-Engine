#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stdio.h>
#include "Colors.h"
#include "Func.h"


#define ERROR_IO_READ -1
#define ERROR_EMPTY_FILE 1


class BitmapData {
public:
	
	BitmapData(int width, int height);
	~BitmapData();

	int width;
	int height;
	int data_count;
	Color * Data;

	

};

class Bitmap : public BitmapData {
public:
	Color transparent_color;
	
	virtual BitmapData* get_sprite(int loc_x, int loc_y, int WIDTH, int HEIGHT) final;

	virtual int Load(char* FileName);
};

#endif
