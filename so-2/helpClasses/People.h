#ifndef SO_2_PEOPLE_H
#define SO_2_PEOPLE_H

#include <thread>
#include <random>
#include <cstdlib>
#include <atomic>

class People {
private:
    std::atomic<bool> running;
    std::atomic<bool> toErase;
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
