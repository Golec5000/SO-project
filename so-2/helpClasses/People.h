#ifndef SO_2_PEOPLE_H
#define SO_2_PEOPLE_H

#include <thread>
#include <random>
#include <cstdlib>
#include <atomic>
#include <vector>
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
    std::atomic_bool running;
    std::atomic_bool toErase;
    std::atomic_bool hasCrossedSwitch;
    std::atomic_bool closedThreadBySpaceVar;
    int speed;
    std::string name;
    std::thread thread;
    std::shared_ptr<Cord> cord;
    char direction;
    std::vector<std::vector<Cord>> &map;
    SharedData &sharedData;

    void checkCordLimits();

    void checkEndPosition();

    void setClientDirection();

    Cord *findCord(int x, int y);

    static int getRandInt(int min, int max);

public:

    void closedThreadBySpace();

    People(std::vector<std::vector<Cord>> &map, SharedData &sharedData);

    void start();

    void moveClient();

    void joinThread();

    [[nodiscard]] bool getToErase() const;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::shared_ptr<Cord> getCord() const;

    void setCord(std::shared_ptr<Cord> newCord);

    void realseCords();

};


#endif //SO_2_PEOPLE_H
