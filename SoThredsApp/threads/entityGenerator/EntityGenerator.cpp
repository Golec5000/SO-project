#include "EntityGenerator.h"

EntityGenerator::EntityGenerator() : people(new std::vector<Person *>), finishedPeople(new std::vector<Person *>), thread(0), running(false) {
}

EntityGenerator::~EntityGenerator() {
    if (people != nullptr) {
        for (auto &person: *people){
            person->stop();
            delete person;
            person = nullptr;
        }

        delete people;
        people = nullptr;
    }

    stop();
}

void EntityGenerator::run() {
    running = true;
    pthread_create(&thread, NULL, &EntityGenerator::pthreadStart, this);
}

void EntityGenerator::stop() {
    if (running) {
        running = false;
        mtx.lock();
        pthread_join(thread, NULL);
        mtx.unlock();
    }
}

pthread_t EntityGenerator::getThread() const {
    return thread;
}

void *EntityGenerator::pthreadStart(void *arg) {
    auto *instance = static_cast<EntityGenerator *>(arg);
    while (instance->running) {
        instance->generate();
        usleep(10000000);
    }
    pthread_exit(nullptr);
    return nullptr;
}

void EntityGenerator::removeFinishedPeople() {
    mtx.lock();
    for (auto &person: *finishedPeople){
        auto it = std::find(people->begin(), people->end(), person);
        if (it != people->end()) {
            people->erase(it);
        }
        delete person;
    }
    finishedPeople->clear();
    mtx.unlock();
}

void EntityGenerator::generate() {
    mtx.lock();
    auto *person = new Person();
    person->setX(map->getMid());
    person->setY(0);
    people->push_back(person);
    people->back()->run();
    mtx.unlock();

    // Dodaj Person do listy zakończonych, gdy zakończy działanie
    if (!person->isRunning()) {
        finishedPeople->push_back(person);
    }

    // Usuń zakończone osoby
    removeFinishedPeople();
}
