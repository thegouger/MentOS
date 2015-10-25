#include "memcpy.h"

void memcpy(char* source, char* dest, int size)
{
    for(; size >= 0; size--)
        dest[size] = source[size];
}
