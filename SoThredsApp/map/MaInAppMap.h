#ifndef MAINAPPMAP_H
#define MAINAPPMAP_H
#include <iostream>
#include <iomanip>

class MaInAppMap
{
public:
    MaInAppMap();
    ~MaInAppMap();

    int** getMap();
    int getWidth();
    int getHeight();
    void diisplayMap() const;

private:

    std::string** map = nullptr;
    int width = 40;
    int height = 31;
    int mid = 15;
    int selectorPoint = 29;
    char pathChar = '1';

    void loadMap();
    void downArm() const;
    void upArm() const;

};


#endif //MAINAPPMAP_H
