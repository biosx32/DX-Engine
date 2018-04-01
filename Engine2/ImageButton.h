#pragma once
#include "Button.h"
#include "Bmap.h"
#include "BitmapFont.h"
#include "GlobalObjects.h"

enum class ImageDisplay : int {
	stretch,
	scale_middle,
};

class ImageButton : public Button {
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
		if (state == MouseState::normal) {
			out->DrawBitmap(img, x, y, rx, ry);
		}
		else if (state == MouseState::hover) {
			out->DrawBitmap(img, x-1, y-1, rx, ry);
		}
		else{
			out->DrawBitmap(img, x+1, y+2, rx, ry);
		}
	

	}

	void DrawImage(Interface* out) {
		ImageSplitCorners * img = StateImages->normal;
		if (state == MouseState::press) {
			img = StateImages->press;
		}
		else if (state == MouseState::hover){
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

		int leftx = GetAbsolutePos().x;
		int middlex = leftx + img->cleft->width * ratiocorner;
		int rightx = middlex + img->cmiddle->width* ratiox;

		DrawSpecial(out,img->cleft, leftx, GetAbsolutePos().y, ratiocorner, ratioy);
		DrawSpecial(out,img->cmiddle, middlex, GetAbsolutePos().y, ratiox, ratioy);
		DrawSpecial(out,img->cright, rightx, GetAbsolutePos().y, ratiocorner, ratioy);

		
	}

	void Draw() override {
		if (autosize) {
			int txtsize = text.size() > 1 ? text.size() : 2;
			size = Vector2(font->charw *txtsize * 1.25, font->charh*1.5);
		}
		int textWidth = text.size() * font->charw;
		int textY = GetAbsolutePos().y + size.y / 2 - font->charh / 2;
		int textX = GetAbsolutePos().x + (size.x - textWidth) / 2;

		this->DrawImage(io->out);
		io->out->PrintText(textX, textY, font, text);
	}
};
