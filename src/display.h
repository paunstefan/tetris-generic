#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"

#define BORDER_DIAMETER 10

void init_game_screen();
void render_piece(const piece_state *const piece);

#endif