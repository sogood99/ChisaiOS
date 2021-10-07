; Print function for debugging and stuff (in 32-b protected mode)
; VGA Layout: (row,col) address is 0xb8000 + 2*(row*80 + col)

[bits 32]

VIDEO_MEM equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
	; PARAM: ebx = string of printed string
	pusha
	mov edx, VIDEO_MEM

print_string_pm_loop:
	mov al, [ebx]
	mov ah, WHITE_ON_BLACK

	cmp al, 0 ; if ebx == 0 then at end of string
	je done

	mov [edx], ax ; store ax to video memory
	add ebx, 1 ; next char
	add edx, 2 ; next place in video memory

	jmp print_string_pm_loop

done:
	popa
	ret
