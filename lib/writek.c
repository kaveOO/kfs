#include "lib.h"

static void vga_scrolling()
{
	unsigned char *last_row_start = VGA_ENTRY + ((HEIGHT - 1) * WIDTH * 2);

	for (int y = 1; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
            unsigned char *src = VGA_ENTRY + (y * WIDTH + x) * 2;
            unsigned char *dst = VGA_ENTRY + ((y - 1) * WIDTH + x) * 2;
            dst[0] = src[0]; // Character
            dst[1] = src[1]; // Color
		}
	}

	for (int x = 0; x < WIDTH; x++) {
		last_row_start[x * 2] = ' ';
		last_row_start[x * 2] = BLACK;
	}
	video = VGA_ENTRY + ((HEIGHT - 1) * WIDTH * 2); // Cursor on the start of last line
}

static int format_handler(int c)
{
	switch (c) {
		case '\n':
			video += (VGA_LINE) - ((video - VGA_ENTRY) % (VGA_LINE));
			return 1;
		case '\t':
			video += 4;
			return 1;
		case '\b':
			if (video > VGA_ENTRY) {
				video -= 2;
				*video = ' ';
				*(video + 1) = 7;
			}
			return 1;
		case '\a':
			beep();
			return 1;
		case '\r':
			video -= (video - VGA_ENTRY);
			return 1;
		case '\v':
			video += VGA_LINE;
			return 1;
	}
	return 0;
}

int writek(int c, unsigned int len, unsigned int color) {
	for (int i = 0; i < len; i++) {
		if (format_handler(c))
			continue;
		if (video == end)
			vga_scrolling();
		*video++ = c;
		*video++ = color;
	}
	UpdateCursor();
	return (len);
}
