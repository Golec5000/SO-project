#ifndef ENTITYGENERATOR_H
#define ENTITYGENERATOR_H

#include <mutex>
#include <pthread.h>
#include <vector>
#include <algorithm>
#include "../entity/Person.h"
#include "../../map/MainAppMap.h"

class EntityGenerator {
public:
    EntityGenerator();

    ~EntityGenerator();

    void run();

    void stop();

    std::vector<Person *> *getPeople() const {
        return people;
    }

    void setMap(MainAppMap *map) {
        this->map = map;
    }

private:
    pthread_t generateThread;
    pthread_t removeThread;

    bool running;

    void generate();

    std::mutex mtx;
    std::vector<Person *> *people;
    MainAppMap *map = nullptr;

    void removePerson(Person *person);

    void removeFinishedPeople();

    static void *generateThreadStart(void *arg);

    static void *removeThreadStart(void *arg);
};


#endif //ENTITYGENERATOR_H
