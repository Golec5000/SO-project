#include "People.h"

People::People(int x, int y) : running(true), toErase(false), direction('>') {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(150, 1650);
    speed = dis(gen);

    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ234567890!@$%&*()_+-=[]{}|;':,<?";
    for (int i = 0; i < 2; i++)
        name += chars[dis(gen) % chars.size()];

    xPos = x;
    yPos = y;

    thread = std::thread([this](){
        while (running){
            moveClient();
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }
    });
}

void People::moveClient() {
    if (direction == '^' && xPos > 0) {
        --xPos;
    } else if (direction == 'v' && xPos < 30) {
        ++xPos;
    } else {
        ++yPos;
        direction = '>';
    }

    if (yPos == 39) {
        running = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        toErase = true;
    }
}

void People::joinThread() {
    running = false;
    thread.join();
}

int People::getXPos() const {
    return xPos;
}

int People::getYPos() const {
    return yPos;
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

void People::setX(int x) {
    xPos = x;
}

void People::setY(int y) {
    yPos = y;
}