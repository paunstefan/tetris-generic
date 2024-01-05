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

/**
 * @brief One time initialization to be done at the start of the program.
 * 
 * @return int 0 on success
 */
int generic_init();

/**
 * @brief Render a frame to the screen. Framebuffer is held in the `generic_screenbuffer` array.
 * 
 */
void generic_draw_frame();

/**
 * @brief Sleep for a number of milliseconds.
 * 
 * @param ms Time to sleep.
 */
void generic_sleepms(const uint32_t ms);

/**
 * @brief Get the current time in milliseconds. It just has to be monotonic.
 * 
 * @return uint32_t Current time value.
 */
uint32_t generic_get_time();

/**
 * @brief Get the currently pressed keys.
 * 
 * @param pressed Bitmap of the keys. Each bit's meaning can be found in the `BUTTONS` enum.
 */
void generic_get_key(key_map *pressed);

/**
 * @brief Generate a random number to be used for choosing the next pieces.
 * 
 * @return int32_t
 */
int32_t generic_random();

#endif