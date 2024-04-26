#include "SwitchThread.h"

SwitchThread::SwitchThread() : switchState(new char[3]{'^', '>', 'v'}), switchStateIndex(0), running(false) {
}

SwitchThread::~SwitchThread() {
    delete[] switchState;
    switchState = nullptr;

    stop();

    std::cout << "SwitchThread stopped" << std::endl;
}

void SwitchThread::run() {
    running = true;
    this->thread = std::thread(&SwitchThread::switchStateChange, this);
}

char SwitchThread::getSwitchState() const {
    return switchState[switchStateIndex];
}

void SwitchThread::switchStateChange() {
    while (running){
        std::lock_guard<std::mutex> lock(mtx);
        switchStateIndex = (switchStateIndex + 1) % 3;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void SwitchThread::stop() {
    if (running) {
        running = false;
        if(thread.joinable()) {
            thread.join();
        }
    }
}
