#include <iostream>
#include "../map/MaInAppMap.h"
#include "../threads/mapRender/MapRender.h"

int main()
{
    MaInAppMap * map = new MaInAppMap();
    MapRender * mapRender = new MapRender();

    mapRender->setMap(map);
    mapRender->start();

    // Czekaj na zakończenie renderowania
    while(mapRender->isRunning()) {
        usleep(5000000); // Zasypia na 1 sekundę
    }

    delete map;
    delete mapRender;

    return 0;
}
