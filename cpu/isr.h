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

extern void isr0(), isr1(), isr2(), isr3(), isr4(), isr5(), isr6(), isr7(),
    isr8(), isr9(), isr10(), isr11(), isr12(), isr13(), isr14(), isr15(),
    isr16(), isr17(), isr18(), isr19(), isr20(), isr21(), isr22(), isr23(),
    isr24(), isr25(), isr26(), isr27(), isr28(), isr29(), isr30(), isr31();

extern void irq0(), irq1(), irq2(), irq3(), irq4(), irq5(), irq6(), irq7(),
    irq8(), irq9(), irq10(), irq11(), irq12(), irq13(), irq14(), irq15();

#define IRQ0 32

// function that takes in a register as parameter
typedef void (*isr_t)(registers_t);
void register_interrupt_handler(uint8_t n, isr_t handler);

#endif
