#include "font.h"
#include "game.h"
#include <stdio.h>

Font font;

void fontInit(SDL_Renderer* renderer, const char* path){
	TTF_Init();
	font.font = TTF_OpenFont(path, 24);
	if(font.font == NULL){
		fprintf(stderr, "failed %s\n", TTF_GetError());
	}
	font.color = (SDL_Color){255,255,255,255};
	
	font.recti.x = 40;
	font.recti.y = 5;
	font.recti.w = 120;
	font.recti.h = 48;

	font.rectai.x = 640;
	font.rectai.y = 5;
	font.rectai.w = 120;
	font.rectai.h = 48;
}

void fontRender(SDL_Renderer* renderer){
	snprintf(font.scorei, sizeof(font.scorei), "Score: %d", game.scorei);
	snprintf(font.scoreai, sizeof(font.scoreai), "Score: %d", game.scoreai);

	font.surfacei = TTF_RenderText_Solid(font.font, font.scorei, font.color);
	font.texturei = SDL_CreateTextureFromSurface(renderer, font.surfacei);
	font.surfaceai = TTF_RenderText_Solid(font.font, font.scoreai, font.color);
	font.textureai = SDL_CreateTextureFromSurface(renderer, font.surfaceai);
	
	SDL_RenderCopy(renderer, font.textureai, NULL, &font.rectai);
	SDL_RenderCopy(renderer, font.texturei, NULL, &font.recti);
}

void fontClean(){
	SDL_FreeSurface(font.surfacei);
	SDL_FreeSurface(font.surfaceai);
	SDL_DestroyTexture(font.texturei);
	SDL_DestroyTexture(font.textureai);
	TTF_CloseFont(font.font);
	TTF_Quit();
}
