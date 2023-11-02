/*
 * Main file for the whole OS
 */

#include "../cpu/idt.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../drivers/timer.h"

void kmain() {
  clear_screen();

  kprint("Welcome to ChisaiOS\n");
  kprint("> ");

  // initialize interrupt table
  init_idt();
  // initialize timer
  init_timer(50);
  init_keyboard();
  __asm__ __volatile__("int $3");

  while (1)
    ;
}
