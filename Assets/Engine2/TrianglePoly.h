#pragma once
#include "Bmap.h"
#include "Vectors.h"
#include "Func.h"
#include "GuiBuilder.h"
#include "Interface.h"

class TrianglePoly {
public:
	Vector2 v1, v2, v3, origin;
	Vector2* Vertices[3] = { &v1, &v2, &v3 };


	TrianglePoly(Vector2 v1, Vector2 v2, Vector2 v3);

	void DrawTexture(Interface* out, Bitmap* source);

	void DrawVertex(Vector2* pos, Interface* out, Color q);

	Vector2 GetTransformation(Vector2 orignal, float data[3][3]);

	void ApplyMatrix(float data[3][3]);


	void Scale(Vector2 scale);

	void Translate(Vector2 translation);

	void Rotate(float radian);

	void RotateRad(float degree) {
		Rotate(Radians(degree));
	}

	void Draw(Interface* out);
};
