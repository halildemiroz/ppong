#pragma once

#include <SDL2/SDL.h>

typedef struct{
	int x,y;
	int width,height;
	int speed;
} Ai;
extern Ai ai;

void aiInit();

void aiRender();

void aiMove();

