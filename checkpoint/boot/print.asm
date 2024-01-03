print:
    pusha

start:
    mov al, [bx] ; bx is string base address
    cmp al, 0    ; check if byte is null
    je done      ; finish if it is

    ; printing part
    mov ah, 0x0e
    int 0x10

    ; increment i and loop again
    add bx, 1
    jmp start

done:
    popa
    ret

print_nl:
    pusha

    mov ah, 0x0e

    mov al, 0x0a
    int 0x10
    mov al, 0x0d
    int 0x10

    popa
    ret
