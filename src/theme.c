#include "theme.h"

void replace_vga_theme(unsigned int color) {
	unsigned char *vga_start = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		vga_start[1] = (unsigned char)color;
		vga_start += 2;
	}
}

static unsigned int translate_key_to_color(uint8_t key) {
	switch (key) {
		case 0x3B: return BLUE; // F1
		case 0x3C: return GREEN;
		case 0x3D: return CYAN;
		case 0x3E: return RED;
		case 0x3F: return PURPLE;
		case 0x40: return BROWN;
		case 0x41: return GRAY;
		case 0x42: return DARK_GRAY;
		case 0x43: return LIGHT_BLUE;
		case 0x44: return LIGHT_GREEN;
		case 0x57: return LIGHT_PURPLE;
		case 0x58: return YELLOW; // F12
		default: return 42; // Error way,
	}
}

void theme_changer(uint8_t key) {
	unsigned int color = translate_key_to_color(key);
	if (color != 42) {
		change_theme(color);
	}
}
