#include "GuiBuilder.h"

TrianglePoly* poly = new  TrianglePoly(Vector2(307, 147), Vector2(468, 137), Vector2(442, 367));
void ScalePoly20x() {
	poly->Scale(Vector2(2, 2));
}
void ScalePoly05x() {
	poly->Scale(Vector2(0.5, 0.5));
}

void RotatePolyP15() {
	poly->RotateRad(15);
}
void RotatePolyN15() {
	poly->RotateRad(-15);
}