#include "screen.h"
#include "../utils/types.h"
#include "ports.h"

/* Screen UI and stuff */

// Private function

int get_screen_offset(int row, int col);
int get_cursor_offset();
void set_cursor_offset(int offset);
int handle_scrolling(int offset);

int get_offset_row(int offset) { return offset / (2 * MAX_COL); }
int get_offset_col(int offset) {
  return (offset - (get_offset_row(offset) * 2 * MAX_COL)) / 2;
}

int print_char(char c, int row, int col, uint8_t attribute_byte) {
  uint8_t *vidmem = (uint8_t *)VIDEO_ADDRESS;

  if (!attribute_byte) {
    attribute_byte = WHITE_ON_BLACK;
  }

  int offset;
  if (row >= 0 && col >= 0) {
    offset = get_screen_offset(row, col);
  } else {
    offset = get_cursor_offset();
  }

  if (c == '\n') {
    int row = get_offset_row(offset);
    offset = get_screen_offset(row + 1, 0);
  } else {
    vidmem[offset] = c;
    vidmem[offset + 1] = attribute_byte;
    offset += 2;
  }

  offset = handle_scrolling(offset);

  set_cursor_offset(offset);
  return offset;
}

void memory_copy(char *src, char *dst, int n) {
  for (int i = 0; i < n; i++) {
    *(dst + i) = *(src + i);
  }
}

int handle_scrolling(int offset) {
  if (offset < MAX_ROW * MAX_COL * 2) {
    return offset;
  }

  // copy to prev row
  for (int i = 1; i < MAX_ROW; i++) {
    memory_copy((char *)VIDEO_ADDRESS + get_screen_offset(i, 0),
                (char *)VIDEO_ADDRESS + get_screen_offset(i - 1, 0), MAX_COL);
  }

  char *last_line = (char *)VIDEO_ADDRESS + get_screen_offset(MAX_ROW - 1, 0);
  for (int i = 0; i < 2 * MAX_COL; i++) {
    last_line[i] = 0;
  }

  offset -= 2 * MAX_COL;
  return offset;
}

int get_cursor_offset() {
  port_byte_out(REG_SCREEN_CTRL, 14);
  int offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);
  return offset * 2;
}
void set_cursor_offset(int offset) {
  offset /= 2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset & 0xff));
}

int get_screen_offset(int row, int col) { return 2 * (row * MAX_COL + col); }

// Public Functions
void clear_screen() {
  int screen_size = MAX_COL * MAX_ROW;
  int i;
  uint8_t *screen = (uint8_t *)VIDEO_ADDRESS;

  for (i = 0; i < screen_size; i++) {
    screen[i * 2] = ' ';
    screen[i * 2 + 1] = WHITE_ON_BLACK;
  }
  set_cursor_offset(get_screen_offset(0, 0));
}

void kprint_at(char *str, int row, int col) {
  int offset;
  if (row >= 0 && col >= 0)
    offset = get_screen_offset(row, col);
  else {
    offset = get_cursor_offset();
    row = get_offset_row(offset), col = get_offset_col(offset);
  }

  /* Loop through message and print it */
  int i = 0;
  while (str[i] != 0) {
    offset = print_char(str[i++], row, col, WHITE_ON_BLACK);
    /* Compute row/col for next iteration */
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }
}

void kprint(char *message) { kprint_at(message, -1, -1); }
