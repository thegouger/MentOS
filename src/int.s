; defines a symbol for load_idt
; which loads the idt into IDTR
global load_idt

; void load_idt(IDT_Desc* tableDesc)
; esp + 4 => tableDesc
load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret

; interrupt handlers
extern interrupt_handler
global systick_handler
global keyboard_handler

systick_handler:
    push dword 0 ; push interrupt number
    jmp common_handler

keyboard_handler:
    push dword 1 ; push interrupt number
    jmp common_handler

common_handler:
    pushad ; push all general purpose registers
    call interrupt_handler
    popad  ; restore all general purpose registers
    add esp, 4 ; move stack pointer up by 4 (to reverse pushing interrupt number)
    iret
