; defines a symbol for load_idt
; which loads the idt into IDTR
global load_idt

; void load_idt(IDT_Desc* tableDesc)
; esp + 4 => tableDesc
load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret

; handler macros
%macro handler 1
global handler_%1

handler_%1:
    push dword %1 ; push interrupt number
    jmp common_handler
%endmacro

extern interrupt_handler

common_handler:
    pushad ; push all general purpose registers
    call interrupt_handler
    popad  ; restore all general purpose registers
    add esp, 4 ; move stack pointer up by 4 (to reverse pushing interrupt number)
    iret

handler 1 ; keyboard handler
