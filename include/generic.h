#ifndef GENERIC_H
#define GENERIC_H

#include <stdint.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

extern uint32_t generic_screenbuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

int generic_init();
void generic_draw_frame();
void generic_sleepms(uint32_t ms);
uint32_t generic_get_time();
int generic_get_key(uint8_t *pressed);

#endif