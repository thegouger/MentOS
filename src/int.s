; defines a symbol for load_idt
; which loads the idt into IDTR
global load_idt

; void load_idt(IDT_Desc* tableDesc)
; esp + 4 => tableDesc
load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret
    
