#ifndef __PONG_H__
#define __PONG_H__

#include <stdint.h>
#include <unistd.h>
#include <linux/input.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#include "ssdd_display.h"

#define Y_MIN 3
#define Y_MAX 35
#define X_MIN 0
#define X_MAX 47
#define W_KEY_VAL 0x7001a //0x11
#define Q_KEY_VAL 0x70014 // ?
#define S_KEY_VAL 0x70016 //0x1F
#define INPUT_EVENT "/dev/input/event3"
#define GAME_SPEED 25
#define PADDLE_COUNTER_LIMIT 35

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

static digit banana[18][48];

static uint8_t paddle[6] = {15, 16, 17, 18, 19, 20};
static uint8_t compPaddle[6] = {16, 17, 18, 19, 20, 21};

static int fd, bytes;
struct input_event data;

static uint8_t counter = 0;
static uint8_t paddleCounter = 0;

void initPongScreen();
int pong();

#endif