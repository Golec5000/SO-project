#ifndef MAPRENDER_H
#define MAPRENDER_H

#include <thread>
#include <unistd.h>
#include <mutex>
#include <ncurses.h>
#include <thread>

#include "../../map/MainAppMap.h"
#include "../switch/SwitchThread.h"
#include "../entityGenerator/EntityGenerator.h"

class MapRender {
public:
    void start();

    void stop();

    void render();

    void setMap(MainAppMap *map);

    void setSwitchThread(SwitchThread *switchThread);

    void setEntityGenerator(EntityGenerator *entityGenerator);

    MapRender();

    ~MapRender();

    bool isRunning() const;

private:
    MainAppMap *map = nullptr;
    SwitchThread *switchThread = nullptr;
    EntityGenerator *entityGenerator = nullptr;
    std::thread thread;
    bool running = false;

    std::mutex mtx;
};

#endif //MAPRENDER_H
