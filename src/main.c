#include "generic.h"

#include <stdio.h>

uint32_t generic_screenbuffer[SCREEN_WIDTH * SCREEN_HEIGHT] = {0};

int main(int argc, char **argv) {
  printf("Tetris Generic\n");
  printf("Initializing\n");
  generic_init();

  while(1){
    generic_draw_frame();

    generic_sleepms(30);
  }
  return 0;
}