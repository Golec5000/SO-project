#include "People.h"

People::People(int x, int y) : running(true), toErase(false), direction('>'){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(300, 1500);
    this->speed = dis(gen);

    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ234567890!@$%&*()_+-=[]{}|;':,<?";

    for (int i = 0; i < 2; i++)
        name += chars[dis(gen) % chars.size()];

    this->xPos = x;
    this->yPos = y;

    this->thread = std::thread([this](){
        while (this->running){
            this->moveClient();
            std::this_thread::sleep_for(std::chrono::milliseconds(this->speed));
        }
    });
}

void People::moveClient() {
    switch (this->direction) {
        case '^':
            if (getXPos() > 0) {
                setX(getXPos() - 1);
            } else {
                setY(getYPos() + 1);
                setDirection('>');
            }
            break;
        case '>':
            if (getYPos() < 40)
                setY(getYPos() + 1);
            break;
        case 'v':
            if (getXPos() < 30) {
                setX(getXPos() + 1);
            } else {
                setY(getYPos() + 1);
                setDirection('>');
            }
            break;
    }
    if (this->yPos == 39) {
        this->running = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        this->toErase = true;
    }
}

void People::joinThread() {
    this->running = false;
    this->thread.join();
}

int People::getXPos() const {
    return this->xPos;
}

int People::getYPos() const {
    return this->yPos;
}

bool People::getToErase() const {
    return this->toErase;
}

std::string People::getName() const {
    return this->name;
}

char People::getDirection() const {
    return this->direction;
}

void People::setDirection(char direction) {
    this->direction = direction;
}

void People::setX(int x) {
    this->xPos = x;
}

void People::setY(int y) {
    this->yPos = y;
}
