#ifndef UTILS_H
#define UTILS_H

void enableANSI();
void setCoord();
void clearScreen();
void sleep(int msTime);

#ifdef __unix__
    int _kbhit();
    int _getch();
#endif

#endif