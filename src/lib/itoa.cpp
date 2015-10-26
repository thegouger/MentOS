#include "itoa.h"

void itoa(char* buf, unsigned int num, int base)
{
    if(!buf) 
        return;

    if(base != 2 && base != 8 && base != 10 && base != 16)
    {
        buf[0] = '\0';
        return;
    }

    int digit = 0;
    buf[digit++] = '\0';

    while(num)
    {
        buf[digit++] = num % base > 9 ? (num % base - 10) + 'A' : num % base + '0';
        num /= base;
    }

    digit--;

    for(int i = 0; digit > i; digit--, i++)
    {
        char tmp = buf[digit];
        buf[digit] = buf[i];
        buf[i] = tmp;
    }
    
}
