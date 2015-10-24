#pragma once

#include <cstdint>

class Framebuffer
{
public:
    static char* const FRAMEBUFFER_LOCATION;
    static const int FRAMEBUFFER_ROWS;
    static const int FRAMEBUFFER_COLS;
    static const int CURSOR_LOCATION_H_IDX;
    static const int CURSOR_LOCATION_L_IDX;
    static const int ADDR_REGISTER;
    static const int DATA_REGISTER;
    
    // clear the framebuffer
    static void clear();

    // writes a character at the current cursor location to the framebuffer
    static void write(char c, uint8_t colour = 0x0F);

    // writes a string starting at the current cursor location to the framebuffer
    static void write(char const* str, uint8_t colour = 0x0F);

    // move cursor to a position
    static void moveCursor(uint16_t pos);

private:
    static uint16_t _cursorPos;

    // write a character to a position in the framebuffer
    static void writeCell(unsigned int position, char c, uint8_t colour = 0x0F);
};
