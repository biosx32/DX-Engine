#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__
#include "Bmap.h"

class Spritesheet: public Bitmap {
public:
	Spritesheet(char* FileName, int W_COUNT, int H_COUNT);
	Spritesheet(char* FileName, int W_COUNT, int H_COUNT, int ColorReplaceMode, int ReplaceColor, int NewColor);
	~Spritesheet();

	int SH_W_COUNT;
	int SH_H_COUNT;
	int SH_SLOTS_MAX;
	int SH_SPRITE_W;
	int SH_SPRITE_H;


	

	Bitmap** SPRITE_DATA;
	

protected:
	
	void _initialise(char* FileName, int W_COUNT, int H_COUNT);
};


#endif
