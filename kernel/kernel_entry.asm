; Routine work
; Simply call the main_kernel function
; ensure we jump to the correct main function
[bits 32]
[extern main_kernel]

call main_kernel
jmp $ ; infinite loop
