#include "generic.h"

#include "display.h"
#include "game.h"
#include <stdint.h>
#include <stdio.h>

uint32_t generic_screenbuffer[SCREEN_WIDTH * SCREEN_HEIGHT] = {0};

int main(int argc, char **argv) {
  printf("Tetris Generic\n");
  printf("Initializing\n");
  generic_init();
  init_game_screen();

  key_map keys = 0;
  bool rotate_drop_latch = false;
  bool move_latch = false;
  uint32_t move_debounce = 0;

  uint32_t game_steps = 20;
  uint32_t remaining_steps = game_steps;
  new_piece();

  while (1) {
    // Input handling
    generic_get_key(&keys);

    // Game logic
    bool moved = check_move(&keys, &current_piece, &move_latch);
    if (moved) {
      move_debounce = 3;
    }

    check_rotate_or_drop(&keys, &current_piece, &rotate_drop_latch);

    if (move_debounce > 0) {
      move_debounce--;
    } else {
      move_latch = false;
    }

    remaining_steps--;
    if (remaining_steps == 0) {
      game_step(&current_piece);
      game_steps = 20 - (total_lines / 10) * 2;
      remaining_steps = game_steps;
    }

    // Display
    render_board();
    render_piece(&current_piece);
    generic_draw_frame();

    // Timing
    generic_sleepms(50);
  }
  return 0;
}