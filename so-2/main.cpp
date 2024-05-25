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
#include "helpClasses/Cord.h"

std::mutex directionMutex;

std::vector<std::vector<Cord>> map;
std::list<std::shared_ptr<People *>> clients;

std::atomic_bool isRunning = true;
std::atomic_bool isSwitchBlocked = false;

std::atomic_int switchCounter = 0;

int width = 40;
int height = 31;
int mid = 15;
int selectorPoint = 29;
int switchBorder = 10; // Domyslna wartosc wynosi 10

char pathChar = '_';
char switchChar = '^';
char stationChar = '#';

void draw_map(WINDOW *ptr);

void down_arm();

void up_arm();

void switchDirection();

void generateClients();

void checkClients();

void setSwitchDirectionForClients();

void endProgram(std::thread &switchThread, std::thread &clientsThread, std::thread &checkClientsThread);

void prepareMainMap();

int main(int argc, char **argv) {

    // Sprawdź, czy została podana wartość graniczna przełącznika
    if (argc > 1) {
        switchBorder = std::stoi(argv[1]);
    }

    initscr();
    curs_set(0);
    nodelay(stdscr, TRUE);
    WINDOW *buffer = newwin(0, 0, 0, 0);

    prepareMainMap();

    std::thread switchThread(switchDirection);
    std::thread clientsThread(generateClients);
    std::thread checkClientsThread(checkClients);

    while (isRunning) {
        werase(buffer);

        wprintw(buffer, "City Hall simulation\n");
        wprintw(buffer, "Living threads: %zu\n", clients.size());
        wprintw(buffer, "Threads after switch: %d\n", switchCounter.load());
        wprintw(buffer, "Lock on switch: %d\n", switchBorder);

        setSwitchDirectionForClients();

        draw_map(buffer);

        wprintw(buffer, "Point 1 lock: %d\n", map[0][39].ocupied.load());
        wprintw(buffer, "Point 2 lock: %d\n", map[mid][39].ocupied.load());
        wprintw(buffer, "Point 3 lock: %d\n", map[height - 1][39].ocupied.load());
        wprintw(buffer, "Switch lock: %d\n", isSwitchBlocked.load());
        wprintw(buffer, "Generator lock: %d\n", map[mid][0].ocupied.load());
        wprintw(buffer, "Press 'space' to quit\n");
        overwrite(buffer, stdscr);
        refresh();

        endProgram(switchThread, clientsThread, checkClientsThread);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}

void prepareMainMap() {
    map = std::vector<std::vector<Cord>>(height, std::vector<Cord>(width));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            map[i][j] = Cord(i, j);
        }
    }
}

void endProgram(std::thread &switchThread, std::thread &clientsThread, std::thread &checkClientsThread) {
    if (getch() == ' ') {
        endwin();
        isRunning = false;
        std::cout << "Wyłączanie switcha" << std::endl;
        if (switchThread.joinable()) {
            switchThread.join();
        }
        std::cout << "Wyłączanie generatora ludzi" << std::endl;
        if (clientsThread.joinable()) {
            clientsThread.join();
        }
        std::cout << "Wyłączanie watku za sprawdzanie życia wątków" << std::endl;
        if (checkClientsThread.joinable()) {
            checkClientsThread.join();
        }
        std::cout << "Wyłączanie pozostałych ludzi którzy nie dotarli do końca" << std::endl;
        for (auto &client: clients) {
            if (client && *client) { // Sprawdź, czy wskaźnik do klienta i wskaźnik do wątku nie są null
                (*client)->setRunning(false);
                if ((*client)->isThreadJoinable()) {
                    (*client)->joinThread();
                }
            }
        }
        std::cout << "Wyłączanie całęgo systemu powidło sie !" << std::endl;
    }
}

void setSwitchDirectionForClients() {
    //Synchronizacja wątków obiektow klasy People z wątkiem głównym ze zmiana kierunku przełącznika za pomocą mutexa
    std::lock_guard<std::mutex> lock(directionMutex);
    for (auto &client: clients) {
        if ((*client)->getCord()->y == selectorPoint && (*client)->getCord()->x == mid &&
            !(*client)->getHasCrossedSwitch()) {

            (*client)->setDirection(switchChar);
            (*client)->setHasCrossedSwitch(true);
            switchCounter++;

            // Jeśli liczba osób, które przekroczyły przełącznik, osiągnęła określony próg, zablokuj przełącznik
            if (switchCounter >= switchBorder) {
                isSwitchBlocked = true;
            }
        }

    }
}

void draw_map(WINDOW *ptr) {
    for (int j = 0; j < width - 1; j++) map[mid][j].cordChar = pathChar;

    map[mid][width - 1].cordChar = stationChar;
    map[mid][selectorPoint].cordChar = switchChar;

    down_arm();
    up_arm();

    for (auto &client: clients)
        if (!(*client)->getToErase())
            map[(*client)->getCord()->x][(*client)->getCord()->y].cordChar = (*client)->getName();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            wprintw(ptr, "%4s", map[i][j].cordChar.c_str());
        wprintw(ptr, "\n");
    }
}

void down_arm() {
    for (int i = mid + 1; i < height; i++) map[i][selectorPoint].cordChar = pathChar;
    for (int i = selectorPoint + 1; i < width - 1; i++) map[height - 1][i].cordChar = pathChar;
    map[height - 1][width - 1].cordChar = stationChar;
}

void up_arm() {
    for (int i = mid - 1; i >= 0; i--) map[i][selectorPoint].cordChar = pathChar;
    for (int i = selectorPoint + 1; i < width - 1; i++) map[0][i].cordChar = pathChar;
    map[0][width - 1].cordChar = stationChar;
}

void switchDirection() {
    std::array<char, 3> directions = {'^', '>', 'v'};
    int index = 0;

    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        switchChar = directions[index++ % directions.size()];
    }
}

void generateClients() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(500, 2000);

    while (isRunning) {
        if (!map[mid][0].ocupied.load()) {
            clients.push_back(std::make_shared<People *>(new People(mid, 0, map)));
            map[mid][0].ocupied.store(true);
            (*clients.back())->start(isSwitchBlocked);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
    }
}

void checkClients() {
    while (isRunning) {
        clients.remove_if([&](const auto &client) {
            bool toErase = (*client)->getToErase();
            if (toErase) {
                --switchCounter;
                if (switchCounter < switchBorder) {
                    isSwitchBlocked = false;
                }
            }
            return toErase;
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
}
