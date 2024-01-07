#include "display.h"
#include "game.h"
#include "generic.h"
#include <assert.h>
#include <stdint.h>

static const uint32_t color_ids[4] = {BLACK, RED, GREEN, BLUE};

static const uint32_t cell_diameter =
    (SCREEN_HEIGHT - BORDER_DIAMETER * 2) / FIELD_HEIGHT;
static const uint32_t border_width =
    (cell_diameter * FIELD_WIDTH) + BORDER_DIAMETER * 2;
static const uint32_t border_x_start = (SCREEN_WIDTH / 2) - (border_width / 2);
static const uint32_t border_x_end = border_x_start + border_width;

static void draw_rect(uint32_t *buffer, uint32_t x, uint32_t y, uint32_t w,
                      uint32_t h, uint32_t color) {
  assert(x + w <= SCREEN_WIDTH);
  assert(y + h <= SCREEN_HEIGHT);

  for (uint32_t row = y; row < (y + h); row++) {
    for (uint32_t col = x; col < (x + w); col++) {
      buffer[row * SCREEN_WIDTH + col] = color;
    }
  }
}

static void draw_cell(uint32_t *buffer, int8_t x, int8_t y, uint8_t color_id) {
  static const uint32_t field_start_x = border_x_start + 10;
  static const uint32_t field_start_y = 10;

  draw_rect(buffer, field_start_x + cell_diameter * x,
            field_start_y + cell_diameter * y, cell_diameter, cell_diameter,
            color_ids[color_id]);
}

void init_game_screen() {

  // Game borders
  draw_rect(generic_screenbuffer, border_x_start, 0, border_width,
            BORDER_DIAMETER, VLIGHT_GREY);
  draw_rect(generic_screenbuffer, border_x_start,
            SCREEN_HEIGHT - BORDER_DIAMETER, border_width, BORDER_DIAMETER,
            VLIGHT_GREY);

  draw_rect(generic_screenbuffer, border_x_start, 0, BORDER_DIAMETER,
            SCREEN_HEIGHT, VLIGHT_GREY);
  draw_rect(generic_screenbuffer, border_x_end - BORDER_DIAMETER, 0,
            BORDER_DIAMETER, SCREEN_HEIGHT, VLIGHT_GREY);
}

int8_t rotation_coords(int8_t x, int8_t y, int8_t rot) {
  assert(rot >= 0);
  assert(rot <= 3);

  int8_t index = 0;

  switch (rot) {
  // 0 degrees
  case 0:
    index = y * 4 + x;
    break;
  // 90 degrees
  case 1:
    index = 12 + y - (x * 4);
    break;
  // 180 degrees
  case 2:
    index = 15 - (y * 4) - x;
    break;
  // 270 degrees
  case 3:
    index = 3 - y + (x * 4);
    break;
  }
  return index;
}

void render_piece(const piece_state *const piece) {
  for (int8_t y = 0; y < 4; y++) {
    for (int8_t x = 0; x < 4; x++) {
      if (tetrominos[piece->piece][rotation_coords(x, y, piece->rotation)] ==
          1) {
        draw_cell(generic_screenbuffer, piece->x + x, piece->y + y,
                  piece->color_id);
      }
    }
  }
}

void render_board() {
  for (int8_t y = 0; y < FIELD_HEIGHT; y++) {
    for (int8_t x = 0; x < FIELD_WIDTH; x++) {
        draw_cell(generic_screenbuffer, x, y, playfield[y][x]);
    }
  }
}