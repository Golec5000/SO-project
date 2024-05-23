#include "People.h"

People::People(int x, int y, std::vector<std::vector<Cord>> &map) : cord(new Cord(x, y)), running(true), toErase(false),
                                                                    direction('>'), hasCrossedSwitch(false), map(map) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(150, 1650);
    speed = dis(gen);

    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ234567890!@$%&*()_+-=[]{}|;':,<?";
    for (int i = 0; i < 2; i++)
        name += chars[dis(gen) % chars.size()];

}

void People::start() {
    thread = std::thread([this]() {
        while (running) {
            moveClient();
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }
    });
}

void People::moveClient() {
    int nextX = cord->x;
    int nextY = cord->y;

    // Modyfikacja x i y na podstawie kierunku
    if (direction == '^' && cord->x > 0) {
        --nextX;
    } else if (direction == 'v' && cord->x < 30) {
        ++nextX;
    } else {
        ++nextY;
        direction = '>';
    }

    Cord *tmpCord = nullptr;
    // Znalezienie aktualnego pola
    for (auto &c1: map) {
        for (auto &c2: c1) {
            if (c2.x == this->cord->x && c2.y == this->cord->y) {
                tmpCord = &c2;
                break;
            }
        }
    }

    // Sprawdzenie, czy nastepne pole jest wolne
    Cord *nextCord = nullptr;
    for (auto &c1: map) {
        for (auto &c2: c1) {
            if (c2.x == nextX && c2.y == nextY) {
                nextCord = &c2;
                break;
            }
        }
    }

    if (nextCord && nextCord->move(*this, nextX, nextY) && tmpCord) {
        tmpCord->free();
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }

    if (cord->y == 39) {
        if (tmpCord) {
            tmpCord->free();
        }
        running = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        toErase = true;
        // Znajdź obiekt Cord w mapie i zwolnij go
        for (auto &c1: map) {
            for (auto &c2: c1) {
                if (c2.x == cord->x && c2.y == cord->y) {
                    c2.free();
                    break;
                }
            }
        }
    }
}

void People::joinThread() {
    running = false;
    thread.join();
}

bool People::getToErase() const {
    return toErase;
}

std::string People::getName() const {
    return name;
}

char People::getDirection() const {
    return direction;
}

void People::setDirection(char newDirection) {
    direction = newDirection;
}

const Cord *People::getCord() const {
    return cord;
}

void People::setCord(Cord *newCord) {
    delete cord; // Zwolnienie starego obiektu Cord
    cord = newCord; // Przypisanie nowego obiektu Cord
}

const std::atomic_bool &People::getHasCrossedSwitch() const {
    return hasCrossedSwitch;
}

void People::setHasCrossedSwitch(const std::atomic_bool &hasCrossedSwitch) {
    People::hasCrossedSwitch = hasCrossedSwitch.load();
}

People::~People() {
    delete cord;
}

