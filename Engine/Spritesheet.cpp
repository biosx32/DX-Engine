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

Animation::Animation(Spritesheet * sh)
{
	this->Load(sh);
}

void Animation::Load(Spritesheet * sh)
{
	this->spritesheet = sh;

}

void Animation::Step()
{
	currentFrame++;
	if (currentFrame > endFrame) {
		currentFrame = startFrame;
	}
}

void Animation::SynchronizedStep()
{
	float fps_step = FPS / FULLFPS;
	frame_counter += 1.00f;

	if (frame_counter >= fps_step) {
		frame_counter -= fps_step;
		Step();
	}
}

Bitmap * Animation::GetCurrent()
{
	return data->currentFrame;
}
