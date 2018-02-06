#pragma once
#include "Button.h"
#include "Bmap.h"
#include "RasterFont.h"
#include "GlobalObjects.h"

enum class ImageDisplay : int {
	stretch,
	stretch_corners,
	dynamicExtend
};

class ImageButton : public Button {
public:

	Bitmap * image = &DEFAULT_BUTTON;
	Bitmap *cleft, *cright, *cmiddle;
	bool autosize = false;
	float corners = 0.33f;
	ImageDisplay display = ImageDisplay::stretch;

	void SetImage(Bitmap* image) {
		this->image = image;
	}

	void Draw(Interface* out) {
		if (autosize) {
			size = Vector2(font->charw * text.size() * 1.25, font->charh*1.5);
		}
		int textWidth = text.size() * font->charw;
		int textY = pos.y + size.y / 2 - font->charh / 2;
		int textX = pos.x + (size.x - textWidth) / 2;

		this->DrawImage(out);
		out->PrintText(textX, textY, font, text);
	}

	void DrawSpecial(Interface* out, Bitmap* img, int x, int y, float rx, float ry) {
		if (state == ButtonState::normal) {
			out->DrawBitmap(img, x, y, rx, ry);
		}
		
		else if (state == ButtonState::press) {
			out->DrawBitmap(img, x + img->width *0.1*rx / 2, y + img->height *0.1*ry / 2, rx*0.9, ry*0.9);
		}
		else /*(state == ButtonState::hover)*/ {
			out->DrawBitmap(img, x - img->width *0.1*rx / 2, y - img->height *0.1*ry / 2, rx*1.1, ry*1.1);
		}

	}

	void DrawImage(Interface* out) {
		if (display == ImageDisplay::stretch) {
			float ratiox = size.x / image->width;
			float ratioy = size.y / image->height;
			DrawSpecial(out,image, pos.x, pos.y, ratiox, ratioy);
		}

		if (display == ImageDisplay::stretch_corners) {

			if (!cleft || !cright || !cmiddle) {
				float perOne = corners / 2;
				float perMid = 1 - corners;
				int sidew = perOne * image->width;
				int middlew = perMid * image->width;
				cleft = image->GetBitmapPart(0, 0, sidew, image->height);
				cright = image->GetBitmapPart(0 + sidew + middlew, 0, sidew, image->height);
				cmiddle = image->GetBitmapPart(0 + sidew, 0, middlew, image->height);
			}

			float sidescale = corners / 2;
			int sidew_scaled = cleft->width * sidescale;

			float ratiox = (size.x - sidew_scaled * 2) / cmiddle->width;
			float ratioy = size.y / cmiddle->height;

			int leftx = pos.x;
			int middlex = leftx + sidew_scaled;
			int rightx = middlex + cmiddle->width* ratiox;

			DrawSpecial(out,cleft, leftx, pos.y, sidescale, ratioy);
			DrawSpecial(out,cmiddle, middlex, pos.y, ratiox, ratioy);
			DrawSpecial(out,cright, rightx, pos.y, sidescale, ratioy);


		}
	}

	ImageButton(Vector2 position, void(*function)(), char* textsrc) :
		Button(position, V2(), function, textsrc), autosize(true),
		cleft(nullptr), cright(nullptr), cmiddle(nullptr) {
	}

	ImageButton(Vector2 position, void(*function)(), char* textsrc, Vector2 size) :
		Button(position,size, function, textsrc), autosize(false),
		cleft(nullptr), cright(nullptr), cmiddle(nullptr) {
	}

};