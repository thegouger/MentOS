#include "kmain.h"
#include "interrupts.h"
#include "framebuffer.h"

void kmain()
{
    Framebuffer::clear();

    Interrupts::init();

    Framebuffer::write("Hello World");

    while(1);
}
