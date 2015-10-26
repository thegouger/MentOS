#pragma once

#include <cstdint>

class Keyboard
{
public:
    static const uint16_t KEYBOARD_PORT = 0x60;
    static void keyPressed();
};
