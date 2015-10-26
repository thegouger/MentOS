#include "keyboard.h"
#include "framebuffer.h"
#include "io_ports.h"
#include "itoa.h"

void Keyboard::keyPressed()
{
    uint8_t scan_code = inb(KEYBOARD_PORT);

    char buf[32];
    itoa(buf, scan_code, 16);
    Framebuffer::write(buf);
    Framebuffer::write(' ');
}
