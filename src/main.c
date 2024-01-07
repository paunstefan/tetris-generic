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
  bool rotate_latch = false;
  bool move_latch = false;
  uint32_t move_debounce = 0;

  uint32_t game_steps = 20;
  uint32_t remaining_steps = game_steps;

  while(1){
    // Input handling
    generic_get_key(&keys);

    // Game logic
    bool moved = check_move(&keys, &current_piece, &move_latch);
    if(moved){
      move_debounce = 3;
    }

    check_rotate(&keys, &current_piece, &rotate_latch);


    // Display
    render_board();
    render_piece(&current_piece);
    generic_draw_frame();

    // Timing
    if(move_debounce > 0){
      move_debounce--;
    }
    else{
      move_latch = false;
    }

    remaining_steps--;
    if(remaining_steps == 0){
      game_step(&current_piece);
      remaining_steps = game_steps;
    }
    generic_sleepms(50);
  }
  return 0;
}