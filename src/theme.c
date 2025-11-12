#include "theme.h"

unsigned int g_color = 42;

void replace_vga_theme(unsigned int color) {
	unsigned char *vga_start = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		vga_start[1] = (unsigned char)color;
		vga_start += 2;
	}
}

static bool get_theme_from_key(uint8_t key, unsigned int *theme_out) {
	if (!g_shift_down && key < sizeof(f_keys_to_int)) {
		uint8_t theme = f_keys_to_int[key];
		if (theme > 0 && theme <= 12) {
			*theme_out = theme;
			return true;
		}
	}
	return false;
}

void theme_changer(uint8_t key) {
	unsigned int theme;
	if (get_theme_from_key(key, &theme)) {
		replace_vga_theme(theme);
		g_screens[g_current_screen].theme = theme;
		g_color = theme;
	}
}
