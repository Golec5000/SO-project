#ifndef SO_2_PEOPLE_H
#define SO_2_PEOPLE_H

#include <thread>
#include <random>
#include <cstdlib>
#include <atomic>
#include "Cord.h"

class People {
private:
    std::atomic_bool running;
    std::atomic_bool toErase;
    std::atomic_bool hasCrossedSwitch;
    int speed;
    std::string name;
    std::thread thread;
    Cord cord;
    char direction;

public:

    People(int x, int y);

    void moveClient();

    void joinThread();

    bool getToErase() const;

    std::string getName() const;

    char getDirection() const;

    void setDirection(char direction);

    const Cord &getCord() const;

    void setCord(const Cord &cord);

    const std::atomic_bool &getHasCrossedSwitch() const;

    void setHasCrossedSwitch(const std::atomic_bool &hasCrossedSwitch);

};


#endif //SO_2_PEOPLE_H
