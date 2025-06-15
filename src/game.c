#include "game.h"
#include "racket.h"
#include "ball.h"
#include "ai.h"
#include "menu.h"

Game game;

void gameInit(const char *title, int width, int height, bool isfullscreen){
	if(!SDL_Init(SDL_INIT_EVERYTHING))
		printf("SDL Initialized\n");
	
	if(isfullscreen){
		game.gwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FULLSCREEN);
	} else{
		game.gwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	}
	if(game.gwindow)
		printf("Window created\n");
	
	game.grenderer = SDL_CreateRenderer(game.gwindow, -1, 0);
	if(game.grenderer){
		SDL_SetRenderDrawColor(game.grenderer, 255, 255, 255, 255);
		printf("Renderer created\n");
	}

	racketInit();
	ballInit();
	aiInit();

	game.isrunning = true;
	game.scorei = 0;
	game.scoreai = 0;
	game.gameState = START;
}

void gameRender(){
	SDL_RenderClear(game.grenderer);

	switch (game.gameState) {
		case START:
			renderStartMenu("../assets/font3.ttf", game.grenderer);
			break;
		case GAME:
			renderGameMenu("../assets/font3.ttf", game.grenderer);
	}
	
	SDL_SetRenderDrawColor(game.grenderer, 0, 0, 0, 255);
	SDL_RenderPresent(game.grenderer);
}

void gameUpdate(){
	if(300 < game.mbx && game.mbx < 500 && 225 < game.mby && game.mby < 375)
		game.gameState = GAME;
	ballMove();
	aiMove();
}

void gameHandleEvents(){
	SDL_Event event;
	SDL_PollEvent(&event);

	racketMove();
	
	switch(event.type){
		case SDL_QUIT:
			game.isrunning = false;
			break;
		default:
			break;
	}
	switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&game.mbx, &game.mby);
			break;
	}
}

void gameClean(){
	SDL_DestroyWindow(game.gwindow);
	SDL_DestroyRenderer(game.grenderer);
	SDL_Quit();
	printf("Game cleaned\n");
}

