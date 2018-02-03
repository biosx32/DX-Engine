#include "RasterFont.h"


RasterFont::RasterFont(char* image_src,int wcount, int hcount, float size, Color bckclr)
{
	Bitmap* font_bitmap = new Bitmap(image_src,bckclr);
	this->character_map = new FixedSpriteArray(font_bitmap, wcount, hcount,size);
	delete font_bitmap;

}

Bitmap * RasterFont::GetCharacterRepr(char c)
{
	int fix = (c) % 256;
	int index = translate[fix];
	return this->character_map->sprites[index];
}
