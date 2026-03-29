#include <stdio.h>
#include "utils.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

int kbhitOS()
{
#ifdef _WIN32
    return _kbhit();
#elif __unix__
    int ch = getchar();
    if (!ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
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

// https://stackoverflow.com/a/62784810 - ty ! enables color escape codes on windows
void enableANSI()
{
#ifdef _WIN32
    DWORD dwMode = 0;
    HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleMode(stdoutHandle, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(stdoutHandle, dwMode);
#endif
}

// https://stackoverflow.com/a/54652335 - ty!
void setCoord()
{
#ifdef _WIN32
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#elif __unix__
    fprintf(stdout, "\033[H");
#endif
}

void clearScreen()
{
    fprintf(stdout, "\033[H\033[J");
}

void sleepOS(int msTime)
{
#ifdef _WIN32
    Sleep(msTime);
#elif __unix__
    sleep(msTime / 1000);
#endif
}
