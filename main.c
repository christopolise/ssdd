#include <stdio.h>
#include "pong.h"
#include "snake.h"

int main(int argc, char * argv[])
{
    
    initPongScreen();
    pong();

    // initSnakeScreen();
    // snake();

    printf("BANANA\n");

    return 0;
}