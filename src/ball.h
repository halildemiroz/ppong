#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    float x;
    float y;
    float vx;
    float vy;
    int radius;
} Ball;

extern Ball ball;

void ballInit();
void ballRender(SDL_Renderer *renderer, int cx, int cy, int radius);
void ballMove();
void ballCollisionRacket();
void ballCollisionAi();
void ballResetPos();
void ballCollisionWall();
float calculateSpeed(int vx, int vy);


