#pragma once
#include <string>
#include "Vectors.h"
#include "Painter.h"
#include "BitmapFont.h"


void PrintText (GFXDraw * draw, Vector2 pos, BitmapFont * font, Size scale, std::string text);

void PrintText (GFXDraw * draw, Vector2 pos, BitmapFont * font, Size scale, const char * fmt, ...);
