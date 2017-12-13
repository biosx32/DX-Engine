#include "Spritesheet.h"




Spritesheet::Spritesheet(TransparentBitmap * BitmapImage)
{

}

Spritesheet::~Spritesheet() {
	for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
	{
		delete *it;
	}
}




