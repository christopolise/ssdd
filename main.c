#include <stdio.h>
#include "ssdd_display.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>

#define Y_MIN 3
#define Y_MAX 35
#define X_MIN 0
#define X_MAX 47

static bool up = false;
static bool left = true;

static uint8_t curX = 24;
static uint8_t curY = 18;
static uint8_t lastX;
static uint8_t lastY;

static uint16_t playerScore = 0;
static uint16_t compScore = 0;
static uint16_t prevPlayerScore = 0;
static uint16_t prevCompScore = 0;

static uint8_t counter = 0;

static uint8_t paddle[6] = {15, 16, 17, 18, 19, 20};
static uint8_t compPaddle[6] = {16, 17, 18, 19, 20, 21};

void drawScore(int score, bool isPlayer, digit screen[18][48])
{
    digit ones = drawNum(score % 10);
    digit tens = drawNum((score / 10) % 10);
    digit hundreds = drawNum((score / 100) % 10);
    digit thousands = drawNum(score / 1000);

    if(isPlayer)
    {
        screen[0][21] = ones;
        screen[0][20] = tens;
        screen[0][19] = hundreds;
        screen[0][18] = thousands; 
    }
    else
    {
        screen[0][44] = ones;
        screen[0][43] = tens;
        screen[0][42] = hundreds;
        screen[0][41] = thousands;
    }
}

void moveBall()
{
    lastX = curX;
    lastY = curY;

    if(up)
    {
        if(curY == Y_MIN)
        {
            up = false;
            curY++;
        }
        else
        {
            curY--;
        }
    }
    else
    {
        if(curY == Y_MAX)
        {
            up = true;
            curY--;
        }
        else
        {
            curY++;
        }
    }

    if(left)
    {
        if(curX == (X_MIN + 2))
        {
            for(int i = 0; i < 6; i++)
            {
                if(curY == paddle[i])
                {
                    left = false;
                    curX++;
                    break;
                }
            }
        }
        if(curX == X_MIN)
        {
            left = false;
            curX = 24;
            curY = 18;
            prevCompScore = compScore;
            compScore++;
        }
        else
        {
            curX--;
        }
    }
    else
    {
        if(curX == (X_MAX - 2))
        {
            for(int i = 0; i < 6; i++)
            {
                if(curY == compPaddle[i])
                {
                    left = true;
                    curX--;
                    break;
                }
            }
        }
        if(curX == X_MAX)
        {
            left = true;
            curX = 24;
            curY = 18;
            prevPlayerScore = playerScore;
            playerScore++;
        }
        else
        {
            curX++;
        }
    }
}

int main(int argc, char * argv[])
{

    digit banana[18][48];

    // char screenbuff[10410];

    int fd, bytes;
    struct input_event data;

    const char *pDevice = "/dev/input/event3";

    // Open Keyboard
    fd = open(pDevice, O_RDONLY | O_NONBLOCK);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }

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

    initScreen();

    // Draw Upper Border
    for(int i = 1; i < 47; i++)
    {
        banana[1][i].a = true;
    }
    banana[0][24].e = true;
    banana[0][24].f = true;
    updateScreen(banana);

    while(1)
    {

        // Read Keyboard Data
          bytes = read(fd, &data, sizeof(data));
          if(bytes > 0)
          {
            //   printf("Keypress value=%x, type=%x, code=%x\n", data.value, data.type, data.code);
          }
        //   else
        //   {
        //       // Nothing read
        //       sleep(1);
        //   }


        // Draw paddle
        for(int i = 0; i < 6; i++)
        {
            drawPixel(1, paddle[i], banana, true);
        }

        // Draw compPaddle
        for(int i = 0; i < 6; i++)
        {
            drawPixel(46, compPaddle[i], banana, true);
        }

        if(data.value == 0x11)
        {
            if(paddle[0] != Y_MIN)
            {
                for(int i = 0; i < 6; i++)
                {
                    paddle[i]--;
                }
                drawPixel(1, paddle[0], banana, true);
                drawPixel(1, paddle[5] + 1, banana, false);
            }
        }
        else if(data.value == 0x1f)
        {
            if(paddle[5] != Y_MAX)
            {
                for(int i = 0; i < 6; i++)
                {
                    paddle[i]++;
                }
                drawPixel(1, paddle[0] - 1, banana, false);
                drawPixel(1, paddle[5], banana, true);
            }
        }

        // Draw Scores
        drawScore(playerScore, true, banana);
        drawScore(compScore, false, banana);

        // Draw Ball
        counter++;
        if(counter == 25)
        {
            counter = 0;
            moveBall();
            drawPixel(lastX , lastY, banana, false);
            drawPixel(curX , curY, banana, true);
        }

        // Draw Player Line
        for(int i = 0; i < 18; i++)
        {
            banana[i][0].b = true;
            banana[i][0].c = true;
        }

        // Draw Computer Line
        for(int i = 0; i < 18; i++)
        {
            banana[i][47].e = true;
            banana[i][47].f = true;
        }

        // Draw Meridian Line
        for(int i = 1; i < 18; i++)
        {
            banana[i][24].f = true;
            // banana[i][47].f = true;
        }
        
        updateScreen(banana);
        // usleep(5000);
    }

    

    // endwin();

    return 0;
}