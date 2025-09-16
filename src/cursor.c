#include "cursor.h"
#include "kernel.h"
#include "types.h"
#include "io.h"

void UpdateCursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t) (pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (uint8_t) ((pos >> 8) & 0xFF));
}
