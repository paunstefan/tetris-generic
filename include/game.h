#ifndef GAME_H
#define GAME_H

#include "generic.h"
#include <stdbool.h>
#include <stdint.h>

#define FIELD_HEIGHT 20
#define FIELD_WIDTH 10

_Static_assert(FIELD_WIDTH >= 8, "Min FIELD_WIDTH is 8");
_Static_assert(FIELD_HEIGHT >= 12, "Min FIELD_HEIGHT is 12");

_Static_assert(FIELD_WIDTH <= 15, "Max FIELD_WIDTH is 15");
_Static_assert(FIELD_HEIGHT <= 30, "Max FIELD_HEIGHT is 30");

typedef struct {
  int8_t piece_id;
  int8_t x;
  int8_t y;
  uint8_t rotation;
} piece_state;

typedef struct {
  uint8_t data[16];
  uint8_t diameter;
  uint8_t color_id;
} tetromino;

extern piece_state current_piece;
extern tetromino tetrominos[7];
extern uint8_t playfield[FIELD_HEIGHT][FIELD_WIDTH];
extern uint32_t total_lines;

void new_piece();
void game_step(piece_state *const piece);
bool check_move(const key_map *const keys, piece_state *const piece,
                bool *const latch);
void check_rotate_or_drop(const key_map *const keys, piece_state *const piece,
                          bool *const latch);
#endif