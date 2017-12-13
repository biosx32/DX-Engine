#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__
#include "Bmap.h"
#include "Interface.h"


class Sprite: public VectorBitmap {

};



class Spritesheet{
public:
	Spritesheet(TransparentBitmap* BitmapImage);
	~Spritesheet();
	vector<Sprite*> sprites;
};







#endif
