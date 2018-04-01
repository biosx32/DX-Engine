#include "GlobalObjects.h"

BitmapFont DOS_BLACK_MINI("..\\Assets\\Resources\\Fonts\\DOS_BLACK_MINI.bin");
BitmapFont DOS_BLACK("..\\Assets\\Resources\\Fonts\\DOS_BLACK.bin");
BitmapFont DOS_BLACK_HUGE("..\\Assets\\Resources\\Fonts\\DOS_BLACK_HUGE.bin");;
BitmapFont DOS_WHITE_MINI("..\\Assets\\Resources\\Fonts\\DOS_WHITE_MINI.bin");
BitmapFont DOS_WHITE("..\\Assets\\Resources\\Fonts\\DOS_WHITE.bin");

ButtonImageGroup DEFAULT_BUTTON_SINGLE = ButtonImageGroup("..\\Assets\\Resources\\Buttons\\test.bmp", Colors::White, 1);
ButtonImageGroup DEFAULT_BUTTON_MULTI = ButtonImageGroup("..\\Assets\\Resources\\Buttons\\test_m.bmp", Colors::Blue,0);
OutputStream DebugPrint = OutputStream();