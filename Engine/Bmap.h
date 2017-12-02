#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stdio.h>
#include <math.h>  
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


class Bitmap : public BitmapProperties {
public:
	Bitmap();
	Bitmap(char* FileName);
	Bitmap(int width, int height);
	~Bitmap();

	BitmapDS* BitmapData = nullptr;
	virtual Bitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT);

	int Load(char* FileName);
	int SetDataSource(BitmapDS* ptr);

	virtual int IsColorTransparent(Color color) override;
	virtual int GetBitmapType() override;
	virtual Bitmap * GetTypeInstance() override;
};

class TransparentBitmap : public Bitmap {
public:
	TransparentBitmap() : Bitmap() {}
	TransparentBitmap(char* FileName) : Bitmap(FileName) {}
	TransparentBitmap(int width, int height) : Bitmap(width, height) {}

	Color transparency = 0x00b1f4b1; // 177,244,177
	double tolerance = 0.001f;

	virtual int IsColorTransparent(Color color) override;
	virtual int GetBitmapType() override;
	virtual Bitmap * GetTypeInstance() override;

	Bitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT) override;
	
};







#endif
