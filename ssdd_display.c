#include "ssdd_display.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void initScreen() 
{
    initscr();
    noecho();
    curs_set(FALSE);
}

void updateScreen(digit screen[18][48])
{

    // clear();

    char screenbuff[10410];

    screenbuff[0] = '\0';

    for(uint8_t i = 0; i < 18; i ++)
    {
        for(uint8_t l = 0; l < 3; l++)
        {
            for(uint8_t j = 0; j < 48; j++)
            {
                if(l == 0){
                    // printf(" ");
                    sprintf(screenbuff, "%s ", screenbuff);
                    // (screen[i][j].a) ? printf("_") : printf(" ");
                    (screen[i][j].a) ? sprintf(screenbuff, "%s_", screenbuff) : sprintf(screenbuff, "%s ", screenbuff);
                    // printf("  ");
                    sprintf(screenbuff, "%s  ", screenbuff);
                }

                if(l == 1){
                    // screen[i][j].f ? printf("|") : printf(" ");
                    screen[i][j].f ? sprintf(screenbuff, "%s|", screenbuff) : sprintf(screenbuff, "%s ", screenbuff);
                    // screen[i][j].g ? printf("_") : printf(" ");
                    screen[i][j].g ? sprintf(screenbuff, "%s_", screenbuff) : sprintf(screenbuff, "%s ", screenbuff);
                    // screen[i][j].b ? printf("|") : printf(" ");
                    screen[i][j].b ? sprintf(screenbuff, "%s|", screenbuff) : sprintf(screenbuff, "%s ", screenbuff);
                    // printf(" ");
                    sprintf(screenbuff, "%s ", screenbuff);
                }

                if(l == 2){
                    // screen[i][j].e ? printf("|") : printf(" ");
                    screen[i][j].e ? sprintf(screenbuff, "%s|", screenbuff) : sprintf(screenbuff, "%s ", screenbuff);
                    // screen[i][j].d ? printf("_") : printf(" ");
                    screen[i][j].d ? sprintf(screenbuff, "%s_", screenbuff) : sprintf(screenbuff, "%s ", screenbuff);
                    // screen[i][j].c ? printf("|") : printf(" ");
                    screen[i][j].c ? sprintf(screenbuff, "%s|", screenbuff) : sprintf(screenbuff, "%s ", screenbuff);
                    // screen[i][j].dp ? printf(".") : printf(" ");
                    screen[i][j].dp ? sprintf(screenbuff, "%s.", screenbuff) : sprintf(screenbuff, "%s ", screenbuff);
                }
                // if(j == 47) printf("\n");
                if(j == 47) sprintf(screenbuff, "%s\n", screenbuff);
            }
        }
    }

    sprintf(screenbuff, "%s%c", screenbuff , '\0');

    mvprintw(0,0, screenbuff);
    refresh();
}

int drawPixel(uint8_t x, uint8_t y, digit screen[18][48], bool enable) 
{
    if(x >= 48 || x < 0 || y >= 36 || y < 0) return -1;

    if (y % 2)
    {
        screen[y / 2][x].c = enable;
        screen[y / 2][x].d = enable;
        screen[y / 2][x].e = enable; 
        screen[y / 2][x].g = enable;
        // if(!screen[y / 2][x].g && !enable)
        // {

        // }
    }
    else
    {
        screen[y / 2][x].a = enable;
        screen[y / 2][x].b = enable;
        screen[y / 2][x].f = enable; 
        screen[y / 2][x].g = enable;
    }

     

    return 0;
    
}

