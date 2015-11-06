#include "framebuffer.h"
#include "io_ports.h"

char* const Framebuffer::FRAMEBUFFER_LOCATION = (char*)0xB8000;
const int Framebuffer::FRAMEBUFFER_ROWS = 25;
const int Framebuffer::FRAMEBUFFER_COLS = 80;
const int Framebuffer::CURSOR_LOCATION_H_IDX = 0x0E;
const int Framebuffer::CURSOR_LOCATION_L_IDX = 0x0F;
const int Framebuffer::ADDR_REGISTER = 0x3D4;
const int Framebuffer::DATA_REGISTER = 0x3D5;

uint16_t Framebuffer::_cursorPos = 0;

void Framebuffer::writeCell(unsigned int pos, char c, uint8_t colour)
{
    if(pos > FRAMEBUFFER_ROWS * (FRAMEBUFFER_COLS - 1)) // pos out of range
        return;
    
    auto fb = FRAMEBUFFER_LOCATION;
    fb[pos << 1] = c;
    fb[(pos << 1) + 1]  = colour;
}

void Framebuffer::write(char c, uint8_t colour)
{
    if(c == '\n')
    {
        _cursorPos = (_cursorPos + FRAMEBUFFER_COLS) / FRAMEBUFFER_COLS * FRAMEBUFFER_COLS;
        moveCursor(_cursorPos);
        return;
    }
    writeCell(_cursorPos, c, colour);
    moveCursor(++_cursorPos);
}

void Framebuffer::write(char const* str, uint8_t colour)
{
    if(!str) 
        return;

    auto chr = str;

    while(*chr)
    {
        if(*chr == '\n')
        {
            _cursorPos = (_cursorPos + FRAMEBUFFER_COLS) / FRAMEBUFFER_COLS * FRAMEBUFFER_COLS;
            moveCursor(_cursorPos);
            chr++;
            continue;
        }
        writeCell(_cursorPos, *chr, colour);
        _cursorPos++;
        chr++;
    }

    moveCursor(_cursorPos);
}

void Framebuffer::moveCursor(uint16_t pos)
{
    if(pos > FRAMEBUFFER_ROWS * (FRAMEBUFFER_COLS - 1)) // pos out of range
        return;

    _cursorPos = pos;

    outb(ADDR_REGISTER, CURSOR_LOCATION_H_IDX);
    outb(DATA_REGISTER, (pos >> 8) & 0xFF);

    outb(ADDR_REGISTER, CURSOR_LOCATION_L_IDX);
    outb(DATA_REGISTER, pos & 0xFF);
}

void Framebuffer::clear()
{
    for(auto rowIdx = 0; rowIdx < FRAMEBUFFER_ROWS; rowIdx++)
        for(auto colIdx = 0; colIdx < FRAMEBUFFER_COLS; colIdx++)
            writeCell(rowIdx*FRAMEBUFFER_COLS + colIdx, '\0');
    
    moveCursor(_cursorPos = 0);
}
