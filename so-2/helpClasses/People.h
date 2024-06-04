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

class Cord;

class People {
private:

    std::mutex sleepMutex;
    static std::condition_variable cv;
    std::condition_variable sleepCv;
    std::atomic_bool running;
    std::atomic_bool toErase;
    std::atomic_bool hasCrossedSwitch;
    std::atomic_bool closedThreadBySpace;
    int speed;
    std::string name;
    std::thread thread;
    std::shared_ptr<Cord> cord;
    char direction;
    std::vector<std::vector<Cord>> &map;
    std::atomic_int &switchCounter;
    int &switchBorder;

    void checkCordLimits();

    void checkEndPosition();

    void setClientDirection(std::atomic_bool &isSwitchBlocked);

    Cord *findCord(int x, int y);

    static int getRandInt(int min, int max);

public:

    void setClosedThreadBySpace(const std::atomic_bool &closedThreadBySpace);

    People(int x, int y, std::vector<std::vector<Cord>> &map, std::atomic_int &switchCounter, int &switchBorder);

    void start(std::atomic_bool &isSwitchBlocked);

    void moveClient(std::atomic_bool &isSwitchBlocked);

    void joinThread(std::atomic_bool &isSwitchBlocked);

    [[nodiscard]] bool getToErase() const;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::shared_ptr<Cord> getCord() const;

    void setCord(std::shared_ptr<Cord> newCord);

    static std::condition_variable &getCv();

    void realseCords();
};


#endif //SO_2_PEOPLE_H
