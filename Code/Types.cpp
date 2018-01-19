#include "Types.h"

float Vector2::GetSquareDistance(Vector2 other)
{
	return GetSquareDistance2(*this, other);
}

float Vector3::GetSquareDistance(Vector3 other)
{
	return GetSquareDistance3(*this, other);
}