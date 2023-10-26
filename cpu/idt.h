#ifndef IDT_H
#define IDT_H

#include "../utils/types.h"

struct idt_entry_struct {
  uint16_t base_lo; // The lower 16 bits of the address to jump to when this
                    // interrupt fires.
  uint16_t sel;     // Kernel segment selector.
  uint8_t always0;  // This must always be zero.
  uint8_t flags;    // More flags. See documentation.
  uint16_t base_hi; // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct {
  uint16_t limit;
  uint16_t base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

extern void isr0(), isr1();

#endif