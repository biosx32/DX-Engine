#ifndef __ANIM_H__
#define __ANIM_H__
#include "Spritesheet.h"
class Animation {
public:
	Animation();
	Animation(float FPS, VectorSpriteSheet* sh, int s, int e);
	Animation(float FPS, VectorSpriteSheet* sh);
	void Load(float FPS, VectorSpriteSheet* sh);

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
	MySprite* GetCurrent();


	VectorSpriteSheet* spritesheet = nullptr;

};
#endif