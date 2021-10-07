; print string starting from bx
; uses bios interupts
print_bios:
	pusha

loop:
	; al is also whwere BIOS looks with interupt pring
	mov al, [bx]
	cmp al, 0
	je done_print ; if string[i] == 0
	; else

	; print with BIOS interupt
	mov ah, 0x0e
	int 0x10
	add bx, 1
	jmp loop	

done_print:
	popa
	ret
