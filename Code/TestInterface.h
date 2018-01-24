#ifndef __T_INTERF_H__
#define __T_INTERF_H__
#include "Interface.h"
#include "Vectors.h"
#include "Labelz.h"
#include "..\Assets\Mouse.h"
#include <stdio.h>

class TestInterface : public Interface {
public:
	TestInterface(D3DGraphics* gfx): Interface(gfx){}
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
	Vector2 * v1, *v2, *v3;
	Vector2* Vertices[3] ={ v1, v2, v3 };
	Vector2* origin;
	TrianglePoly(Vector2 v1, Vector2 v2, Vector2 v3);


	void DrawTexture(Bitmap* source) {

		Vector2* v1r = new Vector2(*v1);
		Vector2* v2r = new Vector2(*v2);
		Vector2* v3r = new Vector2(*v3);

		if (v1r->x < 0) v1r->x = 0;
		if (v2r->x < 0) v2r->x = 0;
		if (v3r->x < 0) v3r->x = 0;
		if (v1r->x >= SCREENWIDTH) v1r->x = SCREENWIDTH - 1;
		if (v2r->x >= SCREENWIDTH) v2r->x = SCREENWIDTH - 1;
		if (v3r->x >= SCREENWIDTH) v3r->x = SCREENWIDTH - 1;

		if (v1r->y < 0) v1r->y = 0;
		if (v2r->y < 0) v2r->y = 0;
		if (v3r->y < 0) v3r->y = 0;
		if (v1r->y >= SCREENHEIGHT) v1r->y = SCREENHEIGHT - 1;
		if (v2r->y >= SCREENHEIGHT) v2r->y = SCREENHEIGHT - 1;
		if (v3r->y >= SCREENHEIGHT) v3r->y = SCREENHEIGHT - 1;


		Vector2* a, *b, *c;
		//zorad podla y
		Vector2* sorted[3] = { v1, v2, v3 };

		float smallest = 999999999.0f;
		int sortI = 0;
		while (sortI < 3) {
			for (int i = sortI; i < 3; i++) {
				if (Vertices[i]->x <= smallest) {
					sorted[sortI] = Vertices[i];
					smallest = Vertices[i]->x;
					sortI++;
				}
			}
		}
		int j = 00;


		//ak nie su dve rovnake y
		//najdi vektor stredneho y
		//ak current y pri kresleni = vektoru stredneho y tak prepni deltu

		bool flat = v1->y == v2->y || v1->y == v3->y || v2->y == v3->y;

		float deltaXstart = 0;
		for (int i = 0; i < 3; i++) {
			
		}


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


	void ApplyMatrix(float data[3][3]) {
		Vector2* vertices[3] = { v1,v2,v3 };

		for (int i = 0; i < 3; i++) {
			Vector2* pos = vertices[i];
			float x = pos->x - origin->x;
			float y = pos->y - origin->y;
			float src[3] = { x, y, 1 };
			float xres = src[0] * data[0][0] + src[1] * data[0][1] + src[2] * data[0][2];
			float yres = src[0] * data[1][0] + src[1] * data[1][1] + src[2] * data[1][2];
			Vector2 npos = Vector2(xres, yres);
			pos->x = npos.x + origin->x;
			pos->y = npos.y + origin->y;
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