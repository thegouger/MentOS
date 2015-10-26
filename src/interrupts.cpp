#include "interrupts.h"
#include "io_ports.h"
#include "framebuffer.h"
#include "memcpy.h"
#include "cpu.h"
#include "keyboard.h"

extern "C"
{
    void keyboard_handler(); // defined in int.s
    void load_idt(const IDT_Desc* tableDesc); // defined in interrupts.s
}

void Interrupts::init()
{
    IDT_Desc idt_desc;
    IDT_Entry IDT[256];

    IDT[0x21].addr_l = ((uint32_t) &keyboard_handler) & 0xFFFF;
    IDT[0x21].addr_h = (((uint32_t) &keyboard_handler) >> 16) & 0xFFFF;

    memcpy((char *)IDT, (char *)idt_desc.base, idt_desc.limit);

    load_idt(&idt_desc);
    init_pic();

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
    outb(MASTER_COMMAND_PORT, ICW1); 
    outb(SLAVE_COMMAND_PORT,  ICW1); 

    outb(MASTER_DATA_PORT, MASTER_ICW2); 
    outb(SLAVE_DATA_PORT,  SLAVE_ICW2); 

    outb(MASTER_DATA_PORT, MASTER_ICW3); 
    outb(SLAVE_DATA_PORT,  SLAVE_ICW3); 

    outb(MASTER_DATA_PORT, ICW4); 
    outb(SLAVE_DATA_PORT,  ICW4); 

    outb(MASTER_DATA_PORT, 0xFD); 
    outb(SLAVE_DATA_PORT,  0xFF); 
}

void Interrupts::pic_ack(unsigned int irq)
{
    // notify end of interrupt

    if(irq >= 8)
        outb(SLAVE_COMMAND_PORT, EOI);

    outb(MASTER_COMMAND_PORT, EOI);
}

void interrupt_handler(CPU_Registers /*r*/, uint8_t interrupt_number, InterruptState /*is*/)
{
    // handle interrupt
    switch(interrupt_number)
    {
        case 1:
            Keyboard::keyPressed();
            // send ack to PIC
            Interrupts::pic_ack(1);
            break;
        default:
            Framebuffer::write("unknown int");
            break;
    }
}
