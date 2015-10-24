global loader                  ; entry symbol
extern kmain                   ; kmain symbol defined in kmain.cpp

MAGIC equ 0x1BADB002           ; magic number
FLAGS equ 0x0                  ; multiboot flags
CHECKSUM equ -(MAGIC + FLAGS)  ; checksum + magic + flags = 0

KERNEL_STACK_SIZE equ 4096     ; 4kb stack size

section .text    ; text section
align 4          ; 4 byte aligned
    dd MAGIC     ; write out magic, flags, checksum as machine code
    dd FLAGS
    dd CHECKSUM

loader:          ; entry label
    mov esp, kernel_stack + KERNEL_STACK_SIZE  ; set the stack pointer to the beginning of the stack
    call kmain ; call kernel main

section .bss    ; uninitialized data section
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE ; resb pseudo-instruction reserves memory
