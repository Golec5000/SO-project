#include <unistd.h>
#include <ncurses.h>
#include <iostream>

#include "../map/MainAppMap.h"
#include "../threads/mapRender/MapRender.h"


int main() {

    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    auto *map = new MainAppMap();
    auto *mapRender = new MapRender();
    auto *switchThread = new SwitchThread();
    auto *entityGenerator = new EntityGenerator();

    mapRender->setMap(map);
    mapRender->setSwitchThread(switchThread);
    mapRender->setEntityGenerator(entityGenerator);
    entityGenerator->setMap(map);
    mapRender->start();

    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    // Czekaj na zakończenie renderowania
    while (mapRender->isRunning()) {
        int ch = getch();
        if (ch == ' ') // Jeśli naciśnięto spację, zakończ pętlę
        {
            mapRender->stop();
            switchThread->stop();
            entityGenerator->stop();
            break;
        }
        usleep(100000); // Zasypia na 1 sekundę
    }

    delete map;
    delete mapRender;
    delete switchThread;
    delete entityGenerator;

    endwin();

    return 0;
}
