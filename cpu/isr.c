#include "isr.h"
#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../utils/types.h"

isr_t interrupt_handlers[256];

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs) { kprint("Recieved interrupt\n"); }

void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers[n] = handler;
}

void irq_handler(registers_t regs) {
  // Send an EOI (end of interrupt) signal to the PICs.
  // If this interrupt involved the slave.
  if (regs.int_no >= 40)
    port_byte_out(0xA0, 0x20); // slave
  port_byte_out(0x20, 0x20);   // master

  // handle interrupt based on interrupt_handlers
  if (interrupt_handlers[regs.int_no] != 0) {
    isr_t handler = interrupt_handlers[regs.int_no];
    handler(regs);
  }
}
