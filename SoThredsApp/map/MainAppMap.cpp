#include "MainAppMap.h"

MainAppMap::MainAppMap() {
    map = new std::string *[height];
    for (int i = 0; i < height; i++) {
        map[i] = new std::string[width];
        for (int j = 0; j < width; j++) {
            map[i][j] = "kl";
        }
    }

    loadMap();
}

void MainAppMap::loadMap() {
    if (map != nullptr) {
        //srodkowy rzad
        for (int j = 0; j < width; j++)
            map[mid][j] = pathChar;

        //przelacznik kierunku
        map[mid][selectorPoint] = switchChar;

        //dolna galoz
        downArm();
        //gorna galoz
        upArm();

        if (people != nullptr && !people->empty()) {
            for (auto &person: *people) {
                if (person->isRunning()) {
                    map[person->getX()][person->getY()] = person->getName();
                } else {
                    map[person->getX()][person->getY()] = "1";
                }
            }
        }
    }
}

void MainAppMap::downArm() const {
    for (int i = mid + 1; i < height; i++)
        map[i][selectorPoint] = pathChar;
    for (int i = selectorPoint + 1; i < width; i++)
        map[height - 1][i] = pathChar;
}

void MainAppMap::upArm() const {
    for (int i = mid - 1; i >= 0; i--)
        map[i][selectorPoint] = pathChar;
    for (int i = selectorPoint + 1; i < width; i++)
        map[0][i] = pathChar;
}

void MainAppMap::deleteMap() {
    if (map != nullptr) {
        for (int i = 0; i < height; i++)
            delete[] map[i];
        delete[] map;
        map = nullptr;
    }
}


void MainAppMap::displayMap() const {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            std::cout << std::setw(4) << map[i][j];
        std::cout << std::endl;
    }
}

void MainAppMap::setSwitchChar(char arg) {
    this->switchChar = arg;
}

MainAppMap::~MainAppMap() {
    deleteMap();
    std::cout << "Map deleted" << std::endl;
}

std::string **MainAppMap::getMap() const {
    return map;
}

void MainAppMap::setPeople(std::vector<Person *> *people) {
    this->people = people;

}
