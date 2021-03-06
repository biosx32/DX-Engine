#pragma once
#include "PixelMap.h"
#include "FloodfillMap.h"
class VectorSpriteSheet {
public:
	vector<PixelMap*> sprites;
public:
	VectorSpriteSheet(Bitmap* BitmapImage) {
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

	
	~VectorSpriteSheet(){
		for (std::vector<PixelMap*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
		{
			delete *it;
		}
	}

};

