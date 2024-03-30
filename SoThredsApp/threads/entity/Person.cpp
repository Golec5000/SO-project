#include "Person.h"


Person::Person() : thread(0), running(false), diretion('>') {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 5000);
    this->sleepTime = dis(gen);

    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ234567890!@$%&*()_+-=[]{}|;':,<?";

    for (int i = 0; i < 2; i++)
        name += chars[dis(gen) % chars.size()];

}

Person::~Person() {
    stop();
//    std::cout << "Person " << name << " deleted" << std::endl;
}

void Person::run() {
    running = true;
    pthread_create(&thread, NULL, &Person::pthreadStart, this);
//    std::cout << "Person " << name << " started" << std::endl;
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
    std::mutex cv_m;
    std::unique_lock<std::mutex> lk(cv_m);
    while (instance->running) {
        instance->move();
        usleep(instance->sleepTime * 100);
    }
    pthread_exit(nullptr);
}

void Person::move() {
    mtx.lock();
    switch (diretion) {
        case '^':
            if (getX() > 0) {
                setX(getX() - 1);
            } else {
                setY(getY() + 1);
                setDirection('>');
            }
            break;
        case '>':
            if (getY() < 40)
                setY(getY() + 1);
            break;
        case 'v':
            if (getX() < 30) {
                setX(getX() + 1);
            } else {
                setY(getY() + 1);
                setDirection('>');
            }
            break;
    }
    if(getY() == 39) {
        usleep(500000); // Zasypia na 0.5 sekundy
        stop();
    }
    mtx.unlock();
}

std::string Person::getName() const {
    return name;
}

int Person::getX() const {
    return x;
}

int Person::getY() const {
    return y;
}

void Person::setX(int x) {
    this->x = x;
}

void Person::setY(int y) {
    this->y = y;
}

bool Person::isRunning() const {
    return running;
}

void Person::setDirection(char direction) {
    this->diretion = direction;
}
