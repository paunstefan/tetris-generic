#include "generic.h"

#include <stdint.h>
#include <stdio.h>
#include "display.h"
#include "game.h"

uint32_t generic_screenbuffer[SCREEN_WIDTH * SCREEN_HEIGHT] = {0};


int main(int argc, char **argv) {
  printf("Tetris Generic\n");
  printf("Initializing\n");
  generic_init();
  init_game_screen();

  key_map keys = 0;

  while(1){
    // Input handling
    generic_get_key(&keys);

    // Game logic

    // Display
    render_piece(&current_piece);
    generic_draw_frame();

    // Timing
    generic_sleepms(50);
  }
  return 0;
}