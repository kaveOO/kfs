#include "io.h"
#include "types.h"

void outb(uint16_t port, uint8_t val) // http://www.osdever.net/FreeVGA/vga/portidx.htm
{
    asm volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

