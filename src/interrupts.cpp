#include "interrupts.h"
#include "io_ports.h"
#include "framebuffer.h"
#include "memcpy.h"
#include "cpu.h"
#include "keyboard.h"

extern "C"
{
    void systick_handler();  // defined in int.s
    void keyboard_handler(); // defined in int.s
    void load_idt(const IDT_Desc* tableDesc); // defined in int.s
}

void Interrupts::init()
{
    IDT_Desc idt_desc;
    IDT_Entry IDT[256];

    // systick handler located at vector 0x20
    IDT[0x20].addr_l = ((uint32_t) &systick_handler) & 0xFFFF;
    IDT[0x20].addr_h = (((uint32_t) &systick_handler) >> 16) & 0xFFFF;

    // keyboard handler located at vector 0x21
    IDT[0x21].addr_l = ((uint32_t) &keyboard_handler) & 0xFFFF;
    IDT[0x21].addr_h = (((uint32_t) &keyboard_handler) >> 16) & 0xFFFF;

    memcpy((char *)IDT, (char *)idt_desc.base, idt_desc.limit);

    load_idt(&idt_desc);
    init_pic();
    init_pit();

    enable_interrupts();
}

void Interrupts::enable_interrupts()
{
    __asm__("sti");
}

void Interrupts::disable_interrupts()
{
    __asm__("cli");
}

void Interrupts::init_pic()
{
    // send first initialization command word
    outb(MASTER_PIC_COMMAND_PORT, PIC_ICW1); 
    outb(SLAVE_PIC_COMMAND_PORT,  PIC_ICW1); 

    // set IRQ->IDT vector offset
    outb(MASTER_PIC_DATA_PORT, MASTER_PIC_ICW2); 
    outb(SLAVE_PIC_DATA_PORT,  SLAVE_PIC_ICW2); 

    // set Master/Slave cascade setup
    outb(MASTER_PIC_DATA_PORT, MASTER_PIC_ICW3); 
    outb(SLAVE_PIC_DATA_PORT,  SLAVE_PIC_ICW3); 

    // Set mode
    outb(MASTER_PIC_DATA_PORT, PIC_ICW4); 
    outb(SLAVE_PIC_DATA_PORT,  PIC_ICW4); 

    // Only allow timer and keyboard IRQs
    outb(MASTER_PIC_DATA_PORT, MASTER_PIC_IRQ_MASK); 
    outb(SLAVE_PIC_DATA_PORT,  SLAVE_PIC_IRQ_MASK); 
}

void Interrupts::init_pit()
{
    outb(PIT_COMMAND_PORT, PIT_CONFIG_BYTE);
    outb(PIT_CH0_PORT, PIT_FREQ_WORD & 0xFF);
    outb(PIT_CH0_PORT, (PIT_FREQ_WORD & 0xFF00) >> 8);
}

void Interrupts::pic_ack(unsigned int irq)
{
    // notify end of interrupt
    if(irq >= 8)
        outb(SLAVE_PIC_COMMAND_PORT, PIC_EOI);

    outb(MASTER_PIC_COMMAND_PORT, PIC_EOI);
}

void interrupt_handler(CPU_Registers /*r*/, uint8_t interrupt_number, InterruptState /*is*/)
{
    // handle interrupt
    switch(interrupt_number)
    {
        case 0:
            Interrupts::pic_ack(0);
            break;
        case 1:
            Keyboard::keyPressed();
            // send ack to PIC
            Interrupts::pic_ack(1);
            break;
        default:
            break;
    }
}
