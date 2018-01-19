#ifndef __TYPEZ_H__PRIM__
#define __TYPEZ_H__PRIM__
#include  "Func.h"
class Vector2;

class Vector2 {
public:
	float x, y;
	Vector2(float x, float y) :x(x), y(y) {}
	float GetSquareDistance(Vector2 other);

};

class Vector3: public Vector2 {
public:
	float z;
	Vector3(float x, float y, float z) :Vector2(x,y),z(z){}
	float GetSquareDistance(Vector3 other);
};



#endif