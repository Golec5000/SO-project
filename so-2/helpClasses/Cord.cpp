#include "Cord.h"

bool Cord::canMove(People &people, int nextX, int nextY) {
    if (occupied && y != 38) {
        return false;
    }
    occupied = true;
    people.setCord(std::make_shared<Cord>(nextX, nextY));
    return true;
}

void Cord::freeOccupiedCord() {
    std::lock_guard<std::mutex> lock(mtx);
    occupied = false;
    cv.notify_all();
}
