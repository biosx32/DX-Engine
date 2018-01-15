#ifndef __T_INTERF_H__
#define __T_INTERF_H__
#include "Interface.h"


class TestInterface : public Interface {
public:
	TestInterface(D3DGraphics* gfx): Interface(gfx){}
	void DrawPixelContainer(PixelContainer * src, int fx, int fy);
	void DrawSpritesheet(SymetricSpriteSheet* sh, int xoff, int yoff);


};
class Grid {
public:
	int x, y, size;
	int mid;
	const int wc = 20;
	Grid(int x, int y, int size) : x(x), y(y), size(size) { mid = size / 2; }
	void Draw(Interface* out);
};
class Vertex {
public:
	Color c;
	float _x,_y;
	Grid* parent;
	Vertex(Grid* par, float x, float y);
	float x() { return -parent->mid+ _x ;}
	float y() { return +parent->mid -_y ;}
	float rx() { return _x * parent->size + parent->x; }
	float ry() { return _y * parent->size + parent->y; }
	
	void Draw(Interface* out);
};


class TrianglePoly {
public:
	Vertex * a, *b, *c;
	Vertex* origin;
	TrianglePoly(Grid* parent, float x, float y, float xx, float yy, float xxx, float yyy);

	void Draw(Interface* out);
};






#endif