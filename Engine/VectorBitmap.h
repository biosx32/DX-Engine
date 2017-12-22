#ifndef __VBMP_H__
#define __VBMP_H__
#include <vector>
#include "Bmap.h"
using std::vector;


class FPixel {
public:
	int x, y;
	Color color;
	FPixel(int x, int y, Color c) : x(x), y(y), color(c) {}
};


class VectorBitmap {

protected:
	int offx, offy;

public:
	int width, height;
	std::vector<FPixel*>* pixels;

public:
	VectorBitmap(vector<FPixel*>* src);
	VectorBitmap(TransparentBitmap* src);
	void ComputeSize();
	void NormalizeV();
	void NormalizeH();
	~VectorBitmap();

};

#endif