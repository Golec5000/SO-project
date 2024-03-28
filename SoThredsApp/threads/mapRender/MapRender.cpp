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
    if (switchThread != nullptr)
    {
        switchThread->run();
    }
}

void MapRender::stop()
{
    if (running)
    {
        running = false;

        mtx.lock();
        pthread_join(thread, NULL);
        mtx.unlock();

    }
}
void MapRender::render()
{
    while (running)
    {
        if (switchThread != nullptr) {
            const char direction = switchThread->getSwitchState();
            mtx.lock();
            map->setSwitchChar(direction);
            mtx.unlock();
        }
        map->loadMap();
        map->diisplayMap();
        system("clear");
    }
}

void MapRender::setMap(MaInAppMap* map)
{
    this->map = map;
}

void MapRender::setSwitchThread(SwitchThread* switchThread)
{
    this->switchThread = switchThread;
}

bool MapRender::isRunning() const
{
    return running;
}

void* MapRender::pthreadStart(void* arg)
{
    auto* instance = static_cast<MapRender*>(arg);
    instance->render();
    pthread_exit(nullptr);
    return nullptr;
}
