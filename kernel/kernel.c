/*
 * Main file for the whole OS
 */

#include "../cpu/idt.h"
#include "../drivers/screen.h"

void kmain() {
  clear_screen();

  // initialize interrupt table
  init_idt();

  kprint("Welcome to ChisaiOS\n");
  kprint(">");

  __asm__ __volatile__("int $0x3");
}
