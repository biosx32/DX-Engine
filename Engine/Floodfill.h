#ifndef __FLOODFILL_H__
#define __FLOODFILL_H__
#include "Colors.h"
#include "Interface.h"
#include "BMap.h"

enum pixelstate {
	raw = 1, background = 2, pending = 4, checked = 8, stalled = 16,
};

class FFPixel {
public:
	FFPixel(int x, int y, Color c, int state);
	int x, y;
	Color color;

	int state;

};

class PixelContainer {
public:
	int pixelcount;
	int width;
	int height;

	int pendingcount = 0;
	
	Color transparency = 0x00b1f4b1;
	FFPixel* pending[16];
	FFPixel** pixels;

	void Load(Bitmap* bmp);
	void Draw(Interface* out, int fx, int fy);
	FFPixel* getPixelAt(int x, int y);
	FFPixel* getFirstRawPixel();


	bool IsColorBackground(Color c);

	void StartVirus(FFPixel * pixel);
	void StepPending();
	void StallCheck(FFPixel * pixel);
	int AddToPendingTest(FFPixel * pixel);
	void AddToPending(FFPixel * pixel);

	FFPixel * GetPending();

	

};




#endif