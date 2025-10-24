#ifndef IO_H
#define IO_H

#include "types.h"

void outb(uint16_t port, uint8_t val); // http://www.osdever.net/FreeVGA/vga/portidx.htm
uint8_t inb(uint16_t port);

#endif
