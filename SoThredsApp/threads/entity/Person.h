#ifndef PERSON_H
#define PERSON_H

#include <mutex>
#include <pthread.h>
#include <unistd.h>

class Person
{
public:
    Person();
    ~Person();
    void run();
    void stop();
    pthread_t getThread() const;

private:
    char* direction;
    pthread_t thread;
    bool running;
    static void* pthreadStart(void* arg);
    void switchDirection();
    std::mutex mtx;
};


#endif //PERSON_H
