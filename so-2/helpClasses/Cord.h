#ifndef SO_2_CORD_H
#define SO_2_CORD_H

#include <string>
#include <atomic>
#include <mutex>
#include <utility>
#include "People.h"

class People;

class Cord {
public:
    int x, y;
    std::atomic_bool ocupied;
    std::string cordChar;
    std::mutex mutex;

    explicit Cord(int x = 0, int y = 0, std::string cordChar = "  ")
            : x(x), y(y), ocupied(false), cordChar(std::move(cordChar)) {}

    Cord(const Cord &other)
            : x(other.x), y(other.y), ocupied(other.ocupied.load()), cordChar(other.cordChar) {}

    Cord &operator=(const Cord &other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            ocupied.store(other.ocupied.load());
            cordChar = other.cordChar;
        }
        return *this;
    }

    bool move(People &people, int nextX, int nextY);

    void free();
};

#endif //SO_2_CORD_H