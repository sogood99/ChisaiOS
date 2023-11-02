#include "timer.h"
#include "../cpu/isr.h"
#include "ports.h"
#include "screen.h"

static void timer_callback(registers_t *regs) {}

void init_timer(uint32_t freq) {
  register_interrupt_handler(IRQ0, timer_callback);

  uint32_t divisor = 1193180 / freq;

  // Send the command byte.
  port_byte_out(0x43, 0x36);

  // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
  uint8_t l = LO_8(divisor);
  uint8_t h = HI_8(divisor);

  // Send the frequency divisor.
  port_byte_out(0x40, l);
  port_byte_out(0x40, h);
}
