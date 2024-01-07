#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "display.h"
#include "generic.h"
#include "stdbool.h"

uint8_t playfield[FIELD_HEIGHT][FIELD_WIDTH] = {0};

piece_state current_piece = {3, 0, 0,0, 1};

uint8_t tetrominos[7][16] = {
    {0,0,1,0,
         0,0,1,0,
         0,0,1,0,
        0,0,1,0},
    
    {0,0,0,0,
         0,0,1,0,
         0,0,1,0,
        0,1,1,0},

    {0,0,0,0,
         0,1,0,0,
         0,1,0,0,
        0,1,1,0},
    
    {0,0,0,0,
         0,0,0,0,
         0,0,1,0,
        0,1,1,1},

    {0,0,0,0,
         0,0,0,0,
         0,1,1,0,
        0,1,1,0},
    
    {0,0,0,0,
         0,0,0,0,
         0,1,1,0,
        0,0,1,1},

    {0,0,0,0,
         0,0,0,0,
         0,0,1,1,
        0,1,1,0},
};

static bool check_collision(const piece_state *const piece, int8_t px, int8_t py, int8_t rot){
    for (int8_t y = 0; y < 4; y++) {
        for (int8_t x = 0; x < 4; x++) {
            if (tetrominos[piece->piece][rotation_coords(x, y, rot)] == 1) {
                // Borders collision
                if(x + px < 0 || x + px >= FIELD_WIDTH){
                    return false;
                }
                if(y + py >= FIELD_HEIGHT){
                    return false;
                }

                // Piece collision
                if(playfield[y + py][x + px] != 0){
                    return false;
                }
          }
        }
    }
    return true;
}

static void new_piece(){
    int8_t piece = generic_random() % 7;

    current_piece.piece = piece;
    current_piece.rotation = 0;
    current_piece.x = 0;
    current_piece.y = 0;
    current_piece.color_id = 1;
}

static void check_full_line(const piece_state *const piece){
    for(int8_t py = piece->y + 3; py >= piece->y; py--){
        bool full = true;
        for(int8_t cols = 0; cols < FIELD_WIDTH; cols++){
            if(playfield[py][cols] == 0){
                full = false;
            }
        }

        if(full){
            for(int8_t y = py; y > 0; y--){
                memcpy(playfield[y], playfield[y-1], FIELD_WIDTH);
            }
            py++;
        }
    }
}

static void lock_piece(piece_state *const piece){
    for (int8_t y = 0; y < 4; y++) {
        for (int8_t x = 0; x < 4; x++) {
            if (tetrominos[piece->piece][rotation_coords(x, y, piece->rotation)] == 1) {
                playfield[y + piece->y][x + piece->x] = piece->color_id; 
            }
        }
    }
    check_full_line(piece);
    new_piece();
}

bool check_move(const key_map *const keys, piece_state *const piece, bool *const latch){
    bool ret = false;
    if(ISSET_BIT(*keys, LEFT)){
        if(check_collision(piece, piece->x - 1, piece->y, piece->rotation) && !(*latch)){
            piece->x -= 1;
            *latch = true;
            ret = true;
        }
    }
    else if(ISSET_BIT(*keys, RIGHT)){
        if(check_collision(piece, piece->x + 1, piece->y, piece->rotation) && !(*latch)){
            piece->x += 1;
            *latch = true;
            ret = true;
        }
    }
    else if(ISSET_BIT(*keys, DOWN)){
        if(check_collision(piece, piece->x, piece->y + 1, piece->rotation)){
            if(!(*latch)){
                piece->y += 1;
                *latch = true;
                ret = true;
            }
        }else{
            lock_piece(piece);
        }
    }
    else{
        *latch = false;
    }
    return ret;
}

void check_rotate(const key_map *const keys, piece_state *const piece, bool *const latch){
    if(ISSET_BIT(*keys, Z)){
        if(check_collision(piece, piece->x, piece->y, (piece->rotation + 1) % 4)&& !(*latch)){
            piece->rotation = (piece->rotation + 1) % 4;
            *latch = true;
        }   
    }else if(ISSET_BIT(*keys, X)){
        if(check_collision(piece, piece->x, piece->y, piece->rotation == 0 ? 3 : piece->rotation - 1)&& !(*latch)){
            piece->rotation = piece->rotation == 0 ? 3 : piece->rotation - 1;
            *latch = true;
        }
    }
    else{
        *latch = false;
    }
}

void game_step(piece_state *const piece) {
    if(check_collision(piece, piece->x, piece->y + 1, piece->rotation)){
        piece->y += 1;
    }else{
        lock_piece(piece);
    }
}