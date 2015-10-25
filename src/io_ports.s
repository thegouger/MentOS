; defines a symbol for outb
; which when called will send a byte to a corresponding address
global outb

; defines a symbol for inb
; which will return an input byte from a particular address
global inb

; using cdecl calling convention
; void outb(uint16_t port, uint8_t data)
; esp + 8 => data
; esp + 4 => port
outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

 ; using cdecl calling convention
 ; uint8_t inb(uint16_t port)
 ; esp + 4 => port
inb:
    mov dx, [esp + 4]
    in al, dx
    ret ; return value will be in eax (al => lower 8 bits of eax)
