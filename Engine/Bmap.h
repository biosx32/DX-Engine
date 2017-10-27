#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stdio.h>
#include "Colors.h"

#define ONE_COLOR 1
#define ANY_COLOR 2
#define NO_COLOR 0

class Bitmap {
public:
	
	Bitmap(char* FileName);
	Bitmap(Bitmap* source, int loc_x, int loc_y, int width, int height);
	~Bitmap();

	Color TRANSPARENCY_KEY = 0xb1f4b1;


	int IMG_WIDTH;
	int IMG_HEIGHT;
	int IMG_DATA_SIZE;
	int IMG_LINE_DATA;
	int IMG_PIXEL_COUNT;

	unsigned char * Data;
	unsigned char * Header;

	Bitmap* get_sprite(int loc_x, int loc_y, int WIDTH, int HEIGHT);
	int const static COLOR_BSIZE = 3 * 1;
protected:
	
	
	bool IMG_TOP_DOWN;
	bool IMG_LOADED;
	int COLOR_REPLACE_MODE;

	int Get_image_bytes(FILE* p_file, int offset);

	Color READ_COLOR;
	Color FROM_REPLACE_KEY;
	Color TO_REPLACE_KEY;

	char REP_R;
	char REP_G;
	char REP_B;
};

#endif#pragma once
