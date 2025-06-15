#include "game.h"
#include <stdio.h>

#define FPS 60
#define FRAME_DELAY (1000 / FPS)

int main(int argc, char* argv[]){
	gameInit("Ppong", 800, 600, false);

	unsigned int frameStart, frameTime;

	printf("hle");

	while(game.isrunning){
		frameStart = SDL_GetTicks();
		// Game functions
		gameUpdate();
		gameRender();
		gameHandleEvents();

		frameTime = SDL_GetTicks() - frameStart;
		if(FRAME_DELAY > frameTime){
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	// Clean up
	gameClean();
	return 0;
}
