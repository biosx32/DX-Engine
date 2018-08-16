
#include "GameDebug.h"

int FPS_frame = 0;
float FPS_elapsed_from_last_update = 0;
clock_t begin = -1;
const int UpdatesPerSecond = 1;
const int FrameLimit = 60;
const int UpdateEveryN = 60 / UpdatesPerSecond;
float FPS_result = 0;


IOgroup* io = nullptr;
GFXDraw* draw = nullptr;

Label* FRA_label    =nullptr;
Label* FPS_label    =nullptr;
Label* EPS_label    =nullptr;
Label* MousePosLabel=nullptr;
Label* LIDLabel = nullptr;
Label* ProgramNameLabel = nullptr;

void
CreateDebugUI(){
	FRA_label  = new Label(Pos (0, 24), "NO_FRAME_UPDATE");
	FPS_label  = new Label(Pos (0, 0), "NO_FPS_UPDATE");
	EPS_label  = new Label(Pos (0, 48), "NO_EPS_UPDATE");
	MousePosLabel = new Label(Pos (0, 72), "NO_MOUSE_UPDATE");
	LIDLabel         = new Label(Pos (0, 99), "NO_LID_UPDATE");
	ProgramNameLabel = new Label(Pos (SCREENWIDTH / 2 - 170 / 2,
		SCREENHEIGHT - DOS_WHITE.charh),
		__PROG__HEADER_);
}

void
SetDebugIO(IOgroup* ios)
{
  io = ios;
  draw = new GFXDraw(io->gfx);
}

void
UpdateHeader()
{
  int magic =
    ProgramNameLabel->property.font->charw * ProgramNameLabel->property.text.length() / 2;
  draw->paint->line(0,
                    SCREENHEIGHT - DOS_WHITE.charh * 1.05,
                    SCREENWIDTH,
                    SCREENHEIGHT - DOS_WHITE.charh * 1.05,
                    Colors::GreenDark,
                    2);
  ProgramNameLabel->property.SetRel(
    Pos(SCREENWIDTH / 2 - magic, SCREENHEIGHT - DOS_WHITE.charh));

  FRA_label->property.SetRel(Pos(SCREENWIDTH - FRA_label->GetWidth(), 0));
  FPS_label->property.SetRel(Pos(SCREENWIDTH - FPS_label->GetWidth (), 25));
  EPS_label->property.SetRel(Pos(SCREENWIDTH - EPS_label->GetWidth(), 50));
  MousePosLabel->property.SetRel(Pos(SCREENWIDTH - MousePosLabel->GetWidth(), 75));
  LIDLabel->property.SetRel(Pos(SCREENWIDTH - LIDLabel->GetWidth(), 125));
}

void
UpdateFrameInfo()
{


  FPS_frame++;
  if (FPS_frame > FrameLimit)
    FPS_frame = 1;

  if (FPS_frame % UpdateEveryN == 0) {
    clock_t end = clock();
    FPS_elapsed_from_last_update = double(end - begin) / CLOCKS_PER_SEC;
    begin = end;
  }
  float FPS_real_elapsed = FPS_elapsed_from_last_update / UpdateEveryN;
  FPS_result = 1/FPS_real_elapsed;
  FPS_result = FPS_result > 1000 ? NAN : FPS_result;

  FRA_label->SetText(FSTR("Frame: %02d", FPS_frame));
  EPS_label->SetText(FSTR ("EPS: %0.4f", FPS_real_elapsed));
  FPS_label->SetText(FSTR ("FPS: %2.3f", FPS_result));
  MousePosLabel->SetText(FSTR ("MouseX: %3.0f(+%4.0f)\nMouseY: %3.0f(+%4.0f)",
                        io->mhelper->position.x,
                        io->mhelper->mouseDelta.x,
                        io->mhelper->position.y,
                        io->mhelper->mouseDelta.y));
  LIDLabel->SetText(FSTR("LOCKED ID: %4d", io->mhelper->lockedobject));
}


void UpdateDebugInfo(){
	UpdateHeader ();
	UpdateFrameInfo ();

}
