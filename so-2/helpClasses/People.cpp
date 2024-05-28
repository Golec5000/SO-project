#include "People.h"

People::People(int x, int y, std::vector<std::vector<Cord>> &map) : cord(std::make_shared<Cord>(x, y)), running(true),
                                                                    toErase(false),
                                                                    direction('>'), hasCrossedSwitch(false), map(map) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(150, 1000);
    speed = dis(gen);

    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%&*()+-=[]{}|;':,<?";
    name += chars[dis(gen) % chars.size()];
    name += chars[dis(gen) % chars.size()];

}

void People::start(std::atomic_bool &isSwitchBlocked) {
    thread = std::thread([&] {
        while (running) {
            moveClient(isSwitchBlocked);
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }
    });
}

void People::moveClient(std::atomic_bool &isSwitchBlocked) {
    if (!running) return;

    // Wait if switch is blocked
    while (cord->y == 28 && !hasCrossedSwitch && isSwitchBlocked && running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
    if (!running) return;

    checkCordLimits();

    int nextX = cord->x + (direction == '^' && cord->x > 0) - (direction == 'v' && cord->x < 30);
    int nextY = cord->y + (direction == '>');

    Cord *tmpCord = findCord(cord->x, cord->y);
    Cord *nextCord = findCord(nextX, nextY);

    // Move to next position if possible
    if (nextCord && nextCord->canMove(*this, nextX, nextY) && tmpCord) {
        tmpCord->freeOccupiedCord();
    } else if (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }

    checkEndPosition();
}

void People::checkCordLimits() {
    if (cord->x == 0 || cord->x == 30) direction = '>';
}

void People::checkEndPosition() {
    if (cord->y == 39 && running) {
        running = false;
        std::this_thread::sleep_for(std::chrono::seconds(6));
        toErase = true;
        findCord(cord->x, cord->y)->freeOccupiedCord();
    }
}

Cord *People::findCord(int x, int y) {
    for (auto &row: map) {
        auto it = std::find_if(row.begin(), row.end(),
                               [&](const Cord &cordToFind) { return cordToFind.x == x && cordToFind.y == y; });
        if (it != row.end()) return &(*it);
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

