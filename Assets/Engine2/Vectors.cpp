#include "Vectors.h"

float Vector2::DistanceFrom(Vector2 other)
{
	return GetSquareDistance2(*this, other);
}

float Vector2::GetSquareDistance2(Vector2 v1, Vector2 v2)
{
	return GetSquareDistance1(v2.x, v1.x) + GetSquareDistance1(v2.y, v1.y);
}

float Vector3::DistanceFrom(Vector3 other)
{
	return GetSquareDistance3(*this, other);
}

float Vector3::GetSquareDistance3(Vector3 v1, Vector3 v2)
{
	return GetSquareDistance2(v1, v2) + GetSquareDistance1(v2.z, v1.z);
}

