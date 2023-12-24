#include "generic.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#define SDL_WIDTH 800
#define SDL_HEIGHT 600

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

int generic_init(){
	window = SDL_CreateWindow("Tetris-generic", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL_WIDTH, SDL_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == NULL){
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == NULL){
        SDL_DestroyWindow(window);
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
	}

	SDL_RenderSetLogicalSize(renderer, SDL_WIDTH, SDL_HEIGHT);

	texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);
    
    if(texture == NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
		printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
	}

    return 0;
}

void generic_draw_frame(){
    SDL_UpdateTexture(texture, NULL, generic_screenbuffer, SCREEN_WIDTH * sizeof(uint32_t));	

    SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

    SDL_Event event;
	bool done = false;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				done = true;
				break;
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ){
						case SDLK_LEFT:
							break;
						case SDLK_RIGHT:
							break;
						case SDLK_UP:
							break;
						case SDLK_DOWN:
							break;
						default:
							break;
				}
				break;
			case SDL_KEYUP:
				break;
			default:
				break;
		}
	}

	if(done){
		SDL_Quit();
		exit(0);
	}
}

void generic_sleepms(uint32_t ms){
    SDL_Delay(ms);
}

uint32_t generic_get_time(){
    return SDL_GetTicks();
}

int generic_get_key(uint8_t *pressed){
    return 0;
}