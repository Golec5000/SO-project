#ifndef MAINAPPMAP_H
#define MAINAPPMAP_H
#include <iostream>
#include <iomanip>

class MaInAppMap
{
public:
    MaInAppMap();
    ~MaInAppMap();

    std::string** getMap();
    void diisplayMap() const;
    void setSwitchChar(char arg);
    void loadMap();

private:

    std::string** map = nullptr;
    int width = 40;
    int height = 31;
    int mid = 15;
    int selectorPoint = 29;
    char pathChar = '1';
    char switchChar = '^';

    void downArm() const;
    void upArm() const;

};


#endif //MAINAPPMAP_H
