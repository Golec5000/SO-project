#ifndef SWITCHTHREAD_H
#define SWITCHTHREAD_H

#include <mutex>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

class SwitchThread {
public:
    SwitchThread();

    ~SwitchThread();

    void run();

    char getSwitchState() const;

    pthread_t getThread() const;

    void stop();

private:
    char *switchState;
    int switchStateIndex;
    pthread_t thread;
    bool running;

    static void *pthreadStart(void *arg);

    void switchStateChange();

    std::mutex mtx;
};

#endif //SWITCHTHREAD_H
