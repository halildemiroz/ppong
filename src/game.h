#pragma once
#include "racket.h"

typedef enum{
	START = 0,
	GAME = 1
} GameState;

typedef struct {
	SDL_Window* gwindow;
	SDL_Renderer* grenderer;
	bool isrunning;
	int scorei;
	int scoreai;
	int mbx, mby;
	GameState gameState;
} Game;

extern Game game;

void gameInit(const char* title, int width, int height, bool isfullscreen);

void gameUpdate();

void gameRender();

void gameHandleEvents();

void gameClean();

