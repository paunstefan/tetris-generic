#ifndef GENERIC_H
#define GENERIC_H

#include <stdint.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef uint8_t key_map;

extern uint32_t generic_screenbuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

#define SET_BIT(var, bit) (var |= (uint8_t)1 << (bit))
#define UNSET_BIT(var, bit) (var &= ~((uint8_t)1 << (bit)))
#define ISSET_BIT(var, bit) (((var) & (bit)) != 0)

typedef enum {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    Z = 4,
    X = 5
} BUTTONS;

int generic_init();
void generic_draw_frame();
void generic_sleepms(uint32_t ms);
uint32_t generic_get_time();
void generic_get_key(key_map *pressed);

#endif