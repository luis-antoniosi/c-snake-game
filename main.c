#include "utils.h"
#include "game.h"

int main()
{
    initOS();

    Snake snake;
    Fruit fruit;
    
    int score = 0, key = -1;

    printStart();

    setup(&snake, &fruit);

    while (key != LEAVE)
    {
        input(&key);
        
        processInput(&snake, &fruit, &key, &score);
        
        drawGame(&snake, &fruit, score);

        sleepOS(500);
    }

    printGameOver();

    return 0;
}
