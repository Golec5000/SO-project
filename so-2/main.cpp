#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <thread>
#include <ncurses.h>
#include <atomic>
#include <mutex>
#include <list>
#include <sstream>
#include <iomanip>
#include "helpClasses/People.h"
#include "helpClasses/Cord.h"

std::mutex clientsMutex;
std::mutex switchCharMutex;

std::vector<std::vector<Cord>> map;
std::list<std::shared_ptr<People *>> clients;

std::atomic_bool isRunning = true;
std::atomic_bool isSwitchBlocked = false;

std::atomic_int switchCounter = 0;

const int width = 40;
const int height = 31;
const int mid = 15;
const int selectorPoint = 29;

int switchBorder = 10; // Domyslna wartosc wynosi 10

const char pathChar = '_';
std::atomic_char switchChar = '^';
const char stationChar = '#';

void draw_map(WINDOW *ptr);

void down_arm();

void up_arm();

void switchDirection();

void generateClients();

void checkClients();

void endProgram(std::thread &switchThread, std::thread &clientsThread, std::thread &checkClientsThread);

void prepareMainMap();

void mapDrawer(WINDOW *buffer);

int main(int argc, char **argv) {

    try {
        // Sprawdź, czy została podana wartość graniczna przełącznika
        if (argc > 1) {
            switchBorder = std::stoi(argv[1]);
        }
    } catch (std::invalid_argument &e) {
        std::cerr << "Invalid argument for switch border value: " << argv[1] << std::endl;
        return 1;
    } catch (std::out_of_range &e) {
        std::cerr << "Out of range argument for switch border value: " << argv[1] << std::endl;
        return 1;
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
        mapDrawer(buffer);
        endProgram(switchThread, clientsThread, checkClientsThread);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}

void mapDrawer(WINDOW *buffer) {
    werase(buffer);

    // Inicjalizacja kolorów
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);

    wprintw(buffer, "\n");
    // Użycie kolorów
    wattron(buffer, COLOR_PAIR(1));
    wprintw(buffer, "  City Hall simulation\n");
    wattroff(buffer, COLOR_PAIR(1));

    wattron(buffer, COLOR_PAIR(2));
    wprintw(buffer, "  Living threads: %zu\n", clients.size());
    wattroff(buffer, COLOR_PAIR(2));

    wattron(buffer, COLOR_PAIR(3));
    wprintw(buffer, "  Threads after switch: %d\n", switchCounter.load());
    wattroff(buffer, COLOR_PAIR(3));

    wprintw(buffer, "  Lock on switch: %d\n", switchBorder);

    draw_map(buffer);

    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);

    wprintw(buffer, "  Endpoints status:\n");
    wattron(buffer, COLOR_PAIR(3));
    wprintw(buffer, "  Point up lock: ");
    wattroff(buffer, COLOR_PAIR(3));
    wattron(buffer, map[0][39].occupied.load() ? COLOR_PAIR(5) : COLOR_PAIR(4));
    wprintw(buffer, "%s\n", map[0][39].occupied.load() ? "Locked" : "Unlocked");
    wattroff(buffer, map[0][39].occupied.load() ? COLOR_PAIR(5) : COLOR_PAIR(4));

    wattron(buffer, COLOR_PAIR(3));
    wprintw(buffer, "  Point mid lock: ");
    wattroff(buffer, COLOR_PAIR(3));
    wattron(buffer, map[mid][39].occupied.load() ? COLOR_PAIR(5) : COLOR_PAIR(4));
    wprintw(buffer, "%s\n", map[mid][39].occupied.load() ? "Locked" : "Unlocked");
    wattroff(buffer, map[mid][39].occupied.load() ? COLOR_PAIR(5) : COLOR_PAIR(4));

    wattron(buffer, COLOR_PAIR(3));
    wprintw(buffer, "  Point down lock: ");
    wattroff(buffer, COLOR_PAIR(3));
    wattron(buffer, map[height - 1][39].occupied.load() ? COLOR_PAIR(5) : COLOR_PAIR(4));
    wprintw(buffer, "%s\n\n", map[height - 1][39].occupied.load() ? "Locked" : "Unlocked");
    wattroff(buffer, map[height - 1][39].occupied.load() ? COLOR_PAIR(5) : COLOR_PAIR(4));

    wprintw(buffer, "  Switch and generator status:\n");
    wattron(buffer, COLOR_PAIR(3));
    wprintw(buffer, "  Switch lock: ");
    wattroff(buffer, COLOR_PAIR(3));
    wattron(buffer, isSwitchBlocked.load() ? COLOR_PAIR(5) : COLOR_PAIR(4));
    wprintw(buffer, "%s\n", isSwitchBlocked.load() ? "Locked" : "Unlocked");
    wattroff(buffer, isSwitchBlocked.load() ? COLOR_PAIR(5) : COLOR_PAIR(4));

    wattron(buffer, COLOR_PAIR(3));
    wprintw(buffer, "  Generator lock: ");
    wattroff(buffer, COLOR_PAIR(3));
    wattron(buffer, map[mid][0].occupied.load() ? COLOR_PAIR(5) : COLOR_PAIR(4));
    wprintw(buffer, "%s\n", map[mid][0].occupied.load() ? "Locked" : "Unlocked");
    wattroff(buffer, map[mid][0].occupied.load() ? COLOR_PAIR(5) : COLOR_PAIR(4));

    // Rysowanie ramki wokół okna
    box(buffer, 0, 0);

    overwrite(buffer, stdscr);
    wrefresh(buffer);
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
            if (client && *client) {
                std::cout << "Wyłączanie klienta: " << (*client)->getName() << std::endl;
                (*client)->joinThread(isSwitchBlocked);
            }
        }

        std::cout << "Wyłączanie całego systemu powiodło się!" << std::endl;
    }
}

