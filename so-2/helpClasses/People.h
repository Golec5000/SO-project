#ifndef SO_2_PEOPLE_H
#define SO_2_PEOPLE_H

#include <thread>
#include <random>
#include <cstdlib>
#include <memory>
#include <utility>
#include <iostream>
#include <condition_variable>
#include "Cord.h"
#include "SharedData.h"

class Cord;

class People {
private:

    std::mutex sleepMutex;
    std::condition_variable sleepCv;
    bool running;
    bool toErase;
    bool hasCrossedSwitch;
    bool closedThreadBySpaceVar;
    int speed;
    std::string name;
    std::thread thread;
    std::shared_ptr<Cord> cord;
    char direction;
    SharedData &sharedData;

    void checkCordLimits();

    void checkEndPosition();

    void setClientDirection();

    Cord *findCord(int x, int y);

    static int getRandInt(int min, int max);

public:

    void closedThreadBySpace();

    explicit People(SharedData &sharedData);

    void start();

    void moveClient();

    void joinThread();

    [[nodiscard]] bool getToErase() const;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::shared_ptr<Cord> getCord() const;

    void setCord(std::shared_ptr<Cord> newCord);

};


#endif //SO_2_PEOPLE_H
