#ifndef __TYPEZ_H__PRIM__
#define __TYPEZ_H__PRIM__
#include "CustomMath.h"

class Vector2 {
public:
	float x, y;
	Vector2() :Vector2(0, 0){}
	Vector2(float x, float y) :x(x), y(y) {}


	float DistanceFrom(Vector2 other);
	float GetSquareDistance2(Vector2 v1, Vector2 v2);
	
};

class Vector3: public Vector2 {
public:
	float z;
	Vector3(float x, float y, float z) :Vector2(x,y),z(z){}
	float DistanceFrom(Vector3 other);
	float GetSquareDistance3(Vector3 v1, Vector3 v2);
};



typedef Vector2 V2;
typedef Vector3 V3;
typedef V2 pos;
typedef V2 size;

#endif