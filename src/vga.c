#include "vga.h"

unsigned char *vga		= VGA_ENTRY;
unsigned char *vga_end	= VGA_END;


// TODO Move scroll function from writek here and rework it
void scroll_up() {


}


// TODO make sure that cursor is properly updated (having doubts)
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
		ERASE_CHAR(screen_entry);
		screen_entry += 2;
	}
	update_cursor(0, 0);
}

void clear_line(int line) {
	unsigned char *line_entry = VGA_ENTRY + line * VGA_LINE;

	for (int i = 0; i < VGA_WIDTH; i++) {
		ERASE_CHAR(line_entry);
		line_entry += 2;
	}
}

static void init_header() {
	printk(PURPLE, "\t\t\t\t\t\t   _     __       _  _ ___\n");
	printk(PURPLE, "\t\t\t\t\t\t  | |   / _|     | || |__ \\\n");
	printk(PURPLE, "\t\t\t\t\t\t  | | _| |_ ___  | || |_ ) |\n");
	printk(PURPLE, "\t\t\t\t\t\t  | |/ /  _/ __| |__   _/ /\n");
	printk(PURPLE, "\t\t\t\t\t\t  |   <| | \\__ \\    | |/ /_\n");
	printk(PURPLE, "\t\t\t\t\t\t  |_|\\_\\_| |___/    |_|____|\n\n");

	printk(CYAN, "\t\t\t\t   Made by kaveO - https://github.com/kaveOO\n\n");
}

void vga_init() {
	#if HEADER == true
		init_header();
	#endif
}
