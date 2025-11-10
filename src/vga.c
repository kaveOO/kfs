#include "vga.h"

unsigned char *vga		= VGA_ENTRY;
unsigned char *vga_end	= VGA_END;

t_screen save[10];
unsigned int current_screen = 0;
unsigned int g_cursor_col = 0;
unsigned int g_cursor_row = 0;

static unsigned int key_to_screen_entry(uint8_t key) {
	if (g_shift_down) {
		switch (key) {
			case 0x3B:
				return SCREEN_1; // F1
			case 0x3C:
				return SCREEN_2;
			case 0x3D:
				return SCREEN_3;
			case 0x3E:
				return SCREEN_4;
			case 0x3F:
				return SCREEN_5;
			case 0x40:
				return SCREEN_6;
			case 0x41:
				return SCREEN_7;
			case 0x42:
				return SCREEN_8;
			case 0x43:
				return SCREEN_9;
			case 0x44:
				return SCREEN_10;
			case 0x57:
				return SCREEN_11;
			case 0x58:
				return SCREEN_12; // F12
			default:
				return 42; // Error way,
		}
	}
	return 42;
}

static void save_screen_state() {
	unsigned char *vga_start = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		save[current_screen].buffer[i] = vga_start[i];
	}
}

static void load_screen(unsigned int screen) {
	unsigned char *vga_start = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		vga_start[i] = save[screen].buffer[i];
	}
	current_screen = screen;
	update_cursor(0, 0);
}

void screen_changer(uint8_t key) {
	unsigned int screen = key_to_screen_entry(key);
	(void) screen;
	if (screen != 42) {
		save_screen_state(); // Save actual screen
		load_screen(screen);
	}
}

void scroll_up() {
	for (int y = 1; y < VGA_HEIGHT; y++) {
		copy_line(y, y - 1);
	}

	clear_line(VGA_HEIGHT - 1);
	vga = VGA_ENTRY + ((VGA_HEIGHT - 1) * VGA_WIDTH * 2);
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
