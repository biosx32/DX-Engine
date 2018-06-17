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
	
	ImageButton(Vector2 position, void(*function)(), std::string textsrc) :
		Button(position, V2(), function, textsrc) {
	}

	ImageButton(Vector2 position, void(*function)(), std::string textsrc, Vector2 size) :
		Button(position, size, function, textsrc), autosize(false) {
	}



	void DrawSpecial(Bitmap* img, int x, int y, float rx, float ry) {
		if (mregion->state == MouseState::none) {
			draw->DrawBitmap(img, x, y, rx, ry);
		}
		else if (mregion->state == MouseState::hovered) {
			draw->DrawBitmap(img, x-1, y-1, rx, ry);
		}
		else{
			draw->DrawBitmap(img, x+1, y+2, rx, ry);
		}
	

	}

	void DrawImage() {
		Vector2 pos = GetAbs();
		ImageSplitCorners * img = StateImages->none;
		if (mregion->state == MouseState::pressed) {
			img = StateImages->pressed;
		}
		else if (mregion->state == MouseState::hovered){
			img = StateImages->hovered;
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

		DrawSpecial(img->cleft, leftx, pos.y, ratiocorner, ratioy);
		DrawSpecial(img->cmiddle, middlex, pos.y, ratiox, ratioy);
		DrawSpecial(img->cright, rightx, pos.y, ratiocorner, ratioy);

		
	}

	void Draw() override {
		Vector2 pos = GetAbs();
		if (autosize) {
			int txtsize = text.size() > 1 ? text.size() : 2;
			size = Vector2(DFONT->charw *txtsize * 1.25, DFONT->charh*1.5);
			mregion->size = size;
		}
		int textWidth = text.size() * DFONT->charw;
		int textY = pos.y + size.y / 2 - DFONT->charh / 2;
		int textX = pos.x + (size.x - textWidth) / 2;

		this->DrawImage();
		PrintText(draw, textX, textY, text,DFONT);
	}
};
