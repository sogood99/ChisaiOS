; Routine work
; Simply call the main_kernel function
; ensure we jump to the correct main function
[bits 32]
[extern kmain]

call kmain
jmp $ ; infinite loop, should not run
