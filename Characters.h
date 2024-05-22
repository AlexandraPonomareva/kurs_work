#ifndef CHARACTERS.H
#define CHARACTERS .H
#include "Point2D.h"

class Character {
protected:
  Point2D pos;

public:
  Character(int x, int y) : pos(x, y) {}

  virtual void move(char key) = 0;

  Point2D getPosition() const { return pos; }
};

#endif "CHARACTERS.H"