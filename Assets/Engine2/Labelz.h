#ifndef __LABELZ_H___
#define __LABELZ_H___

#define TXT_BUFFER_SIZE 1024
#include "RasterFont.h"

class Label {
public:
	char text[TXT_BUFFER_SIZE];
	RasterFont* font;
	int x, y;

	Label(int x, int y, RasterFont* font, char* default_text);

	void SetText(const char *fmt, ...);
};



#endif // !__LABELZ_H___
