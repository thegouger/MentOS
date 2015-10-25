#include "interrupts.h"
#include "io_ports.h"

IDT_Entry const Interrupts::_IDT[256] = {};

void Interrupts::init()
{
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
