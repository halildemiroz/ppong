#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window = SDL_CreateWindow("ppong",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);
    
    bool quit = false;
    SDL_Event event;
    while(!quit){
        while(SDL_PollEvent(&e){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
    }
}
