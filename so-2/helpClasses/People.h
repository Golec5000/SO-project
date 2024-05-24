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
#include "Cord.h"

class Cord;

class People {
private:
    std::atomic_bool running;
    std::atomic_bool toErase;
    std::atomic_bool hasCrossedSwitch;
    int speed;
    std::string name;
    std::thread thread;
    std::shared_ptr<Cord> cord;
    char direction;
    std::vector<std::vector<Cord>> &map;

public:

    People(int x, int y, std::vector<std::vector<Cord>> &map);

    void start(std::atomic_bool &isSwitchBlocked, std::atomic_int &switchCounter, int switchBorder);

    void moveClient(std::atomic_bool &isSwitchBlocked, std::atomic_int &switchCounter, int switchBorder);

    void joinThread();

    [[nodiscard]] bool getToErase() const;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] char getDirection() const;

    void setDirection(char direction);

    [[nodiscard]] const std::atomic_bool &getHasCrossedSwitch() const;

    void setHasCrossedSwitch(const std::atomic_bool &hasCrossedSwitch);

    [[nodiscard]] std::shared_ptr<Cord> getCord() const;

    void setCord(std::shared_ptr<Cord> newCord);

    bool isThreadJoinable();
};


#endif //SO_2_PEOPLE_H
