#include <conio.h> 
#include <cstdlib> 
#include <ctime> 
#include <iostream> 

// Определение класса Point2D для хранения двухмерных точек
class Point2D {
public:
    int x; // Координата X точки
    int y; // Координата Y точки

    // Конструктор класса Point2D, принимающий координаты x и y
    Point2D(int x, int y) : x(x), y(y) {}

    // Геттеры для доступа к координатам x и y
    int getX() const { return x; }
    int getY() const { return y; }
};

// Базовый класс Character для обозначения персонажей игры
class Character {
protected:
    Point2D position; // Позиция персонажа

public:
    // Конструктор класса Character, принимающий начальные координаты x и y
    Character(int x, int y) : position(x, y) {}

    // Абстрактный метод move, который должен быть переопределен в производных классах
    virtual void move(char key) = 0;

    // Метод для получения текущей позиции персонажа
    Point2D getPosition() const { return position; }
};

// Перечисление типов игроков
enum PlayerType { PREY, PREDATOR };

// Класс Arena представляет собой игровое поле
class Arena {
private:
    static constexpr int WIDTH = 30; 
    static constexpr int HEIGHT = 30; 
    static constexpr int MOVES_LIMIT = 100; 

    Point2D preyPosition; 
    Point2D predPosition; 
    PlayerType playerType; 

public:
    // Статическая переменная для реализации шаблона Singleton
    static Arena* instance;

    // Конструктор класса Arena
    Arena()
        : preyPosition(WIDTH / 2, HEIGHT / 2), predPosition(0, 0), playerType(PREY) {} // Инициализация позиций и типа игрока

    // Статический метод для получения единственного экземпляра класса Arena
    static Arena& getInstance() {
        if (!instance) {
            instance = new Arena();
        }
        return *instance;
    }

    // Методы для доступа к позициям жертвы и хищника
    Point2D getPreyPosition() const { return preyPosition; }
    Point2D getPredatorPosition() const { return predPosition; }

    // Статические методы для получения размеров игрового поля
    static int getWidth() { return WIDTH; }
    static int getHeight() { return HEIGHT; }

    // Метод для установки типа игрока
    void setPlayerType(PlayerType type) { playerType = type; }

    // Метод для запуска игры
    void startGame();
};
// Реализация класса Prey, наследующего от Character
class Prey : public Character {
public:
    // Конструктор класса Prey
    Prey(int x, int y) : Character(x, y) {}


    void move(char key) override {
        switch (key) {
        case 'w':
            position.y -= 1;
            break;
        case 'W':
            position.y -= 1;
            break;
        case 's':
            position.y += 1;
            break;
        case 'S':
            position.y += 1;
            break;
        case 'a':
            position.x -= 1;
            break;
        case 'A':
            position.x -= 1;
            break;
        case 'd':
            position.x += 1;
            break;
        case 'D':
            position.x += 1;
            break;
        case 'q':
            position.x -= 1;
            position.y -= 1;
            break;
        case 'Q':
            position.x -= 1;
            position.y -= 1;
            break;
        case 'e':
            position.x += 1;
            position.y -= 1;
            break;
        case 'E':
            position.x += 1;
            position.y -= 1;
            break;
        case 'z':
            position.x -= 1;
            position.y += 1;
            break;
        case 'Z':
            position.x -= 1;
            position.y += 1;
            break;
        case 'c':
            position.x += 1;
            position.y += 1;
            break;
        case 'C':
            position.x += 1;
            position.y += 1;
            break;
        default:
            std::cout << "Invalid input" << std::endl;
        }
