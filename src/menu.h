#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
	TTF_Font* font;
	SDL_Rect startButtonRect, scoreP1Rect, scoreCPURect; 
} Menu;
extern Menu menu;

void renderStartMenu(const char* fontPath, SDL_Renderer* renderer);
void renderGameMenu(const char* fontPath, SDL_Renderer* renderer);

