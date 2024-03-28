#ifndef MAPRENDER_H
#define MAPRENDER_H
#include <pthread.h>
#include <unistd.h>

#include "../../map/MaInAppMap.h"


class MapRender
{
public:
    void start();
    void stop();
    void render();
    void setMap(MaInAppMap* map);
    MapRender();
    ~MapRender();
    bool isRunning() const;

private:
    MaInAppMap* map = nullptr;
    pthread_t thread = 0;
    bool running = false;
    static void* pthreadStart(void* arg);
};


#endif //MAPRENDER_H
