#include "Spritesheet.h"


Spritesheet::Spritesheet()
{
}

Spritesheet::Spritesheet(Bitmap * BitmapImage, int wcount, int hcount)
{
	this->Load(BitmapImage, wcount, hcount);
}

Spritesheet::~Spritesheet() {
	this->RemoveSpriteData();
}


void Spritesheet::Load(Bitmap * BitmapImage, int wcount, int hcount)
{
	this->Data = new SpritesheetDS();
	this->Data->Load(BitmapImage, wcount, hcount);
}

void Spritesheet::RemoveSpriteData()
{
	delete this->Data;
	this->Data = nullptr;

}

SpritesheetDS::~SpritesheetDS()
{
	delete[] ptr;
	this->ptr = nullptr;
}

void SpritesheetDS::Load(Bitmap * BitmapImage, int wcount, int hcount)
{

	this->wcount = wcount;
	this->hcount = hcount;
	this->count  = wcount * hcount;

	this->BitmapImage = BitmapImage;
	this->ptr = new (Bitmap*[count]);

	int sprite_width = BitmapImage->BitmapData->width / wcount;
	int sprite_height = BitmapImage->BitmapData->height / hcount;

	for (int y = 0; y < hcount; y++) {
		for (int x = 0; x < wcount; x++) {
			this->ptr[y * wcount + x] = BitmapImage->GetBitmapPart(x * sprite_width, y * sprite_height, sprite_width, sprite_height);
		}
	}
}

Animation::Animation()
{
}

Animation::Animation(int FPS, Spritesheet * sh, int s, int e): Animation(FPS, sh)
{
	this->SetRange(s, e);
}

Animation::Animation(int FPS, Spritesheet * sh)
{
	this->Load(FPS, sh);
}

void Animation::Load(int FPS, Spritesheet * sh)
{
	this->spritesheet = sh;
	this->endFrame = sh->Data->count - 1;

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

Bitmap * Animation::GetCurrent()
{
	return spritesheet->Data->ptr[currentFrame];
}
