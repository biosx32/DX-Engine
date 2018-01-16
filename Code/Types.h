#ifndef __TYPEZ_H__PRIM__
#define __TYPEZ_H__PRIM__
#include  "Func.h"
class Vector2 {
public:
	int x, y;
	Vector2(int x, int y) :x(x), y(y) {}
	float DistanceCompare(Vector2 other);
	float DistanceReal(Vector2 other) {
		return distance_real(this->x, this->y, other.x, other.y);
	}

};

#endif