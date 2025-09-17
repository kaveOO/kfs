#pragma once

#include "types.h"

void outb(uint16_t port, uint8_t val); // http://www.osdever.net/FreeVGA/vga/portidx.htm
uint8_t inb(uint16_t port);
