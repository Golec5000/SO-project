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

    std::mutex mapMutex;
    std::condition_variable cv;
    std::atomic_bool running;
    std::atomic_bool toErase;
    std::atomic_bool hasCrossedSwitch;
    int speed;
    std::string name;
    std::thread thread;
    std::shared_ptr<Cord> cord;
    char direction;
    std::vector<std::vector<Cord>> &map;

    void checkCordLimits();

    void checkEndPosition();

public:

    People(int x, int y, std::vector<std::vector<Cord>> &map);

    void start(std::atomic_bool &isSwitchBlocked);

    void moveClient(std::atomic_bool &isSwitchBlocked);

    void joinThread();

    [[nodiscard]] bool getToErase() const;

    [[nodiscard]] std::string getName() const;

    void setDirection(char direction);

    [[nodiscard]] const std::atomic_bool &getHasCrossedSwitch() const;

    void setHasCrossedSwitch(const std::atomic_bool &hasCrossedSwitch);

    [[nodiscard]] std::shared_ptr<Cord> getCord() const;

    void setCord(std::shared_ptr<Cord> newCord);

    void setRunning(const std::atomic_bool &running);

    Cord *findCord(int x, int y);

    std::condition_variable &getCv();

};


#endif //SO_2_PEOPLE_H
