#ifndef ARENA.H
#define ARENA .H
#include "Point2D.h"

enum class PlayerType { PREY, PREDATOR };

class Arena {
private:
  static constexpr int WIDTH = 30;
  static constexpr int HEIGHT = 30;
  static constexpr int MOVES_LIMIT = 100;

  Point2D preyPos;
  Point2D predatorPos;
  PlayerType pl;

public:
  static Arena *getInstance();

  Arena()
      : preyPos(WIDTH / 2, HEIGHT / 2), predatorPos(0, 0),
        pl(PlayerType::PREY) {}

  Point2D getPreyPosition() const { return preyPos; }
  Point2D getPredatorPosition() const { return predatorPos; }

  static int getWidth() { return WIDTH; }
  static int getHeight() { return HEIGHT; }

  void setPlayerType(PlayerType type) { pl = type; }

  void startGame();
};

#endif "ARENA.H"