/*
 * Main file for the whole OS
 */

#include "../drivers/screen.h"

void kmain() {
  clear_screen();
  kprint("Welcome to ChisaiOS\n");
  kprint(">");
}
