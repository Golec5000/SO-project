#ifndef SO_2_CORD_H
#define SO_2_CORD_H

#include <string>
#include <atomic>
#include <mutex>
#include <utility>
#include <iostream>
#include <condition_variable>
#include "People.h"

class People;

class Cord {
public:
    int x, y;
    std::atomic_bool occupied;
    std::string cordChar;
    std::mutex mtx;
    std::condition_variable cv;

    explicit Cord(int x = 0, int y = 0, std::string cordChar = "  ")
            : x(x), y(y), occupied(false), cordChar(std::move(cordChar)) {}

    Cord(const Cord &other)
            : x(other.x), y(other.y), occupied(other.occupied.load()), cordChar(other.cordChar) {}

    Cord &operator=(const Cord &other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            occupied.store(other.occupied.load());
            cordChar = other.cordChar;
        }
        return *this;
    }

    bool canMove(People &people, int nextX, int nextY);

    void freeOccupiedCord();

private:

    static bool isWithinBounds(int nextX, int nextY);

};

#endif //SO_2_CORD_H