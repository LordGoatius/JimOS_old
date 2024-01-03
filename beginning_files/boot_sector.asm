; infinite loop
loop:
    jmp loop

; fill with 0's
times 510-($-$$) db 0
; boot sector
dw 0xaa55
