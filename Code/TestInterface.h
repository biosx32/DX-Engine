#ifndef __T_INTERF_H__
#define __T_INTERF_H__
#include "Interface.h"
#include "Types.h"
#include "..\Assets\Mouse.h"

class TestInterface : public Interface {
public:
	TestInterface(D3DGraphics* gfx): Interface(gfx){}
	void DrawPixelContainer(PixelContainer * src, int fx, int fy);
	void DrawSpritesheet(SymetricSpriteSheet* sh, int xoff, int yoff);


};
class Grid {
public:
	int x, y, size;
	int mid;
	const int wc = 20;
	Grid(int x, int y, int size) : x(x), y(y), size(size) { mid = wc / 2; }
	void Draw(Interface* out);
};



class Vertex {
public:
	Color c;
	float _x,_y;
	Grid* parent;
	Vertex(Grid* par, float x, float y);
	float x() { return -parent->mid+ _x ;}
	float y() { return +parent->mid -_y ;}
	float rx() { return _x * parent->size + parent->x; }
	float ry() { return _y * parent->size + parent->y; }

	Vector2 GetPosition() { return Vector2(this->rx(), this->ry()); }
	
	void Draw(Interface* out);
};




class TrianglePoly {
public:
	Vertex * a, *b, *c;
	Vertex* origin;
	TrianglePoly(Grid* parent, float x, float y, float xx, float yy, float xxx, float yyy);

	void Draw(Interface* out);
};

class Button {
public:
	int x, y;
	int w, h;
	bool depressed;
	Color clr;
	const static int bfsz = 256;
	char text[bfsz];

	FontType* font;
	void Draw(Interface* out) {
		int charcnt = strlen(text);
		int textw = charcnt * font->sprite_sheet->wsize;
		float s = (float) w/ textw;
		out->Painter->rectangle_fill(x, y, w, h, clr);
		for (int i = 0; i < 3; i++) {
			out->Painter->rectangle(x + i, y + i, w - i * 2, h - i * 2, Colors::Black);
		}
		

		int textY = y + h / 2 - s*font->sprite_sheet->hsize/2;

		int textX = x + s*textw*0.1;

		out->PrintText(textX, textY, text, s, font);

		

	}

	bool isHover(MouseClient mouse) {
		Vector2 mousePosition = Vector2(mouse.GetMouseX(), mouse.GetMouseY());
		return mousePosition.x >= x && mousePosition.y >= y && mousePosition.x < x + w && mousePosition.y < y+h;
	}

	bool isPress(MouseClient mouse) {
		Vector2 mousePosition = Vector2(mouse.GetMouseX(), mouse.GetMouseY());
		return isHover(mouse) && mouse.LeftIsPressed();
	}

	Button(int x, int y, int w, int h, char* src, FontType* font) :x(x), y(y), w(w), h(h), font(font),clr(Colors::LightGray),depressed(false) { strcpy_s(text, src); text[bfsz - 1] = 0; }
};



#endif