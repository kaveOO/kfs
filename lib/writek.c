#include "lib.h"

static void scroll_up()
{
	unsigned char *last_row_start = VGA_ENTRY + ((VGA_HEIGHT - 1) * VGA_WIDTH * 2);

	for (int y = 1; y < VGA_HEIGHT; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
            unsigned char *src = VGA_ENTRY + (y * VGA_WIDTH + x) * 2;
            unsigned char *dst = VGA_ENTRY + ((y - 1) * VGA_WIDTH + x) * 2;
            dst[0] = src[0]; // Character
            dst[1] = src[1]; // Color
		}
	}

	for (int x = 0; x < VGA_WIDTH; x++) {
		last_row_start[x * 2] = ' ';
		last_row_start[x * 2] = BLACK;
	}
	vga = VGA_ENTRY + ((VGA_HEIGHT - 1) * VGA_WIDTH * 2); // Cursor on the start of last line
}

static int format_handler(int c)
{
	switch (c) {
		case '\n':
			vga += (VGA_LINE) - ((vga - VGA_ENTRY) % (VGA_LINE));
			return 1;
		case '\t':
			vga += 8;
			return 1;
		case '\b':
			if (vga > VGA_ENTRY) ERASE_CHAR(vga);
			return 1;
		case '\a':
			beep();
			return 1;
		case '\r':
			vga -= (vga - VGA_ENTRY);
			return 1;
		case '\v':
			vga += VGA_LINE;
			return 1;
	}
	return 0;
}

int writek(int c, int len, unsigned int color) {
	for (int i = 0; i < len; i++) {
		if (format_handler(c)) continue;
		if (vga == vga_end) scroll_up();
		*vga++ = (unsigned char)c;
		*vga++ = (unsigned char)color;
	}
	move_cursor();
	return len;
}
