#include "MaInAppMap.h"

MaInAppMap::MaInAppMap()
{
    loadMap();
}

void MaInAppMap::loadMap()
{
    map = new std::string*[height];
    for (int i = 0; i < height; i++)
    {
        map[i] = new std::string[width];
        for (int j = 0; j < width; j++)
        {
            map[i][j] = "kl";
        }
    }

    if (map != nullptr)
    {
        //srodkowy rzad
        for (int j = 0; j < width; j++)
            map[mid][j] = pathChar;

        //przelacznik kierunku
        map[mid][selectorPoint] = switchChar;

        //dolna galoz
        downArm();
        //gorna galoz
        upArm();
    }
}

void MaInAppMap::downArm() const
{
    for (int i = mid + 1; i < height; i++)
        map[i][selectorPoint] = pathChar;
    for (int i = selectorPoint + 1; i < width; i++)
        map[height - 1][i] = pathChar;
}

void MaInAppMap::upArm() const
{
    for (int i = mid - 1; i >= 0; i--)
        map[i][selectorPoint] = pathChar;
    for (int i = selectorPoint + 1; i < width; i++)
        map[0][i] = pathChar;
}


void MaInAppMap::diisplayMap() const
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            std::cout << std::setw(4) << map[i][j];

        std::cout << std::endl;
    }
}

void MaInAppMap::setSwitchChar(char arg)
{
    this->switchChar = arg;
}

MaInAppMap::~MaInAppMap()
{
    for (int i = 0; i < height; i++)
        delete map[i];
    delete[] map;
}

std::string** MaInAppMap::getMap()
{
    return map;
}
