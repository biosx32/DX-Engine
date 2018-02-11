#ifndef __VBMP_H__
#define __VBMP_H__
#include "Bmap.h"
#include <vector>
using std::vector;

namespace pxstate
{
	enum Type
	{
		background = 1, checked = 2, skip = (background | checked)
	};
};


class FPixel {
public:
	int x, y;
	Color color;
	FPixel(int x, int y, Color c) : x(x), y(y), color(c) {}
};

class FFPixel : public FPixel {
public:
	int state;
	FFPixel(int x, int y, Color c, int state) : FPixel(x, y, c), state(state) {}
};



class PixelMap {

protected:
	int offx, offy;
public:
	int width, height;
	std::vector<FPixel*>* pixels;

public:
	PixelMap(vector<FPixel*>* src);
	PixelMap(Bitmap* src);
	void ComputeSize();
	void NormalizeV();
	void NormalizeH();
	~PixelMap();

};

#endif