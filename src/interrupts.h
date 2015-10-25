#pragma once

#include <cstdint>

struct IDT_Entry
{
   uint16_t addr_h;
   uint16_t type;
   uint16_t segment;
   uint16_t addr_l;

   IDT_Entry() : type(0x8300), // in memory handler, privilege level 0
                 segment(0x08) // kernel segment
   {
   }
} __attribute__((packed));

class Interrupts
{
public:
    static const uint16_t MASTER_COMMAND_PORT = 0x20; // Master PIC Initialization Command Word 1 IO Port
    static const uint16_t MASTER_DATA_PORT = 0x21; // Master PIC Initialization Command Word 2 IO Port
    static const uint16_t SLAVE_COMMAND_PORT  = 0xA0; // Slave PIC Initialization Command Word 1 IO Port
    static const uint16_t SLAVE_DATA_PORT  = 0xA1; // Slave PIC Initialization Command Word 2 IO Port

    static const uint8_t ICW1 = 0x11;
    static const uint8_t ICW4 = 0x01;
    static const uint8_t MASTER_ICW2 = 0x20; // Master IRQs will trigger interrupts starting at vector 0x20
    static const uint8_t SLAVE_ICW2  = 0x70; // Slave IRQs will trigger interrupts starting at vector 0x70

    static const uint8_t MASTER_ICW3 = 0x04; // Tells Master there is a Slave on IRQ 2, the Cascade IRQ (0100)
    static const uint8_t SLAVE_ICW3  = 0x02; // Tells Slave its cascade identity (010)

    static void init();
private:
    static void init_pic();
    static IDT_Entry const _IDT[256];
};
