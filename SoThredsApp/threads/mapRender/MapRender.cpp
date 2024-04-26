#include "MapRender.h"

MapRender::MapRender() = default;

MapRender::~MapRender() {
    if (running) {
        stop();
    }
    std::cout << "MapRender destroyed" << std::endl;
}

void MapRender::start() {

    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    running = true;
    this->thread = std::thread(&MapRender::render, this);
    if (switchThread != nullptr) {
        switchThread->run();
    }
    if (entityGenerator != nullptr) {
        map->setPeople(entityGenerator->getPeople());
        entityGenerator->run();
    }
}

void MapRender::stop() {
    if(running) {
        running = false;
        if (this->thread.joinable()) {
            this->thread.join();
        }
    }
    endwin();
}

void MapRender::render() {

    WINDOW *buffer = newwin(0, 0, 0, 0);

    while (running) {
        werase(buffer);

        // Update switch state
        if (switchThread != nullptr) {
            map->setSwitchChar(switchThread->getSwitchState());
        }

        if (entityGenerator != nullptr) {
            mtx.lock();
            for (auto &person: *entityGenerator->getPeople()) {
                if (person->getY() == map->getSelectorPoint() && person->getX() == map->getMid()) {
                    person->setDirection(map->getSwitchChar());
                }
            }
            mtx.unlock();
        }

        map->loadMap();
        map->displayMap(buffer);
        wprintw(buffer, "Press 'space' to quit\n");

        // Skopiuj bufor na ekran
        overwrite(buffer, stdscr);
        // Odśwież ekran
        refresh();
        // Wyczyść bufor
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

    delwin(buffer);
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

void MapRender::setEntityGenerator(EntityGenerator *entityGenerator) {
    this->entityGenerator = entityGenerator;

}
