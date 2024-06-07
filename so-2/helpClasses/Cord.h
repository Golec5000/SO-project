#ifndef SO_2_CORD_H
#define SO_2_CORD_H

#include <string>
#include <mutex>
#include <utility>
#include <condition_variable>
#include "People.h"

class People;

class Cord {
public:
    int x, y;
    bool occupied;
    std::string cordChar;
    std::mutex mtx;
    std::condition_variable cv;

    explicit Cord(int x = 0, int y = 0, std::string cordChar = "  ")
            : x(x), y(y), occupied(false), cordChar(std::move(cordChar)) {}

    Cord(const Cord &other)
            : x(other.x), y(other.y), occupied(other.occupied), cordChar(other.cordChar) {}

    Cord &operator=(const Cord &other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            occupied = other.occupied;
            cordChar = other.cordChar;
        }
        return *this;
    }

    bool canMove(People &people, int nextX, int nextY);

    void freeOccupiedCord();

};

#endif //SO_2_CORD_H