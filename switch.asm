; Switch to 32 bit protected mode

[bits 16] ; tell assembler we are in 16 bit mode

switch_32_pm: ; switch to 32 bit protected mode
	cli ; bios goodbye
	lgdt [gdt_descriptor] ; load global descriptor

	mov eax, cr0 ; set first bit of cr0 to 1
	or eax, 0x1
	mov cr0, eax

	jmp CODE_SEG:init ; make far jump so cpu flushes future code as to not have weird stuff happen

[bits 32] ; tell assembler we are in 32 bit mode

init:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000 ; set stack pointers
	mov esp, ebp
	
	call begin_pm
