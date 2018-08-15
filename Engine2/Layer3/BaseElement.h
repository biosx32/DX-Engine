#pragma once

#include "ElementProperty.h"
#include "IOgroup.h"
#include "Painter.h"
#include <map>

class BaseElement
{
public:
	static std::map<std::string, int> class_map;

public:
  static GFXDraw* draw;
  static IOgroup* io;
  static BitmapFont* DFONT;

public:
  ElementProperty property;
  virtual void Draw() = 0;
  virtual void Update () = 0;	


  BaseElement(std::string classname);
  virtual void __InitName () = 0;
};

#include "Container.h"
