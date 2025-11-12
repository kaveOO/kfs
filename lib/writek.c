#include "lib.h"

static int format_handler(int c)
{
	switch (c) {
		case '\n':
			g_vga += (VGA_LINE) - ((g_vga - VGA_ENTRY) % (VGA_LINE));
			if (g_vga >= vga_end) {
				scroll_up();
			}
			if (get_cursor_y() >= 11) {
				printk(RED, "> ");
			}
			return 1;
		case '\t':
			if (get_cursor_x() > 76) {
				scroll_up();
			}
			g_vga += 8;
			return 1;
		case '\b':
			if (get_cursor_x() <= 2) {
				return 1;
			}
			g_vga -= 2;
			BLANK_CELL(g_vga);
			return 1;
		case '\a':
			beep();
			return 1;
		case '\r':
			g_vga -= (g_vga - VGA_ENTRY);
			return 1;
		case '\v':
			g_vga += VGA_LINE;
			return 1;
	}
	return 0;
}

int writek(int c, int len, unsigned int color) {
	if (g_color != 42) {
		color = g_color;
	}
	for (int i = 0; i < len; i++) {
		if (format_handler(c)) {
			continue;
		}
		if (g_vga >= vga_end) {
			scroll_up();
		}
		if (*g_vga != ' ' && !g_insert_on) {
			shift_chars_right(g_vga);
		}
		*g_vga++ = (unsigned char)c;
		*g_vga++ = (unsigned char)color;
	}
	move_cursor();
	return len;
}
