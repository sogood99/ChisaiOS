#include "isr.h"
#include "../drivers/screen.h"
#include "../utils/types.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs) { kprint("recieved interrupt\n"); }
