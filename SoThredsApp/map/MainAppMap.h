#ifndef MAINAPPMAP_H
#define MAINAPPMAP_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "../threads/entity/Person.h"

class MainAppMap {
public:
    MainAppMap();

    ~MainAppMap();

    std::string **getMap() const;

    void displayMap() const;

    void setSwitchChar(char arg);

    void loadMap();

    void setPeople(std::vector<Person*> * people);

    int getMid() const {
        return mid;
    }

    int getSelectorPoint() const {
        return selectorPoint;
    }
    char getSwitchChar() const {
        return switchChar;
    }

private:
    std::string **map = nullptr;
    std::vector<Person*> * people = nullptr;
    int width = 40;
    int height = 31;
    int mid = 15;
    int selectorPoint = 29;
    char pathChar = '1';
    char switchChar = '^';

    void downArm() const;

    void upArm() const;

    void deleteMap();
};


#endif //MAINAPPMAP_H
