#pragma once

#include <cstdint>

// we do a pushad dumping these registers to the stack in our common handler
struct CPU_Registers
{
    uint32_t eax;
    uint32_t ebx; 
    uint32_t ecx;
    uint32_t edx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
} __attribute__((packed));

// registers saved to stack when an interrupt happens
struct InterruptState
{
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed));
    
