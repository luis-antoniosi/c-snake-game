#define _POSIX_C_SOURCE 199309L // needed for nanosleep()

#include <stdio.h>
#include "utils.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>

// https://stackoverflow.com/a/62784810 - ty ! enables escape codes on windows cmd
void enableANSI()
{
    DWORD dwMode = 0;
    HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleMode(stdoutHandle, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(stdoutHandle, dwMode);
}
#elif __unix__
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <time.h>

static struct termios ogTerm;

void restoreTerminal()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &ogTerm);
}

void setupTerminal()
{
    tcgetattr(STDIN_FILENO, &ogTerm);
    atexit(restoreTerminal);

    struct termios term = ogTerm;
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
#endif

// general functions

// https://stackoverflow.com/a/54652335 - ty!
void setCoord()
{
#ifdef _WIN32
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#elif __unix__
    printf("\033[H");
#endif
}

void clearScreen()
{
    printf("\033[H\033[J");
}

// OS specific functions

void initOS()
{
#ifdef _WIN32
    enableANSI();
#elif __unix__
    setupTerminal();
#endif
}

void sleepOS(int msTime)
{
#ifdef _WIN32
    Sleep(msTime);
#elif __unix__
    struct timespec ts;

    ts.tv_sec = (long)(msTime / 1000);
    ts.tv_nsec = (long)((msTime - (ts.tv_sec * 1000)) * 1000000);
    nanosleep(&ts, NULL);
#endif
}

int kbhitOS()
{
#ifdef _WIN32
    return _kbhit();
#elif __unix__
    int bytesWaiting;
    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
    return bytesWaiting;
#endif
}

int getchOS()
{
#ifdef _WIN32
    return getch();
#elif __unix__
    return getchar();
#endif
}
