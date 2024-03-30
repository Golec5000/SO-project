#include "MapRender.h"

MapRender::MapRender() = default;

MapRender::~MapRender() {
    if (running) {
        stop();
    }
    std::cout << "MapRender destroyed" << std::endl;
}

void MapRender::start() {
    running = true;
    pthread_create(&thread, NULL, &MapRender::pthreadStart, this);
    if (switchThread != nullptr) {
        switchThread->run();
    }
    if (entityGenerator != nullptr) {
        map->setPeople(entityGenerator->getPeople());
        entityGenerator->run();
    }
}

void MapRender::stop() {
    if (running) {
        running = false;

        mtx.lock();
        pthread_join(thread, NULL);
        mtx.unlock();
    }
}

void MapRender::render() {
    while (running) {
        if (switchThread != nullptr) {
            const char direction = switchThread->getSwitchState();
            mtx.lock();
            map->setSwitchChar(direction);
            mtx.unlock();
        }
        if (entityGenerator != nullptr) {
           mtx.lock();
           for (auto &person: *entityGenerator->getPeople()) {
               if(person->getY() == map->getSelectorPoint() && person->getX() == map->getMid()) {
                   person->setDirection(map->getSwitchChar());
               }
           }
           mtx.unlock();
        }
        map->loadMap();
        map->displayMap();
        system("clear");
    }
}

void MapRender::setMap(MainAppMap *map) {
    this->map = map;
}

void MapRender::setSwitchThread(SwitchThread *switchThread) {
    this->switchThread = switchThread;
}

bool MapRender::isRunning() const {
    return running;
}

void *MapRender::pthreadStart(void *arg) {
    auto *instance = static_cast<MapRender *>(arg);
    instance->render();
    pthread_exit(nullptr);
    return nullptr;
}

void MapRender::setEntityGenerator(EntityGenerator *entityGenerator) {
    this->entityGenerator = entityGenerator;

}
