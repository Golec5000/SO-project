#include "Cord.h"

bool Cord::move(People &people, int nextX, int nextY) {
    std::lock_guard<std::mutex> lock(mutex);
    if (nextX < 0 || nextX >= 31 || nextY < 0 || nextY >= 40) {
        return false;
    }
    if (ocupied.load() && y != 38) { // Jeśli pole jest zajęte i nie jest polem przed stacją
        return false;
    } else {
        ocupied.store(true); // Ustaw ocupied na true, chyba że pole jest polem przed stacją
        people.setCord(std::make_shared<Cord>(x, y));
        return true;
    }
}

void Cord::free() {
    std::lock_guard<std::mutex> lock(mutex);
    this->ocupied = false;
}
