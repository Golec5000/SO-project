#include "SwitchThread.h"
#include <unistd.h>

SwitchThread::SwitchThread() : switchState(new char[3]{'^', '>', 'v'}), switchStateIndex(0), thread(0), running(false)
{
}

SwitchThread::~SwitchThread()
{
    delete[] switchState;

    if (running)
    {
        pthread_join(thread, NULL);
    }

}

void SwitchThread::run()
{
    running = true;
    pthread_create(&thread, NULL, &SwitchThread::pthreadStart, this);
}

char SwitchThread::getSwitchState() const
{
    return switchState[switchStateIndex];
}

pthread_t SwitchThread::getThread() const
{
    return thread;
}

void* SwitchThread::pthreadStart(void* arg)
{
    auto* instance = static_cast<SwitchThread*>(arg);
    while (instance->running)
    {
        instance->switchStateChange();
        usleep(1000000); // Zasypia na 1 sekundę
    }
    pthread_exit(nullptr);
    return nullptr;
}

void SwitchThread::switchStateChange()
{
    switchStateIndex = (switchStateIndex + 1) % 3;
}

void SwitchThread::stop()
{
    if (running)
    {
        running = false;
        mtx.lock();
        pthread_join(thread, NULL);
        mtx.unlock();
    }
}
