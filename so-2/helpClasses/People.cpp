#include "People.h"


People::People(SharedData &sharedData) : sharedData(sharedData) {

    this->running = true;
    this->toErase = false;
    this->hasCrossedSwitch = false;
    this->closedThreadBySpaceVar = false;
    this->direction = '>';
    this->cord = std::make_shared<Cord>(sharedData.mid, 0);


    speed = getRandInt(100, 1000);

    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%&*()+-=[]{}|;':,<?";
    name += chars[getRandInt(100, 1000) % chars.size()];
    name += chars[getRandInt(100, 1000) % chars.size()];
}

void People::start() {
    thread = std::thread([&] {
        while (running) {
            moveClient();
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }
    });
}

void People::moveClient() {
    if (!running) return;

    checkCordLimits();

    int nextX = cord->x + (direction == '^' && cord->x > 0 ? -1 : 0) + (direction == 'v' && cord->x < 30 ? 1 : 0);
    int nextY = cord->y + (direction == '>' ? 1 : 0);

    Cord *tmpCord = findCord(cord->x, cord->y);
    Cord *nextCord = findCord(nextX, nextY);

    if (nextCord && tmpCord) {
        std::unique_lock<std::mutex> lock(nextCord->mtx);
        sharedData.switchCV.wait(lock, [&] {
            return !sharedData.isSwitchBlocked || tmpCord->y != 28 || !running;
        });

        if (!running) return;

        if (nextCord->canMove(*this, nextX, nextY)) {
            tmpCord->freeOccupiedCord();
            setClientDirection();
        } else {
            nextCord->cv.wait(lock, [&] {
                return !nextCord->occupied || !running;
            });
        }
    }

    checkEndPosition();
}

void People::setClientDirection() {
    if (hasCrossedSwitch) return;

    //pozycja switcha
    if (cord->y == sharedData.selectorPoint
        && cord->x == sharedData.mid
        && !hasCrossedSwitch) {

        direction = sharedData.switchChar;  //zmiana kierunku

        sharedData.switchCounter++;         //zwiększenie licznika przejść
        hasCrossedSwitch = true;            //ustawnienie flagi przejścia

        if (sharedData.switchCounter >= sharedData.switchBorder) {
            sharedData.isSwitchBlocked = true;  //blokada przełącznika i poinformowanie innych wątków o zmianie stanu
            sharedData.switchCV.notify_all();
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
            return closedThreadBySpaceVar;
        });

        toErase = true;
        findCord(cord->x, cord->y)->freeOccupiedCord();
    }
}

Cord *People::findCord(int x, int y) {
    for (auto &row: sharedData.map) {
        auto it = std::find_if(row.begin(), row.end(),
                               [&](const Cord &cordToFind) { return cordToFind.x == x && cordToFind.y == y; });
        if (it != row.end()) return &(*it);
    }
    return nullptr;
}

void People::joinThread() {
    running = false; // zatrzymanie wątku
    realseCords();

    --sharedData.switchCounter; // zmniejszenie licznika przejść

    if (sharedData.switchCounter < sharedData.switchBorder) {
        sharedData.isSwitchBlocked = false; // odblokowanie przełącznika
    }

    sharedData.switchCV.notify_all(); // poinformowanie innych wątków o zmianie stanu

    if (thread.joinable()) // czekanie na zakończenie wątku
        thread.join(); // zakończenie wątku
}

void People::realseCords() {
    for (auto &row: sharedData.map) {
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

int People::getRandInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void People::closedThreadBySpace() {
    People::closedThreadBySpaceVar = true;
    sleepCv.notify_one();
}

