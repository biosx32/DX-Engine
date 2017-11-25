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
	~BitmapDS();
	int width;
	int height;
	Color * ptr;
};

class Bitmap {
public:
	Bitmap();
	~Bitmap();
	BitmapDS* BitmapData;

	Bitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT);
	int Load(char* FileName);
	int SetDataSource(BitmapDS* data);

	virtual int IsColorVisible(Color color);
};

class TransparentBitmap : public Bitmap {
	Color transparency = Color(0xb1f4b1);
	int IsColorVisible(Color color) override;
};



#endif
