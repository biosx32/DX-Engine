#pragma once
#include "Container.h"
#include "ElementProperty.h"
#include "Func3.h"
#include "IOgroup.h"
#include "Painter.h"


class Element
{
public:
  static int ElementCount;
  static GFXDraw* draw;
  static IOgroup* io;
  static BitmapFont* DFONT;

public:
  ElementProperty property;
  virtual void Update() = 0;
  virtual void Draw() = 0;

  Element();
};


class ConstructElement: public Element
{
public:
  ConstructElement(Vector2 pos, Vector2 size)
  {
    property.SetRel(pos);
    property.SetSize(size);
  }

  void DrawName();
  void DrawBorder();
  void DrawCorners();

  virtual void Update() override;
  virtual void Draw() override;

};
