#include "cursor.h"

// Cursor is moving following the video memory
void move_cursor() {
	int	pos = ((vga - VGA_ENTRY) / 2); // Calculte bytes from VGA entry

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t) (pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (uint8_t) ((pos >> 8) & 0xFF));
}

void update_cursor(int row, int col) {
	int	pos = ((row * VGA_WIDTH) + col);

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t)(pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (uint8_t)((pos >> 8) & 0xFF));
}
