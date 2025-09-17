#include "cursor.h"
#include "kernel.h"
#include "types.h"
#include "io.h"

void UpdateCursor()
{
	uint16_t pos = (video - VGA_ENTRY) / 2; // Calculte bytes from VGA entry

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t) (pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (uint8_t) ((pos >> 8) & 0xFF));
}
