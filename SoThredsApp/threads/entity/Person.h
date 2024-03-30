#ifndef PERSON_H
#define PERSON_H

#include <mutex>
#include <pthread.h>
#include <unistd.h>
#include <random>
#include <iostream>

class Person {
public:
    Person();

    ~Person();

    void run();

    void stop();

    pthread_t getThread() const;

    std::string getName() const;

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }

    bool isRunning() const {
        return running;
    }

private:
    char *direction;
    pthread_t thread;
    bool running;
    std::string name;

    int x;
    int y;

    static void *pthreadStart(void *arg);

    void move();

    long sleepTime;
    std::mutex mtx;
};


#endif //PERSON_H
