#include "lib.h"

static int format_handler(int c)
{
	switch (c) {
		case '\n':
			vga += (VGA_LINE) - ((vga - VGA_ENTRY) % (VGA_LINE));
			if (vga >= vga_end) {
				scroll_up();
			}
			return 1;
		case '\t':
			vga += 8;
			return 1;
		case '\b':
			vga -= 2;
			*vga++ = ' ';
			*vga++ = GRAY;
			vga -= 2;
			move_cursor();
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
		if (format_handler(c)) {
			continue;
		}
		if (vga >= vga_end) {
			scroll_up();
		}
		*vga++ = (unsigned char)c;
		*vga++ = (unsigned char)color;
	}
	move_cursor();
	return len;
}
