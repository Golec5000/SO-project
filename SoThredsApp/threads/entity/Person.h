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

    int getX() const;

    int getY() const;

    void setX(int x);

    void setY(int y);

    void setDirection(char direction);

    bool isRunning() const;

private:
    char diretion;
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
