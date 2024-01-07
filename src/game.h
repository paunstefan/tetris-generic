#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>
#include "generic.h"

#define FIELD_HEIGHT 20
#define FIELD_WIDTH 10

_Static_assert(FIELD_WIDTH >= 8, "Min FIELD_WIDTH is 8");
_Static_assert(FIELD_HEIGHT >= 12, "Min FIELD_HEIGHT is 12");

_Static_assert(FIELD_WIDTH <= 15, "Max FIELD_WIDTH is 15");
_Static_assert(FIELD_HEIGHT <= 30, "Max FIELD_HEIGHT is 30");

typedef struct {
    int8_t piece;
    int8_t x;
    int8_t y;
    uint8_t rotation;
    uint8_t color_id;
} piece_state;

extern piece_state current_piece;
extern uint8_t tetrominos[7][16];
extern uint8_t playfield[FIELD_HEIGHT][FIELD_WIDTH];

void game_step(piece_state *const piece);
bool check_move(const key_map *const keys, piece_state *const piece, bool *const latch);
void check_rotate(const key_map *const keys, piece_state *const piece, bool *const latch);
#endif