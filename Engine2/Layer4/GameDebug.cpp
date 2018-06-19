#include "Static.h"
#include "GameDebug.h"



int FPS_frame = 0;
float FPS_elapsed_from_last_update = 0;
clock_t begin = -1;

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
	FRA_label  = new Label(Pos (0, 24), "NO_FRAME_UPDATE", &DOS_BLACK_MINI);
	FPS_label  = new Label(Pos (0, 0), "NO_FPS_UPDATE", &DOS_BLACK_MINI);
	EPS_label  = new Label(Pos (0, 48), "NO_EPS_UPDATE", &DOS_BLACK_MINI);
	MousePosLabel = new Label(Pos (0, 72), "NO_MOUSE_UPDATE", &DOS_BLACK_MINI);
	LIDLabel         = new Label(Pos (0, 99), "NO_LID_UPDATE", &DOS_BLACK_MINI);
	ProgramNameLabel = new Label(Pos (SCREENWIDTH / 2 - 170 / 2,
		SCREENHEIGHT - DOS_WHITE.charh),
		__PROG__HEADER_,
		&DOS_WHITE);
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
    ProgramNameLabel->property.font->charw * ProgramNameLabel->text.length() / 2;
  draw->paint->line(0,
                    SCREENHEIGHT - DOS_WHITE.charh * 1.05,
                    SCREENWIDTH,
                    SCREENHEIGHT - DOS_WHITE.charh * 1.05,
                    Colors::GreenDark,
                    2);
  ProgramNameLabel->property.SetRel(
    Pos(SCREENWIDTH / 2 - magic, SCREENHEIGHT - DOS_WHITE.charh));

  magic = FRA_label->property.font->charw * FRA_label->text.length() + 5;
  FRA_label->property.SetRel(Pos(SCREENWIDTH - magic, 0));

  magic = FPS_label->property.font->charw * FPS_label->text.length() + 5;
  FPS_label->property.SetRel(Pos(SCREENWIDTH - magic, 25));

  magic = EPS_label->property.font->charw * EPS_label->text.length() + 5;
  EPS_label->property.SetRel(Pos(SCREENWIDTH - magic, 50));

  magic = MousePosLabel->property.font->charw * MousePosLabel->text.length() / 2 + 5;
  MousePosLabel->property.SetRel(Pos(SCREENWIDTH - magic, 75));

  magic = LIDLabel->property.font->charw * LIDLabel->text.length() + 5;
  LIDLabel->property.SetRel(Pos(SCREENWIDTH - magic, 125));
}

void
UpdateFrameInfo()
{
  const int UpdatesPerSecond = 5;
  const int FrameLimit = 60;
  const int UpdateEveryN = 60 / UpdatesPerSecond;

  FPS_frame++;
  if (FPS_frame > FrameLimit)
    FPS_frame = 1;

  if (FPS_frame % UpdateEveryN == 0) {
    clock_t end = clock();
    FPS_elapsed_from_last_update = double(end - begin) / CLOCKS_PER_SEC;
    begin = end;
  }
  float FPS_real_elapsed = FPS_elapsed_from_last_update / UpdateEveryN;
  float FPS_fps = UpdateEveryN / FPS_elapsed_from_last_update;
  FPS_fps = FPS_fps > 1000 ? 0 : FPS_fps;
  FRA_label->SetText("Frame: %02d", FPS_frame);
  EPS_label->SetText("EPS: %0.4f", FPS_real_elapsed);
  FPS_label->SetText("FPS: %2.3f", FPS_fps);
  MousePosLabel->SetText("MouseX: %3.0f + %3.0f\nMouseY: %3.0f + %3.0f\0",
                        io->mhelper->position.x,
                        io->mhelper->mouseDelta.x,
                        io->mhelper->position.y,
                        io->mhelper->mouseDelta.y);
  LIDLabel->SetText("LOCKED ID: %4d", io->mhelper->lockedobject);
}


void UpdateDebugInfo(){
	UpdateHeader ();
	UpdateFrameInfo ();

}
