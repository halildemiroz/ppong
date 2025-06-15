#include "menu.h"
#include "game.h"
#include <stdio.h>
#include "racket.h"
#include "ball.h"
#include "ai.h"

Menu menu;

void renderStartMenu(const char *fontPath, SDL_Renderer *renderer){
	TTF_Init();
	
	menu.font = TTF_OpenFont(fontPath, 24);
	SDL_Color white = {255,255,255,255};

	SDL_Surface* startButtonSurface = TTF_RenderText_Solid(menu.font, "Start", white);
	SDL_Texture* startButton = SDL_CreateTextureFromSurface(renderer, startButtonSurface);

	menu.startButtonRect.x = 300;
	menu.startButtonRect.y = 225;
	menu.startButtonRect.w = 200;
	menu.startButtonRect.h = 150;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &menu.startButtonRect);

	SDL_RenderCopy(renderer, startButton, NULL, &menu.startButtonRect);

	SDL_FreeSurface(startButtonSurface);
	SDL_DestroyTexture(startButton);
	TTF_CloseFont(menu.font);
	
}

void renderGameMenu(const char *fontPath, SDL_Renderer *renderer){
	TTF_Init();
	
	menu.font = TTF_OpenFont(fontPath, 24);
	SDL_Color white = {255,255,255,255};

	char scoreTextP1[50];
	snprintf(scoreTextP1, sizeof(scoreTextP1), "Score: %d", game.scorei);

	char scoreTextCPU[50];
	snprintf(scoreTextCPU, sizeof(scoreTextCPU), "Score: %d", game.scoreai);

	SDL_Surface* scoreTextP1Surface = TTF_RenderText_Solid(menu.font, scoreTextP1, white);
	SDL_Surface* scoreTextCPUSurface = TTF_RenderText_Solid(menu.font, scoreTextCPU, white);

	SDL_Texture* scoreTextureP1 = SDL_CreateTextureFromSurface(renderer, scoreTextP1Surface);
	SDL_Texture* scoreTextureCPU = SDL_CreateTextureFromSurface(renderer, scoreTextCPUSurface);

	menu.scoreP1Rect.x = 40;
	menu.scoreP1Rect.y = 5;
	menu.scoreP1Rect.w = 120;
	menu.scoreP1Rect.h = 48;

	menu.scoreCPURect.x = 640;
	menu.scoreCPURect.y = 5;
	menu.scoreCPURect.w = 120;
	menu.scoreCPURect.h = 48;
	
	SDL_RenderCopy(renderer, scoreTextureP1, NULL, &menu.scoreP1Rect);
	SDL_RenderCopy(renderer, scoreTextureCPU, NULL, &menu.scoreCPURect);

	// Burada diğer şeyleri renderlicaz
	ballRender(game.grenderer, ball.x, ball.y, ball.radius);
	racketRender(game.grenderer);
	aiRender();	
	// -------
	
	SDL_FreeSurface(scoreTextCPUSurface);
	SDL_FreeSurface(scoreTextP1Surface);
	SDL_DestroyTexture(scoreTextureP1);
	SDL_DestroyTexture(scoreTextureCPU);
	TTF_CloseFont(menu.font);
}
