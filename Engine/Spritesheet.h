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
public:
	Animation();
	Animation(int FPS, Spritesheet* sh, int s, int e);
	Animation(int FPS, Spritesheet* sh);
	void Load(int FPS, Spritesheet* sh);

	int startFrame = 0;
	int endFrame = 0;
	int currentFrame = 0;
	float frame_counter = 0.00;

	float FPS = 8.00f;
	const float FULLFPS = 60.00f;

	void SetRange(int s, int e);
	void SetFPS(float FPS);





	void ForceStep();
	void Step();
	Bitmap* GetCurrent();

	
	Spritesheet* spritesheet = nullptr;

};


#endif
