#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"

#define BORDER_DIAMETER 10

typedef enum {
  BLACK = 0xFF000000,
  WHITE = 0xFFFFFFFF,
  VLIGHT_GREY = 0xFFDDDDDD,
  RED = 0xFFFF0000,
  GREEN = 0xFF00FF00,
  BLUE = 0xFF0000FF,
  AQUA = 0xFF00FFFF,
  ORANGE = 0xFFFF9900,
  YELLOW = 0xFFFFFF00,
  PURPLE = 0xFFCC00CC,
} COLORS;

void init_game_screen();
int8_t rotation_coords(int8_t x, int8_t y, int8_t rot, uint8_t diam);
void render_piece(const piece_state *const piece);
void render_board();

#endif