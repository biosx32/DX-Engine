#include "Static.h"
#include "CustomMath.h"

float GetSquareDistance1(float a, float b) {
	return a >= b ? (a - b)*(a - b) : (b - a)*(b - a);
}

float GetDistance1(float a, float b) {
	return sqrt(GetSquareDistance1(a, b));
}

float Radians(float degree) {
	float deg = (int)degree % 360 + (degree - (int)degree);
	return MM_PI * deg / 180;
}

float maximum(float x, float y, float z) {
	return (x > y ? (x > z ? x : z) : (y > z ? y : z));
}

float minimum(float x, float y, float z) {
	return (x < y ? (x < z ? x : z) : (y < z ? y : z));
}


