#include "game.h"
#include "racket.h"

#define MAX_SPEED 10.0f
#define ACCELERATION 0.5f

Racket racket;

void racketInit(){
	racket.width = 7;
	racket.height = 100;
	racket.x = 20;
	racket.y = 20;
	racket.speed = 5;

	printf("Racket initialized\n");
}

void racketRender(SDL_Renderer *renderer){
	SDL_SetRenderDrawColor(renderer, 255,255,255,255);
	SDL_Rect racketRect = {racket.x, racket.y, racket.width, racket.height};
	SDL_RenderFillRect(renderer, &racketRect);
}

void racketMove() {
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_W] && racket.y >= 20) {
        racket.y -= racket.speed;
    }
    if (keystate[SDL_SCANCODE_S] && racket.y <= 580 - racket.height) {
        racket.y += racket.speed;
    }
}

