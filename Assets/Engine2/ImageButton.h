#pragma once
#include "Button.h"
#include "Bmap.h"
#include "RasterFont.h"
#include "GlobalObjects.h"

enum class ImageDisplay : int {
	stretch,
	scale_middle,
};

class ImageButton : public Button{
public:
	ImageDisplay display = ImageDisplay::stretch;
	bool autosize = true;
	float corners = 0.33f;
	ButtonImageGroup * StateImages = &DEFAULT_BUTTON_MULTI;
	
	ImageButton(Vector2 position, void(*function)(), char* textsrc) :
		Button(position, V2(), function, textsrc) {
	}

	ImageButton(Vector2 position, void(*function)(), char* textsrc, Vector2 size) :
		Button(position, size, function, textsrc), autosize(false) {
	}



	void DrawSpecial(Interface* out, Bitmap* img, int x, int y, float rx, float ry) {
		if (state == ButtonState::normal) {
			out->DrawBitmap(img, x, y, rx, ry);
		}
		else if (state == ButtonState::press) {
			out->DrawBitmap(img, x+1, y+2, rx, ry);
		}
		else if (state == ButtonState::hover) {
			out->DrawBitmap(img, x - img->width *0.15*rx / 2, y - img->height *0.15*ry / 2, rx*1.15, ry*1.15);
		}

	}

	void DrawImage(Interface* out) {
		ImageSplitCorners * img = StateImages->normal;
		if (state == ButtonState::press) {
			img = StateImages->press;
		}
		else if (state == ButtonState::hover){
			img = StateImages->hover;
		}


		float ratiox = size.x / img->width;
		float ratioy = size.y / img->height;
		float ratiocorner = ratiox;

		if (display == ImageDisplay::scale_middle) {
			float sidescale = corners / 2;
			int sidew_scaled = img->cleft->width * sidescale;
			ratiox = (size.x - sidew_scaled * 2) / img->cmiddle->width;
			ratiocorner = sidescale;
		}

		int leftx = pos.x;
		int middlex = leftx + img->cleft->width * ratiocorner;
		int rightx = middlex + img->cmiddle->width* ratiox;

		DrawSpecial(out,img->cleft, leftx, pos.y, ratiocorner, ratioy);
		DrawSpecial(out,img->cmiddle, middlex, pos.y, ratiox, ratioy);
		DrawSpecial(out,img->cright, rightx, pos.y, ratiocorner, ratioy);

		
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
};
