#include "Cord.h"

bool Cord::move(People &people, int nextX, int nextY) {
    std::lock_guard<std::mutex> lock(mutex);
    if (nextX < 0 || nextX >= 31 ||
        nextY < 0 || nextY >= 40 ||
        (ocupied && y != 38)/*dodanie warunku, żeby moznabylo stakowac na polu przed stacja*/) {
        return false;
    }
    ocupied = true;
    people.setCord(std::make_shared<Cord>(x, y));
    return true;
}

void Cord::free() {
    std::lock_guard<std::mutex> lock(mutex);
    ocupied = false;
}