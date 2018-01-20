#include "CustomMath.h"

float GetSquareDistance1(float a, float b) {
	return a >= b ? (a - b)*(a - b) : (b - a)*(b - a);
}

float Radians(float degree) {
	float deg = (int)degree % 360 + (degree - (int)degree);
	return MM_PI * deg / 180;
}

int maximum(float x, float y, float z) {
	return (x > y ? (x > z ? x : z) : (y > z ? y : z));
}

int minimum(float x, float y, float z) {
	return (x < y ? (x < z ? x : z) : (y < z ? y : z));
}

void SwapNumbers(int * x1, int * x0)
{
	if (1) {
		int t = *x1;
		*x1 = *x0;
		*x0 = t;
	}
}
