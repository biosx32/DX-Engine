#ifndef __ANIM_H__
#define __ANIM_H__
#include "Spritesheet.h"
class Animation {
public:
	int startFrame = 0;
	int endFrame = 0;
	int currentFrame = 0;
	float frame_counter = 0.00;

	float FPS = 8.00f;
	const float FULLFPS = 60.00f;

	void SetRange(int s, int e);
	void SetFPS(float FPS);


	VectorSpriteSheet* spritesheet = nullptr;

	Animation(){}

	Animation::Animation(float FPS, VectorSpriteSheet * sh, int s, int e) : Animation(FPS, sh)
	{
		this->SetRange(s, e);
	}

	Animation::Animation(float FPS, VectorSpriteSheet * sh)
	{
		this->Load(FPS, sh);
	}

	void Animation::Load(float FPS, VectorSpriteSheet * sh)
	{
		this->spritesheet = sh;
		this->FPS = FPS;
		this->endFrame = (int)(sh->sprites.size() - 1);

	}

	void SetRange(int s, int e)
	{
		this->startFrame = s;
		this->endFrame = e;
		this->currentFrame = s;
	}

	void SetFPS(float FPS)
	{
		this->FPS = FPS;
	}

	void Step()
	{
		float fps_step = FULLFPS / FPS;
		frame_counter += 1.00f;

		if (frame_counter >= fps_step) {
			frame_counter -= fps_step;
			currentFrame++;
			if (currentFrame > endFrame) {
				currentFrame = startFrame;
			}
		}
	}

	PixelMap * Animation::GetCurrent()
	{
		return spritesheet->sprites[currentFrame];
	}



};
#endif