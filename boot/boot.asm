; Enter 32 bit protected mode

[org 0x7c00] ; boot sector starts in 0x7c00

KERNEL_OFFESET equ 0x1000 ; where we defined the kernel main function to be located

	mov [BOOT_DRIVE], dl ; initallly dl = disk # of boot drive

	mov bp, 0xf000 ; lol 16 bit stuff (sets a stack)

	mov bx, MSG_16_BIT ; print success message from bios
	call print_bios

	call load_kernel

	call switch_32_pm ; enters 32 bit mode and jumps to begin_pm

; pure 16bit land
%include "./boot/print/print_bios.asm"
%include "./boot/disk/disk.asm"

load_kernel:
	; load kernel to memory
	mov bx , KERNEL_OFFESET ; load stuff from disk to KERNEL_OFFESET in mem
	mov dh , 0x20 ; size of 31 sectors ( 14 MB should be enough )
	mov dl , [BOOT_DRIVE] ; drive = boot drive
	call disk_load

	mov bx, MSG_LOAD_KERNEL
	call print_bios	
	ret

; might be contaminated with 32bit stuff
%include "./boot/switch.asm"
%include "./boot/gdt.asm"
%include "./boot/print/print.asm"

[bits 32]

begin_pm:
	mov bx, MSG_32_BIT
	call print_string_pm

	call KERNEL_OFFESET ; call the kernel

	jmp $ ; infinite loop ( doesnt actually get called )

; constants
BOOT_DRIVE db 0

MSG_LOAD_KERNEL db "Successfully loaded Kernel", 0
MSG_16_BIT db "Successfully loaded 16-bit Mode", 0
MSG_32_BIT db "Sucessfully loaded 32-bit Protected Mode", 0

; for booting
times 510 - ($-$$) db 0
dw 0xaa55 ; magic number

