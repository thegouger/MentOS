#include "kmain.h"
#include "interrupts.h"
#include "framebuffer.h"
#include "itoa.h"

void kmain()
{
    Framebuffer::clear();

    Framebuffer::write("Initializing Interrupts\n");
    Interrupts::init();

    Framebuffer::write("Booted successfully\n");


    while(1);
}
