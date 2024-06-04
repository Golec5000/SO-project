#include "People.h"

std::condition_variable People::cv;

People::People(int x, int y, std::vector<std::vector<Cord>> &map, std::atomic_int &switchCounter, int &switchBorder)
        : map(map), switchCounter(switchCounter), switchBorder(switchBorder) {

    this->running = true;
    this->toErase = false;
    this->hasCrossedSwitch = false;
    this->closedThreadBySpace = false;
    this->direction = '>';
    this->cord = std::make_shared<Cord>(x, y);


    speed = getRandInt(100, 1000);

    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%&*()+-=[]{}|;':,<?";
    name += chars[getRandInt(100, 1000) % chars.size()];
    name += chars[getRandInt(100, 1000) % chars.size()];
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

    checkCordLimits();

    int nextX = cord->x + (direction == '^' && cord->x > 0 ? -1 : 0) + (direction == 'v' && cord->x < 30 ? 1 : 0);
    int nextY = cord->y + (direction == '>' ? 1 : 0);

    Cord *tmpCord = findCord(cord->x, cord->y);
    Cord *nextCord = findCord(nextX, nextY);

    if (nextCord && tmpCord) {
        std::unique_lock<std::mutex> lock(nextCord->mtx);
        cv.wait(lock, [&] {
            return !isSwitchBlocked || tmpCord->y != 28 || !running;
        });

        if (!running) return;

        if (nextCord->canMove(*this, nextX, nextY)) {
            tmpCord->freeOccupiedCord();
            setClientDirection(isSwitchBlocked);
        } else {
            nextCord->cv.wait(lock, [&] {
                return !nextCord->occupied || !running;
            });
        }
    }

    checkEndPosition();
}

void People::setClientDirection(std::atomic_bool &isSwitchBlocked) {
    if (hasCrossedSwitch) return;

    Cord *tmpCord = findCord(cord->x, cord->y);

    if (tmpCord->y == 29 && tmpCord->x == 15 && !hasCrossedSwitch) {
        direction = tmpCord->getDirection();

        switchCounter++;
        hasCrossedSwitch = true;

        if (switchCounter >= switchBorder) {
            isSwitchBlocked = true;
            cv.notify_all();
        }

    }
}

void People::checkCordLimits() {
    if (cord->x == 0 || cord->x == 30) direction = '>';
}

void People::checkEndPosition() {
    if (cord->y == 39 && running) {
        running = false;

        std::unique_lock<std::mutex> lock(sleepMutex);
        sleepCv.wait_for(lock, std::chrono::seconds(getRandInt(3, 10)), [&] {
            return closedThreadBySpace.load();
        });

        toErase = true;
        findCord(cord->x, cord->y)->freeOccupiedCord();
        cv.notify_all();
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

void People::joinThread(std::atomic_bool &isSwitchBlocked) {
    running = false;
    realseCords();

    --switchCounter;

    if (switchCounter < switchBorder) {
        isSwitchBlocked = false;
    }
    cv.notify_all();
    if (thread.joinable())
        thread.join();
}

void People::realseCords() {
    for (auto &row: map) {
        for (auto &c: row) {
            if (c.cordChar != "  ") {
                c.cv.notify_all();
            }
        }
    }
}

bool People::getToErase() const {
    return toErase;
}

std::string People::getName() const {
    return name;
}

std::shared_ptr<Cord> People::getCord() const {
    return cord;
}

void People::setCord(std::shared_ptr<Cord> newCord) {
    cord = std::move(newCord); // Automatyczne zwalnianie starego obiektu Cord
}

std::condition_variable &People::getCv() {
    return cv;
}

int People::getRandInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void People::setClosedThreadBySpace(const std::atomic_bool &closedThreadBySpace) {
    People::closedThreadBySpace = closedThreadBySpace.load();
    sleepCv.notify_all();
}

