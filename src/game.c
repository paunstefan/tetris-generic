#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "display.h"
#include "generic.h"
#include "stdbool.h"

uint8_t playfield[FIELD_HEIGHT][FIELD_WIDTH] = {0};

piece_state current_piece = {0};
uint32_t total_lines = 0;

tetromino tetrominos[7] = {
    {{0,0,0,0,
                1,1,1,1,
                0,0,0,0,
               0,0,0,0}, 4, 4}, // I
    
    {{0,1,0,
                0,1,0,
                1,1,0,
        0,0,0, 0,0,0,0}, 3, 5}, // J

    {{1,0,0,
                1,0,0,
                1,1,0,
        0,0,0,0,0,0,0}, 3, 3}, // L
    
    {{0,1,0,
                1,1,1,
                0,0,0,
        0,0,0,0,0,0,0}, 3, 7}, // T

    {{1,1,
                1,1,
        0,0,0,0,0,
        0,0,0,0,0,0,0}, 2, 6}, // O
    
    {{1,1,0,
                0,1,1,
                0,0,0,
        0,0,0,0,0,0,0}, 3,1}, // Z

    {{0,1,1,
                1,1,0,
                0,0,0,
        0,0,0,0,0,0,0}, 3, 2} // S
};

static bool check_collision(const piece_state *const piece, int8_t px, int8_t py, int8_t rot){
    for (int8_t y = 0; y < tetrominos[piece->piece_id].diameter; y++) {
        for (int8_t x = 0; x < tetrominos[piece->piece_id].diameter; x++) {
            if (tetrominos[piece->piece_id].data[rotation_coords(x, y, rot, tetrominos[piece->piece_id].diameter)] == 1) {
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

void new_piece(){
    int8_t piece = generic_random() % 7;

    current_piece.piece_id = piece;
    current_piece.rotation = 0;
    current_piece.x = FIELD_WIDTH / 2 - 2;
    current_piece.y = 0;
}

static void check_full_line(const piece_state *const piece){
    uint32_t lines = 0;
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
            lines++;
            py++;
        }
    }
    total_lines += lines;
}

static void lock_piece(piece_state *const piece){
    for (int8_t y = 0; y < tetrominos[piece->piece_id].diameter; y++) {
        for (int8_t x = 0; x < tetrominos[piece->piece_id].diameter; x++) {
            if (tetrominos[piece->piece_id].data[rotation_coords(x, y, piece->rotation, tetrominos[piece->piece_id].diameter)] == 1) {
                playfield[y + piece->y][x + piece->x] = tetrominos[piece->piece_id].color_id; 
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
        }
    }
    else{
        *latch = false;
    }
    return ret;
}

void check_rotate_or_drop(const key_map *const keys, piece_state *const piece, bool *const latch){
    if(ISSET_BIT(*keys, X)){
        if(check_collision(piece, piece->x, piece->y, (piece->rotation + 1) % 4)&& !(*latch)){
            piece->rotation = (piece->rotation + 1) % 4;
            *latch = true;
        }   
    }else if(ISSET_BIT(*keys, Z)){
        if(check_collision(piece, piece->x, piece->y, piece->rotation == 0 ? 3 : piece->rotation - 1)&& !(*latch)){
            piece->rotation = piece->rotation == 0 ? 3 : piece->rotation - 1;
            *latch = true;
        }
    }
    else if(ISSET_BIT(*keys, UP)){
        if(!(*latch)){
            while(check_collision(piece, piece->x, piece->y + 1, piece->rotation)){
                piece->y += 1;
            }
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