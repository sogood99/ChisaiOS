; Enter 32 bit protected mode

[org 0x7c00] ; boot sector starts in 0x7c00

KERNEL_OFFESET equ 0x1000 ; where we defined the kernel main function to be located

mov bp, 0x9000 ; lol 16 bit stuff (sets a stack)
call switch_32_pm ; enters 32 bit mode and jumps to begin_pm

%include "switch.asm"
%include "gdt.asm"
%include "print/print.asm"

[bits 32]

begin_pm:
	mov bx, MSG_32_BIT
	call print_string_pm
	jmp $ ; infinite loop

; constants
MSG_32_BIT db "Sucessfully loaded 32-bit Protected Mode", 0

; for booting
times 510 - ($-$$) db 0
dw 0xaa55
