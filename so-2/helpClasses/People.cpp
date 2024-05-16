#include "People.h"

People::People(int x, int y) : cord(x, y), running(true), toErase(false), direction('>'), hasCrossedSwitch(false) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(150, 1650);
    speed = dis(gen);

    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ234567890!@$%&*()_+-=[]{}|;':,<?";
    for (int i = 0; i < 2; i++)
        name += chars[dis(gen) % chars.size()];

    thread = std::thread([this]() {
        while (running) {
            moveClient();
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }
    });
}

void People::moveClient() {
    if (direction == '^' && cord.x > 0) {
        --cord.x;
    } else if (direction == 'v' && cord.x < 30) {
        ++cord.x;
    } else {
        ++cord.y;
        direction = '>';
    }

    if (cord.y == 39) {
        running = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        toErase = true;
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

const Cord &People::getCord() const {
    return cord;
}

void People::setCord(const Cord &cord) {
    People::cord = cord;
}

const std::atomic_bool &People::getHasCrossedSwitch() const {
    return hasCrossedSwitch;
}

void People::setHasCrossedSwitch(const std::atomic_bool &hasCrossedSwitch) {
    People::hasCrossedSwitch = hasCrossedSwitch.load();
}
