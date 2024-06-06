#ifndef SO_2_SHAREDDATA_H
#define SO_2_SHAREDDATA_H

#include <condition_variable>
#include <atomic>
#include <vector>
#include "Cord.h"

class Cord;

struct SharedData {

    std::condition_variable switchCV;

    std::atomic_int switchCounter = 0;
    std::atomic_bool isSwitchBlocked = false;
    std::atomic_char switchChar = '^';

    int switchBorder = 10; // wartość domyślna

    const int width = 40;
    const int height = 31;
    const int mid = 15;
    const int selectorPoint = 29;

    const char pathChar = '_';
    const char stationChar = '#';

    std::vector<std::vector<Cord>> map;

    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%&*()+-=[]{}|;':,<?";

};

#endif //SO_2_SHAREDDATA_H
