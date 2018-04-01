#ifndef __BITMAP_H__
#define __BITMAP_H__
#include "Colors.h"
#include <math.h>
#include <stdio.h>
#include "OutputStream.h"
#include "Func.h"

class Bitmap {

public:
	Bitmap(char* FileName);
	Bitmap(char* FileName, Color c) :Bitmap(FileName) { keying_enabled = true; bckclr = c; }
	Bitmap(int width, int height, Color bkclr);
	~Bitmap();

	void ReserveMemory(int width, int height, Color bkclr);
	
public:
	int width, height;
	Color* data;

	int pixelcount() { return width * height; }
	Color* GetPixelPointer(int x, int y);
	bool  GetIsBackground(Color c) { return  keying_enabled && GetBackgroundSimilarity(c) < tolerance; }
	float GetBackgroundSimilarity(Color c);

public:
	double tolerance = 0.000001;
	Color bckclr = 0;
	bool keying_enabled = false;

public: 
	Bitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT);
	Bitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT, float size);
};


class ImageSplitCorners {
public:
	Bitmap * cleft = nullptr, *cright = nullptr, *cmiddle = nullptr;
	int width, height;
	ImageSplitCorners(Bitmap* img) {
		this->width = img->width;
		this->height = img->height;
		float corners = 0.3f;
		float perOne = corners / 2;
		float perMid = 1 - corners;
		int sidew = perOne * img->width;
		int middlew = perMid * img->width;
		cleft = img->GetBitmapPart(0, 0, sidew, img->height);
		cright = img->GetBitmapPart(0 + sidew + middlew, 0, sidew, img->height);
		cmiddle = img->GetBitmapPart(0 + sidew, 0, middlew, img->height);
	}

	~ImageSplitCorners() {
		delete cleft; delete cright; delete cmiddle;
	}
};


class ButtonImageGroup {
public:
	ImageSplitCorners * normal = nullptr;
	ImageSplitCorners* hover = nullptr;
	ImageSplitCorners* press = nullptr;

	ButtonImageGroup(char* src, Color key, bool single) {
		Bitmap* img = new Bitmap(src, key);
		if (single) {
			normal = hover = press = new ImageSplitCorners(img);
		}
		else {
			int sizeh = img->height / 3;
			int sizew = img->width;

			Bitmap * Bnormal = img->GetBitmapPart(0 , sizeh * 0, sizew, sizeh);
			Bitmap * Bhover = img->GetBitmapPart(0, sizeh * 1, sizew, sizeh);
			Bitmap * Bpress = img->GetBitmapPart(0, sizeh * 2, sizew, sizeh);

			normal = new  ImageSplitCorners(Bnormal);
			hover = new  ImageSplitCorners(Bhover);
			press = new  ImageSplitCorners(Bpress);

			delete Bnormal;
			delete Bhover;
			delete Bpress;
		}

		delete img;
	}


};

#endif
