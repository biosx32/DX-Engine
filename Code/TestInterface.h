#ifndef __T_INTERF_H__
#define __T_INTERF_H__
#include "Interface.h"
#include "Vectors.h"
#include "Labelz.h"
#include "..\Assets\Mouse.h"
#include <stdio.h>

class TestInterface : public Interface {
public:
	TestInterface(PixelDest dest) : Interface(dest) {}
	void DrawPixelContainer(PixelContainer * src, int fx, int fy);
	void DrawSpritesheet(FixedSpriteArray* sh, int xoff, int yoff);
	void DrawLabel(Label* label);
	
};


class Grid {
public:
	int x, y, size;
	int mid;
	const int wc = 20;
	Grid(int x, int y, int size) : x(x), y(y), size(size) { mid = wc / 2; }
	void Draw(Interface* out);
};



class TrianglePoly {
public:
	Vector2 v1, v2, v3, origin;
	Vector2* Vertices[3] ={ &v1, &v2, &v3 };


	TrianglePoly(Vector2 v1, Vector2 v2, Vector2 v3);

	void DrawTexture(Interface* out,Bitmap* source) {
		
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


				if (*bitmap.GetPixelPointer(x, y) == Colors::Black && x+2 < width) {

					if (*bitmap.GetPixelPointer(x+1, y) == Colors::White) {
						

						bool inloop = true;
						int xt = 2;
						while (inloop) {

							if (x + xt >= width) {
								inloop = false;
								continue;
							}

							if (*bitmap.GetPixelPointer(x + xt, y) == Colors::Black) {
								if (y % 2) {
									bitmapdrawer.paint->line(x, y, x + xt, y, Colors::Red);
								}
								else {
									bitmapdrawer.paint->line(x, y, x + xt, y, Colors::Blue);
								}
								for (int i = 0; i < xt; i++) {

									float radian = -1.57f;
									float matrix[3][3] = {
									{ cos(radian), -sin(radian), 0 },
									{ sin(radian),  cos(radian), 0 } ,
									{ 0, 0, 1 }
									};
									
									Color* srcc = source->GetPixelPointer(x + i + origin.x, y + origin.y);

									if (!srcc) {
										i = xt;
										continue;
									}

				
									Vector2 dest = Vector2(x + i, y);
									Vector2 fest = Vector2(dest.x + xmin,dest.y + ymin);

									Vector2 rotated = GetTransformation(fest, matrix);
								
								
									out->paint->DrawPixel(fest.x , fest.y, *srcc);
									
			


									
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

		bitmapdrawer.paint->line(d1.x, d1.y, d2.x, d2.y,Colors::Black, 1);
		bitmapdrawer.paint->line(d1.x, d1.y, d3.x, d3.y,Colors::Black, 1);
		bitmapdrawer.paint->line(d3.x, d3.y, d2.x, d2.y,Colors::Black, 1);




		
	
		
	}

	void DrawVertex(Vector2* pos, Interface* out, Color q) {
		out->paint->circle(pos->x, pos->y, 5,q,true);
		char buffer[256];
		sprintf_s(buffer, "x:%3.0f\ny:%3.0f", pos->x, pos->y);
		out->paint->rectangle(pos->x + 10, pos->y - 20, 55, 40, q, true);
		out->paint->line(pos->x, pos->y, pos->x + 2, pos->y - 13, q);
		out->paint->FastHLine(pos->x + 2, pos->y - 13, 5, q);
		out->PrintText(pos->x + 15, pos->y - DOS_BLACK_MINI.sprite_sheet->hsize, &DOS_BLACK_MINI, buffer);
	}

	Vector2 GetTransformation(Vector2 orignal, float data[3][3]) {
		Vector2* pos = &orignal;
		float x = pos->x - origin.x;
		float y = pos->y - origin.y;
		float src[3] = { x, y, 1 };
		float xres = src[0] * data[0][0] + src[1] * data[0][1] + src[2] * data[0][2];
		float yres = src[0] * data[1][0] + src[1] * data[1][1] + src[2] * data[1][2];
		Vector2 npos = Vector2(xres, yres);
		return npos;
	}

	void ApplyMatrix(float data[3][3]) {

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


	void Scale(Vector2 scale) {
		float matrix[3][3] = {
			{ scale.x, 0, 0 },
			{ 0, scale.y, 0 } ,
			{ 0,       0, 1 }
		};
	
		ApplyMatrix(matrix);
	}

	void Translate(Vector2 translation) {
		float matrix[3][3] = {
	    { 1, 0, translation.x },
		{ 0, 1, translation.y } ,
		{ 0, 0,             1 }
		};

		ApplyMatrix(matrix);
	}

	void Rotate(float radian) {
		float matrix[3][3] = {
		{ cos(radian), -sin(radian), 0 },
		{ sin(radian),  cos(radian), 0 } ,
		{ 0, 0, 1 }
		};

		ApplyMatrix(matrix);
	}

	void RotateRad(float degree) {
		Rotate(Radians(degree));
	}


	void Draw(Interface* out);
};






#endif