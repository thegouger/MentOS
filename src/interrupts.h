#pragma once

#include <cstdint>
#include "cpu.h"

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

    IDT_Desc() : limit(0x7F8), // 256 IDT entries * 8 bytes
                 base(0x00)
    {
    }
} __attribute__((packed));

extern "C"
{
    // this is called from int.s
    void interrupt_handler(CPU_Registers reg, uint8_t interrupt_number, InterruptState state);
}

class Interrupts
{
public:
    /** PIC consts */
    static const uint16_t MASTER_PIC_COMMAND_PORT = 0x20; // Master PIC Initialization Command Word 1 IO Port
    static const uint16_t MASTER_PIC_DATA_PORT    = 0x21; // Master PIC Initialization Command Word 2 IO Port
    static const uint16_t SLAVE_PIC_COMMAND_PORT  = 0xA0; // Slave PIC Initialization Command Word 1 IO Port
    static const uint16_t SLAVE_PIC_DATA_PORT     = 0xA1; // Slave PIC Initialization Command Word 2 IO Port

    static const uint8_t PIC_ICW1 = 0x11;
    static const uint8_t PIC_ICW4 = 0x01;
    static const uint8_t MASTER_PIC_ICW2 = 0x20; // Master IRQs will trigger interrupts starting at vector 0x20
    static const uint8_t SLAVE_PIC_ICW2  = 0x70; // Slave IRQs will trigger interrupts starting at vector 0x70

    static const uint8_t MASTER_PIC_ICW3 = 0x04; // Tells Master there is a Slave on IRQ 2, the Cascade IRQ (0100)
    static const uint8_t SLAVE_PIC_ICW3  = 0x02; // Tells Slave its cascade identity (010)

    static const uint8_t MASTER_PIC_IRQ_MASK = 0xFC; // Master IRQ mask
    static const uint8_t SLAVE_PIC_IRQ_MASK  = 0xFF; // Slave IRQ mask

    static const uint8_t PIC_EOI = 0x20; // End of Interrupt

    /** PIT consts */
    static const uint16_t PIT_COMMAND_PORT = 0x43; // PIT command port
    static const uint8_t  PIT_CONFIG_BYTE  = 0x36; // Configures PIT for channel 0 interrupts
    static const uint16_t PIT_CH0_PORT     = 0x40; // PIT Channel 0 port
    static const uint16_t PIT_FREQ_WORD    = 0x2E9C; // Configues PIT for interrupt frequency of 100 Hz

    static void init();

    // send End of Interrupt to PIC for given IRQ
    static void pic_ack(unsigned int irq);
private:
    // init Programmable Interrupt Controller
    static void init_pic();

    // init Programmable Interval Timer
    static void init_pit();

    // methods to globally enable/disable interrupts
    static void enable_interrupts();
    static void disable_interrupts();
};
