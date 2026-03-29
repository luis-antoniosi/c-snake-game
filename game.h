#ifndef GAME_H
#define GAME_H

// Dimensions
#define WIDTH       40
#define HEIGHT      20
#define BUFSIZE     (WIDTH * HEIGHT * 15)
#define TAILSIZE    100

// Borders and characters
#define TOPBOTTOM   '-'
#define LEFTRIGHT   '|'
#define SNAKEHEAD   'O'
#define SNAKETAIL   'o'
#define FRUIT       '*'

// Inputs
#define UP          0
#define DOWN        1
#define LEFT        2
#define RIGHT       3
#define LEAVE       4

// Colors
#define RESET       "\x1b[0m"
#define RED         "\x1b[31m"
#define GREEN       "\x1b[32m"

typedef struct
{
    int x;
    int y;
    int tailX[TAILSIZE];
    int tailY[TAILSIZE];
    int tailLen;
} Snake;

typedef struct
{
    int x;
    int y;
} Fruit;

void createSnake(Snake *snake);
void createFruit(Fruit *fruit);

void setup(Snake *snake, Fruit *fruit);
void drawGame(Snake *snake, Fruit *fruit, int score);

void input(int *key);
void processInput(Snake *snake, Fruit *fruit, int *key, int *score);

void printStart();
void printGameOver();

#endif