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
        //Условия краёв поля(В данном случае Prey н может ходить через стены)
        if (position.x < 0) position.x = Arena::getWidth() - 1;
        if (position.y < 0) position.y = Arena::getHeight() - 1; 
        if (position.x >= Arena::getWidth()) position.x = 0;
        if (position.y >= Arena::getHeight()) position.y = 0;
    }
  //Метод реализации поведения жертвы, когда выбран хищник 
    void moveForPredator() {
        int predX = Arena::getInstance().getPredatorPosition().x; //Получаем координату Pred по x
        int predY = Arena::getInstance().getPredatorPosition().y; //Получаем координату Pred по y
        int preyX = position.getX(); //Получаем координату Prey по x
        int preyY = position.getY(); //Получаем координату Prey по y

        //Высчитываем разницу в координатах
        int dx = abs(predX - preyX); 
        int dy = abs(predY - preyY);
        
        
        if (dx > dy) {
            //Проверяем в какую стороную лучше всего сходить и присваеваем к позиции
            int moveDirection = (preyX < predX) ? 1 : ((preyX > predX) ? -1 : 0);
            position = Point2D(preyX - moveDirection, preyY);
        }
        else {
            int moveDirection = (preyY < predY) ? 1 : ((preyY > predY) ? -1 : 0);
            position = Point2D(preyX, preyY - moveDirection);
        }
        //Условия краёв поля(В данном случае Prey не может ходить через стены,
        // т.к. имбалансная особенность, с которой нельзя выиграть за Predator)
        if (position.x < 0) position.x = 0;
        if (position.y < 0) position.y = 0;
        if (position.x >= Arena::getWidth()) position.x = Arena::getWidth() - 1;
        if (position.y >= Arena::getHeight()) position.y = Arena::getWidth() - 1;
    }
};

class Predator : public Character {
public:
    Predator(int x, int y) : Character(x, y) {}

    void move(char key) override {
        switch (key) {
        case 'w':
            position.y -= 1 + (rand() % 3);
            break;
        case 'W':
            position.y -= 1 + (rand() % 3);
            break;
        case 's':
            position.y += 1 + (rand() % 3);
            break;
        case 'S':
            position.y += 1 + (rand() % 3);
            break;
        case 'a':
            position.x -= 1 + (rand() % 3);
            break;
        case 'A':
            position.x -= 1 + (rand() % 3);
            break;
        case 'd':
            position.x += 1 + (rand() % 3);
            break;
        case 'D':
            position.x += 1 + (rand() % 3);
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
            std::cout << "Wrong button" << std::endl;
        }
        if (position.x < 0) position.x = 0;
        if (position.y < 0) position.y = 0;
        if (position.x >= Arena::getWidth()) position.x = Arena::getWidth() - 1;
        if (position.y >= Arena::getHeight()) position.y = Arena::getHeight() - 1;
    }
    //Тот же самый метод для Pred
    void moveForPrey() {

        int predX = position.getX();
        int predY = position.getY();
        int preyX = Arena::getInstance().getPreyPosition().getX();
        int preyY = Arena::getInstance().getPreyPosition().getY();

        int dx = abs(predX - preyX);
        int dy = abs(predY - preyY);
        //Только добавляем рандомное увелечение хода в position = Point2D(predX + moveDirection * distance, predY);
        int distance = rand() % 3 + 1;

        if (dx > dy) {
            int moveDirection = (predX < preyX) ? 1 : ((predX > preyX) ? -1 : 0);
            position = Point2D(predX + moveDirection * distance, predY);
        }
        else {
            int moveDirection = (predY < preyY) ? 1 : ((predY > preyY) ? -1 : 0);
            position = Point2D(predX, predY + moveDirection * distance);

        }
    }
};

// Инициализация статической переменной для реализации шаблона Singleton
Arena* Arena::instance = nullptr;


void Arena::startGame() {
    srand(time(nullptr));
    int movesLeft = MOVES_LIMIT;

    while (movesLeft > 0) {
        system("cls"); //Для коректного отображения поля
        std::cout << "+ ";
        for (int i = 0; i < WIDTH; ++i) {
            std::cout << "- ";
        }
        std::cout << "+" << std::endl;
        for (int y = 0; y < HEIGHT; ++y) {
            std::cout << "|";
            for (int x = 0; x < WIDTH; ++x) {
                if (x == preyPosition.x && y == preyPosition.y)
                    std::cout << "$ ";
                else if (x == predPosition.x && y == predPosition.y)
                    std::cout << "@ ";
                // Проверяем, достигли ли мы правой границы поля
                // else if (x == WIDTH - 1 || x == 0)
                //     std::cout << "|";
                else if (y == HEIGHT / 2) {
                    // Выводим центральную линию
                    std::cout << ". ";
                }
                else {
                    // Выводим пустые места для вертикальных линий центра
                    std::cout << "  ";
                }
            }
            std::cout << "|" << std::endl;
        }

        // Выводим нижнюю границу поля
        std::cout << "+";
        for (int i = 0; i < WIDTH; ++i) {
            std::cout << "- ";
        }
        std::cout << "+" << std::endl;

        Prey prey(preyPosition.x, preyPosition.y);
        Predator predator(predPosition.x, predPosition.y);

        if (playerType == PlayerType::PREY) {
            prey.move(_getch());
            predator.moveForPrey();
        }
        else if (playerType == PlayerType::PREDATOR) {
            predator.move(_getch());
            prey.moveForPredator();
        }

        preyPosition = prey.getPosition();
        predPosition = predator.getPosition();

        if (abs(preyPosition.x - predPosition.x) <= 1 &&
            abs(preyPosition.y - predPosition.y) <= 1) {
            std::cout << "Game over You got caught!" << std::endl;
            break;
        }

        _getch();
        --movesLeft;
    }

    if (movesLeft == 0) {
        std::cout << "Game over The moves are over." << std::endl;
    }
}

int main() {
    PlayerType choose;
    int ch;
    std::cout << "Choose hero: \n 1. Predator \n 2. Prey" << std::endl;
    std::cin >> ch;
    if (ch == 1)
        choose = PlayerType::PREDATOR;
    else if (ch == 2)
        choose = PlayerType::PREY;
    Arena::getInstance().setPlayerType(choose);
    Arena::getInstance().startGame();
    return 0;
}
