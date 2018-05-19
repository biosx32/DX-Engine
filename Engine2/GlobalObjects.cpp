#include "Static.h"
#include "GlobalObjects.h"

BitmapFont DOS_BLACK_MINI("..\\Resources\\Fonts\\DOS_BLACK_MINI.bin");
BitmapFont DOS_BLACK("..\\Resources\\Fonts\\DOS_BLACK.bin");
BitmapFont DOS_BLACK_HUGE("..\\Resources\\Fonts\\DOS_BLACK_HUGE.bin");;
BitmapFont DOS_WHITE_MINI("..\\Resources\\Fonts\\DOS_WHITE_MINI.bin");
BitmapFont DOS_WHITE("..\\Resources\\Fonts\\DOS_WHITE.bin");

ButtonImageGroup DEFAULT_BUTTON_SINGLE = ButtonImageGroup("..\\Resources\\Buttons\\test.bmp", Colors::White, 1);
ButtonImageGroup DEFAULT_BUTTON_MULTI = ButtonImageGroup("..\\Resources\\Buttons\\test_m.bmp", Colors::Blue,0);
OutputStream DebugPrint = OutputStream();