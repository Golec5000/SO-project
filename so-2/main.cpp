#include <iostream>
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
std::vector<char> switchChars = {'^', '>', 'v'};
std::list<std::shared_ptr<People *>> clients;

std::atomic<bool> isSwitchRunning = true;
std::atomic<bool> isGeneratorRunning = true;
std::atomic<bool> isClientCheckerRunning = true;

std::mutex clientsMutex;

int width = 40;
int height = 31;
int mid = 15;
int selectorPoint = 29;

char pathChar = '1';
char switchChar = '^';
char stationChar = '#';

void draw_map(WINDOW *ptr);
void draw_arm(int start, int end, int row);
void switchDirection();
void generateClients();
void checkClients();

int main() {
    initscr();
    curs_set(0);
    nodelay(stdscr, TRUE);
    WINDOW *buffer = newwin(0, 0, 0, 0);

    map = std::vector<std::vector<std::string>>(height, std::vector<std::string>(width, ".."));

    std::thread switchThread(switchDirection);
    std::thread clientsThread(generateClients);
    std::thread checkClientsThread(checkClients);

    while (true) {
        werase(buffer);

        if (!clients.empty()) {
            for (auto &client: clients) {
                if ((*client)->getYPos() == selectorPoint && (*client)->getXPos() == mid)
                    (*client)->setDirection(switchChar);
            }
        }

        draw_map(buffer);
        wprintw(buffer, "Press 'space' to quit\n");

        overwrite(buffer, stdscr);
        refresh();

        int c = getch();
        if (c == ' ') {
            endwin();

            isSwitchRunning = false;
            switchThread.join();

            isGeneratorRunning = false;
            clientsThread.join();

            isClientCheckerRunning = false;
            checkClientsThread.join();

            for (auto &client: clients) {
                (*client)->joinThread();
            }

            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}

void draw_map(WINDOW *ptr) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map[i][j] = "..";
        }
    }

    for (int j = 0; j < width - 1; j++)
        map[mid][j] = pathChar;

    map[mid][width - 1] = stationChar;
    map[mid][selectorPoint] = switchChar;

    draw_arm(mid + 1, height, height - 1);
    draw_arm(mid - 1, 0, 0);

    if (!clients.empty()) {
        for (auto &client: clients) {
            if (!(*client)->getToErase()) {
                map[(*client)->getXPos()][(*client)->getYPos()] = (*client)->getName();
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            wprintw(ptr, "%4s", map[i][j].c_str());
        wprintw(ptr, "\n");
    }
}

void draw_arm(int start, int end, int row) {
    for (int i = start; i != end; i += (start < end ? 1 : -1))
        map[i][selectorPoint] = pathChar;
    for (int i = selectorPoint + 1; i < width - 1; i++)
        map[row][i] = pathChar;
    map[row][width - 1] = stationChar;
}

void switchDirection() {
    int cycle = 0;

    while (isSwitchRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        switchChar = switchChars[cycle % 3];
        cycle++;
    }
}

void generateClients() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(2000, 6000);

    while (isGeneratorRunning) {
        auto client = std::make_shared<People *>(new People(mid, 0));
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.push_back(client);
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
    }
}

void checkClients() {
    while (isClientCheckerRunning) {
        if (!clients.empty()) {
            for (auto client = clients.begin(); client != clients.end();) {
                if ((*(*client))->getToErase()) {
                    client = clients.erase(client);
                } else {
                    ++client;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}