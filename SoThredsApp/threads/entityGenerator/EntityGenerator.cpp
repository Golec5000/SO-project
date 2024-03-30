#include "EntityGenerator.h"

EntityGenerator::EntityGenerator() : people(new std::vector<Person *>), finishedPeople(new std::vector<Person *>),
                                     thread(0), running(false) {
}

EntityGenerator::~EntityGenerator() {
    if (people != nullptr) {
        for (auto &person: *people) {
            person->stop();
            delete person;
            person = nullptr;
        }

        delete people;
        people = nullptr;
        std::cout << "People collection deleted" << std::endl;
    }

    stop();

    std::cout << "EntityGenerator stopped" << std::endl;
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
        instance->removeFinishedPeople();
        usleep(1000000);
    }
    pthread_exit(nullptr);
}

void EntityGenerator::removeFinishedPeople() {

    for (auto &person: *finishedPeople)
        if (person->getY() == 39)
            removePerson(person);

}

void EntityGenerator::generate() {
    mtx.lock();
    auto *person = new Person();
    person->setX(map->getMid());
    person->setY(0);
    people->push_back(person);
    people->back()->run();
    mtx.unlock();
}

void EntityGenerator::removePerson(Person *person) {
    mtx.lock();
    auto it = std::find(people->begin(), people->end(), person);
    if (it != people->end()) {
        people->erase(it);
    }
    std::cout << "Person " << person->getName() << " removed" << std::endl;
    std::cout << "People size: " << people->size() << std::endl;
    delete person;
    person = nullptr;
    mtx.unlock();
}
