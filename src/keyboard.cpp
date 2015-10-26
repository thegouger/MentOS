#include "keyboard.h"
#include "framebuffer.h"
#include "io_ports.h"

void Keyboard::keyPressed()
{
    /*uint8_t scan_code =*/ inb(KEYBOARD_PORT);
    Framebuffer::write("LOL");
}
