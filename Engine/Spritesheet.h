#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__
#include "Bmap.h"

class SpritesheetDS {
public:
	~SpritesheetDS();

	int wcount;
	int hcount;
	int count;
	Bitmap* BitmapImage = nullptr;
	Bitmap** ptr = nullptr;
	void Load(Bitmap* BitmapImage, int wcount, int hcount);
};

class Spritesheet {
public:
	Spritesheet();
	Spritesheet(Bitmap* BitmapImage, int wcount, int hcount);
	~Spritesheet();
	SpritesheetDS* Data = nullptr;

	void Load(Bitmap* BitmapImage, int wcount, int hcount);
	void RemoveSpriteData();
};



class Animation {
	Animation();
	Animation(Spritesheet* sh);
	void Load(Spritesheet* sh);

	int startFrame = 0;
	int endFrame = 0;
	int currentFrame = 0;
	float frame_counter = 0.00;

	int FPS = 15;
	const int FULLFPS = 60;




	void Step();
	void SynchronizedStep();

	
	Spritesheet* data = nullptr;

};


#endif
