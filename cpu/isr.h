#ifndef ISR_H
#define ISR_H

#include "../utils/types.h"

typedef struct registers {
  uint32_t ds;                                     // Data segment selector
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
  uint32_t int_no, err_code; // Interrupt number and error code (if applicable)
  uint32_t eip, cs, eflags, useresp,
      ss; // Pushed by the processor automatically.
} registers_t;

#define IRQ0 32
#define IRQ1 33

// function that takes in a register as parameter
typedef void (*isr_t)(registers_t);
void register_interrupt_handler(uint8_t n, isr_t handler);

#endif
