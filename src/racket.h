#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct{
	short width, height;
	int speed, x, y;
} Racket;

extern Racket racket;

//game init
void racketInit();
//game render
void racketRender();
//game update
void racketMove();

