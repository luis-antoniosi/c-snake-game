#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"
#include "game.h"

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#endif

void createSnake(Snake *snake)
{
    snake->x = WIDTH / 2;
    snake->y = HEIGHT / 2;
    snake->tailLen = 0;
}

void createFruit(Fruit *fruit)
{
    fruit->x = rand() % (WIDTH - 2) + 1;
    fruit->y = rand() % (HEIGHT - 2) + 1;
}

// 

void setup(Snake *snake, Fruit *fruit)
{
    clearScreen();
    srand(time(NULL));

    createSnake(snake);
    createFruit(fruit);
}

void drawGame(Snake *snake, Fruit *fruit, int score)
{
    setCoord();

    // clearest way I found was to use a buffer
    char buffer[BUFSIZE] = {0};
    char *ptr = buffer;

    for (int i = 0; i < WIDTH; i++)
        *ptr++ = TOPBOTTOM;

    *ptr++ = '\n';

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0 || j == WIDTH - 1)
                *ptr++ = LEFTRIGHT;
            else if (i == snake->y && j == snake->x)
                ptr += sprintf(ptr, GREEN "%c" RESET, SNAKEHEAD);
            else if (i == fruit->y && j == fruit->x)
                ptr += sprintf(ptr, RED "%c" RESET, FRUIT);
            else
            {
                int tail = 0;
                for (int k = 0; k < snake->tailLen; k++)
                {
                    if (snake->tailX[k] == j && snake->tailY[k] == i)
                    {
                        ptr += sprintf(ptr, GREEN "%c" RESET, SNAKETAIL);
                        tail = 1;
                        break;
                    }
                }

                if (!tail)
                    *ptr++ = ' ';
            }
        }

        *ptr++ = '\n';
    }

    for (int i = 0; i < WIDTH; i++)
        *ptr++ = TOPBOTTOM;
    *ptr++ = '\n';

    ptr += sprintf(ptr, "Score: %-4d\n", score);

    *ptr = '\0';
    fputs(buffer, stdout);
}
 
// Snake related

void processTail(Snake *snake)
{
    int prevX = snake->x, prevY = snake->y;

    for (int i = 0; i < snake->tailLen; i++)
    {
        // saves the snake's path to be used in case theres a tail
        int prev2X = snake->tailX[i], prev2Y = snake->tailY[i];

        snake->tailX[i] = prevX;
        snake->tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }
}

void input(int *key)
{
    if (kbhitOS())
    {
        int ch = getchOS();
        switch (tolower(ch))
        {
        case 'w':
            *key = UP;
            break;
        case 's':
            *key = DOWN;
            break;
        case 'a':
            *key = LEFT;
            break;
        case 'd':
            *key = RIGHT;
            break;
        case 'q':
            *key = LEAVE;
            break;
        }
    }
}

void processInput(Snake *snake, Fruit *fruit, int *key, int *score)
{
    processTail(snake);

    switch (*key)
    {
    case UP:
        snake->y--;
        break;
    case DOWN:
        snake->y++;
        break;
    case LEFT:
        snake->x--;
        break;
    case RIGHT:
        snake->x++;
        break;
    }

    if ((snake->x <= 0 || snake->x >= WIDTH - 1) || (snake->y <= 0 || snake->y >= HEIGHT - 1))
        *key = LEAVE;

    if (snake->x == fruit->x && snake->y == fruit->y)
    {
        (*score) += 5;

        if (snake->tailLen < TAILSIZE)
            snake->tailLen++;

        createFruit(fruit);
    }
}

// Game state functions

// https://patorjk.com/software/taag/
void printStart()
{
    clearScreen();
    const char *start =
        " _____             _          _____\n"
        "/  ___|           | |        |  __ \\\n"
        "\\ `--. _ __   __ _| | _____  | |  \\/ __ _ _ __ ___   ___\n"
        " `--. \\ '_ \\ / _` | |/ / _ \\ | | __ / _` | '_ ` _ \\ / _ \\\n"
        "/\\__/ / | | | (_| |   <  __/ | |_\\ \\ (_| | | | | | |  __/\n"
        "\\____/|_| |_|\\__,_|_|\\_\\___|  \\____/\\__,_|_| |_| |_|\\___|\n"
        "\n"
        "______                    _____   _              _             _\n"
        "| ___ \\                  |  _  | | |            | |           | |\n"
        "| |_/ / __ ___  ___ ___  | |/' | | |_ ___    ___| |_ __ _ _ __| |_\n"
        "|  __/ '__/ _ \\/ __/ __| |  /| | | __/ _ \\  / __| __/ _` | '__| __|\n"
        "| |  | | |  __/\\__ \\__ \\ \\ |_/ / | || (_) | \\__ \\ || (_| | |  | |_\n"
        "\\_|  |_|  \\___||___/___/  \\___/   \\__\\___/  |___/\\__\\__,_|_|   \\__|\n";

    printf("%s", start);

    int ch = 0;
    while (ch != '0')
    {
        if (kbhitOS())
            ch = getchOS();
    }
}

void printGameOver()
{
    clearScreen();
    const char *gameOver =
        " _____                        _____                  __\n"
        "|  __ \\                      |  _  |                 \\ \\\n"
        "| |  \\/ __ _ _ __ ___   ___  | | | |_   _____ _ __  (_) |\n"
        "| | __ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|   | |\n"
        "| |_\\ \\ (_| | | | | | |  __/ \\ \\_/ /\\ V /  __/ |     _| |\n"
        " \\____/\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|    (_) |\n"
        "                                                     /_/\n";

    printf("%s", gameOver);
}
