#ifndef UTILS_H
#define UTILS_H

#ifdef _WIN32
void enableANSI();
#elif __unix__
void setupTerminal();
#endif

void setCoord();
void clearScreen();

void initOS();
void sleepOS(int msTime);
int kbhitOS();
int getchOS();

#endif
