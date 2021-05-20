#ifndef __SSDD_DISPLAY_H__
#define __SSDD_DISPLAY_H__

#include <stdint.h>
#include <stdbool.h>
#include <ncurses.h>

typedef struct Digit {
    bool a ;
    bool b ;
    bool c ;
    bool d ;
    bool e ;
    bool f ;
    bool g ;
    bool dp ;
} digit;

void initScreen();

void updateScreen(digit screen[18][48]);

int drawPixel(uint8_t x, uint8_t y, digit screen[18][48], bool enable);

digit drawNum(int num);

#endif