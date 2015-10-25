#pragma once

#include <cstdint>

struct IDT_Entry
{
   uint16_t addr_l;
   uint16_t segment;
   uint16_t type;
   uint16_t addr_h;

   IDT_Entry() : addr_l(0x00),
                 segment(0x08), // kernel segment
                 type(0x8E00), // in memory handler, privilege level 0
                 addr_h(0x00)
   {
   }
} __attribute__((packed));

struct IDT_Desc
{
    uint16_t limit;
    uint32_t base;

    IDT_Desc() : limit(0x7F8),
                 base(0x00)
    {
    }
} __attribute__((packed));

extern "C"
{
    void load_idt(const IDT_Desc* tableDesc); // defined in interrupts.s
}

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

    static const uint8_t EOI = 0x20; // End of Interrupt

    static void init();
private:
    static void init_pic();
    static void pic_ack(unsigned int irq);
};

