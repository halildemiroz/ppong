#include "ai.h"
#include "game.h"
#include "ball.h"

Ai ai;

void aiInit(){
	ai.width = 7;
	ai.height = 100;
	ai.x = 773;
	ai.y = 20;
	ai.speed = 8;
}

void aiRender(){
	SDL_SetRenderDrawColor(game.grenderer, 255,255,255,255);
	SDL_Rect aiRect = {ai.x, ai.y, ai.width, ai.height};
	SDL_RenderFillRect(game.grenderer, &aiRect);
}

void aiMove(){
	if(ball.x > 400){
	if(ball.y < ai.y + ai.height / 2 && ai.y >= 20){
		ai.y -= ai.speed;
	}
	if(ball.y > ai.y + ai.height / 2 && ai.y <= 580 - ai.height){
		ai.y += ai.speed;
	}
}}

