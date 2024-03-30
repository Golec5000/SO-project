#include "EntityGenerator.h"

EntityGenerator::EntityGenerator() : people(new std::vector<Person *>), removeThread(0),
                                     generateThread(0), running(false) {
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
    mtx.lock();
    running = true;
    pthread_create(&generateThread, NULL, &EntityGenerator::generateThreadStart, this);
    pthread_create(&removeThread, NULL, &EntityGenerator::removeThreadStart, this);
    mtx.unlock();
}

void EntityGenerator::stop() {
    mtx.lock();
    if (running) {
        running = false;
        pthread_join(generateThread, NULL);
        pthread_join(removeThread, NULL);
    }
    mtx.unlock();
}


void *EntityGenerator::generateThreadStart(void *arg) {
    auto *instance = static_cast<EntityGenerator *>(arg);
    while (instance->running) {
        instance->generate();
        usleep(2000000); // Zasypia na 2 sekundy
    }
    pthread_exit(nullptr);
}

void *EntityGenerator::removeThreadStart(void *arg) {
    auto *instance = static_cast<EntityGenerator *>(arg);
    while (instance->running) {
        instance->removeFinishedPeople();
        usleep(10000); // Zasypia na 0.01 sekundę
    }
    pthread_exit(nullptr);
}

void EntityGenerator::removeFinishedPeople() {


//    std::cout << "remover" << std::endl;
    mtx.lock();
    for (auto &person: *people)
        if (!person->isRunning())
            removePerson(person);
    mtx.unlock();
}

void EntityGenerator::generate() {
    mtx.lock();
//    std::cout << "generator" << std::endl;
    auto *person = new Person();
    person->setX(map->getMid());
    person->setY(0);
    people->push_back(person);
    people->back()->run();
    mtx.unlock();
}

void EntityGenerator::removePerson(Person *person) {

    auto it = std::find(people->begin(), people->end(), person);
    if (it != people->end()) {
        people->erase(it);
    }
//    std::cout << "Person " << person->getName() << " removed" << std::endl;
//    std::cout << "People size: " << people->size() << std::endl;
    delete person;
    person = nullptr;

}
