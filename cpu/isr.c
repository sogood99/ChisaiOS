#include "isr.h"
#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../utils/types.h"

isr_t interrupt_handlers[256];

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t *regs) {
  kprint("Recieved Interupt");
  char s[10];
  s[0] = regs->int_no / 10 + '0';
  s[1] = regs->int_no % 10 + '0';
  s[2] = ',';
  s[3] = regs->err_code / 10 + '0';
  s[4] = regs->err_code % 10 + '0';
  s[5] = '\n';
  s[6] = 0;
  kprint(s);
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers[n] = handler;
}

void irq_handler(registers_t *regs) {
  // Send an EOI (end of interrupt) signal to the PICs.
  // If this interrupt involved the slave. (32+16)
  if (regs->int_no >= 40)
    port_byte_out(0xA0, 0x20); // slave
  port_byte_out(0x20, 0x20);   // master

  // handle interrupt based on interrupt_handlers
  if (interrupt_handlers[regs->int_no] != 0) {
    isr_t handler = interrupt_handlers[regs->int_no];
    handler(regs);
  }
}
