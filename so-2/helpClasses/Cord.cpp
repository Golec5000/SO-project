#include "Cord.h"

bool Cord::canMove(People &people, int nextX, int nextY) {
    if (!isWithinBounds(nextX, nextY) || (occupied && y != 38)) {
        return false;
    }
    occupied = true;
    people.setCord(std::make_shared<Cord>(nextX, nextY));
    return true;
}


bool Cord::isWithinBounds(int nextX, int nextY) {
    return !(nextX < 0 || nextX >= 31 || nextY < 0 || nextY >= 40);
}

void Cord::freeOccupiedCord(std::condition_variable &cvPeople) {
    std::lock_guard<std::mutex> lock(freeMutex);
    occupied = false;
    cvPeople.notify_all();
}
