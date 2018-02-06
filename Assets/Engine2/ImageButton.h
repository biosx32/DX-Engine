#pragma once
#include "Button.h"
#include "Bmap.h"
#include "RasterFont.h"

enum class ImageDisplay : int {
	stretch,
	stretch_corners,
	dynamicExtend
};

class ImageButton : public Button {
public:

	Bitmap* image;
	Bitmap *cleft, *cright, *cmiddle;
	bool autosize = false;
	float corners = 0.33f;
	ImageDisplay display = ImageDisplay::stretch;

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

	void DrawImage(Interface* out){
		if (display == ImageDisplay::stretch) {
			float ratiox = size.x / image->width;
			float ratioy = size.y / image->height;
			out->DrawBitmap(image, pos.x, pos.y, ratiox, ratioy);
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

			float sidescale = corners/2;
			int sidew_scaled = cleft->width * sidescale;

			float ratiox = (size.x - sidew_scaled*2) / cmiddle->width;
			float ratioy = size.y / cmiddle->height;

			int leftx = pos.x;
			int middlex = leftx + sidew_scaled;
			int rightx = middlex + cmiddle->width* ratiox;

			out->DrawBitmap(cleft, leftx, pos.y, sidescale, ratioy);
			out->DrawBitmap(cmiddle, middlex, pos.y, ratiox, ratioy);
			out->DrawBitmap(cright, rightx , pos.y, sidescale, ratioy);
			

		}
	}

	ImageButton(Vector2 position, Vector2 size, void(*function)(), char* textsrc, RasterFont* font, Bitmap* image) :
		Button(position, size, function, textsrc, font), image(image), autosize(false),
		cleft(nullptr),cright(nullptr), cmiddle(nullptr){
	}

	ImageButton(Vector2 position, void(*function)(), string textsrc, RasterFont* font, Bitmap* image) :
		Button(position,V2(), function, textsrc, font), image(image), autosize(true),
		cleft(nullptr), cright(nullptr), cmiddle(nullptr) {
	}

};