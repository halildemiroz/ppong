#ifndef BALL_H
#define BALL_H

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
float calculateSpeed(float vx, float vy);

#endif
/*
#pragma once

#include <SDL2/SDL.h>

typedef struct{
	int radius,x,y;
	int vx,vy;
} Ball;

extern Ball ball;

void ballInit();

void ballRender(SDL_Renderer* renderer, int x, int y, int radius);

void ballMove();

void ballCollisionRacket();

void ballCollisionAi();

void ballCollisionWall();

void ballResetPos();
*/
