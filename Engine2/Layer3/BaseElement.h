#pragma once

#include "Layer2.h"
#include "ElementProperty.h"
#include <map>

class BaseElement
{
public:
	static std::map<std::string, int> class_map;

public:
  static GFXDraw* draw;
  static IOgroup* io;

public:
  ElementProperty property;
  virtual void Draw () { _DrawSimple (); } //default drawing, can be overriden
  virtual void Update () = 0;

public:
	BaseElement (std::string name);
	BaseElement (std::string classname, V2 pos, Vector2 size);
	void _DrawSimple () { DrawName (); DrawBorder (); DrawCorners (); }

	virtual ~BaseElement ()= 0{}

protected:
	void DrawName ();
	void DrawBorder ();
	void DrawCorners ();
};

#include "Container.h"
