#include "generic.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SDL_WIDTH 800
#define SDL_HEIGHT 600

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static uint8_t *sdl_keys = NULL;

int generic_init() {

  srand(time(NULL));

  window = SDL_CreateWindow("Tetris-generic", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SDL_WIDTH, SDL_HEIGHT,
                            SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == NULL) {
    SDL_DestroyWindow(window);
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_RenderSetLogicalSize(renderer, SDL_WIDTH, SDL_HEIGHT);

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH,
                              SCREEN_HEIGHT);

  if (texture == NULL) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  sdl_keys = SDL_GetKeyboardState(NULL);

  return 0;
}

void generic_draw_frame() {
  SDL_UpdateTexture(texture, NULL, generic_screenbuffer,
                    SCREEN_WIDTH * sizeof(uint32_t));

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void generic_sleepms(uint32_t ms) { SDL_Delay(ms); }

uint32_t generic_get_time() { return SDL_GetTicks(); }

void generic_get_key(key_map *keys) {
  bool done = false;

  SDL_PumpEvents();

  if (sdl_keys[SDL_SCANCODE_LEFT]) {
    SET_BIT(*keys, LEFT);
  } else {
    UNSET_BIT(*keys, LEFT);
  }

  if (sdl_keys[SDL_SCANCODE_RIGHT]) {
    SET_BIT(*keys, RIGHT);
  } else {
    UNSET_BIT(*keys, RIGHT);
  }

  if (sdl_keys[SDL_SCANCODE_UP]) {
    SET_BIT(*keys, UP);
  } else {
    UNSET_BIT(*keys, UP);
  }

  if (sdl_keys[SDL_SCANCODE_DOWN]) {
    SET_BIT(*keys, DOWN);
  } else {
    UNSET_BIT(*keys, DOWN);
  }

  if (sdl_keys[SDL_SCANCODE_Z]) {
    SET_BIT(*keys, Z);
  } else {
    UNSET_BIT(*keys, Z);
  }

  if (sdl_keys[SDL_SCANCODE_X]) {
    SET_BIT(*keys, X);
  } else {
    UNSET_BIT(*keys, X);
  }

  if (sdl_keys[SDL_SCANCODE_Q]) {
    done = true;
  }

  if (done) {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
  }
}

int32_t generic_random() { return rand(); }