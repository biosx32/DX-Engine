#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stdio.h>
#include "Colors.h"
#include "Func.h"

#define ERROR_IO_READ -1
#define ERROR_EMPTY_FILE 1

enum BitmapType {
	normal,
	transparent
};


class BitmapDS {
public:
	
	BitmapDS(int width, int height);
	~BitmapDS();
	int width;
	int height;
	Color * ptr;
};


class Bitmap;
class BitmapProperties;
class TransparentBitmap;

class BitmapProperties {
public:
	virtual int IsColorTransparent(Color color) = 0;
	virtual int GetBitmapType() = 0;
	virtual Bitmap * GetTypeInstance() = 0;

};


class Bitmap : BitmapProperties {
public:
	Bitmap();
	Bitmap(Bitmap* src);
	~Bitmap();
	BitmapDS* BitmapData;
	Bitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT);

	int Load(char* FileName);
	int SetDataSource(BitmapDS* data);

	virtual int IsColorTransparent(Color color) override;
	virtual int GetBitmapType() override;
	virtual Bitmap * GetTypeInstance() override;
};

class TransparentBitmap : public Bitmap {
public:

	TransparentBitmap(Bitmap* src);
	Color transparency = 0x00b1f4b1;
	TransparentBitmap();

	virtual int IsColorTransparent(Color color) override;
	virtual int GetBitmapType() override;
	virtual Bitmap * GetTypeInstance() override;
	
};







#endif
