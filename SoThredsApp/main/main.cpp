#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <csignal>
#include <cstdlib>
#include <fcntl.h>

#include <iostream>
#include "../map/MaInAppMap.h"
#include "../threads/mapRender/MapRender.h"
#include "../threads/switch/SwitchThread.h"


// Zmienna globalna do przechowywania stanu działania
volatile sig_atomic_t running = 1;

// Funkcja obsługi sygnału
void handle_signal(int signal)
{
    // Ustaw zmienną running na 0, aby zakończyć pętlę
    running = 0;
}

// Funkcja do sprawdzenia, czy klawisz został naciśnięty
int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


int main()
{
    MaInAppMap* map = new MaInAppMap();
    MapRender* mapRender = new MapRender();
    SwitchThread* switchThread = new SwitchThread();

    mapRender->setMap(map);
    mapRender->setSwitchThread(switchThread);
    mapRender->start();

    // Czekaj na zakończenie renderowania
    while (mapRender->isRunning())
    {
        if (kbhit())
        {
            int ch = getchar();
            if (ch == ' ') // Jeśli naciśnięto spację, zakończ pętlę
            {
                mapRender->stop();
                switchThread->stop();
                break;
            }
        }
        usleep(1000000); // Zasypia na 1 sekundę
    }

    delete map;
    delete mapRender;
    delete switchThread;

    return 0;
}
