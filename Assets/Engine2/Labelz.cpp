#include "Labelz.h"

Label::Label(int x, int y, RasterFont * font, char * default_text) :x(x), y(y), font(font) {
	memset(text, 1, sizeof(text));
	strcpy_s(text, default_text);
}

void Label::SetText(const char * fmt, ...)

{
	va_list args;
	va_start(args, fmt);
	int rc = vsnprintf(text, sizeof(text), fmt, args);
	va_end(args);
}
