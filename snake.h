#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <stdint.h>
#include <unistd.h>
#include <linux/input.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include "ssdd_display.h"

#define SNAKE_W_KEY_VAL 0x7001a //0x11
#define SNAKE_Q_KEY_VAL 0x70014 // ?
#define SNAKE_S_KEY_VAL 0x70016 //0x1F
#define SNAKE_D_KEY_VAL 0x00000
#define SNAKE_A_KEY_VAL 0x00000

typedef struct Coordinate {
    uint8_t x;
    uint8_t y;
} xy;


static int fd, bytes;
struct input_event data;

static bool snakeUp = false;
static bool snakeDown = false;
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