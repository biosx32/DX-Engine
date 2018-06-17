#pragma once
#include <string>
#include "Vectors.h"
#include "Painter.h"
#include "BitmapFont.h"

void PrintText (GFXDraw * draw, Vector2 pos, std::string text, BitmapFont * font);
void PrintText (GFXDraw * draw, Vector2 pos, BitmapFont * font, const char *fmt, ...);
void PrintText (GFXDraw * draw, int x, int y, std::string text, BitmapFont * font);
