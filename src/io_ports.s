; defines a symbol for outb
; which when called will send a byte to a corresponding address
global outb

; using cdecl calling standard
; void outb(uint16_t port, uint8_t data)
; esp + 8 => data
; esp + 4 => port
outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret
