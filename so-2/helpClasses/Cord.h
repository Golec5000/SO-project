#ifndef SO_2_CORD_H
#define SO_2_CORD_H

#include <string>
#include <atomic>
#include <utility>
#include <mutex>
#include "People.h"

class People;

class Cord {
public:
    int x;
    int y;
    std::atomic_bool ocupied;
    std::string cordChar;
    std::mutex mutex;

    Cord() : x(0), y(0), ocupied(false), cordChar("..") {}

    Cord(int x, int y, std::string cordChar = "..")
            : x(x), y(y), ocupied(false), cordChar(std::move(cordChar)) {}

    // Konstruktor kopiujący
    Cord(const Cord &other)
            : x(other.x), y(other.y), ocupied(other.ocupied.load()), cordChar(other.cordChar) {}

    // Operator przypisania kopiującego
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
