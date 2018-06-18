#pragma once
#include "Vectors.h"

struct ElementProperty
{
public:
  int ID = -1;
  std::string name = "DEFAULT";
  bool enabled = true;
  bool visible = true;

public:
  Size size;
  ElementProperty() {}
  

public:
  Vector2 GetAbs() { return parent ? position + parent->GetAbs() : position; }
  float GetAbsX() { return parent ? position.x + parent->GetAbsX() : position.x; }
  float GetAbsY() { return parent ? position.y + parent->GetAbsY() : position.y; }

  void SetRel(Vector2 pos) { position = pos; }
  void SetSize(Size next) { size = next; }

  Vector2 GetRel() { return position; }
  Vector2 GetSize() { return size; }

protected:
  ElementProperty* parent = nullptr;
  Pos position;


protected:
};