void draw_map(WINDOW *ptr) {
    std::stringstream buffer;

    // Inicjalizacja stałych części mapy
    for (int j = 0; j < width - 1; j++) map[mid][j].cordChar = pathChar;
    map[mid][width - 1].cordChar = stationChar;
    map[mid][selectorPoint].cordChar = switchChar;
    down_arm();
    up_arm();

    // Dodanie klientów do mapy
    for (auto &client: clients) {
        if (!(*client)->getToErase()) {
            map[(*client)->getCord()->x][(*client)->getCord()->y].cordChar = (*client)->getName();
        }
    }

    // Buforowanie mapy
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            buffer << std::setw(4) << map[i][j].cordChar;
        }
        buffer << "\n";
    }

    // Wydrukowanie całego bufora do okna jednocześnie
    wprintw(ptr, "%s", buffer.str().c_str());
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
        {
            std::lock_guard<std::mutex> lock(switchCharMutex);
            switchChar = directions[index++ % directions.size()];
            map[mid][selectorPoint].setDirection(switchChar);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
    }
}

void generateClients() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(500, 2000);

    while (isRunning) {
        if (!map[mid][0].occupied.load()) {
            auto newClient = std::make_shared<People *>(new People(mid, 0, map, switchCounter, switchBorder));
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                clients.push_back(newClient);
            }
            map[mid][0].occupied.store(true);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            (*newClient)->start(isSwitchBlocked);
            {
                std::unique_lock<std::mutex> lock(clientsMutex);
                (*newClient)->getCv().notify_all();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
    }
}


void checkClients() {
    while (isRunning) {
        try {
            std::lock_guard<std::mutex> lock(clientsMutex); // Dodajemy blokadę dla synchronizacji
            clients.remove_if([&](const auto &client) {
                bool toErase = (*client)->getToErase();
                if (toErase) {
                    (*client)->joinThread(isSwitchBlocked);  // Ensure thread is joined
                }
                return toErase;
            });
        } catch (const std::exception &e) {
            std::cerr << "Exception caught during client removal: " << e.what() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
}

