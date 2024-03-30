#ifndef MAPRENDER_H
#define MAPRENDER_H

#include <pthread.h>
#include <unistd.h>
#include <mutex>

#include "../../map/MaInAppMap.h"
#include "../switch/SwitchThread.h"
#include "../entityGenerator/EntityGenerator.h"

class MapRender {
public:
    void start();

    void stop();

    void render();

    void setMap(MaInAppMap *map);

    void setSwitchThread(SwitchThread *switchThread);

    void setEntityGenerator(EntityGenerator *entityGenerator);

    MapRender();

    ~MapRender();

    bool isRunning() const;

private:
    MaInAppMap *map = nullptr;
    SwitchThread *switchThread = nullptr;
    EntityGenerator *entityGenerator = nullptr;
    pthread_t thread = 0;
    bool running = false;

    static void *pthreadStart(void *arg);

    std::mutex mtx;
};

#endif //MAPRENDER_H
