#include "MapRender.h"

MapRender::MapRender() = default;

MapRender::~MapRender()
{
    if (running)
    {
        stop();
    }
}

void MapRender::start()
{
    running = true;
    pthread_create(&thread, NULL, &MapRender::pthreadStart, this);
}

void MapRender::stop()
{
    running = false;
    pthread_join(thread, NULL);
}

void MapRender::render()
{
    while (running)
    {
        map->diisplayMap();
        system("clear");
        usleep(50); // Zasypia na 0.5 sekundy
    }
}

void MapRender::setMap(MaInAppMap* map)
{
    this->map = map;
}

bool MapRender::isRunning() const
{
    return running;
}

void* MapRender::pthreadStart(void* arg)
{
    auto* instance = static_cast<MapRender*>(arg);
    instance->render();
    return nullptr;
}
