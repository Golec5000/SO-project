//
// Created by wombat on 29.03.24.
//

#include "Person.h"

Person::Person(): direction(new char[3]{'^', '>', 'v'}), thread(0), running(false)
{
}

Person::~Person()
{
    delete[] direction;
    direction = nullptr;

    stop();
}

void Person::run()
{
    running = true;
    pthread_create(&thread, NULL, &Person::pthreadStart, this);
}

void Person::stop()
{
    if (running)
    {
        running = false;
        mtx.lock();
        pthread_join(thread, NULL);
        mtx.unlock();
    }
}

pthread_t Person::getThread() const
{
    return thread;
}

void* Person::pthreadStart(void* arg)
{
    auto* instance = static_cast<Person*>(arg);
    while (instance->running)
    {
        instance->switchDirection();
        usleep(1000000); // Zasypia na 1 sekundę
    }
    pthread_exit(nullptr);
    return nullptr;
}

void Person::switchDirection()
{
}
