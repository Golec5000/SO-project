#include "People.h"

People::People(int x, int y, std::vector<std::vector<Cord>> &map) : cord(std::make_shared<Cord>(x, y)), running(true),
                                                                    toErase(false),
                                                                    direction('>'), hasCrossedSwitch(false), map(map) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(150, 1000);
    speed = dis(gen);

    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ234567890!@$%&*()_+-=[]{}|;':,<?";
    for (int i = 0; i < 2; i++)
        name += chars[dis(gen) % chars.size()];

}

void People::start(std::atomic_bool &isSwitchBlocked) {
    thread = std::thread([this, &isSwitchBlocked]() {
        while (running) {
            moveClient(isSwitchBlocked);
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }
    });
}

void People::moveClient(std::atomic_bool &isSwitchBlocked) {

    if (!running) return;

    // Sprawdzenie, czy switch jest zablokowany
    if (cord->y == 28 && !hasCrossedSwitch) {
        while (isSwitchBlocked && running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }
        if (!running) return;
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

    Cord *tmpCord = findCord(cord->x, cord->y);
    Cord *nextCord = findCord(nextX, nextY);

    if (nextCord && nextCord->move(*this, nextX, nextY) && tmpCord) {
        tmpCord->free();
    } else {
        if (!running) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }

    if (cord->y == 39) {
        running = false;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        toErase = true;
        findCord(cord->x, cord->y)->free();
    }
}

Cord *People::findCord(int x, int y) {
    for (auto &c1: map) {
        for (auto &c2: c1) {
            if (c2.x == x && c2.y == y) {
                return &c2;
            }
        }
    }
    return nullptr;
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

void People::setRunning(const std::atomic_bool &running) {
    People::running = running.load();
}