digit drawNum(int num)
{
    digit val = { .a=false, 
                  .b=false, 
                  .c=false, 
                  .d=false, 
                  .e=false, 
                  .f=false, 
                  .g=false, 
                  .dp=false 
                };
    switch(num)
    {
        case 0:
            val.a = true;
            val.b = true;
            val.c = true;
            val.d = true;
            val.e = true;
            val.f = true;
            break;
        case 1:
            val.b = true;
            val.c = true;
            break;
        case 2:
            val.a = true;
            val.b = true;
            val.d = true;
            val.e = true;
            val.g = true;
            break;
        case 3:
            val.a = true;
            val.b = true;
            val.c = true;
            val.d = true;
            val.g = true;
            break;
        case 4:
            val.b = true;
            val.c = true;
            val.f = true;
            val.g = true;
            break;
        case 5:
            val.a = true;
            val.c = true;
            val.d = true;
            val.f = true;
            val.g = true;
            break;
        case 6:
            val.a = true;
            val.c = true;
            val.d = true;
            val.e = true;
            val.f = true;
            val.g = true;
            break;
        case 7:
            val.a = true;
            val.b = true;
            val.c = true;
            break;
        case 8:
            val.a = true;
            val.b = true;
            val.c = true;
            val.d = true;
            val.e = true;
            val.f = true;
            val.g = true;
            break;
        case 9:
            val.a = true;
            val.b = true;
            val.c = true;
            val.d = true;
            val.f = true;
            val.g = true;
            break;
        case 'a':
            val.a = true;
            val.b = true;
            val.c = true;
            val.e = true;
            val.f = true;
            val.g = true;
            break;
        case 'b':
            val.c = true;
            val.d = true;
            val.e = true;
            val.f = true;
            val.g = true;
            break;
        case 'c':
            val.a = true;
            val.d = true;
            val.e = true;
            val.f = true;
            break;
        case 'd':
            val.b = true;
            val.c = true;
            val.d = true;
            val.e = true;
            val.g = true;
            break;
        case 'e':
            val.a = true;
            val.d = true;
            val.e = true;
            val.f = true;
            val.g = true;
            break;
        case 'f':
            val.a = true;
            val.e = true;
            val.f = true;
            val.g = true;
            break;
        case 'g':
            val.a = true;
            val.b = true;
            val.c = true;
            val.d = true;
            val.f = true;
            val.g = true;
            break;
        case 'h':
            val.b = true;
            val.c = true;
            val.e = true;
            val.f = true;
            val.g = true;
            break;
        case 'i':
            val.b = true;
            val.c = true;
            break;
        case 'j':
            val.b = true;
            val.c = true;
            val.d = true;
            break;
        case 'k':
            val.a = true;
            val.c = true;
            val.e = true;
            val.f = true;
            val.g = true;
            break;
        case 'l':
            val.d = true;
            val.e = true;
            val.f = true;
            break;
        case 'm':
            val.a = true;
            val.c = true;
            val.e = true;
            break;
        case 'n':
            val.a = true;
            val.b = true;
            val.c = true;
            val.e = true;
            val.f = true;
            break;
        case 'o':
            val.c = true;
            val.d = true;
            val.e = true;
            val.g = true;
            break;
        case 'p':
            val.a = true;
            val.b = true;
            val.e = true;
            val.f = true;
            val.g = true;
            break;
        case 'q':
            val.a = true;
            val.b = true;
            val.c = true;
            val.f = true;
            val.g = true;
            break;
        case 'r':
            val.a = true;
            val.e = true;
            val.f = true;
            break;
        case 's':
            val.a = true;
            val.c = true;
            val.d = true;
            val.g = true;
            break;
        case 't':
            val.b = true;
            val.c = true;
            val.g = true;
            break;
        case 'u':
            val.b = true;
            val.c = true;
            val.d = true;
            val.e = true;
            val.f = true;
            break;
        case 'v':
            val.b = true;
            val.d = true;
            val.f = true;
            break;
        case 'w':
            val.a = true;
            val.b = true;
            val.c = true;
            val.d = true;
            val.e = true;
            val.f = true;
            val.g = true;
            break;
        case 'x':
            val.b = true;
            val.d = true;
            val.e = true;
            val.f = true;
            val.g = true;
            break;
        case 'y':
            val.b = true;
            val.c = true;
            val.d = true;
            val.f = true;
            val.g = true;
            break;
        case 'z':
            val.a = true;
            val.d = true;
            val.e = true;
            val.g = true;
            break;
                    
    }

    return val;
}