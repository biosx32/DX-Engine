#include "Animation.h"
Animation::Animation()
{
}

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
	this->endFrame = (int) (sh->sprites.size() - 1);

}

void Animation::SetRange(int s, int e)
{
	this->startFrame = s;
	this->endFrame = e;
	this->currentFrame = s;
}

void Animation::SetFPS(float FPS)
{
	this->FPS = FPS;
}

void Animation::ForceStep()
{
	currentFrame++;
	if (currentFrame > endFrame) {
		currentFrame = startFrame;
	}
}

void Animation::Step()
{
	float fps_step = FULLFPS / FPS;
	frame_counter += 1.00f;

	if (frame_counter >= fps_step) {
		frame_counter -= fps_step;
		ForceStep();
	}
}

FPixelMap * Animation::GetCurrent()
{
	return spritesheet->sprites[currentFrame];
}
