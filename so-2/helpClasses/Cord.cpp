#include "Cord.h"

bool Cord::move(People &people, int nextX, int nextY) {
    std::lock_guard<std::mutex> lock(mutex);
    if (nextX < 0 || nextX >= 31 || nextY < 0 || nextY >= 40) {
        return false;
    }
    if (this->ocupied.load()) {
        return false;
    }
    this->ocupied = true;
    people.setCord(new Cord(nextX, nextY));
    return true;
}

void Cord::free() {
    std::lock_guard<std::mutex> lock(mutex);
    this->ocupied = false;
}
