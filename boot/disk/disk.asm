; Load DH sectors to ES:BX from drive DL
; if load size < dx or read error print out error
disk_load:
	pusha

	push dx 

	mov ah, 0x02 ; Read
	mov al, dh ; DH sectors
	mov ch, 0x00 ; cylinder 0
	mov dh, 0x00 ; head 0
	mov cl, 0x02 ; start from 2nd sector

	int 0x13 ; bios interrupt read

	; error detection

	jc disk_error ; if read error bios sets carry flag = true

	pop dx
	cmp dh, al
	jne sector_not_fully_read ; if actual readed sector ( = al ) != dh, error

	popa

	ret ; else
disk_error:
	mov bx, DISK_ERROR_MSG
	call print_bios
	jmp $ ; do nothing

sector_not_fully_read:
	mov bx, SECTOR_NOT_READ_MSG
	call print_bios
	jmp $

DISK_ERROR_MSG db "Disk Read Error", 0
SECTOR_NOT_READ_MSG db "Sector not fully read", 0
