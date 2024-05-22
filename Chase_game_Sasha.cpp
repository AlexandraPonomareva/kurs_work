#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Arena.h"
#include "Characters.h"
#include "Point2D.h"

class Prey : public Character {
public:
  Prey(int x, int y) : Character(x, y) {}

  void move(char key) override {
    switch (key) {
    case 'w':
      pos.y -= 1;
      break;
    case 'x':
      pos.y += 1;
      break;
    case 'a':
      pos.x -= 1;
      break;
    case 'd':
      pos.x += 1;
      break;
    case 'q':
      pos.x -= 1;
      pos.y -= 1;
      break;
    case 'e':
      pos.x += 1;
      pos.y -= 1;
      break;
    case 'z':
      pos.x -= 1;
      pos.y += 1;
      break;
    case 'c':
      pos.x += 1;
      pos.y += 1;
      break;
    }

    if (pos.x < 0)
      pos.x = 0;
    if (pos.y < 0)
      pos.y = 0;
    if (pos.x >= Arena::getWidth())
      pos.x = Arena::getWidth() - 1;
    if (pos.y >= Arena::getHeight())
      pos.y = Arena::getHeight() - 1;
  }
};

class Predator : public Character {
public:
  Predator(int x, int y) : Character(x, y) {}

  void move(char key) override {
    switch (key) {
    case 'w':
      pos.y -= 1 + (rand() % 3);
      break;
    case 'x':
      pos.y += 1 + (rand() % 3);
      break;
    case 'a':
      pos.x -= 1 + (rand() % 3);
      break;
    case 'd':
      pos.x += 1 + (rand() % 3);
      break;
    case 'q':
      pos.x -= 1 + (rand() % 3);
      pos.y -= 1 + (rand() % 3);
      break;
    case 'e':
      pos.x += 1 + (rand() % 3);
      pos.y -= 1 + (rand() % 3);
      break;
    case 'z':
      pos.x -= 1 + (rand() % 3);
      pos.y += 1 + (rand() % 3);
      break;
    case 'c':
      pos.x += 1 + (rand() % 3);
      pos.y += 1 + (rand() % 3);
      break;
    }

    if (pos.x < 0)
      pos.x = 0;
    if (pos.y < 0)
      pos.y = 0;
    if (pos.x >= Arena::getWidth())
      pos.x = Arena::getWidth() - 1;
    if (pos.y >= Arena::getHeight())
      pos.y = Arena::getHeight() - 1;
  }
};

Arena *Arena::getInstance() {
  static Arena instance;
  return &instance;
}

void Arena::startGame() {
  srand(time(nullptr));
  int movesLeft = MOVES_LIMIT;

  while (movesLeft > 0) {
    system("cls");
    for (int y = 0; y < HEIGHT; ++y) {
      for (int x = 0; x < WIDTH; ++x) {
        if (x == preyPos.x && y == preyPos.y)
          std::cout << "$ ";
        else if (x == predatorPos.x && y == predatorPos.y)
          std::cout << "@ ";
        else
          std::cout << ". ";
      }
      std::cout << std::endl;
    }

    Prey prey(preyPos.x, preyPos.y);
    Predator predator(predatorPos.x, predatorPos.y);

    if (pl == PlayerType::PREY) {
      prey.move(_getch());
      predator.move(_getch());
    } else if (pl == PlayerType::PREDATOR) {
      predator.move(_getch());
      prey.move(_getch());
    }

    preyPos = prey.getPosition();
    predatorPos = predator.getPosition();

    if (abs(preyPos.x - predatorPos.x) <= 1 &&
        abs(preyPos.y - predatorPos.y) <= 1) {
      std::cout << "Игра окончена, тебя поймали!" << std::endl;
      break;
    }

    _getch();
    --movesLeft;
  }

  if (movesLeft == 0)
    std::cout << "Игра окончена, ходы закончились." << std::endl;
}

int main() {
  PlayerType choose;
  int ch;
  std::cout << "Выбери героя:" << std::endl;
  std::cout << "1. Убийца" << std::endl;
  std::cout << "2. Жертва" << std::endl;
  std::cin >> ch;
  if (ch == 1)
    choose = PlayerType::PREDATOR;
  else
    choose = PlayerType::PREY;
  Arena::getInstance()->setPlayerType(choose);
  Arena::getInstance()->startGame();
  return 0;
}
