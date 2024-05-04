#include <vector>
#include <random>
#include <memory>
#include <thread>
#include <ncurses.h>
#include <atomic>
#include <mutex>
#include <list>
#include "helpClasses/People.h"

std::vector<std::vector<std::string>> map;
std::list<std::shared_ptr<People *>> clients;

std::atomic<bool> isRunning = true;
std::mutex clientsMutex;

int width = 40;
int height = 31;
int mid = 15;
int selectorPoint = 29;

char pathChar = '1';
char switchChar = '^';
char stationChar = '#';

void draw_map(WINDOW *ptr);

void down_arm();

void up_arm();

void switchDirection();

void generateClients();

void checkClients();

void setSwitchDirectionForClients();

int main() {
    initscr();
    curs_set(0);
    nodelay(stdscr, TRUE);
    WINDOW *buffer = newwin(0, 0, 0, 0);

    map = std::vector<std::vector<std::string>>(height, std::vector<std::string>(width, ".."));

    std::thread switchThread(switchDirection);
    std::thread clientsThread(generateClients);
    std::thread checkClientsThread(checkClients);

    while (isRunning) {
        werase(buffer);

        wprintw(buffer, "City Hall simulation\n");
        wprintw(buffer, "Living threads: %zu\n", clients.size());

        setSwitchDirectionForClients();

        draw_map(buffer);
        wprintw(buffer, "Press 'space' to quit\n");
        overwrite(buffer, stdscr);
        refresh();

        if (getch() == ' ') {
            endwin();
            isRunning = false;
            switchThread.join();
            clientsThread.join();
            checkClientsThread.join();
            for (auto &client: clients) {
                (*client)->joinThread();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}

void setSwitchDirectionForClients() {
    if (!clients.empty()) {
        for (auto &client: clients) {
            if ((*client)->getYPos() == selectorPoint && (*client)->getXPos() == mid)
                (*client)->setDirection(switchChar);
        }
    }
}

void draw_map(WINDOW *ptr) {
    for (int j = 0; j < width - 1; j++) map[mid][j] = pathChar;

    map[mid][width - 1] = stationChar;
    map[mid][selectorPoint] = switchChar;

    down_arm();
    up_arm();

    for (auto &client: clients) {
        if (!(*client)->getToErase()) {
            map[(*client)->getXPos()][(*client)->getYPos()] = (*client)->getName();
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            wprintw(ptr, "%4s", map[i][j].c_str());
        wprintw(ptr, "\n");
    }
}

void down_arm() {

    for (int i = mid + 1; i < height; i++) map[i][selectorPoint] = pathChar;
    for (int i = selectorPoint + 1; i < width - 1; i++) map[height - 1][i] = pathChar;
    map[height - 1][width - 1] = stationChar;

}

void up_arm() {

    for (int i = mid - 1; i >= 0; i--) map[i][selectorPoint] = pathChar;
    for (int i = selectorPoint + 1; i < width - 1; i++) map[0][i] = pathChar;
    map[0][width - 1] = stationChar;

}

void switchDirection() {
    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
        switchChar = (switchChar == '^') ? '>' : (switchChar == '>') ? 'v' : '^';
    }
}

void generateClients() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 7);

    while (isRunning) {
        auto client = std::make_shared<People *>(new People(mid, 0));
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.push_back(client);
        std::this_thread::sleep_for(std::chrono::seconds(dis(gen)));
    }
}

void checkClients() {
    while (isRunning) {
        for (auto client = clients.begin(); client != clients.end();) {
            if ((*(*client))->getToErase()) client = clients.erase(client);
            else ++client;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}