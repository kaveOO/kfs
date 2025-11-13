#include "vga.h"

unsigned char *g_vga	= VGA_ENTRY;
unsigned char *vga_end	= VGA_END;

void scroll_up() {
	for (int y = 12; y < VGA_HEIGHT; y++) {
		copy_line(y, y - 1);
	}

	clear_line(VGA_HEIGHT - 1);
	g_vga = VGA_ENTRY + ((VGA_HEIGHT - 1) * VGA_WIDTH * 2);
}

void copy_line(int src, int dest) {
	unsigned char *src_entry = VGA_ENTRY + src * VGA_LINE;
	unsigned char *dest_entry = VGA_ENTRY + dest * VGA_LINE;

	for (int i = 0; i < VGA_WIDTH; i++) {
		COPY_CHAR(src_entry, dest_entry);
		src_entry += 2;
		dest_entry += 2;
	}
	update_cursor(dest + 1, 0);
}

void clear_screen() {
	unsigned char *screen_entry = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		BLANK_CELL(screen_entry);
		screen_entry += 2;
	}
	update_cursor(0, 0);
}

void clear_line(int line) {
	unsigned char *line_entry = VGA_ENTRY + line * VGA_LINE;

	for (int i = 0; i < VGA_WIDTH; i++) {
		BLANK_CELL(line_entry);
		line_entry += 2;
	}
}

void shift_chars_right(unsigned char *pos) {
	unsigned char *line_start = VGA_ENTRY + ((pos - VGA_ENTRY) / VGA_LINE) * VGA_LINE;
	unsigned char *line_end = line_start + VGA_LINE - 2;

	unsigned char *last_char = line_end;
	while (last_char >= pos && last_char[0] == ' ') {
		last_char -= 2;
	}

	if (last_char >= pos) {
		unsigned char *src = last_char;
		unsigned char *dest = last_char + 2;

		if (dest > line_end) {
			dest = line_end;
			src = line_end - 2;
		}

		while (src >= pos) {
			if (dest <= line_end) {
				COPY_CHAR(src, dest);
			}
			src -= 2;
			dest -= 2;
		}
	}
}

void init_header() {
	printk(RED, "\n\t\t\t\t\t\t\t\t[ Screen %d/12 ]\n", g_current_screen);

	printk(PURPLE, "\t\t\t\t\t\t   _	 __	   _  _ ___\n");
	printk(PURPLE, "\t\t\t\t\t\t  | |   / _|	 | || |__ \\\n");
	printk(PURPLE, "\t\t\t\t\t\t  | | _| |_ ___  | || |_ ) |\n");
	printk(PURPLE, "\t\t\t\t\t\t  | |/ /  _/ __| |__   _/ /\n");
	printk(PURPLE, "\t\t\t\t\t\t  |   <| | \\__ \\	| |/ /_\n");
	printk(PURPLE, "\t\t\t\t\t\t  |_|\\_\\_| |___/	|_|____|\n\n");

	printk(CYAN, "\t\t\t\t   Made by kaveO - https://github.com/kaveOO\n\n");

	printk(RED, "> ");
}

void vga_init() {
	init_header();
	init_screens();
}
