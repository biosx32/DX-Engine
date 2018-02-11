#ifndef __TYPEZ_H__PRIM__
#define __TYPEZ_H__PRIM__
#include "CustomMath.h"

class Vector2 {
public:
	float x, y;
	Vector2() :Vector2(0, 0){}
	Vector2(float x, float y) :x(x), y(y) {}


	float DistanceFrom(Vector2 other) { 
		return GetSquareDistance2(*this, other); }
	float GetSquareDistance2(Vector2 v1, Vector2 v2) { 
		return GetSquareDistance1(v2.x, v1.x) + GetSquareDistance1(v2.y, v1.y); }
	
};


class Vector3: public Vector2 {
public:
	float z;
	Vector3(float x, float y, float z) :Vector2(x,y),z(z){}
	float DistanceFrom(Vector3 other){ return GetSquareDistance3(*this, other); }
	float GetSquareDistance3(Vector3 v1, Vector3 v2) {
		return GetSquareDistance2(v1, v2) + GetSquareDistance1(v2.z, v1.z);
	};
};



typedef Vector2 V2;
typedef Vector3 V3;
typedef V2 Pos;
typedef V2 Size;

#endif