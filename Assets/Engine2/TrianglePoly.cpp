#include "TrianglePoly.h"



TrianglePoly::TrianglePoly(Vector2 vs1, Vector2 vs2, Vector2 vs3)
{
	v1 = Vector2(vs1);
	v2 = Vector2(vs2);
	v3 = Vector2(vs3);

	float xr = maximum(v1.x, v2.x, v3.x) / 2 + minimum(v1.x, v2.x, v3.x) / 2;
	float yr = maximum(v1.y, v2.y, v3.y) / 2 + minimum(v1.y, v2.y, v3.y) / 2;
	origin = Vector2(xr, yr);
}

void TrianglePoly::DrawTexture(Interface * out, Bitmap * source)
{

	out->paint->line(v1.x, v1.y, v2.x, v2.y, Colors::Red, 3);
	out->paint->line(v1.x, v1.y, v3.x, v3.y, Colors::Red, 3);

	float ymin = minimum(v1.y, v2.y, v3.y);
	float ymax = maximum(v1.y, v2.y, v3.y);
	float xmin = minimum(v1.x, v2.x, v3.x);
	float xmax = maximum(v1.x, v2.x, v3.x);
	float height = ymax - ymin + 1;
	float width = xmax - xmin + 1;

	Vector2 d1, d2, d3;
	d1 = Vector2(v1.x - xmin, v1.y - ymin);
	d2 = Vector2(v2.x - xmin, v2.y - ymin);
	d3 = Vector2(v3.x - xmin, v3.y - ymin);


	Bitmap bitmap = Bitmap(width, height, Colors::White);
	PixelDest bmpd = PixelDest(&bitmap);
	Interface bitmapdrawer = Interface(bmpd);

	bitmapdrawer.paint->line(d1.x, d1.y, d2.x, d2.y, Colors::Black, 1);
	bitmapdrawer.paint->line(d1.x, d1.y, d3.x, d3.y, Colors::Black, 1);
	bitmapdrawer.paint->line(d3.x, d3.y, d2.x, d2.y, Colors::Black, 1);
	//	out->DrawBitmap(&bitmap, 0, 100, 1, 1);
	for (int y = 0; y < height; y++) {

		for (int x = 0; x < width; x++) {


			if (*bitmap.GetPixelPointer(x, y) == Colors::Black && x + 2 < width) {

				if (*bitmap.GetPixelPointer(x + 1, y) == Colors::White) {


					bool inloop = true;
					int xt = 2;
					while (inloop) {

						if (x + xt >= width) {
							inloop = false;
							continue;
						}

						if (*bitmap.GetPixelPointer(x + xt, y) == Colors::Black) {

							for (int i = 0; i < xt; i++) {

								float radian = -1.57f;
								float matrix[3][3] = {
									{ cos(radian), -sin(radian), 0 },
								{ sin(radian),  cos(radian), 0 } ,
								{ 0, 0, 1 }
								};

								Color* srcc = source->GetPixelPointer(x + i + origin.x, y + origin.y);
								Vector2 dest = Vector2(x + i, y);
								Vector2 fest = Vector2(dest.x + xmin, dest.y + ymin);
								Vector2 rotated = GetTransformation(fest, matrix);
								if (!srcc) {
									int dstn = (xt - i);
									int mm = (y / 4 + (int)origin.y) % 2 * (x / 4 + i / 4 + (int)origin.x) % 2;
									if (mm == 0) {
										out->paint->DrawPixel(fest.x, fest.y, Colors::Gray);
									}
									if (mm == 1) {
										out->paint->DrawPixel(fest.x, fest.y, Colors::White);
									}


									continue;
								}

								out->paint->DrawPixel(fest.x, fest.y, *srcc);





							}


							x += -1 + xt;
							inloop = false;

						}
						xt++;
					}

				}

			}



		}
	}

	bitmapdrawer.paint->line(d1.x, d1.y, d2.x, d2.y, Colors::Black, 1);
	bitmapdrawer.paint->line(d1.x, d1.y, d3.x, d3.y, Colors::Black, 1);
	bitmapdrawer.paint->line(d3.x, d3.y, d2.x, d2.y, Colors::Black, 1);


}

void TrianglePoly::DrawVertex(Vector2 * pos, Interface * out, Color q)
{
	out->paint->circle(pos->x, pos->y, 5, q, true);
	char buffer[256];
	sprintf_s(buffer, "x:%3.0f\ny:%3.0f", pos->x, pos->y);
	out->paint->rectangle(pos->x + 10, pos->y - 20, 55, 40, q);
	out->paint->line(pos->x, pos->y, pos->x + 2, pos->y - 13, q);
	out->paint->FastHLine(pos->x + 2, pos->y - 13, 5, q);
	out->PrintText(pos->x + 15, pos->y - DOS_BLACK_MINI.character_map->hsize, &DOS_BLACK_MINI, buffer);
}

Vector2 TrianglePoly::GetTransformation(Vector2 orignal, float data[3][3])
{
	Vector2* pos = &orignal;
	float x = pos->x - origin.x;
	float y = pos->y - origin.y;
	float src[3] = { x, y, 1 };
	float xres = src[0] * data[0][0] + src[1] * data[0][1] + src[2] * data[0][2];
	float yres = src[0] * data[1][0] + src[1] * data[1][1] + src[2] * data[1][2];
	Vector2 npos = Vector2(xres, yres);
	return npos;
}

void TrianglePoly::ApplyMatrix(float data[3][3])
{
	for (int i = 0; i < 3; i++) {
		Vector2* pos = Vertices[i];
		float x = pos->x - origin.x;
		float y = pos->y - origin.y;
		float src[3] = { x, y, 1 };
		float xres = src[0] * data[0][0] + src[1] * data[0][1] + src[2] * data[0][2];
		float yres = src[0] * data[1][0] + src[1] * data[1][1] + src[2] * data[1][2];
		Vector2 npos = Vector2(xres, yres);
		pos->x = npos.x + origin.x;
		pos->y = npos.y + origin.y;
	}
}

void TrianglePoly::Scale(Vector2 scale)
{
	{
		float matrix[3][3] = {
			{ scale.x, 0, 0 },
		{ 0, scale.y, 0 } ,
		{ 0,       0, 1 }
		};

		ApplyMatrix(matrix);
	}
}

void TrianglePoly::Translate(Vector2 translation)
{
	{
		float matrix[3][3] = {
			{ 1, 0, translation.x },
		{ 0, 1, translation.y } ,
		{ 0, 0,             1 }
		};

		ApplyMatrix(matrix);
	}
}

void TrianglePoly::Rotate(float radian)
{
	{
		float matrix[3][3] = {
			{ cos(radian), -sin(radian), 0 },
		{ sin(radian),  cos(radian), 0 } ,
		{ 0, 0, 1 }
		};

		ApplyMatrix(matrix);
	}
}

void TrianglePoly::Draw(Interface * out)
{


	out->paint->line(v1.x, v1.y, v2.x, v2.y, Colors::Black, 6);
	out->paint->line(v1.x, v1.y, v3.x, v3.y, Colors::Black, 6);
	out->paint->line(v3.x, v3.y, v2.x, v2.y, Colors::Black, 6);


	this->DrawVertex(&v1, out, Colors::DarkGreen);
	this->DrawVertex(&v2, out, Colors::DarkGreen);
	this->DrawVertex(&v3, out, Colors::DarkGreen);
	this->DrawVertex(&origin, out, Colors::Red);

}

