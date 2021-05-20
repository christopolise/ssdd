#include <ncurses.h>
#include <stdio.h>

#include "snake.h"


#define SNAKE_INPUT_EVENT "/dev/input/event3"

void genDot()
{
    srand(time(NULL));
    dotX = (rand() % 45) + 1;
    dotY = (rand() % 35) + 1;

    drawPixel(dotX, dotY, banana, true);
}

void initSnakeScreen()
{

    initScreen();

    // Initialize snake
    snakePath = calloc(sizeof(xy), 1);
    snakePath[0].x = 10;
    snakePath[0].y = 10;

    // Initialize blank screen buffer
    for(uint8_t row = 0; row < 18; row++)
    {
        for(uint8_t col = 0; col < 48; col++)
        {
            banana[row][col].a = false;
            banana[row][col].b = false;
            banana[row][col].c = false;
            banana[row][col].d = false;
            banana[row][col].e = false;
            banana[row][col].f = false;
            banana[row][col].g = false;
            banana[row][col].dp = false;
        }
    }

    // Draw Border
    for(int i = 0; i < 48; i++)
    {
        banana[0][i].a = true;
        banana[17][i].d = true;
    }
    for(int i = 0; i < 18; i++)
    {
        banana[i][0].e = true;
        banana[i][0].f = true;
        banana[i][47].b = true;
        banana[i][47].c = true;
    }

    // Place dot
    genDot();
    snakeRight = true;

    updateScreen(banana);
}

bool checkSnake()
{
    return false;
}

void drawSnake()
{
    if(snakeUp)
    {
        if(snakePath[0].y == 0)
        {
            // Die
        }
        else
        {
            drawPixel(snakePath[score - 1].x, snakePath[score - 1].y, banana, false);
            for(int i = score - 1; i > 0; i--)
            {
                snakePath[i].x = snakePath[i-1].x;
                snakePath[i].y = snakePath[i-1].y;
            }
            snakePath[0].x = snakePath[1].x;
            snakePath[0].y = snakePath[1].y - 1;
            drawPixel(snakePath[0].x, snakePath[0].y, banana, true);
        }

    }
    else if(snakeDown)
    {
        if(snakePath[0].y == 35)
        {
           // Die
        }
        else
        {
            drawPixel(snakePath[score - 1].x, snakePath[score - 1].y, banana, false);
            for(int i = score - 1; i > 0; i--)
            {
                snakePath[i].x = snakePath[i-1].x;
                snakePath[i].y = snakePath[i-1].y;
            }
            snakePath[0].x = snakePath[1].x;
            snakePath[0].y = snakePath[1].y + 1;
            drawPixel(snakePath[0].x, snakePath[0].y, banana, true);
        }
    }
    else if(snakeLeft)
    {
        if(snakePath[0].x == 0)
        {
            // Die
        }
        else
        {
            drawPixel(snakePath[score - 1].x, snakePath[score - 1].y, banana, false);
            for(int i = score - 1; i > 0; i--)
            {
                snakePath[i].x = snakePath[i-1].x;
                snakePath[i].y = snakePath[i-1].y;
            }
            snakePath[0].x = snakePath[1].x - 1;
            snakePath[0].y = snakePath[1].y;
            drawPixel(snakePath[0].x, snakePath[0].y, banana, true);
        }
    }
    else if(snakeRight)
    {
        if(snakePath[0].x == 47)
        {
            // Die
        }
        else
        {
            drawPixel(snakePath[score - 1].x, snakePath[score - 1].y, banana, false);
            for(int i = score - 1; i > 0; i--)
            {
                snakePath[i].x = snakePath[i-1].x;
                snakePath[i].y = snakePath[i-1].y;
            }
            snakePath[0].x = snakePath[1].x + 1;
            snakePath[0].y = snakePath[1].y;
            drawPixel(snakePath[0].x, snakePath[0].y, banana, true);
        }
    }
}

int snake()
{

    char *pDevice = SNAKE_INPUT_EVENT;

    // Open Keyboard
    fd = open(pDevice, O_RDONLY | O_NONBLOCK);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }

    while(data.value != SNAKE_Q_KEY_VAL)
    {

        // Draw snake
        for(int i = 0; i < score; i++)
        {
            drawPixel(snakePath[i].x, snakePath[i].y, banana, true);
        }

        if(data.value == SNAKE_W_KEY_VAL)
        {
            snakeUp = true;
            snakeDown = false;
            snakeLeft = false;
            snakeRight = false;
        }
        else if(data.value == SNAKE_S_KEY_VAL)
        {
            snakeUp = false;
            snakeDown = true;
            snakeLeft = false;
            snakeRight = false;
        }
        else if(data.value == SNAKE_D_KEY_VAL)
        {
            snakeUp = false;
            snakeDown = false;
            snakeLeft = false;
            snakeRight = true;
        }
        else if(data.value == SNAKE_A_KEY_VAL)
        {
            snakeUp = false;
            snakeDown = false;
            snakeLeft = true;
            snakeRight = false;
        }
        drawSnake();
        updateScreen(banana);
    }

    return endwin();
}