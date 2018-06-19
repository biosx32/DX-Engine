#ifndef __TYPEZ_H__PRIM__
#define __TYPEZ_H__PRIM__
#include "CustomMath.h"





class Vector2 {
public:
	float x, y;
	Vector2() :Vector2(0, 0){}
    Vector2(float a): x(a), y(a){}
	Vector2(float x, float y) :x(x), y(y) {}

	

	Vector2 operator+(Vector2 other) {
		return Vector2(this->x + other.x, this->y + other.y);
	}
	Vector2 operator-(Vector2 other) {
		return Vector2(this->x - other.x, this->y - other.y);
	}

	Vector2& operator=(const Vector2& other)
        { (*this).x = other.x;
          (*this).y = other.y;
          return (*this);
        }

	Vector2& operator+=(const Vector2& other) {
		(*this) = (*this) + other;
		return (*this);
	}
	Vector2& operator-=(const Vector2& other) {
		(*this) = (*this) - other;
		return (*this);
	}

	const float& w = x;
    const float& h = y;

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
typedef Vector2 Size;
typedef Vector2 Pos;


#endif