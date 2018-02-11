#ifndef __LABELZ_H___
#define __LABELZ_H___
#include "Element.h"
#include <string>
using std::string;
#include "BitmapFont.h"
#include "GlobalObjects.h"

class Label: public Manageable {
public:
	string text = "";
	BitmapFont* font = &DOS_BLACK;

	Label(Vector2 position, char* newtext): Manageable(position), text(newtext) {	}
	void Update(IoGroup * ig) {}
	void Draw(IoGroup* ig) {
		ig->out->PrintText(this->pos.x, this->pos.y, this->font, this->text);
	}

	void SetText(const char *fmt, ...){
		va_list args;
		va_start(args, fmt);
		const int size = 32768;
		char buffer[size];
		int rc = vsnprintf(buffer, size - 1, fmt, args);
		text = string(buffer);
		va_end(args);
	}
};



#endif // !__LABELZ_H___