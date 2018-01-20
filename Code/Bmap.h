#ifndef __BITMAP_H__
#define __BITMAP_H__
#include "Colors.h"
#include <math.h>
#include <stdio.h>
#include "OutputStream.h"
#include "Func.h"

class Bitmap {

public:
	Bitmap(char* FileName);
	Bitmap(char* FileName, Color c) :Bitmap(FileName) { keying_enabled = true; bckclr = c; }
	Bitmap(int width, int height, Color bkclr);
	~Bitmap();

	void ReserveMemory(int width, int height, Color bkclr);
	
public:
	int width, height;
	Color* data;

	int pixelcount() { return width * height; }
	Color* GetPixelPointer(int x, int y);
	bool  GetIsBackground(Color c) { return  keying_enabled && GetBackgroundSimilarity(c) < tolerance; }
	float GetBackgroundSimilarity(Color c);

public:
	double tolerance = 0.000001;
	Color bckclr = 0;
	bool keying_enabled = false;

public: 
	Bitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT);
	Bitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT, float size);
};


#endif
