; GDT: basic flat model
; check gdt segment descriptor stucture for more detail

gdt_start:

gdt_null: ; 8 bytes of null descriptor
	dd 0x0
	dd 0x0

gdt_code: ; data segment descriptor
	dw 0xffff ; lower 16 bit of the limit
	dw 0x0 ; lower 16 bit of the base
	db 0x0 ; midde 16 bit of the base
	db 10011010b ; access flags
	db 11001111b ; granularity
	db 0x0 ; upper 16 bit of the base

gdt_data: ; data segment, basically the same as code (execpt for flags)
	dw 0xffff ; limit
	dw 0x0 ; base
	db 0x0 ; base
	db 10010010b ; flags
	db 11001111b ; flags
	db 0x0

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start

; Useful constants  
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
