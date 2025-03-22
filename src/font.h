#pragma once

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct{
	const char* path;
	TTF_Font* font;

	SDL_Surface* surfacei;
	SDL_Surface* surfaceai;
	SDL_Texture* texturei;
	SDL_Texture* textureai;
	
	SDL_Rect recti;
	SDL_Rect rectai;
	SDL_Color color;
	

	char scorei[30];
	char scoreai[30];
} Font;

extern Font font;

void fontInit(SDL_Renderer* renderer, const char* path);

void fontRender(SDL_Renderer* renderer);

void fontClean();

