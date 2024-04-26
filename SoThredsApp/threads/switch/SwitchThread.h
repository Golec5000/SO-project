#ifndef SWITCHTHREAD_H
#define SWITCHTHREAD_H

#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>

class SwitchThread {
public:
    SwitchThread();

    ~SwitchThread();

    void run();

    char getSwitchState() const;

    void stop();

private:
    char *switchState;
    int switchStateIndex;
    std::thread thread;
    bool running;

    void switchStateChange();

    std::mutex mtx;
};

#endif //SWITCHTHREAD_H
