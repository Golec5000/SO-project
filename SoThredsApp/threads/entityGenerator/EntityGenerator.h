#ifndef ENTITYGENERATOR_H
#define ENTITYGENERATOR_H

#include <mutex>
#include <pthread.h>
#include <vector>
#include <algorithm>
#include "../entity/Person.h"
#include "../../map/MaInAppMap.h"

class EntityGenerator {
public:
    EntityGenerator();

    ~EntityGenerator();

    void run();

    void stop();

    pthread_t getThread() const;

    std::vector<Person *> *getPeople() const {
        return people;
    }

    void setMap(MaInAppMap *map) {
        this->map = map;
    }

private:
    pthread_t thread;
    bool running;

    static void *pthreadStart(void *arg);

    void generate();

    std::mutex mtx;
    std::vector<Person *> *people;
    MaInAppMap *map = nullptr;

    void removePerson(Person *person);

    std::vector<Person *> *finishedPeople;

    void removeFinishedPeople();
};


#endif //ENTITYGENERATOR_H
