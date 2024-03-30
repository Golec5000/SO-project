#include "Person.h"

Person::Person() : direction(new char[3]{'^', '>', 'v'}), thread(0), running(false) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 5000);
    this->sleepTime = dis(gen);

    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=[]{}|;':,.<>?";

    for (int i = 0; i < 2; i++)
        name += chars[dis(gen) % chars.size()];

}

Person::~Person() {
    delete[] direction;
    direction = nullptr;

    stop();
}

void Person::run() {
    running = true;
    pthread_create(&thread, NULL, &Person::pthreadStart, this);
}

void Person::stop() {
    if (running) {
        running = false;
        mtx.lock();
        pthread_join(thread, NULL);
        mtx.unlock();
    }
}

pthread_t Person::getThread() const {
    return thread;
}

void *Person::pthreadStart(void *arg) {
    auto *instance = static_cast<Person *>(arg);
    while (instance->running) {
        instance->move();
        usleep(instance->sleepTime * 100);
    }
    pthread_exit(nullptr);
    return nullptr;
}

void Person::move() {
    mtx.lock();
    if(getY() < 40){
        setY(getY() + 1);
    } else {
        stop();
    }
    mtx.unlock();
}

std::string Person::getName() const {
    return name;
}
