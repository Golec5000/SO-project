#include "People.h"

People::People(int x, int y, std::vector<std::vector<Cord>> &map) : cord(std::make_shared<Cord>(x, y)), running(true),
                                                                    toErase(false),
                                                                    direction('>'), hasCrossedSwitch(false), map(map) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(150, 500);
    speed = dis(gen);

    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ234567890!@$%&*()_+-=[]{}|;':,<?";
    for (int i = 0; i < 2; i++)
        name += chars[dis(gen) % chars.size()];

}

void People::start(std::atomic_bool &isSwitchBlocked, std::atomic_int &switchCounter, int switchBorder) {
    thread = std::thread([this, &isSwitchBlocked, &switchCounter, switchBorder]() {
        while (running) {
            moveClient(isSwitchBlocked, switchCounter, switchBorder);
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }
    });
}

void People::moveClient(std::atomic_bool &isSwitchBlocked, std::atomic_int &switchCounter, int switchBorder) {

    if (cord->y == 28 && !hasCrossedSwitch) {
        // Jeśli przełącznik jest zablokowany, czekaj
        while (isSwitchBlocked) {
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }
        // Jeśli liczba osób, które przekroczyły przełącznik, przekroczyła określony próg, zablokuj przełącznik
        if (switchCounter >= switchBorder) {
            isSwitchBlocked = true;
        }
    }

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
    std::cout << "Joining thread: " << name << std::endl;
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

std::shared_ptr<Cord> People::getCord() const {
    return cord;
}

void People::setCord(std::shared_ptr<Cord> newCord) {
    cord = std::move(newCord); // Automatyczne zwalnianie starego obiektu Cord
}

void People::setHasCrossedSwitch(const std::atomic_bool &hasCrossedSwitch) {
    People::hasCrossedSwitch = hasCrossedSwitch.load();
}

const std::atomic_bool &People::getHasCrossedSwitch() const {
    return hasCrossedSwitch;
}

bool People::isThreadJoinable() {
    return thread.joinable();
}

