#ifndef SO_2_PEOPLE_H
#define SO_2_PEOPLE_H

#include <iostream>
#include <thread>
#include <random>
#include <cstdlib>

class People {
private:
    bool volatile running;
    bool volatile finalDirection;
    bool volatile toErase;
    int speed;
    std::string name;
    std::thread thread;
    int xPos;
    int yPos;
    char direction;
public:

    People(int x, int y);

    void moveClient();

    void joinThread();

    int getXPos() const;

    int getYPos() const;

    bool getToErase() const;

    std::string getName() const;

    char getDirection() const;

    void setDirection(char direction);

    void setX(int x);

    void setY(int y);

};


#endif //SO_2_PEOPLE_H
