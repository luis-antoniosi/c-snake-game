#include <stdio.h>
#include "utils.h"

#ifdef _WIN32
#include <windows.h>
#elif __unix__
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// https://bitismyth.wordpress.com/2015/06/18/um-kbhit-para-o-linux/ - ty!
void _kbhit()
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

// https://www.vivaolinux.com.br/topico/C-C++/Erro-no-uso-da-biblioteca-termiosh - ty!
void _getch()
{
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
#endif

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

void sleep(int msTime)
{
#ifdef _WIN32
    Sleep(msTime);
#elif __unix__
    sleep(msTime / 1000);
#endif
}