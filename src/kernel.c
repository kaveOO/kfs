#include "kernel.h"
#include "types.h"

void kmain(void);

void WriteString(int colour, const char *string)
{
	char *video = (char *)0xB8000;

	while(*string)
	{
		*video++ = *string++;
		*video++ = colour;
	}
}

// TODO Scroll && cursor support

static inline void outb(uint16_t port, uint8_t val) // http://www.osdever.net/FreeVGA/vga/portidx.htm
{
    asm volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void kmain(void)
{
	WriteString(VGA_PURPLE, "42 This is mandatory");
	// disable_cursor();
	update_cursor(10, 0);
}
