#pragma once

#include "ElementProperty.h"
#include "IOgroup.h"
#include "Painter.h"

class BaseElement
{
public:
  static int ElementCount;
  static GFXDraw* draw;
  static IOgroup* io;
  static BitmapFont* DFONT;

public:
  ElementProperty property;
  virtual void Draw() = 0;
  virtual void Update () = 0;	


  BaseElement();
};

#include "Container.h"
