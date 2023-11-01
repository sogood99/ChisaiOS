/*
 * Main file for the whole OS
 */

#include "../cpu/idt.h"
#include "../drivers/screen.h"
#include "../drivers/timer.h"

void kmain() {
  clear_screen();

  // initialize interrupt table
  init_idt();

  // initialize timer
  init_timer(50);

  kprint("Welcome to ChisaiOS\n");
  kprint(">");

  // __asm__ __volatile__("int $32");
}
