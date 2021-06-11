#ifndef __SNAKE_H__
#define __SNAKE_H__

// #include <stdint.h>
// #include <stdlib.h>
#include "ssdd_display.h"

#define SNAKE_W_KEY_VAL 0x7001a //0x11
#define SNAKE_Q_KEY_VAL 0x70014 // ?
#define SNAKE_S_KEY_VAL 0x70016 //0x1F
#define SNAKE_D_KEY_VAL 0x70007
#define SNAKE_A_KEY_VAL 0x70004

typedef struct Coordinate {
    uint8_t x;
    uint8_t y;
} xy;

static bool snakeUp = false;
static bool snakeDown = true;
static bool snakeLeft = false;
static bool snakeRight = false;

static uint8_t dotX;
static uint8_t dotY;

static digit banana[18][48];

static uint8_t score = 0;

static xy *snakePath;

void initSnakeScreen();
int snake();

#endif