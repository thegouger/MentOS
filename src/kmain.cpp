#include "kmain.h"
#include "framebuffer.h"

void kmain()
{
    Framebuffer::clear();

    Framebuffer::write("Hello World");

    while(1);
}
