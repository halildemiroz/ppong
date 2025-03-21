#include "game.h"
#include "racket.h"
#include "ball.h"
#include "ai.h"

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
	game.score = 0;
}

void gameRender(){
	SDL_RenderClear(game.grenderer);
	// Render stuff
	ballRender(game.grenderer, ball.x, ball.y, ball.radius);
	racketRender();
	aiRender();

	SDL_SetRenderDrawColor(game.grenderer, 0, 0, 0, 255);
	SDL_RenderPresent(game.grenderer);
}
// topun ve raketin updatei için
void gameUpdate(){
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
}

void gameClean(){
	SDL_DestroyWindow(game.gwindow);
	SDL_DestroyRenderer(game.grenderer);
	SDL_Quit();
	printf("Game cleaned\n");
}

