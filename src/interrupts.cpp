#include "interrupts.h"
#include "io_ports.h"
#include "framebuffer.h"
#include "memcpy.h"

void Interrupts::init()
{
    IDT_Desc idt_desc;
    IDT_Entry IDT[256];

    memcpy((char *)IDT, (char *)idt_desc.base, idt_desc.limit);

    load_idt(&idt_desc);
    init_pic();
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
}

void Interrupts::pic_ack(unsigned int irq)
{
    if(irq >= 8)
        outb(SLAVE_COMMAND_PORT, EOI);

    outb(MASTER_COMMAND_PORT, EOI);
}
