print_hex:
    pusha

    mov cx, 0

; convert hex to ascii
; '0'-'9' add 0x30
; 'A'-'F' add 0x40
hex_loop:
    cmp cx, 4 ; loop 4 times
    je end

    ; step 1: convert last char of dx to ascii
    mov ax, dx
    and ax, 0x000f
    add al, 0x30
    cmp al, 0x39 ; if > 9 add another 8 for 'A'-'F'
    jle step2
    add al, 7

step2:
    ; get position of string so we can place the ASCII char
    ; bx <- base address + string length - index of char
    mov bx, HEX_OUT + 5
    sub bx, cx
    mov [bx], al
    ror dx, 4

    ; increment and loop
    add cx, 1
    jmp hex_loop

end:
    mov bx, HEX_OUT
    call print

    popa
    ret

HEX_OUT:
    db '0x0000',0
