#include "People.h"


People::People(SharedData &sharedData) : sharedData(sharedData) {

    this->running = true;
    this->toErase = false;
    this->hasCrossedSwitch = false;
    this->closedThreadBySpaceVar = false;
    this->direction = '>';
    this->cord = std::make_shared<Cord>(sharedData.mid, 0);

    speed = getRandInt(100, 1000);

    name += sharedData.chars[getRandInt(100, 1000) % sharedData.chars.size()];
    name += sharedData.chars[getRandInt(100, 1000) % sharedData.chars.size()];
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

    if (cord->x == 0 || cord->x == 30) direction = '>';

    int nextX = cord->x + (direction == '^' && cord->x > 0 ? -1 : 0) + (direction == 'v' && cord->x < 30 ? 1 : 0);
    int nextY = cord->y + (direction == '>' ? 1 : 0);

    Cord &tmpCord = sharedData.map[cord->x][cord->y];
    Cord &nextCord = sharedData.map[nextX][nextY];
    {
        std::unique_lock<std::mutex> lock(nextCord.mtx);
        sharedData.switchCV.wait(lock, [&] {
            return !sharedData.isSwitchBlocked || tmpCord.y != 28 || !running;
        });

        if (nextCord.canMove(*this, nextX, nextY)) {
            tmpCord.freeOccupiedCord();
            setClientDirection();
        } else {
            nextCord.cv.wait(lock, [&] {
                return !nextCord.occupied || !running;
            });
        }
    }

    checkEndPosition();
}

void People::setClientDirection() {
    if (hasCrossedSwitch) return; //sprawdzenie czy nie przekroczył przełącznika i jeśli tak to nie zmienia kierunku

    //pozycja switcha
    if (cord->y == sharedData.selectorPoint && cord->x == sharedData.mid) {

        direction = sharedData.switchChar;  //zmiana kierunku

        sharedData.switchCounter++;         //zwiększenie licznika przejść
        hasCrossedSwitch = true;            //ustawnienie flagi przejścia

        if (sharedData.switchCounter >= sharedData.switchBorder) {
            sharedData.isSwitchBlocked = true;  //blokada przełącznika i poinformowanie innych wątków o zmianie stanu
            sharedData.switchCV.notify_all();
        }

    }
}

void People::checkEndPosition() {
    if (cord->y == 39 && running) {
        running = false;

        std::unique_lock<std::mutex> lock(sleepMutex);
        sleepCv.wait_for(lock, std::chrono::seconds(getRandInt(5, 12)), [&] {
            return closedThreadBySpaceVar;
        });

        toErase = true;
        sharedData.map[cord->x][cord->y].freeOccupiedCord();
    }
}

void People::joinThread() {
    running = false; // zatrzymanie wątku

    --sharedData.switchCounter; // zmniejszenie licznika przejść

    if (sharedData.switchCounter < sharedData.switchBorder) {
        sharedData.isSwitchBlocked = false; // odblokowanie przełącznika
    }

    sharedData.switchCV.notify_all(); // poinformowanie innych wątków o zmianie stanu

    sharedData.map[cord->x][cord->y].freeOccupiedCord(); // zwolnienie zasobów Cord w mapie (wątek zakończył działanie wiec dane pole jest wolne)

    if (thread.joinable()) // czekanie na zakończenie wątku
        thread.join(); // zakończenie wątku
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
    sleepCv.notify_all();
}

