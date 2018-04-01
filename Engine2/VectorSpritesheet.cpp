#include "VectorSpritesheet.h"

VectorSpriteSheet::VectorSpriteSheet(Bitmap * BitmapImage)
{
	FloodFillMap* temp = new FloodFillMap(BitmapImage);
	while (1) {
		PixelMap* naw = temp->GetNextSpriteGroup();
		if (naw == nullptr) {
			break;
		}
		else {
			this->sprites.push_back(naw);
		}
	}

}


VectorSpriteSheet::~VectorSpriteSheet() {
	for (std::vector<PixelMap*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
	{
		delete *it;
	}
}
